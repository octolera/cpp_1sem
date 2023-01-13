#pragma once
#include <string>
#include <vector>
namespace printagency {

	class Author
	{
	protected:
		std::string name;
		std::string surname;
		std::string competence;
	public:
		Author();
		Author(std::string, std::string, std::string);
		~Author();
		std::string get_name();
		std::string get_surname();
		std::string get_competence();
		static void add_to_list(Author&, std::vector<Author>&);
		static void print_list(std::vector<Author>&);
	};
}
