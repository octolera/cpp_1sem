// cpp_lab9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cstdio>

#include "Owner.h"
#include "Editorial.h"
#include "Topic.h"
#include "Typography.h"
#include "Author.h"
#include "Newspaper.h"

using namespace std;
std::vector<printagency::Author> author_list;
std::vector<printagency::Newspaper> newspaper_list;
int main()
{ 
    printagency::Owner owner = printagency::Owner();
    printagency::Typography typography = printagency::Typography();
   // printagency::Newspaper newspaper = printagency::Newspaper();
    cout << "Typography and owner created" << endl;
    try {
        string credentials; string n; string s; int vol = 0; int circ = 0; int ch_1 = 0;
        while (1) {
            cout << "1 - change owner's credentials" << endl;
            cout << "2 - change typography data" << endl;
            cout << "3 - add author" << endl;
            cout << "4 - create newspaper" << endl;
            cout << "5 - add to newspaper" << endl << endl;
            cout << "6 - output" << endl;
            int ch;
            cin >> ch;
            if (std::cin.fail()) {
#undef max
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (ch)
            {
            case 1:
                cout << "Enter new owner's credentials" << endl;
                cin >> credentials;
                owner.set_new_credentials(credentials);
                break;
            case 2:
                try {
                    cout << "Enter new title" << endl;
                    cin >> credentials;
                    typography.new_name(credentials);
                    typography.new_owner(owner);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            case 3:
                cout << "Enter new author name" << endl;
                cin >> n;
                cout << "Enter new author surname" << endl;
                cin >> s;
                cout << "Enter new author competence" << endl;
                cin >> credentials;
                author_list.push_back(printagency::Author(n, s, credentials));
                break;
            case 4:
                cout << "Enter newspaper title" << endl;
                cin >> n;
                cout << "Enter newspaper volume" << endl;
                cin >> vol;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                cout << "Enter newspaper circulation" << endl;
                cin >> circ;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                newspaper_list.push_back(printagency::Newspaper(typography, n, vol, circ));
                break;
            case 5:
                try {
                    if (newspaper_list.size() > 0) {
                        cout << "Newspapers list:" << endl;
                        for (int i = 0; i < newspaper_list.size(); i++) {
                            cout << newspaper_list[i].get_title() << endl;
                            cout << "Printed by: " << newspaper_list[i].get_typography().get_name() << endl;
                            cout << "volume: " << newspaper_list[i].get_volume() << endl;
                            cout << "circulation: " << newspaper_list[i].get_circulation() << endl;
                            cout << "editorials: " << newspaper_list[i].get_edit_num() << endl;
                            cout << "topics: " << newspaper_list[i].get_topics_num() << endl;

                            cout << endl;
                        }
                    }
                    else { cout << "No newspapers" << endl; }
                    cout << "Enter the number:" << endl;
                    cin >> ch_1;
                    if (std::cin.fail()) {
#undef max
                        std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    if (ch_1 > newspaper_list.size() - 1) { throw exception("Out of range"); }
                    cout << "1 - add editorial(regular text)" << endl << "2 - add topic(categorised text)" << endl;
                    do {
                        cin >> ch;
                        if (std::cin.fail()) {
#undef max
                            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    } while (ch != 1 && ch != 2);
                    if (author_list.size() == 0) { throw exception("No available authors"); }

                    switch (ch) {
                    case 1:
                        newspaper_list[ch_1].add_editorial(author_list);
                        break;
                    case 2:
                        newspaper_list[ch_1].add_topic(author_list);
                        break;
                    }

                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            case 6:
                cout << "Typography" << endl;
                cout << typography.get_name() << endl;
                cout << "Owner: " << typography.get_owner().get_credentials() << endl << endl;
                if (author_list.size() > 0) {
                    cout << "Author list:" << endl;
                    printagency::Author::print_list(author_list);
                }
                else { cout << "No authors" << endl; }
                if (newspaper_list.size() > 0) {
                    cout << "Newspapers list:" << endl;
                    for (int i = 0; i < newspaper_list.size(); i++) {
                        cout << newspaper_list[i].get_title() << endl;
                        cout << "Printed by: " << newspaper_list[i].get_typography().get_name() << endl;
                        cout << "volume: " << newspaper_list[i].get_volume() << endl;
                        cout << "circulation: " << newspaper_list[i].get_circulation() << endl;
                        cout << "editorials: " << newspaper_list[i].get_edit_num() << endl;
                        cout << "topics: " << newspaper_list[i].get_topics_num() << endl;

                        cout << endl;
                    }
                }
                else { cout << "No newspapers" << endl; }
                break;
            default:
                break;
            }
        }
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
    }




    cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
