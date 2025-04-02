#include "normalmode.h"

Tile** generateBoard(int &m, int &n)
{
    srand(time(NULL));
    m = BOARDHEIGTH;
    n = BOARDWIDTH;
    int pairs = m * n / 2;
    Tile **board = new Tile*[m];
    //Set board size m * n with empty value
    for (int i = 0; i < m; i++)
    {
        board[i] = new Tile[n];
        for (int j = 0; j < n; j++)
        {
            board[i][j].isEmpty = false;
            board[i][j].x = i;
            board[i][j].y = j;
            board[i][j].value = ' ';
        }
    }
    int idx = 0, num, place = 2, size = m * n;
    char randomChar;
    while (pairs > 0)
    {
        randomChar = (char) (rand() % 26 + 65);
        place = 2;
        //Loop 2 time to add the random character to the node
        while (place > 0)
        {
            idx = rand() % size; //random the ith position of the m * n size board
            if (board[idx / n][idx % n].value == ' ')
            {
                board[idx / n][idx % n].value = randomChar;
                place--;
            }
        }
        pairs--;
    }
    return board;
}

void renderBoard(Tile** board, int theme, char bg[][41]) {
    //draw every available node
    for (int i = 0; i < BOARDHEIGTH; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {

                board[i][j].drawBox(theme, bg);//112, 224
        }
    }
}

int checkIMatchYAxis(Tile **board, int y1, int y2, int x)
{
    int min, max;
    //Return 2 if checking the same tile ifself (for other type of checking)
    if (y1 == y2)
        return 2;
    //Get min max value for easier traversing
    if (y1 > y2)
    {
        min = y2;
        max = y1;
    }
    else
    {
        min = y1;
        max = y2;
    }
    //Check if any tile blocking the line
    for (int i = min + 1; i < max; i++)
    {
        if (!board[x][i].isEmpty)
            return 0;
    }
    //Return 1 + 1 for every non-empty tile
    return 1 + !board[x][y1].isEmpty + !board[x][y2].isEmpty;
}

int checkIMatchXAxis(Tile **board, int x1, int x2, int y)
{
    int min, max;
    //Return 2 if checking the same tile ifself (for other type of checking)
    if (x1 == x2)
        return 2;
    //Get min max value for easier traversing
    if (x1 > x2)
    {
        min = x2;
        max = x1;
    }
    else
    {
        min = x1;
        max = x2;
    }
    //Check if any tile blocking the line
    for (int i = min + 1; i < max; i++)
    {
        if (!board[i][y].isEmpty)
        {
            return 0;
        }
    }
    //Return 1 + 1 for every non-empty tile
    return 1 + !board[x1][y].isEmpty + !board[x2][y].isEmpty;
}

bool checkLMatch(Tile **board, int x1, int y1, int x2, int y2)
{
    //Return if straight line of both of the opposite tiles are not empty
    if ((!board[x1][y2].isEmpty && !board[x2][y1].isEmpty) || x1 == x2 || y1 == y2)
        return false;
    //Use I check 2 times to form the L-shape
    if (checkIMatchXAxis(board, x1, x2, y1) == 2 && checkIMatchYAxis(board, y1, y2, x2) == 2)
        return true;
    if (checkIMatchXAxis(board, x1, x2, y2) == 2 && checkIMatchYAxis(board, y1, y2, x1) == 2)
        return true;
    return false;
}

bool checkZAndUMatch(Tile **board, int m, int n, int x1, int y1, int x2, int y2)
{
    //Get min max value for easier traversing
    int minX = min(x1, x2);
    int minY = min(y1, y2);
    int maxX = max(x1, x2);
    int maxY = max(y1, y2);
    int xPos, yPos;
    //Loop for the vertical line
    for (int i = -1; i <= n; i++)
    {
        //Keep the check position in range [0, n - 1]
        yPos = clamp(0, i, n - 1);
        if (i == -1 || i == n || (checkIMatchXAxis(board, minX, maxX, yPos) == 1))
        {
            //continue checking 
            if (checkIMatchYAxis(board, minY, yPos, maxX) == 2 && checkIMatchYAxis(board, maxY, yPos, minX) == 2 && ((x1 = maxX && y1 == minY) || (x2 == maxX && y2 == minY)))
            {
                return true;
            }
            if (checkIMatchYAxis(board, minY, yPos, minX) == 2 && checkIMatchYAxis(board, maxY, yPos, maxX) == 2 && ((x1 = minX && y1 == minY) || (x2 == minX && y2 == minY)))
            {
                return true;
            }
        }
    }
    //Loop for the horizontal line + same logic
    for (int i = -1; i <= m; i++)
    {
        xPos = clamp(0, i, m - 1);
        if (i == -1 || i == m || checkIMatchYAxis(board, minY, maxY, xPos) == 1)
        {
            if (checkIMatchXAxis(board, minX, xPos, maxY) == 2 && checkIMatchXAxis(board, maxX, xPos, minY) == 2 && ((x1 == maxX && y1 == minY) || (x2 == maxX && y2 == minY)))
            {
                return true;
            }
            if (checkIMatchXAxis(board, minX, xPos, minY) == 2 && checkIMatchXAxis(board, maxX, xPos, maxY) == 2 && ((x1 == minX && y1 == minY) || (x2 == minX && y2 == minY)))
            {
                return true;
            }
        }
    }
    return false;
}

//Process the input
void getInput(Tile **board, int m, int n, int &xPos, int &yPos, int &numLocked, char c)
{
    //The changing value
    int xStep = 0, yStep = 0;
    switch (c)
    {
        case KEY_UP:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //move in circular path
            if (xPos == 0)
            {
                xStep = m - 1;
                break;
            }
            xStep--;
            break;
        case KEY_DOWN:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //move in circular path
            if (xPos == m - 1)
            {
                xStep = - m + 1;
                break;
            }
            xStep++;
            break;
        case KEY_RIGHT:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //move in circular path
            if (yPos == n - 1)
            {
                yStep = - n + 1;
                break;
            }
            yStep++;
            break;
        case KEY_LEFT:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //move in circular path
            if (yPos == 0)
            {
                yStep = n - 1;
                break;
            }
            yStep--;
            break;
        case ENTER_KEY:
            //break if tile is empty
            if (board[xPos][yPos].isEmpty)
            {
                break;
            }
            //lock if less than two is locked and the current tile is not locked in
            if (numLocked < 2 && !board[xPos][yPos].isLocked)
            {
                PlaySound(TEXT("enter_sound.wav"), NULL,  SND_ASYNC);
                board[xPos][yPos].isLocked = true;
                numLocked++;
                break;
            }
            //release the lock
            if (board[xPos][yPos].isLocked)
            {
                PlaySound(TEXT("enter_sound.wav"), NULL,  SND_ASYNC);
                board[xPos][yPos].isLocked = false;
                numLocked--;
                break;
            }
            break;
    }
    //unselect the previous tile
    board[xPos][yPos].isSelected = false;
    //calc the new pos
    xPos += xStep;
    yPos += yStep;
    //select the new pos
    board[xPos][yPos].isSelected = true;
}

bool clearChoices(Tile **board, int x1, int y1, int x2, int y2, int &numLocked, bool check)
{
    //reset the locking value
    numLocked = 0;
    //if matched, clear the boxes and other values
    if (check)
    {
        board[x1][y1].deleteBox();
        board[x2][y2].deleteBox();
    }
    //release the lock otherwise
    board[x1][y1].isLocked = false;
    board[x2][y2].isLocked = false;
    return check;
}

//Use for general checking
bool checkforMatch(Tile **board, int m, int n, int x1, int y1, int x2, int y2)
{
    if (board[x1][y1].value != board[x2][y2].value)
    {
        return false;
    }
    if ((checkIMatchXAxis(board, x1, x2, y1) == 3 && (y1 == y2)))
    {
        return true;
    }
    if(checkIMatchYAxis(board, y1, y2, x1) == 3 && (x1 == x2))
    {
        return true;
    }
    if (checkLMatch(board, x1, y1, x2, y2))
    {
        return true;
    }
    if (checkZAndUMatch(board, m, n, x1, y1, x2, y2))
    {
        return true;
    }
    return false;
}

//Process the lock and check action
bool checkMatching(Tile **board, int m, int n, int &numLocked, int theme, int &score, int &streak)
{
    //return if 2 have not been locked
    if (numLocked < 2)
        return false;
    int pos[2][2];
    int idx = 0;
    //loop through the board to store the lock position
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j].isLocked)
            {
                pos[idx][0] = i;
                pos[idx][1] = j;
                idx++;
            }
        }
    }
    int x1 = pos[0][0], y1 = pos[0][1], x2 = pos[1][0], y2 = pos[1][1];
    //if the locked position is a legal match
    if (checkforMatch(board, m, n, x1, y1, x2, y2))
    {
        //highlight green for short time
        matchColorBox(x1, y1, 1, theme);
        matchColorBox(x2, y2, 1, theme);
        //play sound
        PlaySound(TEXT("match_sound.wav"), NULL,  SND_SYNC);
        while(kbhit())
        {
            getch(); //IGNORE ALL KEYBOARD INPUT WHILE PLAYING SOUND
        }
        //calc new score
        score += 20 + streak * 5;
        streak += 1;
        //clear the lock and delete the boxes
        return clearChoices(board, x1, y1, x2, y2, numLocked, true);
    }
    //highlight red
    matchColorBox(x1, y1, 0,theme);
    matchColorBox(x2, y2, 0,theme);
    //play sound
    PlaySound(TEXT("unmatch_sound.wav"), NULL,  SND_SYNC);
    while(kbhit())
    {
        getch(); //IGNORE ALL KEYBOARD INPUT WHILE PLAYING SOUND
    }
    //calc new score
    score -= 10;
    streak = 0;
    //clear the lock
    return clearChoices(board, x1, y1, x2, y2, numLocked, false);
}

void shuffleBoard(Tile **board, int m, int n)
{
    Tile temp;
    int randNum, randX, randY, tempX, tempY;
    srand(time(0));
    //swap every position once
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            randNum = rand() % (m * n);
            randX = randNum / n;
            randY = randNum % n;
            //clear the members before swap
            board[i][j].isSelected = false;
            board[i][j].isHinted = false;
            board[randX][randY].isSelected = false;
            board[randX][randY].isHinted = false;
            //swap two tiles
            temp = board[i][j];
            board[i][j] = board[randX][randY];
            board[randX][randY] = temp;
            //swap back the box position
            tempX = board[i][j].x;
            tempY = board[i][j].y;
            board[i][j].x = board[randX][randY].x;
            board[i][j].y = board[randX][randY].y;
            board[randX][randY].x = tempX;
            board[randX][randY].y = tempY;
        }
    }
}

bool checkForAvailableMove(Tile **board, int m, int n)
{
    //Loop through every non-empty tile
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j].isEmpty)
                continue;
            //Loop through all the next non-empty tile
            for (int k = i; k < m; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    //ignore the duplicate position
                    if (k == i && l == j)
                            continue;
                    //return true if found a legal match
                    if (checkforMatch(board, m, n, i, j, k, l))
                        return true;
                }
            }
        }
    }
    return false;
}

void suggestMove(Tile **board, int m, int n)
{
    //Loop through every non-empty tile
    for (int i = 0; i < m; i++)
    {
        for (int  j = 0; j < n; j++)
        {
            if (board[i][j].isEmpty)
                continue;
            //Loop through all the next non-empty tile
            for (int k = i; k < m; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    if (k == i && l == j)
                        continue;
                    //set to be highlighted if matching case found
                    if (checkforMatch(board, m, n, i, j, k, l))
                    {
                        board[i][j].isHinted = true;
                        board[k][l].isHinted = true;
                        return;
                    }
                }
            }
        }
    }
}

void normalMode(int theme, player &p)
{
    //set score
    p.point = 0;
    p.streak = 0;
    //set size
    int width = 1, height = 1;
    Tile** board = generateBoard(height, width);
    //set the cursor at the middleboard
    int xCur = height / 2, yCur = width / 2, numLocked = 0, pairMatched = 0;
    char input;
    int firstInput = 1;
    string filename = "hiddenImage.txt";
    //ANIMATION START
    char bg[100][41];
    startGame(theme);
    //read the background
    getBackground(bg);
    //draw the board
    renderInstruction(theme, p.point, p.streak);
    renderBoard(board, theme, bg);
    //loop until end condition
    while(pairMatched < width * height / 2)
    {
        //GAMEPLAY
        //Shuffle if no legal pairs
        while (!checkForAvailableMove(board, height, width))
        {
            system("cls");
            shuffleBoard(board, height, width);
            renderBoard(board, theme, bg);
        }
        getInput(board, height, width, xCur, yCur, numLocked, input);
        //check for a matching pair and increase the pairMatched if found
        pairMatched += checkMatching(board, height, width, numLocked, theme, p.point, p.streak);
        renderInstruction(theme, p.point, p.streak);
        renderBoard(board, theme, bg);

        //CHECK FIRST INPUT
        if(!firstInput)
            input = getch();
        else
            firstInput = 0;
        // CHECK FOR HINT REQUEST
        if (input == H_KEY)
        {
            suggestMove(board, height, width);
        }
        //CHECK EXIT REQUEST
        if (input == ESC_KEY)
        {
            char choice;
            int check = 1;
            system("CLS");
            fflush(stdin);
            int word, highLight;
            checkTheme(theme, highLight, word);
            //CONFIRMATION SCREEN LOOP
            while(check)
            {
                goToXY(42, 13);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
                cout << "exit game ?(Y/N): ";
                cin >> choice;
                //exit to the main menu
                if(choice == 'Y' || choice == 'y')
                {

                    system("CLS");
                    gameState(theme, 0, p.point, p.streak);
                    return;
                }
                //continue the game
                else if(choice == 'N' || choice == 'n')
                {
                    break;
                }
                else
                {
                    system("CLS");
                    goToXY(40, 12);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
                    cout << "WRONG INPUT!" << endl;
                }
            }
            renderInstruction(theme, p.point, p.streak);
        }
    }
    //free the board memory
    deleteBoard(board, height);
    system("CLS");
    //update the leaderboard
    gameState(theme, 1, p.point, p.streak);
    system("CLS");
    return;
}

//free the board memory
void deleteBoard(Tile ** board, int height)
{
    for (int i = 0; i < height; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}