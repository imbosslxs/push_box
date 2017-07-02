#include "msgbar.h"

using namespace dog_engine_unit;



void msgbar::set_text(bitchar_type _text){
	((bitchar*)children[0])->set_bitchar(_text);
}
bitchar_type msgbar::get_text(){
	return ((bitchar*)children[0])->get_bitchar();
}

void msgbar::init(){
	layer::init();

	auto bc = bitchar::create(bitchar_type(),{0,0});
	add_child(bc);
}

void msgbar::update(){
	auto &de = get_dog_engine();
	size = dog_point(de.W,((bitchar*)children[0])->get_size().y);
	pos = dog_point(0,(de.H - ((bitchar*)children[0])->get_size().y)/2);

	((bitchar*)children[0])->set_pos({(size.x-((bitchar*)children[0])->get_size().x)/2,0});
	layer::update();

}

msgbar *msgbar::create(bitchar_type _text){
	auto mb = new msgbar();
	mb->init();
	mb->set_text(_text);
	return mb;
}



