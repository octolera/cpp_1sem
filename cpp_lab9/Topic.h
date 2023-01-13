#pragma once

#include "Editorial.h"
#include "Author.h"

namespace printagency {
	class Topic: protected Editorial
	{
	private:
		std::string category;
	public:
		Topic();
		Topic(std::string, Author&, std::string);
		~Topic();
		std::string get_category();
	};
}
