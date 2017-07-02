#ifndef _H_DOG_ENGINE_
#define _H_DOG_ENGINE_


#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <functional>
#include <ctime>
#include <sstream>
#include <vector>
#include <utility>
#include <thread>
#include <fstream>
#include <queue>
#include <commctrl.h>
#include "../include/bass.h"



using namespace std;

#define VK_MOUSE_LEFT 1
#define VK_MOUSE_RIGHT 2
#define VK_MOUSE_MIDDLE 4

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4a
#define VK_K 0x4b
#define VK_L 0x4c
#define VK_M 0x4d
#define VK_N 0x4e
#define VK_O 0x4f
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5a

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_TAB 0x09
#define VK_CAPS 0x14
#define VK_ENTER 0x0d
#define VK_BACKSPACE 0x08
#define VK_ESC 0x1b

#define DOG_COLOR_BLACK 0
#define DOG_COLOR_BLUE  1
#define DOG_COLOR_DARK_GREEN  2
#define DOG_COLOR_LIGHT_BLUE 3
#define DOG_COLOR_RED  4
#define DOG_COLOR_PURPLE  5
#define DOG_COLOR_ORANGE  6
#define DOG_COLOR_GREY  7
#define DOG_COLOR_DARKER_GREY  8
#define DOG_COLOR_MEDIUM_BLUE  9
#define DOG_COLOR_LIGHT_GREEN  10
#define DOG_COLOR_TEAL  11
#define DOG_COLOR_RED_ORANGE  12
#define DOG_COLOR_LIGHT_PURPLE  13
#define DOG_COLOR_YELLOW  14
#define DOG_COLOR_WHITE  15

#define DOG_SOCKET_LOCAL_ADDR "127.0.0.1"

#define MAX_MSG_DATA 4096

string operator+(int a,string b);
string operator+(unsigned short a,string b);
string operator+(string b,int a);
string operator+(string b,unsigned short a);
string operator+(char* a,string b);
string operator+(char a,string b);

string convert_int_to_string(int x);
int convert_string_to_int(string x);
int msg_box(string text,string cap = "You Know What",UINT type = 0);
//mode = 1 means pass word mode
string input_box(string text="write me",string title = "Write whatever you like",int *erro=0,DWORD mode=0);
inline DWORD get_time(){
	return clock();
}

//´ËÎªTCPÐ­ÒéµÄsocket
typedef size_t u_ll;
class Dog_client {
		void on_msg_arrived();
	public:
		fstream *log_out;
		SOCKET m_socket;
		SOCKADDR_IN m_addr;
		bool is_end;
		bool start();//×è¶ÏÊ½Á¬½ÓÖÁ·þÎñÆ÷
		bool close();
		bool send_msg(string msg);
		bool send_bytes(vector<char> v_bytes);

		bool log_enable;

		////MASK 2017.1.8
		bool init();
		string get_addr();
		string get_port();
		bool is_connected();
		void enable_log(bool _is);

		function<void(vector<char>)> on_bytes_arrived_listener;
		function<void(string)> on_msg_arrived_listener;
		function<void()> on_close_call_func;
};
//MASK 2017.1.8
unsigned __LONG32 string_to_addr(string addr);
string addr_to_string(unsigned __LONG32 addr);
class Dog_server_client_class{
public:
	SOCKET client_socket;
	SOCKADDR_IN client_addr;
	int client_listener_msg=-1;
	u_ll id=0;
};
class Dog_server {
		void on_loop();
		void on_msg_arrived(u_ll this_id);
		//MASK 2017.1.8
		u_ll cnt_id;
		u_ll get_id();
	public:
		fstream *log_out;

		//MASK 2017.1.8
		//vector<SOCKET> client_sockets;
		//vector<int> client_listeners_msg;//-1ÎªÍË³ö
		vector<Dog_server_client_class> clients;
		u_ll add_client(Dog_server_client_class);
		void remove_client_by_id(u_ll id);
		void remove_all_clients();
		void remove_marked_clients();
		Dog_server_client_class *find_client_by_id(u_ll id);

		SOCKET m_socket;
		SOCKADDR_IN m_addr;
		bool is_end;
		bool log_enable;


		////MASK 2017.1.8
		string get_server_addr();
		string get_server_port();
		string get_client_addr(Dog_server_client_class *);
		string get_client_port(Dog_server_client_class *);
		bool is_started();
		void enable_log(bool _is);

		bool init();

		bool start(int max_client_num=100);//Æô¶¯²¢¼àÌýÖ¸¶¨¶Ë¿Ú
		bool close();
		bool close_client(u_ll id);
		bool send_msg(string msg,u_ll id);

		bool send_bytes(vector<char> v_bytes,u_ll id);



		function<void(u_ll,vector<char>)> on_bytes_arrived_listener;
		function<void(u_ll,string)> on_msg_arrived_listener;


		function<void(u_ll)> on_client_close_call_func;
		function<void()> on_close_call_func;
};
class Dog_socket {
	public:
		fstream log_out;
		bool init();
		void release();

		Dog_client *create_client(unsigned short port,string ip_addr);//´´½¨¿Í»§¶Ë²¢Ö¸¶¨¶Ë¿ÚºÍ·þÎñÆ÷ipµØÖ·

		Dog_server *create_server(unsigned short port,string ip_addr);
		Dog_server *create_server(unsigned short port);
};


class Dog_point {
	public:
		int x,y;
		Dog_point() {
			x=y=0;
		}
		Dog_point(int _x,int _y) {
			x = _x;
			y = _y;
		}
		Dog_point operator+(Dog_point p) {
			return {this->x+p.x,this->y+p.y};
		}
		Dog_point operator-(Dog_point p) {
			return {this->x-p.x,this->y-p.y};
		}
		int operator*(Dog_point p) {
			return this->x * p.x + this->y * p.y;
		}
		
		bool operator==(Dog_point p){
			return this->x == p.x && this->y == p.y;
		}

		Dog_point &operator=(COORD c) {
			this->x = c.X;
			this->y = c.Y;
			return *this;
		}
		COORD to_coord() {
			COORD c;
			c.X = x;
			c.Y = y;
			return c;
		}
};
//Music power by bass
#define _USING_LOG_
class stream_peace {
	public:
		HSTREAM str;
		int key;
		stream_peace():str(0),key(0) {}
		stream_peace(HSTREAM _s,int _k):str(_s),key(_k) {}
};
class Dog_sound_engine {
		void log(string msg,string tag = "INFO");
		int get_key();
	public:
		int key_count;
		vector<stream_peace> strs;
		fstream *log_out;

		void remove_stream(int key);
		void play_stream(int key,bool is_restart = true);
		void stop_stream(int key);
		int load_straem_from_path(string path);

		void set_volume(float v);//0 ~ 1.f
		float get_volume();
		void init(HWND hwnd = 0);
		void release();
};

//Õý¶ù°Ë¾­µÄ  ¹·ÒýÇæ  By Lx
typedef vector<unsigned short> KEY_STATES;
class Dog_Engine {
		void get_input();
	public:
		HANDLE hOut,hIn,hBuf;
		long long last_time,delay_time;
		string title;
		unsigned short key_state[256];

		bool is_end;

		int W,H;

		DWORD bytes=0;
		char *data;
		WORD *data_a;
		long long size;

		bool is_show_fps;

		void init(bool is_double_buf = true);
		void release();

		void set_deley_time(long long dt);

		void set_title(string title);
		string get_title();

		void set_window_size(int w,int h);
		Dog_point get_window_size();

		void set_window_cp(int cp);

		void enable_fps(bool is_enable);
		void set_cursor(bool is_visible,long size=1);

		void end_draw();
		void begin_draw();

		WORD get_color(Dog_point pos,bool is_background = false);
		Dog_point get_center_pos();

		void draw_color(WORD color = DOG_COLOR_GREY);
		void draw_text(string text,Dog_point pos,WORD color_f = DOG_COLOR_BLACK,bool is_alpha = true,WORD color_b = DOG_COLOR_GREY,int mode = 0);
		void draw_rect(Dog_point pos,Dog_point _size,WORD color_b = DOG_COLOR_ORANGE,char c = ' ',WORD color_f = DOG_COLOR_BLACK,int mode = 0);
		void draw_char(char c,Dog_point pos,WORD color_f = DOG_COLOR_BLACK,bool is_alpha = true,WORD color_b = DOG_COLOR_GREY);


		void(*draw)(float,Dog_Engine&) ;

		bool get_keyboard_down(int);
		bool get_keyboard_up(int);
		bool get_mouse_down(int);
		bool get_mouse_up(int);
		Dog_point get_mouse_pos();

		KEY_STATES get_keyboard_down_states();
		KEY_STATES get_keyboard_up_states();



		void update();

};



#endif
