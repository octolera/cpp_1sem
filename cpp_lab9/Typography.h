#pragma once
#include "Owner.h"
#include <string>
namespace printagency {
	class Typography
	{
	private:
		Owner owner;
		std::string agency_name;		
	public:
		Typography();
		Typography(Owner&, std::string&);
		~Typography();
		void new_name(std::string&);
		void new_owner(Owner&);
		Owner& get_owner();
		std::string get_name();
	};
}
