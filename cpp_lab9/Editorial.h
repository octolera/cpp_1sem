#pragma once
#include "Author.h"
#include <string>
#include <vector>
namespace printagency {
	class Editorial
	{
	protected:
		std::string title;
		std::string text;
		Author author;
	public:
		Editorial();
		Editorial(std::string, Author&);
		~Editorial();
		void new_author(Author&);
		void new_title(std::string);
		void new_text(std::string);
	};
}

