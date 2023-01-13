#include "Author.h"
#include <iostream>

using namespace std;
using namespace printagency;

Author::Author(){}
Author::Author(std::string n, std::string s, std::string c) {
	name = n;
	surname = s;
	competence = c;
}
Author::~Author() {}
std::string Author::get_name() { return name; }
std::string Author::get_surname() { return surname; }
std::string Author::get_competence() { return competence; }
void Author::add_to_list(Author& author,std::vector<Author>& author_list) {
	author_list.push_back(author);
}
void Author::print_list(std::vector<Author>& author_list) {
	for (int i = 0; i < author_list.size(); i++) {
		cout << author_list[i].get_name() << " " << author_list[i].get_surname() << endl;
		cout << "Competence: " << author_list[i].get_competence() << endl << endl;
	}
}