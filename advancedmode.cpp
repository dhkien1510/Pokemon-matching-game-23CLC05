#include "advancedmode.h"

NodeTile *createNodeTile(int x, int y, char value)
{
    //create a node with given value and position
    NodeTile *res = new NodeTile;
    res->next = NULL;
    res->value = value;
    res->x = x;
    res->y = y;
    return res;
}

void addTail(NodeTile *&head, int x, int y, char value)
{
    if (head == NULL)
    {
        head = createNodeTile(x, y, value);
        return;
    }
    NodeTile *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = createNodeTile(x, y, value);
}

NodeTile *goToNode(NodeTile **board, int x, int y)
{
    //return the node at x, y
    NodeTile *temp = board[x];
    while (temp != NULL && temp->y != y)
    {
        temp = temp->next;
    }
    return temp;
}

void deleteNode(NodeTile **board, int x, int y)
{
    //Set temp pointer
    NodeTile *temp = board[x];
    if (temp == NULL)
    {
        return;
    }
    //Delete first node
    if (y == 0)
    {
        board[x] = temp->next;
        delete temp;
        NodeTile *temp2 = board[x];
        while (temp2->next != NULL)
        {
        //Shift the image position
        temp2->y -= 1;
        temp2 = temp2->next;
        }
        temp2->deleteBox();
        temp2->y -= 1;
        return;
    }
    while (temp->next != NULL && temp->next->y != y)
    {
        temp = temp->next;
    }
    if (temp->next == NULL)
    {
        return;
    }
    NodeTile *temp2 = temp->next->next;
    temp->next->deleteBox();
    delete temp->next;
    temp->next = temp2;
    if (temp2 == NULL)
    {
        return;
    }
    while (temp2->next != NULL)
    {
        //Shift the image position
        temp2->y -= 1;
        temp2 = temp2->next;
    }
    //Delete the last node image and shift it to the left
    temp2->deleteBox();
    temp2->y -= 1;
}

void renderBoard(NodeTile** board, int theme)
{
    NodeTile *temp;
    //draw every available node
    for (int i = 0; i < BOARDHEIGTH; i++) 
    {
        temp = board[i];
        while (temp != NULL)
        {
            temp->drawBox(theme);
            temp = temp->next;
        }
    }
}

NodeTile **generateAdvancedBoard(int &m, int &n)
{
    m = BOARDHEIGTH;
    n = BOARDWIDTH;
    NodeTile **board = new NodeTile*[m];
    srand(time(NULL));
    int pairs = m * n / 2;
    //Set board size m * n with empty value
    for (int i = 0; i < m; i++)
    {
        board[i] = NULL;
        for (int j = 0; j < n; j++)
        {
           addTail(board[i], i, j, ' ');
        }
    }
    int idx = 0, num, place = 2, size = m * n;
    char randomChar;
    NodeTile *temp;
    while (pairs > 0)
    {
        randomChar = (char) (rand() % 26 + 65);
        place = 2;
        //Loop 2 time to add the random character to the node
        while (place > 0)
        {
            idx = rand() % size; //random the ith position of the m * n size board
            temp = goToNode(board, idx / n, idx % n);
            if (temp->value == ' ')
            {
                temp->value = randomChar;
                place--;
            }
        }
        pairs--;
    }
    return board;
}

int checkIMatchYAxis(NodeTile **board, int y1, int y2, int x)
{
    int min, max;
    //Get the pointers to the node at the input position
    NodeTile *temp;
    NodeTile *node1 = goToNode(board, x, y1);
    NodeTile *node2 = goToNode(board, x, y2);
    //Return 2 if checking the same node ifself (for other type of checking)
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
    //Check if any node blocking the line
    for (int i = min + 1; i < max; i++)
    {
        temp = goToNode(board, x, i);
        if (temp)
            return 0;
    }
    //Return 1 + 1 for every non-empty node
    return 1 + (node1 != NULL) + (node2 != NULL);
}

int checkIMatchXAxis(NodeTile **board, int x1, int x2, int y)
{
    int min, max;
    //Get the pointers to the node at the input position
    NodeTile *temp;
    NodeTile *node1 = goToNode(board, x1, y);
    NodeTile *node2 = goToNode(board, x2, y);
    //Return 2 if checking the same node ifself (for other type of checking)
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
    //Check if any node blocking the line
    for (int i = min + 1; i < max; i++)
    {
        temp = goToNode(board, i, y);
        if (temp)
        {
            return 0;
        }
    }
    //Return 1 + 1 for every non-empty node
    return 1 + (node1 != NULL) + (node2 != NULL);
}

bool checkLMatch(NodeTile **board, int x1, int y1, int x2, int y2)
{
    //Get the pointers to the node at the input position
    NodeTile *node1 = goToNode(board, x1, y1);
    NodeTile *node2 = goToNode(board, x2, y2);
    //Get the pointers to the node at the opposite position of the rectangle
    NodeTile *node3 = goToNode(board, x1, y2);
    NodeTile *node4 = goToNode(board, x2, y1);
    //Return if straight line of both of the opposite nodes are not empty
    if ((node3 && node4) || x1 == x2 || y1 == y2)
        return false;
    //Use I check 2 times to form the L-shape
    if (checkIMatchXAxis(board, x1, x2, y1) == 2 && checkIMatchYAxis(board, y1, y2, x2) == 2)
        return true;
    if (checkIMatchXAxis(board, x1, x2, y2) == 2 && checkIMatchYAxis(board, y1, y2, x1) == 2)
        return true;
    return false;
}

int checkZAndUMatch(NodeTile **board, int m, int n, int x1, int y1, int x2, int y2)
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
        //if the line is clear
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

//Use for general checking
bool checkforMatch(NodeTile **board, int m, int n, int x1, int y1, int x2, int y2)
{
    NodeTile *node1 = goToNode(board, x1, y1);
    NodeTile *node2 = goToNode(board, x2, y2);
    if (node1->value != node2->value)
    {
        return false;
    }
    if ((checkIMatchXAxis(board, x1, x2, y1) == 3 && (y1 == y2)) || (checkIMatchYAxis(board, y1, y2, x1) == 3 && (x1 == x2)))
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

//Process the input
void getInput(NodeTile **board, int m, int n, int &xPos, int &yPos, int &numLocked, char c)
{
    //The changing value
    int xStep = 0, yStep = 0;
    //Get the pointer to the node at the previous loop call
    NodeTile *node1 = goToNode(board, xPos, yPos);
    switch (c)
    {
        case KEY_UP:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //break if cannot reach
            if (xPos == 0 || !goToNode(board, xPos - 1, yPos))
            {
                break;
            }
            xStep--;
            break;
        case KEY_DOWN:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //break if cannot reach
            if (xPos == m - 1 || !goToNode(board, xPos + 1, yPos))
                break;
            xStep++;
            break;
        case KEY_RIGHT:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //break if cannot reach
            if (!goToNode(board, xPos, yPos + 1))
                break;
            yStep++;
            break;
        case KEY_LEFT:
            PlaySound(TEXT("move_sound.wav"), NULL,  SND_ASYNC);
            //break if cannot reach
            if (yPos == 0)
                break;
            yStep--;
            break;
        case ENTER_KEY:
            PlaySound(TEXT("enter_sound.wav"), NULL,  SND_ASYNC);
            //break if not exist
            if (!node1)
                break;
            //lock if less than two is locked and the current node is not locked in
            if (numLocked < 2 && !node1->isLocked)
            {
                node1->isLocked = true;
                numLocked++;
                break;
            }
            //release the lock
            if (node1->isLocked)
            {
                node1->isLocked = false;
                numLocked--;
                break;
            }
            break;
    }
    //unselect the previous node
    if (node1)
        node1->isSelected = false;
    //calc the new pos
    xPos += xStep;
    yPos += yStep;
    //select the new pos
    NodeTile *node2 = goToNode(board, xPos, yPos);
    if (node2)
        node2->isSelected = true;
}

bool clearChoices(NodeTile **board, int x1, int y1, int x2, int y2, int &numLocked, bool check)
{
    //reset the locking value
    numLocked = 0;
    //Get the pointers to the node at the input position
    NodeTile *node1 = goToNode(board, x1, y1);
    NodeTile *node2 = goToNode(board, x2, y2);
    //if matched
    if (check)
    {
        //delete from right to left to avoid shifting the next node to be deleted
        if (y1 > y2)
        {
            deleteNode(board, x1, y1);
            deleteNode(board, x2, y2);
        }
        else
        {
            deleteNode(board, x2, y2);
            deleteNode(board, x1, y1);
        }
    }
    //release the lock otherwise
    else
    {
        node1->isLocked = false;
        node2->isLocked = false;
    }
    return check;
}

//Process the lock and check action
bool checkMatching(NodeTile **board, int m, int n, int &numLocked, int theme, int &score, int &streak)
{
    //return if 2 have not been locked
    if (numLocked < 2)
        return false;
    NodeTile *temp;
    int pos[2][2];
    int idx = 0;
    //loop through the board to store the lock position
    for (int i = 0; i < m; i++)
    {
        int yPos = 0;
        temp = board[i];
        while (temp != NULL)
        {
            if (temp->isLocked)
            {
            pos[idx][0] = i;
            pos[idx][1] = yPos;
            idx++;
            }
            yPos++;
            temp = temp->next;
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
        //clear the lock and delete the node
        return clearChoices(board, x1, y1, x2, y2, numLocked, true);
    }
    //highlight red
    matchColorBox(x1, y1, 0, theme);
    matchColorBox(x2, y2, 0, theme);
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

void suggestMove(NodeTile **board, int m, int n)
{
    NodeTile *temp = NULL;
    NodeTile *temp2 = NULL;
    //Loop through every non-empty node
    for (int i = 0; i < m; i++)
    {
        for (int  j = 0; j < n; j++)
        {
            temp = goToNode(board, i, j);
            if (!temp)
                continue;
            //Loop through all the next non-empty node
            for (int k = i; k < m; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    temp2 = goToNode(board, k, l);
                    //ignore the duplicate position and the empty node
                    if ((k == i && l == j) || !temp2)
                        continue;
                    //set to be highlighted if matching case found
                    if (checkforMatch(board, m, n, i, j, k, l))
                    {
                        temp->isHinted = true;
                        temp2->isHinted = true;
                        return;
                    }
                }
            }
        }
    }
}

bool checkForAvailableMove(NodeTile **board, int m, int n)
{
    //same logic as move suggestion
    NodeTile *temp = NULL;
    NodeTile *temp2 = NULL;
    for (int i = 0; i < m; i++)
    {
        for (int  j = 0; j < n; j++)
        {
            temp = goToNode(board, i, j);
            if (!temp)
                continue;
            for (int k = i; k < m; k++)
            {
                for (int l = 0; l < n; l++)
                {
                    temp2 = goToNode(board, k, l);
                    if ((k == i && l == j) || !temp2)
                        continue;
                    // only return true instead
                    if (checkforMatch(board, m, n, i, j, k, l))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void advancedMode(int theme)
{
    //set size
    int width = 1, height = 1;
    //set score
    int score = 0, streak = 0;
    //generate board
    NodeTile** board = generateAdvancedBoard(height, width);
    //set the cursor at the middleboard
    int xCur = height / 2, yCur = width / 2, numLocked = 0, pairMatched = 0;
    char input;
    int firstInput = 1;
    //draw the board
    renderBoard(board, theme);
    //loop until end condition
    while(pairMatched < width * height / 2 && checkForAvailableMove(board, height, width))
    {
        //GAMEPLAY
        getInput(board, height, width, xCur, yCur, numLocked, input);
        pairMatched += checkMatching(board, height, width, numLocked, theme, score, streak);
        renderInstruction(theme, score, streak);
        renderBoard(board, theme);

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
        // CHECK FOR EXIT REQUEST
        if (input == ESC_KEY )
        {
            char choice;
            int check = 1;
            system("CLS");
            fflush(stdin);
            int word = 7, highLight = 0;
            if(theme == 1)
            {
                    word = 0;
                    highLight = 14;
            }
            else if(theme == 2)
            {
                word = 0;
                highLight = 7;
            }
            //CONFIRMATION SCREEN LOOP
            while(check)
            {
                goToXY(40, 13);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
                cout << "exit game ?(Y/N): ";
                cin >> choice;
                //exit to the main menu
                if(choice == 'Y' || choice == 'y')
                {
                    system("CLS");
                    gameState(theme, 0, score, streak);
                    return;
                }
                //continue the game
                else if(choice == 'N' || choice == 'n')
                {
                    break;
                }
                //Blocking invalid input
                else
                {
                    system("CLS");
                    goToXY(40, 12);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highLight * 16 + word);
                    cout << "WRONG INPUT!" << endl;
                }
            }
        }
    }
    system("CLS");
    gameState(theme, 1, score, streak);
    deleteBoard(board, height);
    return;
}
//remove every element of a linked list
void removeList(NodeTile *&pHead)
{
    if(!pHead)
        return;
    NodeTile* pCur = pHead;
    while(pCur)
    {
        NodeTile* pTemp = pCur;
        pCur = pCur->next;
        delete pTemp;
    }
    pHead = NULL;
}

//free the board memory
void deleteBoard(NodeTile **board, int height)
{
    for (int i = 0; i < height; i++)
    {
        removeList(board[i]);
    }
    delete[] board;
}