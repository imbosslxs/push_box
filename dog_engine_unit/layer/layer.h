#ifndef _DEU_LAYER_H_
#define _DEU_LAYER_H_


#include "../node/node.h"

namespace dog_engine_unit{

	class layer : public node{
	public:
		dog_point size;//-1 means window_W/H
		int color;//always b_color and -1 means alpha = 0
		char c;

		void set_char(char _c);
		char get_char();

		void set_size(dog_point _s);
		dog_point get_size();

		void set_color(int _c);
		int get_color();

		virtual void update();
		virtual bool event_update();

		virtual void init();

		static layer *create();
		static layer *create(dog_point _pos);
		static layer *create(dog_point _pos,dog_point _size,int _color);

	};


}


#endif