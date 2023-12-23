#include"Restaurant.h"

#include<string>
using namespace std;

int main() {
    // Specify the path of the csv file
    string csvFile = "Restaurants_dataset.csv";

    // Specify the number of restaurants you want to generate
    int numRestaurants = 15000; // Change this to your desired number

    // Call the function to write restaurants to CSV
    Restaurant::RestaurantsToCSV(csvFile, numRestaurants);

    return 0;
}
