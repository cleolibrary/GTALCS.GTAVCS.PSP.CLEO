#pragma once
#include "common.h"
#include "utils.h"
#include "../external/injector/include/psp/hooks_guest.h"
#include "../external/injector/include/psp/patches.h"
#include "../external/injector/include/psp/memalloc.h"
#include "../external/injector/include/psp/game_abi.hpp"

// Prepared once per module; code and handles live in this plugin's reservation.
namespace guest_hooks {
inline psp_hook_guest storage;
inline psp_hook_backend backend;
inline bool initialized;
inline uint32_t function_hooks, call_patches;
inline psp::GameCallbacks callbacks;
inline void require(bool success, const char* operation)
{
    if (!success) { utils::log("CLEO hook failure: %s", operation); __builtin_trap(); }
}
inline void initialize()
{
    if (initialized) return;
    auto status = psp_hook_guest_backend(&backend, &storage, psp_mem_storage_begin(), psp_mem_storage_size(), AllocMemBlock, FreeMemBlock);
    if (status != PSP_HOOK_OK)
        utils::log("CLEO hook backend: status %d, pool %08lX, bytes %lu", (int)status,
            (unsigned long)psp_mem_storage_begin(), (unsigned long)psp_mem_storage_size());
    require(status == PSP_HOOK_OK, "backend");
    initialized = true;
}
template<class Function> inline ptr bridge(Function function) {
    // The public CLEO plugin API also accepts erased raw stubs. Their stack
    // layout is owned by that plugin; keep its established native ABI contract.
    if constexpr (!std::is_function_v<std::remove_pointer_t<Function>>) return cast<ptr>(function);
    else {
        initialize();
        uint32_t entry=0;
        require(callbacks.bind(backend,function,entry)==PSP_HOOK_OK,"game callback ABI");
        return cast<ptr>(entry);
    }
}
inline void replace_call(ptr address, ptr target)
{
    initialize();
    psp_patch patch = {};
    require(psp_patch_create_call(&patch, &backend, (uint32_t)(uintptr_t)address,
        (uint32_t)(uintptr_t)target) == PSP_HOOK_OK, "prepare call");
    require(psp_patch_enable(&patch) == PSP_HOOK_OK, "publish call");
    ++call_patches;
    // Permanent legacy call patch: no code allocation or destructor needed.
}
inline void hook_function(ptr address, uint32_t bytes, ptr target, ptr* original)
{
    initialize();
    require(original && bytes >= 8 && !(bytes & 3) && bytes <= PSP_HOOK_MAX_INSTRUCTIONS * 4, "prologue size");
    auto* hook = static_cast<psp_hook*>(AllocMemBlock(sizeof(psp_hook)));
    require(hook != nullptr, "handle allocation");
    memset(hook, 0, sizeof(*hook));
    auto status = psp_hook_create_inline(hook, &backend, (uint32_t)(uintptr_t)address,
        (uint32_t)(uintptr_t)target, bytes / 4);
    if (status != PSP_HOOK_OK) { FreeMemBlock(hook); require(false, "relocate prologue"); }
    // The callback may run as soon as the entry patch is published.
    *original = (ptr)(uintptr_t)hook->trampoline;
    status = psp_hook_enable(hook);
    if (status != PSP_HOOK_OK) {
        *original = nullptr;
        (void)psp_hook_destroy(hook); FreeMemBlock(hook);
        require(false, "publish hook");
    }
    ++function_hooks;
    // Permanent legacy function hook: retain its handle and original trampoline.
}
inline void write_code(ptr address, const uint32_t* words, size_t bytes)
{
    initialize();
    require(backend.write(backend.user, (uint32_t)(uintptr_t)address, words, bytes) != 0, "write code");
    backend.flush(backend.user, (uint32_t)(uintptr_t)address, bytes);
}
}
