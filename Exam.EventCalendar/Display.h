#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Global.h"
#include "Tools.h"
#include "Logic.h"
#include "Print.h"
#include "Select.h"
#include "Search.h"

using namespace std;

void DisplayListEmpty();

void DisplayCurrentDate(const CurrentDate& curdate);

void DisplayMenu(const CurrentDate& curdate, const char* menu[], int row, int select);

void DisplayStartItems(Calendar(&cal)[CAL_ROW][CAL_COL], int year, int month, int day);

void DisplayAdd(EventList& list, Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate);

void DisplayPrint(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

void DisplaySearch(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

void DisplayRemove(EventList& list, const CurrentDate& curdate);

void DisplayEdit(EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

void DisplaySort(EventList& list, const CurrentDate& curdate);
