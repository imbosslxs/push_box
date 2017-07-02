#ifndef _DEU_BITCHAR_TYPE_H_
#define _DEU_BITCHAR_TYPE_H_

#include "../../dog_engine/dog_engine.h"
#include "../node/node.h"
#include "../json_object_type/json_object_type.h"

namespace dog_engine_unit{

	const int BCT_VERSION = 1;
	class bit_char{
	public:
		char c;
		int f_color = DOG_COLOR_BLACK,b_color = -1;
	};

	class bitchar_type{

	public:

		dog_point size;
		vector<vector<bit_char> > bc;


		bitchar_type();
		bitchar_type(string s);

		bitchar_type get_cut(dog_point _size);
		bitchar_type get_cut(dog_point _pos,dog_point _size);

		dog_point get_size();
		void set_size(dog_point _s);

		void set_color(int color,bool is_front = true,int x=-1,int y=-1);
		int get_color(bool is_front = true,int x=-1,int y=-1);


		static bitchar_type create_from_string(string s,bool normal);
		static bitchar_type create_from_string(string s);
		static bitchar_type create_from_file(string path);
		static void draw_bitchar_type(dog_engine &de,dog_point pos,bitchar_type &bt);

	};

}



#endif