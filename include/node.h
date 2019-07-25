#ifndef NODE_H
#define NODE_H

#include <iostream>

namespace art{
template <class T> node{
public:
  virtual ~node() = default;
  node() = default;

  virtual bool is_leaf() const = 0;
  int check_prefix(const char *key) const;

  char *prefix;
  uint16_t prefix_len_ = 0;
  
};
}


#endif
