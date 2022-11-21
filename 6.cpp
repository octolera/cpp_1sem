//Класс «Матрица»
#include <iostream>
#include <exception>
using namespace std;
#define LEN 3
#define STRLEN 256

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

void new_unexpected() {
    cout << "new_unexpected called" << endl;
    void new_terminate(); 
}
void new_terminate() {
    cout << "new_reminate called" << endl;
    abort();

}
class ProcessUnexpected {
    public:
        char desc[80];
        ProcessUnexpected() { *desc = 0; }
        ProcessUnexpected(const char* s) { strcpy_s(desc,256, s); }  

        void what_happened() {
            cout << desc << endl;
        }
};

class IndexError : public IntPair {
public:
    int str;
    int col;
    char desc[80];
    IndexError() {str = 0; col = 0; *desc = 0; }
    IndexError(int l, int c, const char* s) { str = l; col = c; strcpy_s(desc, 256, s); }
    int get_line() {
        return str;
    }
    int get_col() {
        return col;
    }
    void what_happened() {
        cout << desc << endl;
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
        if (s < 1|| c < 1 ){
            throw IndexError(s, c, "Cant create matrix with length below 1\n");
        }
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
template <typename T> class Matrix : public Base {
private:
    T** matrix;
    T* temp;

public:
    Matrix() : Base() {
        temp = new T;
        cout << "enter the elements" << endl;
        matrix = new T * [get_strnum()];
        if (!matrix) {
            throw  ProcessUnexpected("Failed to create matrix\n");
        }
        for (int i = 0; i < get_strnum(); ++i)
        {
            matrix[i] = new T[get_colnum()];
            if (!matrix[i]) {
                throw  ProcessUnexpected("Failed to create line\n");
            }
            for (int j = 0; j < get_colnum(); ++j) {
                cin >> matrix[i][j];
            }
        }
    }
    Matrix(int s, int c) :Base(s, c) {
        temp = new T;
        cout << "enter the elements" << endl;
        matrix = new T * [get_strnum()];
        if (!matrix) {
            throw  ProcessUnexpected("Failed to create matrix\n");
        }
        for (int i = 0; i < get_strnum(); ++i)
        {
            matrix[i] = new T[get_colnum()];
            if (!matrix[i]) {
                throw  ProcessUnexpected("Failed to create line\n");
            }
            for (int j = 0; j < get_colnum(); ++j) {
                cin >> matrix[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < get_strnum(); ++i)
            delete[] matrix[i];
        delete[] matrix;
        delete temp;

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
        if (get_colnum() < 2) {
            throw  ProcessUnexpected("Lines too short to sort\n");
        }
        for (int i = 0; i < get_strnum(); i++) {
            for (int j = 0; j < get_colnum() - 1; j++) {
                for (int k = j + 1; k < get_colnum(); k++) {
                    if (matrix[i][j] > matrix[i][k]) {
                        *temp = matrix[i][j];
                        matrix[i][j] = matrix[i][k];
                        matrix[i][k] = *temp;
                    }
                }
            }
        }
    }
    IntPair find(T& val) {
        for (int i = 0; i < get_strnum(); i++) {
            for (int j = 0; j < get_colnum(); j++) {
                if (val == matrix[i][j]) {
                    return IntPair{ i, j };
                }
            }
        }
        throw  ProcessUnexpected("No matches found");
    };

    void clear_el(int line, int col) {
        if (line < 0 || col < 0 || line > get_strnum() - 1 || col > get_colnum() - 1) {
            throw IndexError(line, col, "Invalid index\n");
        }
        matrix[line][col] = 0;
    }
    void edit_el(int line, int col, T val) {
        if (line < 0 || col < 0 || line > get_strnum() - 1 || col > get_colnum() - 1) {
            throw IndexError(line, col, "Invalid index\n");
        }
        if (!val) {
            throw ProcessUnexpected("No value given\n");
        }
        matrix[line][col] = val;
    }
    void operator + (Matrix& other) {
        if (other.get_strnum() == this->get_strnum()) {
            if (other.get_colnum() == this->get_colnum()) {
                for (int i = 0; i < get_strnum(); i++) {
                    for (int j = 0; j < get_colnum(); j++) {
                        this->matrix[i][j] += other.matrix[i][j];
                    }
                }

            }
            else {
                throw ProcessUnexpected("The number of columns is not equal. Addition stopped\n");
            }
        }
        else {
            throw ProcessUnexpected("The number of lines is not equal. Addition stopped\n");
        }
    }
    void operator = (Matrix& other) {

        if (other.get_strnum() != this->get_strnum() || this->get_colnum() != other.get_strnum()) {
            throw other;
        }
        else {
            for (int i = 0; i < get_strnum(); i++) {
                for (int j = 0; j < get_colnum(); j++) {
                    this->matrix[i][j] = other.matrix[i][j];
                }
            }
            return;
        }

    }




    };

int main() {
    set_unexpected(new_unexpected);
    set_terminate(new_terminate);

    //демонстрация работы каждого из исключений. Можно урезать, можно нет
   
    try {
        cout << "creating 0x0 matrix attempt: " << endl;
        Matrix<int> m1{ 0,0 };
     
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
    try {
        cout << "creating 2x1 matrix attempt: " << endl;
        Matrix<int> m1{ 2,1 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
      
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element -1X0" << endl;
        m1.clear_el(-1, 0);
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
        cout << "replace element 1X2" << endl;
        m1.edit_el(1, 2, 999);
   
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
   
   
   
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
        cout << "replace element 1X1" << endl;
        m1.edit_el(m1.get_strnum() - 1, m1.get_colnum() - 1, 999);
        m1.print_matrix();
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
   
   
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
        cout << "replace last element (ind 1X1)" << endl;
        m1.edit_el(m1.get_strnum() - 1, m1.get_colnum() - 1, 999);
        m1.print_matrix();
        
        cout << "Adding 3X3 matrix";  
        Matrix<int> m2{3, 3};
        m1 + m2;
   
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
        cout << "replace last element (ind 1X1)" << endl;
        m1.edit_el(m1.get_strnum() - 1, m1.get_colnum() - 1, 999);
        m1.print_matrix();
   
        cout << "Adding 3X3 matrix" << endl;
        Matrix<int> m2{3, 3};
        m1 + m2;
        m1.print_matrix();
        
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
   
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
        cout << "replace last element (ind 1X1)" << endl;
        m1.edit_el(m1.get_strnum() - 1, m1.get_colnum() - 1, 999);
        m1.print_matrix();

        cout << "Adding 2X2 matrix m2" << endl;
        Matrix<int> m2{ 2, 2 };
        m1 + m2;
        m1.print_matrix();
        cout << "Assigning 2x2 matrix to m1" << endl;
        m1 = m2;
        m1.print_matrix();
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
    try {
        cout << "creating 2x2 matrix attempt: " << endl;
        Matrix<int> m1{ 2,2 };
        m1.print_matrix();
        cout << "sort" << endl;
        m1.sort();
        m1.print_matrix();
        cout << "clear element 0X0" << endl;
        m1.clear_el(0, 0);
        m1.print_matrix();
        cout << "replace last element (ind 1X1)" << endl;
        m1.edit_el(m1.get_strnum() - 1, m1.get_colnum() - 1, 999);
        m1.print_matrix();


        cout << "Assigning 3x3 matrix to m1" << endl;

        Matrix<int> m2{ 3, 3 };
        m1 = m2;
        m1.print_matrix();
    }
    catch (IndexError error_index) {
        error_index.what_happened();
        cout << "Entered: " << error_index.get_line() << "X" << error_index.get_line() << endl;
    }
    catch (ProcessUnexpected err) {
        err.what_happened();
    }
    catch (...) {
        unexpected();
    }
    return 0;

}