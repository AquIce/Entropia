
enum ent_front_token_type {
    OPERATOR,

    OPEN_PAREN,
    CLOSE_PAREN,

    NUMBER,
}

typedef struct ent_front_token {
    ent_front_token_type type;
    char* value;
} ent_front_token;