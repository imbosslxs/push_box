#include "color_selector.h"

using namespace dog_engine_unit;

void color_selector::set_value(int _v){
	value = _v;
	if(value > 999) value = -1;
	else if(value < -1) value = 999;
	auto la = (layer*)find_child_by_key("la");
	if(la) la->set_color(value);
	auto lb = (label*)find_child_by_key("l1");
	if(lb) lb->set_text(convert_int_to_string(value));
}
int color_selector::get_value(){
	return value;
}

void color_selector::set_on_value_change_call_func(function<void(int,color_selector&)> _f){
	on_value_change_call_func = _f;
}

void color_selector::init(){
	layer::init();
	set_value(0);
	on_value_change_call_func = 0;

	auto la = layer::create({0,0},{5,2},value);
	add_child(la,"la");

	auto &a = *this;
	auto bt1 = bitchar_type::create_from_string("-",true);
	bt1.set_color(9);
	auto bt1_1 = bitchar_type::create_from_string("-",true);;
	bt1_1.set_color(12);
	auto b1 = button::create(
								{0,2},
								bitchar_type::create_from_string("-",true),
								bt1_1,
								bt1,
								[&]()->bool{
									//msg_box("I'm a button1 !");
									a.set_value(a.get_value()-1);
									if(a.on_value_change_call_func)a.on_value_change_call_func(a.get_value(),a);
									return true;
								});
	add_child(b1,"b1");

	auto bt2 = bitchar_type::create_from_string("+",true);
	bt2.set_color(9);
	auto bt2_1 = bitchar_type::create_from_string("+",true);
	bt2_1.set_color(12);
	auto b2 = button::create(
								{4,2},
								bitchar_type::create_from_string("+",true),
								bt2_1,
								bt2,
								[&]()->bool{
									//msg_box("I'm a button1 !");
									a.set_value(a.get_value()+1);
									if(a.on_value_change_call_func)a.on_value_change_call_func(a.get_value(),a);
									return true;
								});
	add_child(b2,"b2");

	auto l1 = label::create(convert_int_to_string(get_value()),{1,2});
	add_child(l1,"l1");

}



color_selector *color_selector::create(dog_point _pos,int _v){
	auto cs = new color_selector();
	cs->init();
	cs->set_pos(_pos);
	cs->set_value(_v);
	return cs;
}
