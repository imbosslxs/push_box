#include "GameResource.h"
#include "GameLog.h"

using namespace std;
using namespace push_box;
using namespace dog_engine_unit;

#define LOGI(m) GameLog::Instance()->LogI("GameResource",m)
#define LOGW(m) GameLog::Instance()->LogW("GameResource",m)
#define LOGE(m) GameLog::Instance()->LogE("GameResource",m)

GameResource *GameResource::Instance(){
	static GameResource g;
	return &g;
}

string GameResource::ReadTextFromFile(string path){
	fstream f_in(path,ios::in);
	string s;
	s = json_object_type::read_file_all(f_in);
	f_in.close();
	return s;
}


void GameResource::LoadGameCfgFile(string path){
	fstream f_in(path,ios::in);
	LOGI(string("Loading game cfg file:") + path);
	string fs = json_object_type::read_file_all(f_in);
	f_in.close();
	LOGI("Analyzing...");
	game_cfg = json_object_type::phraze(fs);
	LOGI("Loading completed.");
	//LOGI(json_object_type::json_object_type_to_string(game_cfg,0));

	m_cfg_path = path;
}

void GameResource::SaveGameCfgFile(){
	fstream f_out(m_cfg_path,ios::out | ios::trunc);
	LOGI("Saving game cfg...");
	f_out<<json_object_type::json_object_type_to_string(game_cfg,0);
	LOGI("Done.");
	f_out.close();
}