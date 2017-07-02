#include "node.h"

using namespace dog_engine_unit;

node* node::create(dog_point _pos,string _key){
	auto n = new node();
	/*n->pos = _pos;
	n->key = _key;
	n->on_event_call_func = 0;
	n->parent = 0;*/
	n->init();
	n->set_pos(_pos);
	n->set_key(_key);
	return n;
}

void node::init(){
	set_pos({0,0});
	set_key(string());
	set_on_event_call_func(0);
	set_parent(0);
	set_visible(true);
	is_release = false;
}

node* node::create(dog_point _pos){
	return node::create(_pos,string());
}

node* node::create(){
	return node::create({0,0});
}

void node::add_child(node *_n){
	//_n->parent = this;
	_n->set_parent(this);
	_n->set_dog_engine(p_de);
	_n->is_release = false;
	children.push_back(_n);
}

void node::add_child(node *_n,string _key){
	_n->set_key(_key);
	_n->is_release = false;
	add_child(_n);
}

void node::remove_child_by_key(string _key){
	for(size_t i = 0;i < children.size();++i){
		if(children[i]->key == _key){
			/*delete children[i];
			children.erase(children.begin() + i,children.begin() + i+1);
			--i;*/
			children[i]->is_release = true;
			children[i]->remove_all_children();
		} 
	}
}

void node::remove_all_children(){
	for(auto &p : children){
		if(p) {
			p->is_release = true;
			p->remove_all_children();
		}//p->remove_all_children();
		//delete p;
		//p = 0;
	}
	//children.clear();
}

node *node::find_child_by_key(string _key){
	for(auto &p:children){
		if(p->get_key() == _key && !(p->is_release)) return p;
	}
	return 0;
}
void node::top_child_by_key(string _key){
	for(int i=0;i<children.size();++i){
		if(children[i]->get_key() == _key){
			if(i == children.size()-1) break;
			auto t_n = children[i];
			children.erase(children.begin()+i,children.begin()+i+1);
			children.push_back(t_n);
			i -= 1;
			return;
		}
	}
}

void node::set_parent(node* _p){
	parent = _p;
}
node *node::get_parent(){
	return parent;
}

void node::set_on_event_call_func(function<bool()>_func){
	event_call_func = _func;
}

void node::set_key(string _key){
	key = _key;
}
string node::get_key(){
	return key;
}
void node::set_dog_engine(dog_engine *_p_de){
	p_de = _p_de;
	for(auto &c:children)
		c->set_dog_engine(_p_de);
}
dog_engine &node::get_dog_engine(){
	if(!p_de) deu_throw("NULL p_de!");
	return *p_de;
}

void node::set_pos(dog_point _pos){
	pos = _pos;
}
dog_point node::get_pos(){
	return pos;
}
void node::set_pos_x(int x){
	pos.x = x;
}
void node::set_pos_y(int y){
	pos.y = y;
}
int node::get_pos_x(){
	return pos.x;
}
int node::get_pos_y(){
	return pos.y;
}
dog_point node::get_world_pos(){
	return get_parent_pos_sum() + pos;
}
dog_point node::get_parent_pos_sum(){
	dog_point p = { 0,0 };
	for(auto i = parent;i != 0;i = i->parent){
		p = p + i->pos;
	}
	return p;
}

bool node::is_visible(){
	return visible;
}
void node::set_visible(bool _v){
	visible = _v;
}

void node::_update(){
	if(!visible) return;

	if(p_de)
		update();
	
	for(auto &c : children){
		if(c) c->_update();
	}

}
void node::_rev_update(){
	for(auto &c:children)
	{
		if(c)c->_rev_update();
	}
	for(int i=0;i<children.size();++i){
		if(children[i] && children[i]->is_release){
			delete children[i];
			children[i] = 0;
			children.erase(children.begin()+i,children.begin()+i+1);
			--i;
		}
	}
}

bool node::_event_update(){
	if(!visible) return false;

	bool is_continue = true;
	for(int i=children.size()-1;i>=0;--i){
		if(children[i] && children[i]->_event_update()){
			is_continue = false;
			break;
		}
	}
	if(is_continue){
		return event_update();
	}
	return false;
}


void node::update(){

}

bool node::event_update(){
	return false;
}