#include "relatedTree.hpp"

long RelatedTree::searchAncestor(long personID, short choice) {

    Person* person = table->searchPerson(personID);
    if (person != nullptr) {

        if (choice == ON_MOTHER_SIDE)
            if (person->relations.mother != nullptr)
                return person->relations.mother->getID();
            else
                return 0;
        else if (choice == ON_FATHER_SIDE)
            if (person->relations.father != nullptr)
                return person->relations.father->getID();
            else
                return 0;
    }
    else
        throw NotExistPerson();
}

int RelatedTree::moveToCrossLine(Person* person, int bias) {

    int lengthOfName = person->firstName.length() + person->lastName.length() + 1;
    for (int i = 0; i < lengthOfName + bias; i++)
        cout << ' ';
    return lengthOfName;
}

void RelatedTree::printTreeForPerson(long personID, int bias) {

    Person* person = table->searchPerson(personID);

    if (person != nullptr) {
        cout << person->firstName << ' ' << person->lastName;

        if (person->relations.partner != nullptr) {
            cout << "___" << person->relations.partner->firstName << ' '
                << person->relations.partner->lastName << endl;
        }
        else
            cout << "___UNKNOW\n";

        if (person->relations.childrens.size() != 0) {

            int curBias;
            for (auto children : person->relations.childrens) {

                moveToCrossLine(person, bias);
                cout << " |\n";
                curBias = moveToCrossLine(person, bias);
                cout << " |_";
                
                long childrenID = children->getID();
                printTreeForPerson(childrenID, bias + curBias + 3);
            }
        }
    }
}

void RelatedTree::printTree(long personID, short choice) {

    if (choice == ON_FATHER_SIDE || choice == ON_MOTHER_SIDE) {

        long ancestorID = searchAncestor(personID, choice);

        if (ancestorID != 0) {
            cout << endl;
            printTreeForPerson(ancestorID, 0);
        }
        else
            throw NotExistPerson();
    }
    else if (choice == ON_OWN_SIDE) {

        if (table->searchPersonID(personID) != 0) {
            cout << endl;
            printTreeForPerson(personID, 0);
        }
        else
            throw NotExistPerson();
    }
}

void GrandMother::findRelative() {

    if (person->relations.mother->relations.mother != nullptr)
        table.addPerson(*person->relations.mother->relations.mother);

    if (person->relations.father->relations.mother != nullptr)
        table.addPerson(*person->relations.father->relations.mother);
}

void GrandFather::findRelative() {

    if (person->relations.mother->relations.father != nullptr)
        table.addPerson(*person->relations.mother->relations.father);

    if (person->relations.father->relations.father != nullptr)
        table.addPerson(*person->relations.father->relations.father);
}

void Creator::runFindRelative(Person* person) {

    Relative* relative = this->factoryMethod(person);
    relative->findRelative();
    relative->outputRelative();
    delete relative;
}