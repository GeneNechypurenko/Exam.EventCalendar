#include "Display.h"

void DisplayListEmpty() {

    short x = 48, y = 13;

    system("cls");
    ToolsTextColor(STANDART);
    ToolsSetCoords(x, y);
    cout << "Список порожній!";
    ToolsPause();
    return;
}

void DisplayCurrentDate(const CurrentDate& curdate) {

    ToolsTextColor(STANDART);
    ToolsSetCoords(0, 0);
    cout << curdate.currentdate.day << " " << curdate.currentdate.weekday << "." << curdate.currentdate.monthname << "." << curdate.currentdate.year;
}

void DisplayMenu(const CurrentDate& curdate, const char* menu[], int row, int select) {

	short x = 45, y = 11;
	char marker = 149;

	system("cls");

    DisplayCurrentDate(curdate);

	for (int i = 0; i < row; i++) {

		ToolsSetCoords(x, y++);

		if (i == select) {
			ToolsTextColor(HIGHLIGHT);
			cout << " " << marker << " ";
			cout << menu[i] << endl;
		}

		else {
			ToolsTextColor(STANDART);
			cout << "   ";
			cout << menu[i] << endl;
		}
	}
}

void DisplayStartItems(Calendar(&cal)[CAL_ROW][CAL_COL], int year, int month, int day) {

    short x = 48, y = 11;

    ToolsSetCoords(x, y);
    cout << "введіть назву події";

    ToolsSetCoords(x + 5, y + 2);
    cout << cal[year][month].day[day] << " " << cal[year][month].weekday[day]  << " " << cal[year][month].monthname << " " << cal[year][0].year;

    ToolsSetCoords(x + 11, y + 3);
    cout << "середній";
}

void DisplayAdd(EventList& list, Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate) {

	short x = 48, y = 12;
	int row = 3;

    Event* event = new Event;
	const char* add[]{ " ", "дата", "приоритет" };

	system("cls");

    DisplayCurrentDate(curdate);

	ToolsTextColor(HIGHLIGHT);
	ToolsSetCoords(x, y);

	for (int i = 0; i < row; i++) {

		ToolsTextColor(STANDART);
		ToolsSetCoords(x, y++);
		cout << add[i] << endl;
	}

    LogicInitEvent(event, cal, curdate);
    LogicAddEvent(list, event);

    ToolsPause();
}

void DisplayPrint(const EventList& list, const CurrentDate& curdate, Calendar (&cal)[CAL_ROW][CAL_COL]) {

    short x = 45, y = 11;

    int row = 6;
    int i = 0;

    if (list.size == 0)
        DisplayListEmpty();

    else {

        const char* out[]
        {
        "Вивести список подій",
        "Список подій на рік",
        "Список подій на місяць",
        "Список подій на тиждень",
        "Список подій за датою",
        "До головного меню"
        };

        while (true) {

            DisplayMenu(curdate, out, row, i);

            char action = _getch();
            if (action == 0 || action == 224)
                action = _getch();

            if (action == UP)
                i = (i - 1 + row) % row;

            else if (action == DOWN)
                i = (i + 1) % row;

            else if (action == ENTER) {

                if (i == 0)
                    PrintList(list);
                else if (i == 1)
                    PrintListCurYear(list, curdate);
                else if (i == 2)
                    PrintListCurMonth(list, curdate);
                else if (i == 3)
                    PrintListCurWeek(list, curdate, cal);
                else if (i == 4)
                    PrintListByDate(list, curdate, cal);
                else if (i == 5)
                    return;
            }
        }
        ToolsPause();
    }
}

void DisplaySearch(const EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    short x = 45, y = 11;

    int row = 5;
    int i = 0;

    if (list.size == 0)
        DisplayListEmpty();

    else {

        const char* search[]
        {
        "Вивести список",
        "Пошук за датою",
        "Пошук за назвою",
        "Пошук за індексом",
        "До головного меню"
        };

        while (true) {

            DisplayMenu(curdate, search, row, i);

            char action = _getch();
            if (action == 0 || action == 224)
                action = _getch();

            if (action == UP)
                i = (i - 1 + row) % row;

            else if (action == DOWN)
                i = (i + 1) % row;

            else if (action == ENTER) {

                if (i == 0)
                    PrintList(list);
                else if (i == 1)
                    PrintSearchByDate(list, curdate, cal);
                else if (i == 2)
                    PrintSearchByName(list, curdate);
                else if (i == 3)
                    PrintByIndex(list, curdate);
                else if (i == 4)
                    return;
            }
        }
        ToolsPause();
    }
}

void DisplayRemove(EventList& list, const CurrentDate& curdate) {

    int index = 0;

    if(list.size == 0)
        DisplayListEmpty();

    else {

        PrintList(list);
        SearchByIndex(curdate, list, index);
        LogicRemoveEvent(list, index);
        PrintList(list);
    }
}

void DisplayEdit(EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    int index = 0;

    if (list.size == 0)
        DisplayListEmpty();

    else {

        PrintList(list);

        SearchByIndex(curdate, list, index);

        short x = 48, y = 12;
        int row = 3;
        const char* add[]{ " ", "дата", "приоритет" };

        system("cls");

        DisplayCurrentDate(curdate);

        ToolsTextColor(HIGHLIGHT);
        ToolsSetCoords(x, y);

        for (int i = 0; i < row; i++) {

            ToolsTextColor(STANDART);
            ToolsSetCoords(x, y++);
            cout << add[i] << endl;
        }

        LogicEditEvent(list, curdate, cal, index);

        PrintList(list);
    }
}

void DisplaySort(EventList& list, const CurrentDate& curdate) {

    short x = 45, y = 12;

    int row = 4;
    int i = 0;

    if (list.size == 0)
        DisplayListEmpty();

    else {

        const char* sort[]
        {
          "Вивести список",
          "Сортування за датою",
          "Сортування за приоритетом",
          "До головного меню"
        };

        while (true) {

            DisplayMenu(curdate, sort, row, i);

            char action = _getch();
            if (action == 0 || action == 224)
                action = _getch();

            if (action == UP)
                i = (i - 1 + row) % row;

            else if (action == DOWN)
                i = (i + 1) % row;

            else if (action == ENTER) {

                if (i == 0)
                    PrintList(list);
                else if (i == 1) {
                    LogicSortByDate(list);
                    PrintList(list);
                }
                else if (i == 2) {
                    LogicSortByPrior(list);
                    PrintList(list);
                }
                else if (i == 3)
                    return;
            }
        }
        ToolsPause();
    }
}