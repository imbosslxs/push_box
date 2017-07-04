#ifndef _H_GAMELEVEL
#define _H_GAMELEVEL

#include <vector>
#include <string>
#include "dog_engine/dog_engine.h"
#include "dog_engine_unit/dog_engine_unit.h"

namespace push_box{
	class GameLevelObject{
	public:
		int type;
		dog_engine_unit::label *m_skin;
	};
	class GameLevelObject_wall : public GameLevelObject{
	public:
		GameLevelObject_wall(dog_engine_unit::dog_point _pos,int _color){
			type = 0;
			m_skin = dog_engine_unit::label::create("#",_pos,_color,-1);
		}
	};
	class GameLevelObject_box : public GameLevelObject{
	public:
		GameLevelObject_box(dog_engine_unit::dog_point _pos,int _color){
			type = 1;
			m_skin = dog_engine_unit::label::create("@",_pos,_color,-1);
		}
	};
	class GameLevelObject_target : public GameLevelObject{
	public:
		GameLevelObject_target(dog_engine_unit::dog_point _pos,int _color){
			type = 2;
			m_skin = dog_engine_unit::label::create("O",_pos,_color,-1);
		}
	};
	class GameLevelObject_player : public GameLevelObject{
	public:
		GameLevelObject_player(dog_engine_unit::dog_point _pos,int _color){
			type = 3;
			m_skin = dog_engine_unit::label::create("T",_pos,_color,-1);
		}
	};

	class GameLevel{
	public:
		int level;
		int time;
		int size_w,size_h;

		std::vector<GameLevelObject*> m_objects;
		int player_id;
		int player_move_speed;
		int player_move_speed_ctime;

		int main_layer_color,second_layer_color;
		dog_engine_unit::layer *main_layer,*second_layer;
	
		void InitLevelWithFile(std::string path);

		void Release();


		GameLevel(){}
		~GameLevel(){}
	};
}


#endif