#include "Typography.h"

using namespace printagency;
Typography::Typography() {
}
Typography::Typography(Owner& owner_i, std::string& name_i) {
	owner = owner_i;
	agency_name = name_i;
}
Typography::~Typography() {
}
void Typography::new_name(std::string& name_i) {
	agency_name = name_i;
}

void Typography::new_owner(Owner& owner_i) {
	owner = owner_i;
}
Owner& Typography::get_owner() { return owner; }
std::string Typography::get_name() { return agency_name; }
