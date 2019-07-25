#ifndef ART_H
#define ART_H

#include <iostream>

namespace art{
  
template <class T> class art{
public:
  ~art();
  T *get(const char *key) const;
  bool set(const char *key, T *value);
  bool del(const char *key);
  
  

private:
  //inner_node<T> *root;
  
};
}



#endif
