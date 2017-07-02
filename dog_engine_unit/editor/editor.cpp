#include "editor.h"

using namespace dog_engine_unit;


void editor::set_on_text_change_call_func(function<void()> _f){
	on_text_change_call_func = _f;
}
void editor::set_on_text_change_call_func(function<void(string,editor&)> _f){
	on_text_change_call_func_1 = _f;
}

void editor::edit_text(){
	set_text(input_box(get_text(),"Edit it"));
	if(on_text_change_call_func) on_text_change_call_func();
	if(on_text_change_call_func_1)on_text_change_call_func_1(get_text(),*this);
}
void editor::set_text(string _text){
	text = _text;
	auto bc = bitchar_type::create_from_string(text,true);

	bc = bc.get_cut(size);

	bc.set_color(f_color,true);
	bc.set_color(b_color,false);
	set_skin(bc,0);
	set_skin(bc,1);
	set_skin(bc,2);
	set_skin(bc,3);
}
string editor::get_text(){
	return text;
}

void editor::set_edit_size(dog_point _s){
	size = _s;
	set_text(get_text());
}
dog_point editor::get_edit_size(){
	return size;
}

void editor::set_f_color(int _c){
	f_color = _c;
}
int editor::get_f_color(){
	return f_color;
}
void editor::set_b_color(int _c){
	b_color = _c;
}
int editor::get_b_color(){
	return b_color;
}


void editor::init(){
	button::init();
	f_color = DOG_COLOR_WHITE;
	b_color = DOG_COLOR_BLACK;

	size = dog_point(20,1);

	auto &a = *this;
	set_on_mouse_down_call_func(
								[&](){
									a.edit_text();
									return true;
								}
							);
	on_text_change_call_func = 0;
	on_text_change_call_func_1 = 0;
}

editor *editor::create(dog_point _pos,dog_point _size,string _text){
	auto e = new editor();
	e->init();
	e->set_pos(_pos);
	e->set_edit_size(_size);
	e->set_text(_text);
	return e;
}










