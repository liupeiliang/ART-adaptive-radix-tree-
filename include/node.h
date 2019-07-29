#ifndef NODE_H
#define NODE_H

namespace art{
template <class T> Node{
public:
    virtual ~Node() = default;
    Node() = default;

    virtual bool isLeaf() const = 0;
    int checkPrefix(const char *key) const;

    char *prefix;
    uint16_t prefixLength = 0;
  
};
}


#endif
