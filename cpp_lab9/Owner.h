#pragma once
#include <string>
namespace printagency {
	class Owner
	{private:
		std::string credentials;
	 public:
		Owner();
		Owner(std::string&);
		~Owner();
		std::string get_credentials();
		void set_new_credentials(std::string&);
	};
}
