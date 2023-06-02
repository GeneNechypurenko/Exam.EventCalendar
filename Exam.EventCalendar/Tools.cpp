#include "Tools.h"

HANDLE hSettings = GetStdHandle(STD_OUTPUT_HANDLE);

void ToolsHideCursor(bool hide) {

    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hSettings, &structCursorInfo);
    structCursorInfo.bVisible = hide;
    SetConsoleCursorInfo(hSettings, &structCursorInfo);
}

void ToolsSetCoords(short x, short y) {

    SetConsoleCursorPosition(hSettings, { x,y });
}

void ToolsTextColor(int textcolor) {

    SetConsoleTextAttribute(hSettings, textcolor);
}

void ToolsPause() {

    const short x = 0, y = 0;
    SetConsoleCursorPosition(hSettings, { x,y });
    system("pause");
}