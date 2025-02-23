#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stack>
#include <list>
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
            //std::cout <<"************************\n" ;
            //std::cout <<"*******INSERTING*******\n" ;
            //std::cout <<"************************\n" ;
            //std::cout << "key: "<< k << std::endl;
            //std::cout << "value: "<< *e << std::endl;
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

        /*
        Compilation error: 
        error: passing ‘const AVL<EventPoint, EventPoint*>’ as ‘this’ argument discards qualifiers [-fpermissive]
   89 |             return getMaxHelp(root);
      |                    ~~~~~~~~~~^~~~~~
      The issue here is that your findMax function is marked as const, which means it should not modify any member variables of the class. 
      However, your getMaxHelp function is not const, which implies that it might modify this,
       and the compiler flags this as an error when getMaxHelp is called in a const context.
        */
        E findMax() const{
            //E getMaxHelp(AVLNode<Key, E>* rt)
            return getMaxHelp(root);
        }
        //pop removes the top value from the stack
        //top returns the top value from the stack, but it does not
        std::list<AVLNode<Key, E>*> getInOrderElementsAsNodes(){
            //std::cout << "getInOrderElementsAsNodes\n";
            if(root==nullptr){
                //Doing nothing because the tree is empty
                std::cout << "Doing nothign, the tree is empty\n";
                return std::list<AVLNode<Key, E>*>(); // Return an empty stack
            }
            std::list<AVLNode<Key, E>*> response;
            std::stack<AVLNode<Key, E>*> mStack;
            int counter =0;
            std::cout << "My Size: " << size() << std::endl;
            std::cout << "Adding root to the stack\n";
            mStack.push(root);
            std::cout << "root: " << root << std::endl;
            while(!mStack.empty()){
                //std::cout << "##############################";
                //std::cout << "###### step "<< counter << "\n";
                counter++;
                if(counter>20){
                   // break;
                }
                
                int counter =0;
                while(!mStack.empty()){
                    AVLNode<Key, E>* v = mStack.top();
                    //std::cout << "Starting cycle while v has left child\n";
                    while(v->left()!=nullptr){
                        //std::cout << "Inside while v has left child\n";
                        mStack.push(v->left());
                        v = v->left();
                    }
                    //std::cout << "Removing the top and assigning it to the v variable\n";
                    v = mStack.top();
                    mStack.pop();
                    response.push_back(v);
                    if(v->right()!=nullptr){
                        //std::cout << "Case when v has a right child\n";
                        //std::cout << "Pushing right child of v to the stack\n";
                        mStack.push(v->right());
                        //std::cout << "Assigning the right child to variable v\n";
                        v = v->right();
                    } else {
                        //std::cout << "Case when v HAS NOT a right child\n";

                        while(!mStack.empty() && v->right()==nullptr){
                            //std::cout << "Inside while loop mStack is not empty and v has not a right child\n";
                            v = mStack.top();
                            mStack.pop();
                            response.push_back(v);
                        }
                    }

                    if(v->right()!=nullptr){
                        //std::cout << "Case v has a right child\n";
                        //std::cout << "Pushing right child to stacm\n";
                        mStack.push(v->right());
                        //std::cout << "Assigning right child to v\n";
                        v = v->right();
                    }
                }
            }
            std::cout << "Returning response from getInOrderElementsAsNodes\n" ;
            return response;
            
        }

        std::list<E> getInOrderElements(){
            //std::cout << "getInOrderElements\n";
            if(root==nullptr){
                //Doing nothing because the tree is empty
                //std::cout << "Doing nothign, the tree is empty\n";
                return std::list<E>(); // Return an empty stack
            }
            std::list<E> response;
            std::stack<AVLNode<Key, E>*> mStack;
            int counter =0;
            //std::cout << "My Size: " << size() << std::endl;
            //std::cout << "Adding root to the stack\n";
            mStack.push(root);
            //std::cout << "root: " << root << std::endl;
            while(!mStack.empty()){
                //std::cout << "##############################";
                //std::cout << "###### step "<< counter << "\n";
                counter++;
                if(counter>20){
                   // break;
                }
                
                int counter =0;
                while(!mStack.empty()){
                    AVLNode<Key, E>* v = mStack.top();
                    //std::cout << "Starting cycle while v has left child\n";
                    while(v->left()!=nullptr){
                        //std::cout << "Inside while v has left child\n";
                        mStack.push(v->left());
                        v = v->left();
                    }
                    //std::cout << "Removing the top and assigning it to the v variable\n";
                    v = mStack.top();
                    mStack.pop();
                    response.push_back(v->element());
                    if(v->right()!=nullptr){
                        //std::cout << "Case when v has a right child\n";
                        //std::cout << "Pushing right child of v to the stack\n";
                        mStack.push(v->right());
                        //std::cout << "Assigning the right child to variable v\n";
                        v = v->right();
                    } else {
                        //std::cout << "Case when v HAS NOT a right child\n";

                        while(!mStack.empty() && v->right()==nullptr){
                            //std::cout << "Inside while loop mStack is not empty and v has not a right child\n";
                            v = mStack.top();
                            mStack.pop();
                            response.push_back(v->element());
                        }
                    }

                    if(v->right()!=nullptr){
                        //std::cout << "Case v has a right child\n";
                        //std::cout << "Pushing right child to stacm\n";
                        mStack.push(v->right());
                        //std::cout << "Assigning right child to v\n";
                        v = v->right();
                    }
                }
            }
            std::cout << "Returning response from getInOrderElements\n" ;
            return response;
            
        }
    /*
        HERE START THE PRIVATE SECTION
    */
        bool isEmpty(){
            return root==nullptr;
        }

	E getSuccesor(const Key& k)
	{
            return getSuccesorHelp(root,k);    
	}

	E getPredecessor(const Key& k)
	{
            return getPredecessorHelp(root, k);
	}

    private:

        

        AVLNode<Key, E>* root = nullptr;//Root of the AVL BST
        int nodecount; //Number of nodes in the BST
    
        //private "helper" functions
        void clearhelp(AVLNode<Key,E>* rt){
            if(rt==nullptr){
                return;
            } 
            clearhelp(rt->left());
            clearhelp(rt->left());
            delete rt;
        }

        AVLNode<Key, E>* insertHelp(
            AVLNode<Key, E>* rt, const Key& k, const E& it){
            //HERE to implement the AVL algorithm to 
            //insert a node and balance the tree.

            if(rt==nullptr){
                //std::cout << "Creating AVL node with key: " << k << " and returning the new node\n"; 
                return new AVLNode<Key, E>(k, it, nullptr, nullptr);
            } else if (k< rt->key()){
                //std::cout << "Calling setLeft(insertHelp)" << "\n";
                rt->setLeft(insertHelp(rt->left(), k, it));
            } else if(k>rt->key()) {
                //std::cout << "Calling setRight(insertHelp)" << "\n";
                rt->setRight(insertHelp(rt->right(), k, it));
                //std::cout << "Printing right \n";
                //std:: cout << "["<<root->right()->key() << ": "<< root->right()->element() << "]\n";
            } else {
                rt->setElement(it);
            }

            if(rt==nullptr){
                std::cout << "root is nullptr\n";
            }

            int leftHeight = getHeight(rt->left());
            int rightHeight = getHeight(rt->right());

            if(leftHeight>rightHeight){
                rt->setHeight(1+leftHeight);
            } else {
                rt->setHeight(1+rightHeight);
            }
            //std::cout << "Printing before Rebalancing \n";
            print();

            int balance = getBalance(rt);
            //std::cout << "Balance: " << balance << " \n";
            //Left Left case
            if(balance > 1 && k< rt->left()->key()){
                std::cout << "Left left case \n";
                return rightRotate(rt);
            }

            //Right right case
            if(balance < -1 && k > rt->right()->key()){
                std::cout << " Right right case \n";
                return leftRotate(rt);
            }
            //Left right case
            if(balance > 1 && k > rt->left()->key()){
                std::cout << "Left-Right case \n";
                rt->setLeft(leftRotate(rt->left()));
                return rightRotate(rt);
            }

            //Right left case 
            if(balance < -1 && k < rt->right()->key()){
                std::cout << "Right left case \n";
                rt->setRight(rightRotate(rt->right()));
                return leftRotate(rt);
            }
            //Return the unchanged node pointer
            //std::cout << "Returning unchanged node pointer \n";
            return rt;
        }

        int getHeight(AVLNode<Key, E>* node){
            if(node==nullptr){
                return 0;
            }else {
                return node->getHeight();
            }
        }

        AVLNode<Key, E>* rightRotate(AVLNode<Key, E>* node){
            //std::cout << "rightRotate \n";
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


        int getBalance(AVLNode<Key, E>* rt){
            if(rt==nullptr){
                return 0;
            }
            return getHeight(rt->left())-getHeight(rt->right());
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
            } else if (k< rt->key()){
                //std::cout << "Calling setLeft(insertHelp)" << "\n";
                AVLNode<Key, E>* left = removeHelp(rt->left(), k);
                rt->setLeft(left);
            } else if(k>rt->key()) {
                //std::cout << "Calling setRight(insertHelp)" << "\n";
                AVLNode<Key, E>* right = removeHelp(rt->right(), k);
                rt->setRight(right);
                //std::cout << "Printing right \n";
                //std:: cout << "["<<root->right()->key() << ": "<< root->right()->element() << "]\n";
            } else {
                //Root is the element we're deleting. 
                if(rt->isLeaf()==true){
                    //std::cout << "Is leaf, returning rt" << "\n";
                    delete rt;
                    return nullptr;
                } else if(rt->left()==nullptr){
                    //return the right as the root
                    //std::cout << "Returning right as left is null \n";
                    AVLNode<Key, E>* temp = rt->right();
                    delete rt;
                    return temp;
                } else if(rt->right()==nullptr){
                    //return the right as the root
                    //std::cout << "Returning left as right is null \n";
                    AVLNode<Key, E>* temp = rt->left();
                    delete rt;
                    return temp;
                } else {
                     // Find in-order successor (smallest in the right subtree)
                    //std::cout << "Finding in order successor \n";
                    AVLNode<Key, E>* temp = rt->right();
                    while (temp->left() != nullptr) {
                        temp = temp->left();
                    }
                    // Replace node's key and element with successor's key and element
                    rt->setKey(temp->key());
                    rt->setElement(temp->element());
                    // Delete the in-order successor
                    rt->setRight(removeHelp(rt->right(), temp->key()));
                }
                
            }

            int leftHeight = getHeight(rt->left());
            int rightHeight = getHeight(rt->right());

            if(leftHeight>rightHeight){
                rt->setHeight(1+leftHeight);
            } else {
                rt->setHeight(1+rightHeight);
            }
            //std::cout << "Printing before Rebalancing \n";
            print();

            int balance = getBalance(rt);
            //std::cout << "Balance: " << balance << " \n";
            //Left Left case
            if(balance > 1 && k< rt->left()->key()){
                std::cout << "Left left case \n";
                return rightRotate(rt);
            }

            //Right right case
            if(balance < -1 && k > rt->right()->key()){
                std::cout << " Right right case \n";
                return leftRotate(rt);
            }
            //Left right case
            if(balance > 1 && k > rt->left()->key()){
                std::cout << "Left-Right case \n";
                rt->setLeft(leftRotate(rt->left()));
                return rightRotate(rt);
            }

            //Right left case 
            if(balance < -1 && k < rt->right()->key()){
                std::cout << "Right left case \n";
                rt->setRight(rightRotate(rt->right()));
                return leftRotate(rt);
            }
            //Return the unchanged node pointer
            //std::cout << "Returning unchanged node pointer \n";
            return rt;
        }

        E findHelp(
            AVLNode<Key, E>* rt, 
            const Key& k) const {
            if(rt==nullptr){
                return nullptr;
            }
            if(k<rt->key()){
                //Check left
                return findHelp(rt->left(), k);
            }else if (k>rt->key()){
                //Check right
                return findHelp(rt->right(), k);
            } else {
                //Found it
                return rt->element();
            }
        } 

        E getPredecessorHelp(AVLNode<Key,E>* rt, const Key& k)
	{
            AVLNode<Key,E>* searchedNode = nullptr;
	    while(rt)
	    {
                if(k>rt->key())
		{
                    searchedNode = rt;
		    rt = rt->right();
		}else
		{
                    rt = rt->left();
		}
	    }

	    if(searchedNode!=nullptr)
	    {
                return searchedNode->element();
	    }

	    return nullptr;


	}


        E getSuccesorHelp(AVLNode<Key,E>* rt, const Key& k)
	{
            AVLNode<Key,E>* searchedNode = nullptr;

            while(rt){
                if(k<rt->key())
		{
                    searchedNode= rt;
		    rt = rt->left();
		}else
		{
                    rt = rt->right();
		}
	    }

	    if(searchedNode!=nullptr)
	    {
                return searchedNode->element();
	    }
            return nullptr;

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

        E getMaxHelp(AVLNode<Key, E>* rt) const {
            if (rt == nullptr) {
                return nullptr;
            }
            if(rt->right()==nullptr){
                //The root is the max
                return rt->element();
            } 
            AVLNode<Key, E>* temp = rt->right();
            while (temp->right() != nullptr) {
                temp = temp->right();
            }
            return temp->element();
        }
};

#endif //AVL_TREE_H
