#include "bitchar.h"


using namespace dog_engine_unit;

void bitchar::set_bitchar(bitchar_type _bt){
	bt = _bt;
	size = _bt.size;
}
bitchar_type bitchar::get_bitchar(){
	return bt;
}

dog_point bitchar::get_size(){
	return size;
}

void bitchar::update(){
	auto &de = get_dog_engine();
	//msg_box(string("size W:") + bt.size.x);
	//msg_box(string("size H:") + bt.size.y);
	bitchar_type::draw_bitchar_type(de,get_parent_pos_sum()+pos,bt);
}

void bitchar::init(){
	node::init();

	size = dog_point(0,0);
}



bitchar *bitchar::create(bitchar_type _bt,dog_point _pos){
	auto b = new bitchar();
	b->init();
	b->set_bitchar(_bt);
	b->set_pos(_pos);
	return b;
}

bitchar *bitchar::create(bitchar_type _bt){
	return bitchar::create(_bt,{0,0});
}