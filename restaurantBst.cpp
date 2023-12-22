#include "BinarySearchTree.h"
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <numeric>
#include<vector>
#include <sstream>//to use it with the iss when reading from the file
using namespace std;

// Constructor
BinarySearchTree::BinarySearchTree() : root{nullptr} {}

// Move constructor
BinarySearchTree::BinarySearchTree(BinarySearchTree &&rhs) : root{rhs.root}
{
    rhs.root = nullptr;
}
//copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) : root{nullptr} {
    root = clone(other.root);
}

// Destructor
BinarySearchTree::~BinarySearchTree()
{
    makeEmpty();
}

// Copy assignment operator
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &rhs)
{
     if (this != &rhs) // Check for self-assignment
    {
        makeEmpty(); // Clear the current tree

        // Deep copy the tree
        root = clone(rhs.root);
    }
    return *this;
}

// Move assignment operator
BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&rhs)
{
    swap(root, rhs.root);
    return *this;
}


// Private member function to insert a restaurant into the binary search tree
    //using the idea of inertion of the one used in the implementation aid 
    // the insertion is made upon the id of the restaurant
   
    // we compare each time the id of the
    // restaurant with the node existing in it
     //x is the restaurant to be inserted
    //t is the treeNode where the restaurant is gonna be inserted

void BinarySearchTree::insert(const Restaurant &x, BinaryNode *&t)
{   //if the tree is empty create a new node 
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};
    //if the id of the restaurant is less than the id of the node then insert from the left 
    else if (x.getID() < t->element.getID())
        insert(x, t->left);
     //if the id of the restaurant is bigger than the id of the node then insert from the right 
    else if (t->element.getID() < x.getID())
        insert(x, t->right);
    else
    ;  // Duplicate; do nothing
}

// Private member function to insert a restaurant (move version) into the binary search tree
//basicaly the same operations as the previous one
void BinarySearchTree::insert(Restaurant &&x, BinaryNode *&t)
{
    if (t == nullptr)
        t = new BinaryNode{std::move(x), nullptr, nullptr};
    else if (x.getID() < t->element.getID())
        insert(std::move(x), t->left);
    else if (t->element.getID() < x.getID())
        insert(std::move(x), t->right);
    else 
    ;  // Duplicate; do nothing
}

// Private member function to remove a restaurant from the binary search tree
//the idea is from the implemetanition aid
void BinarySearchTree::remove(const Restaurant &x, BinaryNode *&t)
{   //if the tree is empty do nothing
    if (t == nullptr)
        return; // Item not found; do nothing
      
        //if the id of the restaurant is less than the id of the node then remove from the left
    if (x.getID() < t->element.getID())
        remove(x, t->left);
        //if the id of the restaurant is bigger than the id of the node then remove from the right
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

// Private member function to find the minimum restaurant in the binary search tree
BinarySearchTree::BinaryNode *BinarySearchTree::findMin(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

// Private member function to find the maximum restaurant in the binary search tree
BinarySearchTree::BinaryNode *BinarySearchTree::findMax(BinaryNode *t) const
{
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}

// Private member function to check if the binary search tree contains a specific restaurant
bool BinarySearchTree::contains(const Restaurant &x, BinaryNode *t) const
{
    if (t == nullptr)
        return false;
    else if (x.getID() < t->element.getID())
        return contains(x, t->left);
    else if (t->element.getID() < x.getID())
        return contains(x, t->right);
    else
        return true;
}

// Private member function to make the binary search tree empty
void BinarySearchTree::makeEmpty(BinaryNode *&t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

// Private member function to print the binary search tree
//in-order traversal
void BinarySearchTree::printTree(BinaryNode *t, ostream &out) const
{
    if (t != nullptr)
    {
        printTree(t->left, out);
        out << t->element << endl;
        printTree(t->right, out);
    }
}

//a public function that prints the tree (an overloaded function)
void BinarySearchTree::printTree()const
{
    ostringstream out;
    printTree(root, out);
}

// Private member function to clone a binary search tree
//it makes a copy of the tree 
BinarySearchTree::BinaryNode *BinarySearchTree::clone(BinaryNode *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}
//the new member functions 

//private member function to find the the restaurant by id 


// Replace the existing findRestaurantByID function with this one
Restaurant BinarySearchTree::findRestaurantByID(const string& id) const
{
    BinaryNode* result = findRestaurantByIDHelper(id, root);
    if (result == nullptr) {
        throw runtime_error("Restaurant not found");
    }
    return result->element;
}

// Keep the existing findRestaurantByIDHelper function
BinarySearchTree::BinaryNode* BinarySearchTree::findRestaurantByIDHelper(const string& id, BinaryNode* t) const
{   //if the tree is empty or the node we are in is the one we need then return the node 
    //that woould either be null or a restaurant 
    if (t == nullptr || t->element.getID() == id)
        return t;
    //if the id is less traverse the left subtree 
    if (id < t->element.getID())
        return findRestaurantByIDHelper(id, t->left);
    //if the id is greater traverse the right subtree
    if (id > t->element.getID())
        return findRestaurantByIDHelper(id, t->right);

    //if the restaurant is not found return null
    return nullptr;
}
const char* filename="algeria_cities.xlsx";
// a function to read cities from file
vector<string> BinarySearchTree::ReadCitiesFromFile(const string &fileName)
{
   

    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string city;

            
            //because in the file we have the cities aka communes in the index 1
            //we skip the first  column
            
                string dummy;
                iss >> dummy;
            

            
            if (iss >> city)
            {
                AlgerianCities.push_back(city);//puch the cities in the algeriancities vector to be used later in checking the validity of the city
            }
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error: Unable to open file." << endl;
    }

    return AlgerianCities;
}

bool BinarySearchTree::IsCity(const string &enteredCity) const
{
    //go through the vector algerian cities and check if the entered city matches a city in the vector 
    return find(AlgerianCities.begin(), AlgerianCities.end(), enteredCity) != AlgerianCities.end();
}
//a private function to get the restaurants in a city 
vector<Restaurant> BinarySearchTree::getRestaurantsInCityHelper(const string &city, BinaryNode *node) const
    {   //checks if the entered city is a city 
        if(!IsWilaya(city)){ 
        cerr << "Error: Invalid city." << endl;
        return vector<Restaurant>(); //return an empty vector
        }
        //a vector to hold the restaurants of that city 
       vector<Restaurant> restaurantsCity;

        if (node != nullptr)
        {
            if (node->element.getCity() == city)
            {
                restaurantsCity.push_back(node->element);
            }
            //define 2 vectors to hold the restaurants that are in the left subtree and the right subtree 
            auto leftRest = getRestaurantsInCityHelper(city, node->left);
            auto rightRest = getRestaurantsInCityHelper(city, node->right);
            //combine them in one vector 
            restaurantsCity.insert(restaurantsCity.end(), leftRest.begin(), leftRest.end());
            restaurantsCity.insert(restaurantsCity.end(), rightRest.begin(), rightRest.end());
        }

        return restaurantsCity;
    }
//a function that returns all the restaurants in the city 
//this function calls the getRestaurantsinCityHelper function
vector<Restaurant> BinarySearchTree::getRestaurantsInCity(const string &city) const
    {
        if (getRestaurantsInCityHelper(city, root).empty())
             cout << "No restaurants found in the city: " << city << endl;
        return getRestaurantsInCityHelper(city, root);
    }
//read the wilayas from the file 
vector<string> BinarySearchTree::ReadWilayasFromFile(const string &fileName)
{
    vector<string> AlgerianWilayas;

    ifstream inputFile(fileName);

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string wilaya;

            //the wilaya will be the last column of the file 
            //skip the 5 first columns
            for (int i = 0; i <5;i++){ 
             string dummy;
            iss >> dummy;}
          

            // Assuming the wilaya is the second column (index 1)
            if (iss >> wilaya)
            {
                AlgerianWilayas.push_back(wilaya);
            }
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error: Unable to open file." << endl;
    }

    return AlgerianWilayas;
}
//check if the entered wilaya is a wilaya 
bool BinarySearchTree::IsWilaya(const string &enteredWilaya) const
{
    return find(AlgerianWilayas.begin(), AlgerianCities.end(), enteredWilaya) != AlgerianWilayas.end();
}
//a private helper function that returns all the restaurant in the wilaya
//same logic for as the getRestaurants in city 
vector<Restaurant> BinarySearchTree::getRestaurantsInWilayaHelper(const string &wilaya, BinaryNode *node) const
    {
        if(!IsWilaya(wilaya)){ 
        cerr << "Error: Invalid wilaya." << endl;
        return vector<Restaurant>(); 
        }
       
        else{vector<Restaurant> restaurantsWilaya;

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

        return restaurantsWilaya;}
        
    }

//a function that returns all the restaurants in wilaya 
vector<Restaurant> BinarySearchTree::getRestaurantsInWilaya(const string &wilaya) const
    {
        //if theres no restaurant found in the wilaya the vector will be empty 
        if (getRestaurantsInWilayaHelper(wilaya, root).empty())
             cout << "No restaurants found in the wilaya: " << wilaya << endl;
        return getRestaurantsInWilayaHelper(wilaya, root);
    }

//a function that returns all thcities in the district
 bool BinarySearchTree::IsDistrict(const string& district) const {
    vector<BinarySearchTree::DistrictCities> districts = readCitiesAndDistrictsFromFile("filename");

    for (const auto &entry : districts) {
        if (entry.district == district) {
            return true; // District found, it is valid
        }
    }

    return false;
}

//this function goes through the file and collect all the cities of a district 

  
  
vector<BinarySearchTree::DistrictCities> BinarySearchTree::readCitiesAndDistrictsFromFile(const string &fileName) const
{
    vector<DistrictCities> result;

    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return result; // Return an empty vector if the file can't be opened
    }

    string line;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string codeWilaya, nomWilaya, codePostal, nomCommune, daira;

      
        
            string dummy;
            iss >> dummy;
        

        // Read the district
        iss >> daira;

        // Create a DistrictCities object
        DistrictCities districtEntry;
        districtEntry.district = daira;

        // Read cities in the district
        while (iss >> nomCommune)
        {
            districtEntry.cities.push_back(nomCommune);
        }

        // Add the entry to the result vector
        result.push_back(districtEntry);
    }

    inputFile.close();
    return result;
}

vector<Restaurant> BinarySearchTree::getRestaurantsInDistrict(const string& district)const{
    //if the district does nor exist
     if (!IsDistrict(district))
    {
        cerr << "Error: Invalid district." << endl;
        return vector<Restaurant>(); // Return an empty vector 
    }

     vector<Restaurant> restaurantsInDistrict;

    // Use the readCitiesAndDistrictsFromFile function to get cities in the district
    vector<BinarySearchTree::DistrictCities> districts = readCitiesAndDistrictsFromFile("filename");

    // Find the district in the vector
    auto districtIter = find_if(districts.begin(), districts.end(), [district](const DistrictCities &entry) {
        return entry.district == district;
    });

    // If the district is found, get all the restaurants in each city
    if (districtIter != districts.end())
    {
        for (const string &city : districtIter->cities)
        {
            vector<Restaurant> restaurantsInCity = getRestaurantsInCity(city);
            restaurantsInDistrict.insert(restaurantsInDistrict.end(), restaurantsInCity.begin(), restaurantsInCity.end());
        }
    }
    else
    {
        cerr << "District not found." << endl;
    }

    return restaurantsInDistrict;
}
//a function that returns the restaurants of a location 
//it checks if the location entered is a city or wilaya or district then calls the defined function and it returns  a vector of restaurants
vector<Restaurant> BinarySearchTree::getRestaurantsByLocation(const string& location) const{

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


 
    //a function that lists the sales of restaurants in a specific location
    //the user just enters the location that can be (wilaya v district v city) and he gets the result displayed like so (restaurant name + the sales of that restaurant)
    //first we need a vector to store the restaurant name and the sales
    
    
    vector< pair < string, vector<double> > > RestaurantSales;

    // A helper function to store the information aka sales of a restaurant
    void BinarySearchTree::listCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date, BinaryNode *node) const {
        //if the tree is not empty go throu these steps
        
        if (node != nullptr) {
            
            //a map that stores the daily data of the restaurant using the getdailydata defined in the restaurant class
            const auto &dailyData = node->element.getDailyData();
            
            //an iterator that goes into the daily data map and search for the first pointer or something that points to the start date
                  auto dateIter = dailyData.find(start_date);

            
            //a vector that has the sales of the 5 cuisines + the total sales of a day (it is initialized to zero)
            
            vector<double> totalSalesForRestaurant(6, 0.0);
            
            //while we haven't reached the daily data end and didn't reached the end_date intered by the user we enter the loop:
            
            while (dateIter != dailyData.end() && dateIter->first <= end_date) {
                
                //check if the location entered by the user is a city/district/wilaya of the node /restaurant in this case
                
                if(IsCity(location)||IsDistrict(location)||IsWilaya(location)) 

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


    //a  public function to list the sales of all restaurants of a specific location(we will get the sales of a specific periode of time
    //for a year we enter the start date 01-01-year and endDate 31-12-year
    //for a month we enter 01-mm-yyyy -->31-mm-yyyy
    //for a day we only enter the day
    //update
    //the date format is yyyy-mm-dd
void BinarySearchTree::displayAllCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date) const {
    // Empty the vector before each use
    RestaurantSales.clear();

    // Call the private function (the helper)
    listCuisineSalesInLocationDuringPeriod(location, start_date, end_date, root);

    // Display the collected sales information
    for (const auto &sales : RestaurantSales) {
        cout << "Restaurant: " << sales.first << ", Sales: DZ";

        double totalSales = 0.0;

        for (double cuisineSales : sales.second) {
            cout << cuisineSales << " ";
            totalSales += cuisineSales;
        }

        cout << "(Total: DZ" << totalSales << ")" << endl;
    }
}

    //end of the function

    //a function that gets the ratio of the restaurant wanted
    //this function uses the ratio counter that is defined  in the restaurant class
    //it is somehow like the previous function
    //the ratio could be retrieved only by month or by year
    // if the user enters a period of time that won't work since the second month is not over yet
    

// Modified helper function to check for the specified location or restaurant name
void BinarySearchTree::listLocationRatioHelper(BinaryNode* node, const string& location, const string& start_date, const string& end_date) const {
    if (node != nullptr) {
        // Check if the current node's location (city or Wilaya) matches the specified input
        if (node->element.getCity() == location || node->element.getWilaya() == location) {
            // Get monthly data for the restaurant
            const auto& monthlyData = node->element.getMonthlyData();

            // Find the first date in the specified range
            auto dateIter = monthlyData.find(start_date);

            while (dateIter != monthlyData.end() && dateIter->first <= end_date) {
                // Get the ratio for the specified month
                double ratio = dateIter->second.ROI;

                cout << "Restaurant: " << node->element.getName() << ", Location: " << location
                     << ", ROI for " << dateIter->first << ": " << ratio << endl;

                ++dateIter;
            }
        }

        // Recursively traverse the left and right subtrees
        listLocationRatioHelper(node->left, location, start_date, end_date);
        listLocationRatioHelper(node->right, location, start_date, end_date);
    }
}


// Helper function to display ratios for a specific restaurant name
void BinarySearchTree::listRestaurantRatioHelper(BinaryNode* node, const string& restaurantName, const string& start_date, const string& end_date) const 
{
    if (node != nullptr) 
    {
        // Check if the current node's restaurant name matches the specified input
        if (node->element.getName() == restaurantName) {
            // Get monthly data for the restaurant
            const auto& monthlyData = node->element.getMonthlyData();

            // Find the first date in the specified range
            auto dateIter = monthlyData.find(start_date);

            while (dateIter != monthlyData.end() && dateIter->first <= end_date) {
                // Get the ratio for the specified month
                double ratio = dateIter->second.ROI;

                cout << "Restaurant: " << node->element.getName() << ", Location: " << node->element.getCity()
                     << ", ROI for " << dateIter->first << ": " << ratio << endl;

                ++dateIter;
            }
        }

        // Recursively traverse the left and right subtrees
        listRestaurantRatioHelper(node->left, restaurantName, start_date, end_date);
        listRestaurantRatioHelper(node->right, restaurantName, start_date, end_date);
    }
}
//----------------------------------------------------------------
    //the public function that gets the ratio 
        // Function to display ratios for a specified location (city or Wilaya)
void BinarySearchTree::listRatioForLocation(const string& location, const string& start_date, const string& end_date) const {
    // Call the helper function to display ratios for the specified location
    listLocationRatioHelper(root, location, start_date, end_date);
}

// Overloaded function for displaying ratios for a specific restaurant
void BinarySearchTree::listRatioForRestaurant(const string& restaurantName, const string& start_date, const string& end_date) const {
    // Call the helper function to display ratios for the specified restaurant name
    listRestaurantRatioHelper(root, restaurantName, start_date, end_date);
}

