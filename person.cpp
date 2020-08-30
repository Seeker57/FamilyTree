#include "person.hpp"

bool Date::isTrueDate() {
    
    return ((day > 0 && day <= 31) && 
            (month > 0 && month <= 12) &&
            (year > 0 && year <= CURRENT_YEAR));
}

istream& operator>>(istream& stream, Date& date) {

    stream >> date.day;
    stream.ignore();
    stream >> date.month;
    stream.ignore();
    stream >> date.year;

    if (!date.isTrueDate())
        throw IncorrectDate();
    return stream;
}

ostream& operator<<(ostream& stream, Date& date) {

    stream << setw(2) << right << setfill('0') << date.day << '.' 
           << setw(2) << right << setfill('0') << date.month << '.' 
           << setw(4) << right << setfill('0') << date.year;
    return stream;
}

bool Date::operator==(Date& obj) {
    return (this->day == obj.day && this->month == obj.month && this->year == obj.year);
}

bool Date::operator>(Date& obj) {
    return (this->year > obj.year);
}

bool Date::operator<(Date& obj) {
    return (this->year < obj.year);
}

istream& operator>>(istream& stream, PersonInformation& person) {

    stream >> person.ID;
    stream.ignore();
    stream >> person.firstName >> person.lastName;
    char gender;
    string str;
    
    stream >> gender;
    if (toupper(gender) == 'M')
        person.gender = MALE;
    else if (toupper(gender) == 'F')
        person.gender = FEMALE;
    else
        throw UnknowGender();

    stream >> person.dBirth;
    stream >> person.placeBirth;
    return stream;
}

ostream& operator<<(ostream& stream, PersonInformation& person) {

    stream << person.ID << ") ";
    stream << setw(10) << left << setfill(' ') << person.firstName << ' ' 
           << setw(10) << left << setfill(' ') << person.lastName;
           
    if (person.gender == MALE)
        stream << "M ";
    else if (person.gender == FEMALE)
        stream << "F ";
    
    stream << person.dBirth << ' ';
    stream << person.placeBirth;
    return stream;
}

ostream& operator<<(ostream& stream, FamilyRelation& relations) {

    stream << "\n\tМать: ";
    if (relations.mother != nullptr)
        stream << relations.mother->getID();
    else
        stream << 0;

    stream << "\n\tОтец: ";
    if (relations.father != nullptr)
        stream << relations.father->getID();
    else
        stream << 0;
    
    stream << "\n\tСупруг(а): ";
    if (relations.partner != nullptr)
        stream << relations.partner->getID();
    else
        stream << 0;

    stream << "\n\tДети: ";
    if (relations.childrens.size() != 0) {
        for (auto children : relations.childrens)
            stream << children->getID() << ' ';
    }
    else
        stream << 0;

    return stream;
}

bool Person::operator==(Person& obj) {
    return (this->firstName == obj.firstName && this->lastName == obj.lastName &&
            this->dBirth == obj.dBirth && this->placeBirth == obj.placeBirth);
}

void Person::setRelations(Person* person) {

    cout << "\nВыберете вид связи:\n";
    cout << "\n1) Мать\n2) Отец\
             \n3) Супруг\n4) Ребёнок\
             \nВведите цифру: ";
    short kindOfSet;
    cin >> kindOfSet;

    if (checkForCorrectRelations(this, person, kindOfSet)) {

        switch (kindOfSet)
        {
        case SET_MOTHER: {
            relations.setMother(person);
            person->relations.addChildren(this);
            break;
        }
        case SET_FATHER: {
            relations.setFather(person);
            person->relations.addChildren(this);
            break;
        }
        case SET_PARTNER: {
            relations.setPartner(person);
            person->relations.setPartner(this);
            person->status = MARRIED;
            this->status = MARRIED;
            break;
        }
        case ADD_CHILDREN: {
            relations.addChildren(person);
            if (this->gender == MALE)
                person->relations.setFather(this);
            else if (this->gender == FEMALE)
                person->relations.setMother(this);
            break;
        }
        default:
            throw UnexpectedEvent();
        }
    }
    else
        throw WrongRelations();
}

void Person::setRelations(Person* person, short kindOfSet) {

    if (checkForCorrectRelations(this, person, kindOfSet)) {

        switch (kindOfSet)
        {
        case SET_MOTHER: {
            relations.setMother(person);
            person->relations.addChildren(this);
            break;
        }
        case SET_FATHER: {
            relations.setFather(person);
            person->relations.addChildren(this);
            break;
        }
        case SET_PARTNER: {
            relations.setPartner(person);
            person->relations.setPartner(this);
            person->status = MARRIED;
            this->status = MARRIED;
            break;
        }
        case ADD_CHILDREN: {
            relations.addChildren(person);
            if (this->gender == MALE)
                person->relations.setFather(this);
            else if (this->gender == FEMALE)
                person->relations.setMother(this);
            break;
        }
        default:
            throw UnexpectedEvent();
        }
    }
}

bool Person::checkForCorrectRelations(Person* obj, Person* subObj, short choice) {

    //нельзя установить родственную связь с самим собой
    if (*obj == *subObj)
        return false;

    //нельзя установить персону больше чем на одну родственную связь
    if (obj->relations.mother == subObj || obj->relations.father == subObj ||
        obj->relations.partner == subObj)
            return false;

    for (auto children : obj->relations.childrens)
        if (*children == *subObj)
            return false;

    switch (choice)
    {
    case SET_MOTHER:
        //мать обязательно - женского пола и старше сына, а ребенок не имеет матери
        return (subObj->gender == FEMALE && obj->dBirth > subObj->dBirth && 
                obj->relations.mother == nullptr);
    case SET_FATHER:
        //отец обязательно мужского пола и старше сына, а ребенок не имеет отца
        return (subObj->gender == MALE && obj->dBirth > subObj->dBirth && 
                obj->relations.father == nullptr);
    case SET_PARTNER:
        //супруги обязательно разных полов, и оба не состоят в браке
        return !(subObj->gender == obj->gender) && obj->relations.partner == nullptr &&
                subObj->relations.partner == nullptr;
    case ADD_CHILDREN:
        //сын обязательно младше родителя
        if (obj->dBirth < subObj->dBirth) {
            if (obj->gender == MALE) //и если это отец, то ребенок не имеет сына
                return (subObj->relations.father == nullptr);
            else if (obj->gender == FEMALE) //и если это мать, то ребенок не имеет матери
                return (subObj->relations.mother == nullptr);
        }
        else
            return false;
    default:
        throw UnexpectedEvent();
    }
}

void Person::deleteChildren(Person* parent, Person* child) {

    vector<Person*>::iterator children = parent->relations.childrens.begin();
    while (children != parent->relations.childrens.end()) {
        if (*children == child){
            parent->relations.childrens.erase(children);
            break;
        }
        children++;
    }
}

void Person::deleteRelations(Person* person) {

    if (this->relations.mother == person) {

        this->relations.mother = nullptr;
        deleteChildren(person, this);
    }
    else if (this->relations.father == person) {

        this->relations.father = nullptr;
        deleteChildren(person, this);    
    }
    else if (this->relations.partner == person) {

        this->relations.partner = nullptr;
        person->relations.partner = nullptr;
        person->status = NOT_MARRIED;
        this->status = NOT_MARRIED;
    }
    else if (person->relations.mother == this || person->relations.father == this) {

        deleteChildren(this, person);
        if (this->gender == MALE)
            person->relations.father = nullptr;
        else if (this->gender == FEMALE)
            person->relations.mother = nullptr;
    }
    else
        throw NoRelations();
}