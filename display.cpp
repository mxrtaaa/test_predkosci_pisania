#include "header.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // do ustawiania pozycji kursora
CONSOLE_CURSOR_INFO     cursorInfo; // do pokazywania lub schowania kursora

// funkcja wyœwitlaj¹ca ekran koñcowy ze statystykami gry i rekordem u¿ytkownika
void endingScreen(float accuracy, int charsPerMin, int wordsCount) {
	int highscore{}; // rekord pobierany z pliku
	string highscoreName{}; // nazwa u¿ytkownika, który ustanowi³ rekord

	system("cls");
	showCursor(0);
	SetConsoleTextAttribute(console, 15); // bial³y tekst

	cout << " >>> Koniec gry <<<" << endl << endl;
	cout << "Poprawnoœæ: " << setprecision(2) << accuracy << "%        " << endl << endl;
	cout << "Wpisanych s³ów: " << wordsCount << endl << endl;
	cout << "Znaków na minutê: " << charsPerMin << endl;

	// sprawdzenie i porównanie rekordu u¿ytkownika z uzyskanym wynikiem
	fstream highscoreFile;
	highscoreFile.open("highscore.txt");
	if (highscoreFile.good()) {
		highscoreFile >> highscore;
		if (charsPerMin > highscore) {
			cout << "Brawo! Ustanowi³eœ nowy rekord!" << endl;
			cout << "Twój poprzedni rekord: " << highscore << endl;
			highscoreFile.close();
			highscoreFile.open("highscore.txt", ios::out);
			highscoreFile << charsPerMin;
		}
		else if (charsPerMin == highscore) {
			cout << "Brawo! Wyrówna³eœ swój rekord";
		}
		else {
			cout << "Twój rekord: " << highscore << endl;
		}
	}
	highscoreFile.close();

	cout << endl << " --------------------------------------" << endl;
	cout << "| Aby wróciæ do menu, naciœnij Escape" << endl;

	// czekanie, a¿ u¿ytkownik wciœnie Escape
	Sleep(500);
	do {
	} while (_getch() != 27);

	PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
	showCursor(1);

	return;
}

// funkcja wyœwietlaj¹ca instrukcje dla u¿ytkownika
void instructions() {
	system("cls");
	cout << " >>> Instrukcja <<<" << endl << endl;
	cout << "Na ekranie zostanie wyœwietlony tekst, który nale¿y przepisaæ." << endl;
	cout << "Czas rozpoczyna siê automatycznie, gdy wpiszesz pierwszy znak." << endl;
	cout << "Jeœli pope³nisz b³¹d, mo¿esz go poprawiæ naciskaj¹c Backspace." << endl << endl;
	cout << " Aby dostosowaæ:" << endl;
	cout << " > czas trwania testu" << endl;
	cout << " > typ tekstu do wpisania (czy ma zawieraæ polskie znaki)" << endl;
	cout << "wejdŸ przez menu do panelu Ustawieñ." << endl << endl;
	cout << "Po up³ywie czasu program wyœwietli statystyki, takie jak:" << endl;
	cout << " > poprawnoœæ" << endl;
	cout << " > liczba wpisanych s³ów" << endl;
	cout << " > liczba znaków na minutê" << endl;
	cout << " > rekord u¿ytkownika" << endl;
	cout << endl;
	cout << " --------------------------------------" << endl;
	cout << "| Aby wróciæ do menu, naciœnij Escape" << endl;

	// czekanie, a¿ u¿ytkownik wciœnie Escape
	Sleep(500);
	do {
	} while (_getch() != 27);

	PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);

	return;
}

// funkcja wyœwietlaj¹ca pasek z tekstem wpisanym i do wpisania
void displayText(string& inputText, string text) {
	int position = inputText.length() - 1; // pozycja najnowszego znaku
	int i{}, j{};

	SetConsoleTextAttribute(console, 15); // bia³y tekst
	showCursor(0);

	// jeœli nic nie wpisane
	if (position < 0) {
		gotoXY(0, BASE_LINE);
		cout << text.substr(0, TARGET_L);
		return;
	}

	// jeœli pasek siê przesuwa
	if (position >= TARGET_POS) {
		i = position - TARGET_POS;
		j = 0;

		// wyœwietlanie i kolorowanie wpisanego tekstu
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

		// wyœwietlanie jeszcze niewpisanego tekstu
		SetConsoleTextAttribute(console, 15); // bia³y tekst
		gotoXY(TARGET_POS + 1, BASE_LINE);
		cout << text.substr(position + 1, TARGET_L - TARGET_POS);
		gotoXY(TARGET_POS, BASE_LINE);
	}
	// jeœli pasek siê jeszcze nie przesuwa
	else { 
		// wyœwietlanie tylko najnowszego znaku, ¿eby ograniczyæ miganie w konsoli
		if (text[position] != inputText[position])
			SetConsoleTextAttribute(console, 12); // czerwony tekst
		else
			SetConsoleTextAttribute(console, 10); //zielony tekst
		gotoXY(position, BASE_LINE);
		cout << inputText[position];

		//wyœwietlanie jeszcze niewpisanego tekstu
		SetConsoleTextAttribute(console, 15); // bia³y tekst
		gotoXY(position + 1, BASE_LINE);
		cout << text.substr(position + 1, TARGET_L - position);
	}

	return;
}

// funcja wyœwietlaj¹ca ile zosta³o czasu
void displayTime(float t, int maxTime) {
	int precision = 2;

	showCursor(0);
	SetConsoleTextAttribute(console, 15); // bia³y tekst
	gotoXY(11, 2);
	cout << fixed << setprecision(precision) << maxTime - t << "s ";

	return;
}