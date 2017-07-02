/*==============================================================*\
                
                a sort of JSON lib by Lx
                email: imbosslx@sina.com
                last_update: 2016.12.18 


\*==============================================================*/
#ifndef _DEU_JSON_OBJECT_TYPE_H_
#define _DEU_JSON_OBJECT_TYPE_H_

#include "../../dog_engine/dog_engine.h"
#include "../deu_exception/deu_exception.h"


namespace dog_engine_unit{


	class json_object_type{
	public:
		string key, text;
		vector<json_object_type> children;

		string get_key();
		void set_key(string _k);

		string get_text();
		void set_text(string _t);

		int get_type();//1 = string ,2 = value,3 = object,4 = array 

		string get_string();
		int get_int();
		long long get_long_long();
		double get_double();
		float get_float();

		void put_string(string v);
		void put_int(int v);
		void put_long_long(long long v);
		void put_double(double v);
		void put_float(float v);

		json_object_type &at(string _key);
		json_object_type &at(size_t _i);
		json_object_type add_object(json_object_type jo);
		json_object_type add_object(string _k,string _v);
		json_object_type add_object(string _k,long long _v);
		json_object_type add_object(string _k,double _v);

		json_object_type clone();


		json_object_type();
		json_object_type(string s);
		json_object_type(string s,string _k);

		json_object_type & operator[](string _k);
		json_object_type & operator[](size_t _i);


		static json_object_type phraze(string);
		static string json_object_type_to_string(const json_object_type &,int d = -1);
		static string read_file_all(fstream&);

	};

}





#endif