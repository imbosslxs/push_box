#include "deu_exception.h"

using namespace dog_engine_unit;

void deu_exception::show_msg(){
	msg_box(msg,tag);
}

deu_exception::deu_exception(){
	msg = "none";
	tag = "You Know What:";
	type = 0;
}

deu_exception::deu_exception(string _tag,string _msg,int _type){
	msg = _msg;
	tag = _tag;
	type =_type;
}

deu_exception::deu_exception(string _msg,int _type){
	msg = _msg;
	tag = "You Know What:";
	type = _type;
}