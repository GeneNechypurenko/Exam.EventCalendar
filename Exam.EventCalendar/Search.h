#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Global.h"
#include "Tools.h"
#include "Logic.h"

using namespace std;

void SearchYear(Calendar(&cal)[CAL_ROW][CAL_COL], int& year);

void SearchMonth(Calendar(&cal)[CAL_ROW][CAL_COL], int& year, int& month);

void SearchDay(Calendar(&cal)[CAL_ROW][CAL_COL], int& year, int& month, int& day);

void SearchByDate(Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate, int& year, int& month);
void SearchByDate(Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate, int& year, int& month, int& day);

char* SearchByName(const CurrentDate& curdate, char search_name[], const int buffer);

void SearchByIndex(const CurrentDate& curdate, const EventList& list, int& index);
