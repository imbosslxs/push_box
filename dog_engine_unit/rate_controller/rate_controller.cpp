#include "rate_controller.h"

using namespace dog_engine_unit;


void rate_controller::set_value(int _v){
	value = _v;
	auto &lb1 = *((label*)children[2]);
	lb1.set_text(convert_int_to_string(value));
	set_size({lb1.get_size().x+2,1});
	auto &b2 = *((button*)children[1]);
	b2.set_pos({lb1.get_size().x+1,0});
}
int rate_controller::get_value(){
	return value;
}

void rate_controller::set_on_value_change_call_func(function<void(int,rate_controller&)> _f){
	on_value_change_call_func = _f;
}


void rate_controller::init(){
	layer::init();

	set_size({3,1});
	value = 0;

	on_value_change_call_func = 0;

	auto &a = *this;
	auto b1_bt = bitchar_type::create_from_string("-",true);
	auto b2_bt = bitchar_type::create_from_string("-",true);
	b1_bt.set_color(12);
	b2_bt.set_color(9);
	auto b1 = button::create(
								{0,0},
								bitchar_type::create_from_string("-",true),
								b1_bt,
								b2_bt,
								[&]()->bool{
									a.set_value(a.get_value()-1);
									if(a.on_value_change_call_func)a.on_value_change_call_func(a.get_value(),a);
									return true;
								});
	add_child(b1);
	b1_bt = bitchar_type::create_from_string("+",true);
	b2_bt = bitchar_type::create_from_string("+",true);
	b1_bt.set_color(12);
	b2_bt.set_color(9);
	b1 = button::create(
								{2,0},
								bitchar_type::create_from_string("+",true),
								b1_bt,
								b2_bt,
								[&]()->bool{
									a.set_value(a.get_value()+1);
									if(a.on_value_change_call_func)a.on_value_change_call_func(a.get_value(),a);
									return true;
								});
	add_child(b1);
	auto lb1 = label::create("0",{1,0});
	add_child(lb1);
}


rate_controller *rate_controller::create(dog_point _pos,int _v){
	auto rc = new rate_controller();
	rc->init();
	rc->set_value(_v);
	rc->set_pos(_pos);
	return rc;
}



