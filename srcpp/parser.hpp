#ifndef __ENT_FRONT_PARSER__
#define __ENT_FRONT_PARSER__

#include "token.hpp"
#include "ast.hpp"

namespace ent {
	namespace front {
        ent::front::ast::Program parse(std::vector<ent::type::token> tokens);
    }
}

#endif // __ENT_FRONT_PARSER__