#include "player.h"

bool comparePoints(const player& p1, const player& p2) {
  return p1.point > p2.point; // Sort from highest to lowest point
}
//https://stackoverflow.com/questions/48275446/creating-a-leader-board-need-help-pairing-an-array-of-total-points-to-the-play

int createPlayerInfo(player &p, int &check)
{
    string name;
    string ignoreLine;

    //ERASE ERRORLINE
    system("cls");
    goToXY(49, 14);
    cout << "                                      ";

    //INPUT NAME
    goToXY(49, 14);
    cout << "Input new name: ";
    fflush(stdin);
    getline(cin, p.name);

    //CHECK VALID NAME
    ifstream ifs("leaderboard.txt");
    if(ifs)
    {
        while(getline(ifs, name, ','))
        {
            if(name == p.name)
            {
                goToXY(49, 10);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0 * 16+ 4);
                cout << "name is already assigned";
                sleep_1(400);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0 * 16+ 7);
                check++;
                if(check == 3) //check if the name exceed 5 times error
                {
                    char choice;
                    goToXY(49, 14);
                    cout << "It seem that name already assigned!";
                    goToXY(49, 15);
                    cout << "Do want to login? (Y/N): ";
                    cin >> choice;

                    if(choice == 'Y' || choice == 'y')
                    {
                        check = 0; //reset check to 0 and go back to main
                        system("cls");
                        return 0;
                    }
                    else
                    {
                        check = 0;

                    }
                }

                return 1;
            }
            for(int i = 0; i < 2; i++)
            {
                getline(ifs, ignoreLine, ',');
            }
            getline(ifs, ignoreLine, '\n');
        }

        //ERASE ERRORLINE
        goToXY(49, 10);
        cout << "                          ";

        //INPUT PASSWORD AND GENERATE DEFAULT STATE AND POINT
        goToXY(49, 15);
        cout << "Input password: ";
        getline(cin, p.password);
        p.point = -1;
        p.state = -1;
        p.streak = -1;
    }
    else
        cout << "cannot open file";
    ifs.close();

    //APPEND NEW PLAYER INFO TO FILE
    ofstream ofs("leaderboard.txt", ios::app);
    ofs << p.name << "," << p.password << "," << p.state << "," << p.streak << "," << p.point << "\n";
    ofs.close();
    check = 1; //FINISH

    return 0;


}

int checkOldPlayer(player &p, int &check)
{

    string password; //variable to compare with p.password
    string ignoreLine;
    string name; //variable to compare with p.name

    //INPUT NAME
    fflush(stdin);
    goToXY(49, 14);
    cout << "Input name: ";
    getline(cin, p.name);


    ifstream ifs("leaderboard.txt");
    //CHECK VALID NAME
    if(ifs)
    {
        while(getline(ifs, name, ','))
        {
            if(p.name == name)
            {
                //INPUT PASSWORD
                getline(ifs, password, ',');
                goToXY(49, 15);
                cout << "Input password: ";
                getline(cin, p.password);

                //CHECK VALID PASSWORD - FINISH
                if(p.password == password)
                {
                    check = 1;
                    return 0;
                }
                else
                {
                    goToXY(49, 10);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0 * 16+ 4);
                    cout << "wrong password";
                    sleep_1(400);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0 * 16+ 7);
                    system("cls");
                    return 1;
                }
            }
            //SKIP VARIABLES IN THE FILE
            for(int i = 0; i < 2; i++)
            {
                getline(ifs, ignoreLine, ',');
            }
            getline(ifs, ignoreLine, '\n');

        }

    }
    //IF NAME NOT FOUND
    system("cls");
    goToXY(49, 10);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0 * 16+ 4);
    cout << "name not found";
    sleep_1(1000);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0 * 16+ 7);
    ifs.close();
    check++;
    //CHECK IF NAME INPUT EXCEED 3 TIMES
    if(check == 3)
    {
        char choice;
        goToXY(49, 14);
        cout << "Name not found 5 times!";
        goToXY(49, 15);
        cout << "Do want to create a new ID? (Y/N): ";
        cin >> choice;
        if(choice == 'Y' || choice == 'y')
        {
            check = 0;
            system("cls");
            return 0;
        }
        check = 0;
        system("cls");
        return 1;

    }


    return 1;
}

void inputPlayer(int theme, player &p)
{

    char choice;
    int check = 0; //0 - if the input exceed 3 times, GO BACK TO LINE 205
                   //1 - EXIT inputPLAYER function
    fflush(stdin);

    while(true)
    {
        goToXY(50, 14);
        cout << "New player ?(Y/N): ";
        cin >> choice;
        goToXY(50, 14);
        cout << "                               ";
        if(choice == 'Y' || choice == 'y')//old user
        {
            while(createPlayerInfo(p, check));
            if(check)
                break;
            else
                continue;
        }
        else if(choice == 'N' || choice == 'n')//new user
        {
            while(checkOldPlayer(p, check));
            if(check)
                break;
            else
                continue;

        }
        else
        {
            goToXY(50, 15);
            cout << "wrong intput";
        }

    }

    system("cls");
    return;
}

void checkLeaderBoard(player newPlayer)
{
    ifstream ifs;
    ifs.open("leaderboard.txt");

    vector <player> listPlayer;
    player p;
    string name, password, state, streak, point;

    if(ifs)
    {
        while(getline(ifs, name, ','))
        {
            getline(ifs,password, ',');
            getline(ifs, state, ',');
            getline(ifs, streak, ',');
            getline(ifs, point, '\n');
            p.name = name;
            p.password = password;
            p.state = stoi(state);
            p.streak = stoi(streak);
            p.point = stoi(point);
            if(newPlayer.name == p.name)
            {

                if(newPlayer.point > p.point)
                    p.point = newPlayer.point;
            }
            p.state = newPlayer.state;
            p.streak = newPlayer.streak;
            listPlayer.push_back(p);
        }
    }
    ifs.close();

    ofstream ofs;
    ofs.open("leaderboard.txt");

    for(int i = 0; i < listPlayer.size(); i++)
    {
        ofs << listPlayer[i].name << "," << listPlayer[i].password << "," << listPlayer[i].state << "," << listPlayer[i].streak << "," << listPlayer[i].point << "\n";
    }
    ofs.close();
}


void readLeaderBoard(int theme, player user) {

    int highlight, word;
    int rank = 1;
    checkTheme(theme, highlight, word);
    int cur_highlight = highlight;
    int cur_word = word;

    goToXY(60, 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight * 16 + word + 1);
    cout << R"(
                                 _                _             _                         _
                                | | ___  __ _  __| | ___ _ __  | |__   ___   __ _ _ __ __| |
                                | |/ _ \/ _` |/ _` |/ _ \ '__| | '_ \ / _ \ / _` | '__/ _` |
                                | |  __/ (_| | (_| |  __/ |    | |_) | (_) | (_| | | | (_| |
                                |_|\___|\__,_|\__,_|\___|_|    |_.__/ \___/ \__,_|_|  \__,_|
                )" << '\n';
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight * 16+ word);
    goToXY(57, 7);
    cout << "BEST OF 8";
    goToXY(20, 8);
    cout << "No";
    goToXY(23, 8);
    cout << "NAME";
    goToXY(50, 8);
    cout << "MODE";
    goToXY(70, 8);
    cout << "STREAK";
    goToXY(93, 8);
    cout << "POINT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),highlight * 16+ word);
    goToXY(20, 9);
    for (int i = 0; i < 78; i++) {
        cout << "=";
    }
    ifstream ifs;
    ifs.open("leaderboard.txt");
    if (ifs) {
        vector <player> list_player;
        player p;
        string name;
        string password;
        string point;
        string state;
        string streak;
        while (getline(ifs, p.name, ','))
        {
            getline(ifs, password, ',');
            getline(ifs, state, ',');
            getline(ifs, streak, ',');
            getline(ifs, point, '\n');
            p.state = stoi(state);
            p.streak = stoi(streak);
            p.point = stoi(point);
            list_player.push_back(p);

        }
        ifs.close();

        sort(list_player.begin(),list_player.end(), comparePoints);
        int rows = 0;
        for(int i = 0; i < list_player.size(); i++)
        {
            if(i < 8)
            {

                switch(rank)
                {
                    case 1: word = 2; break;
                    case 2: word = 4; break;
                    case 3: word = 8; break;
                    default: word = cur_word; break;
                }
                if(user.name == list_player[i].name && list_player[i].state != -1)
                {

                    highlight = 2, word = 7;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),highlight * 16);
                    for(int i = 20; i < 94; i++)
                    {
                        goToXY(i, 10 + rows);
                        cout << " ";
                    }

                }

                if(list_player[i].state != -1)
                {
                    goToXY(20, 11 + rows);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cur_highlight * 16+ cur_word);
                    for (int j = 0; j < 78; j++) {
                        cout << "=";
                    }

                    //FIND USER
                    if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight *16 + word);
                    goToXY(20, 10 + rows);
                    cout << rank;
                    rank++;
                    goToXY(23, 10 + rows);
                    cout << list_player[i].name;
                    goToXY(50, 10 + rows);
                    if(list_player[i].state == 0)
                        cout << "Normal";
                    else
                        cout << "Advanced";
                    goToXY(70, 10 + rows);
                    cout << list_player[i].streak;
                    goToXY(93, 10 + rows);
                    cout << list_player[i].point;
                    if (rows <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), highlight* word);
                    rows += 2;
                    highlight =cur_highlight;
                    word = cur_word;

                }

            }
            else
            {

                    if(user.name == list_player[i].name && list_player[i].state != -1)
                    {
                        highlight = 2, word = 7;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),highlight * 16);
                        for(int i = 20; i < 94; i++)
                        {
                            goToXY(i, 10 + rows);
                            cout << " ";
                        }

                        goToXY(20, 10 + rows);
                        cout << rank;
                        goToXY(23, 10 + rows);
                        cout << list_player[i].name;
                        goToXY(50, 10 + rows);
                        if(list_player[i].state == 0)
                            cout << "Normal";
                        else
                            cout << "Advanced";
                        goToXY(70, 10 + rows);
                        cout << list_player[i].streak;
                        goToXY(93, 10 + rows);
                        cout << list_player[i].point;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),cur_highlight * 16 + cur_word);
                    }
                    rank++;

            }


        }

    }
    _getch();
    system("cls");
}
