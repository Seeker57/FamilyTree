#include <iostream>
#include "mainMenu.hpp"

using namespace std;

int main() {

    try {

        MainMenu menu;
        menu.callMainMenu(); 
    }
    catch (PersonException exception) {
        cout << endl << exception.what() << endl;
    }

    system("pause");
    return 0;
}