#include "json_object_type.h"


using namespace dog_engine_unit;


typedef long long ll;

ll find_c(string s, ll pos , char c , vector<char> ignor_chars = vector<char>()) {
	for (ll i = pos; i < s.size(); ++i) {
		bool is_continue = false;
		for (int j = 0; j < ignor_chars.size(); ++j) {
			if (s[i] == ignor_chars[j]) {
				is_continue = true;
				break;
			}
		}
		if (is_continue) continue;

		if (c == '\0' || s[i] == c) return i;
	}

	return -1;

}

ll find_r_c(string s, ll pos , char c , vector<char> ignor_chars = vector<char>()) {
	for (ll i = pos - 1; i >= 0; --i) {
		bool is_continue = false;
		for (int j = 0; j < ignor_chars.size(); ++j) {
			if (s[i] == ignor_chars[j]) {
				is_continue = true;
				break;
			}
		}
		if (is_continue) continue;

		if (c == '\0' || s[i] == c) return i;
	}

	return -1;

}

ll find_comp(string s, ll pos, char comp_first, char comp_second) {
	//cout << endl;
	ll p =  1;
	for (ll i = pos; i < s.size(); ++i) {
		//cout << "finding \"" << s[i] << "\" comp_f = " << comp_first << " comp_s = " << comp_second << endl;
		if (s[i] == '\\' && i < s.size() - 1 && s[i + 1] == comp_first)
		{
			i += 1;
			continue;
		}
		if (comp_first == comp_second && s[i] == comp_second) p -= 1;
		else if (s[i] == comp_first) p += 1;
		else if (s[i] == comp_second) p -= 1;

		if (p == 0) return i;
	}

	return -1;
}

ll find_comp(string s, ll pos, char comp_c) {
	char c_s = 0;
	if (comp_c == '{')
		c_s = '}';
	else if (comp_c == '[')
		c_s = ']';
	else if (comp_c == '\"')
		c_s = '\"';
	else if (comp_c == '(')
		c_s = ')';
	else if (comp_c == '<')
		c_s = '>';
	else if (comp_c == '\'')
		c_s = '\'';
	else
		c_s = comp_c;
	//cout<<"we comp this "<<comp_c<<" and "<<c_s<<endl;
	return find_comp(s, pos, comp_c, c_s);
}


string delete_side_blank(string s, vector<char> blank = { ' ', '\n', '\t', '\r' }) {
	int p_1 = find_c(s, 0, '\0', blank);
	int p_2 = find_r_c(s, s.size(), '\0', blank);
	//msg_box(s.substr(p_1, p_2 - p_1) + "! debug 1");
	return s.substr(p_1, p_2 - p_1 + 1);
}



string json_object_type::read_file_all(fstream &f_in) {
	string text;
	char c;
	while ((c = f_in.get()) != EOF) text += c;
	return text;
}

json_object_type json_object_type::phraze(string texts) {
	json_object_type jo;
	texts = delete_side_blank(texts);
	char c_0 = texts[0];
	if (c_0 == '\"' || (c_0 != '{' && c_0 != '[')) {
		jo.text = texts;
	} else {
		string key, text;
		ll base_c = 0;
		while (texts[base_c] != '}' && texts[base_c] != ']') {
			key.clear();
			text.clear();
			if (c_0 == '{') { //object type!
				ll p_1 = find_c(texts, base_c + 1, '\0', { ' ', '\n', '\t', '\r' });
				ll p_2 = find_c(texts, p_1, ':');
				ll p_3 = find_r_c(texts, p_2, '\0', { ' ', '\n', '\t', '\r' });
				//cout<<"p_1 = "<<p_1<<" p_3 = "<<p_3<<"base_c = "<<base_c<<endl;
				key = texts.substr(p_1, p_3 - p_1 + 1);
				base_c = p_2;
			}
			ll p_1 = find_c(texts, base_c + 1, '\0', { ' ', '\n', '\t', '\r' });
			//cout<<"here p_1("<<texts[p_1]<<") = "<<p_1<<endl;
			char c_1 = texts[p_1];
			if (c_1 != '{' && c_1 != '[' && c_1 != '\"') { //text as vallue type!
				ll p_2 = find_c(texts, p_1, ',');
				if (p_2 == -1) p_2 = find_comp(texts, p_1, c_0);
				ll p_3 = find_r_c(texts, p_2, '\0', { ' ', '\n', '\t', '\r' });
				text = texts.substr(p_1, p_3 - p_1 + 1);
				base_c = p_2;
			} else { //object type or array or string type!
				ll p_2 = find_comp(texts, p_1 + 1, c_1);
				//cout<<"here p_2("<<texts[p_2]<<") = "<<p_2<<endl;
				text = texts.substr(p_1, p_2 - p_1 + 1);
				ll p_3 = find_c(texts, p_2 + 1, ',');
				if (p_3 == -1) p_3 = find_comp(texts, p_2 + 1, c_0);
				//cout<<"here p_3 = "<<p_3<<endl;
				base_c = p_3;
			}
			json_object_type jo_c = json_object_type::phraze(text);
			jo_c.key = key;
			jo.children.push_back(jo_c);
		}
	}

	return jo;
}


string json_object_type::json_object_type_to_string(const json_object_type &jo, int d) {
	string s;
	for (int i = 0; i < d; ++i) s += "\t";
	if (jo.key.size()) {
		s += jo.key;
		s += ":";
	}
	if (jo.children.size() == 0)
	{
		s += jo.text;
	} else {
		s += !jo.children[0].key.size() ? '[' : '{';
		if(d != -1) s += '\n';
		for (int j = 0; j < jo.children.size(); ++j)
		{
			s += json_object_type::json_object_type_to_string(jo.children[j], (d == -1 ? d : d + 1));
			if (j <  jo.children.size() - 1) s += ',';
			if(d != -1) s += '\n';
		}
		for (int i = 0; i < d; ++i) s += "\t";
		s += !jo.children[0].key.size() ? ']' : '}';

	}
	return s;
}

string json_object_type::get_key(){
	if(!key.size()) return key;
	if(key.size() >= 2 && key[0] == '\"' && key[key.size()-1] == '\"')
		return key.substr(1,key.size()-2);
	return key;
}
void json_object_type::set_key(string _k){
	if(_k.size()>=2 && _k[0] == '\"' && _k[_k.size()-1] == '\"'){
		key = _k;
	}else{
		key.clear();
		key += '\"';
		key += _k;
		key += '\"';
	}
}

string json_object_type::get_text(){
	return text;
}
void json_object_type::set_text(string _t){
	text = _t;
}

int json_object_type::get_type(){
	if(children.size() == 0){
		if(text.size() >= 2 && text[0] == '\"' && text[text.size()-1] == '\"')
			return 1;
		else
			return 2;
	}else
	{
		if(children[0].key.size() == 0)
			return 4;
		else
			return 3;
	}
	return 0;
}

string json_object_type::get_string(){
	if(get_type() == 1){
		return text.substr(1,text.size()-2);
	}
	return text;
}
int json_object_type::get_int(){
	stringstream ss;
	ss<<text;
	int a;
	ss>>a;
	return a;
}
long long json_object_type::get_long_long(){
	stringstream ss;
	ss<<text;
	long long a;
	ss>>a;
	return a;
}
double json_object_type::get_double(){
	stringstream ss;
	ss<<text;
	double a;
	ss>>a;
	return a;
}
float json_object_type::get_float(){
	stringstream ss;
	ss<<text;
	float a;
	ss>>a;
	return a;
}

void json_object_type::put_string(string v){
	text.clear();
	text += '\"';
	text += v;
	text += '\"';
}
void json_object_type::put_int(int v){
	text.clear();
	stringstream ss;
	ss<<v;
	ss>>text;
}
void json_object_type::put_long_long(long long v){
	text.clear();
	stringstream ss;
	ss<<v;
	ss>>text;
}
void json_object_type::put_double(double v){
	text.clear();
	stringstream ss;
	ss<<v;
	ss>>text;
}
void json_object_type::put_float(float v){
	text.clear();
	stringstream ss;
	ss<<v;
	ss>>text;
}

json_object_type json_object_type::add_object(json_object_type jo){
	children.push_back(jo);
	return *this;
}
json_object_type json_object_type::add_object(string _k,string _v){
	json_object_type a_jo;
	a_jo.set_key(_k);
	a_jo.put_string(_v);
	return add_object(a_jo);
}
json_object_type json_object_type::add_object(string _k,long long _v){
	json_object_type a_jo;
	a_jo.set_key(_k);
	a_jo.put_long_long(_v);
	return add_object(a_jo);
}
json_object_type json_object_type::add_object(string _k,double _v){
	json_object_type a_jo;
	a_jo.set_key(_k);
	a_jo.put_double(_v);
	return add_object(a_jo);
}

json_object_type &json_object_type::at(string _key){
	for(auto &c : children){
		//msg_box((_key + " = user || c = ") + c.get_key());
		if(c.get_key() == _key)
			return c;
	}
	msg_box(_key + "! no such child! [JSON_OBJECT_TYPE]");
	deu_throw(_key + "! no such child!");
}
json_object_type &json_object_type::at(size_t i){
	if(!children.size()) deu_throw("None of child !");
	if(i >= children.size()) deu_throw("Over the children!");
	return children[i];
}
json_object_type &json_object_type::operator[](string _k){
	return at(_k);
}
json_object_type &json_object_type::operator[](size_t _i){
	return at(_i);
}

json_object_type json_object_type::clone(){
	json_object_type jo = *this;
	return jo;
}


json_object_type::json_object_type(){
	key.clear();
	text.clear();
	children.clear();
}

json_object_type::json_object_type(string s){
	*this = json_object_type::phraze(s);
}

json_object_type::json_object_type(string s,string _k){
	*this = json_object_type::phraze(s);
	key = _k;
}