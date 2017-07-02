#include "director.h"

using namespace dog_engine_unit;


director *_this_director = 0;



Dog_Engine &director::get_dog_engine(){
	return de;
}

void director::begin_scene(scene *sc){
	if(now_scene) return;
	if(!sc) deu_throw("NULL sc!");
	sc->set_dog_engine(&de);
	now_scene = sc;
	now_scene->init();
}

void director::change_scene(scene *sc){
	if(!now_scene) return;
	if(!sc) deu_throw("NULL sc!");
	sc->set_dog_engine(&de);
	now_scene->release();
	delete now_scene;
	now_scene = sc;
	now_scene->init();
}

void director::quit(){
	_is_quit = true;
}

bool director::is_quit(){
	return _is_quit;
}

scene *director::get_now_scene(){
	return now_scene;
}

void draw(float dt,Dog_Engine &de){
	//de.draw_text("Hello Wolrd!",{10,5});
	de.draw_color();
	auto now_scene = director::get_instance().get_now_scene();
	if(director::get_instance().now_scene) {
		now_scene->_update();
		now_scene->_rev_update();
	}
}

void director::null_now_scene(){
	now_scene = 0;
}

void director::set_resouce(resouce *_res){
	if(p_res){
		p_res->release();
		delete p_res;
	}
	p_res = _res;
	if(p_res)p_res->init();
} 
resouce *director::get_resouce_pointer(){
	return p_res;
}
resouce &director::get_resouce(){
	if(!p_res)deu_throw("None pointer of resouce!");
	return *p_res;
}

void director::release(){
	if(now_scene) now_scene->release();
	if(p_res) p_res->release();
}

void director::init(){

	_this_director = new director();
	director &d = *_this_director;
	d.de.init();
	d.de.draw = draw;
	d.null_now_scene();


	d.de.enable_fps(true);

	d._is_quit = false;

	d.p_res = 0;

	d.task_id = 0;
}

director & director::get_instance(){
	if(!_this_director) deu_throw("NULL director");
	return *_this_director;
}


//===========task=============
int director::count_task_id(){
	return task_id++;
}
void director::update_task(){
	for(auto &pt:tasks){
		if(pt){
			auto &t = *pt;
			if(get_time()-t.n_time > t.t_time){
					t.n_time = get_time();
					if(t.cnt > 0) --t.cnt; 
					if(t.call_func) t.call_func();
				}
		}
	}
	for(int i=0;i<tasks.size();++i){
		//msg_box(convert_int_to_string(i));
		if(tasks[i] && tasks[i]->cnt == 0){
			delete tasks[i];
			tasks.erase(tasks.begin()+i,tasks.begin()+i+1);
			--i;
		}
	}
}
int director::add_task(DWORD t_time,function<void()> _f,int cnt){
	int id = count_task_id();
	task *t  = new task({get_time(),t_time,cnt,id,_f});
	tasks.push_back(t);
	return id;
}
void director::remove_task(int id){
	for(int i=0;i<tasks.size();++i){
		if(tasks[i] && tasks[i]->id == id){
			delete tasks[i];
			tasks.erase(tasks.begin()+i,tasks.begin()+i+1);
			--i;
		}
	}
}
//============================