#ifndef _DEU_SCENE_H_
#define _DEU_SCENE_H_

#include "../../dog_engine/dog_engine.h"
#include "../node/node.h"

namespace dog_engine_unit{


	class scene{
	public:
		vector<node*> children;
		dog_engine *p_de;

		function<bool()> event_call_func;

		void set_dog_engine(dog_engine *_p_de);
		dog_engine &get_dog_engine();

		virtual void init();
		virtual void release();


		void add_child(node *_node);
		void add_child(node *_node,string _key);
		node *find_child_by_key(string _key);
		//remove as delete the child's pointer
		void remove_child_by_key(string _key);
		void remove_all_children();

		void set_on_event_call_func(function<bool()> _func);

		void _rev_update();
		void _update();
		bool _event_update();

		virtual void update();
		virtual bool event_update();

		static scene* create();

	};

}



#endif