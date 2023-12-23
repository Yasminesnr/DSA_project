#include "Restaurant.h"
#include "Timer.h"

#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<list>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Initialization of the static member
int Restaurant::restaurantNum = 0;

// constructor
Restaurant::Restaurant(string name, int noe, string& w, string& c)
    : name{ name }, num_of_employees{ noe },  wilaya{ w }, city{ c } {
    restaurantNum++;
    generate_id(w, c);
    
    fill(begin(WSG), end(WSG), 0.0);  // Initialize the WSG array with zeros
}
//movingis more efficient when it comes to large set of data

// the rendom constructor
Restaurant::Restaurant()
        : name(generateRandomName()), num_of_employees(generateRandomNumber()), wilaya(generateRandomWilaya()), city(generateRandomCity()) {
        restaurantNum++;
        generate_id(wilaya, city);
        fill(begin(WSG), end(WSG), 0.0);
    }

// Getter for ID
string Restaurant::getID() const {
    return ID;
}

// Getter for Name
string Restaurant::getName() const {
    return name;
}

// Getter for Num of Employees
int Restaurant::getNumOfEmployees() const {
    return num_of_employees;
}

// Getter for Daily Data
unordered_map<string, DailyData>& Restaurant::getDailyData() {
    return daily_data;
}

// Getter for Monthly Data
unordered_map<string, MonthlyData>& Restaurant::getMonthlyData() {
    return monthly_data;
}

// Getter for Wilaya
string Restaurant::getWilaya() const {
    return wilaya;
}

// Getter for City
string Restaurant::getCity() const {
    return city;
}

// Getter for WSG array
const double* Restaurant::getWSG() const {
    return WSG;
}

bool Restaurant::isGreater(Restaurant root) {
    //compare the wilayas
    string idRestau = this->getID();
    string wilayaCodeRest = idRestau.substr(0, 2);
    int wCodeRestau = stoi(wilayaCodeRest); //convert the code to int

    string idRoot = root.getID();
    string wilayaCodeRoot = idRoot.substr(0, 2);
    int wCodeRoot = stoi(wilayaCodeRoot); //convert the code to int

    if (wCodeRestau > wCodeRoot)
        return true; //the child is greater than the parent
    else if (wCodeRestau < wCodeRoot)
        return false; //the child is smaller than the parent
    else //they have the same wilaya 
    {

        //compare their cities
        string cityCodeRest = idRestau.substr(2, 6);
        int cCodeRestau = stoi(cityCodeRest); //convert the code to int

        string cityCodeRoot = idRoot.substr(2, 6);
        int cCodeRoot = stoi(cityCodeRoot); //convert the code to int

        if (cCodeRestau > cCodeRoot)
        {
            cout << "cCodeRestau= " << cCodeRestau;
            return true; //the child is greater than the parent
        }
        else if (cCodeRestau < cCodeRoot)
            return false; //the child is smaller than the parent

        else//they have the same city
        {
            //compare their 6 digits number
            string SixDigCodeRest = idRestau.substr(6, 12);
            int SixDigCodeRestau = stoi(SixDigCodeRest); //convert the code to int

            string SixDigCodeRootStr = idRoot.substr(0, 2);
            int SixDigCodeRoot = stoi(SixDigCodeRootStr); //convert the code to int

            if (SixDigCodeRestau > SixDigCodeRoot)
            {
                return true; //the child is greater than the parent
            }
            else if (SixDigCodeRestau < SixDigCodeRoot)
            {
                return false; //the child is smaller than the 
            }

        }
    }
    return false; // or true idk
}

//******************************* Daily Data Functions ************************************************

// function to calculate the daily cost according to that date
// consider reducing the number of parameters, maybe the all the ingrediants together?
// we may want to add a condition to make sure the date exists
double Restaurant::update_cost(const string& date, double rent, double employees_pay, double electricity, double gas, double vegetables, double meat, double other_ingrediants, double others) {
    // Check if the date exists in daily_data
    auto corr_date = daily_data.find(date);

    if (corr_date != daily_data.end()) {
        // Date exists, return the calculated cost
        // employees_pay is the payment of one employee. to get the total amount of payment we multiply it by the number of employees
        return rent + employees_pay * num_of_employees + electricity + gas + vegetables + meat + other_ingrediants + corr_date->second.daily_pub + others;
    }
    else {
        // Date doesn't exist
        cerr << "Error: Date not found in daily_data for update_cost." << endl;
        return 0.0;
    }
}


// function to update (enter) the daily sales for each cuisine
void Restaurant::update_daily_sales(string date, double algerian_sales, double syrian_sales, double chinese_sales, double indian_sales, double european_sales) {
    // first find the corresponding date and retrieve the daily_sales array and update it
    auto corr_date = daily_data.find(date);

    corr_date->second.daily_sales[1] = algerian_sales;
    corr_date->second.daily_sales[2] = syrian_sales;
    corr_date->second.daily_sales[3] = chinese_sales;
    corr_date->second.daily_sales[4] = indian_sales;
    corr_date->second.daily_sales[5] = european_sales;
    // update the total sales
    corr_date->second.daily_sales[0] = algerian_sales + syrian_sales + chinese_sales + indian_sales + european_sales;
}

// *************************************** Monthly Data Functions ********************************

// function to calculate the monthly cuisine sales
// remember, the order of the cuisines is Algerian, Syrian, Chinese, Indian, and European
// i am not sure wether to add a restriction or not ???
void Restaurant::update_monthly_sales(const string& target_month) {
    // the month must be of the format YYYY-MM so that it is unique


    // find the first day of the month
    string first_day = target_month + "-01";

    // iterate throught the daily_data beginning from the first day of the month
    auto date_iter = daily_data.find(first_day); // this returns a ptr to the first day of the month
    while (date_iter != daily_data.end() && date_iter->first.substr(0, 7) == target_month) { // the iterator didn't reach the end and the months match
        for (int cuisine = 1; cuisine < 6; cuisine++) {
            monthly_data[target_month].monthly_sales[cuisine] += date_iter->second.daily_sales[cuisine];
        }
        ++date_iter;
    }

    // update the monthly total sales
    for (int cuisine = 1; cuisine < 6; cuisine++) {
        monthly_data[target_month].monthly_sales[0] += monthly_data[target_month].monthly_sales[cuisine];
    }
}

// function to calculate the monthly rating
void Restaurant::update_monthly_rating(const string& target_month) {
    // the month must be of the format YYYY-MM so that it is unique


    // find the first day of the month
    string first_day = target_month + "-01";

    // iterate throught the daily_data beginning from the first day of the month
    auto date_iter = daily_data.find(first_day); // this returns a ptr to the first day of the month
    int days = 0; // to count the number of days in the month and divide the sum over it to get the avg rating
    while (date_iter != daily_data.end() && date_iter->first.substr(0, 7) == target_month) { // the iterator didn't reach the end and the months match
        for (int cuisine = 0; cuisine < 5; cuisine++) {
            monthly_data[target_month].monthly_rating[cuisine] += date_iter->second.daily_rating[cuisine];
        }
        ++date_iter;
        ++days;
    }

    // Calculate the avg rating for each cuisine
    for (int cuisine = 0; cuisine < 5; cuisine++) {
        if (days > 0)
            monthly_data[target_month].monthly_rating[cuisine] /= days;
    }
}

// function to calculate the monthly amount of money spent in a month
void Restaurant::update_monthly_pub(const string& target_month) {
    // the month must be of the format YYYY-MM so that it is unique


    // find the first day of the month
    string first_day = target_month + "-01";

    // iterate throught the daily_data beginning from the first day of the month
    auto date_iter = daily_data.find(first_day); // this returns a ptr to the first day of the month
    while (date_iter != daily_data.end() && date_iter->first.substr(0, 7) == target_month) { // the iterator didn't reach the end and the months match // +"-32" ensures that we don't fall in an infinite loop
        monthly_data[target_month].monthly_pub += date_iter->second.daily_pub;
        ++date_iter;
    }
}

// function to calculate the ratio known as return of investment ROI
void Restaurant::update_ROI(const string& target_month) {
    monthly_data[target_month].ROI = monthly_data[target_month].monthly_sales[0] / monthly_data[target_month].monthly_pub;
}

// function to calculate the Weighted Sales Growth (sales in a given month + x/100)
// we need to take the month as parameter to retrieve its date (sales and rating)
void Restaurant::update_weighted_sales(const string curr_month) {

    for (int cuisine = 0; cuisine < 5; cuisine++) {
        WSG[cuisine] += monthly_data[curr_month].monthly_sales[0] + monthly_data[curr_month].monthly_rating[cuisine] / 100;
    }
}


// function to display a report of the sales of this restaurant at any month
// this function will be called to display the report of any restaurant at any month
// Inside the Restaurant class
void Restaurant::display_monthly_report(const string& target_month) const {
    Timer timer("display_monthly_report");
    cout << "Report for Restaurant " << name << " in " << target_month << ":" << endl;

    // 1. Total Sales
    double total_sales = monthly_data.at(target_month).monthly_sales[0];
    cout << "Total Sales: $" << total_sales << endl;

    // 2. Cuisine-wise Sales Breakdown
    cout << "Cuisine-wise Sales Breakdown:" << endl;
    for (int cuisine = 1; cuisine < 6; cuisine++) {
        double cuisine_sales = monthly_data.at(target_month).monthly_sales[cuisine];
        cout << "   Cuisine " << cuisine << ": $" << cuisine_sales << endl;
    }

    // 3. Monthly Rating
    cout << "Monthly Rating:" << endl;
    for (int cuisine = 0; cuisine < 5; cuisine++) {
        double avg_rating = monthly_data.at(target_month).monthly_rating[cuisine];
        cout << "   Cuisine " << cuisine + 1 << ": " << avg_rating << endl;
    }

    // 4. Return of Investment (ROI)
    double roi = monthly_data.at(target_month).ROI;
    cout << "Return of Investment (ROI): " << roi << endl;

}

// *************************************** Period Functions ************************************

// function to calculate the sales for a specific month
double* Restaurant::calculate_period_sales(const string& start_date, const string& end_date) {
    double* sales = new double[6];
    fill(sales, sales + 6, 0); // initialize them to zero

    // find the start date for the iteration
    auto date_iter = daily_data.find(start_date);

    // iterate over the daily sales within the specified period
    while (date_iter != daily_data.end() && date_iter->first <= end_date) {
        // iterate over the cuisines
        for (int cuisine = 0; cuisine < 6; cuisine++) {
            sales[cuisine] += date_iter->second.daily_sales[cuisine];
        }
        date_iter++;
    }
    return sales;

    // DO NOT FORGET TO DELETE THE SALES AFTER USING THEM TO AVOID MEMORY LEAK
}


// ******************************* generate the Id ************************************************

// function to generate the id
// so far this function depends on the file containing the wilayas and cities and thier corresponding numbers
// ideas: add function to transform wilayas and cities to numbers and vice versa
// still don't get the cities and districts thing
void Restaurant::generate_id(const string& wilaya, const string& city) {
    //the ID is composed of: wilaya code|city code|6 digits number 
    string SixDigitsNum = "000000" + to_string(restaurantNum);
    //If the restaurant count has fewer than 6 digits, 
    //the string "000000" is used to pad and fill the remaining 
    //digits to ensure a fixed width of 6 characters.
    SixDigitsNum = SixDigitsNum.substr(SixDigitsNum.length() - 6); //to take the last 6 characters

    ID = wilaya + city + SixDigitsNum;
}

// ******************************* functions for randomly generate the dataset *******************************
string Restaurant::generateRandomName() {
    // Possible names for the restaurant
    vector<string> pre = {"El-baraka", "El-Rahma", "El-Djenina", "El-Boustane", "El-Magharibi", "Lalla", "El-Mesk"};
    vector<string> post = {"Grill House", "Cuisine Haven", "Palace Kitchen", "Taste Oasis", "Flavors Shack"};

    // Randomly select a pre and post
    string randomPre = pre[rand() % pre.size()];
    string randomPost = post[rand() % post.size()];

    // Combine them
    return randomPre + " " + randomPost;
}

int Restaurant::generateRandomNumber() {
    // reasonable range for the number of employees as the restaurant has five cuisines
    const int min = 20;
    const int max = 100;

    // Generate a random number within the specified range
    return rand() % (max - min + 1) + min;
}

string Restaurant::generateRandomWilaya() {
    // range for Wilaya numbers
    const int minWilaya = 1;
    const int maxWilaya = 58;

    // Generate a random Wilaya number within the specified range
    return to_string(rand() % (maxWilaya - minWilaya + 1) + minWilaya);
}

string Restaurant::generateRandomCity() {
    // Define the range for Cities numbers
    const int minCity = 0101;
    const int maxCity = 5803;

    // Generate a random Wilaya number within the specified range
    return to_string(rand() % (maxCity - minCity + 1) + minCity);
}

// Static function to enter random restaurants to a CSV file
void Restaurant::RestaurantsToCSV(const string& filename, int numRestaurants){
    // open the CSV file
    ofstream csvFile(filename);

    // write the header that represents the columns
    csvFile << "Name,Number_of_Employees,Wilaya,City\n";

    // seed the random number generator
    srand(time(0));

    // generate and enter random restaurants to the csv file
    for(int i = 0; i < numRestaurants; i++){
        // create the Restaurant object
        Restaurant restaurant;

        // enter the restaurant data in the csv file
        csvFile << restaurant.getName() << "," << restaurant.getNumOfEmployees() << ","
                << restaurant.getWilaya() << "," << restaurant.getCity() << "\n";
    }
    // Close the CSV file
    csvFile.close();
}