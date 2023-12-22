#include "Month.h"

Month::Month():month(1)
{
	for (int i = 0; i < 5; i++) {
		fiveWinners[i] = Restaurant();
	}
}

Month::Month(int month,Restaurant array[])
{
	setMonth(month);
	setFiveWinners(array);
}

void Month::setMonth(const int month)
{
	if (month < 1 || month>12)
		cout << "unvalid month!";
	else
		this->month = month;
}

int Month::getMonth() const
{
	return month;
}

void Month::setFiveWinners(Restaurant array[])
{
	for (int i = 0; i < 5; i++) {
		fiveWinners[i] = array[i];
	}
}

Restaurant* Month::getFiveWinners() const
{
	Restaurant* winners = new Restaurant[5];
	for (int i = 0; i < 5; i++) {
		winners[i] = fiveWinners[i];
	}
	return winners;
}

Restaurant Month::getOneCuisineWinner(int i) const
{
	return this->fiveWinners[i];
}
