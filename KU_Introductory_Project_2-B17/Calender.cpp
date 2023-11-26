#include "Calender.h"

Calender::Calender()
{
}

void Calender::setHighestKey()
{
	for (Schedule sch : allSchs) {
		int currSchKey = sch.getKey();
		if (highestKey < currSchKey) {
			highestKey = currSchKey;
		}
	}
}

int Calender::getHighestKey()
{
	return highestKey;
}
