// cpp_lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#define ARRLEN 5
#define BLOCK_SIZE 63
using namespace std;
class Car {
public:
    int sys_num;
    char brand[20];
    char model[20];
    char last_use[10];

    Car() {
        sys_num = 0;  
    };
    Car(int num) {
        cout << "Enter id - brand - model";
        cin >> this->sys_num >> this->model >> this->brand;
        try {
            new_use();
        }
        catch (exception& ex) {
            throw ex;
        }
    }
    Car(int num, std::string a, std::string b) {
        sys_num = num;
        strcpy_s(model, a.c_str());
        strcpy_s(brand, b.c_str());
        errno_t err = _strtime_s(last_use, 10);
        if (err)
        {throw exception("Error whilist handling time assignment");
        }
    };
    Car(int num, std::string a, std::string b, char* last) {
        sys_num = num;
        a.resize(19); b.resize(19);
        strcpy_s(this->brand, a.c_str());
        strcpy_s(this->model, b.c_str());
        strncpy_s(this->last_use, last, 9);
    };
    Car(const Car& car);
    ~Car() {}
    bool operator!=(Car&);
    int get_num() {
        return sys_num;
    }
    void new_use() {
        errno_t err = _strtime_s(last_use, 10);
        if (err)
        {   throw exception("Error whilist handling time assignment"); }
    }

    std::string get_color() {
        return model;
    }
    std::string get_model() {
        return brand;
    }
   static void output(vector<Car>& car_list);
   static void write_txt(vector<Car>&);
   static void read_txt(vector<Car>&);
   static void read_txt_reverse(vector<Car>&);
   static void find_txt(string,vector<Car>&);
   static void delete_txt(Car&);
   static void read_txt_bmode(vector<Car>&);
   static void read_txt_bmode_reverse(vector<Car>&);
   static void write_bin(vector<Car>&);
   static void read_bin(vector<Car>&);
   static void read_bin_reverse(vector<Car>&);
   static void delete_bin(Car&);
};
bool Car::operator!=(Car& other) {
    if (this->sys_num != other.sys_num) {
        return true; }
    int i = 0;
    while (this->model[i] == other.model[i])
    {   if (this->model[i] != other.model[i]) return true;
        i++; }
    i = 0;
    while (this->model[i] == other.model[i])
    {   if (this->model[i] != other.model[i]) return true;
        i++; }
    i = 0;
    while (this->brand[i] == other.brand[i])
    {   if (this->brand[i] != other.brand[i]) return true;
        i++;}
    return false;
}
ostream& operator<<(ostream& stream, const Car& car)
{   stream << setw(10) << car.sys_num << " " << setw(19)<< car.brand << " " << setw(19) << car.model << " " << setw(9) << car.last_use << " " << std::endl;
    return stream;
}

istream& operator>>(istream& stream,Car& car)
{
    int sys_num;
    char brand[20];
    char model[20];
    char last_use[10];

    stream >> sys_num >> brand >> model >> last_use;
    car.sys_num = sys_num;
    strcpy_s(car.model, model);
    strcpy_s(car.brand,brand);
    strcpy_s(car.last_use,last_use);
    return stream;
}
Car::Car(const Car& car)
{
    this->sys_num = car.sys_num;
    strncpy_s(this->brand, car.brand, 19);
    strncpy_s(this->model, car.model, 19);
    strncpy_s(this->last_use, car.last_use, 9);
}
void Car::write_txt(vector<Car>& car_list) {
    std::fstream dest;
    dest.open("text.txt", ios::trunc | std::ios_base::out);
    for (int i = 0; i < car_list.size(); i++) {
        dest << car_list[i];
    }
    dest.close();
}
void Car::read_txt(vector<Car>& car_list) {
    vector<Car> new_list;
    std::ifstream dest;
    dest.open("text.txt", std::ios_base::in);
    if (!dest.is_open()) { throw; };
    while (!dest.eof()) {
        Car car; 
        dest >> car; 
        new_list.push_back(car);
        }
    dest.close();
    car_list = new_list;
}
void Car::read_txt_reverse(vector<Car>& car_list) {
    vector<Car> new_list;
    std::ifstream dest;
    dest.open("text.txt", std::ios_base::in);
    dest.seekg(-BLOCK_SIZE, dest.end);
    if (!dest.is_open()) { throw; };
    char c; int i = 2;
    while (static_cast<int>(dest.tellg()) != -1) {
        Car car; dest >> car;
        new_list.push_back(car);
        dest.seekg(-(BLOCK_SIZE * i), dest.end);
        i++;
    }
    dest.close();
    car_list = new_list;
}
void Car::read_txt_bmode_reverse(vector<Car>& car_list) {
    vector<Car> new_list;
    std::ifstream inp;
    inp.open("text.txt", ios::in | std::ifstream::binary);
    if (!inp) { throw std::exception("File not opened"); }
    inp.seekg(0, ios::end);
    int num = (static_cast<int>(inp.tellg())) / BLOCK_SIZE;
    char temp[11] = { 0 };
    char temp1[20] = { 0 };  char temp3[10] = { 0 };
    for (int i = 1; i <= num; i++) {
        Car car;
        inp.seekg(-(i * BLOCK_SIZE), ios::end);
        inp.read((char*)&temp, 10);
        car.sys_num = atoi(temp);
        inp.seekg(static_cast<int>(inp.tellg()) + 1, ios::beg);
        inp.read((char*)&temp1, 19);
        strcpy_s(car.brand, temp1);
        inp.seekg(static_cast<int>(inp.tellg()) + 1, ios::beg);
        inp.read((char*)&temp1, 19);
        strcpy_s(car.model, temp1);
        inp.seekg(static_cast<int>(inp.tellg()) + 1, ios::beg);
        inp.read((char*)&temp3, 9);
        strcpy_s(car.last_use, temp3);
        new_list.push_back(car);
    }
    inp.close();
    car_list = new_list;
}
void Car::delete_txt(Car& car_m) {
    Car car;
    std::fstream src;
    src.open("text.txt",ios_base::in);
    int count = 0;
    std::fstream dest;
    dest.open("temporary.txt", ios::trunc |ios_base::in | ios_base::out);
    while (!src.eof()) {
        src >> car;
        if (car.sys_num > 0) {
            if (car != car_m) {
                dest << car;
            }
            else {
                ++count;
            }
        }
    }
    std::cout << "(" << count << ")entries deleted" << std::endl;
    src.close();
    dest.close();
    remove("text.txt");
    rename("temporary.txt", "text.txt");
}
void Car::delete_bin(Car& car_m) {
    Car car;
    std::fstream src;
    src.open("textb.bin", std::ios_base::in);
    int count = 0;
    std::fstream dest;
    dest.open("temp.bin", ios::trunc | ios_base::in | ios_base::out);
    src.seekg(0, ios::end);
    int num = src.tellg() / sizeof(Car);
    src.seekg(0, ios::beg);
    for (int i = 0; i < num; i++) {
        src.read((char*)&car, sizeof(Car));
        if (car_m != car) {
            dest.write((char*)&car, sizeof(Car));
        }
        else {  }
    }
    dest.close(); src.close();
    remove("textb.bin");
    rename("temp.bin", "textb.bin");

}
void Car::read_txt_bmode(vector<Car>& car_list){
    vector<Car> new_list;
    std::ifstream inp;
    inp.open("text.txt", ios::in | std::ifstream::binary);
    if (!inp) { throw std::exception("File not opened"); }
    inp.seekg(0, ios::end);
    int num = (static_cast<int>(inp.tellg())) / BLOCK_SIZE;
    inp.seekg(0, ios::beg);
    char temp[11] = { 0 };
    char temp1[20] = { 0 };  char temp3[10] = { 0 };
    for (int i = 0; i < num; i++) {
        Car car;
        inp.seekg(i*BLOCK_SIZE, ios::beg);
        cout << static_cast<int>(inp.tellg()) << endl;
        inp.read((char*)&temp, 10);
        car.sys_num = atoi(temp);
        inp.seekg(static_cast<int>(inp.tellg()) + 1, ios::beg);
        inp.read((char*)&temp1, 19); 
        strcpy_s(car.brand, temp1);
        inp.seekg(static_cast<int>(inp.tellg()) + 1, ios::beg);
        inp.read((char*)&temp1, 19);
        strcpy_s(car.model, temp1);
        inp.seekg(static_cast<int>(inp.tellg()) + 1, ios::beg);
        inp.read((char*)&temp3, 9);
        strcpy_s(car.last_use, temp3);
        new_list.push_back(car);
    }
    inp.close();
    car_list = new_list;
}
void  Car::write_bin(vector<Car>& car_list) {
   std::ofstream outf("textb.bin", std::ofstream::binary | std::ofstream::trunc);
   if (!outf) { throw std::exception("File not opened"); }
   for (int i = 0; i < car_list.size(); i++) {
       outf.write((char *)&car_list[i], sizeof(Car));
   }
   outf.close();
}
void  Car::read_bin(vector<Car>& car_list) {
    vector<Car> new_list;
    std::ifstream inp;
    inp.open("textb.bin", ios::in | std::ifstream::binary);
    if (!inp) { throw std::exception("File not opened"); }
    inp.seekg(0, ios::end);
    int num = (static_cast<int>(inp.tellg())) / sizeof(Car); 
    inp.seekg(0, ios::beg);
    Car car;
    for (int i = 0; i < num; i++) {
        inp.read((char*)&car, sizeof(Car));
        new_list.push_back(car);
    }
        inp.close();
        car_list = new_list;
    }

void  Car::read_bin_reverse(vector<Car>& car_list) {
    vector<Car> new_list;
    std::ifstream inp;
    inp.open("textb.bin", ios::in | std::ifstream::binary);
    if (!inp) { throw std::exception("File not opened"); }
    inp.seekg(0, ios::end);
    int num = (static_cast<int>(inp.tellg())) / sizeof(Car);
   for(int i = 1; i< num + 1 ; i++){
       Car car;
        inp.seekg(-(static_cast<int>(sizeof(Car))*i), ios::end);
        inp.read((char*)&car, sizeof(Car));
        new_list.push_back(car);
    }
    inp.close();
    car_list = new_list;
}

void Car::output(vector<Car>& car_list) {
    if (car_list.size() > 0) {
        std::cout << std::setw(5) << "___Id" << std::setw(20) << "_______________Model" << std::setw(20) << "______________Brand" << std::setw(15) << "__________used" << std::endl;
        for (int i = 0; i < car_list.size(); i++) {
            if (car_list[i].sys_num > 0) {
                cout << std::setw(5) << car_list[i].sys_num;
                cout << std::setw(20) << car_list[i].brand;
                cout << std::setw(20) << car_list[i].model;
                cout << std::setw(15) << car_list[i].last_use << std::endl;
            }
        }
    }

}

int main()
{
    _tzset();
    const char* filepath = "text.txt";
    const char* filepath_binmode = "textb.txt";
    const char* filepath_bin = "textb.bin";

    vector<Car> cars;
    cars.push_back(Car(1, "toyota", "camry"));
    cars.push_back(Car(2, "hundai", "solaris"));
    cars.push_back(Car(3, "geely", "x"));
    cars.push_back(Car(4, "ford", "focus"));

    int ch;
    do {
        cout << "1 - add element to vector<Car>" << endl;
        cout << "2 - read vector<Car>" << endl << endl;
        cout << "3 - write to txt file" << endl;
        cout << "4 - write to bin file" << endl;
        cout << "5 - read from txt file" << endl;
        cout << "6 - read from txt file (binmode)" << endl;
        cout << "7 - read from bin file" << endl;
        cout << "8 - read from txt file in reverse" << endl;
        cout << "9 - read from bin file in reverse" << endl;
        cout << "10 - read from txt file (binmode) in reverse" << endl;
        cout << "11 - delete from txt file" << endl;
        cout << "12 - delete from bin file" << endl;
        cin >> ch; if (std::cin.fail()) {
#undef max
            std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (ch) {
        case 1:
            try {
                Car new_el = Car(1);
                cars.push_back(new_el);
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 2:
            Car::output(cars);
            break;
        case 3:
            try {
                Car::write_txt(cars);
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 4:
            try {
                Car::write_bin(cars);
            }
            catch (exception& ex) {
                cout << ex.what() << endl;
            }
            break;
        case 5:
            try {
                Car::read_txt(cars);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 6:
            try {
                Car::read_txt_bmode(cars);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 7:
            try {
                Car::read_bin(cars);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 8:
            try {
                Car::read_txt_reverse(cars);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 9:
            try {
                Car::read_bin_reverse(cars);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 10:
            try {
                Car::read_txt_bmode_reverse(cars);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 11:
            try {
                Car temp = Car(1);
                Car::delete_txt(temp);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        case 12:
            try {
                Car temp = Car(1);
                Car::delete_bin(temp);
            }
            catch (exception& ex) { cout << ex.what() << endl; }
            break;
        defaut:
            break;
        }

    } while (ch);
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
