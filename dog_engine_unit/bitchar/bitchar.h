#ifndef _DEU_BITCHAR_H_
#define _DEU_BITCHAR_H_

#include "../bitchar_type/bitchar_type.h"
#include "../node/node.h"

namespace dog_engine_unit{

	class bitchar : public node{
		public:
			dog_point size;
			bitchar_type bt;

			void set_bitchar(bitchar_type _bt);
			bitchar_type get_bitchar();

			dog_point get_size();

			virtual void update();
			virtual void init();

			static bitchar *create(bitchar_type _bt,dog_point _pos);
			static bitchar *create(bitchar_type _bt);

	};


}



#endif