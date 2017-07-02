#ifndef _DEU_BUTTON_H_
#define _DEU_BUTTON_H_

#include "../../dog_engine/dog_engine.h"
#include "../node/node.h"
#include "../bitchar_type/bitchar_type.h"

namespace dog_engine_unit{

	class button : public node{
		bool is_call[3];
		int mode;
	public:

		bitchar_type skins[4];//0 = normal,1 = move,2 = down,3 = disable


		function<bool()> on_mouse_move_call_func;
		function<bool()> on_mouse_down_call_func;
		function<bool()> on_mouse_up_call_func;

		void set_on_mouse_move_call_func(function<bool()>);
		void set_on_mouse_down_call_func(function<bool()>);
		void set_on_mouse_up_call_func(function<bool()>);

//by 2017.1.11
		function<bool(button*)> on_mouse_move_call_func_1;
		function<bool(button*)> on_mouse_down_call_func_1;
		function<bool(button*)> on_mouse_up_call_func_1;

		void set_on_mouse_move_call_func(function<bool(button*)>);
		void set_on_mouse_down_call_func(function<bool(button*)>);
		void set_on_mouse_up_call_func(function<bool(button*)>);

		int get_mode();

		void freeze();
		void un_freeze();
		bool is_freeze();

		void set_skin(bitchar_type bt,int id);
		bitchar_type get_skin(int id);

		dog_point get_size();

		virtual void update();
		virtual bool event_update();

		virtual void init();

		static button *create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,function<bool()> down_call_func);
		static button *create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,bitchar_type s3,function<bool()> f1,function<bool()>f2,function<bool()>f3);

		//by 2017.1.11
		static button *create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,function<bool(button*)> down_call_func);
		static button *create(dog_point _pos,bitchar_type s0,bitchar_type s1,bitchar_type s2,bitchar_type s3,function<bool(button*)> f1,function<bool(button*)>f2,function<bool(button*)>f3);
	};


}


#endif