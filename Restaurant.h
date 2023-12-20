#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>

using namespace std;

struct DailyData{

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
    DailyData(double s[6], double &c, double &pub, double r[5])
        : daily_cost{c}, daily_pub{pub}{
            // initialize the daily_sales array by copying the array s
            // in this case the name of the array s is treated as a pointer to the first element of the array
            // similarly s+6 is treated as a pointer to the last element of the array
            copy(s, s+6, daily_sales); 

            // initialize the daily_rating array by copying the array r
            copy(r, r+5, daily_rating);
        }
};

struct MonthlyData{
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
    MonthlyData(double s[6], double r[5], double &pub, double &roi)
        : monthly_pub(pub), ROI(roi){
            copy(s, s+6, monthly_sales);

            copy(r, r+5, monthly_rating);  
        }
};

class Restaurant {

public:
    // constructor
    Restaurant(string name, int noe, unordered_map<string, DailyData> ddata, unordered_map<string, MonthlyData> mdata, string &w, string &c, double wsg[5])
        : name{name}, num_of_employees{noe}, daily_data{move(ddata)}, monthly_data{move(mdata)}, wilaya{w}, city{c}{ 
            restaurantNum++;
            generate_id(w,c);
            copy(wsg, wsg+5, WSG);
        } //movingis more efficient when it comes to large set of data

        // Getter for ID
    string getID() const {
        return ID;
    }

    // Getter for Name
    string getName() const {
        return name;
    }

    // Getter for Num of Employees
    int getNumOfEmployees() const {
        return num_of_employees;
    }

    // Getter for Daily Data
    const unordered_map<string, DailyData>& getDailyData() const {
        return daily_data;
    }

    // Getter for Monthly Data
    const unordered_map<string, MonthlyData>& getMonthlyData() const {
        return monthly_data;
    }

    // Getter for Wilaya
    string getWilaya() const {
        return wilaya;
    }

    // Getter for City
    string getCity() const {
        return city;
    }

    // Getter for WSG array
    const double* getWSG() const {
        return WSG;
    }

bool isGreater(Restaurant root) {
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
    }

    //******************************* Daily Data Functions ************************************************

    // function to calculate the daily cost according to that date
    // consider reducing the number of parameters, maybe the all the ingrediants together?
    // we may want to add a condition to make sure the date exists
    double update_cost(const string &date, double rent, double employees_pay, double electricity, double gas, double vegetables, double meat, double other_ingrediants, double others){
        // first find the corresponding date and retrieve the daily_data of that date
        auto corr_date = daily_data.find(date);

        return rent + employees_pay + electricity + gas + vegetables + meat + other_ingrediants + corr_date->second.daily_pub + others;
    }

    // function to update (enter) the daily sales for each cuisine
    void update_daily_sales(string date, double algerian_sales, double syrian_sales, double chinese_sales, double indian_sales, double european_sales){
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
    void update_monthly_sales(const string &target_month){
        // the month must be of the format YYYY-MM so that it is unique

        // initialize the monthly sales to zeros
        fill(begin(monthly_data[target_month].monthly_sales), end(monthly_data[target_month].monthly_sales), 0);


        // find the first day of the month
        string first_day = target_month + "-01";

        // iterate throught the daily_data beginning from the first day of the month
        auto date_iter = daily_data.lower_bound(first_day); // this returns a ptr to the first day of the month
        while(date_iter != daily_data.end() && date_iter->first.substr(0, 7) == target_month) { // the iterator didn't reach the end and the months match
            for(int cuisine = 1; cuisine < 6; cuisine ++){
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
    void update_monthly_rating(const string &target_month){
        // the month must be of the format YYYY-MM so that it is unique

        // initialize the monthly rate array to zeros
        fill(begin(monthly_data[target_month].monthly_rating), end(monthly_data[target_month].monthly_rating), 0);


        // find the first day of the month
        string first_day = target_month + "-01";

        // iterate throught the daily_data beginning from the first day of the month
        auto date_iter = daily_data.lower_bound(first_day); // this returns a ptr to the first day of the month
        while(date_iter != daily_data.end() && date_iter->first.substr(0, 7) == target_month) { // the iterator didn't reach the end and the months match
            for(int cuisine = 0; cuisine < 5; cuisine ++){
                    monthly_data[target_month].monthly_rating[cuisine] += date_iter->second.daily_rating[cuisine];
            }
            ++date_iter;
        }
    }

    // function to calculate the monthly amount of money spent in a month
    void update_monthly_pub(const string &target_month){
        // the month must be of the format YYYY-MM so that it is unique

        // initialize to zero
        monthly_data[target_month].monthly_pub = 0;

        // find the first day of the month
        string first_day = target_month + "-01";

        // iterate throught the daily_data beginning from the first day of the month
        auto date_iter = daily_data.lower_bound(first_day); // this returns a ptr to the first day of the month
        while(date_iter != daily_data.end() && date_iter->first.substr(0, 7) == target_month) { // the iterator didn't reach the end and the months match
            monthly_data[target_month].monthly_pub += date_iter->second.daily_pub;
            ++date_iter;
        }
    }

    // function to calculate the ratio known as return of investment ROI
    void update_ROI(const string &target_month){
        monthly_data[target_month].ROI = monthly_data[target_month].monthly_sales[0]/monthly_data[target_month].monthly_pub;
    }

    // function to calculate the Weighted Sales Growth (sales in a given month + x/100)
    // we need to take the month as parameter to retrieve its date (sales and rating)
    void update_weighted_sales(const string curr_month){ 

        for(int cuisine=0; cuisine<5; cuisine++){
            WSG[cuisine] += monthly_data[curr_month].monthly_sales[0] + monthly_data[curr_month].monthly_rating[cuisine] / 100;
        }
    }


    // function to display a report of the sales of this restaurant at any month
    // this function will be called to display the report of any restaurant at any month
    // Inside the Restaurant class
    void display_monthly_report(const string &target_month) const {
        cout << "Report for Restaurant " << ID << " in " << target_month << ":" << endl;

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
    double* calculate_period_sales(const string &start_date, const string &end_date){
        double* sales = new double[6]; 
        fill(sales, sales+6, 0); // initialize them to zero

        // iterate over the daily sales within the specified period
        auto date_iter = daily_data.lower_bound(start_date);
        while(date_iter != daily_data.end() && date_iter->first <= end_date){
            // iterate over the cuisines
            for(int cuisine = 0; cuisine < 6; cuisine++){
                sales[cuisine] += date_iter->second.daily_sales[cuisine];
            }
            date_iter++;    
        }
        return sales;

        // DO NOT FORGET TO DELETE THE SALES AFTER USING THEM TO AVOID MEMORY LEAK
    }

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
    double WSG[5]= {0}; //initialize at zero value

    static int restaurantNum; //for the ID initialzed at 0 it increments everytime a restaurant is created
    // ******************************* generate the Id ************************************************

    // function to generate the id
    // so far this function depends on the file containing the wilayas and cities and thier corresponding numbers
    // ideas: add function to transform wilayas and cities to numbers and vice versa
    // still don't get the cities and districts thing
    void generate_id(const string &wilaya, const string &city){
        void generate_id(const string& wilaya, const string& city) {
        //the ID is composed of: wilaya code|city code|6 digits number 
        string SixDigitsNum = "000000" + to_string(restaurantNum); 
        //If the restaurant count has fewer than 6 digits, 
        //the string "000000" is used to pad and fill the remaining 
        //digits to ensure a fixed width of 6 characters.
        SixDigitsNum = SixDigitsNum.substr(SixDigitsNum.length() - 6); //to take the last 6 characters

        ID = wilaya + city + SixDigitsNum;
    }
    }

};



#endif
