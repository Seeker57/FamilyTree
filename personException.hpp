#ifndef EXCP_H
#define EXCP_H

#include <iostream>
#include <string>

using namespace std;

class PersonException : public exception {
    string mesError;

public:
    PersonException(string _mes) : mesError(_mes) {};
    ~PersonException() = default; 
    virtual const char* what() { return mesError.c_str(); };
};

class IncorrectDate : public PersonException {
public:
    IncorrectDate() : PersonException("Некорректная дата!!!") {};
};

class UnknowGender : public PersonException {
public:
    UnknowGender() : PersonException("Неизвестный пол!!! (только M или F)") {};
};

class WrongRelations : public PersonException {
public:
    WrongRelations() : PersonException("Некорректные родственные связи!!!\
    \n1. Если вы устанавливаете мать, то это обязательно должна быть женщина и её возраст должен быть больше возраста ребёнка\
    \n2. Отец обязательно мужчина и его возраст больше возраста ребёнка\
    \n3. Супруги должны быть разных полов\
    \n4. Дети должны быть младше своих родителей\
    \n5. Так же проверьте, не состоят ли выбранные персоны уже в связях, если состоят, удалите их и попробуйте заново") {};
};

class ReEntryPerson : public PersonException {
public:
    ReEntryPerson() : PersonException("Такой человек уже есть!!!") {};
};

class NoRelations : public PersonException {
public:
    NoRelations() : PersonException("Родственные отношения для данных персон не установлены!!!") {};
};

class NotExistPerson : public PersonException {
public:
    NotExistPerson() : PersonException("Такой персоны не существует!!!") {};
};

class UnexpectedEvent : public PersonException {
public:
    UnexpectedEvent() : PersonException("Непредвиденный случай!!!") {};
};

#endif