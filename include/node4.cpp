#ifndef NODE4_CPP
#define NODE4_CPP

#include "node4.h"

namespace art{
  
    template <class T>
    node<T> *node4<T>::find_child(char partial_key){
        for(int i = 0; i < n_children_; i++){
            if(keys_[i] == partial_key){
                return child_pointer_[i];
            }
        }
        return nullptr;
    }

    template <class T>
    void node4<T>::set_child(char partial_key, node<T> *child){
    
        int pos = 0;
        while(pos < n_children_ && keys_[pos] <= partial_key) pos++;
        for(int i = n_children_; i > pos+1; i--){
            keys_[i] = keys_[i-1];
            child_pointer_[i] = child_pointer_[i-1];
        };
    
        key_[pos] = partial_key;
        child_pointer_[pos] = child;
        ++n_children_;
    }

    template <class T>
    bool del_child(char partial_key){
        for(int i = 0; i < n_children_; i++){
            if(keys_[i] == partial_key){
                for(int j = i; j < n_children_-1; j++)
                    keys_[j] = keys_[j+1];
                keys_[n_children_-1] = nullptr;
                --n_children_;
                return true;
            }
        }
        return false;
    }

    template <class T>
    inner_node<T> *node4<T>::grow(){
        auto new_node = new node16<T>();
        new_node->prefix = this->prefix;
        new_node->prefix_len_ = this->prefix_len_;
        new_node->n_children_ = this->n_children_;
        
        std::copy(this->keys_, this->keys_ + this->n_children_, new_node->keys);
        std::copy(this->child_pointer_, this->child_pointer_ + this->n_children_, new_node->child_pointer_);
        
        delete this;
        return new_node;
    }

    template <class T>
    inner_node<T> *node4<T>::shrink(){
        throw std::runtime_error("node4 cannot shrink");
    }

    template <class T>
    bool node4<T>::is_full() const { return (n_children_==4); }

    template <class T>
    bool node4<T>::is_underfull() const { return false;  }

    template <class T>
    int node4<T>::n_children() { return n_children_; }

    template <class T>
    char node4<T>::next_partial_key(char partial_key) const{
        for(int i = 0; i < n_children; i++){
            if(keys_[i] >= partial_key)
                return keys_[i];
        }

        throw std::out_of_range("provided partial key does not have a successor");
    }

    template <class T>
    char node4<T>::prev_partial_key(char partial_key) const {
        for(int i = n_children_-1; i >= 0; i--){
            if(keys_[i] <= partial_key)
                return keys_[i];
        }

        throw std::out_of_range("provided partial key does not have a predecessor");
    }
  
}

#endif
