//Binary Search Tree implementation for the dictionary ADT 

#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include "dictionary.h"

template <typename Key, typename E>
class BST : public Dictionary<Key, E>{

    private:
        BSTNode<Key, E>* root; //Root of the BST
        int nodeCount; //Number of nodes in the BST
        std::function<int(const Key&, const Key&)> compare;
    
    //private helper functions
    void clearhelp(BSTNode<Key, E>* root){
        if(root==nullptr){
            return;
        }
        clearhelp(root->left());
        clearhelp(root->right());
        delete root;
    }
    BSTNode<Key, E>* inserthelp(BSTNode<Key, E>* root, 
    const Key& k, const E& it){
        if(root==nullptr){
            //Empty tree, create node
            return new BSTNode<Key, E>(k, it, nullptr, nullptr);
        }
        int mComp = compare(k, root->key());
        std::cout<<"mComp: " << mComp << std::endl;
        if(mComp ==-1 || mComp ==0){
            //If the new key is lower than the root key //Insert on the left
            root->setLeft(inserthelp(root->left(), k, it));
        } else {
            root->setRight(inserthelp(root->right(), k, it));
        }/*
        if(k<root->key()){
            root->setLeft(inserthelp(root->left(), k, it));
        } else {
            root->setRight(inserthelp(root->right(), k, it));
        }*/
        return root;//Return tree with node inserted
    }
    BSTNode<Key, E>* deleteMin(BSTNode<Key, E>* rt){
        if(rt->left()==nullptr){
            //Found min, because the left side of the each 
            //node has
            //always a value lower than the current node. 
            return rt->right();
        } else {//continue left
            rt->setLeft(deleteMin(rt->left()));
            return rt;
        }
    }
    BSTNode<Key, E>* getmin(BSTNode<Key, E>* rt){
        if(rt->left()==nullptr){
            return rt;
        } else {
            return getmin(rt->left());
        }
    }

    BSTNode<Key, E>* removehelp(BSTNode<Key, E>* rt, 
    const Key& k){
        if(rt==nullptr){
            return nullptr;//K is not in tree
        }
        int mComp = compare(k, rt->key());
        //if (k<rt->key()){
        if(mComp==-1){
            rt->setLeft(removehelp(rt->left(),k));
        //} else if (k > rt->key()){
        } else if (mComp==1){
            rt->setRight(removehelp(rt->right(), k));
        }else{
            //Found, remove it. 
            BSTNode<Key, E>* temp = rt;
            if(rt->left()==nullptr){//Only a right child
                rt = rt->right();//So, point to right
                delete temp;
            } else  if(rt->right()==nullptr){//Only a left child
                rt = rt->left();//so point to left
                delete temp;
            } else {
                //Both children are non-empty
                //Get the min value of the right side/branch
                BSTNode<Key, E>* temp = getmin(rt->right());
                //Use the min of the right side to put the 
                //values in the rt node
                rt->setElement(temp->element());
                rt->setKey(temp->key());
                rt->setRight(deleteMin(rt->right()));
                delete temp;
            }
        }
        return rt;
    }
    E findhelp(BSTNode<Key, E>* root, const Key& k) const{
        if(root==nullptr){
            return nullptr;//Empty tree
        }
        int mComp = compare(k, root->key());
        //if(k<root->key()){
        if(mComp==-1){
            return findhelp(root->left(), k);//Check left
        //} else if (k > root->key()){
        } else if (mComp==1){
            return findhelp(root->right(), k);//Check right
        } else {
            return root->element();//Found it
        }
    }
    void printHelp(BSTNode<Key, E>* root, int level) const {
        if(root==nullptr){
            //Empty tree
            return;
        }
        printHelp(root->left(), level+1);//Do left subtree
        for(int i=0; i<level; i++){//Indent to level
            std::cout<<"    ";
        }
        std::cout << root->key() << "\n"; //Print node value
        printHelp(root->right(), level+1);//Do right subtree 

    }
    E findmax(BSTNode<Key, E>* node)const {
        if(node==nullptr){
            return nullptr;
        }
        while(node->right()!=nullptr){
            node =  node->right();
        }
        return node->element();
    }

    public: 
        //Constructor
        BST(){
            root=nullptr;
            nodeCount=0;
        }
        //Destructor
        ~BST(){
            clearhelp(root);
        }

        //Reinitialize tree
        void clear(){
            clearhelp(root);
            nodeCount=0;
        }
        //Insert a record into the tree
        //k - Key value of the record
        //e - The record to insert
        void insert(const Key& k, const E& e){
            root = inserthelp(root, k, e);
            nodeCount++;
        }

        //Remove a record from the tree
        // k Key value of the record to remove
        //Return: the record removed, or nullptr if there is none. 
        E remove(const Key& k){
            //First find it
            E temp = findhelp(root, k); 
            if(temp!=nullptr){
                root = removehelp(root, k);
                nodeCount--;
            }
            return temp;
        }

        //Remove and return the root node from the dictionary
        //Return: the record removed, null if tree is empty
        //Delete the min value
        E removeAny(){
            if(root!=nullptr){
                E temp = root->element();
                root = removehelp(root, root->key());
                nodeCount--;
                return temp;
            } else {
                return nullptr;
            }
            
        }

        //REturn record with key value k, nullptr if non exist. 
        //k: the key value to find
        //Return some record matching "k"
        //Return true if such exists, false otherwise. 
        //If multiple records match "k", return arbitrary one. 
        E find(const Key& k) const{
            return findhelp(root, k);
        }

        E getMax() const {
            return findmax(root);
        }

        //return the number of records in the dictionary
        int size(){
            return nodeCount;
        }

        void print() {
            if(root==nullptr){
                std::cout<< "The BST is empty\n";
            } else {
                printHelp(root, 0);
            }
        }

        void setCompare(std::function<int(const Key&, const Key&)> c){
            compare=c;
        }
};


#endif //BST_H
