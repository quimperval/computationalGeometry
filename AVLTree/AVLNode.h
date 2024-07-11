#ifndef AVLNODE_H
#define AVLNODE_H

#include<functional>
#include <iostream>

#include "BinNode.h"
#include "dictionary.h"

//Simple binary tree node implementation
template <typename Key, typename E>
 class AVLNode : public BinNode<E>{

    private: 
        Key k; //The node's key
        E it; //The node's value
        AVLNode* lc; //Pointer to left child
        AVLNode* rc; //Pointer to right child
        int height;

    public:
        //Two constructors -- with and without initial values
        AVLNode(){
            lc=rc=nullptr;
            height=0;
        }

        AVLNode(Key K, E e, AVLNode* l=nullptr, AVLNode* r = nullptr){
            k=K;
            it=e;
            lc=l;
            rc=r;
            height=0;
        }
        //Destructor
        ~AVLNode(){

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
        inline AVLNode* left() const{
            //std::cout << "Getting left \n";
            return lc;
        }

        void setLeft(BinNode<E>* b){
            lc= (AVLNode*) b;
        }

        inline AVLNode* right() const {
            //std::cout << "Getting right \n";
            return rc;
        };

        void setRight(BinNode<E>* b){
            //std::cout << "Setting right node \n";
            rc = (AVLNode* ) b;
        }

        //Return true if is a leaf, false otherwise
        bool isLeaf(){
            return (lc==nullptr) && (rc==nullptr);
        }

        void traverse(AVLNode *root){
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
            //TO-DO
            throw std::invalid_argument("insert function in AVLNode is not implemented");
        }
        
        void setHeight(int newValue){
            height = newValue;
        }

        int getHeight(){
            return height;
        }

};

#endif //AVLNODE_H