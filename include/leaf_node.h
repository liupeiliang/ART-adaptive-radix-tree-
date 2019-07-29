#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include "node.h"

namespace art{

template <class T> class leaf_node : public node<T> {
public:
    explicit leaf_node(T *value);
    bool is_leaf() const override;

    T *value_;
}

  
}



#endif
