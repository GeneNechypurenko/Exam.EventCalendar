#include "Search.h"

void SearchYear(Calendar(&cal)[CAL_ROW][CAL_COL], int& year) {

    short x = 60, y = 13;

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

        else if (action == ENTER)
            break;
    }
}

void SearchMonth(Calendar(&cal)[CAL_ROW][CAL_COL], int& year, int& month) {

    short x = 56, y = 13;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][month].monthname;

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

        else if (action == ENTER)
            break;
    }
}

void SearchDay(Calendar(&cal)[CAL_ROW][CAL_COL], int& year, int& month, int& day) {

    short x = 58, y = 14;

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x, y);
    cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];

    int size = 0;

    LogicSetSize(cal, size, year, month);

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

        else if (action == ENTER)
            break;
    }
}

void SearchByDate(Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate, int& year, int& month) {

    short x = 48, y = 12;

    system("cls");

    DisplayCurrentDate(curdate);

    ToolsSetCoords(x, y);
    cout << "вкажіть дату для пошуку:";

    ToolsSetCoords(x + 8, y + 1);
    cout << cal[year][month].monthname << " " << cal[year][0].year;

    SearchYear(cal, year);
    SearchMonth(cal, year, month);
}

void SearchByDate(Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate, int& year, int& month, int& day) {

    short x = 48, y = 12;

    system("cls");

    DisplayCurrentDate(curdate);

    ToolsSetCoords(x, y);
    cout << "вкажіть дату для пошуку:";

    ToolsSetCoords(x + 8, y + 1);
    cout << cal[year][month].monthname << " " << cal[year][0].year;

    ToolsSetCoords(x + 10, y + 2);
    cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day];

    SearchYear(cal, year);
    SearchMonth(cal, year, month);
    SearchDay(cal, year, month, day);
}

char* SearchByName(const CurrentDate& curdate, char search_name[], const int buffer) {

    short x = 48, y = 12;

    system("cls");

    DisplayCurrentDate(curdate);
    ToolsSetCoords(x, y);
    cout << "введіть назву для пошуку:";

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x + 8, y + 1);
    cin.getline(search_name, buffer);
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    return search_name;
}

void SearchByIndex(const CurrentDate& curdate, const EventList& list, int& index) {

    short x = 48, y = 12;

    system("cls");

    DisplayCurrentDate(curdate);
    ToolsSetCoords(x, y);
    cout << "індекс пошуку події:";

    ToolsTextColor(HIGHLIGHT);
    ToolsSetCoords(x + 21, y);
    cout << index + 1;

    while (true) {

        char action = _getch();
        if (action == 0 || action == 224)
            action = _getch();

        if (action == UP) {

            ToolsSetCoords(x + 21, y);
            cout << "     ";
            index = (index - 1 + list.size) % list.size;
            ToolsSetCoords(x + 21, y);
            cout << index + 1;
        }

        else if (action == DOWN) {

            ToolsSetCoords(x + 21, y);
            cout << "     ";
            index = (index + 1) % list.size;
            ToolsSetCoords(x + 21, y);
            cout << index + 1;
        }

        else if (action == ENTER)
            break;
    }
}