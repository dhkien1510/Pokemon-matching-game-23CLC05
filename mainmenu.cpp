#include "mainmenu.h"

//Process the theme color set
int changeThemeColour(int theme)
{
	int highlight = 7;
	int unHighlight = 0;
	if(theme == 2)
    {
        highlight = 0;
        unHighlight = 7;
        system("color 70");
    }
    else if(theme == 1)
    {
        highlight = 1;
        unHighlight = 14;
        system("color E0");
    }
    else
    	system("color 07");

	int choice[3] = {0,0,0};
	int curChoice = 0;
    int temp, key;
    //Theme menu loop
    while (1) {
        //draw and check for choices
        choice[curChoice] = 1;

        if (choice[0]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 14 + i);
                cout << "             ";
            }


            goToXY(81, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highlight*16 + 3);
            cout << "DARK MODE";


        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 + 7);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 14 + i);
                cout << "             ";
            }


            goToXY(81, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 +3);
            cout << "DARK MODE";

        }

        if (choice[1]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 17 + i);
                cout << "              ";
            }

            goToXY(80, 18);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 4);
            cout << "PIKACHU MODE";

        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  unHighlight*16+7);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 17 + i);
                cout << "              ";
            }


            goToXY(80, 18);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 + 4);
            cout << " PIKACHU MODE";

        }

        if (choice[2]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 20 + i);
                cout << "             ";
            }

            goToXY(81, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 2);
            cout << "LIGHT MODE";

        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 +  7);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 20 + i);
                cout << "             ";
            }


            goToXY(81, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 + 2);
            cout << "LIGHT MODE";

        }
        //get input
        if (temp = _getch()) {
            if (temp != 224 && temp)
            {

                if (temp == ENTER_KEY) {
                    PlaySound(TEXT("changeTheme_sound.wav"), NULL,  SND_ASYNC);
                    return curChoice;
                }
            }
            else {
                key = _getch();
                PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
                switch (key)
                {
                case KEY_UP:

                    choice[curChoice] = 0;
                    if (curChoice > 0) curChoice--;
                    else curChoice = 2;
                    break;
                case KEY_DOWN:

                    choice[curChoice] = 0;
                    if (curChoice < 2) curChoice++;
                    else curChoice = 0;
                default:
                    break;
                }
            }
        }
    }
}

//Load the current theme to the file
int updateTheme(int theme, int check)
{
    int oldTheme;
    ifstream ifs;
    ifs.open("backgroundTheme.txt");
    if(ifs)
        ifs >> oldTheme;
    ifs.close();
    if(check == 0)
        return oldTheme;
    else
    {
         if(theme != oldTheme)
        {
            ofstream ofs;
            ofs.open("backgroundTheme.txt");
            if(ofs)
            {
                ofs << theme;
            }
            ofs.close();
        }
        return theme;
    }
}

int mainMenu(int theme) {
    //process the theme
    int highlight = 7;
    int unHighlight = 0;
    if(theme == 2)
    {
        highlight = 0;
        unHighlight = 7;
        system("color 70");
    }
    else if(theme == 1)
    {
        highlight = 1;
        unHighlight = 14;
        system("cls");
        system("color E0");
    }
    else
    	system("color 07");
    int choice[5] = {0,0,0,0,0}, temp, key;
    int curChoice = 0;
    //load the images
    string filename = "pikachu_imj.txt";
    string background1 = "background1.txt";
    printASCII(filename, 1, 50, theme);
    printASCII(background1,0, 1, theme);
    goToXY(40,50);

    //https://learn.microsoft.com/en-us/previous-versions/dd743680(v=vs.85)
    //main menu game loop
    while (1) {
        ShowCursor(0);
        choice[curChoice] = 1;
        //highlight the button if the user select them or present them in a normal look
        if (choice[0]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 14 + i);
                cout << "             ";
            }

            goToXY(81, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 3);
            cout << "NORMAL MODE";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  unHighlight*16 );
            for (int i = 0; i < 3; i++) {
                goToXY(80, 14 + i);
                cout << "             ";
            }
            goToXY(81, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 + 3);
            cout << "NORMAL MODE";
        }
        if (choice[1]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 17 + i);
                cout << "              ";
            }
            goToXY(80, 18);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 4);
            cout << " SPECIAL MODE";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 17 + i);
                cout << "              ";
            }
            goToXY(80, 18);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 +  4);
            cout << " SPECIAL MODE";
        }

        if (choice[2]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 20 + i);
                cout << "             ";
            }
            goToXY(81, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 2);
            cout << "LEADERBOARD";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 20 + i);
                cout << "             ";
            }
            goToXY(81, 21);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 +  2);
            cout << "LEADERBOARD";
        }
        if (choice[3]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);

            for (int i = 0; i < 3; i++) {
                goToXY(80, 23 + i);
                cout << "             ";
            }
            goToXY(84, 24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 6);
            cout << "THEME";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 23 + i);
                cout << "             ";
            }
            goToXY(84, 24);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16 +  6);
            cout << "THEME";
        }
        if (choice[4]) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 26 + i);
                cout << "             ";
            }
            goToXY(84, 27);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight*16 + 4);
            cout << "EXIT";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unHighlight*16);
            for (int i = 0; i < 3; i++) {
                goToXY(80, 26 + i);
                cout << "             ";
            }
            goToXY(84, 27);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  unHighlight*16 + 4);
            cout << "EXIT";
        }
        //get the input keyboard
        if (temp = _getch()) {
            if (temp != 224 && temp)
            {
                if (temp == ENTER_KEY) {
                    system("cls");
                    PlaySound(TEXT("changeTheme_sound.wav"), NULL,  SND_ASYNC);
                    return curChoice;
                }
            }
            else {
                key = _getch();
                switch (key)
                {
                case KEY_UP:
                     PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
                    choice[curChoice] = 0;
                    if (curChoice > 0) curChoice--;
                    else curChoice = 4;
                    break;
                case KEY_DOWN:
                     PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
                    choice[curChoice] = 0;
                    if (curChoice < 4) curChoice++;
                    else curChoice = 0;
                default:
                    break;
                }
            }
        }
    }
}