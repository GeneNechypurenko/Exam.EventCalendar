#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "Global.h"
#include "Tools.h"
#include "Display.h"
#include "Logic.h"
#include "Print.h"
#include "Select.h"
#include "Search.h"

using namespace std;

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const char* monthname[]{ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	const char* weekday[]{ "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" };
	int year[CAL_ROW] = { 2023,2024,2025,2026,2027 };

	CurrentDate curdate;
	Calendar cal[CAL_ROW][CAL_COL];
	EventList list;

	char filename[MAX_PATH] = "save.bin";
	FILE* file = nullptr;
	LogicReadData(file, list, filename);

	LogicInitCal(cal, monthname, weekday, year);
	LogicInitCurrentDate(curdate, cal);

	const char* menu[]
	{
		"Запланувати подію  ",
		"Список подій       ",
		"Пошук події        ",
		"Видалити подію     ",
		"Редагувати подію   ",
		"Сортування			",
		"Вихід              "
	};

	char select = 0;

	while (true) {

		DisplayMenu(curdate, menu, MENU_ROW, select);

		ToolsHideCursor(FALSE);

		char action = _getch();
		if (action == 0 || action == 224)
			action = _getch();

		switch (action) {

		case UP:
			select = (select - 1 + MENU_ROW) % MENU_ROW;
			break;

		case DOWN:
			select = (select + 1) % MENU_ROW;
			break;

		case ENTER:
			switch (select) {

			case ADD:
				DisplayAdd(list, cal, curdate);
				break;

			case PRINT:
				DisplayPrint(list, curdate, cal);
				break;

			case SEARCH:
				DisplaySearch(list, curdate, cal);
				break;

			case REMOVE:
				DisplayRemove(list, curdate);
				break;

			case EDIT:
				DisplayEdit(list, curdate, cal);
				break;

			case SORT:
				DisplaySort(list, curdate);
				break;

			case EXIT:
				LogicSaveData(file, list, filename);
				LogicCleanMem(cal);
				LogicCleanMem(list);
				return 0;
			}
			break;

		case ESC:
			LogicSaveData(file, list, filename);
			LogicCleanMem(cal);
			LogicCleanMem(list);
			return 0;
		}
	}
}