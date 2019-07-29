#ifndef NODE16_H
#define NODE16_H

namespace art{
  
    template <class T> class node16 : public inner_node<T>{

        friend class node4<T>;
        friend class node48<T>;


    public:
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
        char keys_[16];
        node<T> *child_pointer_[16];
        uint8_t n_children_ = 0;
    
    };
}



#endif
