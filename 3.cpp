#include <iostream>
#include <string.h>

#define MAXLEN 80

class Book {
private:
    char* title = new char[MAXLEN];

public:
    Book() {
        std::cout << "Enter the title manually" << std::endl;
        std::cin.getline(title, MAXLEN);
    }
    Book(const char a[]) {
        strcpy_s(title, MAXLEN, a);
    }
    ~Book() {
        delete[] title;
    }
    virtual void print_book() {
        std::cout << "Title: "<< title<< std::endl;
    }

    char* get_title() {
        return title;
    }
};
class P1 : virtual public Book {
private:
    int num_pages;
public:
    P1(const char title[], int len) :Book(title) {
        num_pages = len;
    }
    ~P1() {
       
    }

    virtual void print_book() {
        std::cout << "Title: " << get_title() << " Length: " << num_pages << std::endl;
    }

    int get_pages() {
        return num_pages;
    }

};
class P2 :virtual public Book {
private: 
    char *author = new char[MAXLEN];
public:
    P2(const char title[], const char name[]) :Book(title) {
        strcpy_s(author, MAXLEN, name);
    }
    ~P2() {
        delete[] author;
    }

    virtual void print_book() {
        std::cout << "Title: " << get_title() << "Author: " << author << std::endl;
    }

    char* get_author() {
        return author;
    }
};
class P11 : public P1 {
private:
    float rating;

public:
    P11(const char title[], int len, float d) :P1(title, len) {
        rating = d;
    }
    ~P11(){
        
    }

    virtual void print_book() {
        std::cout << "Title: " << get_title() << " Length: " << get_pages() << " Rating: " << rating << std::endl;
    }
    float get_rating() {
        return rating;
    }

};
class P21 : public P2{
private:
    char *genre = new char[MAXLEN];

public:
    P21(const char title[], const char auth[], const char gen[]) :P2(title, auth) {
        strcpy_s(genre, MAXLEN,  gen);
    }

    ~P21() {
        delete[] genre;
    }

    virtual void print_book() {
         std::cout << "Title: " << get_title() << "Author: " << get_author() << " Genre: " << genre << std::endl;
    }

    char* get_genre() {
        return genre;
    }
};

class P3: public P21, public P11 {
private:
    char *description = new char[1000];
public:
    P3(const char title[], const char auth[], const char genre[], int len, float rating,const char desc[]) : P21(title, auth, genre), P11(title, len, rating) {
        strcpy_s(description, 1000,  desc);
    }
    ~P3() {
        delete[] description;
    }
    virtual void print_book() {

        std::cout << "Title: " << get_title() << " Author: " << get_author() << " Genre: " << get_genre() << " Length: " << get_pages() << " Rating: " << get_rating() << std::endl;
        std::cout << "Description:\n" << description << std::endl;
}

};


int main()
{

    P3 mybook = P3("Quatrevingt-treize", "Victor Hugo", "Historical novel", 890, 4.2, "Ninety-Three (Quatrevingt-treize)[1] is the last novel by the French writer Victor Hugo. Published in 1874, three years after the bloody upheaval of the Paris Commune that resulted out of popular reaction the failure of Napoleon III to win the Franco-Prussian War, the novel concerns the Revolt in the Vendée and Chouannerie – the counter-revolutionary revolts in 1793 during the French Revolution. It is divided into three parts, but not chronologically; each part tells a different story, offering a different view of historical general events. The action mainly takes place in Brittany and in Paris.");
    mybook.print_book();

    return 0;
}
