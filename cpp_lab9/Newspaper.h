#pragma once
#include "topic.h"
#include "Typography.h"
#include "Owner.h"

namespace printagency {


	class Newspaper
	{
	private:
		std::string title;
		size_t volume;
		size_t circulation; //тираж
		Typography printed_by;
		Topic* topics = nullptr;
		size_t t_num = 0;
		Editorial* editorials = nullptr;
		size_t e_num = 0;

	public:
		Newspaper();
		Newspaper(Typography&, std::string, int, int);
		~Newspaper();

		Typography& get_typography();
		std::string get_title(); 
		int get_topics_num();
		int get_edit_num();
		int get_volume();
		int get_circulation();

		void add_topic(std::vector<Author>&);
		void add_editorial(std::vector<Author>&);
	};
}
