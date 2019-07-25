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
    
  }
  
  
}




#endif
