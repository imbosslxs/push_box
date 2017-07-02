#include "GameClassStates.h"
#include "../GameClass.h"

using namespace push_box;
using namespace dog_engine_unit;
using namespace GameClassStates;

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