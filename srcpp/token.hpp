#ifndef __ENT_TYPES_TOKEN__
#define __ENT_TYPES_TOKEN__

#include <iostream>
#include <string>

enum ent_type_token_type {
    OPERATOR,

    OPEN_PAREN,
    CLOSE_PAREN,

    NUMBER,
};

class ent_type_token {
private:
    enum ent_type_token_type type;
	std::string value;
public:
	ent_type_token(enum ent_type_token_type type, std::string value);
	ent_type_token();
	enum ent_type_token_type get_type();
	std::string get_value();
	void set_type(enum ent_type_token_type type);
	void set_value(std::string value);
	std::string pretty_print();
};

#endif // __ENT_TYPES_TOKEN__