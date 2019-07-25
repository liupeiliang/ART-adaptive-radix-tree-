#ifndef LEAF_NODE_CPP
#define LEAF_NODE_CPP

#include "leaf_node.h"
#include <iostream>

namespace art{

  template <class T>
  leaf_node<T>::leaf_node(T *value): value_(value) {}
  
  template <class T>
  bool leaf_node<T>::is_leaf() const { return true;  }
  
}



#endif
