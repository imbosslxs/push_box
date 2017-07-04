#ifndef _H_GAMECLASS_
#define _H_GAMECLASS_

#include "dog_engine_unit/dog_engine_unit.h"
#include "state/StateMachine.h"
#include "state/GameClassStates.h"
#include "GameLevel.h"

namespace push_box{
	class GameClass{
		dog_engine_unit::layer *m_main_layer;

		StateMachine<GameClass> *m_state_machine;

		GameLevel m_game_level;

		int W,H;
	public:
		GameClass():m_main_layer(0),
					m_state_machine(0){}
		~GameClass(){}

		void Init();

		void Update();

		int GetWindowW(){return W;}
		int GetWindowH(){return H;}

		GameLevel *GetGameLevel(){return &m_game_level;}
		StateMachine<GameClass> *GetStateMachine(){return m_state_machine;}
		dog_engine_unit::layer *GetMainLayer(){return m_main_layer;}
	};
}


#endif