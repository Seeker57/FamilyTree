#ifndef TABLE_H
#define TABLE_H 1

#include <iostream>
#include <map>
#include <fstream>
#include "person.hpp"

using namespace std;

class Creator;

class TablePerson {

    map<long, Person> table;

    void setRelationFromFile(ifstream& file, long setPersonID, Person* setPerson, Person* currentPerson, short choice);
public:
    TablePerson() {};
    void addPerson();
    void addPerson(Person person);
    void deletePerson();
    void changePerson();
    Person* searchPerson(long ID);
    void searchRelatives(long personID, Creator* creator);
    long searchPersonID(long ID);
    bool isReEntryPerson(Person person);

    void output();
    void outputRelations();
    void save();
    void saveRelations();
    void load();
    void loadRelations();
};

#endif