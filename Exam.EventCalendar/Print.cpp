#include "Print.h"

void PrintEvent(const EventList& list, int i, short x, short y) {

    ToolsSetCoords(x, y++);
    ToolsTextColor(HIGHLIGHT);
    cout << "_________________________" << endl;

    ToolsSetCoords(x, y++);
    cout << "подія[" << i + 1 << "] : "
        << list.eventlist[i]->date.day << " "
        << list.eventlist[i]->date.weekday << "."
        << list.eventlist[i]->date.monthname << "."
        << list.eventlist[i]->date.year << endl;

    ToolsTextColor(STANDART);
    ToolsSetCoords(x, y++);
    cout << list.eventlist[i]->eventname << endl;

    ToolsSetCoords(x, y++);
    cout << "приоритет події " << list.eventlist[i]->priorstr << endl;

    ToolsSetCoords(x, y++);
    cout << "_________________________" << endl;
}

void PrintList(const EventList& list) {

    short x = 48, y = 0;
    int indent = 6;

    system("cls");

    for (int i = 0; i < list.size; i++) {

        PrintEvent(list, i, x, y);
        y += indent;
    }

    ToolsPause();
}

void PrintListCurYear(const EventList& list, const CurrentDate& curdate) {

    short x = 48, y = 0;
    int indent = 6;

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (list.eventlist[i]->date.year == curdate.currentdate.year) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}

void PrintListCurMonth(const EventList& list, const CurrentDate& curdate) {

    short x = 48, y = 0;
    int indent = 6;

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (list.eventlist[i]->date.year == curdate.currentdate.year && list.eventlist[i]->date.month == curdate.currentdate.month) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}

void PrintListCurWeek(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    short x = 48, y = 0;
    int indent = 6;

    int year = curdate.currentdate.year;
    int month = curdate.currentdate.month;
    int weekstart = curdate.currentdate.day;
    int weekend = 0;

    LogicSetIndexes(cal, year, month, weekstart, weekend);

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (list.eventlist[i]->date.year == cal[year][month].year &&
            list.eventlist[i]->date.month == cal[year][month].month &&
            list.eventlist[i]->date.day >= weekstart + 1 && list.eventlist[i]->date.day <= weekend + 1) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}

void PrintListByDate(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    short x = 48, y = 0;
    int indent = 6;

    int year = curdate.currentdate.year;
    int month = curdate.currentdate.month;
    int empty_day = 0;
    int empty_weekday = 0;

    LogicSetIndexes(cal, year, month, empty_day, empty_weekday);
    SearchByDate(cal, curdate, year, month);

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (list.eventlist[i]->date.year == cal[year][0].year &&
            list.eventlist[i]->date.month == cal[year][month].month) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}

void PrintSearchByDate(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    short x = 48, y = 0;
    int indent = 6;

    int year = curdate.currentdate.year;
    int month = curdate.currentdate.month;
    int day = curdate.currentdate.day;
    int empty = 0;

    LogicSetIndexes(cal, year, month, day, empty);
    SearchByDate(cal, curdate, year, month, day);

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (list.eventlist[i]->date.day == cal[year][month].day[day] &&
            list.eventlist[i]->date.month == cal[year][month].month &&
            list.eventlist[i]->date.year == cal[year][0].year) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}

void PrintSearchByName(const EventList& list, const CurrentDate& curdate) {

    short x = 48, y = 0;
    int indent = 6;

    const int buffer = 26;
    char search_name[buffer];
    strcpy_s(search_name, buffer, SearchByName(curdate, search_name, buffer));

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (strncmp(search_name, list.eventlist[i]->eventname, 1) == 0 ||
            strncmp(search_name, list.eventlist[i]->eventname, 3) == 0 ||
            strcmp(search_name, list.eventlist[i]->eventname) == 0) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}

void PrintByIndex(const EventList& list, const CurrentDate& curdate) {

    short x = 48, y = 0;
    int indent = 6;

    int index = 0;

    SearchByIndex(curdate, list, index);

    system("cls");

    for (int i = 0; i < list.size; i++) {

        if (i == index) {

            PrintEvent(list, i, x, y);
            y += indent;
        }
    }

    ToolsPause();
}