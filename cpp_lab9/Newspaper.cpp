#include "Newspaper.h"
#include <iostream>

using namespace std;
using namespace printagency;


Newspaper::Newspaper() {
}
Newspaper::Newspaper(Typography& typography, std::string name, int vol, int circ) {
	printed_by = typography;
	title = name;
	volume = vol;
	circulation = circ;
}

Newspaper::~Newspaper() {
	if (t_num > 0) {
		delete[] topics;
	}
	if (e_num > 0) {
		delete[] editorials;
	}
}
Typography& Newspaper::get_typography() { return printed_by; }
string Newspaper::get_title() { return title; }
int Newspaper::get_topics_num(){ return t_num; }
int Newspaper::get_edit_num() { return e_num; }
int Newspaper::get_volume() { return volume; }
int Newspaper::get_circulation() { return circulation; }
void Newspaper::add_topic(std::vector<Author>& author_list) {
	Topic* topics_new;
	++t_num;
	topics_new = new Topic[t_num]();
	for (int i = 0; i < t_num - 1; i++) {
		topics_new[i] = topics[i];
	}
	int c; string title; string theme;
	Author::print_list(author_list);
	cout << "Choose the author" << endl;
	cin >> c;
	if(c > author_list.size() - 1 ) throw exception("Out of range");
	cout << "Enter the title" << endl;
	cin >> title;
	cout << "Enter the theme" << endl;
	cin >> theme;
	Topic insert = Topic(title, author_list[c], theme);
	topics_new[t_num - 1] = insert;
	topics = topics_new;
}
void Newspaper::add_editorial(std::vector<Author>& author_list) {
	Editorial* editorials_new;
	++e_num;
	editorials_new = new Editorial[e_num]();
	for (int i = 0; i < e_num - 1; i++) {
		editorials_new[i] = editorials[i];
	}
	int c;
	cout << endl;
	Author::print_list(author_list);
	cout << "Choose the author" << endl;
	cin >> c;
	if (c > author_list.size() - 1) throw exception("Out of range");
	cout << "Enter the title" << endl;
	cin >> title;
	Editorial insert = Editorial(title, author_list[c]);
	editorials_new[t_num - 1] = insert;
	editorials = editorials_new;
}