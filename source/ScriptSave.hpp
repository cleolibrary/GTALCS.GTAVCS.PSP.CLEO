#pragma once
#include <cstddef>

namespace cleo {
// Native saves must see only native scripts. Keep every original link so that
// the exact running order is restored, including empty/native-only lists.
template<class Node, size_t Capacity=1024> class ScriptSave {
    struct Link { Node* node; Node* next; Node* previous; };
    inline static Link links_[Capacity];
    inline static bool active_=false;
    Node*& head_;
    Node* original_;
    size_t count_=0;
    bool ready_=false;
public:
    template<class IsCustom> ScriptSave(Node*& head,IsCustom custom) : head_(head),original_(head) {
        if (active_) return;
        for (Node* node=head;node;node=node->next) {
            if (count_==Capacity) return;
            for (size_t i=0;i<count_;++i) if (links_[i].node==node) return;
            links_[count_++]={node,node->next,node->prev};
        }
        active_=true;
        Node* last=nullptr;head_=nullptr;
        for (size_t i=0;i<count_;++i) {
            Node* node=links_[i].node;
            if (custom(node)) continue;
            node->prev=last;
            if (last) last->next=node;else head_=node;
            last=node;
        }
        if (last) last->next=nullptr;
        ready_=true;
    }
    ScriptSave(const ScriptSave&)=delete;
    ScriptSave& operator=(const ScriptSave&)=delete;
    ~ScriptSave() {
        if (!ready_) return;
        for (size_t i=0;i<count_;++i) {
            links_[i].node->next=links_[i].next;
            links_[i].node->prev=links_[i].previous;
        }
        head_=original_;
        active_=false;
    }
    explicit operator bool() const { return ready_; }
};
}
