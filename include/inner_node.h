#ifndef INNER_NODE_H
#define INNER_NODE_H

#include "Node.h"

namespace art{
    template <class T> InnerNode : public Node<T> {
    public:
        virtual ~InnerNode() = default;
        InnerNode() = default;
    
        bool isLeaf() const override;
    
        virtual Node<T> *findChild(char partialKey) const = 0;
        virtual void setChild(char partialKey, Node<T> *child) = 0;
        virtual bool delChild(char partialKey) = 0;
    
        virtual innerNode<T> *grow() = 0;
        virtual innerNode<T> *shrink() = 0;
    
        virtual bool is_full() const = 0;
        virtual bool is_underfull() const = 0;
        virtual int n_children() const = 0;

        virtual char next_partialKey(char partialKey) const = 0;
        virtual char prev_partialKey(char partialKey) const = 0;
    
    };
}



#endif
