#ifndef _DEU_MSGBAR_H_
#define _DEU_MSGBAR_H_

#include "../layer/layer.h"
#include "../bitchar/bitchar.h"

namespace dog_engine_unit{

	class msgbar : public layer{
	public:

		void set_text(bitchar_type _text);
		bitchar_type get_text();

		virtual void init();

		virtual void update();


		static msgbar *create(bitchar_type _text);

	};

}






#endif