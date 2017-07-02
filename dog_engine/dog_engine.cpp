#include "dog_engine.h"

string operator+(int a,string b){
	string aa;
	stringstream ss;
	ss<<a;
	ss>>aa;
	return aa += b;
}

string operator+(unsigned short a,string b){
	string aa;
	stringstream ss;
	ss<<a;
	ss>>aa;
	return aa += b;
}

string operator+(string b,int a){
	string aa;
	stringstream ss;
	ss<<a;
	ss>>aa;
	return b + aa;
}

string operator+(string b,unsigned short a){
	string aa;
	stringstream ss;
	ss<<a;
	ss>>aa;
	return b + aa;
}

string operator+(char* a,string b){
	string aa;
	stringstream ss;
	ss<<a;
	ss>>aa;
	return aa + b;
}

string operator+(char a,string b){
	string aa;
	stringstream ss;
	ss<<a;
	ss>>aa;
	return aa += b;
}

int msg_box(string text,string cap,UINT type) {
	return MessageBox(0,text.c_str(),cap.c_str(),type);
}

string convert_int_to_string(int x) {
	stringstream ss;
	ss<<x;
	string a;
	ss>>a;
	return a;
}

int Dconvert_string_to_int(string x) {
	int a=0;
	for(int i=x.size()-1; i>=0; --i) {
		if(x[i] == '-') {
			a *= -1;
			break;
		} else {
			a += (x[i] - '0') * (10*(x.size()-i-1));
		}
	}
	return a;
}

void Dog_Engine::set_deley_time(long long dt) {
	delay_time = dt;
}

string Dog_Engine::get_title() {
	char *ts = new char[1024];
	GetConsoleTitle(ts,1024);
	string a(ts);
	return a;
}

void Dog_Engine::set_title(string t) {
	title = t;
	SetConsoleTitle(t.c_str());
}

void Dog_Engine::enable_fps(bool is_enable) {
	is_show_fps = is_enable;
	if(!is_show_fps)
		set_title(title);
}

KEY_STATES Dog_Engine::get_keyboard_down_states() {
	KEY_STATES ks;
	for(int i=0; i<256; ++i) {
		if(key_state[i] == 1)
			ks.push_back(i);
	}
	return ks;
}

KEY_STATES Dog_Engine::get_keyboard_up_states() {
	KEY_STATES ks;
	for(int i=0; i<256; ++i) {
		if(key_state[i] == 2)
			ks.push_back(i);
	}
	return ks;
}

bool Dog_Engine::get_keyboard_down(int vKey) {
	return key_state[vKey] == 1;
}

bool Dog_Engine::get_keyboard_up(int vKey) {
	return key_state[vKey] == 2;
}

bool Dog_Engine::get_mouse_down(int vKey) {
	return key_state[vKey] == 1;
}

bool Dog_Engine::get_mouse_up(int vKey) {
	return key_state[vKey] == 2;
}



Dog_point Dog_Engine::get_mouse_pos() {
	return {key_state[254],key_state[255]};
}

WORD Dog_Engine::get_color(Dog_point pos,bool is_background) {
	ReadConsoleOutputAttribute(hOut,data_a,1,pos.to_coord(),&bytes);
	return (is_background ? (data_a[0]>>4) : ((data_a[0]<<4)>>4));
}

Dog_point Dog_Engine::get_center_pos() {
	return Dog_point(W/2,H/2);
}

void Dog_Engine::draw_color(WORD color) {
	CONSOLE_SCREEN_BUFFER_INFO csbInfo;
	GetConsoleScreenBufferInfo(hOut, &csbInfo);
	SetConsoleTextAttribute(hOut, ((color<<4) | ((csbInfo.wAttributes<<4)>>4)));
	FillConsoleOutputAttribute(hOut, ((color<<4) | ((csbInfo.wAttributes<<4)>>4)), size, { 0, 0}, &bytes);
	FillConsoleOutputCharacter(hOut, ' ', size, { 0, 0}, &bytes);
}

void Dog_Engine::draw_text(string text,Dog_point pos,WORD color_f,bool is_alpha,WORD color_b,int mode) {
	switch(mode) {
		case 0://裁掉
			if(pos.y >= H)
				break;
			if(is_alpha) {
				for(int i=0; i<text.size(); ++i) {
					if(pos.x + i >= W) break;
					FillConsoleOutputAttribute(hOut, color_f | (get_color(Dog_point(pos.x+i,pos.y),true))<<4, 1, {SHORT(pos.x+i),SHORT(pos.y)}, &bytes);
				}
			} else FillConsoleOutputAttribute(hOut, color_f | color_b<<4, text.size() + pos.x >= W ? W - pos.x : text.size(), pos.to_coord(), &bytes);

			WriteConsoleOutputCharacter(hOut,text.c_str(),text.size() + pos.x >= W ? W - pos.x : text.size(),pos.to_coord(),&bytes);
			break;
		case 1://不裁
			if(pos.y >= H)
				break;
			if(is_alpha) {
				for(int i=0; i<text.size(); ++i) {
					if(pos.x + i >= W) break;
					FillConsoleOutputAttribute(hOut, color_f | (get_color(Dog_point(SHORT(pos.x+i),SHORT(pos.y)),true))<<4, 1, {SHORT(pos.x+i),SHORT(pos.y)}, &bytes);
				}
			} else FillConsoleOutputAttribute(hOut, color_f | color_b<<4, text.size(), pos.to_coord(), &bytes);

			WriteConsoleOutputCharacter(hOut,text.c_str(),text.size(),pos.to_coord(),&bytes);
			break;
	}
}
void Dog_Engine::draw_char(char c,Dog_point pos,WORD color_f,bool is_alpha,WORD color_b) {

		if(pos.y >= H)
			return;
		if(is_alpha) {
			FillConsoleOutputAttribute(hOut, color_f | (get_color(pos,true))<<4, 1, pos.to_coord(), &bytes);
		} else FillConsoleOutputAttribute(hOut, color_f | color_b<<4, 1, pos.to_coord(), &bytes);

		//WriteConsoleOutputCharacter(hOut,text.c_str(),text.size() + pos.x >= W ? W - pos.x : text.size(),pos.to_coord(),&bytes);
		FillConsoleOutputCharacter(hOut, c, 1, pos.to_coord(), &bytes);
}

void Dog_Engine::draw_rect(Dog_point pos,Dog_point _size,WORD color_b,char c,WORD color_f,int mode) {
	switch(mode) {
		case 0:
			for(int i=pos.y; i<pos.y+_size.y; ++i) {
				FillConsoleOutputAttribute(hOut, color_f | color_b<<4, _size.x, { SHORT(pos.x), SHORT(i)}, &bytes);
				FillConsoleOutputCharacter(hOut, c, _size.x, { SHORT(pos.x), SHORT(i)}, &bytes);
			}

			break;
	}
}

void Dog_Engine::set_window_cp(int cp){
	SetConsoleOutputCP(cp);
}

void Dog_Engine::set_window_size(int w,int h){
	SMALL_RECT rc = {0,0,0,0};
	SetConsoleWindowInfo(hOut,true,&rc);
	SetConsoleWindowInfo(hBuf,true,&rc);

	SetConsoleScreenBufferSize(hOut,Dog_point(w,h).to_coord());
	SetConsoleScreenBufferSize(hBuf,Dog_point(w,h).to_coord());

	rc = {0,0,SHORT(w-1),SHORT(h-1)};
	SetConsoleWindowInfo(hOut,true,&rc);
	SetConsoleWindowInfo(hBuf,true,&rc);

	size = w * h;
	W = w;
	H = h;
	delete []data;
	delete []data_a;
	data = new char[size];
	data_a = new WORD[size];
}
Dog_point Dog_Engine::get_window_size(){
	return Dog_point(W,H);
}

void Dog_Engine::init(bool is_double_buf) {
	delay_time = 1000/60;
	//获取默认标准显示缓冲区句柄
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口缓冲区信息
	GetConsoleScreenBufferInfo( hOut, &bInfo ); // 获取窗口缓冲区信息
	size = bInfo.dwSize.X * bInfo.dwSize.Y;
	W = bInfo.srWindow.Right;
	H = bInfo.srWindow.Bottom;
	data = new char[size];
	data_a = new WORD[size];

	//创建新的缓冲区
	hBuf = CreateConsoleScreenBuffer(
	           GENERIC_READ | GENERIC_WRITE,
	           FILE_SHARE_READ | FILE_SHARE_WRITE,
	           NULL,
	           CONSOLE_TEXTMODE_BUFFER,
	           NULL
	       );


	//设置新的缓冲区为活动显示缓冲
	if(is_double_buf) SetConsoleActiveScreenBuffer(hBuf);
	hIn = GetStdHandle(STD_INPUT_HANDLE);

	set_cursor(false);

	set_title("Dog_Engine Demo");

	draw = 0;
	is_show_fps = false;
	last_time = 0;
	for(int i=0; i<256; ++i) {
		key_state[i] = 0;

	}

	is_end = false;
	//启动获取输入线程
	thread input_thread(&Dog_Engine::get_input,this);
	input_thread.detach();

}

void Dog_Engine::release() {
	is_end = true;
	delete[] data;
	delete[] data_a;
	data = 0;
	data_a = 0;
	CloseHandle(hOut);
	CloseHandle(hBuf);
	CloseHandle(hIn);
}

void Dog_Engine::set_cursor(bool is_visible,long size) {
	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible=is_visible;
	cci.dwSize=size;
	SetConsoleCursorInfo(hOut, &cci);
	SetConsoleCursorInfo(hBuf, &cci);
}

void Dog_Engine::get_input() {
	INPUT_RECORD mouseRec;
	DWORD res;
	while(!is_end) {

		//get input
		for(int i=0; i<256; ++i) {
			if(GetAsyncKeyState(i) & 0x8000) {
				key_state[i] = 1;
			} else if(key_state[i] == 1) {
				key_state[i] = 2;
			} else if(key_state[i] == 2) {
				key_state[i] = 0;
			}
		}

		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		if (mouseRec.EventType == MOUSE_EVENT) {
			auto pos = mouseRec.Event.MouseEvent.dwMousePosition;
			key_state[254] = pos.X;
			key_state[255] = pos.Y;
		}
	}
}

void Dog_Engine::update() {
	SMALL_RECT rc = {0,0,SHORT(W-1),SHORT(H-1)};
	SetConsoleWindowInfo(hOut,true,&rc);
	SetConsoleWindowInfo(hBuf,true,&rc);
	long long dt = clock() - last_time;
	stringstream ss;
	if(dt >= delay_time) {
		last_time = clock();
		begin_draw();
		if(is_show_fps) {
			string st;
			ss.clear();
			ss<<(int)(1000/float(dt));
			ss>>st;
			string a = title;
			a += " [fps:";
			a += st;
			a += "]";
			SetConsoleTitle(a.c_str());
		}
		if(draw)
			draw(dt > 0 ? 1/float(dt) : 0,*this);
		end_draw();
	}


}

void Dog_Engine::begin_draw() {
	//system("cls");
	//FillConsoleOutputCharacter(hOut,' ', size, {0,0}, &bytes);
	draw_color();

}

void Dog_Engine::end_draw() {

	ReadConsoleOutputAttribute(hOut,data_a,size, {0,0},&bytes);
	ReadConsoleOutputCharacterA(hOut, data, size, {0,0}, &bytes);
	WriteConsoleOutputAttribute(hBuf,data_a,size, {0,0},&bytes);
	WriteConsoleOutputCharacterA(hBuf, data, size, {0,0}, &bytes);

}


//==============================Dog_socket 简单tcp协议网络通信============================================


bool Dog_socket::init() {
	log_out.open("dog_engine_socket.log",ios::out | ios::trunc);
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)) {
		log_out<<"初始化winsocket环境错误!"<<endl;
	} else {
		log_out<<"成功初始化winsocket环境"<<endl;
	}
}

void Dog_socket::release() {
	WSACleanup();
	log_out<<"清理winsocket环境成功"<<endl;
}

Dog_server *Dog_socket::create_server(unsigned short port,string ip_addr) {
	Dog_server *s = new Dog_server;
	s->m_socket = socket(AF_INET,SOCK_STREAM,0);

	s->m_addr.sin_port = htons(port);
	s->m_addr.sin_addr.S_un.S_addr = inet_addr(ip_addr.c_str());
	s->m_addr.sin_family = AF_INET;

	bind(s->m_socket,(SOCKADDR*)&s->m_addr,sizeof(SOCKADDR));

	s->log_out = &log_out;
	log_out<<"创建一个服务器成功!"<<endl;
	return s;
}

Dog_client *Dog_socket::create_client(unsigned short port,string ip_addr) {
	Dog_client *s = new Dog_client;
	s->m_socket = socket(AF_INET,SOCK_STREAM,0);

	s->m_addr.sin_port = htons(port);
	s->m_addr.sin_addr.S_un.S_addr = inet_addr(ip_addr.c_str());
	s->m_addr.sin_family = AF_INET;

	s->log_out = &log_out;
	log_out<<"成功创建一个客户端"<<endl;
	return s;
}

//dog client
bool Dog_client::is_connected(){
	return !is_end;
}
void Dog_client::enable_log(bool _is){
	log_enable = _is;
}
string Dog_client::get_addr(){
	return string(inet_ntoa(m_addr.sin_addr));
}
string Dog_client::get_port(){
	return convert_int_to_string(int(m_addr.sin_port));
}

bool Dog_client::init(){
	log_enable = true;
	return true;
}

bool Dog_client::start() {
	if(log_enable)(*log_out)<<"正在连接目标服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")"<<endl;
	connect(m_socket,(SOCKADDR*)&(m_addr),sizeof(SOCKADDR));//开始连接
	thread on_msg_arrived_thread(on_msg_arrived,this);
	on_msg_arrived_thread.detach();
	is_end = false;
	if(log_enable)(*log_out)<<"连接服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")成功，并开启新线程监听服务器发来的消息"<<endl;
	return true;
}

bool Dog_client::send_msg(string msg) {
	if(log_enable)(*log_out)<<"正在向服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")发送消息:"<<endl<<msg<<endl;
	send(m_socket,msg.c_str(),msg.size(),0);
	return true;
}
bool Dog_client::send_bytes(vector<char> v_bytes) {
	auto a_msg = new char[v_bytes.size()];
	for(size_t i=0;i<v_bytes.size();++i)
		a_msg[i] = v_bytes[i];
	send(m_socket,a_msg,v_bytes.size(),0);
	if(log_enable)(*log_out)<<"正在向服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")发送消息:"<<endl<<a_msg<<endl;
	delete[] a_msg;
	return true;
}

void Dog_client::on_msg_arrived() {
	char receiveBuf[MAX_MSG_DATA];//接收
	while(!is_end) {
		for(u_ll i=0;i<MAX_MSG_DATA;++i)
			receiveBuf[i] = 0;
		int result = recv(m_socket,receiveBuf,sizeof(receiveBuf),0);
		if(result == 0) {
			if(log_enable)(*log_out)<<"与服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")的连接中断!"<<endl;
			close();
			break;
		} else if(result == SOCKET_ERROR) {
			if(log_enable)(*log_out)<<"与服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")连接发生错误，将关闭客户端"<<endl;
			close();
			break;
		}
		if(log_enable)(*log_out)<<"收到服务器("<<inet_ntoa(m_addr.sin_addr)<<":"<<m_addr.sin_port<<")的消息:"<<endl<<receiveBuf<<endl;
		if(on_msg_arrived_listener) on_msg_arrived_listener(string(receiveBuf));
		if(on_bytes_arrived_listener) {
			vector<char> v_bytes(MAX_MSG_DATA);
			for(size_t i=0;i<v_bytes.size();++i){
				v_bytes[i] = receiveBuf[i];
			}
			on_bytes_arrived_listener(v_bytes);
		}
	}
}

bool Dog_client::close() {
	is_end = true;
	closesocket(m_socket);
	if(on_close_call_func) on_close_call_func();
	if(log_enable)(*log_out)<<"关闭客户端成功"<<endl;
	return true;
}

Dog_server *Dog_socket::create_server(unsigned short port) {
	SOCKADDR_IN addr;
	addr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	return create_server(port,inet_ntoa(addr.sin_addr));
}

//Dog_server
u_ll Dog_server::get_id(){
	return cnt_id++;
}
u_ll Dog_server::add_client(Dog_server_client_class dscc){
	dscc.id = get_id();
	dscc.client_listener_msg = 0;
	clients.push_back(dscc);
	return dscc.id;
}
void Dog_server::remove_client_by_id(u_ll id){
	for(long long i=0;i<clients.size();++i){
		if(clients[i].id == id){
			clients.erase(clients.begin()+i,clients.begin()+i+1);
			break;
		}
	}
}
void Dog_server::remove_all_clients(){
	clients.clear();
}
void Dog_server::remove_marked_clients(){
	for(long long i=0;i<clients.size();++i){
		if(clients[i].client_listener_msg == -1)
		{
			clients.erase(clients.begin()+i,clients.begin()+i+1);
			--i;
		}
	}
}
Dog_server_client_class *Dog_server::find_client_by_id(u_ll id){
	for(auto &c:clients){
		if(c.id == id)
			return &c;
	}
	return 0;
}
bool Dog_server::is_started(){
	return !is_end;
}
void Dog_server::enable_log(bool _is){
	log_enable = _is;
}

bool Dog_server::init(){
	cnt_id = 1;
	log_enable = true;
	return true;
}

bool Dog_server::start(int max_client_num) {
	listen(m_socket,max_client_num);
	is_end = false;


	thread on_loop_thread(Dog_server::on_loop,this);
	on_loop_thread.detach();
	if(log_enable) (*log_out)<<"服务器监听成功,开始新线程等待客户端的连接"<<endl;
	return true;
}
//MASK 2017.1.8

bool Dog_server::send_msg(string msg,u_ll id) {
	if(!is_started()) return false;
	auto c = find_client_by_id(id);
	if(!c) return false;
	if(log_enable) (*log_out)<<"正在向客户端("<<get_client_addr(c)<<":"<<get_client_port(c)<<")发送消息:"<<endl<<msg<<endl;
	send(c->client_socket,msg.c_str(),msg.size(),0);
	return true;
}
bool Dog_server::send_bytes(vector<char>v_bytes,u_ll id){
	if(!is_started()) return false;
	auto c = find_client_by_id(id);
	if(!c) return false;
	auto a_msg = new char[v_bytes.size()];
	for(size_t i=0;i<v_bytes.size();++i)
		a_msg[i] = v_bytes[i];
	send(c->client_socket,a_msg,v_bytes.size(),0);
	if(log_enable) (*log_out)<<"正在向客户端("<<get_client_addr(c)<<":"<<get_client_port(c)<<")发送消息:"<<endl<<a_msg<<endl;
	delete[] a_msg;
	return true;
}
//MASK 2017.1.8
void Dog_server::on_msg_arrived(u_ll this_id) {
	char receiveBuf[MAX_MSG_DATA];//接收
	auto c = find_client_by_id(this_id);
	if(!c) return;
	while(c->client_listener_msg != -1) {
		for(u_ll i=0;i<MAX_MSG_DATA;++i)
			receiveBuf[i] = 0;
		int result = recv(c->client_socket,receiveBuf,sizeof(receiveBuf),0);
		if(result == 0) {
			if(log_enable)(*log_out)<<"与客户端("<<get_client_addr(c)<<":"<<get_client_port(c)<<")的连接中断!"<<endl;
			c->client_listener_msg = -1;
			break;
		} else if(result == SOCKET_ERROR) {
			if(log_enable)(*log_out)<<"与客户端("<<get_client_addr(c)<<":"<<get_client_port(c)<<")的连接发生错误，将与其中断连接!"<<endl;
			c->client_listener_msg = -1;
			break;
		}
		if(log_enable)(*log_out)<<"收到客户端("<<get_client_addr(c)<<":"<<get_client_port(c)<<")的消息:"<<endl<<receiveBuf<<endl;
		if(on_msg_arrived_listener) on_msg_arrived_listener(this_id,string(receiveBuf));
		if(on_bytes_arrived_listener) {
			vector<char> v_bytes(MAX_MSG_DATA);
			for(size_t i=0;i<v_bytes.size();++i){
				v_bytes[i] = receiveBuf[i];
			}
			on_bytes_arrived_listener(this_id,v_bytes);
		}
	}
	closesocket(c->client_socket);
	if(on_client_close_call_func) on_client_close_call_func(this_id);
	remove_client_by_id(this_id);
	if(log_enable)(*log_out)<<"与客户端("<<get_client_addr(c)<<":"<<get_client_port(c)<<")断开连接成功"<<endl;
}
//MASK 2017.1.8
void Dog_server::on_loop() {
	while(!is_end) {
		SOCKADDR_IN clientsocket;
		if(log_enable)(*log_out)<<"服务器正在监听客户端中..."<<endl;
		int len=sizeof(SOCKADDR);
		//wait for the clients
		SOCKET serConn=accept(m_socket,(SOCKADDR*)&clientsocket,&len);
		//client_sockets.push_back(serConn);
		//client_listeners_msg.push_back(0);
		Dog_server_client_class dscc;
		dscc.client_socket = serConn;
		dscc.client_addr = clientsocket;
		u_ll dscc_id = add_client(dscc);
		if(log_enable)(*log_out)<<"客户端("<<inet_ntoa(clientsocket.sin_addr)<<":"<<clientsocket.sin_port<<")连接成功！"<<endl;
		//启动信息监听
		thread msg_thread(on_msg_arrived,this,dscc_id);
		msg_thread.detach();
	}
}

string Dog_server::get_server_addr(){
	return string(inet_ntoa(m_addr.sin_addr));
}
string Dog_server::get_server_port(){
	return convert_int_to_string(int(m_addr.sin_port));
}
string Dog_server::get_client_addr(Dog_server_client_class *dscc){
	if(!dscc) return string();
	return string(inet_ntoa(dscc->client_addr.sin_addr));
}
string Dog_server::get_client_port(Dog_server_client_class *dscc){
	if(!dscc) return string();
	return convert_int_to_string(int(dscc->client_addr.sin_port));
}

bool Dog_server::close() {
	is_end = true;
	//remove_all_clients();
	for(auto &c:clients){
		//c.client_listener_msg = -1;
		closesocket(c.client_socket);
	}
	remove_all_clients();
	closesocket(m_socket);
	if(on_close_call_func) on_close_call_func();
	if(log_enable)(*log_out)<<"已关闭服务器"<<endl;
	return true;
}

bool Dog_server::close_client(u_ll id) {
	//client_listeners_msg[id] = -1;
	auto c = find_client_by_id(id);
	if(!c) return false;
	c->client_listener_msg = -1;
	return true;
}
//end dog server

unsigned __LONG32 string_to_addr(string addr) {
	return inet_addr(addr.c_str());
}

string addr_to_string(unsigned __LONG32 addr) {
	SOCKADDR_IN addr1;
	addr1.sin_addr.S_un.S_addr=addr;
	return string(inet_ntoa(addr1.sin_addr));
}

//============Dog sound engine ======================================
void Dog_sound_engine::log(string msg,string tag){
	if(log_out)
	{
		#ifdef _USING_LOG_
		(*log_out)<<"["<<tag<<"](time:"<<time(0)<<"):"<<msg<<endl;
		#endif
	}
}
int Dog_sound_engine::get_key(){
	return key_count++;
}
void Dog_sound_engine::init(HWND hwnd) {
	#ifdef _USING_LOG_
	log_out = new fstream("DOG_SOUND_ENGINE.log",ios::out | ios::trunc);
	#endif
	if (!BASS_Init(-1,44100,0,hwnd,NULL))
		log("Can't initialize device",string("ERRO|") + BASS_ErrorGetCode());
	log("Init bass successfully!");
	key_count = 0;
}

int Dog_sound_engine::load_straem_from_path(string path){
	auto path_c = new wchar_t[path.size()];
	swprintf(path_c,L"%s",path.c_str());
	auto str = BASS_StreamCreateFile(FALSE,path_c,0,0,0);
	if(str)
	{
		strs.push_back({str,get_key()});
		log(string("Load stream file(") + path + ") successfully!");
		return strs[strs.size()-1].key;
	}else{
		log(string("Load stream file(") + path + ") fails!",string("ERRO|") + BASS_ErrorGetCode());
		return -1;
	} 
	return -1;
}
void Dog_sound_engine::remove_stream(int key){
	for(auto i = strs.begin();i != strs.end();++i)
	{
		if(i->key == key)
		{
			BASS_StreamFree(i->str);
			strs.erase(i,i+1);
			--i;
			break;
		}
	}
}
void Dog_sound_engine::play_stream(int key,bool is_restart)
{
	for(auto c:strs)if(c.key == key) BASS_ChannelPlay(c.str,is_restart);
} 
void Dog_sound_engine::stop_stream(int key){
	for(auto c:strs)if(c.key == key) BASS_ChannelStop(c.str);
}

void Dog_sound_engine::set_volume(float v){
	BASS_SetVolume(v);
}

float Dog_sound_engine::get_volume(){
	return BASS_GetVolume();
}

void Dog_sound_engine::release(){
	
	BASS_Free();
}


//==========input_box============================
string ib_text;
bool is_ib_ok = false;
HWND ib_hwnd = 0,ib_edit = 0;

LRESULT CALLBACK ib_proc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam){
	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
			EndPaint(hwnd,&ps);
			break;
		}
		case WM_CREATE:
		{
			break;
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam)){
				case 8801:
					//PostQuitMessage(0);
					char cs[20480];
					GetWindowTextA(ib_edit,cs,20480);
					ib_text = cs;
					DestroyWindow(ib_hwnd);
					break;
				case 8802:
					//PostQuitMessage(0);
					DestroyWindow(ib_hwnd);
					break;
			}
			break;
		}
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

string input_box(string text,string title ,int *erro,DWORD mode){
	ib_text = text;


	//create a window
	WNDCLASS wc = { };

	wc.lpfnWndProc = ib_proc;
	wc.hInstance = 0;
	wc.lpszClassName = "ib_box";
	RegisterClass(&wc);

	HWND hwnd = CreateWindow(
								
								"ib_box",
								title.c_str(),
								WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
								CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
								0,
								0,
								0,
								0
								);

	ib_hwnd = hwnd;

	HWND b1 = CreateWindow("Button","OK",WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,0,250,60,20,hwnd,(HMENU)8801,0,0);
	HWND b2 = CreateWindow("Button","Nope!",WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,300,250,60,20,hwnd,(HMENU)8802,0,0);
	ib_edit = (mode == 1 ? CreateWindow("edit",text.c_str(),WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_PASSWORD,0,0,400,250,hwnd,0,0,0) : CreateWindow("edit",text.c_str(),WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,0,0,400,250,hwnd,0,0,0));
	ShowWindow(hwnd,SW_SHOW);

	MSG msg = { };
	while(GetMessage(&msg,0,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if(erro) *erro = is_ib_ok;
	return ib_text;
}






//===============================================

