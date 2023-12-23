#ifndef BST_h
#define BST_h

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
#include "Restaurant.h"
#include "PrizeWinners.h"
using namespace std;



//define a class binary search tree

class binarySearchTree {
    //define the data members and member functions as protcted because they will be used later for the avl
protected:
    //vectors to store the Algerian Cities /wilayas
    vector<int> AlgerianCities;
    vector<int> AlgerianWilayas;

    Restaurant* root;


    //the functions needed

    //FindMin
    Restaurant* findMinHelper(Restaurant* t) const;
    //FindMax
    Restaurant* findMaxHelper(Restaurant* t) const;
    //contains
    bool containsHelper(const Restaurant& x, Restaurant* t) const;
    //clone
    //Restaurant* clone(Restaurant* t) const;
    //makeEmpty
    void makeEmptyHelper(Restaurant*& t);

    //printTree
    void printTreeHelper(Restaurant* t, ostream& out) const;


    //insertHelper
    void addRestaurant(const Restaurant& x,Restaurant*& t);
    //deleteHelper
    void removeHelper(const Restaurant& x, Restaurant*& t);
    //searchHelper
    Restaurant*& findRestaurantByIDHelper(const string& id, Restaurant* t) const;

    Restaurant*& findRestaurantByNameHelper(const string& name, Restaurant* t) const;

    //a function to check if the entered city is a city
    bool IsCity(const string& city) const;
    //a function to check if the entered  district is a district
    bool IsDistrict(const string& district) const;
    //a function to check if the entered wilaya is a wilaya
    bool IsWilaya(const string& wilaya) const;

    //a helper function to get the restaurants of a city
    vector<Restaurant> getRestaurantsInCityHelper(const string& city, Restaurant* node, vector<Restaurant>& restaurantsCity) const;
    //a function to get all the restaurants in a given wilaya
    vector<Restaurant> getRestaurantsInWilayaHelper(const string& wilaya, Restaurant* node, vector<Restaurant>& restaurantsWilaya) const;

    //a function to get all the restaurants in a given district
    vector<string> getCitiesInDistrictHelper(const string& district) const;

    //helper function to get all the cuisine sales during a period of time
    void listCuisineSalesInLocationDuringPeriod(const string& location, const string& start_date, const string& end_date, Restaurant* node) const;

    //helper functions for the ratio
    //function to get the ratio with location
    void listLocationRatioHelper(Restaurant* node, const string& location, const string& start_date, const string& end_date) const;
    //function to get the ratio by restaurant name
    void listRestaurantRatioHelper(Restaurant* node, const string& restaurantName, const string& start_date, const string& end_date) const;

    //function to find a prize winner
    Restaurant* findOneCuisinePrizeWinner(int i, Restaurant* temp, Restaurant*& winner);

    vector<Restaurant> getAllRestaurants(Restaurant* temp, vector<Restaurant>& restaurants);


public:
    //to store the 5 prize winners in a given month
    PrizeWinners winners = PrizeWinners(2023);

    //constructor
    binarySearchTree();
    //copy constructor
    binarySearchTree(const binarySearchTree& rhs);
    //move constructor
    binarySearchTree(binarySearchTree&& rhs);
    //destructor
    ~binarySearchTree();
    //copy assignment
    binarySearchTree& operator=(const binarySearchTree& rhs)
    {
        binarySearchTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    //move assignment
    /*binarySearchTree& operator=(binarySearchTree&& rhs)
    {
        std::swap(root, rhs.root);
        return *this;
    }*/

    //findMin
    const Restaurant& findMin() const;
    //findMax
    const Restaurant& findMax() const;
    //conatains
    bool contains(const Restaurant& x) const;
    //tree isempty
    bool isEmpty() const;
    //printTree
    void printTree(ostream& out = cout) const;
    //makeempty
    void makeEmpty();

    //insert
    void addRestaurant(const Restaurant& x);
    //delete
    void remove(const Restaurant& x);
    //search
    Restaurant* findRestaurantByID(const string& id) const;
    Restaurant*& findRestaurantByName(const string& name) const;
    //function to get the city code from file
    int getCityNumberFromFile(const string& wcdFile)const;
    //function to get the wilaya code from file
    int getWilayaCodeFromFile(const string& wilayaName, const string& filename)const;

    //function to read the cities/wilayas/districts  from the file and initialize the vector

    void initializeAlgerianCities(const string& filename);
    void initializeAlgerianWilayas(const string& filename);
    vector<string> readDistrictsFromFile(const string& fileName) const;


    //function to get the cities of a district
    //define a struct that takes the cities and district
    struct DistrictCities
    {
        string district;
        vector<string> cities;
    };
    vector<DistrictCities> readCitiesAndDistrictsFromFile(const string& fileName) const;

    //the getters from city/district/wilaya
    vector<Restaurant> getRestaurantsInCity(const string& city) const;
    vector<Restaurant> getRestaurantsInDistrict(const string& district) const;
    vector<Restaurant> getRestaurantsInWilaya(const string& wilaya) const;
    vector<Restaurant> getRestaurantsByLocation(const string& location) const;

    //display the sales of each cuisine during a period of time in a location
    void displayAllCuisineSalesInLocationDuringPeriod(const string& location, const string& start_date, const string& end_date) const;

    void listRatioForLocation(const string& location, const string& start_date, const string& end_date) const;
    void listRatioForRestaurant(const string& restaurantName, const string& start_date, const string& end_date) const;

    //a function to get the prize winners in a given month
    //i is the index of the cuisine 
    //1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
    Restaurant* findOneCuisinePrizeWinner(int i);
    
    vector<Restaurant> getAllRestaurants();
};

#endif
