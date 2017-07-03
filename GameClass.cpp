#include "GameClass.h"
#include "GameResource.h"
#include <string>

using namespace dog_engine_unit;
using namespace push_box;
using namespace std;

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
									msg_box("I'm a button !");
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


	//Init StateMachine
	m_state_machine = new StateMachine<GameClass>(this);
	m_state_machine->ChangeState(GameClassStates::MainMenuState::Instance());
	m_state_machine->SetGlobleState(GameClassStates::GlobleState::Instance());

}

void GameClass::Update(){
	//Update the StateMachine
	m_state_machine->Update();

}