#include "Editorial.h"
using namespace printagency;
Editorial::Editorial() {
}
Editorial::Editorial(std::string title_i, Author& author_i) {
	author = author_i;
	title = title_i;
	text = std::string("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas pretium tristique mi eget aliquet. Nam metus leo, molestie a efficitur at, maximus in orci. Donec gravida purus et malesuada bibendum. Aliquam erat volutpat. Maecenas commodo massa sit amet turpis suscipit facilisis. Fusce pulvinar nunc est, a aliquam lacus porttitor non. Maecenas non mauris porttitor nisl bibendum laoreet eget ut tellus. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec eu quam fermentum, elementum nulla at, dictum mauris. Suspendisse sollicitudin mattis ligula ut aliquet. Duis lacinia leo magna, sed vulputate nibh eleifend at. Aliquam non nisl id lectus auctor vehicula eget non massa. Vivamus laoreet ornare felis, in facilisis dui congue id.");
}
Editorial::~Editorial() {
}
void Editorial::new_author(Author& author_i) {
	author = author_i;
}
void Editorial::new_title(std::string title_i) {
	title = title_i;
}
void Editorial::new_text(std::string text_i) {
	text = text_i;
}
