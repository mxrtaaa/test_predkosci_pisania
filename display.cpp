#include "header.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // do ustawiania pozycji kursora
CONSOLE_CURSOR_INFO     cursorInfo; // do pokazywania lub schowania kursora

// funkcja wy�witlaj�ca ekran ko�cowy ze statystykami gry i rekordem u�ytkownika
void endingScreen(float accuracy, int charsPerMin, int wordsCount) {
	int highscore{}; // rekord pobierany z pliku
	string highscoreName{}; // nazwa u�ytkownika, kt�ry ustanowi� rekord

	system("cls");
	showCursor(0);
	SetConsoleTextAttribute(console, 15); // bial�y tekst

	cout << " >>> Koniec gry <<<" << endl << endl;
	cout << "Poprawno��: " << setprecision(2) << accuracy << "%        " << endl << endl;
	cout << "Wpisanych s��w: " << wordsCount << endl << endl;
	cout << "Znak�w na minut�: " << charsPerMin << endl;

	// sprawdzenie i por�wnanie rekordu u�ytkownika z uzyskanym wynikiem
	fstream highscoreFile;
	highscoreFile.open("highscore.txt");
	if (highscoreFile.good()) {
		highscoreFile >> highscore;
		if (charsPerMin > highscore) {
			cout << "Brawo! Ustanowi�e� nowy rekord!" << endl;
			cout << "Tw�j poprzedni rekord: " << highscore << endl;
			highscoreFile.close();
			highscoreFile.open("highscore.txt", ios::out);
			highscoreFile << charsPerMin;
		}
		else if (charsPerMin == highscore) {
			cout << "Brawo! Wyr�wna�e� sw�j rekord";
		}
		else {
			cout << "Tw�j rekord: " << highscore << endl;
		}
	}
	highscoreFile.close();

	cout << endl << " --------------------------------------" << endl;
	cout << "| Aby wr�ci� do menu, naci�nij Escape" << endl;

	// czekanie, a� u�ytkownik wci�nie Escape
	Sleep(500);
	do {
	} while (_getch() != 27);

	PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
	showCursor(1);

	return;
}

// funkcja wy�wietlaj�ca instrukcje dla u�ytkownika
void instructions() {
	system("cls");
	cout << " >>> Instrukcja <<<" << endl << endl;
	cout << "Na ekranie zostanie wy�wietlony tekst, kt�ry nale�y przepisa�." << endl;
	cout << "Czas rozpoczyna si� automatycznie, gdy wpiszesz pierwszy znak." << endl;
	cout << "Je�li pope�nisz b��d, mo�esz go poprawi� naciskaj�c Backspace." << endl << endl;
	cout << " Aby dostosowa�:" << endl;
	cout << " > czas trwania testu" << endl;
	cout << " > typ tekstu do wpisania (czy ma zawiera� polskie znaki)" << endl;
	cout << "wejd� przez menu do panelu Ustawie�." << endl << endl;
	cout << "Po up�ywie czasu program wy�wietli statystyki, takie jak:" << endl;
	cout << " > poprawno��" << endl;
	cout << " > liczba wpisanych s��w" << endl;
	cout << " > liczba znak�w na minut�" << endl;
	cout << " > rekord u�ytkownika" << endl;
	cout << endl;
	cout << " --------------------------------------" << endl;
	cout << "| Aby wr�ci� do menu, naci�nij Escape" << endl;

	// czekanie, a� u�ytkownik wci�nie Escape
	Sleep(500);
	do {
	} while (_getch() != 27);

	PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);

	return;
}

// funkcja wy�wietlaj�ca pasek z tekstem wpisanym i do wpisania
void displayText(string& inputText, string text) {
	int position = inputText.length() - 1; // pozycja najnowszego znaku
	int i{}, j{};

	SetConsoleTextAttribute(console, 15); // bia�y tekst
	showCursor(0);

	// je�li nic nie wpisane
	if (position < 0) {
		gotoXY(0, BASE_LINE);
		cout << text.substr(0, TARGET_L);
		return;
	}

	// je�li pasek si� przesuwa
	if (position >= TARGET_POS) {
		i = position - TARGET_POS;
		j = 0;

		// wy�wietlanie i kolorowanie wpisanego tekstu
		while (i <= position) {
			if (text[i] != inputText[i])
				SetConsoleTextAttribute(console, 12); // czerwony tekst
			else
				SetConsoleTextAttribute(console, 10); //zielony tekst
			gotoXY(j, BASE_LINE);
			cout << inputText[i];
			i++;
			j++;
		}

		// wy�wietlanie jeszcze niewpisanego tekstu
		SetConsoleTextAttribute(console, 15); // bia�y tekst
		gotoXY(TARGET_POS + 1, BASE_LINE);
		cout << text.substr(position + 1, TARGET_L - TARGET_POS);
		gotoXY(TARGET_POS, BASE_LINE);
	}
	// je�li pasek si� jeszcze nie przesuwa
	else { 
		// wy�wietlanie tylko najnowszego znaku, �eby ograniczy� miganie w konsoli
		if (text[position] != inputText[position])
			SetConsoleTextAttribute(console, 12); // czerwony tekst
		else
			SetConsoleTextAttribute(console, 10); //zielony tekst
		gotoXY(position, BASE_LINE);
		cout << inputText[position];

		//wy�wietlanie jeszcze niewpisanego tekstu
		SetConsoleTextAttribute(console, 15); // bia�y tekst
		gotoXY(position + 1, BASE_LINE);
		cout << text.substr(position + 1, TARGET_L - position);
	}

	return;
}

// funcja wy�wietlaj�ca ile zosta�o czasu
void displayTime(float t, int maxTime) {
	int precision = 2;

	showCursor(0);
	SetConsoleTextAttribute(console, 15); // bia�y tekst
	gotoXY(11, 2);
	cout << fixed << setprecision(precision) << maxTime - t << "s ";

	return;
}