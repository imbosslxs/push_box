#include "GameLog.h"
#include "dog_engine/dog_engine.h"
#include <ctime>

using namespace std;
using namespace push_box;

GameLog *GameLog::Instance(){
	static GameLog g;
	return &g;
}

void GameLog::Release(){
	if(log_out){
		log_out->close();
		delete log_out;
		log_out = 0;
	}
}
void GameLog::Init(){
	time_t t;
	t = time(&t);
	string formatted_t = string(ctime(&t));
	for(auto &s : formatted_t)
		if(s == ':') s = '_';
		else if(s == ' ') s = '_';
		else if(s == '\n') s = '_';
		else if(s == '\r') s = '_';
	log_out = new fstream(string("./logs/")+formatted_t+string(".log"),ios::out|ios::trunc  );
	//msg_box(string("./logs/")+formatted_t+string(".log"));
}

void GameLog::Log(string tag,string msg,LogType mode){
	switch(mode){
		case LogType::lt_ERROR:
			tag += "[ERROR]";
		case LogType::lt_WORNING:
			tag += "[WORNING]";
		case LogType::lt_INFO:
			tag += "[INFO]";
	}
	tag += "[";
	time_t t;
	t = time(&t);
	string ft = ctime(&t);
	for(auto &s : ft)
		if(s == '\n') s = ' ';
		else if(s == '\r') s = ' ';
	tag += ft;
	tag += "]:";
	(*log_out)<<tag<<endl<<msg<<endl;
}

GameLog::GameLog(){
	log_out = 0;
	Init();
}

GameLog::~GameLog(){
	Release();
}