#include "tablePerson.hpp"
#include "relatedTree.hpp"
#include "mainMenu.hpp"

void TablePerson::addPerson() {

    Person newPerson;
    cout << "\nВведите информацию о персоне:\n";
    cin >> newPerson;

    if (isReEntryPerson(newPerson))
        throw ReEntryPerson();

    table[newPerson.getID()] = newPerson;
}

void TablePerson::addPerson(Person person) {

    if (isReEntryPerson(person))
        throw ReEntryPerson();

    table[person.getID()] = person;
}

void TablePerson::deletePerson() {

    long ID;
    cout << "\nВведите ID персоны, которую хотите удалить: ";
    cin >> ID;

    if (table.count(ID) != 0) {

        table.erase(ID);
        cout << "\nПерсона удалена!\n";
    }
    else
        throw NotExistPerson();
}

void TablePerson::changePerson() {

    long ID;
    cout << "\nВведите ID персоны, которую хотите отредактировать: ";
    cin >> ID;

    if (table.count(ID) != 0) {

        cout << "\n1) Изменить имя\n2) Изменить фамилию\n3) Изменить пол\n4) Изменить дату рождения\
                 \n5) Изменить место рождения\nВведите цифру: ";
        short choice;
        cin >> choice;
        Person* person = searchPerson(ID);

        switch (choice)
        {
        case FIRST: {
            cout << "\nВведите новое имя: ";
            cin >> person->firstName;
            break;
        }
        case SECOND: {
            cout << "\nВведите новую фамилию: ";
            cin >> person->lastName;
            break;
        }
        case THIRD: {
            if (person->gender == MALE)
                person->gender = FEMALE;
            else
                person->gender = MALE; 
            break;
        }
        case FOURTH: {
            cout << "\nВведите новую дату рождения: ";
            cin >> person->dBirth;
            break;
        }
        case FIFTH: {
            cout << "\nВведите новое место рождения: ";
            cin >> person->placeBirth;
            break;
        }
        default:
            UnexpectedEvent();
        }

        cout << "\nПерсона изменена!\n";
    }
    else
        throw NotExistPerson();

}

Person* TablePerson::searchPerson(long ID) {
    if (table.count(ID) != 0)
        return &table[ID];
    else
        return nullptr;
}

void TablePerson::searchRelatives(long personID, Creator* creator) {

    Person* person = searchPerson(personID);

    if (person != nullptr)
        creator->runFindRelative(person);
    else
        NotExistPerson(); 
}

long TablePerson::searchPersonID(long ID) {
    if (table.count(ID) != 0)
        return table[ID].getID();
    else
        return 0;
}

bool TablePerson::isReEntryPerson(Person person) {
    for (auto sPerson : table)
        if (sPerson.second == person)
            return true;
    return false;
}

void TablePerson::output() {

    cout << endl;
    for (auto person : table)
        cout << person.second << endl;
}

void TablePerson::save() {

    string fileName;
    cout << "\nВведите имя файла: ";
    cin >> fileName;

    ofstream file(fileName);
    for (auto person : table)
        file << endl << person.second;
    file.close();
}

void TablePerson::load() {

    string fileName;
    cout << "\nВведите имя файла: ";
    cin >> fileName;

    ifstream file(fileName);
    Person newPerson;
    while (!file.eof()) {
        file >> newPerson;

        if (isReEntryPerson(newPerson)) {
            throw ReEntryPerson();
        }

        table[newPerson.getID()] = newPerson;
    }
    file.close();
}

void TablePerson::outputRelations() {

    for (auto person : table) {
        cout << "Для персоны: " << person.second.getID();
        cout << person.second.relations << endl << endl;
    }
}

void TablePerson::saveRelations() {

    string fileName;
    cout << "\nВведите имя файла: ";
    cin >> fileName;

    ofstream file(fileName);
    for (auto person : table) {
        file << person.second.getID();
        file << person.second.relations << endl << endl;
    } 
    file.close();
}

void TablePerson::setRelationFromFile(ifstream& file, long setPersonID, Person* setPerson, Person* currentPerson, short choice) {

    string temp;
    file >> temp >> setPersonID;
    setPerson = searchPerson(setPersonID);
    if (setPerson != nullptr)
        currentPerson->setRelations(setPerson, choice);
}

void TablePerson::loadRelations() {

    string fileName;
    cout << "\nВведите имя файла: ";
    cin >> fileName;

    ifstream file(fileName);
    while (!file.eof()) {

        long currentPersonID, setPersonID;
        Person *currentPerson, *setPerson;
        file >> currentPersonID;
        currentPerson = searchPerson(currentPersonID);

        setRelationFromFile(file, setPersonID, setPerson, currentPerson, SET_MOTHER);
        setRelationFromFile(file, setPersonID, setPerson, currentPerson, SET_FATHER);
        setRelationFromFile(file, setPersonID, setPerson, currentPerson, SET_PARTNER);
        setRelationFromFile(file, setPersonID, setPerson, currentPerson, ADD_CHILDREN);

        char c;
        file.get(c);
        while (c != '\n') {
            setPerson = searchPerson(setPersonID);
            if (setPerson != nullptr)
                currentPerson->setRelations(setPerson, ADD_CHILDREN);
            file.get(c);
        }
    }
    file.close();
}