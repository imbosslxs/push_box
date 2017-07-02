#ifndef _H_STATEMACHINE_
#define _H_STATEMACHINE_

#include "State.h"
#include <typeinfo>

namespace push_box {
template<class EntityClass>
class StateMachine {
	State<EntityClass> *m_current_state;
	State<EntityClass> *m_previou_state;
	State<EntityClass> *m_globle_state;

	EntityClass *m_owner;

	StateMachine() {}
public:
	StateMachine(EntityClass* owner):
		m_owner(owner),
		m_current_state(0),
		m_previou_state(0),
		m_globle_state(0) {}

	void ChangeState(State<EntityClass> * new_state) {
		if (m_current_state) m_current_state->Exit(m_owner);
		m_previou_state = m_current_state;
		m_current_state = new_state;
		if (m_current_state) m_current_state->Enter(m_owner);
		if (m_globle_state) m_globle_state->Enter(m_owner);
	}
	void RevertState() {
		ChangeState(m_previou_state);
	}
	void Update() {
		if (m_current_state) m_current_state->Excute(m_owner);
		if (m_globle_state) m_globle_state->Excute(m_owner);
	}

	void SetCurrentState(State<EntityClass> *st) {m_current_state = st;}
	void SetGlobleState(State<EntityClass> *st) {m_globle_state = st;}

	State<EntityClass> *GetCurrentState() {return m_current_state;}
	State<EntityClass> *GetPreviouState() {return m_previou_state;}
	State<EntityClass> *GetGlobleState() {return m_globle_state;}

	bool IsSameState(State<EntityClass> *st){
		return typeid(st) == typeid(m_current_state);
	}

	~StateMachine() {}
};
}


#endif