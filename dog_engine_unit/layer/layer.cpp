#include "layer.h"


using namespace dog_engine_unit;

void layer::set_char(char _c){
	c = _c;
}
char layer::get_char(){
	return c;
}

void layer::set_size(dog_point _s){
	size = _s;
}
dog_point layer::get_size(){
	return size;
}

void layer::set_color(int _c){
	color = _c;
}
int layer::get_color(){
	return color;
}

void layer::init(){
	node::init();
	size = dog_point(-1,-1);
	color = -1;
	c = ' ';
}

void layer::update(){
	//msg_box("a");
	auto &de = get_dog_engine();
	if(color != -1)
		de.draw_rect(
					get_world_pos(),
					{size.x == -1 ? de.W : size.x, size.y == -1 ? de.H : size.y },
					color,
					c
					);
}

bool layer::event_update(){
	auto &de = get_dog_engine();
	auto mp = de.get_mouse_pos();
	auto np = get_world_pos();
	auto size = get_size();
	if(size.x == -1 || size.y == -1) return false;
	if(mp.x >= np.x && mp.x < np.x + size.x && mp.y >= np.y && mp.y < np.y + size.y){
		return true;
	}
	return false;
}

layer *layer::create(){
	return layer::create({0,0});
}

layer *layer::create(dog_point _p){
	return layer::create(_p,{-1,-1},-1);
}

layer *layer::create(dog_point _pos,dog_point _size,int _color){
	auto l = new layer();
	l->init();
	l->pos = _pos;
	l->size = _size;
	l->color = _color;
	return l;
}