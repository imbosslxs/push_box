#ifndef _DEU_LABEL_H_
#define _DEU_LABEL_H_

#include "../../dog_engine/dog_engine.h"
#include "../node/node.h"

namespace dog_engine_unit{
	typedef int dog_color;

	class label : public node{
	public:
		dog_point size;
		string text;
		//-1 means alpha
		dog_color f_color,b_color;


		void set_text(string _t);
		string get_text();

		void set_size(dog_point _s);
		dog_point get_size();

		void set_f_color(dog_color _f_c);
		void set_b_color(dog_color _b_c);
		dog_color get_f_color();
		dog_color get_b_color();


		virtual void update();

		virtual void init();

		static label *create(string _text);
		static label *create(string _text,dog_point _pos);
		static label *create(string _text,dog_point _pos,dog_color _f_c,dog_color _b_c);
	};

}




#endif