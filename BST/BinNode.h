//Binary tree node abstrac class
#ifndef BIN_NODE_H
#define BIN_NODE_H

template<typename E> class BinNode{
    public: 
        //Base destructor
        virtual ~BinNode(){}; 
        //Return the node's value
        //The virtual keyworkd indicates
        //that method can be overrided 
        //in derived classes.
        //=0 indicates that method is pure
        //virtual, making BinNode an
        //abstract class
        virtual E& element()=0;

        //Set the node's value
        virtual void setElement(const E&) = 0;

        //Return the node's left child
        virtual BinNode* left() const = 0;

        //Set the node's left child
        virtual void setLeft(BinNode*) = 0;

        //Return the node's right child
        virtual BinNode* right() const = 0;

        //Set the node's right child
        virtual void setRight(BinNode*) = 0;

        //Return true if the node is a leaf, false otherwise
        virtual bool isLeaf() = 0;

};


#endif BIN_NODE_H