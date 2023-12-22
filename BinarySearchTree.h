#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Restaurant.h"
#include <utility> // Used for the pair feature in vectors

using namespace std;
//define a class binary search tree 
class BinarySearchTree
{

protected://changed to protected because we will be needing the functions in here to be used in the avl tree

    struct BinaryNode
    {
        Restaurant element;
        BinaryNode* left;
        BinaryNode* right;
        int height; //to be used in the avl tree
        //BinaryNode constructor 
        BinaryNode(const Restaurant& theElement, BinaryNode* lt, BinaryNode* rt)
            : element(theElement), left(lt), right(rt) {}
        //BinaryNode move constructor 
        BinaryNode(Restaurant&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ std::move(theElement) }, left{ lt }, right{ rt } {}
    };

    BinaryNode* root;
    //vectors to store the algerian cities,districts,and wilayas after getting them from the files 
    vector<string> AlgerianCities;
    vector<string> AlgerianDistricts;
    vector<string> AlgerianWilayas;

    // overload the '<<' operator for the entire BinarySearchTree
    friend std::ostream& operator<<(std::ostream& out, const BinarySearchTree& tree);


    //private insert function 
    virtual void insert(const Restaurant& x, BinaryNode*& t);
    //private insert function  (to be used with rvalues )
    virtual void insert(Restaurant&& x, BinaryNode*& t);
    //delete a node function 
    virtual void remove(const Restaurant& x, BinaryNode*& t);
    //function to find the min
    BinaryNode* findMin(BinaryNode* t) const;
    //function to find the max
    BinaryNode* findMax(BinaryNode* t) const;
    //function to check if the restaurant   exists in the tree 
    bool contains(const Restaurant& x, BinaryNode* t) const;
    //make empty and delete all the tree
    void makeEmpty(BinaryNode*& t);
    //print the tree
    void printTree(BinaryNode* t, ostream& out) const;
    BinaryNode* clone(BinaryNode* t) const;
    //a helper function to find the restaurant by its id  
    BinaryNode* findRestaurantByIDHelper(const string& id, BinaryNode* t) const;
    //a function to check if the entered city is a city 
    bool IsCity(const string& city) const;
    //a function to check if the entered  district is a district
    bool IsDistrict(const string& district) const;
    //a function to check if the entered wilaya is a wilaya
    bool IsWilaya(const string& wilaya) const;
    //a function to get all the restaurant in a given city     
    vector<Restaurant> getRestaurantsInCityHelper(const string& city, BinaryNode* node) const;
    //a function to get all the restaurants in a given district
    vector<Restaurant> getRestaurantsInDistrict(const string& district) const;
    //a function to get all the restaurants in a given wilaya
    vector<Restaurant> getRestaurantsInWilayaHelper(const string& wilaya, BinaryNode* node) const;
    //a function to get the sales of  restaurant
    void listCuisineSalesInLocationDuringPeriod(const string& location, const string& start_date, const string& end_date, BinaryNode* node) const;

    void listLocationRatioHelper(BinaryNode* node, const string& location, const string& start_date, const string& end_date) const;
    void listRestaurantRatioHelper(BinaryNode* node, const string& restaurantName, const string& start_date, const string& end_date) const;
public:
    //constructor
    BinarySearchTree() : root{ nullptr } {}
    //move constructor
    BinarySearchTree(BinarySearchTree&& rhs) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    // Copy constructor
    BinarySearchTree(const BinarySearchTree& other);
    //destructor
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        if (this != &rhs) // Check for self-assignment
        {
            makeEmpty(); // Clear the current tree

            // Deep copy the tree
            root = clone(rhs.root);
        }
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs)
    {
        swap(root, rhs.root);
        return *this;
    }

    const Restaurant& findMin() const;
    const Restaurant& findMax() const;
    bool contains(const Restaurant& x) const;
    bool isEmpty() const;
    void printTree(ostream& out = cout) const;
    void makeEmpty();
    void insert(const Restaurant& x);
    void insert(Restaurant&& x);
    void remove(const Restaurant& x);
    void printTree()const;
    Restaurant findRestaurantByID(const string& id) const;
    vector<string> ReadCitiesFromFile(const string& wcdFile);

    struct DistrictCities
    {
        string district;
        vector<string> cities;
    };

    vector<DistrictCities> readCitiesAndDistrictsFromFile(const string& fileName) const;

    vector<string> ReadWilayasFromFile(const string& wcdFile);
    vector<Restaurant> getRestaurantsInCity(const string& city) const;
    vector<Restaurant> getRestaurantsInDistrict(const string& district) const;
    vector<Restaurant> getRestaurantsInWilaya(const string& wilaya) const;
    vector<Restaurant> getRestaurantsByLocation(const string& location) const;

    void displayAllCuisineSalesInLocationDuringPeriod(const string& location, const string& start_date, const string& end_date) const;
    void listRatioForLocation(const string& location, const string& start_date, const string& end_date) const;
    void listRatioForRestaurant(const string& restaurantName, const string& start_date, const string& end_date) const;

};

#endif
