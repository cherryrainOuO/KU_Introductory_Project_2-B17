#include "Schedule.h"

Schedule::Schedule(string t, string sd, string ed, string ca, string me)
{
	title = t;
	startDate = sd;
	endDate = ed;
	category = ca;
	memo = me;
}

void Schedule::print()
{
	cout << "제목: " << title << "\n";
	cout << "카테고리: " << category << "\n";
	cout << "날짜: " << startDate << " ~ " << endDate << "\n";
	cout << "메모: " << memo << "\n";
}
