#ifndef ART_H
#define ART_H

namespace art{
  
template <class T> class Art{
public:
    ~art();
    T *getValue(const char *key) const;
    bool setValue(const char *key, T *value);
    bool delValue(const char *key);
  
  

private:
    inner_node<T> *root;
  
};
}



#endif
