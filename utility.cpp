#include "utility.h"

//set the console cursor at the x y position
void goToXY(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(console, cursorPosition);
}

//return the value in the [a, b] range
int clamp(int a, int n, int b)
{
    if (n <= a)
        return a;
    if (n < b)
        return n;
    return b;
}

//pause the program
void sleep_1(long milli)
{
    clock_t end, current = clock();
    for( end = current + milli; current < end; current = clock() );
}

//clear the text
void deleteASCII(int cols, int rows, int highLight)
{
	for(int i = rows; i <= rows + 12; i++)
	{
		goToXY(cols, i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highLight * 16 + highLight);
		cout << "                                                                                                                                   ";
	}
}

//print the image in the text file
void printASCII(string filename, int rows, int cols, int theme)
{
    int highlight = 0;
    int word = 6;
    if(theme == 2)
    {
        highlight = 7;
        word = 0;
    }
     if(theme == 1)
    {
        highlight = 14;
        word = 1;
    }
    string line = "";
    ifstream ifs;
    ifs.open(filename.c_str());
    if(!ifs.is_open())
        cout << "ifs cannot open";
    else
    {
        int temp_rows = rows;

        while(getline(ifs, line))
        {
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight * 16 + word);
             goToXY(cols, rows);
             cout << line << endl;\
             rows++;
        }

    }
    ifs.close();
}