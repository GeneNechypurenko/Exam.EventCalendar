#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Global.h"

using namespace std;

extern HANDLE hSettings;

void ToolsHideCursor(bool hide);

void ToolsSetCoords(short x, short y);

void ToolsTextColor(int textcolor);

void ToolsPause();
