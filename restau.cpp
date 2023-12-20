#include <iostream>
#include <unordered_map>
#include "Restaurant.h"

int main() {
    // Sample data for daily and monthly data
    unordered_map<string, DailyData> dailyData;
    unordered_map<string, MonthlyData> monthlyData;
    string wilaya = "Algiers";
    string city = "Algiers";
    double wsg[5] = {0.1, 0.2, 0.3, 0.4, 0.5};  // Sample Weighted Sales Growth

    // Create a Restaurant instance
    Restaurant myRestaurant("123", "My Restaurant", 10, dailyData, monthlyData, wilaya, city, wsg);

    // Invoke functions to update data
    myRestaurant.update_daily_sales("2023-01-01", 100, 150, 200, 80, 120);
    myRestaurant.update_monthly_sales("2023-01");
    myRestaurant.update_monthly_rating("2023-01");
    myRestaurant.update_monthly_pub("2023-01");
    myRestaurant.update_ROI("2023-01");
    myRestaurant.update_weighted_sales("2023-01");

    // Display a report for a specific month
    myRestaurant.display_monthly_report("2023-01");

    // Calculate sales for a specific period
    double* periodSales = myRestaurant.calculate_period_sales("2023-01-01", "2023-01-31");

    // Display period sales
    std::cout << "Period Sales:" << std::endl;
    for (int cuisine = 0; cuisine < 6; cuisine++) {
        std::cout << "   Cuisine " << cuisine << ": $" << periodSales[cuisine] << std::endl;
    }

    // Don't forget to delete the dynamically allocated array
    delete[] periodSales;

    return 0;
}
