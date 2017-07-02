#ifndef _DE_COLOR_SELECTOR__
#define _DE_COLOR_SELECTOR__

#include "../node/node.h"
#include "../layer/layer.h"
#include "../button/button.h"
#include "../label/label.h"

namespace dog_engine_unit{

	class color_selector : public layer{
	public:
		int value;
		function<void(int,color_selector&)> on_value_change_call_func;

		void set_value(int _v);//-1~255
		int get_value();

		void set_on_value_change_call_func(function<void(int,color_selector&)> _f);

		virtual void init();

		static color_selector *create(dog_point _pos,int _v);
	};

}


#endif