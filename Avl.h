#ifndef AVL_H
#define AVL_H
#include "BinarySearchTree.h"
#include <iostream>
using namespace std;    
//the avl class is a child class of the binary search tree class 
class AvlTree : public BinarySearchTree{

    private:    
    int height(BinaryNode* node);//a function that returns the height of the node 
    int balancedFactor(BinaryNode* node);//the balanced factor {0,1,-1}
    using BinarySearchTree::insert;//allow the avl class to use the functions of insertion 
    //insert into avl 
    void insert(const Restaurant &x, BinaryNode *&t) override;
    void insert(Restaurant &&x, BinaryNode *&t) override;

    using BinarySearchTree::remove;//allow the avl class to use the functions delettion 
    //delete from avl
    virtual void remove(const Restaurant &x, BinaryNode *&t) override;
    //rotations (single rotations)
    //left_rotation
    void rotateRight(BinaryNode *&r);
    //right_rotation
    void rotateLeft(BinaryNode *&r);

    //double rotation
    void leftRightRotation(BinaryNode *&r);
    void rightLeftRotation(BinaryNode *&r);

    void balance(BinaryNode *&node);
    public:
    //constructor
    AvlTree();
    //destructor
    ~AvlTree();
    //copy constructor 
    AvlTree(const AvlTree &t);
    //move constructor
    AvlTree(AvlTree &&t);
    void insert(const Restaurant &x);
    void insert(Restaurant &&x);
    void remove(const Restaurant &x);
};
#endif