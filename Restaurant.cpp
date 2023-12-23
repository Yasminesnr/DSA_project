#include "Restaurant.h"
#include "Timer.h"
#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<list>

using namespace std;

// Initialization of the static member
int Restaurant::restaurantNum = 0;

Restaurant::Restaurant()
{
}

Restaurant::Restaurant(const Restaurant& restaurant) :ID{restaurant.ID},name { restaurant.name }, num_of_employees{ restaurant.num_of_employees }, wilaya{ restaurant.wilaya }, city{ restaurant.city }, left{ nullptr }, right{ nullptr }
{
    daily_data = restaurant.daily_data;
    monthly_data = restaurant.monthly_data;
    copy(begin(restaurant.WSG), end(restaurant.WSG), begin(WSG));
   
}

// constructor
Restaurant::Restaurant(string name, int noe, string& w, string& c)
    : name{ name }, num_of_employees{ noe }, wilaya{ w }, city{ c }, left{ nullptr }, right{nullptr} {
    restaurantNum++;
    generate_id(w, c);
    copy(WSG, WSG + 5, WSG);
    cout << "num: " << restaurantNum << endl;
} //moving is more efficient when it comes to large set of data

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
void Restaurant::update_cost(const string& date, double totalCost) {
    // Check if the date exists in daily_data
    auto corr_date = daily_data.find(date);

    if (corr_date != daily_data.end()) {
        // Date exists, return the calculated cost
        corr_date->second.daily_cost = totalCost;
    }
    else {
        // Date doesn't exist, handle the error (you can return an error value or throw an exception)
        std::cerr << "Error: Date not found in daily_data for update_cost." << std::endl;
        // You might want to handle the error in a way that makes sense for your application
        // For now, returning 0 as an error value
      
    }
}


// function to update (enter) the daily sales for each cuisine
void Restaurant::update_daily_sales(const string& date, double algerian_sales, double chinese_sales, double european_sales, double indian_sales, double syrian_sales) {
    // first find the corresponding date and retrieve the daily_sales array and update it
    auto corr_date = daily_data.find(date);

    corr_date->second.daily_sales[1] = algerian_sales;
    corr_date->second.daily_sales[2] = chinese_sales;
    corr_date->second.daily_sales[3] = european_sales;
    corr_date->second.daily_sales[4] = indian_sales;
    corr_date->second.daily_sales[5] = syrian_sales;
    // update the total sales
    corr_date->second.daily_sales[0] = algerian_sales + syrian_sales + chinese_sales + indian_sales + european_sales;
}

void Restaurant::update_daily_rating(const string& date, double algerian_rating, double chinese_rating, double european_rating, double indian_rating, double syrian_rating)
{
    auto corr_date = daily_data.find(date);

    corr_date->second.daily_rating[1] = algerian_rating;
    corr_date->second.daily_rating[2] = chinese_rating;
    corr_date->second.daily_rating[3] = european_rating;
    corr_date->second.daily_rating[4] = indian_rating;
    corr_date->second.daily_rating[5] = syrian_rating;
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
