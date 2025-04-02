#include <iostream>
#include <Windows.h>

#include "mainmenu.h"
#include "normalmode.h"
#include "advancedmode.h"
#include "player.h"
#include "graphic.h"

using namespace std;

// Driver Code
int main() {
    system("cls");
    //Create the data variables
    char bg[12][41];
    int status;
    int theme = 0;
    player p;
    theme = updateTheme(theme, 0);
    int input = 0;
    //User log in and register check
    inputPlayer(theme, p);
    //Loop until the user choice is "EXIT"
    while ((status = mainMenu(theme)) != 4) {
       if(status == 0) //gameplay
        {
            p.state = 0;
            normalMode(theme, p);
            checkLeaderBoard(p);
        }
        if(status == 1) // advanced mode
        {
            advancedMode(theme);
        }
        if(status == 2)//leaderBoard
        {
            readLeaderBoard(theme, p);
        }
        if(status == 3) //theme tab
        {
           theme = changeThemeColour(theme);
           updateTheme(theme, 1);
        }
    }
    return 0;
}




