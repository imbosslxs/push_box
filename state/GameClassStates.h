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

		class StartMenuState : public State<GameClass>{
		public:
			static StartMenuState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			StartMenuState(){}
			~StartMenuState(){}
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

		//Gaming
		class EnterGamingState : public State<GameClass>{
		public:
			static EnterGamingState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			EnterGamingState(){}
			~EnterGamingState(){}
		};
		class GamingState : public State<GameClass>{
		public:
			static GamingState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			GamingState(){}
			~GamingState(){}
		};
		class GamingWinState : public State<GameClass>{
		public:
			static GamingWinState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			GamingWinState(){}
			~GamingWinState(){}
		};
		class GamingLoseState : public State<GameClass>{
		public:
			static GamingLoseState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			GamingLoseState(){}
			~GamingLoseState(){}
		};
		class ExitGamingState : public State<GameClass>{
		public:
			static ExitGamingState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			ExitGamingState(){}
			~ExitGamingState(){}
		};
		class RestartGamingState : public State<GameClass>{
		public:
			static RestartGamingState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			RestartGamingState(){}
			~RestartGamingState(){}
		};
		class PauseGamingState : public State<GameClass>{
		public:
			static PauseGamingState *Instance();

			virtual void Enter(GameClass*);
			virtual void Excute(GameClass*);
			virtual void Exit(GameClass*);

			PauseGamingState(){}
			~PauseGamingState(){}
		};
	}

}



#endif