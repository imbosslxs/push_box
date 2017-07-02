#ifndef _DEU_EDITOR_H_
#define _DEU_EDITOR_H_

#include "../button/button.h"

namespace dog_engine_unit{

	class editor : public button{
	public:
		string text;
		dog_point size;
		int f_color,b_color;

		function<void()> on_text_change_call_func;
		function<void(string,editor&)> on_text_change_call_func_1;

		void set_on_text_change_call_func(function<void()> _f);
		void set_on_text_change_call_func(function<void(string,editor&)> _f);

		void set_edit_size(dog_point _s);
		dog_point get_edit_size();

		void edit_text();
		void set_text(string _t);
		string get_text();

		void set_f_color(int _c);
		int get_f_color();
		void set_b_color(int _c);
		int get_b_color();

		virtual void init();

		static editor* create(dog_point _pos,dog_point _size = dog_point(20,1),string _text = string());
	};

}




#endif