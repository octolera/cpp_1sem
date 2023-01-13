// cpp_lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <vector>
using namespace std;


template <class elemType> class MatrixContainer {
private:
    elemType** content = nullptr;
    size_t* str;
    size_t* col;
public:
    MatrixContainer() {
        str = new size_t; col = new size_t;
        *str = 0; *col = 0; }
    MatrixContainer(int str_i, int col_i) {
        str = new size_t; *str = str_i; col = new size_t; *col = col_i;
        content = new elemType*[(*str)]();
        for (int i = 0; i < (*str); i++)
        {   content[i] = new elemType[(*col)]();
        }
   }
    MatrixContainer(const MatrixContainer& matr) {
        str = new size_t; 
        col = new size_t; 
        *str = matr.get_str(); 
        *col = matr.get_col();
        content = new elemType*[(*str)]();
        for (int i = 0; i < (*str); i++)
        {content[i] = new elemType[(*col)]();
            for (int j = 0; j < (*col); j++) { content[i][j] = matr.get_el(i, j); }
        }
    }
    ~MatrixContainer() { 
    for (int i = 0; i < (*str); i++)
    { delete[] content[i]; 
    } delete[] content;
    delete str; delete  col; };
    size_t get_str()const { return *str; };
    size_t get_col()const { return *col; };
    
    void сlean_data() { for (int i = 0; i < (*str); i++) { for (int j = 0; j < (*col); j++) { content[i][j] = NULL; } } };
    void add_col(int col_add) {
        MatrixContainer temp = MatrixContainer(*this);
        content = new elemType * [(*str)]();
        (*col) += col_add;
        for (int i = 0; i < (*str); i++)
        { content[i] = new elemType[(*col)]();}
        for (int i = 0; i < temp.get_str(); i++) {
            for (int j = 0; j < temp.get_col(); j++) {
                content[i][j] = temp.content[i][j];
            }   } }

    void add_str(int str_add) {
    MatrixContainer temp = MatrixContainer(*this);
    content = new elemType*[(*str) + str_add]();
    for (int i = 0; i < (*str) + str_add; i++)
    {   content[i] = new elemType [(*col)]();
    } (*str) += str_add;
    for (int i = 0; i < temp.get_str(); i++) {
        for (int j = 0; j < temp.get_col(); j++) {
            content[i][j] = temp.content[i][j];
        }
    }}

    elemType get_el(int str, int col)const {
        return content[str][col];
    }
    void put_el(elemType& val, int str_i, int col_i) { 
        if(str_i > *str || col_i > *col) throw exception("Out of matrix range");
        for (int i = 0; i < *str; i++) {
            for (int j = 0; j < *col; j++) {
                if (content[i][j] == val) throw exception("This element already exists");
            }
        }
        content[str_i][col_i] = val; };

    void clear_el(int str_i, int col_i) { if (str_i > *str || col_i > *col) { throw exception("Out of matrix range"); } content[str_i][col_i] = elemType(); }

    void resize(int str_i, int col_i) {
        if (str_i < 1 || col_i < 1) { throw exception("Wrong size"); }
        MatrixContainer temp = MatrixContainer(*this);
        *col = col_i; *str = str_i;
        content = new elemType * [(*str)]();
        for (int i = 0; i < (*str); i++)
        { content[i] = new elemType[(*col)]();}
        size_t newc_1; size_t newc_2;
        (*str > temp.get_str()) ? newc_1 = temp.get_str() : newc_1 = *str;
        (*col > temp.get_col()) ? newc_2 = temp.get_col(): newc_2 = *col;
        for (int i = 0; i < newc_1; i++) {
            for (int j = 0; j < newc_2; j++) {
                content[i][j] = temp.content[i][j];
            }
        }
    }

    //MatrixContainer operator=(MatrixContainer new_m) const{
    //    for (int i = 0; i < new_m.get_str(); i++) {
    //        for (int j = 0; j < new_m.get_col(); j++) {
    //            content[i][j] = new_m.content[i][j];
    //        }
    //    }
    //}
    pair<int, int>& find_el(elemType& val) {
        for (int i = 0; i < *str; i++) {
            for (int j = 0; j < *col; j++) {
                if (content[i][j] == val) {
                    pair<int, int> i_pair = pair<int, int>(i, j); return i_pair;
               }
            }
        }
        throw exception("Not found");
      }
    friend  ostream& operator<<(ostream& os, const MatrixContainer& matrix); 

  //  operator=();
  //  operator+(MatrixContainer& matrix);
  //  bool operator>(); //сравнение элементов
  //  iterator it_str;
  //      iterator it_col;
};

ostream& operator<<(ostream& os, const MatrixContainer<int>& matrix) {
    for (int i = 0; i < matrix.get_str(); i++) {
        for (int j = 0; j < matrix.get_col(); j++) {
            os << setw(10) << matrix.get_el(i, j);
        }
        os << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const MatrixContainer<double>& matrix) {
    for (int i = 0; i < matrix.get_str(); i++) {
        for (int j = 0; j < matrix.get_col(); j++) {
            os << setw(15) << matrix.get_el(i, j);
        }
        os << endl;
    }        return os;
}

ostream& operator<<(ostream& os, const MatrixContainer<string>& matrix) {
    for (int i = 0; i < matrix.get_str(); i++) {
        for (int j = 0; j < matrix.get_col(); j++) {
            if (matrix.get_el(i, j) == "") {
                os << setw(30) << " empty field!";
            }
            else { os << setw(30) << matrix.get_el(i, j); }
        }
        os << endl;
    }        return os;
}

int main()
{   
    vector <MatrixContainer<int>> matrix_int;
    vector <MatrixContainer<double>> matrix_double;
    vector <MatrixContainer<string>> matrix_l_str;

    MatrixContainer<double>*matrix_c_double;
    MatrixContainer<int>* matrix_c_int;
    MatrixContainer<string>*matrix_str;
    int ch; int str_i; int col_i; int ind; int int_i; double double_i; string string_i;

    do {
        cout << "1 - create empty matrix" << endl;
        cout << "2 - create matrix with defined size" << endl;
        cout << "3 - resize matrix" << endl;
        cout << "4 - write to matrix" << endl;
        cout << "5 - find and delete element in matrix" << endl;
        cout << "6 - matrix output" << endl << endl << endl;
        cin >> ch; 
        if (std::cin.fail()) {
#undef max
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (ch) {
        case 1:
            cout << "1 - int " << endl;
            cout << "2 - double" << endl;
            cout << "3 - <std::string>" << endl;
            cin >> ch; if (std::cin.fail()) {
#undef max
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (ch) {
            case 1:
                matrix_c_int = new MatrixContainer<int>();
                matrix_int.push_back(*matrix_c_int);
                break;
            case 2:
                matrix_c_double = new MatrixContainer<double>();
                matrix_double.push_back(*matrix_c_double);
                break;
            case 3:
                matrix_str = new MatrixContainer<string>();
                matrix_l_str.push_back(*matrix_str);
                break;
            }
            break;
        case 2:
            cout << "1 - int " << endl;
            cout << "2 - double" << endl;
            cout << "3 - <std::string>" << endl;
            cin >> ch;
            cout << "Enter size NxN" << endl;
            cin >> str_i >> col_i;
            if (std::cin.fail()) {
#undef max
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (ch) {
            case 1:
                matrix_c_int = new MatrixContainer<int>(str_i, col_i);
                matrix_int.push_back(*matrix_c_int);
                break;
            case 2:
                matrix_c_double = new MatrixContainer<double>(str_i, col_i);
                matrix_double.push_back(*matrix_c_double);
                break;
            case 3:
                matrix_str = new MatrixContainer<string>(str_i, col_i);
                matrix_l_str.push_back(*matrix_str);
                break;
            }
            break;
        case 3:
            cout << "1 - int " << endl;
            cout << "2 - double" << endl;
            cout << "3 - <std::string>" << endl;
            cin >> ch;
            cout << "Enter size NxN" << endl;
            cin >> str_i >> col_i;
            if (std::cin.fail()) {
#undef max
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (ch) {
            case 1:
                for (auto i : matrix_int) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind; if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    matrix_int[ind].resize(str_i, col_i);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }

                break;
            case 2:
                for (auto i : matrix_double) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind; if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    matrix_double[ind].resize(str_i, col_i);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            case 3:
                for (auto i : matrix_l_str) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind; if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    matrix_l_str[ind].resize(str_i, col_i);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            break;
        case 4:
            cout << "1 - int " << endl;
            cout << "2 - double" << endl;
            cout << "3 - <std::string>" << endl;
            cin >> ch;
            cout << "Enter coordinates NxN" << endl;
            cin >> str_i >> col_i;
            if (std::cin.fail()) {
#undef max
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (ch) {
            case 1:
                for (auto i : matrix_int) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind;
                cout << "Enter the element" << endl;
                cin >> int_i;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    matrix_int[ind].put_el(int_i, str_i, col_i);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }

                break;
            case 2:
                for (auto i : matrix_double) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind;
                cout << "Enter the element" << endl;
                cin >> double_i;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    matrix_double[ind].put_el(double_i, str_i, col_i);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            case 3:
                for (auto i : matrix_l_str) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind;
                cout << "Enter the element" << endl;
                cin >> string_i;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    matrix_l_str[ind].put_el(string_i, str_i, col_i);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            break;
        case 5:
            cout << "1 - int " << endl;
            cout << "2 - double" << endl;
            cout << "3 - <std::string>" << endl;
            cin >> ch;
            if (std::cin.fail()) {
#undef max
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            switch (ch) {
            case 1:
                for (auto i : matrix_int) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind;
                cout << "Enter the element" << endl;
                cin >> int_i;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    pair <int, int> res = matrix_int[ind].find_el(int_i);
                    cout << "Found at ind  " << res.first << "x" << res.second << endl;
                    matrix_int[ind].clear_el(res.first, res.second);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            case 2:
                for (auto i : matrix_double) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind;
                cout << "Enter the element" << endl;
                cin >> double_i;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                    pair <int, int> res = matrix_double[ind].find_el(double_i);
                    cout << "Found at ind  " << res.first << "x" << res.second << endl;
                    matrix_double[ind].clear_el(res.first, res.second);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            case 3:
                for (auto i : matrix_l_str) {
                    cout << i;
                    cout << endl;
                }
                cout << "Enter the index" << endl;
                cin >> ind;
                cout << "Enter the element" << endl;
                cin >> string_i;
                if (std::cin.fail()) {
#undef max
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                try {
                 pair <int, int> res = matrix_l_str[ind].find_el(string_i);
                 cout << "Found at ind  " << res.first << "x" << res.second << endl;
                 matrix_l_str[ind].clear_el(res.first, res.second);
                }
                catch (exception& ex) {
                    cout << ex.what() << endl;
                }
                break;
            }
            break;
        case 6:
            cout << "int : " << endl;
            for (auto i : matrix_int) {
                cout << i;
                cout << endl;
            }
            cout << "double :" << endl;
            for (auto i : matrix_double) {
                cout << i;
                cout << endl;
            }
            cout << "std::string" << endl;
            for (auto i : matrix_l_str) {
                cout << i;
                cout << endl;
            }
            break;
        defaut:
            break;
        }
        ch = 1;
    } while (ch);
