#include "Avl.h"
#include<iostream>
using namespace std;

//constructor 
AvlTree::AvlTree():BinarySearchTree(){}
//destructor 
AvlTree::~AvlTree(){
    makeEmpty();//delete the tree 
}
//copy constructor
AvlTree::AvlTree(const AvlTree& tree):BinarySearchTree(tree){
    //copy the tree 
    root=clone(tree.root);
}
//move constructor
AvlTree::AvlTree(AvlTree&& tree):BinarySearchTree(std::move(tree)){
    //move the tree 
    root=tree.root;
    tree.root=nullptr;
}

//a function that calculates the height of the node (here restaurant)
//the function returns an int which is the height of the node
//if the node is nullptr, then the height is zero
// otherwise, the height is the maximum height of the node left and right side +1 
//note:if the node is a leaf node the height is the max height of the node left and right side which is 0 +1 
int AvlTree::height(BinaryNode* node) {
    if (node == nullptr) return 0;
    return max(height(node->left), height(node->right)) + 1;
}


//a function that calculates the balance factor of the node (here restaurant)
//the function returns an int which is the bf that could be either 0,1 or -1(int the good cases )
//if the node is nullptr, then the balance factor is zero 
// otherwise,the balanced factor is calculated like this :we take the height of the left node  - the height of the right node  recursilvely
 int AvlTree::balancedFactor(BinaryNode* node){
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
 }

//a function that balances the tree 
 //this function calls the single/double rotation methods 
//If BF(node) = +2 and BF(node -> left-child) = +1, perform LL rotation.
//If BF(node) = -2 and BF(node -> right-child) = 1, perform RR rotation.
//If BF(node) = -2 and BF(node -> right-child) = +1, perform lr rotation.
//If BF(node) = +2 and BF(node -> left-child) = -1, perform rl rotation.
 void AvlTree::balance(BinaryNode *&t) {
    int bf = balancedFactor(t);
    if (bf > 1 && balancedFactor(t->left) > 0) {//heavy from the left side so we rotate it from the right 
        rotateRight(t);
    }
    else if (bf < -1 && balancedFactor(t->right) < 0) {//heavy from the right side so we rotate it from the left 
        rotateLeft(t);
    }
    else if (bf > 1 && balancedFactor(t->left) < 0) {
        rightLeftRotation(t);
    }
    else if (bf < -1 && balancedFactor(t->right) > 0) {
        leftRightRotation(t);
    }
}
void AvlTree::rotateRight(BinaryNode *&t ){
    BinaryNode *x=t->left;
    BinaryNode *y=x->right;

    x->right=t;
    t->left=y;
    //update the height of the node t and x 
    t->height=max(height(t->left),height(t->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

}

void AvlTree::rotateLeft(BinaryNode *&t ){
    BinaryNode *x=t->right;
    BinaryNode *y=x->left;

    x->left=t;
    t->right=y;
    //update the height of the node t and x 
    t->height=max(height(t->left),height(t->right))+1;
    x->height=max(height(x->left),height(x->right))+1;

}

 void AvlTree::leftRightRotation(BinaryNode *&r){

    rotateLeft(r->right);
    rotateRight(r);
 }
  void AvlTree::rightLeftRotation(BinaryNode *&r){

    rotateRight(r->left);
    rotateLeft(r);
 }


 //insert to an avl 
 //we follow the same logic for inserting a restaurant into the binary search tree
 //we have to update each time the height of the node to be used to calculate the balance factor
 //if the balance factor is different from the 0,1,-1 we have to use the rotation methods depending on each situation 
//instead of doing the same thing here and in the remove function we call the function balance
 void AvlTree::insert(const Restaurant &x, BinaryNode *&t) {
    BinarySearchTree::insert(x, t);//use the insertion from the binary search tree 
    //now we balance the tree by balancing the node 
    balance(t);
    //update the height of the node
    t->height = max(height(t->left), height(t->right)) + 1;
 }
//2nd insert function 
 void AvlTree::insert(Restaurant &&x, BinaryNode *&t) {
    BinarySearchTree::insert(std::move(x), t);//use the insertion from the binary search tree 
    //now we balance the tree by balancing the node 
    balance(t);
    //update the height of the node
    t->height = max(height(t->left), height(t->right)) + 1;
 }
//the public insert function
//it calls the private function 
 void AvlTree::insert(const Restaurant &x){
    insert(x, root);
 }
 void AvlTree::insert(Restaurant &&x){
    insert(Restaurant(x), root);//sinon try w/ std::move(x)
 }

 //a function to delete the node 
 //it uses the same logic used in the private function in the bst 
  //balance the tree by balancing the node
 //update the height of the node

 void AvlTree::remove(const Restaurant &x, BinaryNode *&t){
    BinarySearchTree::remove(x, t);//use the removal from the binary search tree 
     //now we balance the tree by balancing the node 
    balance(t);
    // then update the height of the node
    t->height = max(height(t->left), height(t->right)) + 1;
   
 }
//the public one 
//it calls the private function
 void AvlTree::remove(const Restaurant &x){
    remove(x, root);
 }