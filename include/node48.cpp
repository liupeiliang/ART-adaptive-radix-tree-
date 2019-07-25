#ifndef NODE48_CPP
#define NODE48_CPP

#include "node48.h"

namespace art{

  template <class T>
  node48<T>::node48(){
    std::fill(child_index_, child_index_+256, EMPTY);
    std::fill(child_pointer_, child_pointer_+48, nullptr);
  }
  
  template <class T>
  node<T> *node48<T>::find_child(char partial_key){
    char tem = child_index_[128+partial_key];
    if(tem == EMPTY) return nullptr;
    return child_pointer_[tem];
  }

  template <class T>
  void node48<T>::set_child(char partial_key, node<T> *child){
    for(int i = 0; i < 48; i++){
      if(child_pointer_[i] == nullptr){
        child_pointer_[i] = child;
        child_index_[128+partial_key] = i;
        ++n_children_;
        return;
      }
    }
  }

  template <class T>
  bool del_child(char partial_key){
    char &tem = child_index_[128+partial_key];
    if(tem == EMPTY) return false;
    child_pointer_[tem] = nullptr;
    tem = EMPTY;
    --n_children_;
    return true;
  }

  template <class T>
  inner_node<T> *node48<T>::grow(){
    auto new_node = new node256<T>;
    new_node->prefix_ = this->prefix;
    new_node->prefix_len_ = this->prefix_len_;
    new_node->n_children_ = this->n_children_;
    for(int i = 0; i < 256; i++){
      char tem = child_index_[i];
      if(tem != EMPTY){
        new_node->child_pointer_[i] = this->child_pointer_[tem];
      }
    }
    delete this;
    return new_node;
  }

  template <class T>
  inner_node<T> *node48<T>::shrink(){
    auto new_node = new node16<T>;
    new_node->prefix_ = this->prefix;
    new_node->prefix_len_ = this->prefix_len_;
    for(int partial_key = -128; partial_key < 127; ++partial_key){
      char tem = child_index_[128+partial_key];
      if(tem != EMPTY){
        //can be improved(don't use set_child())
        new_node->set_child(partial_key, child_pointer_[tem]);
      }
    }
    delete this;
    return new_node;
  }

  template <class T>
  bool node48<T>::is_full() const{
    return (n_children_ == 48);
  }

  template <class T>
  bool node48<T>::is_underfull() const{
    return (n_children_ <= 16);
  }

  template <class T>
  int node48<T>::n_children() const {
    return this->n_children_;
  }

  template <class T>
  char node48<T>::next_partial_key(char partial_key) const{
    for(int i = partial_key+128; i < 256; i++){
      char tem = child_index_[i];
      if(tem != EMPTY){
        return i-128;
      }
    }
    throw std::out_of_range("provided partial key does not have a successor");
  }

  template <class T>
  char node48<T>::prev_partial_key(char partial_key) const {
    for(int i = partial_key+128; i >= 0; i--){
      char tem = child_index_[i];
      if(tem != EMPTY){
        return i-128;
      }
    }
    throw std::out_of_range("provided partial key does not have a predecessor");

  }
  
}



#endif
