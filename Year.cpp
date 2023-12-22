#include "Year.h"

Year::Year()
{
	setYear(2000);
	for (int i = 0; i < 12; i++) {
		months[i].setMonth(i + 1);
	}
	setNextPtr(nullptr);
}

Year::Year(int year)
{
	setYear(year);
	for (int i = 0; i < 12; i++) {
		months[i].setMonth(i + 1);
	}
	setNextPtr(nullptr);
}

void Year::setYear(const int year)
{
	if (year < 0)
		cout << "Unvalid year!";
	else
		this->year = year;
}

int Year::getYear() const
{
	return year;
}

void Year::setWinners(int month, Restaurant restaurants[])
{
	months[month-1].setFiveWinners(restaurants);
}

void Year::setNextPtr(Year* nextyear)
{
	next = nextyear;
}

Year* Year::getNextPtr() const
{
	return next;
}
