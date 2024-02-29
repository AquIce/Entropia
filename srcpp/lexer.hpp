#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>
#include "token.hpp"

std::string shift(std::string& str);

namespace ent {
	namespace front {
		std::vector<ent::type::token> lex(std::string src);
	}
}

#endif // __ENT_FRONT_LEX__