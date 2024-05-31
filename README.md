# Entropia
Entropia is a C++ based programming language, implementing ownership and other usefull stuff

# TODO

- [x] Add variables
  - [x] Declaration syntax
  - [x] Assignment syntax
  - [x] Initialization syntax
- [x] Add functions
  - [x] Declaration syntax
  - [x] Call syntax
  - [x] Scopes
  - [ ] Optionnal arguments
- [ ] Add conditions
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
  - [ ] Switch
- [ ] Add loops
  - [x] For
  - [x] While
  - [ ] For : (requires arrays/strings)
- [x] Add concept of subEnv to allow scoping variables (add scope attribute to fn, if, for, ...)
- [x] Make parenthesis precedence
- [ ] Edit get_operator_return_type to not only checking left (could allow this: let a: i8 = 1 + 1024)
- [ ] Add logical operators between all types (ex: i8 - bool)
- [ ] Add other operators
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
  - [ ] Ternaries
- [ ] Add default to const (mut)
- [ ] Add other datatypes
  - [x] Booleans
  - [ ] Characters
  - [ ] Strings
  - [ ] Arrays
  - [ ] Maps
- [ ] Add classes
  - [ ] Declaration syntax
  - [ ] Member access syntax
  - [ ] ...
- [ ] Add modules

## Extension

[Wiki][wiki_lnk]



[wiki_lnk]: https://code.visualstudio.com/api/get-started/your-first-extension