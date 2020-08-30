#ifndef RTREE_H
#define RTREE_H 1

#include <iostream>
#include "tablePerson.hpp"

using namespace std;

enum sideOfTree { ON_MOTHER_SIDE = 1, ON_FATHER_SIDE, ON_OWN_SIDE };

class RelatedTree {

    TablePerson* table;

    int moveToCrossLine(Person* person, int bias);
public:
    RelatedTree(TablePerson* _table) : table(_table) {};
    long searchAncestor(long personID, short choice);
    void printTree(long personID, short choice);
    void printTreeForPerson(long personID, int bias);
};

class Relative {

protected:
    TablePerson table;
    Person* person;
public:
    Relative(Person* _person) : person(_person) {};
    virtual void findRelative() = 0;
    void outputRelative() { table.output(); };
};

class GrandMother : public Relative {
public:
    GrandMother(Person* _person) : Relative(_person) {};
    void findRelative();
};

class GrandFather : public Relative {
public:
    GrandFather(Person* _person) : Relative(_person) {};
    void findRelative();
};

class Creator {
public:
    Creator() {};
    virtual Relative* factoryMethod(Person* person) = 0;
    void runFindRelative(Person* person);
};

class GrandMotherCreator : public Creator {
public:
    Relative* factoryMethod(Person* person) { return new GrandMother(person); };
};

class GrandFatherCreator : public Creator {
public:
    Relative* factoryMethod(Person* person) { return new GrandFather(person); };
};
#endif