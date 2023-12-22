#include"Year.h"

//This class serves the purpose of both storing all prize winners
//and facilitating their retrieval at any given time.  


class PrizeWinners
{
public:
	Year* startYear; 
	//head of the linked list which represent a ptr that points 
	//to the year when the food service Koul Hani started working (made his first restaurant)
	Year* lastYear; //tail of the linked list 

	//Parameterized constructor
	PrizeWinners(int firstYear);

	//a function to insert a new year to the list
	void addYear();

	//function to traverse the list to get to a specific year
	void traverse(Year* temp,int year);

	//function to set the 5 Prize Winners on a specific month
	void set5PrizeWinners(int year, int month, Restaurant winners[]);

	//function to set a winner of one cuisine in one cuisine on any specefic month (i is the index of the cuisine)
	//1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
	void setOneCuisineWinner(int year, int mont, Restaurant restaurant, int i);

	//function to retrieve the 5 winners from any specefic month a return a pointer to an array of restaurants
	Restaurant* get5PrizeWinners(int year,int month);

	//function to get a winner of one cuisine in one cuisine on any specefic month (i is the index of the cuisine)
	//1: Algerian, 2: Chinese, 3: European, 4: Indian, 5: Syrian
	Restaurant getOneCuisineWinner(int year, int month, int i);
};

