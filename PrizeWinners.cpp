#include "PrizeWinners.h"

PrizeWinners::PrizeWinners(int firstYear)
{
	Year* newYear = new Year(firstYear);
	startYear = newYear;
	lastYear = newYear;
}

void PrizeWinners::addYear()
{
	int value = lastYear->getYear();
	Year* newYear = new Year(++value); //since we're talking about years then the value of the new year is just the previous year +1
	newYear->setNextPtr(nullptr);
	lastYear->setNextPtr(newYear);
	lastYear = newYear;
}

void PrizeWinners::traverse(Year* temp,int year)
{
	while (temp->getYear() != year)
		temp = temp->getNextPtr();
}


void PrizeWinners::set5PrizeWinners(int year, int month, Restaurant winners[])
{
	Year* temp = startYear;

	//traverse the linked list until we get to the wanted year
	traverse(temp, year);

	temp->setWinners(month,winners);
	
}

Restaurant* PrizeWinners::get5PrizeWinners(int year, int month)
{
	Year* temp = startYear;
	traverse(temp, year);

	Month targetMonth = temp->months[month - 1];

	return 	targetMonth.getFiveWinners();
}
