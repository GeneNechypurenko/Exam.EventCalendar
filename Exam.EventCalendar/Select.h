#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Global.h"
#include "Tools.h"
#include "Logic.h"
#include "Print.h"

using namespace std;


void SelectInputEventName(Event*& event);
void SelectInputEventName(EventList& list, int index);

void SelectYear(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], int& year);
void SelectYear(EventList& list, int index, Calendar(&cal)[CAL_ROW][CAL_COL], int& year);

void SelectMonth(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int& month);
void SelectMonth(EventList& list, int index, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int& month);

void SelectDay(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int month, int day);
void SelectDay(EventList& list, int index, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int month, int day);

void SelectPrior(Event*& event);
void SelectPrior(EventList& list, int index);