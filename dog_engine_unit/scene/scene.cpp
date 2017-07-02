#include "scene.h"

using namespace dog_engine_unit;

void scene::add_child(node *_n){
	//_n->parent = this;
	_n->set_parent(0);
	_n->set_dog_engine(p_de);
	_n->is_release = false;
	children.push_back(_n);
}

void scene::add_child(node *_n,string _key){
	_n->set_key(_key);
	add_child(_n);
}

void scene::remove_child_by_key(string _key){
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

void scene::remove_all_children(){
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

node *scene::find_child_by_key(string _key){
	for(auto &p:children){
		if(p->get_key() == _key && !(p->is_release)) return p;
	}
	return 0;
}

void scene::_update(){
	update();
	for(auto &c : children){
		if(c) c->_update();
	}
}

void scene::_rev_update(){
	for(auto &c:children){
		if(c) c->_rev_update();
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

bool scene::_event_update(){
	bool is_continue = true;
	for(int i=children.size()-1;i>=0;--i){
		if(children[i] && children[i]->_event_update()){
			is_continue = false;
			break;
		}
	}
	if(is_continue)
		return event_update();
	return false;
}

scene * scene::create(){
	auto sc = new scene();
	return sc;
}

void scene::set_dog_engine(dog_engine *_p_de){
	p_de = _p_de;
	for(auto &c : children)
		c->set_dog_engine(_p_de);
}
dog_engine &scene::get_dog_engine(){
	if(!p_de) deu_throw("NULL p_de!");
	return *p_de;
}

void scene::set_on_event_call_func(function<bool()>_func){
	event_call_func = _func;
}

void scene::init(){

}

void scene::release(){
	remove_all_children();
}

void scene::update(){
	

}

bool scene::event_update(){
	return false;
}