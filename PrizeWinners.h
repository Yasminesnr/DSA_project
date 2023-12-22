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
	PrizeWinners(int);

	//a function to insert a new year to the list
	void addYear();

	//function to traverse the list to get to a specific year
	void traverse(Year* ,int);

	//function to set the Prize Winners on a specific month
	void set5PrizeWinners(int year, int month, Restaurant winners[]);

	//function to retrieve the winners from any specefic month a return a pointer to an array of restaurants
	Restaurant* get5PrizeWinners(int year,int month);
};

