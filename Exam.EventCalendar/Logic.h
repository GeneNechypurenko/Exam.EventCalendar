#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>

#include "Logic.h"
#include "Tools.h"
#include "Display.h"
#include "Print.h"
#include "Select.h"
#include "Search.h"

using namespace std;

// запись-чтение из файла
void LogicSaveData(FILE* file, EventList& list, const char* filename);
void LogicReadData(FILE* file, EventList& list, const char* filename);

// инициализация текущей даты
void LogicInitCurMonthName(CurrentDate& curdate);
void LogicInitCurWeekday(CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);
void LogicInitCurrentDate(CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]);

// инициализация календаря
void LogicInitCal(Calendar(&cal)[CAL_ROW][CAL_COL], const char* monthname[], const char* weekday[], int year[CAL_ROW]);
void LogicSetSize(Calendar(&cal)[CAL_ROW][CAL_COL], int& size, int n, int i);
void LogicShiftLeft(const char* weekday[], int shift);
void LogicShiftRight(const char* weekday[], int shift);
void LogicSetShift(Calendar(&cal)[CAL_ROW][CAL_COL], int& shift, int n, int i);

// очистка памяти
void LogicCleanMem(Calendar(&cal)[CAL_ROW][CAL_COL]);
void LogicCleanMem(EventList& list);

// иниицализация int priority структуры Event значениями
void LogicInitPriorValue(Event*& event);
void LogicInitPriorValue(EventList& list, int index);

void LogicInitEvent(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate);
void LogicAddEvent(EventList& list, Event*& event);

// получение индексов массива календаря согласно текущей дате
void LogicSetIndexes(Calendar(&cal)[CAL_ROW][CAL_COL], int& year, int& month, int& weekstart, int& weekend);

void LogicRemoveEvent(EventList& list, int index);

void LogicEditEvent(EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL], int index);

void LogicSortByDate(EventList& list);
void LogicSortByPrior(EventList& list);