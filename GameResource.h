#ifndef _H_GAMERESOURCE_
#define _H_GAMERESOURCE_

#include <string>
#include "dog_engine_unit/json_object_type/json_object_type.h"

namespace push_box{

	class GameResource{
		dog_engine_unit::json_object_type game_cfg;
		std::string m_cfg_path;
	public:
		static GameResource* Instance();

		void LoadGameCfgFile(std::string cfg_path);
		dog_engine_unit::json_object_type GetGameCfg(){return game_cfg;}
		std::string GetGameVersion(){return game_cfg["version"].get_string();}
		int GetWindowW(){return game_cfg["window_size"][0].get_int();}
		int GetWindowH(){return game_cfg["window_size"][1].get_int();}

		std::string ReadTextFromFile(std::string path);

		void SaveGameCfgFile();

		GameResource(){}
		~GameResource(){}
	};

}



#endif