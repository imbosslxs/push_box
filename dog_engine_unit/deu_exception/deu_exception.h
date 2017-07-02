#ifndef _DEU_EXCEPTION_H_
#define _DEU_EXCEPTION_H_

#include "../../dog_engine/dog_engine.h"


namespace dog_engine_unit{


	class deu_exception{
	public:
		string msg;
		string tag;
		int type;

		void show_msg();

		deu_exception();
		deu_exception(string _tag,string _msg,int _type = 0);
		deu_exception(string _msg,int _type = 0);
	};
	inline void deu_throw(deu_exception e){
		e.show_msg();
		throw(e);
	}
	inline void deu_throw(string msg){
		auto e = deu_exception(msg);
		e.show_msg();
		throw(e);
	}

}


#endif