#include "bitchar_type.h"

using namespace dog_engine_unit;

bitchar_type::bitchar_type() {
	size = dog_point(0, 0);
}

bitchar_type::bitchar_type(string s) {
	*this = create_from_string(s);
}

bitchar_type bitchar_type::get_cut(dog_point _size) {
	if (size.x == _size.x && size.y == _size.y)
		return *this;

	bitchar_type t_bt;
	t_bt.bc = vector<vector<bit_char> >(_size.x, vector<bit_char>(_size.y));
	t_bt.set_size(_size);
	int o_x = 0, o_y = 0, t_x = 0, t_y = 0;
	while (t_x < _size.x) {
		if (o_x < size.x) {
			o_y = 0;
			t_y = 0;
			while (t_y < _size.y) {
				if (o_y < size.y) {
					t_bt.bc[t_x][t_y] = bc[o_x][o_y];
					o_y += 1;
				}
				//else
				//	break;
				else
					t_bt.bc[t_x][t_y].c = ' ';
				t_y += 1;
			}
			o_x += 1;
		}
		else {
			t_y = 0;
			while (t_y < _size.y) {
				t_bt.bc[t_x][t_y].c = ' ';
				t_y += 1;
			}
		}
		// else
		//	break;
		t_x += 1;
	}

	return t_bt;
}
bitchar_type bitchar_type::get_cut(dog_point _pos,dog_point _size) {
	if (_pos.x == 0 && _pos.y == 0 && size.x == _size.x && size.y == _size.y)
		return *this;

	bitchar_type t_bt;
	t_bt.bc = vector<vector<bit_char> >(_size.x, vector<bit_char>(_size.y));
	t_bt.set_size(_size);
	int o_x = _pos.x, o_y = _pos.y, t_x = 0, t_y = 0;
	while (t_x < _size.x) {
		if (o_x < size.x) {
			o_y = _pos.y;
			t_y = 0;
			while (t_y < _size.y) {
				if (o_y < size.y) {
					t_bt.bc[t_x][t_y] = bc[o_x][o_y];
					o_y += 1;
				}
				//else
				//	break;
				else
					t_bt.bc[t_x][t_y].c = ' ';
				t_y += 1;
			}
			o_x += 1;
		}
		else {
			t_y = 0;
			while (t_y < _size.y) {
				t_bt.bc[t_x][t_y].c = ' ';
				t_y += 1;
			}
		}
		// else
		//	break;
		t_x += 1;
	}

	return t_bt;
}


dog_point bitchar_type::get_size() {
	return size;
}
void bitchar_type::set_size(dog_point _s) {
	size = _s;
}

void bitchar_type::set_color(int color, bool is_front, int x, int y) {
	if (x == -1 || y == -1) {
		for (auto &c1 : bc) {
			for (auto &c2 : c1) {
				if (is_front) c2.f_color = color;
				else c2.b_color = color;
			}
		}
	} else {
		if (is_front) bc[x][y].f_color = color;
		else bc[x][y].b_color = color;
	}
}
int bitchar_type::get_color(bool is_front, int x, int y) {
	if (x == -1 || y == -1) {
		if (is_front) return bc[0][0].f_color;
		return bc[0][0].b_color;
	}
	if (is_front) return bc[x][y].f_color;
	return bc[x][y].b_color;
}


void bitchar_type::draw_bitchar_type(dog_engine &de, dog_point pos, bitchar_type &bt) {
	//de.draw_char('L',{10,0});
	//de.draw_char('X',{11,0});
	auto &bc = bt.bc;
	for (int i = 0; i < bt.size.x; ++i) {
		for (int j = 0; j < bt.size.y; ++j) {
			if (bc[i][j].f_color == -1) de.draw_char(' ', {pos.x + i, pos.y + j}, 0, bc[i][j].b_color == -1, bc[i][j].b_color);
			else de.draw_char(bc[i][j].c, {pos.x + i, pos.y + j}, bc[i][j].f_color, bc[i][j].b_color == -1, bc[i][j].b_color);
		}
	}
}

bitchar_type bitchar_type::create_from_string(string s, bool normal) {
	if (!normal) return create_from_string(s);
	bitchar_type bt;
	int w = 0, h = 0;
	int t_w = 0;
	/*for(int i=0;i<s.size();++i){
		if(s[i] == '\r' ||s[i] == '\t'){
			s.erase(i,i+1);
			--i;
		}
	}*/
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '\n') {
			w = t_w > w ? t_w : w;
			h += 1;
			t_w = 0;
			continue;
		}
		t_w += 1;
	}
	if (s[s.size() - 1] != '\n') {
		w = t_w > w ? t_w : w;
		h += 1;
	}

	//msg_box(string("W:") + w);
	//msg_box(string("H:") + h);
	bt.size = dog_point(w, h);
	bt.bc = vector<vector<bit_char> > (w, vector<bit_char>(h));
	int base_c = 0;
	for (int j = 0; j < h; ++j) {
		for (int i = 0; i < w; ++i) {
			bt.bc[i][j].c = ' ';
			if (base_c < s.size()) {
				if (s[base_c] != '\n') {
					bt.bc[i][j].c = s[base_c];
					++base_c;
				}
			}
		}
		if (s[base_c] == '\n') ++base_c;
	}
	for(auto &c : bt.bc)for(auto &cc: c){
		if(cc.c == '\t' || cc.c == '\r')
			cc.c = ' ';
	}
	return bt;
}

bitchar_type bitchar_type::create_from_file(string path) {
	fstream f_in(path.c_str(), ios::in);
	if (!f_in) deu_throw(string("Erro! None file:") + path);
	string s = json_object_type::read_file_all(f_in);
	f_in.close();

	return bitchar_type::create_from_string(s);
}


bitchar_type bitchar_type::create_from_string(string s) {
	bitchar_type bt;
	auto jo = json_object_type::phraze(s);
	if (jo["version"].get_int() != BCT_VERSION) return bt;
	int w = jo["size"]["W"].get_int();
	int h = jo["size"]["H"].get_int();

	bt.size = dog_point(w, h);

	auto chars = jo["chars"];
	auto f_colors = jo["f_colors"];
	auto b_colors = jo["b_colors"];

	bt.bc = vector<vector<bit_char> >(w, vector<bit_char>(h));

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j) {
			//msg_box(chars[j][i].get_string());
			bt.bc[i][j].c = chars[j][i].get_string()[0];
			bt.bc[i][j].f_color = f_colors[j][i].get_int();
			bt.bc[i][j].b_color = b_colors[j][i].get_int();
		}
	}

	return bt;

}




