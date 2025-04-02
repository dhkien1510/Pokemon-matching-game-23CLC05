#include "graphic.h"


//read background text file to 2D array char
void getBackground(char bg[][41]) {
    ifstream fin("hiddenImage.txt");

    if (fin) {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 41; j++)
            {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        memset(bg, ' ', sizeof(char (*)[41]));
    }
}

//Draw the background in the x1 y1 position
void renderHiddenImage(char bg[][41], int x1, int y1, int theme)
{

    int highLight, word;
    checkTheme(theme, highLight, word);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 2);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            goToXY((y1 + 1)* 10 + j + 1, (x1 + 1) *4 + i + 1);
            cout << bg[x1 * 5 + i][y1 * 10 + j];
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
}

//Draw the sidebar
void renderInstruction(int theme, int score, int streak)
{
    int highLight = 0;
    int word = 7;
    if(theme == 1)
    {
        highLight = 14;
        word = 0;
    }
    if(theme == 2)
    {
        highLight = 7;
        word = 0;
    }
    for(int i = 0; i < 29; i++)
    {
        goToXY(98, i);
        cout << "|" << endl;
    }
    goToXY(100, 3);
    cout << "Score: " << setfill('0') << setw(4) << score;
    goToXY(100, 5);
    cout << "Streak: " << setfill('0') << setw(2) << streak;
    // goToXY(100, 7)
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    // cout << "High score: " << highScore;
    goToXY(100, 9);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << "INSTRUCTION";
    goToXY(100, 11);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
    cout << "ARROW KEY";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << " to move";
    goToXY(100, 13);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
    cout << "ENTER";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << " to choose";
    goToXY(100, 15);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
    cout << "H";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << " for hint";
    goToXY(100, 17);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
    cout << "ESC";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << " exit";
}

//Highlight the box if matched (or not)
void matchColorBox(int x, int y, int state, int theme)
{
    int highLight, word;
    int boxColor = 4;
    checkTheme(theme, highLight, word);
    if(state)
    {
        boxColor = 2;
    }
    for (int i = 1; i < 4; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), boxColor*16 );
        goToXY((y + 1) * 10 + 1, (x + 1) * 4 + i );
        cout << "         ";
    }
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight*16 + word);
}

//render animation and sound effect after starting the game
int startGame(int theme)
{
    //LOAD theme
    int highLight = 0;
    int word = 7;
    checkTheme(theme, highLight, word);

	int check = 1; //set frames
	int i = 0; //set time line for animation

	goToXY(47, 18);
	cout << ">";
	goToXY(73, 18);
	cout << "|";

	PlaySound(TEXT("gameStart_sound.wav"), NULL,  SND_ASYNC);
	while(true)
	{
	    if(i < 10)
        {
            if(check == 1)
            {
                deleteASCII(15, 4, highLight);
                goToXY(15, 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
                cout << R"(
                      ___           ___           ___                    ___           ___           ___
                     /\  \         /\  \         /\  \                  /\  \         /\  \         /\  \
                    /::\  \       /::\  \        \:\  \                /::\  \       /::\  \        \:\  \
                   /:/\:\  \     /:/\:\  \        \:\  \              /:/\ \  \     /:/\:\  \        \:\  \
                  /:/  \:\  \   /::\~\:\  \       /::\  \            _\:\~\ \  \   /::\~\:\  \       /::\  \
                 /:/__/_\:\__\ /:/\:\ \:\__\     /:/\:\__\          /\ \:\ \ \__\ /:/\:\ \:\__\     /:/\:\__\
                 \:\  /\ \/__/ \:\~\:\ \/__/    /:/  \/__/          \:\ \:\ \/__/ \:\~\:\ \/__/    /:/  \/__/
                  \:\ \:\__\    \:\ \:\__\     /:/  /                \:\ \:\__\    \:\ \:\__\     /:/  /
                   \:\/:/  /     \:\ \/__/     \/__/                  \:\/:/  /     \:\ \/__/     \/__/
                    \::/  /       \:\__\                               \::/  /       \:\__\
                     \/__/         \/__/                                \/__/         \/__/
                )";
                check = 0;
            }
            else
            {
                deleteASCII(40, 4, highLight);
                goToXY(15, 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
                cout << R"(
                      ___           ___                                  ___           ___
                     /\__\         /\__\                                /\__\         /\__\
                    /:/ _/_       /:/ _/_         ___                  /:/ _/_       /:/ _/_         ___
                   /:/ /\  \     /:/ /\__\       /\__\                /:/ /\  \     /:/ /\__\       /\__\
                  /:/ /::\  \   /:/ /:/ _/_     /:/  /               /:/ /::\  \   /:/ /:/ _/_     /:/  /
                 /:/__\/\:\__\ /:/_/:/ /\__\   /:/__/               /:/_/:/\:\__\ /:/_/:/ /\__\   /:/__/
                 \:\  \ /:/  / \:\/:/ /:/  /  /::\  \               \:\/:/ /:/  / \:\/:/ /:/  /  /::\  \
                  \:\  /:/  /   \::/_/:/  /  /:/\:\  \               \::/ /:/  /   \::/_/:/  /  /:/\:\  \
                   \:\/:/  /     \:\/:/  /   \/__\:\  \               \/_/:/  /     \:\/:/  /   \/__\:\  \
                    \::/  /       \::/  /         \:\__\                /:/  /       \::/  /         \:\__\
                     \/__/         \/__/           \/__/                \/__/         \/__/           \/__/
                )" << '\n';
                check = 1;
            }

        }
        else if(i >= 10 && i <= 16)
        {

            if(check == 1)
            {
                deleteASCII(40, 4, highLight);
                goToXY(40, 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 2);
                cout << R"(
                                  ___           ___           ___           ___           ___
                                 /\  \         /\  \         /\  \         /\  \         |\__\
                                /::\  \       /::\  \       /::\  \       /::\  \        |:|  |
                               /:/\:\  \     /:/\:\  \     /:/\:\  \     /:/\:\  \       |:|  |
                              /::\~\:\  \   /::\~\:\  \   /::\~\:\  \   /:/  \:\__\      |:|__|__
                             /:/\:\ \:\__\ /:/\:\ \:\__\ /:/\:\ \:\__\ /:/__/ \:|__|     /::::\__\
                             \/_|::\/:/  / \:\~\:\ \/__/ \/__\:\/:/  / \:\  \ /:/  /    /:/~~/~
                                |:|::/  /   \:\ \:\__\        \::/  /   \:\  /:/  /    /:/  /
                                |:|\/__/     \:\ \/__/        /:/  /     \:\/:/  /     \/__/
                                |:|  |        \:\__\         /:/  /       \::/__/
                                 \|__|         \/__/         \/__/         ~~

                )" << '\n';
                check = 0;
            }
            else
            {
                deleteASCII(40, 4, highLight);

                goToXY(40, 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 2);
                cout << R"(
                                  ___           ___           ___           ___
                                 /  /\         /  /\         /  /\         /  /\          __
                                /  /::\       /  /::\       /  /::\       /  /::\        |  |\
                               /  /:/\:\     /  /:/\:\     /  /:/\:\     /  /:/\:\       |  |:|
                              /  /::\ \:\   /  /::\ \:\   /  /::\ \:\   /  /:/  \:\      |  |:|
                             /__/:/\:\_\:\ /__/:/\:\ \:\ /__/:/\:\_\:\ /__/:/ \__\:|     |__|:|__
                             \__\/~|::\/:/ \  \:\ \:\_\/ \__\/  \:\/:/ \  \:\ /  /:/     /  /::::\
                                |  |:|::/   \  \:\ \:\        \__\::/   \  \:\  /:/     /  /:/~~~~
                                |  |:|\/     \  \:\_\/        /  /:/     \  \:\/:/     /__/:/
                                |__|:|~       \  \:\         /__/:/       \__\::/      \__\/
                                 \__\|         \__\/         \__\/            ~~

                    )" << '\n';
                check = 1;
            }

        }
        else
        {
            deleteASCII(60, 4, highLight);

             goToXY(60, 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
                cout << R"(
                                                      ___           ___
                                                     /\  \         /\  \
                                                    /::\  \       /::\  \
                                                   /:/\:\  \     /:/\:\  \
                                                  /:/  \:\  \   /:/  \:\  \
                                                 /:/__/_\:\__\ /:/__/ \:\__\
                                                 \:\  /\ \/__/ \:\  \ /:/  /
                                                  \:\ \:\__\    \:\  /:/  /
                                                   \:\/:/  /     \:\/:/  /
                                                    \::/  /       \::/  /
                                                     \/__/         \/__/


                    )" << '\n';

        }

        //render loadBar
		goToXY(48 + i, 18);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  word * 16 );
        cout << "     ";

		sleep_1(200);

		if(i == 20)
		{
			break;
		}
		i++;
	}
	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highLight * 16 + word);
	 PlaySound(TEXT("click_sound.wav"), NULL,  SND_ASYNC);
	system("cls");
}

//render animation after finishing the game
int gameState(int theme, int state, int score, int streak)
{
    int highLight = 0, word = 7, temp;
    checkTheme(theme, highLight, word);
    string filename1;

    if(state == 1)
    {
        filename1 = "win1.txt";
        PlaySound(TEXT("win_sound.wav"), NULL,  SND_ASYNC);
    }
    else
    {
        filename1 = "over.txt";
        PlaySound(TEXT("lost_sound.wav"), NULL,  SND_ASYNC);
    }

    int loop = 1;
    int rows = 4;
    for(int i = 0; i < 90; i+=2)
    {


        printASCII(filename1, rows, 15 + i, theme);
        sleep_1(50);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + highLight);
        for(int j = rows; j < 12; j++)
        {
            goToXY(16 + i, j);
            cout << "                                                ";
        }

        if(loop)
        {
            if(i == 89)
            {
                i = 0;
                loop = 0;
            }
        }


    }

    system("CLS");
    if(state == 1)
        printASCII(filename1, 5, 13, theme);

    else
        printASCII(filename1, 5, 6, theme);

    goToXY(48, 20);
    cout << "Score: " << score << "\t" << "Streak: " << streak;
    goToXY(48, 21);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << "press";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word + 1);
    cout << " ANY KEY ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
    cout << "to continue";

    if(temp = _getch())
    {
        system("CLS");
        PlaySound(TEXT("changeTheme_sound.wav"), NULL,  SND_ASYNC);
        return 0;
    }

}

//load the theme
int checkTheme(int theme, int &highLight, int &word)
{
    highLight = 0;
    word = 7;
    if(theme == 1)
    {
        highLight = 14;
        word = 1;
    }
    if(theme == 2)
    {
        highLight = 7;
        word = 0;
    }

}
