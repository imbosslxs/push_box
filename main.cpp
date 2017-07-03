#include "GameClass.h"
#include "GameLog.h"
#include "GameResource.h"

using namespace std;
using namespace dog_engine_unit;
using namespace push_box;

GameClass gc;

void Update(){
	gc.Update();
}

int deu_main(int argc,char **argv){
	//GameLog::Instance()->Init();
	//GameLog::Instance()->LogI("main","Yeah!");

	//Load GameCfg file first
	GameResource::Instance()->LoadGameCfgFile("res/game_cfg.json");
	
	//Init GameClass
	gc.Init();

	//Add a Every time scheduler
	director::get_instance().add_task(0,Update);

	return 0;
}