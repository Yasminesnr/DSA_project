#include"Restaurant.h"
class Month
{
public:
	Month(); //default constructor
	Month(int, Restaurant[]); //parametrized constructor

	//setters and getters
	void setMonth(const int);
	int getMonth() const;

	//function to set the 5 restaurants winners in each cuisine
	void setFiveWinners(Restaurant array[]);

	//function to retrieve the 5 winners in each cuisine a return a pointer to an array of restaurants
	Restaurant* getFiveWinners() const;

private:
	int month; // the actual month from 1 to 12
	Restaurant fiveWinners[5]; //1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
};

