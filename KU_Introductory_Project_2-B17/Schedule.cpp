#include "Schedule.h"

Schedule::Schedule(string t, string sd, string ed, string ca, string me, string rED, int cy, int k)
{
	title = t;
	startDate = sd;
	endDate = ed;
	category = ca;
	memo = me;
	rptEndDate = rED;
	cycle = cy;
	key = k;
}

void Schedule::print()
{
	cout << "제목: " << title << "\n";
	cout << "카테고리: " << category << "\n";
	cout << "날짜: " << startDate << " ~ " << endDate << "\n";
	cout << "메모: " << memo << "\n\n";
	//출력은 나중에 추가할게요..
}
