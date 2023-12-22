#include"Month.h"
class Year
{
public:
	Month months[12];

	Year();//default constructor
	Year(int); 

	//setters and getters
	void setYear(const int);
	int getYear() const;
	void setNextPtr(Year*);
	Year* getNextPtr() const;

	//set the 5 winners in on a specefic month 
	void setWinners(int, Restaurant[]);

private:
	int year; //the year associated with this object
	Year* next; //ptr to the next year
};

