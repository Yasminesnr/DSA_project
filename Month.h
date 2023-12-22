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

	//function to set a winner in one cuisine (i is the index of the cuisine)
	//1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
	void setOneCuisineWinner(int i, Restaurant restaurant);

	// function to retrieve the winner for only one cuisine (i is the index of the cuisine)
	//1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
	Restaurant getOneCuisineWinner(int i) const;

private:
	int month; // the actual month from 1 to 12
	Restaurant fiveWinners[5]; //1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
};

