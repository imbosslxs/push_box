#ifndef _DEU_LISTVIEWER_H_
#define _DEU_LISTVIEWER_H_

#include "../layer/layer.h"
#include "../label/label.h"
#include "../button/button.h"

namespace dog_engine_unit{

	class listviewer : public layer{
	public:
		int base_i;
		int gap;

		bool is_up;

		void add_contain(button *_b,string _key);
		void remove_contain(string _key);

		void refresh_contain();
		void prev_contain();
		void next_contain();

		void set_up(bool _u);
		bool get_up();
		void set_base_i(int _b);
		int get_base_i();
		void set_gap(int _g);
		int get_gap();


		virtual void init();

		virtual void update();

		static listviewer *create(dog_point _pos,dog_point _size);

	};

}





#endif