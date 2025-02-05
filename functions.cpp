#include "header.h"

// funkcja umo�liwiaj�ca schowanie/pokazanie kursora w konsoli
void showCursor(bool visibility) {
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = visibility;
	SetConsoleCursorInfo(console, &cursorInfo);
    return;
}

// funkcja zmieniaj�ca pozycj� kursora w konsoli
void gotoXY(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
    return;
}

// funkcja mierz�ca czas
float timer() {
	return (float)(clock() - startTime) / CLOCKS_PER_SEC;
}

// funkcja sprawdzaj�ca, czy klawisz Alt jest aktualnie wci�ni�ty
bool isAltPressed() {
    if (GetAsyncKeyState(VK_MENU) & 0x8000) 
        return 1;
    return 0;
}

// funkcja sprawdzaj�ca, kt�ry klawisz jest aktualnie wci�ni�ty
char getKey() {
    //backspace
    if (GetAsyncKeyState(8) & 0x8000)
        return (char)8;
    
    //escape
    if (GetAsyncKeyState(27) & 0x8000)
        return (char)27;

    //spacja
    if (GetAsyncKeyState(32) & 0x8000)
        return (char)32;

    // A-Z
    for (int keyCode = 65; keyCode <= 90; keyCode++)
        if (GetAsyncKeyState(keyCode) & 0x8000)
            return (char)(keyCode + 32);

	return 0;
}