#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<list>

using namespace std;

struct DailyData {

    // Array containing the daily sales for each cuisine
    // The first item is the total sales for the corresponding day and it is calculated within the function update_daily_sales
    // the other items are entered using the function update_daily_cuisine_sales()
    // the indices correspond to Algerian, Syrian, Chinese, Indian, and European cuisines resp
    double daily_sales[6];

    // The cost of that day, will be calculated using the function update_cost()
    double daily_cost;

    // The daily amount of money spent on publicity
    // will be used to calculate the monthly amount of money spent on publicity used to calculate the return of investment
    double daily_pub;

    // Array containing The average daily rating for each cuisine
    // As the average daily rating for the whole restaurant is not needed, the size of the array will be 5 as the cuisins
    // the order of the cuisins will be the same: Algerian, Syrian, Chinese, Indian, and European
    // THIS POINT CAN BE DISCUSSED 
    double daily_rating[5];

    // The constructor
    DailyData()
        : daily_cost(0), daily_pub(0) {
        fill(begin(daily_sales), end(daily_sales), 0);
        fill(begin(daily_rating), end(daily_rating), 0);
    }

};

struct MonthlyData {
    // ratio, avg rating, sales

    // Just like daily_sales, monthly_sales is an array of the each cuisine monthly sales as well as the total sales for that month (first item)
    // it is calculated by calling the function update_monthly_sales() for cuisine sales and update_monthly_sales() for the total monthly sales
    double monthly_sales[6];

    // average monthly rating
    // it is calculated by calling the function update_monthly_rating() for each cuisine
    double monthly_rating[5];

    // the total monthly amount of money spent on pub
    // it is calculated by calling the function update_monthly_pub()
    double monthly_pub;

    // the ratio calculated by dividing the monthly sales by the total amount of money spent on pub is known as return of investment
    // it is calculated by calling the function update_ROI()
    double ROI;

    // check whether we need to store monthly cost ?????????
    // what about monthly rent? it is mentioned that daily rent is brought from the monthly rent
        // in this case we should create a function to calculate daily rent from monthly rent

    // constructor 
    MonthlyData()
        : monthly_pub(0), ROI(0) {
        fill(begin(monthly_sales), end(monthly_sales), 0);
        fill(begin(monthly_rating), end(monthly_rating), 0);
    }

};

class Restaurant {

public:
    // constructor
    Restaurant(string name, int noe, string& w, string& c);

    // Getter for ID
    string getID() const;

    // Getter for Name
    string getName() const;

    // Getter for Num of Employees
    int getNumOfEmployees() const;

    // Getter for Daily Data
    unordered_map<string, DailyData>& getDailyData();

    // Getter for Monthly Data
    unordered_map<string, MonthlyData>& getMonthlyData();

    // Getter for Wilaya
    string getWilaya() const;

    // Getter for City
    string getCity() const;

    // Getter for WSG array
    const double* getWSG() const;

    bool isGreater(Restaurant root);

    //******************************* Daily Data Functions ************************************************

    // function to calculate the daily cost according to that date
    // consider reducing the number of parameters, maybe the all the ingrediants together?
    // we may want to add a condition to make sure the date exists
    double update_cost(const string& date, double rent, double employees_pay, double electricity, double gas, double vegetables, double meat, double other_ingrediants, double others);

    // function to update (enter) the daily sales for each cuisine
    void update_daily_sales(string date, double algerian_sales, double syrian_sales, double chinese_sales, double indian_sales, double european_sales);

    // *************************************** Monthly Data Functions ********************************

    // function to calculate the monthly cuisine sales
    // remember, the order of the cuisines is Algerian, Syrian, Chinese, Indian, and European
    // i am not sure wether to add a restriction or not ???
    void update_monthly_sales(const string& target_month);

    // function to calculate the monthly rating
    void update_monthly_rating(const string& target_month);

    // function to calculate the monthly amount of money spent in a month
    void update_monthly_pub(const string& target_month);

    // function to calculate the ratio known as return of investment ROI
    void update_ROI(const string& target_month);

    // function to calculate the Weighted Sales Growth (sales in a given month + x/100)
    // we need to take the month as parameter to retrieve its date (sales and rating)
    void update_weighted_sales(const string curr_month);


    // function to display a report of the sales of this restaurant at any month
    // this function will be called to display the report of any restaurant at any month
    // Inside the Restaurant class
    void display_monthly_report(const string& target_month) const;

    // *************************************** Period Functions ************************************

    // function to calculate the sales for a specific month
    double* calculate_period_sales(const string& start_date, const string& end_date);


private:

    // ********************* Data Members ******************************************************

    string ID; // we chose to make it a string so that we can manipulate it using strings functions (e.g., substrings to extract numbers of wilayas and cities)
    string name;
    int num_of_employees;
    unordered_map<string, DailyData> daily_data; // store the daily data in unordered_map based on the string key : date
    unordered_map<string, MonthlyData> monthly_data; // store the monthly data in unordered_map based on the string key : date
    string wilaya;
    string city;
    // the ratio used to determine the winner of the prize. it is also called Weighted Sales Growth
    // it is calculated by calling the function update_weighted_sales()
    // it is cumulative for each cuisine
    double WSG[5] = { 0 }; //initialize at zero value

    static int restaurantNum; //for the ID initialzed at 0 it increments everytime a restaurant is created
    // ******************************* generate the Id ************************************************

    // function to generate the id
    // so far this function depends on the file containing the wilayas and cities and thier corresponding numbers
    // ideas: add function to transform wilayas and cities to numbers and vice versa
    // still don't get the cities and districts thing
    void generate_id(const string& wilaya, const string& city);

};


#endif
