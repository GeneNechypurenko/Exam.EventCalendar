#include "Select.h"

void SelectInputEventName(Event*& event) {

    short x = 48, y = 12;
    int buffer = 26;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cin.getline(event->eventname, buffer);
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    ToolsTextColor(STANDART);
}
void SelectInputEventName(EventList& list, int index) {

    short x = 48, y = 12;
    int buffer = 26;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cin.getline(list.eventlist[index]->eventname, buffer);
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    ToolsTextColor(STANDART);
}

void SelectYear(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], int& year) {

    short x = 63, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][0].year;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            year = (year - 1 + CAL_ROW) % CAL_ROW;
            ToolsSetCoords(x, y);
            cout << cal[year][0].year;
        }

        else if (action == DOWN) {

            year = (year + 1) % CAL_ROW;
            ToolsSetCoords(x, y);
            cout << cal[year][0].year;
        }

        else if (action == ENTER) {

            event->date.year = cal[year][0].year;
            ToolsTextColor(STANDART);
            break;
        }
    }
}
void SelectYear(EventList& list, int index, Calendar(&cal)[CAL_ROW][CAL_COL], int& year) {

    short x = 63, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][0].year;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            year = (year - 1 + CAL_ROW) % CAL_ROW;
            ToolsSetCoords(x, y);
            cout << cal[year][0].year;
        }

        else if (action == DOWN) {

            year = (year + 1) % CAL_ROW;
            ToolsSetCoords(x, y);
            cout << cal[year][0].year;
        }

        else if (action == ENTER) {

            list.eventlist[index]->date.year = cal[year][0].year;
            ToolsTextColor(STANDART);
            break;
        }
    }
}

void SelectMonth(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int& month) {

    short x = 59, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][month].monthname;

    const int buffer = 4;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            month = (month - 1 + CAL_COL) % CAL_COL;
            ToolsSetCoords(x, y);
            cout << cal[year][month].monthname;
        }

        else if (action == DOWN) {

            month = (month + 1) % CAL_COL;
            ToolsSetCoords(x, y);
            cout << cal[year][month].monthname;
        }

        else if (action == ENTER) {

            strcpy_s(event->date.monthname, buffer, cal[year][month].monthname);
            event->date.month = cal[year][month].month;
            ToolsTextColor(STANDART);
            break;
        }
    }
}
void SelectMonth(EventList& list, int index, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int& month) {

    short x = 59, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][month].monthname;

    const int buffer = 4;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            month = (month - 1 + CAL_COL) % CAL_COL;
            ToolsSetCoords(x, y);
            cout << cal[year][month].monthname;
        }

        else if (action == DOWN) {

            month = (month + 1) % CAL_COL;
            ToolsSetCoords(x, y);
            cout << cal[year][month].monthname;
        }

        else if (action == ENTER) {

            strcpy_s(list.eventlist[index]->date.monthname, buffer, cal[year][month].monthname);
            list.eventlist[index]->date.month = cal[year][month].month;
            ToolsTextColor(STANDART);
            break;
        }
    }
}

void SelectDay(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int month, int day) {

    short x = 53, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];

    int size = 0;

    LogicSetSize(cal, size, year, month);

    const int buffer = 3;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            ToolsSetCoords(x, y);
            cout << "     ";
            day = (day - 1 + size) % size;
            ToolsSetCoords(x, y);
            cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];
        }

        else if (action == DOWN) {

            ToolsSetCoords(x, y);
            cout << "     ";
            day = (day + 1) % size;
            ToolsSetCoords(x, y);
            cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];
        }

        else if (action == ENTER) {

            event->date.day = cal[year][month].day[day];
            strcpy_s(event->date.weekday, buffer, cal[year][month].weekday[day]);
            ToolsTextColor(STANDART);
            break;
        }
    }
}
void SelectDay(EventList& list, int index, Calendar(&cal)[CAL_ROW][CAL_COL], int year, int month, int day) {

    short x = 53, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];

    int size = 0;

    LogicSetSize(cal, size, year, month);

    const int buffer = 3;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            ToolsSetCoords(x, y);
            cout << "     ";
            day = (day - 1 + size) % size;
            ToolsSetCoords(x, y);
            cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];
        }

        else if (action == DOWN) {

            ToolsSetCoords(x, y);
            cout << "     ";
            day = (day + 1) % size;
            ToolsSetCoords(x, y);
            cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];
        }

        else if (action == ENTER) {

            list.eventlist[index]->date.day = cal[year][month].day[day];
            strcpy_s(list.eventlist[index]->date.weekday, buffer, cal[year][month].weekday[day]);
            ToolsTextColor(STANDART);
            break;
        }
    }
}

void SelectPrior(Event*& event) {

    short x = 59, y = 14;
    ToolsTextColor(HIGHLIGHT);

    const char* prior[]{ "високий","середній","низький" };

    int row = 3;
    int i = 1;

    const int buffer = 10;

    ToolsSetCoords(x, y);
    cout << prior[i];

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            ToolsSetCoords(x, y);
            cout << "         ";
            i = (i - 1 + row) % row;
            ToolsSetCoords(x, y);
            cout << prior[i];
        }

        else if (action == DOWN) {

            ToolsSetCoords(x, y);
            cout << "         ";
            i = (i + 1) % row;
            ToolsSetCoords(x, y);
            cout << prior[i];
        }

        else if (action == ENTER) {

            strcpy_s(event->priorstr, buffer, prior[i]);
            ToolsTextColor(STANDART);
            break;
        }
    }
}
void SelectPrior(EventList& list, int index) {

    short x = 59, y = 14;
    ToolsTextColor(HIGHLIGHT);

    const char* prior[]{ "високий","середній","низький" };

    int row = 3;
    int i = 1;

    const int buffer = 10;

    ToolsSetCoords(x, y);
    cout << prior[i];

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            ToolsSetCoords(x, y);
            cout << "         ";
            i = (i - 1 + row) % row;
            ToolsSetCoords(x, y);
            cout << prior[i];
        }

        else if (action == DOWN) {

            ToolsSetCoords(x, y);
            cout << "         ";
            i = (i + 1) % row;
            ToolsSetCoords(x, y);
            cout << prior[i];
        }

        else if (action == ENTER) {

            strcpy_s(list.eventlist[index]->priorstr, buffer, prior[i]);
            ToolsTextColor(STANDART);
            break;
        }
    }
}
