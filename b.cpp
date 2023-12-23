#include "binarySearchTree.hpp"
#include "dsException.h"
#include<iostream>
#include<string>
#include<fstream>
#include <vector>
#include <sstream>
using namespace std;


const char* filename="algeria_cities.xlsx";

//constructor
BinarySearchTree::BinarySearchTree( ) : root{ nullptr }{
    initializeAlgerianCities(filename);
    initializeAlgerianWilayas(filename);
}
//copy constructor
BinarySearchTree::BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }
//move constructor
BinarySearchTree::BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
//destructor
BinarySearchTree::~BinarySearchTree( )
    {
    makeEmpty( );
    }

//function to search for the min
const Restaurant & BinarySearchTree::findMin( ) const
 {
     if( isEmpty( ) )
         throw UnderflowException{ };
     return findMinHelper(root)->element;
 }


//function to search for the max
const Restaurant & BinarySearchTree::findMax( ) const
   {
       if( isEmpty( ) )
           throw UnderflowException{ };
       return findMaxHelper( root )->element;
   }


//a function that checks if the restaurant is contained in the tree
bool BinarySearchTree::contains( const Restaurant & x ) const
    {
        return containsHelper( x, root );
    }


// a function to check if the tree is empty
bool BinarySearchTree::isEmpty( ) const
    {
        return root == nullptr;
    }


//a functon to print the tree in a sorted way
void BinarySearchTree::printTree( ostream & out) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTreeHelper( root, out );
    }


//a function that deletes all the tree`Nodes
void BinarySearchTree::makeEmpty( )
    {
        makeEmptyHelper( root );
    }


//insert
//it calls the private function insertHelper
void BinarySearchTree::insert( const Restaurant & x )
    {
        insertHelper( x, root );
    }


//remove
//it calls the private gunction removeHelper
void BinarySearchTree::remove( const Restaurant & x )
   {
       removeHelper( x, root );
   }


//a function to find a restaurant by its id
Restaurant BinarySearchTree::findRestaurantByID(const string& id) const
{   
    //define a node ,call the helper function and assign that that restaurant to the node
    TreeNode* result = findRestaurantByIDHelper(id, root);
    
    if (result == nullptr) {
        throw runtime_error("Restaurant not found");
    }
    
    return result->element;
}

//the private fuctions
//the insertion is done by the Id
void BinarySearchTree::insertHelper(const Restaurant &R, TreeNode *&tn)
{
    // If the treeNode is null, make a newNode
    if (tn == nullptr)
        tn = new TreeNode{R, nullptr, nullptr};
    else{
        // Comparison is done upon the id
        //converting the IDs into int
        int id1 = stoi(R.getID());
        int id2 = stoi(tn->element.getID());
        
        // If the id of the restaurant is less than the node id, insert in the left subtree
        if (id1 < id2)
            insertHelper(R, tn->left);
        // If the id of the restaurant is bigger than the node id, insert in the right subtree
        else if (id2 < id1)
            insertHelper(R, tn->right);
        else
        {
            // Duplicate; handle accordingly (you might want to update the existing node, ignore, or throw an exception)
            // For now, do nothing (duplicate is ignored)
        }
    }
}
   
//the remove function
//deletion is done by the id too
void BinarySearchTree::removeHelper(const Restaurant &x, TreeNode *&t)
{
    if (t == nullptr)
        return; // Item not found; do nothing
    else
    {
        // Comparison is done upon the id
        int id1 = stoi(x.getID());
        int id2 = stoi(t->element.getID());

        if (id1 < id2)
            removeHelper(x, t->left);
        else if (id2 < id1)
            removeHelper(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMinHelper(t->right)->element;
            removeHelper(t->element, t->right);
        }
        else
        {
            TreeNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }
}

BinarySearchTree::TreeNode * BinarySearchTree::findMinHelper( TreeNode *t ) const
{
    if( t == nullptr )
                return nullptr;
            if( t->left == nullptr )
                return t;
            return findMinHelper( t->left );
}

BinarySearchTree::TreeNode * BinarySearchTree::findMaxHelper( TreeNode *t ) const
{
    if( t != nullptr )
        while( t->right != nullptr )
            t = t->right;
    return t;
}
bool BinarySearchTree::containsHelper(const Restaurant &x, TreeNode *t) const
{
    if (t == nullptr)
        return false;
    else
    {
        // Comparison is done upon the id
        int id1 = stoi(x.getID());
        int id2 = stoi(t->element.getID());

        if (id1 < id2)
            return containsHelper(x, t->left);
        else if (id2 < id1)
            return containsHelper(x, t->right);
        else
            return true; // Match
    }
}


void BinarySearchTree::makeEmptyHelper( TreeNode * & t )
    {
        if( t != nullptr )
        {
            makeEmptyHelper( t->left );
            makeEmptyHelper( t->right );
            delete t;
        }
        t = nullptr;
    }

void BinarySearchTree::printTreeHelper(TreeNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTreeHelper( t->left, out );
            out << t->element << endl;
            printTreeHelper( t->right, out );
        }
    }
//function to make a copy of the tree

BinarySearchTree::TreeNode * BinarySearchTree::clone(TreeNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new TreeNode{ t->element, clone( t->left ), clone( t->right )};
    }

//private helper function that searches for the restairnt using its id
//no need to convert the id into int because we are looking for an id not inserting it
BinarySearchTree::TreeNode* BinarySearchTree::findRestaurantByIDHelper(const string& id, TreeNode* t) const
{
    // If the tree is empty or the node we are in is the one we need, return the node
    // (that would either be null or a restaurant)
    if (t == nullptr || t->element.getID() == id)
        return t;

    // If the ID is less, traverse the left subtree
    if (id < t->element.getID())
        return findRestaurantByIDHelper(id, t->left);

    // If the ID is greater, traverse the right subtree
    if (id > t->element.getID())
        return findRestaurantByIDHelper(id, t->right);

    // If the restaurant is not found, return null
    return nullptr;
}



//check the validity of the enterend city

// Function to check if the entered city is a valid city in Algeria

// it returns True if the entered city is found in the vector of Algerian city numbers, False otherwise
bool BinarySearchTree::IsCity(const std::string& enteredCity) const
{
    //find is used to check if enteredCity is in the vector of Algerian city numbers
    // getCityNumberFromFile is used to convert the entered city name to its corresponding number
    auto cityIter = find(AlgerianCities.begin(), AlgerianCities.end(), getCityNumberFromFile(enteredCity));

    // Return true if the entered city is found, false otherwise
    return cityIter != AlgerianCities.end();
}


//check the validity of the enterend wilaya

bool BinarySearchTree::IsWilaya(const string &enteredWilaya) const
{
    // Get the wilaya code for the entered wilaya
    //getWilayaFromFile function is used to convert the wilaya name into an int
    int wilayaCode = getWilayaCodeFromFile(enteredWilaya, filename);

    // Check if the retrieved code is valid and present in AlgerianWilayas
    return wilayaCode != -1 &&
           find(AlgerianWilayas.begin(), AlgerianWilayas.end(), wilayaCode) != AlgerianWilayas.end();
}

//check the validity of the district

bool BinarySearchTree::IsDistrict(const string &enteredDistrict) const
{
    // Read districts from the file
    vector<string> districtsFromFile = readDistrictsFromFile(filename);

    // Check if the entered district is in the vector of districts
    return find(districtsFromFile.begin(), districtsFromFile.end(), enteredDistrict) != districtsFromFile.end();
}

//ReadCitiesFromtheFile
// Get the number of the city from the file
//used to get the restaurant of a city
//since the ity entered by the user will be the city name and in the restaurant node we have the city code or number
//we go through the file and get the city code for the cityname
int BinarySearchTree::getCityNumberFromFile(const string &cityName) const
{
    //open the file
    //
    ifstream inputFile(filename);
    //check if the file is opened
    if (inputFile.is_open())
    {
        //go through all the lines
        string line;
        
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string commune_code,commune_name;
            
            if (iss >> commune_code >> commune_name)
            {
                // Compare the entered city name with the one from the file
                if (commune_name == cityName)
                {
                    // Found a match, return the city number
                    return stoi(commune_code);
                }
            }
        }

        // City not found in the file
        cerr << "Error: Invalid city." << endl;
        return -1;
    }
    else
    {
        throw runtime_error("Error: Unable to open file.");
    }
}
//same thing for the wilaya
int BinarySearchTree::getWilayaCodeFromFile(const string &wilayaName, const string &filename)const
{
    ifstream file(filename);
    //if file is not open
    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        return -1; // Return an invalid code if there's an error opening the file
    }

    string line;
    getline(file, line); // Read and discard the header line

    while (getline(file, line))
    {
        istringstream iss(line);
        vector<string> tokens;

        // Split the line into tokens
        string token;
        while (getline(iss, token, '\t'))
        {
            tokens.push_back(token);
        }

        // our file structure is: commune_code commune_name daira_name wilaya_code wilaya_name
        // So, the wilaya code is at index 3 and the wilaya name is at index 4
        if (tokens.size() >= 5 && tokens[4] == wilayaName)
        {
            return stoi(tokens[3]); // Convert the string to integer and return the wilaya code
        }
    }

    return -1;
}


// Function to initialize AlgerianCities vector
//the vector is used later to check whether thee city is a city that exists in the county
void BinarySearchTree::initializeAlgerianCities(const string& filename)
{// Clear existing data (if any)
    AlgerianCities.clear();
//open file
    ifstream file(filename);

    //thrw an error if the file is closed
    if (!file.is_open())
    {
      cerr << "Error opening file: " << filename << endl;
        return;
    }
//else
    //define the city code
    int cityCode;
    while (file >> cityCode)
    {
        AlgerianCities.push_back(cityCode);//insert into the vector
    }

    file.close();
}

//initialize the wilayasVector
//same logic as the previous one
void BinarySearchTree::initializeAlgerianWilayas(const string& filename)
{
    AlgerianWilayas.clear(); // Clear existing data (if any)
//open file
    ifstream wilayaFile(filename);
    //thrw an error if the file is closed
    if (!wilayaFile.is_open())
    {
        std::cerr << "Error opening wilaya file." << std::endl;
        return;
    }

    int wilayaCode;
    while (wilayaFile >> wilayaCode)
    {
        AlgerianWilayas.push_back(wilayaCode);//insert the wilaya codes into the vector
    }

    wilayaFile.close();
}


// Read districts from the file
vector<string> BinarySearchTree::readDistrictsFromFile(const string &fileName) const
{
    //define a vector that stores the districts that are existing in the file
    vector<string> districts;
//open file
    ifstream inputFile(fileName);
// //thrw an error if the file is closed
    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open file." << endl;
        return districts; // Return an empty vector if the file can't be opened
    }
//we will go through the file line by line

    string line;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        string codeCommune, nomCommune, daira, codeWilaya, nomWilaya;

        // Read the district
        iss >> daira;

        // Check if the district already exists in the vector
        auto it = find(districts.begin(), districts.end(), daira);

        if (it == districts.end())
        {
            // District doesn't exist, add it to the vector
            districts.push_back(daira);
        }
    }

    inputFile.close();
    return districts;
}
//function to get all the cities of a district

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
        string codeCommune, nomCommune, daira, codeWilaya, nomWilaya;

        // Read the commune code
        iss >> codeCommune;

        // Read the commune name
        iss >> nomCommune;

        // Read the district
        iss >> daira;

        // Read the wilaya code
        iss >> codeWilaya;

        // Read the wilaya name
        iss >> nomWilaya;

        // Create a DistrictCities object
        DistrictCities districtEntry;
        districtEntry.district = daira;

        // Add the city to the district
        districtEntry.cities.push_back(nomCommune);

        // Check if the district already exists in the result vector
        auto it = find_if(result.begin(), result.end(),
                          [&](const DistrictCities &entry) {
                              return entry.district == districtEntry.district;
                          });

        if (it != result.end())
        {
            // District already exists, add the city to it
            it->cities.push_back(nomCommune);
        }
        else
        {
            // District doesn't exist, add a new entry to the result vector
            result.push_back(districtEntry);
        }
    }

    inputFile.close();
    return result;
}



//a function that returns all the restaurants in the city
//this function calls the getRestaurantsinCityHelper function
vector<Restaurant> BinarySearchTree::getRestaurantsInCity(const string &city) const
    {
        if (getRestaurantsInCityHelper(city, root).empty())
             cout << "No restaurants found in the city: " << city << endl;
        return getRestaurantsInCityHelper(city, root);
    }

//a function that returns all the restaurants in wilaya
vector<Restaurant> BinarySearchTree::getRestaurantsInWilaya(const string &wilaya) const
    {
        //if theres no restaurant found in the wilaya the vector will be empty
        if (getRestaurantsInWilayaHelper(wilaya, root).empty())
             cout << "No restaurants found in the wilaya: " << wilaya << endl;
        return getRestaurantsInWilayaHelper(wilaya, root);
    }

//display the restaurants of a district
vector<Restaurant> BinarySearchTree::getRestaurantsInDistrict(const string& district) const
{
    // Get the list of cities in the district
    vector<string> citiesInDistrict = getCitiesInDistrictHelper(district);

    // Vector to hold all restaurants in the district
    vector<Restaurant> restaurantsInDistrict;

    // Collect restaurants for each city in the district
    for (const auto& city : citiesInDistrict)
    {
        // Get restaurants in the city
        vector<Restaurant> restaurantsInCity = getRestaurantsInCity(city);

        // Add restaurants to the vector
        restaurantsInDistrict.insert(
            restaurantsInDistrict.end(),
            restaurantsInCity.begin(),
            restaurantsInCity.end()
        );
    }

    return restaurantsInDistrict;
}


//getters helpers


//get restaurants in city helper
vector<Restaurant> BinarySearchTree::getRestaurantsInCityHelper(const string &city, TreeNode *node) const
{
    // Check if the entered city is valid
    int cityNumber = getCityNumberFromFile(city);
    if (cityNumber == -1)
    {
        cerr << "Error: Invalid city." << endl;
        return vector<Restaurant>(); // Return an empty vector for an invalid city
    }

    // Vector to hold the restaurants of that city
    vector<Restaurant> restaurantsCity;

    if (node != nullptr)
    {
        // Check if the city number matches the city number in the node
        if (getCityNumberFromFile(node->element.getCity()) == cityNumber)
        {
            restaurantsCity.push_back(node->element);
        }

        // Define 2 vectors to hold the restaurants that are in the left subtree and the right subtree
        auto leftRest = getRestaurantsInCityHelper(city, node->left);
        auto rightRest = getRestaurantsInCityHelper(city, node->right);

        // Combine them into one vector
        restaurantsCity.insert(restaurantsCity.end(), leftRest.begin(), leftRest.end());
        restaurantsCity.insert(restaurantsCity.end(), rightRest.begin(), rightRest.end());
    }

    return restaurantsCity;
}

//a private helper function that returns all the restaurant in the wilaya
//same logic for as the getRestaurants in city
vector<Restaurant> BinarySearchTree::getRestaurantsInWilayaHelper(const string &wilaya, TreeNode *node) const
{
    int wilayaCode = getWilayaCodeFromFile(wilaya, filename);

    if (wilayaCode == -1)
    {
        cerr << "Error: Invalid wilaya." << endl;
        return vector<Restaurant>();
    }

    vector<Restaurant> restaurantsWilaya;

    if (node != nullptr)
    {
        if (stoi(node->element.getWilaya() )== wilayaCode)
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

//a function to get all the cities in a district
vector<string> BinarySearchTree::getCitiesInDistrictHelper(const string& district) const
{
    vector<string> citiesInDistrict;

    // Iterate through the vector of DistrictCities to find the specified district
    for (const auto& entry : readCitiesAndDistrictsFromFile(filename))
    {
        if (entry.district == district)
        {
            citiesInDistrict = entry.cities;
            break; // Once found, no need to continue searching
        }
    }

    return citiesInDistrict;
}

//get restaurantbylocation
//it uses te previous funtions
//checks the type of the location entered and then call the approprite function
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





//pair vector to store the sales with the name of the restaurant
vector< pair < string, vector<double> > > RestaurantSales;

   // A helper function to store the information aka sales of a restaurant
   void BinarySearchTree::listCuisineSalesInLocationDuringPeriod(const string &location, const string &start_date, const string &end_date, TreeNode *node) const {
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
//the public function
//it uses thie helper  listCuisineSalesInLocationDuringPeriod
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
//a function that gets the ratio of the restaurant wanted
//this function uses the ratio counter that is defined  in the restaurant class
//it is somehow like the previous function
//the ratio could be retrieved only by month or by year
// if the user enters a period of time that won't work since the second month is not over yet


// Modified helper function to check for the specified location or restaurant name
void BinarySearchTree::listLocationRatioHelper(TreeNode* node, const string& location, const string& start_date, const string& end_date) const {
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
void BinarySearchTree::listRestaurantRatioHelper(TreeNode* node, const string& restaurantName, const string& start_date, const string& end_date) const
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

