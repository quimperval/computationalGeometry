#ifndef BSTNODE_H
#define BSTNODE_H

#include<functional>
#include <iostream>

#include "BinNode.h"

//Simple binary tree node implementation
template <typename Key, typename E> class BSTNode : public BinNode<E>{

    private: 
        Key k; //The node's key
        E it; //The node's value
        BSTNode* lc; //Pointer to left child
        BSTNode* rc; //Pointer to right child
        std::function<bool(const Key&, const Key&)> compare;
    public:
        //Two constructors -- with and without initial values
        BSTNode(){
            lc=rc=nullptr;
            compare = nullptr;
        }

        BSTNode(Key K, E e, std::function<bool(const Key&, const Key&)> c, BSTNode* l=nullptr, BSTNode* r = nullptr){
            k=K;
            it=e;
            lc=l;
            rc=r;
            compare=c;
        }
        //Destructor
        ~BSTNode(){

        }
        //Functions to set and return value and key

        E& element(){
            return it;
        }

        void setElement(const E& e){
            it=e;
        }

        Key& key(){
            return k;
        }

        void setKey(const Key& K){
            k=K;
        }

        //Functions to set and return the children
        inline BSTNode* left() const{
            return lc;
        }

        void setLeft(BinNode<E>* b){
            lc= (BSTNode*) b;
        }

        inline BSTNode* right() const {
            return rc;
        };

        void setRight(BinNode<E>* b){
            rc = (BSTNode* ) b;
        }

        //Return true if is a leaf, false otherwise
        bool isLeaf(){
            return (lc==nullptr) && (rc==nullptr);
        }

        void traverse(BSTNode *root){
            if(root==nullptr){
                return;
            }
            if(root->isLeaf()){
                std::cout << "Leaf: " << root->element() <<  std::endl;
            } else {
                std::cout << "Internal: " << root->element() <<  std::endl;
                traverse(root->left());
                traverse(root->right());
            }
        }

        void insert(Key newKey,     E newValue){
            if(compare==nullptr){
                throw std::runtime_error("Comparison function not set");
            }
            // Use the comparison function to determine the correct position for the new key

            if(compare(newKey, k)){
                //If the new key is less than the current key, go to left child
                if(lc==nullptr){
                    lc = new BSTNode(newKey, newValue, compare);  
                } else {
                    lc->insert(newKey, newValue);
                }
            } else {
                //If the new key is greater than the current key, go to right child
                if(rc==nullptr){
                    rc = new BSTNode(newKey, newValue, compare);  
                } else {
                    rc->insert(newKey, newValue);
                }
            }
        }

        void setCompare(std::function<bool(const Key&, const Key&)> c){
            compare=c;
        }
};

#endif BSTNODE_H