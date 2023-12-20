#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;
class Restaurant
{
private:
    int id;
    string city;
    string district;
    string wilaya;

public:
    Restaurant(int id, const std::string &city, const std::string &district, const std::string &wilaya)
        : id(id), city(city), district(district), wilaya(wilaya) {}

    int getID() const { return id; }
    const std::string &getCity() const { return city; }
    const std::string &getDistrict() const { return district; }
    const std::string &getWilaya() const { return wilaya; }

    friend std::ostream &operator<<(std::ostream &out, const Restaurant &restaurant)
    {
        out << "ID: " << restaurant.id << ", City: " << restaurant.city
            << ", District: " << restaurant.district << ", Wilaya: " << restaurant.wilaya;
        return out;
    }
};

template <typename T>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        T element;
        BinaryNode *left;
        BinaryNode *right;
//constructor
        BinaryNode(const T &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}
//move constructor
        BinaryNode(T &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
//copy constructor
//destructor
    };

    BinaryNode *root;
    // a function that inserts a restaurant
    // into the binary search tree
    // the insertion is made upon the id of the
    // restaurants
    // we compare each time the id of the
    // restaurant with the node existing in it
    
    void insert(const T &x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if (x.getID() < t->element.getID())
            insert(x, t->left);
        else if (t->element.getID() < x.getID())
            insert(x, t->right);
    }
//same insert function but this one is like a move one
    void insert(T &&x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        else if (x.getID() < t->element.getID())
            insert(std::move(x), t->left);
        else if (t->element.getID() < x.getID())
            insert(std::move(x), t->right);
    }
//this function deletes a restaurant and adjust the tree again

    void remove(const T &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return;
        if (x.getID() < t->element.getID())
            remove(x, t->left);
        else if (t->element.getID() < x.getID())
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    bool contains(const T &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true;
    }

    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode *t, ostream &out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << endl;
            printTree(t->right, out);
        }
    }

    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }
    //these vectors are used to store the valid cities
    vector<string> AlgerianCities;
    vector<string> AlgerianDistricts;
    vector<string> AlgerianWilayas;

    BinaryNode *findRestaurantByIDHelper(int id, BinaryNode *t) const
    {
        if (t == nullptr || t->element.getID() == id)
            return t;
        if (id < t->element.getID())
            return findRestaurantByIDHelper(id, t->left);
        if (id > t->element.getID())
            return findRestaurantByIDHelper(id, t->right);
        throw runtime_error("Restaurant not found");
    }

    bool IsCity(const string &enteredCity) const
    {
        return find(AlgerianCities.begin(), AlgerianCities.end(), enteredCity) != AlgerianCities.end();
    }

    bool IsDistrict(const string &enteredDistrict) const
    {
        return find(AlgerianDistricts.begin(), AlgerianDistricts.end(), enteredDistrict) != AlgerianDistricts.end();
    }

    bool IsWilaya(const string &enteredWilaya) const
    {
        return find(AlgerianWilayas.begin(), AlgerianWilayas.end(), enteredWilaya) != AlgerianWilayas.end();
    }

   vector<Restaurant> getRestaurantsInCityHelper(const string &city, BinaryNode *node) const
    {
       vector<Restaurant> restaurantsCity;

        if (node != nullptr)
        {
            if (node->element.getCity() == city)
            {
                restaurantsCity.push_back(node->element);
            }

            auto leftRest = getRestaurantsInCityHelper(city, node->left);
            auto rightRest = getRestaurantsInCityHelper(city, node->right);

            restaurantsCity.insert(restaurantsCity.end(), leftRest.begin(), leftRest.end());
            restaurantsCity.insert(restaurantsCity.end(), rightRest.begin(), rightRest.end());
        }

        return restaurantsCity;
    }

    vector<Restaurant> getRestaurantsInDistrictHelper(const string &district, BinaryNode *node) const
    {
        vector<Restaurant> restaurantsDistrict;

        if (node != nullptr)
        {
            if (node->element.getDistrict() == district)
            {
                restaurantsDistrict.push_back(node->element);
            }

            auto leftRest = getRestaurantsInDistrictHelper(district, node->left);
            auto rightRest = getRestaurantsInDistrictHelper(district, node->right);

            restaurantsDistrict.insert(restaurantsDistrict.end(), leftRest.begin(), leftRest.end());
            restaurantsDistrict.insert(restaurantsDistrict.end(), rightRest.begin(), rightRest.end());
        }

        return restaurantsDistrict;
    }

    vector<Restaurant> getRestaurantsInWilayaHelper(const string &wilaya, BinaryNode *node) const
    {
        vector<Restaurant> restaurantsWilaya;

        if (node != nullptr)
        {
            if (node->element.getWilaya() == wilaya)
            {
                restaurantsWilaya.push_back(node->element);
            }

            auto leftRest = getRestaurantsInWilayaHelper(wilaya, node->left);
            auto rightRest = getRestaurantsInWilayaHelper(wilaya, node->right);

            restaurantsWilaya.insert(restaurantsWilaya.end(), leftRest.begin(), leftRest.end());
            restaurantsWilaya.insert(restaurantsWilaya.end(), rightRest.begin(), rightRest.end());
        }

        return restaurantsWilaya;
    }
    /******************************************************************************************************************************************************************************************************/
    
    //a function that lists the sales of restaurants in a specific location
    //the user just enters the location that can be (wilaya v district v city) and he gets the result displayed like so (restaurant name + the sales of that restaurant)
    //first we need a vector to store the restaurant name and the sales
    
    
    mutable vector<pair<string, double>> RestaurantSales;

    // A helper function to store the information aka sales of a restaurant
    void listCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date, BinaryNode *node) const {
        //if the tree is not empty go throu these steps
        
        if (node != nullptr) {
            
            //a map that stores the daily date of the restaurant using the getdailydata defined in the restaurant class
            const auto &dailyData = node->element.getDailyData();
            
            //an iterator that goes into the daily data map and search for the first pointer or something that points to the start date
            
            auto dateIter = dailyData.lower_bound(start_date);
            
            //a vector that has the sales of the 5 cuisines + the total sales of a day (it is initialized to zero)
            
            vector<double> totalSalesForRestaurant(6, 0.0);
            
            //while we haven't reached the daily data end and didn't reached the end_date intered by the user we enter the loop:
            
            while (dateIter != dailyData.end() && dateIter->first <= end_date) {
                
                //check if the location entered by the user is a city/district/wilaya of the node /restaurant in this case
                
                if (node->element.getCity() == location || node->element.getDistrict() == location || node->element.getWilaya() == location)
                {
                    
                    //fill the vector
                    //first the sales of the 5 cuisines
                    for (int cuisine = 0; cuisine < 5; ++cuisine)
                    {
                        totalSalesForRestaurant[cuisine] += dateIter->second.daily_sales[cuisine];
                    }
                    // Calculate the total sales (last index)
                    for (int i=0;i<5;i++){
                        totalSalesForRestaurant[5]+=dateIter->second.daily_sales[i];
                    }
                    
                }
                dateIter++;
            }
            
            //store the sales information for this restaurant
            RestaurantSales.emplace_back(make_pair(node->element.getName(), totalSalesForRestaurant));
            
            //do the same thing for the left and the right
            listCuisineSalesInLocationDuringPeriod(location, start_date, end_date, node->left);
            listCuisineSalesInLocationDuringPeriod(location, start_date, end_date, node->right);
        }
    }
    //end of the function

public:
    //default constructor
    BinarySearchTree() : root{nullptr} {}
    //constructor
    BinarySearchTree(const BinarySearchTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }
    //move constructor
    BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }
    //destructor
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;
        swap(*this, copy);
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        swap(root, rhs.root);
        return *this;
    }

    const T &findMin() const
    {
        if (isEmpty())
            throw runtime_error("Tree is empty");
        return findMin(root)->element;
    }

    const T &findMax() const
    {
        if (isEmpty())
            throw runtime_error("Tree is empty");
        return findMax(root)->element;
    }

    bool contains(const T &x) const
    {
        return contains(x, root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    void printTree(ostream &out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTree(root, out);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(const T &x)
    {
        insert(x, root);
    }

    void insert(T &&x)
    {
        insert(std::move(x), root);
    }

    void remove(const T &x)
    {
        remove(x, root);
    }

    T findRestaurantByID(int id) const
    {
        BinaryNode *nodeFound = findRestaurantByIDHelper(id, root);
        if (nodeFound != nullptr)
        {
            return nodeFound->element;
        }
        else
        {
            throw runtime_error("Restaurant not found");
        }
    }

    void ReadCitiesFromFile(const string &citiesFile)
    {
        ifstream inputFile(citiesFile);
        if (inputFile.is_open())
        {
            string city;
            while (getline(inputFile, city))
            {
                AlgerianCities.push_back(city);
            }
            inputFile.close();
        }
        else
        {
            cerr << "Error: Unable to open file." << endl;
        }
    }

    void ReadDistrictsFromFile(const string &districtsFile)
    {
        ifstream inputFile(districtsFile);
        if (inputFile.is_open())
        {
            string district;
            while (getline(inputFile, district))
            {
                AlgerianDistricts.push_back(district);
            }
            inputFile.close();
        }
        else
        {
            cerr << "Error: Unable to open file." << endl;
        }
    }

    void ReadWilayasFromFile(const string &wilayasFile)
    {
        ifstream inputFile(wilayasFile);
        if (inputFile.is_open())
        {
            string wilaya;
            while (getline(inputFile, wilaya))
            {
                AlgerianWilayas.push_back(wilaya);
            }
            inputFile.close();
        }
        else
        {
            cerr << "Error: Unable to open file." << endl;
        }
    }

    vector<Restaurant> getRestaurantsInCity(const string &city) const
    {
        if (getRestaurantsInCityHelper(city, root).empty())
             cout << "No restaurants found in the city: " << city << endl;
        return getRestaurantsInCityHelper(city, root);
    }

    vector<Restaurant> getRestaurantsInDistrict(const string &district) const
    {
        if (getRestaurantsInDistrictHelper(district, root).empty())
              cout << "No restaurants found in the district: " << district << endl;
        return getRestaurantsInDistrictHelper(district, root);
    }

    vector<Restaurant> getRestaurantsInWilaya(const string &wilaya) const
    {
        if (getRestaurantsInWilayaHelper(wilaya, root).empty())
             cout << "No restaurants found in the wilaya: " << wilaya << endl;
        return getRestaurantsInWilayaHelper(wilaya, root);
    }

   vector<Restaurant> getRestaurantsByLocation(const string &location) const
    {
        vector<Restaurant> result;

        if (IsCity(location))
        {
            result = getRestaurantsInCity(location);
        }
        else if (IsDistrict(location))
        {
            result = getRestaurantsInDistrict(location);
        }
        else if (IsWilaya(location))
        {
            result = getRestaurantsInWilaya(location);
        }
        else
        {
            throw runtime_error("No restaurant found!");
        }

        return result;
    }
    //a function to list the sales of all restaurants of a specific location(we will get the sales of a specific periode of time
    //for a year we enter the start date 01-01-year and endDate 31-12-year
    //for a month we enter 01-mm-yyyy -->31-mm-yyyy
    //for a day we only enter the day
    //the date format is yyyy-mm-dd
    void displayAllCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date) const {
            //empty the vector before each use
            RestaurantSales.clear();
        //call the private function (the helper )
            listCuisineSalesInLocationDuringPeriod(location, start_date, end_date, root);

            // Display the collected sales information
        
            for (const auto &sales : RestaurantSales) {
                cout << "Restaurant: " << sales.first << ", Sales: DZ";
                for (double cuisineSales : sales.second) {
                    cout << cuisineSales << " ";
                }
               cout << "(Total: DZ" << accumulate(sales.second.begin(), sales.second.end(), 0.0) << ")" << endl;
            }
        }
  
    
};

#endif





/*
 //this is to save the binary seearch tree
 // ... (existing code)

 public:
     // ... (existing code)

     // Save the current state of the binary search tree to a file
     void SaveToFile(const std::string &filename) const
     {
         std::ofstream outputFile(filename);

         if (outputFile.is_open())
         {
             saveToFileHelper(root, outputFile);
             outputFile.close();
         }
         else
         {
             std::cerr << "Error: Unable to open file for writing." << std::endl;
         }
     }

     // Load the binary search tree from a file
     void LoadFromFile(const std::string &filename)
     {
         makeEmpty(root); // Clear the existing tree before loading from the file

         std::ifstream inputFile(filename);

         if (inputFile.is_open())
         {
             T restaurant;
             while (inputFile >> restaurant)
             {
                 insert(std::move(restaurant), root);
             }
             inputFile.close();
         }
         else
         {
             std::cerr << "Error: Unable to open file for reading." << std::endl;
         }
     }

 private:
     // Helper function to recursively save the binary search tree to a file
     void saveToFileHelper(BinaryNode *t, std::ofstream &out) const
     {
         if (t != nullptr)
         {
             saveToFileHelper(t->left, out);
             out << t->element << std::endl;
             saveToFileHelper(t->right, out);
         }
     }

     // ... (existing code)
 };
//and here is the usage of it
 #include "BinarySearchTree.h"

 int main()
 {
     // Create a BinarySearchTree object
     BinarySearchTree<Restaurant> restaurantTree;

     // Load data from a file
     restaurantTree.LoadFromFile("restaurant_data.txt");

     // Perform operations on the tree (insert, remove, etc.)
     // For example:
     Restaurant newRestaurant(101, "Algiers", "Center", "Algiers");
     restaurantTree.insert(newRestaurant);

     // Save the updated tree to a file
     restaurantTree.SaveToFile("restaurant_data.txt");

     // Use other functions of the BinarySearchTree class as needed

     return 0;
 }

 */

