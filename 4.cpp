
#include <iostream>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define PS_VAL 6

class P {
private:
    char title[MAXLEN];

public:
    P() {
        std::cout << "Enter the title manually" << std::endl;
        std::cin.getline(title, MAXLEN);
    }
    P(const char a[]) {
        strcpy_s(title, a);
    }
    virtual ~P() {
         delete& title;
    }
    virtual void print_book() = 0;
    virtual int calc() = 0;
 

    char* get_title() {
        return title;
    }
};
class P1 : public P {
private:
    int num_pages;
public:
    P1(const char title[], int len) :P(title) {
        num_pages = len;
    }
    ~P1() {

    }

    virtual void print_book() {
        std::cout << "Title: " << get_title() << " Length: " << num_pages << std::endl;
    }
    virtual int calc() {
        return PS_VAL  + num_pages;
    }

    int get_pages() {
        return num_pages;
    }

};

class P11 : public P1 {
private:
    float rating;

public:
    P11(const char title[], int len, float d) :P1(title, len) {
        rating = d;
    }

    ~P11() {

    }

    virtual void print_book() {
        std::cout << "Title: " << get_title() << " Length: " << get_pages() << " Rating: " << rating << std::endl;
    }
    virtual int calc() {
        return PS_VAL + (int)rating;
    }
    float get_rating() {
        return rating;
    }

};
class P2 : public P {
private:
    char genre[MAXLEN];

public:
    P2(const char title[], const char gen[]) :P(title) {
        strcpy_s(genre, gen);
    }

    ~P2() {
        delete& genre;
    }

    virtual void print_book() {
        std::cout << "Title: " << get_title() <<  " Genre: " << genre << std::endl;
    }
    virtual int calc() {
        return PS_VAL;
    }


    char* get_genre() {
        return genre;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");
    P** arr = new P*[3];
    arr[0] = new P1("Les Miserables", 150);
    arr[1] = new P11("Notre-Dame de Paris", 487, 4.5);
    arr[2] = new P2("LHomme Qui Rit", "romantic novel");
    for (int i = 0; i < 3; i++) {
        arr[i]->print_book();
        std::cout << arr[i]->calc() << std::endl; //вычисления нужны по заданию, но смысла не имеют
    }
    delete[] arr;
    return 0;
}
