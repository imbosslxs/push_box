#include "GameLevel.h"
#include "GameResource.h"
#include "GameLog.h"

using namespace dog_engine_unit;
using namespace push_box;
using namespace std;

#define LOGI(s)(GameLog::Instance()->LogI("GameLevel",s))
#define LOGW(s)(GameLog::Instance()->LogW("GameLevel",s))
#define LOGE(s)(GameLog::Instance()->LogE("GameLevel",s))


void GameLevel::InitLevelWithFile(string path){
	m_objects.clear();
	m_objects.reserve(100);
	LOGI("Reading file...");
	string s = GameResource::Instance()->ReadTextFromFile(path);
	json_object_type jo = json_object_type::phraze(s);
	//LOGI(string("Result:\n")+json_object_type::json_object_type_to_string(jo,0));

	level = jo["level"].get_int();
	time = jo["time"].get_int();
	size_w = jo["size"][0].get_int();
	size_h = jo["size"][1].get_int();
	player_move_speed = 200;
	player_move_speed_ctime = 0;
	LOGI("Readed basic cfg.");

	main_layer = layer::create();
	main_layer->set_size({size_w+2,size_h+2});
	main_layer->set_color(DOG_COLOR_BLUE);
	LOGI("Created main_layer");

	second_layer = layer::create();
	second_layer->set_pos({1,1});
	second_layer->set_size({size_w,size_h});
	second_layer->set_color(DOG_COLOR_WHITE);
	LOGI("Created second_layer");

	main_layer->add_child(second_layer);
	LOGI("Added second_layer to main_layer");

	int n = jo["walls"].children.size();
	for(int i=0;i<n;++i){
		//LOGI(string("Reading walls ") + convert_int_to_string(i) + string(" ..."));
		int x = jo["walls"][i][0].get_int();
		//LOGI("setp 1");
		int y = jo["walls"][i][1].get_int();
		//LOGI("setp 2");
		GameLevelObject* o = new GameLevelObject_wall({x,y},DOG_COLOR_BLACK);
		//LOGI("setp 3");
		m_objects.push_back(o);
		//LOGI("setp 4");
		second_layer->add_child(o->m_skin);
		//LOGI("Done.");
	}
	LOGI("Readed walls.");

	n = jo["targets"].children.size();
	for(int i=0;i<n;++i){
		int x = jo["targets"][i][0].get_int();
		int y = jo["targets"][i][1].get_int();
		auto o = new GameLevelObject_target({x,y},DOG_COLOR_BLACK);
		m_objects.push_back(o);
		second_layer->add_child(o->m_skin);
	}
	LOGI("Readed targets.");

	n = jo["boxes"].children.size();
	for(int i=0;i<n;++i){
		int x = jo["boxes"][i][0].get_int();
		int y = jo["boxes"][i][1].get_int();
		auto o = new GameLevelObject_box({x,y},DOG_COLOR_BLACK);
		m_objects.push_back(o);
		second_layer->add_child(o->m_skin);
	}
	LOGI("Readed box.");

	int x = jo["spawn_point"][0].get_int();
	int y = jo["spawn_point"][1].get_int();
	auto o = new GameLevelObject_player({x,y},DOG_COLOR_BLACK);
	m_objects.push_back(o);
	player_id = m_objects.size()-1;
	second_layer->add_child(o->m_skin);
	LOGI("Readed spawn_point.");

	LOGI("Level done.");
}

void GameLevel::Release(){
	if(main_layer->get_parent()){
		main_layer->get_parent()->remove_child_by_key("GameLevelMainLayer");
	}
	for(auto &o : m_objects){
		delete o;
		o = 0;
	}
	m_objects.clear();
}