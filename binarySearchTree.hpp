#ifndef binarySearchTree_hpp
#define binarySearchTree_hpp

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Restaurant.hpp"
using namespace std;

//define a class binary search tree

class BinarySearchTree {
    //define the data members and member functions as protcted because they will be used later for the avl
protected:
    
    
    //vectors to store the Algerian Cities /wilayas
        vector<int> AlgerianCities;
        vector<int> AlgerianWilayas;
    
    
    //define a struct TreeNode
    struct TreeNode{
        
    protected:
        Restaurant element;
        TreeNode* left;
        TreeNode* right;
        int height;//to be used in the avl
    public:
        //constructor
        TreeNode(const Restaurant &E,TreeNode* l,TreeNode* r):element(E),left(l),right(r){}
        //move constructor
        TreeNode(Restaurant &&theElement, TreeNode *lt, TreeNode *rt)
                   : element{std::move(theElement)}, left{lt}, right{rt} {}
        friend class BinarySearchTree;//so that we can use the treenode elements 
    };
    //end of the struct
    
    TreeNode* root;
    
    //the functions needed
    
    //FindMin
    TreeNode * findMinHelper( TreeNode *t ) const;
    //FindMax
    TreeNode* findMaxHelper( TreeNode *t ) const;
    //contains
    bool containsHelper( const Restaurant & x, TreeNode *t ) const;
    //clone
    TreeNode * clone( TreeNode *t ) const;
    //makeEmpty
    void makeEmptyHelper( TreeNode * & t );
    
    //printTree
    void printTreeHelper( TreeNode *t, ostream & out ) const;
    
    //insertHelper
    void insertHelper( const Restaurant & x, TreeNode * & t );
    //deleteHelper
    void removeHelper( const Restaurant & x, TreeNode * & t );
    //searchHelper
    TreeNode *findRestaurantByIDHelper(const string& id,TreeNode *t) const;
    
    //a function to check if the entered city is a city
    bool IsCity(const string &city) const;
    //a function to check if the entered  district is a district
    bool IsDistrict(const string &district) const;
    //a function to check if the entered wilaya is a wilaya
    bool IsWilaya(const string &wilaya) const;
    
    //a helper function to get the restaurants of a city
    vector<Restaurant> getRestaurantsInCityHelper(const string &city, TreeNode *node) const;
    //a function to get all the restaurants in a given wilaya
    vector<Restaurant> getRestaurantsInWilayaHelper(const string &wilaya, TreeNode *node) const;
    
    //a function to get all the restaurants in a given district
    vector<string>     getCitiesInDistrictHelper(const string &district) const;
    
    //helper function to get all the cuisine sales during a period of time
    void listCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date,TreeNode *node) const;
    
    //helper functions for the ratio
    //function to get the ratio with location
    void listLocationRatioHelper(TreeNode* node, const string& location, const string& start_date, const string& end_date) const ;
    //function to get the ratio by restaurant name
     void listRestaurantRatioHelper(TreeNode* node, const string& restaurantName, const string& start_date, const string& end_date) const ;
    
public:
    //constructor
    BinarySearchTree();
    //copy constructor
    BinarySearchTree(const BinarySearchTree &rhs);
    //move constructor
    BinarySearchTree(BinarySearchTree &&rhs);
    //destructor
    ~BinarySearchTree();
    //copy assignment
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
       {
           BinarySearchTree copy = rhs;
           std::swap( *this, copy );
           return *this;
       }
    //move assignment
    BinarySearchTree & operator=( BinarySearchTree && rhs )
        {
            std::swap( root, rhs.root );
            return *this;
        }
        
    //findMin
    const Restaurant & findMin( ) const;
    //findMax
    const Restaurant & findMax( ) const;
    //conatains
    bool contains( const Restaurant & x ) const;
    //tree isempty
    bool isEmpty( ) const;
    //printTree
    void printTree( ostream & out = cout ) const;
    //makeempty
    void makeEmpty();
    
    //insert
    void insert( const Restaurant & x );
    //delete
    void remove( const Restaurant & x );
    //search
    Restaurant findRestaurantByID(const string& id) const;
    
    //function to get the city code from file
    int getCityNumberFromFile(const string &wcdFile)const;
    //function to get the wilaya code from file
    int getWilayaCodeFromFile(const string &wilayaName, const string &filename)const;
    
    //function to read the cities/wilayas/districts  from the file and initialize the vector
    
    void initializeAlgerianCities(const string& filename);
    void initializeAlgerianWilayas(const string& filename);
    vector<string> readDistrictsFromFile(const string &fileName) const;
    
    
    //function to get the cities of a district
    //define a struct that takes the cities and district
    struct DistrictCities
        {
            string district;
            vector<string> cities;
        };
    vector<DistrictCities> readCitiesAndDistrictsFromFile(const string &fileName) const;
    
    
    //the getters from city/district/wilaya
    vector<Restaurant> getRestaurantsInCity(const string &city) const;
    vector<Restaurant> getRestaurantsInDistrict(const string &district) const;
    vector<Restaurant> getRestaurantsInWilaya(const string &wilaya) const;
    vector<Restaurant> getRestaurantsByLocation(const string &location) const;
    
    //display the sales of each cuisine during a period of time in a location
    void displayAllCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date) const ;
    
    void listRatioForLocation(const string& location, const string& start_date, const string& end_date) const ;
    void listRatioForRestaurant(const string& restaurantName, const string& start_date, const string& end_date) const;

};

#endif
