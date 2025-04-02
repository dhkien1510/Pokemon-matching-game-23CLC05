#include "struct.h"
#include "utility.h"

//the box structure
char box[5][12] = {
            {" --------- "},
            {"|         |"},
            {"|         |"},
            {"|         |"},
            {" --------- "}
};

// empty the value and clear the box
void Tile::deleteBox()
{
    for (int i = 0; i < 5; i++) {
        goToXY((y + 1) * 10, (x + 1) * 4 + i);
        cout << "           ";
    }
    this->isHinted = false;
    this->isEmpty = true;
    this->value = ' ';
}

//draw the box depending on the state
void Tile::drawBox(int theme, char bg[][41])
{
    //check theme
    int m = y + 1;
    int n = x + 1;
    int highLight = 0;
    int selectColor = 7;
    int lockColor = 14;
    int boxColor = 7;
    if(theme == 1)
    {
        selectColor = 11;
        lockColor = 10;
        highLight = 14;
        boxColor = 0;

    }
    else if(theme == 2)
    {
        selectColor = 0;
        lockColor = 1;
        highLight = 7;
        boxColor = 0;
    }


    //highlight the box even when it is emptied for clearer navigation
    if (isSelected && isEmpty)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectColor * 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
        return;
    }
    // draw the background if empty
    else if (isEmpty)
    {
        if(x < 4 && y < 4 )
            renderHiddenImage(bg, x, y, theme);
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
            for (int i = 1; i < 4; i++)
            {
                goToXY(m * 10 + 1, n * 4 + i);
                cout << "         ";
            }
        }

        return;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);

    for (int i = 0; i < 5; i++) {
        goToXY(m * 10, n * 4 + i);
        cout << box[i];
    }
    //Lock highlight
    if (isLocked)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), lockColor* 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }

        goToXY(m * 10 + 5, n * 4 + 2);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
    }
    //Select highlight
    else if (isSelected) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectColor * 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        goToXY(m * 10 + 5, n * 4 + 2);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highLight * 16 + boxColor);
    }
    //Hinting highlight
    else if (isHinted) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 * 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        goToXY(m * 10 + 5, n * 4 + 2);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highLight * 16 + boxColor);
    }
    //Normal state
    else {
        goToXY(m * 10 + 5, n * 4 + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),highLight * 16 +  value % 6 + 1);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
    }

}

// Clear the tile box
void NodeTile::deleteBox()
{
    for (int i = 0; i < 5; i++) {
        goToXY((y + 1) * 10, (x + 1) * 4 + i);
        cout << "           ";
    }
}

//Same box drawing logic as the array version
void NodeTile::drawBox(int theme)
{
    //check theme
    int m = y + 1;
    int n = x + 1;
    int highLight = 0;
    int selectColor = 7;
    int lockColor = 14;
    int boxColor = 7;
    if(theme == 1)
    {
        selectColor = 11;
        lockColor = 10;
        highLight = 14;
        boxColor = 0;

    }
    else if(theme == 2)
    {
        selectColor = 0;
        lockColor = 1;
        highLight = 7;
        boxColor = 0;
    }
    if (isSelected && isEmpty)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectColor * 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
        return;
    }
    else if (isEmpty)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        return;
    }
    for (int i = 0; i < 5; i++) {
        goToXY(m * 10, n * 4 + i);
        cout << box[i];
    }

    if (isLocked)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), lockColor* 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }

        goToXY(m * 10 + 5, n * 4 + 2);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
    }
    else if (isSelected) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selectColor * 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        goToXY(m * 10 + 5, n * 4 + 2);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highLight * 16 + boxColor);
    }
    else if (isHinted) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2 * 16 + (value % 6 + 1));
        for (int i = 1; i < 4; i++) {
            goToXY(m * 10 + 1, n * 4 + i);
            cout << "         ";
        }
        goToXY(m * 10 + 5, n * 4 + 2);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  highLight * 16 + boxColor);
    }
    else {
        goToXY(m * 10 + 5, n * 4 + 2);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),highLight * 16 +  value % 6 + 1);
        cout << value;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + boxColor);
    }
}