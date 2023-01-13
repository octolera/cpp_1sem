#include "Topic.h"
using namespace printagency;
Topic::Topic() {}
Topic::Topic(std::string title_i, Author& auth, std::string category_i) :Editorial(title_i, auth) {
	category = category_i;
};
Topic::~Topic() {}
std::string Topic::get_category() { return category; }