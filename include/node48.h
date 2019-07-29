#ifndef NODE48_H
#define NODE48_H

#include "inner_node.h"

namespace art{
  
    template <class T> class node48 : public inner_node<T>{

        friend class node16<T>;
        friend class node256<T>;
    
    public:
        node48();
    
        node<T> *find_child(char partial_key) override;
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
        static const char EMPTY = 0;
    
        char child_index_[256];
        node<T> *child_pointer_[48];
        uint8_t n_children_ = 0;
    
    };
}



#endif
