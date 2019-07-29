#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"

namespace art{

    template <class T>
    int Node<T>::checkPrefix(const char *key) const {
        for(int i = 0; i < prefixLength; i++){
            if(prefix[i] != key[i])
                return i;
        }
        return prefixLength;
    }
  
}



#endif
