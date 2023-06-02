#include "Logic.h"

void LogicSaveData(FILE* file, EventList& list, const char* filename) {

    const int monthname_size = 4;
    const int weekday_size = 3;
    const int priorstr_size = 10;
    const int eventname_size = 26;

    fopen_s(&file, filename, "wb");

    if (file == nullptr) {

        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    fwrite(&list.size, sizeof(list.size), 1, file);

    for (int i = 0; i < list.size; i++) {

        fwrite(&list.eventlist[i]->date.year, sizeof(int), 1, file);
        fwrite(&list.eventlist[i]->date.month, sizeof(int), 1, file);
        fwrite(&list.eventlist[i]->date.day, sizeof(int), 1, file);
        fwrite(list.eventlist[i]->date.monthname, sizeof(char), monthname_size, file);
        fwrite(list.eventlist[i]->date.weekday, sizeof(char), weekday_size, file);
        fwrite(&list.eventlist[i]->priority, sizeof(int), 1, file);
        fwrite(list.eventlist[i]->priorstr, sizeof(char), priorstr_size, file);
        fwrite(list.eventlist[i]->eventname, sizeof(char), eventname_size, file);
    }

    fclose(file);
}

void LogicReadData(FILE* file, EventList& list, const char* filename) {

    const int monthname_size = 4;
    const int weekday_size = 3;
    const int priorstr_size = 10;
    const int eventname_size = 26;

    fopen_s(&file, filename, "rb");

    if (file == nullptr) {

        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    fread(&list.size, sizeof(list.size), 1, file);
    list.eventlist = new Event * [list.size];

    for (int i = 0; i < list.size; i++) {

        list.eventlist[i] = new Event;
        fread(&list.eventlist[i]->date.year, sizeof(int), 1, file);
        fread(&list.eventlist[i]->date.month, sizeof(int), 1, file);
        fread(&list.eventlist[i]->date.day, sizeof(int), 1, file);
        fread(list.eventlist[i]->date.monthname, sizeof(char), monthname_size, file);
        fread(list.eventlist[i]->date.weekday, sizeof(char), weekday_size, file);
        fread(&list.eventlist[i]->priority, sizeof(int), 1, file);
        fread(list.eventlist[i]->priorstr, sizeof(char), priorstr_size, file);
        fread(list.eventlist[i]->eventname, sizeof(char), eventname_size, file);
    }

    fclose(file);
}

void LogicInitCurMonthName(CurrentDate& curdate) {

    int buffer = 4;

    if (curdate.currentdate.month == 1)
        strcpy_s(curdate.currentdate.monthname, buffer, "Jan");
    else if (curdate.currentdate.month == 2)
        strcpy_s(curdate.currentdate.monthname, buffer, "Feb");
    else  if (curdate.currentdate.month == 3)
        strcpy_s(curdate.currentdate.monthname, buffer, "Mar");
    else  if (curdate.currentdate.month == 4)
        strcpy_s(curdate.currentdate.monthname, buffer, "Apr");
    else  if (curdate.currentdate.month == 5)
        strcpy_s(curdate.currentdate.monthname, buffer, "May");
    else if (curdate.currentdate.month == 6)
        strcpy_s(curdate.currentdate.monthname, buffer, "Jun");
    else  if (curdate.currentdate.month == 7)
        strcpy_s(curdate.currentdate.monthname, buffer, "Jul");
    else if (curdate.currentdate.month == 8)
        strcpy_s(curdate.currentdate.monthname, buffer, "Aug");
    else  if (curdate.currentdate.month == 9)
        strcpy_s(curdate.currentdate.monthname, buffer, "Sep");
    else  if (curdate.currentdate.month == 10)
        strcpy_s(curdate.currentdate.monthname, buffer, "Oct");
    else if (curdate.currentdate.month == 11)
        strcpy_s(curdate.currentdate.monthname, buffer, "Nov");
    else if (curdate.currentdate.month == 12)
        strcpy_s(curdate.currentdate.monthname, buffer, "Dec");
}

void LogicInitCurWeekday(CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    int year = -1;
    int month = -1;
    int size = 0;
    int buffer = 3;

    for (int i = 0; i < CAL_ROW; i++) 
        if (cal[i][0].year == curdate.currentdate.year) {
            year = i;
            break;
        }

    for (int i = 0; i < CAL_COL; i++) 
        if (cal[year][i].month == curdate.currentdate.month) {
            month = i;
            break;
        }
   
    LogicSetSize(cal, size, year, month);

    for (int i = 0; i < size; i++)
        if (cal[year][month].day[i] == curdate.currentdate.day) {
            strcpy_s(curdate.currentdate.weekday, buffer, cal[year][month].weekday[i]);
            break;
        }
}

void LogicInitCurrentDate(CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL]) {

    time_t cdate = time(0);

    tm localeTime;
    localtime_s(&localeTime, &cdate);

    curdate.currentdate.day = localeTime.tm_mday;
    curdate.currentdate.month = localeTime.tm_mon + 1;
    curdate.currentdate.year = localeTime.tm_year + 1900;    
    LogicInitCurMonthName(curdate);
    LogicInitCurWeekday(curdate, cal);
}

void LogicInitCal(Calendar(&cal)[CAL_ROW][CAL_COL], const char* monthname[], const char* weekday[], int year[CAL_ROW]) {

    int n = 0;

    int size = 31;
    int shift = 0;

    const int buffer_mn = 4;
    const int buffer_wd = 3;

    while (n < CAL_ROW) {

        for (int i = 0; i < CAL_COL; i++) {

            cal[n][i].year = year[n];

            cal[n][i].month = i + 1;

            strcpy_s(cal[n][i].monthname, buffer_mn, monthname[i]);


            LogicSetSize(cal, size, n, i);

            cal[n][i].day = new int[size];

            for (int j = 0; j < size; j++)
                cal[n][i].day[j] = j + 1;


            LogicSetShift(cal, shift, n, i);

            LogicShiftLeft(weekday, shift);

            cal[n][i].weekday = new char[size][buffer_wd];

            for (int j = 0; j < size; j++)
                strcpy_s(cal[n][i].weekday[j], buffer_wd, weekday[j % WEEKDAY_ROW]);

            LogicShiftRight(weekday, shift);
        }
        n++;
    }
}

void LogicSetSize(Calendar(&cal)[CAL_ROW][CAL_COL], int& size, int n, int i) {

    if (strcmp(cal[n][i].monthname, "Feb") == 0 && cal[n][i].year % 4 == 0) //желательно добавить в условие (cal[n][i].year % 4 == 0 && (cal[n][i].year % 100 != 0 || cal[n][i].year % 400 == 0)) , если добавить рядки на 100 - 400 лет вперед, возникнет ошибка
        size = 29;

    else if (strcmp(cal[n][i].monthname, "Feb") == 0)
        size = 28;

    else if (strcmp(cal[n][i].monthname, "Apr") == 0 || strcmp(cal[n][i].monthname, "Jun") == 0 || strcmp(cal[n][i].monthname, "Sep") == 0 || strcmp(cal[n][i].monthname, "Nov") == 0)
        size = 30;

    else
        size = 31;
}

void LogicShiftLeft(const char* weekday[], int shift) {

    for (int i = 0; i < shift; i++) {

        const char* temp = weekday[0];

        for (int j = 0; j < WEEKDAY_ROW - 1; j++)
            weekday[j] = weekday[j + 1];

        weekday[WEEKDAY_ROW - 1] = temp;
    }
}

void LogicShiftRight(const char* weekday[], int shift) {

    for (int i = 0; i < shift; i++) {

        const char* temp = weekday[WEEKDAY_ROW - 1];

        for (int j = WEEKDAY_ROW - 1; j > 0; j--)
            weekday[j] = weekday[j - 1];

        weekday[0] = temp;
    }
}

void LogicSetShift(Calendar(&cal)[CAL_ROW][CAL_COL], int& shift, int n, int i) {

    int leap_year = (strcmp(cal[n][i].monthname, "Mar") == 0 && cal[n][i].year % 4 == 0) ? 1 : 0; //желательно добавить в условие (cal[n][i].year % 4 == 0 && (cal[n][i].year % 100 != 0 || cal[n][i].year % 400 == 0)) , если добавить рядки на 100 - 400 лет вперед, возникнет ошибка

    if (strcmp(cal[n][i].monthname, "Aug") == 0)
        shift = 1 + n + leap_year;

    else if (strcmp(cal[n][i].monthname, "Feb") == 0 || strcmp(cal[n][i].monthname, "Nov") == 0)
        shift = 2 + n + leap_year;

    else if (strcmp(cal[n][i].monthname, "Mar") == 0)
        shift = 2 + n + leap_year;

    else if (strcmp(cal[n][i].monthname, "Jun") == 0)
        shift = 3 + n + leap_year;

    else if (strcmp(cal[n][i].monthname, "Sep") == 0 || strcmp(cal[n][i].monthname, "Dec") == 0)
        shift = 4 + n + leap_year;

    //логическая ошибка в апреле 2024. календарь после марта 2024 (1 апреля 2024) проинициализирован днями недели на 1 день смещенными влево.
    else if (strcmp(cal[n][i].monthname, "Apr") == 0 || strcmp(cal[n][i].monthname, "Jul") == 0)
        shift = 5 + n + leap_year;

    else if (strcmp(cal[n][i].monthname, "Jan") == 0 || strcmp(cal[n][i].monthname, "Oct") == 0)
        shift = 6 + n + leap_year;

    else
        shift = 0 + n + leap_year;
}

void LogicCleanMem(Calendar(&cal)[CAL_ROW][CAL_COL]) {

    for (int n = 0; n < CAL_ROW; n++) {

        for (int i = 0; i < CAL_COL; i++) {

            delete[] cal[n][i].day;
            delete[] cal[n][i].weekday;
        }
    }
}
void LogicCleanMem(EventList& list) {

    for (int i = 0; i < list.size; i++)
        delete[]list.eventlist[i];
    delete[]list.eventlist;
}

void LogicInitPriorValue(Event*& event) {

    if (strcmp(event->priorstr, "високий") == 0)
        event->priority = 1;
    else if (strcmp(event->priorstr, "середній") == 0)
        event->priority = 2;
    else if (strcmp(event->priorstr, "низький") == 0)
        event->priority = 3;
}
void LogicInitPriorValue(EventList& list, int index) {

    if (strcmp(list.eventlist[index]->priorstr, "високий") == 0)
        list.eventlist[index]->priority = 1;
    else if (strcmp(list.eventlist[index]->priorstr, "середній") == 0)
        list.eventlist[index]->priority = 2;
    else if (strcmp(list.eventlist[index]->priorstr, "низький") == 0)
        list.eventlist[index]->priority = 3;
}

void LogicInitEvent(Event*& event, Calendar(&cal)[CAL_ROW][CAL_COL], const CurrentDate& curdate) {

    int year = curdate.currentdate.year;
    int month = curdate.currentdate.month;
    int day = curdate.currentdate.day;
    int empty = 0;

    LogicSetIndexes(cal, year, month, day, empty);
    DisplayStartItems(cal, year, month, day);
    SelectInputEventName(event);
    SelectYear(event, cal, year);
    SelectMonth(event, cal, year, month);
    SelectDay(event, cal, year, month, day);
    SelectPrior(event);
    LogicInitPriorValue(event);
}

void LogicAddEvent(EventList& list, Event*& event) {

    Event** temp = new Event * [list.size + 1];

    for (int i = 0; i < list.size; i++)
        temp[i] = list.eventlist[i];

    delete[]list.eventlist;
    list.eventlist = temp;

    ++list.size;
    list.eventlist[list.size - 1] = event;
}

void LogicSetIndexes(Calendar(&cal)[CAL_ROW][CAL_COL], int& year, int& month, int& weekstart, int& weekend) {

    int size = 0;

    for (int i = 0; i < CAL_ROW; i++) {
        if (cal[i][0].year == year) {
            year = i;
            break;
        }
    }

    for (int i = 0; i < CAL_COL; i++) {
        if (cal[year][i].month == month) {
            month = i;
            break;
        }
    }

    LogicSetSize(cal, size, year, month);

    for (int i = 0; i < size; i++) {
        if (cal[year][month].day[i] == weekstart) {
            weekstart = i;
            break;
        }
    }

    for (int i = weekstart; i < size; i++) {
        if (strcmp(cal[year][month].weekday[i], "Su") == 0) {
            weekend = i;
            break;
        }
    }
}

void LogicRemoveEvent(EventList& list, int index) {

    Event** temp = new Event * [list.size - 1];

    for (int i = 0; i < list.size; i++)
        if (i < index)
            temp[i] = list.eventlist[i];
        else
            temp[i] = list.eventlist[i + 1];

    delete[]list.eventlist[index];
    delete[]list.eventlist;

    list.size--;
    list.eventlist = temp;
}

void LogicEditEvent(EventList& list, const CurrentDate& curdate, Calendar(&cal)[CAL_ROW][CAL_COL], int index) {

    int year = curdate.currentdate.year;
    int month = curdate.currentdate.month;
    int day = curdate.currentdate.day;
    int empty = 0;

    LogicSetIndexes(cal, year, month, day, empty);
    DisplayStartItems(cal, year, month, day);
    SelectInputEventName(list, index);
    SelectYear(list, index, cal, year);
    SelectMonth(list, index, cal, year, month);
    SelectDay(list, index, cal, year, month, day);
    SelectPrior(list, index);
    LogicInitPriorValue(list, index);
}

void LogicSortByDate(EventList& list) { // использовал бабл сорт из-за простоты алгоритма, стоит изменить на quicksort если будет использоваться большое количество єлементов для перебора

    for (int i = 0; i < list.size - 1; i++)
        for (int j = 0; j < list.size - i - 1; j++)
            if (list.eventlist[j]->date.year > list.eventlist[j + 1]->date.year)
                swap(list.eventlist[j], list.eventlist[j + 1]);

    for (int i = 0; i < list.size - 1; i++)
        for (int j = 0; j < list.size - i - 1; j++)
            if (list.eventlist[j]->date.year == list.eventlist[j + 1]->date.year &&
                list.eventlist[j]->date.month > list.eventlist[j + 1]->date.month)
                swap(list.eventlist[j], list.eventlist[j + 1]);

    for (int i = 0; i < list.size - 1; i++)
        for (int j = 0; j < list.size - i - 1; j++)
            if (list.eventlist[j]->date.year == list.eventlist[j + 1]->date.year &&
                list.eventlist[j]->date.month == list.eventlist[j + 1]->date.month &&
                list.eventlist[j]->date.day > list.eventlist[j + 1]->date.day)
                swap(list.eventlist[j], list.eventlist[j + 1]);
}

void LogicSortByPrior(EventList& list) {

    for (int i = 0; i < list.size - 1; i++)
        for (int j = 0; j < list.size - i - 1; j++)
            if (list.eventlist[j]->priority > list.eventlist[j + 1]->priority)
                swap(list.eventlist[j], list.eventlist[j + 1]);
}