#include "GameClass.h"

using namespace dog_engine_unit;
using namespace push_box;

void GameClass::Init(){
	auto &d = director::get_instance();
	auto &de = d.get_dog_engine();

	//cfg
	W = 100;
	H = 30;
	de.set_window_size(W,H);
	de.set_title("Push the Box! Powered By Dog Engine");

	auto sc = scene::create();
	d.begin_scene(sc);

	m_main_layer = layer::create();
	sc->add_child(m_main_layer,"m_main_layer");
	//cfg
	m_main_layer->set_color(DOG_COLOR_WHITE);
	

	//Create main menu layer
	auto main_menu_layer = layer::create();
	main_menu_layer->set_color(DOG_COLOR_WHITE);\
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
									msg_box("Push Box 0.0.1\nAuther:Raymond.Lx\nE-mail:imbosslx@sina.com\nQQ:415451178");
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



	//Init StateMachine
	m_state_machine = new StateMachine<GameClass>(this);
	m_state_machine->ChangeState(GameClassStates::MainMenuState::Instance());
	m_state_machine->SetGlobleState(GameClassStates::GlobleState::Instance());

}

void GameClass::Update(){
	//Update the StateMachine
	/*msg_box(string("we got 2:")+convert_int_to_string(int(GameClassStates::GlobleState::Instance())));
	msg_box(string("we got 3:")+convert_int_to_string(int(this->m_state_machine->GetGlobleState())));
	msg_box(string("we got 1.2:")+convert_int_to_string(int(this->m_state_machine)));
	msg_box(string("we got 1.3:")+convert_int_to_string(int(this)));*/
	m_state_machine->Update();
	//if(GameClassStates::GlobleState::Instance() != m_state_machine->GetGlobleState())
	//	msg_box("oops!");

}