#ifndef _H_GAMECLASSSTATES_
#define _H_GAMECLASSSTATES_

#include "State.h"


namespace push_box{
	class GameClass;

	namespace GameClassStates{
		class GlobleState : public State<GameClass>{
		public:
			static GlobleState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			GlobleState(){}
			~GlobleState(){}
		};

		class MainMenuState : public State<GameClass>{
		public:
			static MainMenuState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			MainMenuState(){}
			~MainMenuState(){}
		};

		class AboutMenuState : public State<GameClass>{
		public:
			static AboutMenuState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			AboutMenuState(){}
			~AboutMenuState(){}
		};
	}

}



#endif