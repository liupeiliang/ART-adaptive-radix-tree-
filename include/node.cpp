#ifndef NODE_CPP
#define NODE_CPP

#include "node.h"
#include <iostream>

namespace art{

  template <class T>
  int node<T>::check_prefix(const char *key) const {
    for(int i = 0; i < prefix_len_; i++){
      if(prefix[i] != key[i])
        return i;
    }
    return prefix_len_;
  }
  
}



#endif
