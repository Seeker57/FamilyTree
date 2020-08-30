#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip>
#include "personException.hpp"

using namespace std;

enum Gender { MALE, FEMALE };
enum State { ALIVE, DEAD, UNKNOW };
enum Status { MARRIED, NOT_MARRIED };
enum ChoiceSetRelations { SET_MOTHER = 1, SET_FATHER, SET_PARTNER, ADD_CHILDREN };
const unsigned CURRENT_YEAR = 2020;

class Date {
    unsigned day;
    unsigned month;
    unsigned year;

    bool isTrueDate();
public:
    Date() {};
    Date(unsigned d, unsigned m, unsigned y) : day(d), month(m), year(y) {};
    friend istream& operator>>(istream& stream, Date& date);
    friend ostream& operator<<(ostream& stream, Date& date);
    bool operator==(Date& obj);
    bool operator>(Date& obj);
    bool operator<(Date& obj);
};

class PersonInformation {

protected:
    long ID;
    Gender gender;
    string firstName;
    string lastName;
    Date dBirth;
    string placeBirth;
public:
    PersonInformation() {};
    friend istream& operator>>(istream& stream, PersonInformation& person);
    friend ostream& operator<<(ostream& stream, PersonInformation& person);
};

class Person;

class FamilyRelation {

    Person* mother;
    Person* father;
    Person* partner;
    vector<Person*> childrens;
public:
    FamilyRelation() : mother(nullptr), father(nullptr), partner(nullptr) {};
    void setMother(Person* _mother) { mother = _mother; };
    void setFather(Person* _father) { father = _father; };
    void setPartner(Person* _partner) { partner = _partner;};
    void addChildren(Person* children) { childrens.push_back(children); };
    friend ostream& operator<<(ostream& stream, FamilyRelation& relation);

    friend class Person;
    friend class RelatedTree;
    friend class GrandMother;
    friend class GrandFather;
};

class Person : public PersonInformation {

    State state; 
    Status status;
    FamilyRelation relations;

    void deleteChildren(Person* parent, Person* child);
    bool checkForCorrectRelations(Person* obj, Person* subObj, short choice);
public:
    Person() : PersonInformation(), state(UNKNOW), status(NOT_MARRIED) {};
    void setRelations(Person* person);
    void setRelations(Person* person, short kindOfSet);
    void deleteRelations(Person* person);
    bool operator==(Person& obj);
    long getID() { return ID; };

    friend class TablePerson;
    friend class RelatedTree;
    friend class GrandMother;
    friend class GrandFather;
};

#endif