#ifndef _DEU_RATE_CONTROLLER_H_
#define _DEU_RATE_CONTROLLER_H_

#include "../layer/layer.h"
#include "../label/label.h"
#include "../button/button.h"

namespace dog_engine_unit{

	class rate_controller : public layer{
	public:
		function<void(int,rate_controller&)> on_value_change_call_func;

		int value;

		void set_on_value_change_call_func(function<void(int,rate_controller&)>);

		void set_value(int _v);
		int get_value();

		virtual void init();

		static rate_controller *create(dog_point _pos,int _value);


	};

}









#endif