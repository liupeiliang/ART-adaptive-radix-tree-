#ifndef INNER_NODE_H
#define INNER_NODE_H

namespace art{
  template <class T> inner_node : public node<T> {
  public:
    virtual ~inner_node() = default;
    inner_node() = default;
    
    bool is_leaf() const override;
    
    virtual node<T> *find_child(char partial_key) const = 0;
    virtual void set_child(char partial_key, node<T> *child) = 0;
    virtual bool del_child(char partial_key) = 0;
    
    virtual inner_node<T> *grow() = 0;
    virtual inner_node<T> *shrink() = 0;
    
    virtual bool is_full() const = 0;
    virtual bool is_underfull() const = 0;
    virtual int n_children() const = 0;

    virtual char next_partial_key(char partial_key) const = 0;
    virtual char prev_partial_key(char partial_key) const = 0;
    
  };
}



#endif
