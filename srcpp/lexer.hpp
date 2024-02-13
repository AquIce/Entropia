#ifndef __ENT_FRONT_LEX__
#define __ENT_FRONT_LEX__

#include <vector>
#include "token.hpp"

std::string shift(std::string& str);

std::vector<ent_type_token> ent_front_lex(std::string src);

#endif // __ENT_FRONT_LEX__