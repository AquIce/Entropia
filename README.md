# Entropia
Entropia is a C++ based programming language, implementing ownership and other usefull stuff

# TODO

## Language Features

- [x] Add variables
  - [x] Declaration syntax
  - [x] Assignment syntax
  - [x] Initialization syntax
- [x] Add functions
  - [x] Declaration syntax
  - [x] Call syntax
  - [x] Scopes
  - [ ] Optionnal arguments
  - [x] Return statement
- [x] Add conditions
  - [x] If
  - [x] Else If
  - [x] Else
  - [x] Logical operators
    - [x] Binary operators
      - [x] ==
      - [x] !=
      - [x] &&
      - [x] ||
      - [x] <
      - [x] >
      - [x] <=
      - [x] >=
      - [x] ^^
    - [x] Unary operators
      - [x] !
  - [x] Match
- [ ] Add loops
  - [x] For
  - [x] While
  - [ ] For : (requires arrays/strings)
- [x] Add comments
  - [x] Single line
  - [x] Multi line
- [x] Add other operators
  - [x] Binary operators
    - [x] %
    - [x] <<
    - [x] >>
    - [x] &
    - [x] |
    - [x] ^
  - [x] Unary operators
    - [x] ++
    - [x] --
    - [x] ~
  - [x] Assignment
    - [x] (any)=
  - [x] Ternaries
- [ ] Add other datatypes
  - [x] Booleans
  - [x] Characters
  - [x] Strings
  - [ ] Arrays
  - [ ] Maps
- [ ] Add user-defined types
  - [x] Type declaration
  - [x] Type implementation
  - [x] Access specifiers
  - [ ] Instanciation
  - [ ] Member access syntax
    - [ ] External
    - [ ] Internal
- [ ] Add modules
- [ ] Add testing capabilities
- [ ] Add templating
- [ ] Add better macros

## Fixes / Additionnal features

- [x] Add concept of subEnv to allow scoping variables (add scope attribute to fn, if, for, ...)
- [x] Make parenthesis precedence
- [x] Add default to const (mut)
- [x] Add recursion guards
- [x] Move function call to expression evaluation (to allow fn() + fn())
- [x] Add support for negative numbers
- [ ] Prevent constant assign without value
- [ ] Add `is_valid_value` to every type (easier user-defined types)
- [ ] Fix unsigned variables declaration
- [ ] Fix `magnitude` on runtime NumberValues (u8 <-> i8)
- [ ] Add function args+return type check 
- [ ] Add comments and clean code
- [ ] Add variables check to parsing
- [ ] Evaluate constant expressions at compile time
- [ ] Compile language

## Extension

[Wiki][wiki_lnk]



[wiki_lnk]: https://code.visualstudio.com/api/get-started/your-first-extension