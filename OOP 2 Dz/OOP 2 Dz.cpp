// OOP 2 Dz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
const int MaxSubscribers = 50;

using namespace std;

class Person {
private:
    char* FIO;
    char* homePhone;
    char* workPhone;
    char* mobilePhone;
    char* additionalInform;

public:
    Person()    
    {
        FIO = nullptr;  
        homePhone = nullptr; 
        workPhone = nullptr;
        mobilePhone = nullptr;
        additionalInform = nullptr; 
    }
    Person(const char* _FIO, const char* _homePhone, const char* _workPhone, const char* _mobilePhone, const char* _additionalInform) {
        FIO = new char[strlen(_FIO) + 1];
        strcpy_s(FIO, strlen(_FIO) + 1, _FIO);

        homePhone = new char[strlen(_homePhone) + 1];
        strcpy_s(homePhone, strlen(_homePhone) + 1, _homePhone);

        workPhone = new char[strlen(_workPhone) + 1];
        strcpy_s(workPhone, strlen(_workPhone) + 1, _workPhone);

        mobilePhone = new char[strlen(_mobilePhone) + 1];
        strcpy_s(mobilePhone, strlen(_mobilePhone) + 1, _mobilePhone);

        additionalInform = new char[strlen(_additionalInform) + 1];
        strcpy_s(additionalInform, strlen(_additionalInform) + 1, _additionalInform);
    }
    void FioSearch()
    {
        char buff[30];  
        cout << "Введите ФИО: ";    
        cin.ignore();   
        cin.getline(buff, 30);  
        if (strcmp(FIO, buff) == 0) 
        {
            cout << "Такой абонент есть! " << endl; 
            cout << "--------------------" << endl;
            cout << "ФИО: " << FIO << endl;
            cout << "Домашний телефон: " << homePhone << endl;
            cout << "Рабочий телефон: " << workPhone << endl;
            cout << "Мобильный телефон: " << mobilePhone << endl;
            cout << "Дополнительная информация: " << additionalInform << endl;
            cout << "--------------------" << endl; 
        }
        else {
            cout << "--------------------" << endl;     
            cout << "Такого абонента нет " << endl;  
            cout << "--------------------" << endl;
        }
    } 
    void SaveToFile(FILE* saveFile) 
    {
        fprintf(saveFile, "%s %s %s %s %s\n", FIO, homePhone, workPhone, mobilePhone, additionalInform);
    }
    void Print() {
        cout << "--------------------" << endl;
        cout << "ФИО: " << FIO << endl;
        cout << "Домашний телефон: " << homePhone << endl;
        cout << "Рабочий телефон: " << workPhone << endl;
        cout << "Мобильный телефон: " << mobilePhone << endl;
        cout << "Дополнительная информация: " << additionalInform << endl;
        cout << "--------------------" << endl; 
    }   
    ~Person() {
        delete[] FIO;
        delete[] homePhone;
        delete[] workPhone;
        delete[] mobilePhone;
        delete[] additionalInform;
        cout << "Destructor\n"; 
    }
};

int main() {
    system("chcp 1251");
    system("cls");

    Person* subscribers[MaxSubscribers]; 
    int numSubscribers = 0; 

    char FIO[40];
    char homePhone[20];
    char mobilePhone[20];
    char additionalInform[20];
    char workPhone[50];
    int choise;  
    FILE* file = nullptr;
    const char* filename = "datafile.txt";  
    do {
        cout << "Выберите действие: " << endl;
        cout << "1 - Добавить нового абонента" << endl;
        cout << "2 - Искать абонента по ФИО" << endl;
        cout << "3 - Показать всех абонентов" << endl;
        cout << "4 - Удалить абонента" << endl;
        cout << "5 - Загрузить из файла" << endl;
        cout << "6 - Загрузить в файл" << endl;
        cout << "7 - Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choise;
        switch (choise) {
        case 1:
            if (numSubscribers < MaxSubscribers) {
                cout << "Введите ФИО: ";
                cin.ignore();
                cin.getline(FIO, sizeof(FIO));
                cout << "Введите домашний телефон: ";
                cin.getline(homePhone, sizeof(homePhone));
                cout << "Введите мобильный телефон: ";
                cin.getline(mobilePhone, sizeof(mobilePhone));
                cout << "Введите рабочий телефон: ";
                cin.getline(workPhone, sizeof(workPhone));
                cout << "Введите дополнительную информацию: ";
                cin.getline(additionalInform, sizeof(additionalInform));

                subscribers[numSubscribers] = new Person(FIO, homePhone, workPhone, mobilePhone, additionalInform);
                numSubscribers++;
            }
            else {
                cout << "Достигнуто максимальное количество абонентов." << endl;
            }
            break;  
        case 2:
            for (int i = 0; i < numSubscribers; i++) 
            {
                subscribers[i]->FioSearch();    
            }
            break;  
        case 3:
            for (int i = 0; i < numSubscribers; i++) 
            {
                subscribers[i]->Print(); 
            }
            break;
        case 4:
            int SubscriberDelete;
            cout << "Какого абонента удалить?(2, 3...): ";
            cin >> SubscriberDelete;
            SubscriberDelete--; 
            if (SubscriberDelete > numSubscribers || SubscriberDelete < 1)
            {
                cout << "Вы вышли из диапазона! " << "Всего " << numSubscribers << " абонентов" << endl;
            }
            else {
                delete subscribers[SubscriberDelete];   
                for (int i = SubscriberDelete; i < numSubscribers - 1; i++)
                {
                    subscribers[i] = subscribers[i + 1];
                }
                numSubscribers--;   
            }
            break;
        case 5:
            file = fopen(filename, "r");
            if (!file) {
                cout << "Ошибка открытия файла." << endl;
                break;
            }
            char fio[40];
            char homePhone[20];
            char workPhone[50];
            char mobilePhone[20];
            char additionalInform[20];

            while (fscanf(file, "%s %s %s %s %s\n", fio, homePhone, workPhone, mobilePhone, additionalInform) != EOF) {
                if (numSubscribers < MaxSubscribers) {
                    subscribers[numSubscribers] = new Person(fio, homePhone, workPhone, mobilePhone, additionalInform);
                    numSubscribers++;
                }
                else {
                    cout << "Достигнуто максимальное количество абонентов." << endl;
                    break;
                }
            }
            fclose(file);
            cout << "Данные успешно загружены из файла." << endl;
            break;
        case 6:
            FILE* saveFile = fopen(filename, "w");  
            if (!saveFile) {
                cout << "Ошибка создания файла." << endl;
                break;
            }

            for (int i = 0; i < numSubscribers; i++) {
                subscribers[i]->SaveToFile(saveFile);   
            }

            fclose(saveFile);
            cout << "Данные успешно сохранены в файл." << endl; 
            break;  
        }   
    } while (choise != 7);  

    for (int i = 0; i < numSubscribers; i++)
    {
        delete[] subscribers[i];
    }   
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
