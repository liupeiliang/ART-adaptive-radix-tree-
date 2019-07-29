#ifndef NODE256_CPP
#define NODE256_CPP

#include "node256.h"

namespace art{

    template <class T>
    node256<T>::node256(){
        std::fill(child_pointer_, child_pointer+256, nullptr);
    }
  
    template <class T>
    node<T> *node256<T>::find_child(char partial_key){
        return child_pointer_[partial_key+128];
    }

    template <class T>
    void node256<T>::set_child(char partial_key, node<T> *child){
        child_pointer_[partial_key+128] = child;
        ++n_children_;
    }

    template <class T>
    bool node256<T>::del_child(char partial_key){
        if(child_pointer_[partial_key+128] == nullptr) return false;
        child_pointer_[partial_key+128] = nullptr;
        return true;
    }
  
    template <class T>
    inner_node<T> *node256<T>::grow(){
        throw std::runtime_error("node256 cannot grow");
    }

    template <class T>
    inner_node<T> *node256<T>::shrink(){
        auto new_node = new node48<T>();
        new_node->prefix_ = this->prefix_;
        new_node->prefix_len_ = this->prefix_len_;
        new_node->n_children_ = this->n_children_;
        int pos = 0;
        for(int i = 0; i < 256; i++){
            auto tem = this->child_pointer_[i];
            if(tem != nullptr){
                new_node->child_index_[i] = pos;
                child_pointer_[pos] = tem;
                pos++;
            }
        }
        delete this;
        reutrn new_node;
    }

    template <class T>
    bool node256<T>::is_full() const {
        return (n_children_ == 256);
    }

    template <class T>
    bool node256<T>::is_underfull() const {
        return (n_children_ <= 48);
    }

    template <class T>
    int node256<T>::n_children() const {
        return n_children_;
    }

    template <class T>
    char node256<T>::next_partial_key(char partial_key) const {
        for(int i = partial_key+128; i < 256; i++){
            if(child_pointer_[i] != nullptr){
                return i-128;
            }
        }
        throw std::out_of_range("provided partial key does not have a successor");
    }

    template <class T>
    char node256<T>::prev_partial_key(char partial_key) const {
        for(int i = partial_key+128; i >= 0; i--){
            if(child_pointer_[i] != nullptr){
                return i-128;
            }
        }
        throw std::out_of_range("proveided partial key does not have a predecessor");
    }
  
}




#endif
