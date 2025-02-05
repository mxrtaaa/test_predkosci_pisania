#include "header.h"

clock_t startTime{}; // do odmierzania pozosta�ego czasu
const int BASE_LINE = 4; // linia, w kt�rej jest pasek z tekstem
const int TARGET_L = 40; // d�ugo�� paska z tekstem
const int TARGET_POS = TARGET_L/2-1; // pozycja, od kt�rej pasek zaczyna si� przesuwa�, a kursor stoi w miejscu

// menu wyboru
bool menu(int & maxTime, bool & polishChars) { 
	int option{}; // 0 - graj, 1 - instrukcja, 2 - ustawienia
	char character{}; // klawisz naci�ni�ty przez u�ytkownika

	showCursor(0);
	system("cls");
	cout << " >>> Test pr�dko�ci pisania <<<" << endl << endl;
	cout << "   " << "Graj" << endl;
	cout << "   " << "Instrukcja" << endl;
	cout << "   " << "Ustawienia" << endl << endl;
	cout << " --------------------------------------" << endl;
	cout << "| Do nawigacji u�ywaj strza�ek" << endl;
	cout << "| Aby zatwierdzi� opcj�, naci�nij Enter" << endl;
	cout << "| Aby zako�czy� program, naci�nij Escape" << endl;

	// obs�uga wyboru opcji przez u�ytkownika
	do {
		gotoXY(1, 2);
		cout << ' ';
		gotoXY(1, 3);
		cout << ' ';
		gotoXY(1, 4);
		cout << ' ';
		switch (option) {
		case 0:
			gotoXY(1, 2);
			break;
		case 1:
			gotoXY(1, 3);
			break;
		case 2:
			gotoXY(1, 4);
			break;
		default:
			break;
		}
		cout << '>';
		
		character = _getch();

		// zmiana opcji w zale�no�ci od wci�ni�tego klawisza
		if (character == KEY_UP && option > 0) {
			PlaySound(TEXT("next_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			option--;
		}
		else if (character == KEY_DOWN && option < 2) {
			PlaySound(TEXT("next_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			option++;
		}
		else if (character == 27) { // Escape
			PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;
		}
	} while (character != 13); // Enter
	PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);

	switch (option) {
	case 0:
		typingTest(maxTime, polishChars);
		break;
	case 1:
		instructions();
		break;
	case 2:
		settings(maxTime, polishChars);
		break;
	default:
		break;
	}

	return 1;
}

// funkcja do zmiany ustawie� gry przez u�ytkownika
void settings(int & maxTime, bool & polishChars) {
	int setting{}; // 0 - czas trwania, 1 - czy polskie znaki
	char character{}; // klawisz naci�ni�ty przez u�ytkownika

	system("cls");

	cout << " >>> Ustawienia <<<" << endl << endl;
	cout << "Wybierz czas trwania" << endl;
	cout << "   " << setw(9) << "00 sekund" << endl << endl;
	cout << "Czy tekst ma zawiera� polskie znaki" << endl;

	if (maxTime == 20) {
		gotoXY(3, 3);
		cout << '2';
	}
	else {
		gotoXY(3, 3);
		cout << '6';
	}
	if (polishChars == 0) {
		gotoXY(6, 6);
		cout << "NIE";
	}
	else {
		gotoXY(6, 6);
		cout << "TAK";
	}

	cout << endl << endl;
	cout << " --------------------------------------" << endl;
	cout << "| Do nawigacji u�ywaj strza�ek" << endl;
	cout << "| Aby wr�ci� do menu, naci�nij Escape" << endl;

	// wyb�r opcji na podstawie naci�ni�tego klawisza
	do {
		if (setting == 0) {
			gotoXY(1, 3);
			cout << '<';
			gotoXY(13, 3);
			cout << '>';
			gotoXY(1, 6);
			cout << ' ';
			gotoXY(13, 6);
			cout << ' ';
			if (maxTime == 20) {
				gotoXY(3, 3);
				cout << '2';
			} else {
				gotoXY(3, 3);
				cout << '6';
			}
		} else {
			gotoXY(1, 3);
			cout << ' ';
			gotoXY(13, 3);
			cout << ' ';
			gotoXY(1, 6);
			cout << '<';
			gotoXY(13, 6);
			cout << '>';
			if (polishChars == 0) {
				gotoXY(6, 6);
				cout << "NIE";
			}
			else {
				gotoXY(6, 6);
				cout << "TAK";
			}
		}

		character = _getch();
		if (character == KEY_UP || character == KEY_DOWN) {
			PlaySound(TEXT("next_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			setting++;
			setting %= 2;
		} else if (character == KEY_LEFT || character == KEY_RIGHT) {
			PlaySound(TEXT("next_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (setting == 0) {
				if (maxTime == 60)
					maxTime = 20;
				else
					maxTime = 60;
			}
			else {
				if (polishChars == 0)
					polishChars = 1;
				else
					polishChars = 0;
			}
		}
		else if (character == 27) { // Escape
			PlaySound(TEXT("select_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return;
		}
	} while (1);

	return;
}

// funkcja sprawdzaj�ca wpisany znak
void checkInput(char character, string& inputText, string text, bool altPressed) {
	switch (character) {
	case 0:
		return;

	case 8: // Backspace
		if (inputText.length() < 1)
			return;
		inputText.pop_back();
		break;

	case 27: // Escape
		return;

	default:
		// zamiana na polskie znaki
		if (altPressed) {
			switch (character) {
			case 'a':
				character = '�';
				break;
			case 'c':
				character = '�';
				break;
			case 'e':
				character = '�';
				break;
			case 'l':
				character = '�';
				break;
			case 'n':
				character = '�';
				break;
			case 'o':
				character = '�';
				break;
			case 's':
				character = '�';
				break;
			case 'z':
				character = '�';
				break;
			case 'x':
				character = '�';
				break;
			}
		}
		
		if (character != text[inputText.length()]) {
			PlaySound(TEXT("wrong_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
			if (character == ' ') {
				character = '_';
			}
		}
		inputText += character;

		break;
	}
	displayText(inputText, text);

	return;
}

// g���wna funkcja obs�uguj�ca test pr�dko�ci pisania - losuje tekst do przepisania, inicjuje sprawdzanie inputu, oblicza poprawno��
void typingTest(int maxTime, bool polishChars) { 
	ifstream importText;

	int nrOfLines{}; // liczba s��w w danym pliku
	string fileName;


	string text{}; // tekst do przepisania
	string inputText{}; // wpisany tekst
	int i{};
	
	float t{}, lastT{}; // do wy�wietlania czasu - czas zaokr�glony do 0.1s
	bool keyChange = 1; // czy poprzednio wci�ni�ty klawisz by� inny od obecnie wci�ni�tego
	char character{}; // wci�ni�ty klawisz
	char lastCharacter{}; // poprzedni wci�ni�ty klawisz
	bool altPressed{}; // czy Alt jest aktualnie wci�ni�ty

	int correct{}; // ile poprawnie wpisanych znak�w
	float accuracy{}; // poprawno��
	int charsPerMin{}; // ilo�� znak�w na minut�
	int wordsCount{}; // ilo�� wpisanych s��w

	showCursor(0);
	system("cls");

	SetConsoleTextAttribute(console, 15); // bia�y tekst

	gotoXY(0, 0);
	cout << "Przepisz tekst" << endl << endl;
	cout << "Pozosta�o:" << endl << endl;
	displayTime(0, maxTime);
	gotoXY(0, BASE_LINE);

	// obs�uga pliku ze s�owami do losowania w zale�no�ci od wybranej opcji polskich znak�w
	if (polishChars) {
		fileName = "slowa.txt";
		nrOfLines = 10000;
	}
	else {
		fileName = "slowa2.txt";
		nrOfLines = 5301;
	}
	importText.open(fileName);

	// tablica ze s�owami z pliku
	string* words = nullptr;
	words = new string[nrOfLines];

	// tablica z informacj�, czy dane s�owo zosta�o ju� u�yte
	bool* wordsUsed = nullptr;
	wordsUsed = new bool[nrOfLines];

	// wczytywanie s��w z pliku do tablicy dynamicznej
	while (!importText.eof()) {
		getline(importText, words[i]);
		if (importText.fail())
			break;
		i++;
	}
	importText.close();

	// uk�adanie tekstu z unikatowych s��w z pliku
	srand(time(NULL));
	while (text.length()<1000) {
		do {
			i = rand() % nrOfLines;
		} while (wordsUsed[i] == 1);
		wordsUsed[i] = 1;
		text = text + words[i] + ' ';
	}

	displayText(inputText, text);

	cout << endl << endl;
	cout << " --------------------------------------" << endl;
	cout << "| Aby wr�ci� do menu, naci�nij Escape" << endl;

	gotoXY(0, BASE_LINE);
	showCursor(1);

	// czekanie na pierwszy znak, aby rozpocz�� odliczanie czasu
	while (true) {
		character = getKey();
		if (character > 0) {
			startTime = clock();
			break;
		}
		Sleep(50);
	}
	
	do {
		// je�li Escape - wr�� do menu
		if (character == 27) {
			while (_kbhit())
				_getch();
			return;
		}

		// zaokr�glenie czasu do 1 miejsca po przecinku
		t = ((int)(timer()*10))/10.0; 

		// wy�wietlanie czasu co 0.1s
		if (lastT!=t) {
			displayTime(t, maxTime);
			if (inputText.length() > TARGET_POS)
				gotoXY(TARGET_POS+1, BASE_LINE);
			else
				gotoXY(inputText.length(), BASE_LINE);
			showCursor(1);
			lastT = t;
		}

		// sprawdzanie czy klawisz zmienia stan
		if (character > 0 && keyChange) {
			if (isAltPressed())
				altPressed = 1;
			checkInput(character, inputText, text, altPressed);
			lastCharacter = character;
			keyChange = 0;
			altPressed = 0;
		}
		// je�li �aden klawisz nie jest wci�ni�ty lub wci�ni�ty klawisz jest inny od ostatniego, umo�liw wczytanie kolejnego klawisza
		else if (character==0||lastCharacter!=character)
			keyChange = 1;
		
		//pobieranie znaku
		character = getKey();

	} while (t < maxTime);

	displayTime(maxTime, maxTime);
	displayText(inputText, text);

	// obliczanie poprawno�ci i ilo�ci s��w
	for (i = 0; i < inputText.length(); i++) {
		if (text[i] == ' ')
			wordsCount++;
		if (text[i] == inputText[i])
			correct++;
	}
	if (inputText.length() > 0) 
		accuracy = (correct * 1.0 / inputText.length()) * 100.00;
	else
		accuracy = 0;
	charsPerMin = inputText.length() * (60 / maxTime);

	endingScreen(accuracy, charsPerMin, maxTime);

	return;
}

int main() {
	bool running = 1; // czy program ma dalej dzia�a�
	int maxTime = 60; // jak d�ugo ma trwa� test (w sekundach)
	bool polishChars = 1; // czy tekst do przepisania ma zawiera� polskie znaki

	setlocale(LC_CTYPE, "Polish"); // do obs�ugi polskich znak�w

	// funkcja menu zwraca 0, kiedy naci�ni�to w niej Escape
	do {
		system("cls");
		running = menu(maxTime, polishChars);
	} while (running);

	system("cls");

	return 0;
}