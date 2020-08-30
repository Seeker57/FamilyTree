#include "mainMenu.hpp"

void MainMenu::callMainMenu() {

    cleanScreen();
    cout << "\nПРОГРАММА ПОСТРОЕНИЯ ГЕНЕАЛОГИЧЕСКОГО ДЕРЕВА\n";
    cout << "______________________________________________\n";
    cout << "\n1) Создать новую таблицу персон\n2) Считать данные из файла\nВведите цифру: ";

    short choice;
    cin >> choice;

    switch (choice)
    {
    case FIRST: {
        callMenuCreateTable();
        break;
    }
    case SECOND: {
        table->load();
        callTableMenu();
        break;
    }
    default:
        throw UnexpectedEvent();
    }
}

void MainMenu::callTableMenu() {

    cleanScreen();
    cout << "\nТаблица персон:\n";
    table->output();

    cout <<"\n1) Редактировать таблицу\n2) Сохранить таблицу\n3) Редактировать родственные связи\
            \n4) Посмотреть родственные связи\n5) Вывод генеалогического дерева\n6) Выход\nВведите цифру: ";
    short choice;
    cin >> choice;

    switch (choice)
    {
    case FIRST: {
        callMenuCreateTable();
        break;
    }
    case SECOND: {
        table->save();

        cout << "\nТаблица сохранена!\n";
        cout << "\n1) Продолжить работу с таблицей\n2) Выход\nВведите цифру: ";
        cin >> choice;

        if (choice == FIRST)
            callTableMenu();
        else
            exit(0); 
        break;
    }
    case THIRD: {
        callMenuSetRelations();
        break;
    }
    case FOURTH: {
        seeRelations();
        break;
    }
    case FIFTH: {
        callRelatedTreeMenu();
        break;
    }
    case SIXTH: {
        exit(0);
    }
    default:
        throw UnexpectedEvent();
    }
}

void MainMenu::callMenuCreateTable() {

    cleanScreen();
    cout << "\nСОЗДАНИЕ ТАБЛИЦЫ ПЕРСОН\n";
    cout << "_________________________\n";

    outputTable();
    cout << endl;

    cout << "Ввод производить в следующем формате: " << endl;
    cout << "<ID>) <Имя> <Фамилия> <Пол: M или F> <Дата рождения: дд.мм.гггг> <место рождения>\n";
    
    short choice;
    do {

        try {
            cout << "\n1) Добавить персону\n2) Удалить персону\n3) Редактировать персону\n4) Законичить создание таблицы\nВведите цифру: ";
            cin >> choice;
            if (choice == FIRST)
                table->addPerson();
            else if(choice == SECOND)
                table->deletePerson();
            else if (choice == THIRD)
                table->changePerson();
        }
        catch (PersonException exception) {
            cout << endl << exception.what() << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (choice != FOURTH);

    callTableMenu();
}

void MainMenu::callMenuSetRelations() {

    cleanScreen();
    cout << "\nРЕДАКТИРОВАНИЕ РОДСТВЕННЫХ СВЯЗЕЙ\n";
    cout << "___________________________________\n";

    outputTable();
    cout << endl;

    long currentPersonID;
    cout << "Введите ID персоны для которой хотите настроить родственные отношения: ";
    cin >> currentPersonID;
    Person* currentPerson = table->searchPerson(currentPersonID);

    long setPersonID;
    cout << "Введите ID персоны, которая связана с персоной выше: ";
    cin >> setPersonID;
    Person* setPerson = table->searchPerson(setPersonID);

    cout << "\n1) Установить родственные связи\n2) Удалить родственные связи\nВведите цифру: ";
    short choice;
    cin >> choice;

    try {

        if (currentPerson == nullptr || setPerson == nullptr)
            throw NotExistPerson();

        switch (choice)
        {
        case FIRST: {
            currentPerson->setRelations(setPerson);
            break;
        } 
        case SECOND: {
            currentPerson->deleteRelations(setPerson);
            break;
        }
        default:
            throw UnexpectedEvent();
        }
    }
    catch (PersonException exception) {
        cout << endl << exception.what() << endl;
        system("pause");
    }

    callTableMenu();
}

void MainMenu::seeRelations() {

    cleanScreen();
    cout << "\nРОДСТВЕННЫЕ СВЯЗИ\n";
    cout << "___________________\n";

    outputTable();
    cout << endl;

    table->outputRelations();
    cout << "\n1) Вернуться назад\n2) Редактировать родственные связи\n3) Сохранить родственные связи в файл\
    \n4) Загрузить родственные связи из файла\n5) Найти персон по родственной связи\n6) Выход\nВведите цифру: ";
    short choice;
    cin >> choice;

    switch (choice)
    {
    case FIRST: {
        callTableMenu();
        break;
    }
    case SECOND: {
        callMenuSetRelations();
        break;
    }
    case THIRD: {
        table->saveRelations();
        cout << "\nТаблица сохранена!\n";
        callTableMenu();
        system("pause");
    }
    case FOURTH: {
        table->loadRelations();
        callTableMenu();
        break;
    }
    case FIFTH: {
        callSearchPersonMenu();
    }
    case SIXTH: {
        exit(0);
    }
    default:
        throw UnexpectedEvent();
    }
}

void MainMenu::callRelatedTreeMenu() {

    cleanScreen();
    cout << "\nМЕНЮ ВЫВОДА ГЕНЕАЛОГИЧЕСКОГО ДРЕВА\n";
    cout << "____________________________________\n";

    outputTable();
    cout << endl;

    cout << "Введите ID персоны, чье генеалогическое дерево хотите посмотреть: ";
    short personID;
    cin >> personID;

    cout << "1) По материнской линии\n2) По отцовской линии\n3) По своей линии\nВведите цирфу: ";
    short choice;
    cin >> choice;

    try {

        RelatedTree tree(table);
        tree.printTree(personID, choice);
    }
    catch (PersonException exception) {
        cout << endl << exception.what() << endl;
    }

    cout << "\n1) Вернуться назад\n2) Выход\nВведите цифру: ";
    cin >> choice;

    if (choice == FIRST)
        callTableMenu();
    else if (choice == SECOND)
        exit(0);
};

void MainMenu::callSearchPersonMenu() {

    cleanScreen();
    cout << "\nПОИСК РОДСТВЕННИКОВ\n";
    cout << "_____________________\n";

    outputTable();
    cout << endl;

    cout << "Введите ID персоны, для которой хотите найти родственников: ";
    short personID;
    cin >> personID;

    cout << "\n1) Найти бабушек\n2) Найти дедушек\nВведите цифру: ";
    short choice;
    cin >> choice;

    Creator* creator; 
    if (choice == FIRST) {

        creator = new GrandMotherCreator();
        table->searchRelatives(personID, creator);
    }
    else if (choice == SECOND) {

        creator = new GrandFatherCreator();
        table->searchRelatives(personID, creator);
    }
    delete creator;

    cout << "\n1) Вернуться назад\n2) Выход\nВведите цифру: ";
    cin >> choice;

    if (choice == FIRST)
        callTableMenu();
    else if (choice == SECOND)
        exit(0);
}