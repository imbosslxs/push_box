#ifndef _DEU_DIRECTOR_H_
#define _DEU_DIRECTOR_H_

#include "../../dog_engine/dog_engine.h"
#include "../scene/scene.h"
#include "../resouce/resouce.h"


namespace dog_engine_unit{

	class task{
	public:
		DWORD n_time;//now time
		DWORD t_time;//target time

		int cnt;//repeat times

		int id;

		function<void()> call_func;

	};

	class director{
	public:
		Dog_Engine de;
		bool _is_quit;
		scene *now_scene = 0;
		resouce *p_res;


		Dog_Engine &get_dog_engine();

		scene *get_now_scene();
		void null_now_scene();

		void begin_scene(scene * sc);
		//would delete the now_scene pointer
		void change_scene(scene * sc);

		void quit();

		bool is_quit();

		vector<task*> tasks;
		int count_task_id();
		int task_id;
		void update_task();
		int add_task(DWORD t_time,function<void()>,int cnt = -1);
		void remove_task(int id);


		void set_resouce(resouce *_res);
		resouce *get_resouce_pointer();
		resouce &get_resouce();

		void release();

		static director &get_instance();
		static void init();
	};
}


#endif