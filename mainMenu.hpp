#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <limits>
#include "relatedTree.hpp"

using namespace std;

enum Actions {FIRST = 1, SECOND, THIRD, FOURTH, FIFTH, SIXTH };

class MainMenu {

    TablePerson* table;
public:
    MainMenu() { table = new TablePerson; };
    ~MainMenu() { delete table; };
    void callMainMenu();
    void callMenuCreateTable();
    void callMenuSetRelations();
    void callTableMenu();
    void callRelatedTreeMenu();
    void callSearchPersonMenu();
    void seeRelations();
    void cleanScreen() { system("cls"); };
    void outputTable() { table->output(); };
};

#endif