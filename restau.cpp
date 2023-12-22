#include "Restaurant.h"
#include <iostream>


#include "Restaurant.h"
#include <iostream>

void testUpdateCost() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Call update_cost with sample values
    std::string date = "2023-01-01";

    // Add an entry for the date in daily_data if it doesn't exist
    auto result = restaurant.getDailyData().insert({ date, DailyData() });

    // Check if the insertion was successful or if the date already existed
    if (result.second) {
        std::cout << "Entry for date " << date << " added successfully." << std::endl;
    }
    else {
        std::cout << "Entry for date " << date << " already exists." << std::endl;
    }

    double cost = restaurant.update_cost(date, 1000.0, 500.0, 200.0, 150.0, 50.0, 100.0, 75.0, 30.0);

    // Print the result
    std::cout << "Daily Cost on " << date << ": $" << cost << std::endl;
}

void testUpdateDailySales() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Call update_daily_sales with sample values
    std::string date = "2023-01-01";

    // Add an entry for the date in daily_data if it doesn't exist
    auto result = restaurant.getDailyData().insert({ date, DailyData() });

    // Check if the insertion was successful or if the date already existed
    if (result.second) {
        std::cout << "Entry for date " << date << " added successfully." << std::endl;
    }
    else {
        std::cout << "Entry for date " << date << " already exists." << std::endl;
    }

    // Call update_daily_sales with sales values
    restaurant.update_daily_sales(date, 100.0, 150.0, 200.0, 50.0, 75.0);

    // Print the updated daily sales
    const auto& dailyData = restaurant.getDailyData();
    auto iter = dailyData.find(date);
    if (iter != dailyData.end()) {
        const auto& sales = iter->second.daily_sales;
        std::cout << "Updated Daily Sales on " << date << ":" << std::endl;
        for (int cuisine = 0; cuisine < 6; cuisine++) {
            std::cout << "   Cuisine " << cuisine << ": $" << sales[cuisine] << std::endl;
        }
    }
    else {
        std::cerr << "Error: Date not found in daily_data after update_daily_sales." << std::endl;
    }
}

// Define a function to test update_monthly_sales
void testUpdateMonthlySales() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for daily sales for a specific month
    std::string target_month = "2023-01";
    for (int day = 1; day <= 10; day++) {
        std::string date = target_month + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        auto result = restaurant.getDailyData().insert({ date, DailyData() });
        if (!result.second) {
            std::cerr << "Error: Entry for date " << date << " already exists." << std::endl;
        }
        // Assume some daily sales values (you can modify these)
        restaurant.update_daily_sales(date, 50.0, 30.0, 20.0, 10.0, 40.0);
    }

    // Call update_monthly_sales for the target month
    restaurant.update_monthly_sales(target_month);

    // Print the updated monthly sales
    const auto& monthlyData = restaurant.getMonthlyData();
    auto iter = monthlyData.find(target_month);
    if (iter != monthlyData.end()) {
        const auto& sales = iter->second.monthly_sales;
        std::cout << "Updated Monthly Sales for " << target_month << ":" << std::endl;
        for (int cuisine = 0; cuisine < 6; cuisine++) {
            std::cout << "   Cuisine " << cuisine << ": $" << sales[cuisine] << std::endl;
        }
    }
    else {
        std::cerr << "Error: Month not found in monthly_data after update_monthly_sales." << std::endl;
    }
}

// Define a function to test update_monthly_rating
void testUpdateMonthlyRating() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for daily rating for a specific month
    std::string target_month = "2023-01";
    for (int day = 1; day <= 10; day++) {
        std::string date = target_month + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        auto result = restaurant.getDailyData().insert({ date, DailyData() });
        if (!result.second) {
            std::cerr << "Error: Entry for date " << date << " already exists." << std::endl;
        }
        // Assume some daily rating values (you can modify these)
        DailyData& dailyData = restaurant.getDailyData().at(date);
        dailyData.daily_rating[0] = 4.0;
        dailyData.daily_rating[1] = 3.5;
        dailyData.daily_rating[2] = 5.0;
        dailyData.daily_rating[3] = 4.5;
        dailyData.daily_rating[4] = 3.0;
    }

    // Call update_monthly_rating for the target month
    restaurant.update_monthly_rating(target_month);

    // Print the updated monthly rating
    const auto& monthlyData = restaurant.getMonthlyData();
    auto iter = monthlyData.find(target_month);
    if (iter != monthlyData.end()) {
        const auto& rating = iter->second.monthly_rating;
        std::cout << "Updated Monthly Rating for " << target_month << ":" << std::endl;
        for (int cuisine = 0; cuisine < 5; cuisine++) {
            std::cout << "   Cuisine " << cuisine + 1 << ": " << rating[cuisine] << std::endl;
        }
    }
    else {
        std::cerr << "Error: Month not found in monthly_data after update_monthly_rating." << std::endl;
    }
}

// Define a function to test update_monthly_pub
void testUpdateMonthlyPub() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for the date in daily_data
    std::string date1 = "2023-01-01";
    std::string date2 = "2023-01-02";
    restaurant.getDailyData()[date1] = DailyData();
    restaurant.getDailyData()[date2] = DailyData();

    // Update daily_pub for the dates
    restaurant.getDailyData()[date1].daily_pub = 50.0;
    restaurant.getDailyData()[date2].daily_pub = 75.0;

    // Call update_monthly_pub for the month of January 2023
    std::string target_month = "2023-01";
    restaurant.update_monthly_pub(target_month);

    // Print the result
    std::cout << "Monthly Advertising Cost in " << target_month << ": $" << restaurant.getMonthlyData()[target_month].monthly_pub << std::endl;

}

// Define a function to test update_ROI
// Function to test update_ROI for a specific month
// Function to test update_ROI for a specific month
void testUpdateROI() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 1.0, 2.0, 3.0, 4.0, 5.0 };

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for daily sales and advertising for a specific month
    std::string target_month = "2023-01";
    for (int day = 1; day <= 10; day++) {
        std::string date = target_month + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        auto result = restaurant.getDailyData().insert({ date, DailyData() });
        if (!result.second) {
            std::cerr << "Error: Entry for date " << date << " already exists." << std::endl;
        }
        // Assume some daily sales and advertising values (you can modify these)
        restaurant.update_daily_sales(date, 50.0, 30.0, 20.0, 10.0, 40.0);
        restaurant.getDailyData()[date].daily_pub = 10.0; // Daily advertising cost
    }

    // Update monthly_pub for the month of January 2023
    restaurant.update_monthly_pub(target_month);

    // Update monthly_sales for the month of January 2023
    restaurant.update_monthly_sales(target_month);

    // Call update_ROI for the month of January 2023
    restaurant.update_ROI(target_month);

    // Print the result
    std::cout << "Return of Investment (ROI) in " << target_month << ": " << restaurant.getMonthlyData()[target_month].ROI << std::endl;
}

// Function to test update_weighted_sales for a specific month
void testUpdateWeightedSales() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 }; // Assuming WSG is initialized to zero

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for daily sales and rating for a specific month
    std::string target_month = "2023-01";
    for (int day = 1; day <= 10; day++) {
        std::string date = target_month + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        auto result = restaurant.getDailyData().insert({ date, DailyData() });
        if (!result.second) {
            std::cerr << "Error: Entry for date " << date << " already exists." << std::endl;
        }
        // Assume some daily sales and rating values (you can modify these)
        restaurant.update_daily_sales(date, 50.0, 30.0, 20.0, 10.0, 40.0);
        restaurant.getDailyData()[date].daily_rating[0] = 4.5; // Rating for Cuisine 0
        restaurant.getDailyData()[date].daily_rating[1] = 3.8; // Rating for Cuisine 1
        restaurant.getDailyData()[date].daily_rating[2] = 4.0; // Rating for Cuisine 2
        restaurant.getDailyData()[date].daily_rating[3] = 4.2; // Rating for Cuisine 3
        restaurant.getDailyData()[date].daily_rating[4] = 3.9; // Rating for Cuisine 4
    }

    // Update monthly_sales and monthly_rating for the month of January 2023
    restaurant.update_monthly_sales(target_month);
    restaurant.update_monthly_rating(target_month);

    // Call update_weighted_sales for the month of January 2023
    restaurant.update_weighted_sales(target_month);

    // Print the result
    const double* wsgResult = restaurant.getWSG();
    std::cout << "Weighted Sales Growth (WSG) for " << target_month << ":" << std::endl;
    for (int cuisine = 0; cuisine < 5; cuisine++) {
        std::cout << "   Cuisine " << cuisine << ": " << wsgResult[cuisine] << std::endl;
    }
}

// Function to test display_monthly_report for a specific month
void testDisplayMonthlyReport() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 }; // Assuming WSG is initialized to zero

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for daily sales and rating for a specific month
    std::string target_month = "2023-01";
    for (int day = 1; day <= 10; day++) {
        std::string date = target_month + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        auto result = restaurant.getDailyData().insert({ date, DailyData() });
        if (!result.second) {
            std::cerr << "Error: Entry for date " << date << " already exists." << std::endl;
        }
        // Assume some daily sales and rating values (you can modify these)
        restaurant.update_daily_sales(date, 50.0, 30.0, 20.0, 10.0, 40.0);
        restaurant.getDailyData()[date].daily_rating[0] = 4.5; // Rating for Cuisine 0
        restaurant.getDailyData()[date].daily_rating[1] = 3.8; // Rating for Cuisine 1
        restaurant.getDailyData()[date].daily_rating[2] = 4.0; // Rating for Cuisine 2
        restaurant.getDailyData()[date].daily_rating[3] = 4.2; // Rating for Cuisine 3
        restaurant.getDailyData()[date].daily_rating[4] = 3.9; // Rating for Cuisine 4

        //restaurant.getDailyData()[date].daily_pub = 10.0;
    }

    // Update monthly_sales, monthly_rating, and ROI for the month of January 2023
    restaurant.update_monthly_sales(target_month);
    restaurant.update_monthly_rating(target_month);
    restaurant.update_ROI(target_month);
    restaurant.update_monthly_pub(target_month);

    // Call display_monthly_report for the month of January 2023
    restaurant.display_monthly_report(target_month);
}

// Function to test calculate_period_sales for a specific period
void testCalculatePeriodSales() {
    // Create an instance of Restaurant
    std::unordered_map<std::string, DailyData> ddata;
    std::unordered_map<std::string, MonthlyData> mdata;
    std::string w = "Wilaya";
    std::string c = "City";
    double wsg[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 }; // Assuming WSG is initialized to zero

    Restaurant restaurant("MyRestaurant", 10, w, c, wsg);

    // Add entries for daily sales for a specific month
    std::string target_month = "2023-01";
    for (int day = 1; day <= 10; day++) {
        std::string date = target_month + "-" + (day < 10 ? "0" : "") + std::to_string(day);
        auto result = restaurant.getDailyData().insert({ date, DailyData() });
        if (!result.second) {
            std::cerr << "Error: Entry for date " << date << " already exists." << std::endl;
        }
        // Assume some daily sales values (you can modify these)
        restaurant.update_daily_sales(date, 50.0, 30.0, 20.0, 10.0, 40.0);
    }

    // Call calculate_period_sales for the period from the 1st to the 5th day of January 2023
    std::string start_date = "2023-01-01";
    std::string end_date = "2023-01-05";
    double* period_sales = restaurant.calculate_period_sales(start_date, end_date);

    // Print the result
    std::cout << "Sales for the period from " << start_date << " to " << end_date << ":" << std::endl;
    for (int cuisine = 0; cuisine < 6; cuisine++) {
        std::cout << "   Cuisine " << cuisine << ": $" << period_sales[cuisine] << std::endl;
    }

    // Don't forget to delete the allocated memory to avoid memory leaks
    delete[] period_sales;
}

// Add this testing function to your main function
int main() {
    //// Call the testUpdateCost function
    //testUpdateCost();

    //// Call the testUpdateDailySales function
    //testUpdateDailySales();

    //// Call the testUpdateMonthlySales function
    //testUpdateMonthlySales();

    //// Call the testUpdateMonthlyRating function
    //testUpdateMonthlyRating();

    //// Call the testUpdateMonthlyPub function
    //testUpdateMonthlyPub();

    // Call the testUpdateROI function
    //testUpdateROI();

    // Call the testUpdateWeightedSales function
    //testUpdateWeightedSales();


    // Call the testDisplayMonthlyReport function
    testDisplayMonthlyReport();

    // Call the testCalculatePeriodSales function
    //testCalculatePeriodSales();

    return 0;
}

