#ifndef ART_CPP
#define ART_CPP

#include "art.h"
#include "node.h"
#include "inner_node.h"
#include "leaf_node.h"
#include "node4.h"
#include "node16.h"
#include "node48.h"
#incldue "node256.h"
#include <stack>
#include <iostream>
#include <cstring>
#include <algorithm>

namespace art{

template <class T> Art<T>::~Art(){
    if(root == nullptr) return;
    std::stack<node<T> *> nodeStack;
    nodeStack.push(root);
    node<T> *cur, *tem;
    while(!nodeStack.empty()){
        cur = nodeStack.top();
        nodeStack.pop();
        if(!cur->is_leaf()){
            int n_children_ = cur->n_children();
            char partial_key = cur->next_partial_key(-128);
            for(int i = 0; i < n_children_; i++){
                tem = cur->find_child(partial_key);
        
                //debug
                if(tem == nullptr) std::cout<<"~art() error"<<std::endl;
                //
                
                nodeStack.push(tem);
                if(i < n_children_-1)
                    partial_key = cur->next_partial_key(partial_key+1);
            }
        }
        if(cur->prefix_ != nullptr){
            delete[] cur->prefix_;
        }
        delete cur;
    }
}

template <class T> T *Art<T>::getValue(const char *key) const{
    node<T> *cur = root, *child;
    int depth = 0, key_len = std::strlen(key)+1;
    while(cur != nullptr){
        // prefix mismatch
        if(cur->prefix_len_ != cur->check_prefix(key+depth)){
            return nullptr;
        }
        // exact match
        if(cur->prefix_len_ == key_len-depth){
            return cur->is_leaf() ? cur->value_ : nullptr;
        }
        depth += (cur->prefix_len_ + 1);
        cur = cur->find_child(key[depth + cur->prefix_len_]);
    }
    return nullptr;
}
    
template <class T> bool Art<T>::setValue(const char *key, T *value){
    int key_len = std::strlen(key) + 1;
    if(root == nullptr){
        root = new leaf_node<T>(value);
        root->prefix_ = new char[key_len];
        std::copy(key, key+key_len, root->prefix_);
        root->prefix_len_ = key_len;
        return true;
    }
    
    node<T> *cur = root, *child;
    int depth = 0, prefix_match_len;
    
    while(true){
        prefix_match_len = cur->check_prefix(key+depth);
        
        // part of key match the node's prefix
        bool is_prefix_match = (std::min<int>(cur->prefix_len_, key_len-depth) == prefix_match_len);

        if(is_prefix_match && (cur->prefix_len_ == key_len-depth)){
            // exact match: replace old value
            // must be a leaf_node ?  : \0
            cur->value_ = value;
            return true;
        }
        
        if(!is_prefix_match){
            //prefix mismatch:
            //new branch node be parent of cur and a new node
            auto new_parent = new node4<T>();
            new_parent->prefix_len_ = prefix_match_len;
            new_parent->prefix_ = new char[prefix_match_len];
            std::copy(cur->prefix_, cur->prefix_+prefix_match_len,
                      new_parent->prefix_);
            new_parent->set_child(cur->prefix_[prefix_match_len], cur);

            // 1 char to be the index(partial_key)
            auto old_prefix = cur->prefix_;
            auto old_prefix_len = cur->prefix_len_;
            cur->prefix_ = new char[old_prefix_len - prefix_match_len - 1];
            cur->prefix_len_ = old_prefix_len - prefix_match_len - 1;
            std::copy(old_prefix + prefix_match_len + 1,
                      old_prefix + old_prefix_len, cur->prefix);
            delete old_prefix;
            
            auto new_node = new leaf_node<T>();
            new_node->prefix_len_ = key_len - depth - prefix_match_len - 1;
            new_node->prefix_ = new char[new_node->prefix_len_];
            std::copy(key + depth + prefix_match_len + 1, key + key_len,
                      new_node->prefix_);
            new_parent->set_child(key[depth + prefix_match_len], new_node);
      
            return true;
        }

        // is_prefix_match && (cur->prefix_len_ == prefix_match_len)
        //inner_node<T> *cur_inner = static_cast<inner_node<T>*>(cur);
        char child_partial_key = key[depth + cur->prefix_len_];
        auto child = cur->find_child(child_partial_key);
        
        if(child == nullptr){
            
            if(cur->is_full()){
                cur = cur->grow();
            }
            
            auto new_node = new leaf_node<T>(value);
            new_node->prefix_len_ = key_len - depth - cur->prefix_len_ - 1;
            new_node->prefix_ = new char[new_node->prefix_len_];
            std::copy(key + depth + cur->prefix_len_ + 1, key + key_len,
                      new_node->prefix_);
            
            cur->set_child(key[depth + cur->prefix_len_], new_node);
            return true;
        }
        
        depth += cur->prefix_len_ + 1;
        cur = child;
    }
    return false;
}

template <class T> bool Art<T>::delValue(const char *key){
    int depth = 0, key_len = std::strlen(key) + 1;
    if(root == nullptr) return false;
    
    node<T> *cur = root;
    inner_node<T> *parent = nullptr;
    char cur_partial_key;
    
    while(cur != nullptr){
        
        if(cur->prefix_len_ != cur->check_prefix(key+depth)){
            return false;
        }
        
        // exact match
        if(key_len == depth + cur->prefix_len_){
            if(!(cur->is_leaf())){
                return false;
            }
            
            auto value = cur->value_;
            auto n_siblings = parent!=nullptr ? parent->n_children_-1 : 0;
            
            if(n_siblings == 0){
                //no other siblings
                //delete
                if(cur->prefix_ != nullpter){
                    delete[] cur->prefix_;
                }
                delete cur;
                cur = nullptr;
            }
            else if(n_siblings == 1){
                //path compression
                auto sibling_partial_key = parent->next_partial_key(-128);
                if(sibling_partial_key == cur_partial_key){
                    sibling_partial_key = parent->next_partial_key(cur_partial_key+1);
                }
                auto sibling = parent->find_child(sibling_partial_key);
                
                auto old_prefix = sibling->prefix_;
                auto old_prefix_len = sibling->prefix_len_;
                
                sibling->prefix_len_ = old_prefix_len + parent->prefix_len + 1;
                sibling->prefix_ = new char[sibling->prefix_len_];
                std::copy(parent->prefix_,
                          parent->prefix_ + parent->prefix_len_,
                          sibling->prefix_);
                sibling->prefix_[parent->prefix_len] = cur_partial_key;
                std::copy(old_prefix, old_prefix + old_prefix_len,
                          sibling->prefix_+parent_prefix_len+1);
                
                if(old_prefix != nullptr){
                    delete[] old_prefix;
                }
                if(cur->prefix_ != nullptr){
                    delete[] cur->prefix_;
                }
                delete cur;
                if(parent->prefix_ != nullptr){
                    delete[] parent->prefix_;
                }
                delete parent;
                
            } else{
                //n_siblings > 1
                if(cur->prefix_ != nullptr){
                    delete[] cur->prefix_;
                }
                delete cur;
                parent->del_child(cur_partial_key);
                if(parent->is_underfull()){
                    parent = parent->shrink();
                }
            }
            return true;
            
        }
        
        cur_partial_key = key[depth + cur->prefix_len_];
        depth += cur->prefix_len + 1;
        parent = cur;
        cur = cur->find_child(cur_partial_key);
        
    }
    
    return nullptr;
    
}

}

#endif
