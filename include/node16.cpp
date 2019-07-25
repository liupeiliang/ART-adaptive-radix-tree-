#ifndef NODE16_CPP
#define NODE16_CPP

#include "node16.h"
#include <iostream>

namespace art{

  template <class T>
  node<T> *node16<T>::find_child(char partial_key){
    for(int i = 0; i < n_children_; i++){
      if(keys_[i] == partial_key){
        return child_pointer_[i];
      }
    }
    return nullptr;
  }

  template <class T>
  void node16<T>::set_child(char partial_key, node<T> *child){
    int pos = 0;
    while(pos < n_children_ && keys_[pos] <= partial_key) pos++;
    for(int i = n_children_; i > pos+1; i--){
      keys_[i] = keys_[i-1];
      child_pointer_[i] = child_pointer_[i+1];
    }

    keys_[pos] = partial_key;
    child_pointer_[pos] = child;
    ++n_children_;
  }

  template <class T>
  bool del_child(char partial_key){
    for(int i = 0; i < n_children_; i++){
      if(keys_[i] == partial_key){
        for(int j = i; j < n_children_-1; j++){
          keys_[j] = keys_[j+1];
        }
        keys_[n_children_-1] = nullptr;
        --n_children_;
        return true;
      }
    }
    return false;
  }

  template <class T>
  inner_node<T> *node16::grow(){
    auto new_node = new node48<T>();
    new_node->prefix = this->prefix;
    new_node->prefix_len = this->prefix_len;
    new_node->n_children_ = this->n_children_;

    std::copy(this->child_pointer_, this->child_pointer_ + this->n_children_, new_node->child_pointer_);

    for(int i = 0; i < n_children_; i++){
      new_node->child_index_[this->keys_[i]] = i;
    }

    delete this;
    return newnode;
  }

  template <class T>
  inner_node<T> *node16::shrink(){
    if(this->n_children_ > 4){
      throw std::runtime_error("node 16 cannot shrink now, n_children_ > 4");
    }
    
    auto new_node = new node4<T>();
    new_node->prefix = this->prefix;
    new_node->prefix_len_ = this->prefix_len_;
    new_node->n_children_ = this->n_children_;

    std::copy(this->keys_, this->keys_ + this->n_children_, new_node->keys);
    std::copy(this->child_pointer_, this-<child_pointer_ + this->n_children_, new_node->child_pointer_);

    delete this;
    return new_node;
    
  }

  template <class T>
  bool node16<T>::is_full() const { return (n_children_ == 16); }

  template <class T>
  bool node16<T>::is_underfull() const { return (n_children_ == 4); }

  template <class T>
  int node16<T>::n_children() { return n_children_; }

  template <class T>
  char node16<T>::next_partial_key(char partial_key) const {
    for(int i = 0; i < n_children_; i++){
      if(keys_[i] >= partial_key){
        return keys_[i];
      }
    }
    throw std::out_of_range("provided partial key does not have a successor");
  }

  template <class T>
  char node16<T>::prev_partial_kay(char partial_key) const {
    for(int i = n_children_-1; i >= 0; i--){
      if(keys_[i] <= partial_key){
        return keys_[i];
      }
    }

    throw std::out_of_range("provided partial key does not have a predecessor");
  }
  
}





#endif
