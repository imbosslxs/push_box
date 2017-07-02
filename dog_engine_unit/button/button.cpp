#include "button.h"

using namespace dog_engine_unit;

void button::set_on_mouse_move_call_func(function<bool()> _f){
	on_mouse_move_call_func = _f;
}
void button::set_on_mouse_down_call_func(function<bool()> _f){
	on_mouse_down_call_func = _f;
}
void button::set_on_mouse_up_call_func(function<bool()> _f){
	on_mouse_up_call_func = _f;
}

void button::set_on_mouse_move_call_func(function<bool(button*)> _f){
	on_mouse_move_call_func_1 = _f;
}
void button::set_on_mouse_down_call_func(function<bool(button*)> _f){
	on_mouse_down_call_func_1 = _f;
}
void button::set_on_mouse_up_call_func(function<bool(button*)> _f){
	on_mouse_up_call_func_1 = _f;
}

int button::get_mode(){
	return mode;
}

void button::freeze(){
	mode = 3;
}
void button::un_freeze(){
	mode = 0;
}
bool button::is_freeze(){
	return mode == 3;
}

void button::set_skin(bitchar_type bt,int id){
	skins[id] = bt;
}
bitchar_type button::get_skin(int id){
	return skins[id];
}

dog_point button::get_size(){
	return skins[mode].get_size();
}


void button::init(){
	node::init();
	is_call[0] = 0;
	is_call[1] = 0;
	is_call[2] = 0;
	on_mouse_move_call_func = []()->bool{return true;};
	on_mouse_down_call_func = []()->bool{return true;};
	on_mouse_up_call_func = []()->bool{return true;};

	on_mouse_move_call_func_1 = [](button*)->bool{return true;};
	on_mouse_down_call_func_1 = [](button*)->bool{return true;};
	on_mouse_up_call_func_1 = [](button*)->bool{return true;};
	mode = 0;

}

void button::update(){
	//msg_box("a");
	auto &de = get_dog_engine();
	bitchar_type::draw_bitchar_type(de,get_parent_pos_sum()+pos,skins[mode]);
}

bool button::event_update(){
	auto &de = get_dog_engine();
	auto mp = de.get_mouse_pos();
	auto np = get_world_pos();
	auto size = get_size();
	bool res = false;
	if(mp.x >= np.x && mp.x < np.x + size.x && mp.y >= np.y && mp.y < np.y + size.y){
		mode = 1;
		if(!is_call[0]){
			is_call[0] = 1;
			if(on_mouse_move_call_func) res |= on_mouse_move_call_func();
			if(on_mouse_move_call_func_1) res |= on_mouse_move_call_func_1(this);
		}
		if(de.get_mouse_down(VK_MOUSE_LEFT)){
			mode = 2;
			is_call[2] = 0;
			if(!is_call[1]){
				is_call[1] = 1;
				if(on_mouse_down_call_func) res |= on_mouse_down_call_func();
				if(on_mouse_down_call_func_1) res |= on_mouse_down_call_func_1(this);
			}
		}else{
			is_call[1] = 0;
			if(!is_call[2]){
				is_call[2] = 1;
				if(on_mouse_up_call_func) res |= on_mouse_up_call_func();
				if(on_mouse_up_call_func_1) res |= on_mouse_up_call_func_1(this);
			}
		}
		return true;
	}else{
		mode = 0;
		is_call[0] = 0;
	}

	return false;//res;
}

button *button::create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,function<bool()> down_call_func){
	return button::create(_pos,s0,s1,s2,s1,[](){return true;},down_call_func,[](){return true;});
}

button *button::create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,bitchar_type s3,function<bool()> f1,function<bool()>f2,function<bool()>f3){
	auto b = new button();
	b->init();
	b->set_pos(_pos);
	b->set_on_mouse_move_call_func(f1);
	b->set_on_mouse_down_call_func(f2);
	b->set_on_mouse_up_call_func(f3);

	b->set_skin(s0,0);
	b->set_skin(s1,1);
	b->set_skin(s2,2);
	b->set_skin(s3,3);
}

button *button::create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,function<bool(button*)> down_call_func){
	return button::create(_pos,s0,s1,s2,s1,[](button* b){return true;},down_call_func,[](button* b){return true;});
}

button *button::create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,bitchar_type s3,function<bool(button*)> f1,function<bool(button*)>f2,function<bool(button*)>f3){
	auto b = new button();
	b->init();
	b->set_pos(_pos);
	b->set_on_mouse_move_call_func(f1);
	b->set_on_mouse_down_call_func(f2);
	b->set_on_mouse_up_call_func(f3);

	b->set_skin(s0,0);
	b->set_skin(s1,1);
	b->set_skin(s2,2);
	b->set_skin(s3,3);
}