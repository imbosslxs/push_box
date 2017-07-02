#ifndef _DEU_NODE_H_
#define _DEU_NODE_H_


#include "../../dog_engine/dog_engine.h"
#include "../deu_exception/deu_exception.h"

namespace dog_engine_unit {
typedef Dog_point dog_point;
typedef Dog_Engine dog_engine;


class node {
public:
	dog_point pos;
	string key;
	dog_engine *p_de;

	bool visible;

	function<bool()> event_call_func;

	vector<node*> children;
	node *parent;

	bool is_release;

	void _rev_update();
	void _update();
	bool _event_update();
	virtual void update();
	virtual bool event_update();

	void add_child(node *_n);
	void add_child(node *_n, string _key);
	//remove will delete the child pointer!
	void remove_child_by_key(string _key);
	void remove_all_children();
	node *find_child_by_key(string _key);
	void top_child_by_key(string _key);

	void set_parent(node *_p);
	node *get_parent();

	void set_on_event_call_func(function<bool()> _func);

	void set_key(string _key);
	string get_key();

	void set_dog_engine(dog_engine *_p_de);
	dog_engine &get_dog_engine();


	void set_pos(dog_point _pos);
	dog_point get_pos();
	void set_pos_x(int x);
	void set_pos_y(int y);
	int get_pos_x();
	int get_pos_y();
	dog_point get_world_pos();
	dog_point get_parent_pos_sum();

	bool is_visible();
	void set_visible(bool _v);

	virtual void init();

	static node* create(dog_point _pos, string _key);
	static node* create(dog_point _pos);
	static node* create();

};


}


#endif