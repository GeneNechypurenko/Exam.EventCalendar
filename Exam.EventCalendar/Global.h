#pragma once
#include <iostream>

using namespace std;

enum sizes {
    CAL_ROW = 5,
    WEEKDAY_ROW = 7,
    MENU_ROW = 7,
    CAL_COL = 12
};

enum navikeys {
    ENTER = 13,
    ESC = 27,
    UP = 72,
    DOWN = 80
};

enum textcolor {
    STANDART = 15,
    HIGHLIGHT = 3
};

enum menutitles {
    ADD,
    PRINT,
    SEARCH,
    REMOVE,
    EDIT,
    SORT,
    EXIT
};

struct Date {
    int year;
    int month;
    int day;
    char monthname[4];
    char weekday[3];
};

struct CurrentDate {
    Date currentdate;
};

struct Calendar {
    int year;
    int month;
    int* day = nullptr;
    char monthname[4];
    char(*weekday)[3];
};

struct Event {
    Date date;
    int priority;
    char priorstr[10];
    char eventname[260];
};
struct EventList {
    Event** eventlist = nullptr;
    int size = 0;
};
