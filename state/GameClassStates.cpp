#include "GameClassStates.h"
#include "../GameClass.h"
#include "../GameResource.h"
#include "../GameLog.h"
#include "../GameLevel.h"
#include <ctime>

using namespace push_box;
using namespace dog_engine_unit;
using namespace GameClassStates;

#define LOGI(s)(GameLog::Instance()->LogI("GameClassStates",s))
#define LOGW(s)(GameLog::Instance()->LogW("GameClassStates",s))
#define LOGE(s)(GameLog::Instance()->LogE("GameClassStates",s))


//====================GlobleState
GlobleState *GlobleState::Instance(){
	static GlobleState s;
	return &s;
}
void GlobleState::Enter(GameClass* gc){

}
void GlobleState::Excute(GameClass* gc){
	
}
void GlobleState::Exit(GameClass* gc){

}

//====================MainMenuState
MainMenuState *MainMenuState::Instance(){
	static MainMenuState s;
	return &s;
}
void MainMenuState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("main_menu_layer")->set_visible(true);
}
void MainMenuState::Excute(GameClass* gc){
	
}
void MainMenuState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("main_menu_layer")->set_visible(false);
}

//====================StartMenuState
StartMenuState *StartMenuState::Instance(){
	static StartMenuState s;
	return &s;
}
void StartMenuState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("start_menu_layer")->set_visible(true);
}
void StartMenuState::Excute(GameClass* gc){
	
}
void StartMenuState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("start_menu_layer")->set_visible(false);
	LOGI("exit StartMenuState");
}

//====================AboutMenuState
AboutMenuState *AboutMenuState::Instance(){
	static AboutMenuState s;
	return &s;
}
void AboutMenuState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("about_menu_layer")->set_visible(true);
}
void AboutMenuState::Excute(GameClass* gc){
	
}
void AboutMenuState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("about_menu_layer")->set_visible(false);
}

//====================EnterGamingState
EnterGamingState *EnterGamingState::Instance(){
	static EnterGamingState s;
	return &s;
}
void EnterGamingState::Enter(GameClass* gc){
	LOGI("EnterGamingState entering...pre");
	gc->GetMainLayer()->find_child_by_key("title_bct")->set_visible(false);
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->set_visible(true);

	//Load level
	LOGI("EnterGamingState entering...");
	auto start_menu_layer = gc->GetMainLayer()->find_child_by_key("start_menu_layer");
	auto level_selector =(rate_controller*) start_menu_layer->find_child_by_key("level_selector");
	int now_level = level_selector->get_value();
	string level_path = GameResource::Instance()->MakeLeveFilePath(now_level);
	LOGI(string("Loading level file from ")+level_path);
	gc->GetGameLevel()->InitLevelWithFile(level_path);
	LOGI("Load level done.");

	if(start_menu_layer->find_child_by_key("off_button")->is_visible())
		gc->GetGameLevel()->time = -1;

	gc->GetMainLayer()->find_child_by_key("gaming_layer")->add_child(gc->GetGameLevel()->main_layer,"game_level_main_layer");
	auto game_level_main_layer = gc->GetGameLevel()->main_layer;
	LOGI(string("window.w = ") + convert_int_to_string(GameResource::Instance()->GetWindowW()));
	LOGI(string("main_layer.x = ") + convert_int_to_string((GameResource::Instance()->GetWindowW()-game_level_main_layer->get_size().x)/2));
	game_level_main_layer->set_pos({(GameResource::Instance()->GetWindowW()-game_level_main_layer->get_size().x)/2,2});

	LOGI("EnterGamingState done.");
}
void EnterGamingState::Excute(GameClass* gc){
	gc->GetStateMachine()->ChangeState(GamingState::Instance());
}
void EnterGamingState::Exit(GameClass* gc){
	
}

//====================GamingState

//util
string FormatTime(int min,int sec,int msec){
	string ft;
	string min_s = convert_int_to_string(min);
	if(min_s.size() == 1)
		ft += "0";
	ft += min_s;
	ft += ":";
	string sec_s = convert_int_to_string(sec);
	if(sec_s.size() == 1)
		ft += "0";
	ft += sec_s;
	ft += ":";
	string msec_s = convert_int_to_string(msec);
	if(msec_s.size() == 1)
		ft += "0";
	ft += msec_s;
	return ft;
}

bool move_object(GameClass* gc,GameLevelObject* o,int d,int depth = 0){
	if(depth > 2) return false;
	depth += 1;
	auto game_level = gc->GetGameLevel();
	dog_point tartget_pos = o->m_skin->get_pos();
	if(d == 0) {
		tartget_pos.y -= 1;
		if(tartget_pos.y < 0) tartget_pos.y = game_level->size_h-1;
	}else if(d == 1) {
		tartget_pos.y += 1;
		if(tartget_pos.y >= game_level->size_h) tartget_pos.y = 0; 
	}
	else if(d == 2){
		tartget_pos.x -= 1;
		if(tartget_pos.x < 0) tartget_pos.x = game_level->size_w-1;
	}
	else if(d == 3){
		tartget_pos.x += 1;
		if(tartget_pos.x >= game_level->size_w) tartget_pos.x = 0; 
	}
	else return false;
	if(o->type == 0) return false;
	if(o->type == 2) return true;
	
	for(auto &co : game_level->m_objects){
		if(co != o && co->type != 2 && co->m_skin->get_pos() == tartget_pos){
			if(!move_object(gc,co,d,depth+1)){
				return false;
			}else
				break;
		}
	}
	o->m_skin->set_pos(tartget_pos);
	return true;
}

bool win(GameClass *gc){
	auto gl = gc->GetGameLevel();
	bool is_win = true;
	for(auto o : gl->m_objects){
		if(o->type == 2){
			bool is_fit = false;
			for(auto co : gl->m_objects){
				if(co->type == 1 && co->m_skin->get_pos() == o->m_skin->get_pos()){
					is_fit = true;
					break;
				}
			}
			if(!is_fit){
				is_win = false;
				break;
			}
		}
	}
	return is_win;
}
bool lose(GameClass *gc){
	auto gl = gc->GetGameLevel();
	if(gl->time == 0) return true;
	return false;
}
//util
GamingState *GamingState::Instance(){
	static GamingState s;
	return &s;
}
void GamingState::Enter(GameClass* gc){

}
void GamingState::Excute(GameClass* gc){
	static DWORD last_time = 0;
	auto gl = gc->GetGameLevel();
	auto l =(label*) gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("time_remain_label");

	//check if win
	if(win(gc)){
		//msg_box("You WIn!");
		gc->GetStateMachine()->ChangeState(GamingWinState::Instance());
	}
	//check if lose
	if(lose(gc)){
		//msg_box("Time Up!,you lose!");
		gc->GetStateMachine()->ChangeState(GamingLoseState::Instance());
	}

	//time logic
	if(gl->time == -1){//No limit time
		l->set_text("Time Remain: NA:NA:NA");
	}
	//else if(gl->time == 0){//time up ,game over
	//}
	else if(gl->time > 0){//update time
		if(GetTickCount()-last_time>100){
			last_time = GetTickCount();
			gl->time -= 100;
			if(gl->time < 0) gl->time = 0;

			int msec = gl->time % 1000;
			int sec = gl->time / 1000;
			int min = sec / 60;
			sec = sec % 60;

			l->set_text(string("Time Remain: ") + FormatTime(min,sec,(msec/1000.0)*60));
		}
	}

	//level objects logic
	auto &de = director::get_instance().get_dog_engine();
	auto player = gc->GetGameLevel()->m_objects[gc->GetGameLevel()->player_id];
	auto game_level = gc->GetGameLevel();
	if(GetTickCount() - game_level->player_move_speed_ctime > game_level->player_move_speed){
		//game_level->player_move_speed_ctime = GetTickCount();

		bool is_moved = false;
		if(de.get_keyboard_down(VK_W))is_moved=move_object(gc,player,0);
		if(de.get_keyboard_down(VK_S))is_moved=move_object(gc,player,1);
		if(de.get_keyboard_down(VK_A))is_moved=move_object(gc,player,2);
		if(de.get_keyboard_down(VK_D))is_moved=move_object(gc,player,3);
		if(is_moved)game_level->player_move_speed_ctime = GetTickCount();
	}

}
void GamingState::Exit(GameClass* gc){
	
}

//====================GamingWinState
GamingWinState *GamingWinState::Instance(){
	static GamingWinState s;
	return &s;
}
void GamingWinState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("win_menu_layer")->set_visible(true);
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->top_child_by_key("win_menu_layer");
}
void GamingWinState::Excute(GameClass* gc){
	
}
void GamingWinState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("win_menu_layer")->set_visible(false);
}

//====================GamingLoseState
GamingLoseState *GamingLoseState::Instance(){
	static GamingLoseState s;
	return &s;
}
void GamingLoseState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("lose_menu_layer")->set_visible(true);
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->top_child_by_key("lose_menu_layer");
}
void GamingLoseState::Excute(GameClass* gc){
	
}
void GamingLoseState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("lose_menu_layer")->set_visible(false);
}

//====================ExitGamingState
ExitGamingState *ExitGamingState::Instance(){
	static ExitGamingState s;
	return &s;
}
void ExitGamingState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->remove_child_by_key("game_level_main_layer");
	gc->GetGameLevel()->Release();
}
void ExitGamingState::Excute(GameClass* gc){
	gc->GetStateMachine()->ChangeState(MainMenuState::Instance());
}
void ExitGamingState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->set_visible(false);
	gc->GetMainLayer()->find_child_by_key("title_bct")->set_visible(true);
}

//====================RestartGamingState
RestartGamingState *RestartGamingState::Instance(){
	static RestartGamingState s;
	return &s;
}
void RestartGamingState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->remove_child_by_key("game_level_main_layer");
	gc->GetGameLevel()->Release();
}
void RestartGamingState::Excute(GameClass* gc){
	gc->GetStateMachine()->ChangeState(EnterGamingState::Instance());
}
void RestartGamingState::Exit(GameClass* gc){
	
}

//====================PauseGamingState
PauseGamingState *PauseGamingState::Instance(){
	static PauseGamingState s;
	return &s;
}
void PauseGamingState::Enter(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("pause_menu_layer")->set_visible(true);
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->top_child_by_key("pause_menu_layer");
}
void PauseGamingState::Excute(GameClass* gc){
	
}
void PauseGamingState::Exit(GameClass* gc){
	gc->GetMainLayer()->find_child_by_key("gaming_layer")->find_child_by_key("pause_menu_layer")->set_visible(false);
}