//Класс «Матрица»
#include <iostream>
using namespace std;

#define LEN 3
#define STRLEN 80
class IntPair {
private:
    int res[2];
    
public:
    IntPair() {
        res[0] = 0;
        res[1] = 0;
    }
    IntPair(int t1, int t2) {
        res[0] = t1;
        res[1] = t2;
    }
    ~IntPair() {

    }
    int operator[](int index) {
        return res[index];
    }

};
class Base {
private:
    int str;
    int col;
public:
    Base() {
        str = LEN;
        col = LEN;
    }
    Base(int s, int c) {
        str = s;
        col = c;
    }
    ~Base() {

    }
    int get_strnum() {
        return str;
    }
    int get_colnum() {
        return col;
    }
};
template <typename T> class Matrix: public Base {
    private:
        T** matrix;
        T* temp;

    public:
        Matrix(): Base() {
            temp = new T;
            cout << "enter the elements" << endl;
            matrix = new T*[get_strnum()];
            for (int i = 0; i < get_strnum(); ++i)
            {
                matrix[i] = new T[get_colnum()];
                for (int j = 0; j < get_colnum(); ++j) {
                    cin >>  matrix[i][j];
                }
            }
        }
        Matrix(int s, int c) :Base(s, c) {
            temp = new T;
            cout << "enter the elements" << endl;
            matrix = new T * [get_strnum()];
            for (int i = 0; i < get_strnum(); ++i)
            {
                matrix[i] = new T[get_colnum()];
                for (int j = 0; j < get_colnum(); ++j) {
                    cin >> matrix[i][j];
                }
            }
        }
        ~Matrix() {
            for (int i = 0; i < get_strnum(); ++i)
                delete[] matrix[i];
            delete[] matrix;
        }
        void print_matrix() {
            for (int i = 0; i < get_strnum(); ++i)
            {
                for (int j = 0; j < get_colnum(); ++j) {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
    }
        void sort() {
            for (int i = 0; i < get_strnum(); i++){
                for (int j = 0; j < get_colnum() -1; j++) {
                  for (int k = j + 1 ; k < get_colnum(); k++) {
                    if (matrix[i][j] > matrix[i][k]) {
                        *temp = matrix[i][j];
                        matrix[i][j] = matrix[i][k];
                        matrix[i][k] = *temp;
                    }
                }}
            }
        }

        void clear_el(int line, int col) {
            matrix[line][col] = 0;
        }
        void edit_el(int line, int col, T val) {
            matrix[line][col] = val;
        }
        void operator+(Matrix& other){
            if (other.get_strnum() == this->get_strnum()) {
                if (other.get_colnum() == this->get_colnum()) {
                    for (int i = 0; i < get_strnum(); i++) {
                        for (int j = 0; j < get_colnum(); j++) {
                            matrix[i][j] += other.matrix[i][j];
                        }
                    }
                    
                }
            }   
        }
        bool operator>(Matrix& other) {
            if (other.get_strnum() < this->get_strnum()) {
                if (other.get_colnum() < this->get_colnum()) {
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
};


template <> class Matrix <const char*>: public Base {
private:
     char*** matrix;
     char* temp;
     const char* empty = " ";

public:
    Matrix(): Base() {
        temp = new char[STRLEN];
        cout << "enter the elements" << endl;
        matrix = new char**[get_strnum()];
        for (int i = 0; i < get_strnum(); ++i)
        {
            matrix[i] = new char*[get_colnum()];
            for (int j = 0; j < get_colnum(); ++j) {
                matrix[i][j] = new char[STRLEN];
                cin >> matrix[i][j];
            }
        }
    }
    Matrix(int s, int c) :Base(s, c) {
        temp = new char[STRLEN];
        cout << "enter the elements" << endl;
        matrix = new char** [get_strnum()];
        for (int i = 0; i < get_strnum(); ++i)
        {
            matrix[i] = new char* [get_colnum()];
            for (int j = 0; j < get_colnum(); ++j) {
                matrix[i][j] = new char[STRLEN];
                cin >> matrix[i][j];
            }
        }
    }
    ~Matrix() {
        for (int i = 0; i < get_strnum(); ++i) {
            for (int j = 0; j < get_colnum(); ++j) {
                delete[] matrix[i][j];
            }
            delete[] matrix[i];
        }       
        delete[] matrix;
        delete[] temp;
    }
    void print_matrix() {
        for (int i = 0; i < get_strnum(); ++i)
        {
            for (int j = 0; j < get_colnum(); ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    void sort() {
        
        for (int i = 0; i < get_strnum(); i++) {
            for (int j = 0; j < get_colnum() - 1; j++) {
                for (int k = j + 1; k < get_colnum(); k++) {
                    if (strcmp(matrix[i][j], matrix[i][k]) > 0) {
                        strcpy_s(temp, STRLEN, matrix[i][j]);
                        strcpy_s(matrix[i][j], STRLEN, matrix[i][k]);
                        strcpy_s(matrix[i][k], STRLEN, temp);
                    }
                }
            }
        }
    }

    void clear_el(int line, int col) {
        strcpy_s(matrix[line][col], 2," \0");
    }
    void edit_el(int line, int col, const char* val) {
        strcpy_s(matrix[line][col], STRLEN, val);
    }
    void operator+(Matrix& other) {
        if (other.get_strnum() == this->get_strnum()) {
            if (other.get_colnum() == this->get_colnum()) {
                for (int i = 0; i < get_strnum(); i++) {
                    for (int j = 0; j < get_colnum(); j++) {
                        strcat_s(matrix[i][j] , STRLEN, other.matrix[i][j]);
                    }
                }

            }
        }
    }
    bool operator>(Matrix& other) {
        if (other.get_strnum() * other.get_colnum() < this->get_strnum() * this->get_colnum()) {
            return true;
        }
        else {
            return false;
        }
    }
};




int main(){
    cout << "int 2X3 " << endl;
    Matrix<int> m1{2,3};
    m1.print_matrix();
    cout << "sort" << endl;
    m1.sort();
    m1.print_matrix();
    cout << "clear 1st element" << endl;
    m1.clear_el(0, 0);
    cout << "replace last element" << endl;
    m1.edit_el(m1.get_strnum() - 1, m1.get_colnum() - 1, 999);
    
    m1.print_matrix();
    
    Matrix<int> m1_1{ 2,3 };
    m1_1.print_matrix();
    cout << "int M1 + M1_1 =  " << endl;
    m1 + m1_1;
    m1.print_matrix();

    cout << "const char* 3X3" << endl;
    Matrix<const char*> m2;
    m2.print_matrix();
    cout << "sort" << endl;
    m2.sort();
    m2.print_matrix();
    cout << "clear 1st element" << endl;
    m2.clear_el(0, 0);
    cout << "replace last element" << endl;
    m2.edit_el(m2.get_strnum() - 1, m2.get_colnum() - 1, "Hello!");
    m2.print_matrix();

    cout << "const char* 3X3 No2" << endl;
    Matrix<const char*> m2_1{ 3,3 };
    m2_1.print_matrix();
    cout << "const char* M2 + M2_1 =  " << endl;
    m2 + m2_1;
    m2.print_matrix();
    return 0;
   
}