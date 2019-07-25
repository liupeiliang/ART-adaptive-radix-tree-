#ifndef NODE4_H
#define NODE4_H

#include <algorithm>

namespace art{

template <class T> class node4 : public inner_node<T>{

  friend class node16<T>;
  
public:
  node<T> *find_child(char partial_key) override ;
  void set_child(char partial_key, node<T> *child) override;
  bool del_child(char partial_key) override;

  inner_node<T> *grow() override;
  inner_node<T> *shrink() override;

  bool is_full() const override;
  bool is_underfull() const override;
  int n_children() const override;

  char next_partial_key(char partial_key) const override;
  char prev_partial_key(char partial_key) const override;
  
private:
  char keys_[4];
  node<T> *child_pointer_[4];
  uint8_t n_children_ = 0;
  
};
}

#endif
