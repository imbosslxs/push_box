#include "label.h"

using namespace dog_engine_unit;


void label::set_text(string _t){
	text = _t;
	set_size({ _t.size(),1 });
}
string label::get_text(){
	return text;
}

void label::set_size(dog_point _s){
	size = _s;
}
dog_point label::get_size(){
	return size;
}

void label::set_f_color(dog_color _f_c){
	f_color = _f_c;
}
void label::set_b_color(dog_color _b_c){
	b_color = _b_c;
}
dog_color label::get_f_color(){
	return f_color;
}
dog_color label::get_b_color(){
	return b_color;
}



void label::update(){
	auto &de = get_dog_engine();
	de.draw_text(text,get_parent_pos_sum() + pos,f_color,(b_color == -1 ),WORD(b_color));
}


label *label::create(string _t){
	return create(_t,{ 0,0 });
}

label *label::create(string _t,dog_point _pos){
	return create(_t,_pos,DOG_COLOR_BLACK,-1);
}

void label::init(){
	node::init();
	set_text("I am a label :)");
	set_pos({0,0});
	set_f_color(DOG_COLOR_BLACK);
	set_b_color(-1);
}

label *label::create(string _t,dog_point _pos,dog_color _f_c,dog_color _b_c){
	auto lb = new label();
	lb->init();
	lb->set_text(_t);
	lb->set_pos(_pos);
	lb->set_size({ _t.size(),1 });
	lb->set_f_color(_f_c);
	lb->set_b_color(_b_c);
	return lb;

}

