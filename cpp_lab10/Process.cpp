#include "Process.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;
Process::Process() {

}
Process::~Process() {
}

double Process::process_string(const char* string) {
	int sign;
	int ind = 0;
	int int_size;
	double num = 0;
	while (string[ind] != '\n' && string[ind] != '\0')
	{
		if (ind > 0) ++ind;
		sign = 1;
		while ((int)string[ind] != '+' && (int)string[ind] != '-' && (int)string[ind] < '0' && (int)string[ind] > '9') {
			++ind;
}
		if (string[ind] == '+') {
			++ind;
		}
		else if (string[ind] == '-') {
			sign *= -1;
			++ind;
		}
		int_size = ind;

		while (string[int_size] >= '0' && string[int_size] <= '9') {
			++int_size;
		}
		int_size -= ind;
		while (int_size) {
			int_size--;
			num += (pow(10, int_size) * (string[ind] - '0')*sign);
			++ind;
		}
		
		if (string[ind] == '.' || string[ind] == ',') {
			ind++;
			int dec_size = 1;
			while (string[ind] >= '0' && string[ind] <= '9') {

				num += pow(10, -dec_size) * (string[ind] - '0') * sign;
				++ind;
				dec_size++;
			}
		}

	}
	return num;
}

 void Process::from_file(const char* file_from, const char* file_to) {

	 vector<string> strings;
	 vector<string>::iterator str_iter;

	 vector<double> result;
	 string buffer;

	 ifstream stream;
	 stream.open(file_from, ios::in);
	 if (!stream.is_open()) { throw exception("Failed to open the file for input"); }
	 while (stream.good())
	 {
		 buffer.clear();
		 getline(stream, buffer);
		 strings.push_back(buffer);
	 }
	 stream.close();
	 cout << strings.size() << " lines read" << endl;
	 
	 for (str_iter = strings.begin(); str_iter != strings.end(); str_iter++) {
		 result.push_back(process_string(str_iter->c_str()));
		 cout << "Line " << result.size() << " summary " << result.back() << endl; 
	 }

	 ofstream ostream;
	 ostream.open(file_to);
	 if (!ostream.is_open()) { throw exception("Failed to open the file for output"); }
	 for (int i = 0; i < result.size(); i++) {
		 ostream  << result[i] << endl;
	 }
	 ostream.close();
}

