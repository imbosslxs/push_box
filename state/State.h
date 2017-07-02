#ifndef _H_STATE_
#define _H_STATE_

namespace push_box{

	template<class EntityClass>
	class State{
	public:
		virtual void Enter(EntityClass *)=0;
		virtual void Excute(EntityClass *)=0;
		virtual void Exit(EntityClass *)=0;
		virtual ~State(){}
	};

}

#endif