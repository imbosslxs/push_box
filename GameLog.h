#ifndef _H_GAMELOG_
#define _H_GAMELOG_

#include <fstream>
#include <string>

namespace push_box{

	class GameLog{
		std::fstream *log_out;
	public:
		static GameLog* Instance();

		void Init();
		void Release();

		enum LogType{
			lt_ERROR = 0,
			lt_WORNING,
			lt_INFO
		};

		void LogE(std::string Tag,std::string Msg){Log(Tag,Msg,LogType::lt_ERROR);}
		void LogW(std::string Tag,std::string Msg){Log(Tag,Msg,LogType::lt_WORNING);}
		void LogI(std::string Tag,std::string Msg){Log(Tag,Msg,LogType::lt_INFO);}
		void Log(std::string Tag,std::string Msg,LogType mod);

		GameLog();
		~GameLog();
	};
}



#endif