#ifndef UTILS_H
#define UTILS_H

#include "BinNode.h"
#include "BSTNode.h"

class Utils{
    public: 

    template <typename E> void preorder(BinNode<E>* root){
        if(root=nullptr) return;//Empty subtree, do nothing
        //prints the value or performs whatever computation as required
        //by the application
        visit(root); //Perform desired action
        preorder(root->left());
        preorder(root->right());

    };


    template <typename E> int count(BinNode<E>* root){
        if(root==nullptr) return 0;
        return 1 + count(root->left()) + count(root->right);
    };

    /**
     * This is to know if for a given arbitrary tree. 
     * For every node A, are all nodes in A's left subtree less 
     * than the value of A, and are all nodes in A's right
     * subtree greater than the value of A?
     * 
    */
    template <typename Key, typename E> bool checkBST(BSTNode<Key, E>* root, Key low, Key high){
        if(root==nullptr) return true;//Emtpy subtree
        Key rootkey = root->key();
        if( (rootkey<low) || (rootkey>high)){
            return false// out of range
        }
        if(!checkBST<Key, E>(root->left(), low, rootkey)){
            return false; //Left side failed
        }
        return checkBST<Key, E>(root->right(), rootkey, high);
    }
};

#endif UTILS_H
