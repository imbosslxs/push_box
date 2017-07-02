#include "dog_engine_unit.h"

using namespace dog_engine_unit;



int main(int argc,char **argv){

	director::init();

	deu_main(argc,argv);

	director &d = director::get_instance();
	Dog_Engine &de = d.get_dog_engine();
	while(!d.is_quit()){
		de.update();
		auto p_main_scene = d.get_now_scene();
		if(p_main_scene) p_main_scene->_event_update();
		d.update_task();
	}
	d.release();

	return 0;
}