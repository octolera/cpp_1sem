#include "Owner.h"
#include <string>
using namespace printagency;
Owner::Owner() {
};
Owner::Owner(std::string& name_inp) {
	credentials = name_inp;
};
printagency::Owner::~Owner() {

};
std::string Owner::get_credentials() { return credentials; };
void Owner::set_new_credentials(std::string& name_inp) { credentials = name_inp; };