#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>

#include "Logic.h"
#include "Tools.h"
#include "Display.h"

using namespace std;

void PrintEvent(const EventList& list, int i, short x, short y);

void PrintList(const EventList& list);

void PrintListCurYear(const EventList& list, const CurrentDate& curdate);

void PrintListCurMonth(const EventList& list, const CurrentDate& curdate);

void PrintListCurWeek(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

void PrintListByDate(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

void PrintSearchByDate(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

void PrintSearchByName(const EventList& list, const CurrentDate& curdate);

void PrintByIndex(const EventList& list, const CurrentDate& curdate);
