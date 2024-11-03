#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "AVLNode.h"

//AVL Binary Search Tree implementation for the
//Dictionary ADT 
template <typename Key, typename E>
class AVL : public Dictionary<Key, E> {
//The public Dictionary<Key, E> indicated that this class
//will be inheriting the Dictionary class. 
    public: 
        //Constructor
        AVL(){
            root = nullptr;
            nodecount = 0;
        }
        //Destructor
        ~AVL(){
            clearhelp(root);
        }

        //Reinitialize the tree
        void clear(){
            clearhelp(root);
            root = nullptr;
            nodecount=0;
        }       

        //Insert a record into the tree
        //k - Key value of the item
        //e - The item to insert
        void insert(const Key& k, const E& e){
            root = insertHelp(root, k, e);
            nodecount++;
        }

        //Remove a record from the tree
        //k -  Key value of the item
        //Return: the item removed, or nullptr if there is none
        E remove(const Key& k){
            //Find the item
            E temp = findHelp(root, k);
            if(temp!=nullptr){
                root = removeHelp(root, k);
                nodecount--;
            }
            return temp;
        }

        //Remove and return the root node from 
        //the dictionary
        //Return - the record removed, null if tree
        //is empty
        E removeAny(){
            //Delete min value
            if(root!=nullptr){
                E temp = root->element();
                root = removeHelp(root, root->key());
            } 
            return nullptr;
        }

        //Return record with key value k, nullptr if none exist.
        //k: the key value to find
        //Return some record matching "k"
        //Return true if such exists, false otherwise
        //If multiple records match "k" return an arbitrary one.
        E find(const Key& k) const{
            return findHelp(root, k);
        }

        //Return the number of records in the dictionary
        int size(){
            return nodecount;
        }

        //Print the contents of the AVL 
        void print() {
            if(root==nullptr){
                std::cout << "The AVL is empty. \n";
        }else {
                printhelp(root, 0);
            }
        }

        E findMax() const{
            return getMaxHelp(root);
        }

    private:
        AVLNode<Key, E>* root = nullptr;//Root of the AVL BST
        int nodecount; //Number of nodes in the BST
    
        //private "helper" functions
        void clearhelp(AVLNode<Key,E>* root){
            if(root==nullptr){
                return;
            } 
            clearhelp(root->left());
            clearhelp(root->left());
            delete root;
        }

        AVLNode<Key, E>* insertHelp(
            AVLNode<Key, E>* root, const Key& k, const E& it){
            //HERE to implement the AVL algorithm to 
            //insert a node and balance the tree.

            if(root==nullptr){
                //std::cout << "Creating AVL node with key: " << k << " and returning the new node\n"; 

                return new AVLNode<Key, E>(k, it, nullptr, nullptr);
            } else if (k< root->key()){
                //std::cout << "Calling setLeft(insertHelp)" << "\n";
                root->setLeft(insertHelp(root->left(), k, it));
            } else if(k>root->key()) {
                //std::cout << "Calling setRight(insertHelp)" << "\n";
                root->setRight(insertHelp(root->right(), k, it));
                //std::cout << "Printing right \n";
                //std:: cout << "["<<root->right()->key() << ": "<< root->right()->element() << "]\n";
            } else {
                //TO-DO pending to implement the update of the it, 
                //when a new it is provided
                root->setElement(it);
            }

            if(root==nullptr){
                std::cout << "root is nullptr\n";
            }

            int leftHeight = getHeight(root->left());
            int rightHeight = getHeight(root->right());

            if(leftHeight>rightHeight){
                root->setHeight(1+leftHeight);
            } else {
                root->setHeight(1+rightHeight);
            }
            std::cout << "Printing before Rebalancing \n";
            print();

            int balance = getBalance(root);
            std::cout << "Balance: " << balance << " \n";
            //Left Left case
            if(balance > 1 && k< root->left()->key()){
                std::cout << "Left left case \n";
                return rightRotate(root);
            }

            //Right right case
            if(balance < -1 && k > root->right()->key()){
                std::cout << " Right right case \n";
                return leftRotate(root);
            }
            //Left right case
            if(balance > 1 && k > root->left()->key()){
                std::cout << "Left-Right case \n";
                root->setLeft(leftRotate(root->left()));
                return rightRotate(root);
            }

            //Right left case 
            if(balance < -1 && k < root->right()->key()){
                std::cout << "Right left case \n";
                root->setRight(rightRotate(root->right()));
                return leftRotate(root);
            }
            //Return the unchanged node pointer
            //std::cout << "Returning unchanged node pointer \n";
            return root;
        }

        int getHeight(AVLNode<Key, E>* node){
            if(node==nullptr){
                return 0;
            }else {
                return node->getHeight();
            }
        }

        AVLNode<Key, E>* rightRotate(AVLNode<Key, E>* node){
            std::cout << "rightRotate \n";
            AVLNode<Key, E>* x = node->left();
            AVLNode<Key, E>* T2 = x->right();
            //Do rotation
            x->setRight(node);
            node->setLeft(T2);
            //Update height
            node->setHeight(
                getHeight(node->left()) > getHeight(node->right()) ? 
                getHeight(node->left())+ 1 : 
                getHeight(node->right())+1);
            x->setHeight(
                getHeight(x->left()) > getHeight(x->right()) ? 
                getHeight(x->left())+ 1 : 
                getHeight(x->right())+1);
            //The new root of the tree / subtree
            return x;
        }

        AVLNode<Key, E>* leftRotate(
            AVLNode<Key, E>* node){
            AVLNode<Key, E>* y = node->right();
            AVLNode<Key, E>* T2 = y->left();
            std::cout << "leftRotate \n";
            //Do the rotation
            y->setLeft(node);
            node->setRight(T2);
            node->setHeight(
                getHeight(node->left()) >getHeight( node->right()) ? 
                getHeight(node->left()) +1 : 
                getHeight(node->right())+1);
            
            y->setHeight(getHeight(y->left()) > getHeight(y->right()) ? 
                getHeight(y->left()) +1 : 
                getHeight(y->right())+1);

            return y;
        }


        int getBalance(AVLNode<Key, E>* root){
            if(root==nullptr){
                return 0;
            }
            return getHeight(root->left())-getHeight(root->right());
        }

        AVLNode<Key, E>* deleteMin(
            AVLNode<Key, E>* rt){
            //TO-DO: implement the algorithm to find, 
            //delete and rebalance the tree once the deletion is completed
            
        }
        
        AVLNode<Key, E>* getMin(
            AVLNode<Key, E>* rt){
            if(rt->left()==nullptr) {
                return rt;
            } else {
                return getMin(rt->left());
            }
        }
        
        AVLNode<Key, E>* removeHelp(
            AVLNode<Key, E>* rt , const Key&  k
        ) {
            //K is not in the tree
            if(rt==nullptr){
                return nullptr;
            } else {
                //Implement the AVL algorithm to delete a node and
                //balance the tree after the delation
                return nullptr;
            }
        }

        E findHelp(
            AVLNode<Key, E>* root, 
            const Key& k) const {
            if(root==nullptr){
                return nullptr;
            }
            if(k<root->key()){
                //Check left
                return findHelp(root->left(), k);
            }else if (k>root->key()){
                //Check right
                return findHelp(root->right(), k);
            } else {
                //Found it
                return root->element();
            }
        }
        
        void printhelp(
            AVLNode<Key, E>* rt, 
            int level) {
            
            if(rt==nullptr){
                return;//Empty tree
            }
            if(rt->left()!=nullptr){
                std::cout << "Printing left \n";
                printhelp(rt->left(), level+1);
            }
            
            //Indent to level
            std::cout << "##########";
            for(int i=0; i< level; i++){
                std::cout << "    ";
            }
            //Print node value
            
            std::cout << rt->key() << "\n";
            
            if(rt->right()!=nullptr){
                std::cout << "Printing right \n";
                printhelp(rt->right(), level+1);
            }
            
        }

        AVLNode<Key, E>* getMaxHelp(
            AVLNode<Key, E>* rt){
                if(rt->right()){
                    return rt;
                } else {
                    return getMaxHelp(rt->right());
                }
            }

        

};

#endif //AVL_TREE_H