#include "listviewer.h"

using namespace dog_engine_unit;




void listviewer::add_contain(button *_b, string _key) {
	if (!_b) {
		deu_throw("_b == nullptr !");
	}
	auto &l1 = *( (layer*)children[2] );
	l1.add_child(_b, _key);
}
void listviewer::remove_contain(string _key) {
	auto &l1 = *( (layer*)children[2]);
	l1.remove_child_by_key(_key);
	base_i = 0;
}

void listviewer::refresh_contain() {
	auto &l1 = *( (layer*)children[2] );
	int sum_x = 0;

	for (auto &c : l1.children) {
		if (c)c->set_visible(0);
	}

	if (is_up) {
		for (int i = base_i; i < l1.children.size(); ++i) {
			if (sum_x + ((button*)l1.children[i])->get_size().y <= l1.size.y) {
				((button*)l1.children[i])->set_pos({  (l1.size.x - ((button*)l1.children[i])->get_size().x) / 2, sum_x});
				((button*)l1.children[i])->set_visible(1);
				sum_x += gap + ((button*)l1.children[i])->get_size().y;
			} else
				break;
		}
	} else {
		for (int i = base_i; i < l1.children.size(); ++i) {
			if (sum_x + ((button*)l1.children[i])->get_size().x <= l1.size.x) {
				((button*)l1.children[i])->set_pos({sum_x,  (l1.size.y - ((button*)l1.children[i])->get_size().y) / 2 });
				((button*)l1.children[i])->set_visible(1);
				sum_x += gap + ((button*)l1.children[i])->get_size().x;
			} else
				break;
		}
	}
}



void listviewer::prev_contain() {
	base_i -= 1;
	if (base_i < 0)base_i = 0;
	/*if(base_i == 0) children[0]->set_visible(0);
	children[1]->set_visible(1);*/
}
void listviewer::next_contain() {
	base_i += 1;
	//msg_box(string("s:") + (int)children.size());
	if (base_i > ( (layer*)children[2] )->children.size() - 1) base_i = ( (layer*)children[2] )->children.size() - 1 <= 0 ? 0 : ( (layer*)children[2] )->children.size() - 1;
	/*if(base_i == ( (layer*)children[2] )->children.size()-1) children[1]->set_visible(0);
	children[0]->set_visible(1);*/
}

void listviewer::set_up(bool _u) {
	is_up = _u;
}
bool listviewer::get_up() {
	return is_up;
}

void listviewer::set_base_i(int _b) {
	if (_b < 0) _b = 0;
	else if (_b >= children[2]->children.size()) _b = children[2]->children.size() - 1;
	base_i = _b;
}
int listviewer::get_base_i() {
	return base_i;
}

void listviewer::set_gap(int _g) {
	gap = _g;
}
int listviewer::get_gap() {
	return gap;
}


void listviewer::init() {
	layer::init();
	base_i = 0;
	gap = 1;
	is_up = false;

	auto lv = this;
	auto &a = *lv;

	auto b1 = button::create(
	{lv->size.x / 2 - 6, lv->size.y - 1},
	bitchar_type::create_from_string(" PREV ", true),
	bitchar_type::create_from_string(">PREV<", true),
	bitchar_type::create_from_string("|PREV|", true),
	[&]() {
		a.prev_contain();
		return true;
	}
	);
	lv->add_child(b1);

	auto b2 = button::create(
	{lv->size.x / 2 + 1, lv->size.y - 1},
	bitchar_type::create_from_string(" NEXT ", true),
	bitchar_type::create_from_string(">NEXT<", true),
	bitchar_type::create_from_string("|NEXT|", true),
	[&]() {
		a.next_contain();
		return true;
	}
	);
	lv->add_child(b2);

	auto l1 = layer::create({0, 0}, {lv->size.x, lv->size.y - 1}, 11);
	lv->add_child(l1);
}

void listviewer::update() {
	((button*)children[0])->set_pos({size.x / 2 - 6, size.y - 1});
	((button*)children[1])->set_pos({size.x / 2 + 1, size.y - 1});

	((layer*)children[2])->set_size({size.x, size.y - 1});

	refresh_contain();
	layer::update();
}

listviewer *listviewer::create(dog_point _pos, dog_point _size) {
	auto lv = new listviewer();
	lv->init();
	lv->set_pos(_pos);
	lv->set_size(_size);



	return lv;
}







