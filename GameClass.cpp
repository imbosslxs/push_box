#include "GameClass.h"
#include "GameResource.h"
#include "GameLog.h"
#include <string>

using namespace dog_engine_unit;
using namespace push_box;
using namespace std;

#define LOGI(s)(GameLog::Instance()->LogI("GameClass",s))
#define LOGW(s)(GameLog::Instance()->LogW("GameClass",s))
#define LOGE(s)(GameLog::Instance()->LogE("GameClass",s))


void GameClass::Init(){
	auto &d = director::get_instance();
	auto &de = d.get_dog_engine();
	auto gr = GameResource::Instance();

	//cfg
	W = gr->GetWindowW();
	H = gr->GetWindowH();
	de.set_window_size(W,H);
	de.set_title(string("Push the Box (version:")+gr->GetGameVersion()+string(")! Powered By Dog Engine"));

	auto sc = scene::create();
	d.begin_scene(sc);

	m_main_layer = layer::create();
	sc->add_child(m_main_layer,"m_main_layer");
	//cfg
	m_main_layer->set_color(DOG_COLOR_WHITE);

	//Create title bct
	auto title_bct = bitchar::create(
		bitchar_type(GameResource::Instance()->ReadTextFromFile(
			GameResource::Instance()->GetGameCfg()["title_bct"]["path"].get_string()
			)),
		{
			GameResource::Instance()->GetGameCfg()["title_bct"]["pos"][0].get_int(),
			GameResource::Instance()->GetGameCfg()["title_bct"]["pos"][1].get_int()
		}
		);
	m_main_layer->add_child(title_bct,"title_bct");
	

	//Create main menu layer
	auto main_menu_layer = layer::create();
	main_menu_layer->set_color(DOG_COLOR_WHITE);
	main_menu_layer->set_pos({0,int(H * (1.0/2.0))});
	m_main_layer->add_child(main_menu_layer,"main_menu_layer");

	auto b = button::create(
								{(W-7)/2,0},
								bitchar_type::create_from_string(" Start ",true),
								bitchar_type::create_from_string(">Start<",true),
								bitchar_type::create_from_string("|Start|",true),
								[&]()->bool{
									//msg_box("I'm a button !");
									m_state_machine->ChangeState(GameClassStates::StartMenuState::Instance());
									return true;
								});
	main_menu_layer->add_child(b);

	b = button::create(
								{(W-7)/2,2},
								bitchar_type::create_from_string(" About ",true),
								bitchar_type::create_from_string(">About<",true),
								bitchar_type::create_from_string("|About|",true),
								[&]()->bool{
									//msg_box("Push Box 0.0.1\nAuther:Raymond.Lx\nE-mail:imbosslx@sina.com\nQQ:415451178");
									m_state_machine->ChangeState(GameClassStates::AboutMenuState::Instance());
									return true;
								});
	main_menu_layer->add_child(b);

	b = button::create(
								{(W-6)/2,4},
								bitchar_type::create_from_string(" Quit ",true),
								bitchar_type::create_from_string(">Quit<",true),
								bitchar_type::create_from_string("|Quit|",true),
								[&]()->bool{
									d.quit();
									return true;
								});
	main_menu_layer->add_child(b);
	main_menu_layer->set_visible(false);

	//Create About menu layer
	auto about_menu_layer = layer::create();
	about_menu_layer->set_color(DOG_COLOR_WHITE);
	about_menu_layer->set_pos({0,int(H * (1.0/2.0))});
	m_main_layer->add_child(about_menu_layer,"about_menu_layer");
	about_menu_layer->set_visible(false);

	auto l = label::create("Push Box",{(W-8)/2,0},DOG_COLOR_BLUE,-1);
	about_menu_layer->add_child(l);
	l = label::create("Push the box,use your magicly magic fingers!",{int(W-string("Push the box,use your magicly magic fingers!").size())/2,2},DOG_COLOR_BLUE,-1);
	about_menu_layer->add_child(l);
	l = label::create(string("version:")+GameResource::Instance()->GetGameVersion(),{int(W-string(string("version:")+GameResource::Instance()->GetGameVersion()).size())/2,4},DOG_COLOR_BLUE,-1);
	about_menu_layer->add_child(l);
	l = label::create("Author: Raymond.Lx",{int(W-string("Author: Raymond.Lx").size())/2,6},DOG_COLOR_BLUE,-1);
	about_menu_layer->add_child(l);
	l = label::create("E-mail: imbosslx@sina.com",{int(W-string("E-mail: imbosslx@sina.com").size())/2,8},DOG_COLOR_BLUE,-1);
	about_menu_layer->add_child(l);
	l = label::create("QQ: 415451178",{int(W-string("QQ: 415451178").size())/2,10},DOG_COLOR_BLUE,-1);
	about_menu_layer->add_child(l);
	b = button::create(
								{(W-6)/2,12},
								bitchar_type::create_from_string(" Back ",true),
								bitchar_type::create_from_string(">Back<",true),
								bitchar_type::create_from_string("|Back|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::MainMenuState::Instance());
									return true;
								});
	about_menu_layer->add_child(b);

	//Create start menu
	auto start_menu_layer = layer::create();
	auto &start_menu_layer_res = *start_menu_layer;
	start_menu_layer->set_color(DOG_COLOR_WHITE);
	start_menu_layer->set_pos({0,int(H * (1.0/2.0))});
	m_main_layer->add_child(start_menu_layer,"start_menu_layer");
	start_menu_layer->set_visible(false);

	l = label::create("Level: ",{(W-5-7)/2,0});
	start_menu_layer->add_child(l);

	auto rc = rate_controller::create({(W-5)/2 + 7,0},GameResource::Instance()->GetNowLevel());
	rc->set_on_value_change_call_func([&](int v,rate_controller& _rc){
		if(_rc.get_value() < 0) _rc.set_value(0);
		else if(_rc.get_value() > GameResource::Instance()->GetMaxLevel())
			_rc.set_value(GameResource::Instance()->GetMaxLevel());
	});
	start_menu_layer->add_child(rc,"level_selector");

	l = label::create("Time limit: ",{(W-3-12)/2,2});
	start_menu_layer->add_child(l);

	auto b_on_bct = bitchar_type::create_from_string("On",true);
	auto b_on_bct_down = b_on_bct;
	b_on_bct_down.set_color(DOG_COLOR_BLUE);
	b = button::create(
								{(W-3-12)/2 + 12,2},
								b_on_bct,
								b_on_bct_down,
								b_on_bct,
								[&]()->bool{
									start_menu_layer_res.find_child_by_key("off_button")->set_visible(true);
									start_menu_layer_res.find_child_by_key("on_button")->set_visible(false);
									return true;
								});
	b->set_visible(false);
	start_menu_layer->add_child(b,"on_button");
	auto b_off_bct = bitchar_type::create_from_string("Off",true);
	auto b_off_bct_down = b_off_bct;
	b_off_bct_down.set_color(DOG_COLOR_RED);
	b = button::create(
								{(W-3-12)/2 + 12,2},
								b_off_bct,
								b_off_bct_down,
								b_off_bct,
								[&]()->bool{
									start_menu_layer_res.find_child_by_key("on_button")->set_visible(true);
									start_menu_layer_res.find_child_by_key("off_button")->set_visible(false);
									return true;
								});
	start_menu_layer->add_child(b,"off_button");

	auto go_button = button::create(
								{(W-5)/2,5},
								bitchar_type::create_from_string(" Go! ",true),
								bitchar_type::create_from_string(">Go!<",true),
								bitchar_type::create_from_string("|Go!|",true),
								[&]()->bool{
									LOGI("Changing state to EnterGamingState...");
									m_state_machine->ChangeState(GameClassStates::EnterGamingState::Instance());
									LOGI("Change to EnterGamingState done.");
									return true;
								});
	start_menu_layer->add_child(go_button);

	b = button::create(
								{(W-6)/2,12},
								bitchar_type::create_from_string(" Back ",true),
								bitchar_type::create_from_string(">Back<",true),
								bitchar_type::create_from_string("|Back|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::MainMenuState::Instance());
									//m_state_machine->ChangeState(GameClassStates::EnterGamingState::Instance());
									return true;
								});
	start_menu_layer->add_child(b);

	//Create gaming layer
	auto gaming_layer = layer::create();
	gaming_layer->set_visible(false);
	m_main_layer->add_child(gaming_layer,"gaming_layer");

	l = label::create("Time Remain: 00:53:42",{(W-21)/2,1});
	gaming_layer->add_child(l,"time_remain_label");

	b = button::create(
								{1,H-2},
								bitchar_type::create_from_string(" Pause ",true),
								bitchar_type::create_from_string(">Pause<",true),
								bitchar_type::create_from_string("|Pause|",true),
								[&]()->bool{
									if(m_state_machine->GetCurrentState() != GameClassStates::GamingState::Instance())
										return true;
									m_state_machine->ChangeState(GameClassStates::PauseGamingState::Instance());
									//msg_box("lala");
									return true;
								});
	gaming_layer->add_child(b);

	//Create win menu layer
	auto win_menu_layer = layer::create();
	win_menu_layer->set_pos({(W-60)/2,(H-20)/2});
	win_menu_layer->set_size({60,20});
	win_menu_layer->set_color(DOG_COLOR_GREY);
	win_menu_layer->set_visible(false);
	gaming_layer->add_child(win_menu_layer,"win_menu_layer");

	l = label::create("Congratulations",{(60-15)/2,1},DOG_COLOR_BLUE,-1);
	win_menu_layer->add_child(l);
	l = label::create("You have won the game!",{(60-22)/2,3},DOG_COLOR_BLUE,-1);
	win_menu_layer->add_child(l);

	b = button::create(
								{(2),15-2},
								bitchar_type::create_from_string(" Main Menu ",true),
								bitchar_type::create_from_string(">Main Menu<",true),
								bitchar_type::create_from_string("|Main Menu|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::ExitGamingState::Instance());
									//msg_box("lala");
									return true;
								});
	win_menu_layer->add_child(b);

	b = button::create(
								{(60-2-9-2),15-2},
								bitchar_type::create_from_string(" Try Again ",true),
								bitchar_type::create_from_string(">Try Again<",true),
								bitchar_type::create_from_string("|Try Again|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::RestartGamingState::Instance());
									//msg_box("lala");
									return true;
								});
	win_menu_layer->add_child(b);

	//Create lose menu layer
	auto lose_menu_layer = layer::create();
	lose_menu_layer->set_pos({(W-60)/2,(H-20)/2});
	lose_menu_layer->set_size({60,20});
	lose_menu_layer->set_color(DOG_COLOR_GREY);
	lose_menu_layer->set_visible(false);
	gaming_layer->add_child(lose_menu_layer,"lose_menu_layer");

	l = label::create("What A Pity",{(60-15)/2,1},DOG_COLOR_RED,-1);
	lose_menu_layer->add_child(l);
	l = label::create("You have lost the game!",{(60-22)/2,3},DOG_COLOR_RED,-1);
	lose_menu_layer->add_child(l);

	b = button::create(
								{(2),15-2},
								bitchar_type::create_from_string(" Main Menu ",true),
								bitchar_type::create_from_string(">Main Menu<",true),
								bitchar_type::create_from_string("|Main Menu|",true),
								[&]()->bool{
									//msg_box("lala");
									m_state_machine->ChangeState(GameClassStates::ExitGamingState::Instance());
									return true;
								});
	lose_menu_layer->add_child(b);

	b = button::create(
								{(60-2-9-2),15-2},
								bitchar_type::create_from_string(" Try Again ",true),
								bitchar_type::create_from_string(">Try Again<",true),
								bitchar_type::create_from_string("|Try Again|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::RestartGamingState::Instance());
									//msg_box("lala");
									return true;
								});
	lose_menu_layer->add_child(b);

	//Create pause menu layer
	auto pause_menu_layer = layer::create();
	pause_menu_layer->set_pos({(W-60)/2,(H-20)/2});
	pause_menu_layer->set_size({60,20});
	pause_menu_layer->set_color(DOG_COLOR_GREY);
	pause_menu_layer->set_visible(false);
	gaming_layer->add_child(pause_menu_layer,"pause_menu_layer");

	l = label::create("Pause!",{(60-15)/2,1},DOG_COLOR_BLUE,-1);
	pause_menu_layer->add_child(l);
	l = label::create("You still have time to win,don't worry.",{(60-39)/2,3},DOG_COLOR_BLUE,-1);
	pause_menu_layer->add_child(l);

	b = button::create(
								{(2),15-2},
								bitchar_type::create_from_string(" Main Menu ",true),
								bitchar_type::create_from_string(">Main Menu<",true),
								bitchar_type::create_from_string("|Main Menu|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::ExitGamingState::Instance());
									//msg_box("lala");
									return true;
								});
	pause_menu_layer->add_child(b);

	b = button::create(
								{(60-10-2)/2,15-2},
								bitchar_type::create_from_string(" Continue ",true),
								bitchar_type::create_from_string(">Continue<",true),
								bitchar_type::create_from_string("|Continue|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::GamingState::Instance());
									//msg_box("lala");
									return true;
								});
	pause_menu_layer->add_child(b);

	b = button::create(
								{(60-2-9-2),15-2},
								bitchar_type::create_from_string(" Try Again ",true),
								bitchar_type::create_from_string(">Try Again<",true),
								bitchar_type::create_from_string("|Try Again|",true),
								[&]()->bool{
									m_state_machine->ChangeState(GameClassStates::RestartGamingState::Instance());
									//msg_box("lala");
									return true;
								});
	pause_menu_layer->add_child(b);


	//Init StateMachine
	m_state_machine = new StateMachine<GameClass>(this);
	m_state_machine->ChangeState(GameClassStates::MainMenuState::Instance());
	m_state_machine->SetGlobleState(GameClassStates::GlobleState::Instance());

}

void GameClass::Update(){
	//Update the StateMachine
	m_state_machine->Update();

}