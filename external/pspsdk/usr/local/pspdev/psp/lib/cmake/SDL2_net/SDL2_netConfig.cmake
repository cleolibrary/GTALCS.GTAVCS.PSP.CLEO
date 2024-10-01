set(SDL2_net_FOUND ON)

set(SDL2NET_SDL2_REQUIRED_VERSION  2.0.4)

include(CMakeFindDependencyMacro)

#FIXME: can't add SDL2NET_SDL2_REQUIRED_VERSION since not all SDL2 installs ship SDL2ConfigVersion.cmake
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL2_net-shared-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/SDL2_net-shared-targets.cmake")
endif()

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/SDL2_net-static-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/SDL2_net-static-targets.cmake")
endif()
