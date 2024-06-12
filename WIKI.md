# Documentation

## Table of Contents

- [Documentation](#documentation)
	- [Table of Contents](#table-of-contents)
	- [1. Variables](#1-variables)
		- [1.1. Datatypes](#11-datatypes)
			- [1.1.1. Number Bases](#111-number-bases)
		- [1.2. Declaration](#12-declaration)
		- [1.3. Assignation](#13-assignation)
		- [1.4. Declaration + Assignation](#14-declaration--assignation)
	- [2. Operators](#2-operators)
		- [2.1. Binary Operators](#21-binary-operators)
		- [2.2. Unary Operators](#22-unary-operators)
		- [2.3. Assignation Operators](#23-assignation-operators)
	- [3. Functions](#3-functions)
		- [3.1. Declaration](#31-declaration)
			- [3.1.1. No Arguments Function](#311-no-arguments-function)
			- [3.1.2. Arguments Function](#312-arguments-function)
		- [3.2. Call](#32-call)
			- [3.2.1. No Arguments Call](#321-no-arguments-call)
			- [3.2.2. Arguments Call](#322-arguments-call)
	- [4. Conditions](#4-conditions)
		- [4.1. Logical Operators](#41-logical-operators)
			- [4.1.1. Binary Operators](#411-binary-operators)
			- [4.1.2. Unary Operators](#412-unary-operators)
		- [4.2. If Else](#42-if-else)
		- [4.3. Match](#43-match)
		- [4.4. Ternaries](#44-ternaries)
	- [5. Loops](#5-loops)
		- [5.1. For](#51-for)
		- [5.2. While](#52-while)
		- [5.3. For :  ⚠️](#53-for---️)
	- [6. Types](#6-types)
		- [6.1. Declaration](#61-declaration)
		- [6.2. Implementation](#62-implementation)
			- [6.2.1. Internal Member Access ⚠️](#621-internal-member-access-️)
			- [6.2.2. External Member Access ⚠️](#622-external-member-access-️)
		- [6.3. Public / Private ⚠️](#63-public--private-️)
		- [6.4. Inheritance ⚠️](#64-inheritance-️)
	- [7. Codespaces ⚠️](#7-codespaces-️)
		- [7.1. Creation ⚠️](#71-creation-️)
			- [7.1.1. Using ⚠️](#711-using-️)
		- [7.2. Importation ⚠️](#72-importation-️)
			- [7.2.1. System Import ⚠️](#721-system-import-️)
			- [7.2.2. Custom Import ⚠️](#722-custom-import-️)
			- [7.2.3. Alias Import ⚠️](#723-alias-import-️)
		- [7.3. Member Access ⚠️](#73-member-access-️)
	- [8. Error Handling ⚠️](#8-error-handling-️)
	- [9. Prescedence order](#9-prescedence-order)

> Note:
>
> Sections whose title ends with ⚠️ means they are not yet implemented

## 1. Variables

### 1.1. Datatypes

| Type | Symbol | Range | Example |
| - | - | - | - |
| Int 8 (Signed) | `i8` | -2^7 ->  2^7 - 1 | `let x: i8 = 0;` |
| Int 16 (Signed) | `i16` | -2^15 ->  2^15 - 1 | `let x: i16 = 0;` |
| Int 32 (Signed) | `i32` | -2^31 ->  2^31 - 1 | `let x: i32 = 0;` |
| Int 64 (Signed) | `i64` | -2^63 ->  2^63 - 1 | `let x: i64 = 0;` |
| Unsigned Int 8 | `u8` | 0 -> 2^8 - 1 | `let x: u8 = 0;` |
| Unsigned Int 16 | `u16` | 0 -> 2^16 - 1 | `let x: u16 = 0;` |
| Unsigned Int 32 | `u32` | 0 -> 2^32 - 1 | `let x: u32 = 0;` |
| Unsigned Int 64 | `u64` | 0 -> 2^64 - 1 | `let x: u64 = 0;` |
| Float 32 (float) | `f32` | Depends on the system | `let x: f32 = 0;` |
| Float 64 (double) | `f64` | *`Depends on the system | `let x: f64 = 0;` |
| Boolean | `bool` | true / false | `let x: bool = false;` |
| Character | `char` | '\<Any Character>' | `let x: char = '\n;` |
| Strings | `str` | "\<Any Characters>" | `let x: str = "Hello, World!";` |
| Arrays | `[<Type>, <Length>]` | [\<Any Values>, ...] | `let x: [i8, 3] = [1, 2, 3];` |
| Vectors | `[<Type>]` | [\<Any Values>, ...] | `let x: [i8] = [1, 2, 3, 4];` |
| Maps | `[<KeyType> -> <ValueType>]` | [\<Any Key>: \<Any Value>, ...] | `let x: [str -> i8] = ["one": 1, "two": 2];` |

#### 1.1.1. Number Bases

| Base | Notation | Example (12) | Valid Types |
| - | - | - | - |
| Decimal | `<number>` | `12` | `i8`, `i16`, `i32`, `i64`<br> `u8`, `u16`, `u32`, `u64`<br>`f32`, `f64` 
| Decimal | `0d<number>` | `0d12` | `i8`, `i16`, `i32`, `i64`<br> `u8`, `u16`, `u32`, `u64`
| Hexadecimal | `0x<number>` | `0xc` | `i8`, `i16`, `i32`, `i64`<br> `u8`, `u16`, `u32`, `u64`
| Binary | `0b<number>` | `0b1100` | `i8`, `i16`, `i32`, `i64`<br> `u8`, `u16`, `u32`, `u64`
| Octal | `0o<number>` | `0o14` | `i8`, `i16`, `i32`, `i64`<br> `u8`, `u16`, `u32`, `u64`

### 1.2. Declaration

```
let [mut] <name>: <type>;
```

\[mut] is used to make a variable mutable

\<name> only contains `a-z`, `A-Z` or `_`

\<type> is any valid [datatype](#11-datatypes)

> Note:
>
> All variables are immutable by default

### 1.3. Assignation

```
<name> = <value>;
```

\<name> is the name of the variable to set

\<value> is any valid value for the [datatype](#11-datatypes) of the variable

### 1.4. Declaration + Assignation

```
let [mut] <name>: <type> = <value>;
```

\[mut] is used to make a variable mutable

\<name> only contains `a-z`, `A-Z` or `_`

\<type> is any [native](#11-datatypes) or user-defined datatype

\<value> is any valid value for the [datatype](#11-datatypes) of the variable

## 2. Operators

### 2.1. Binary Operators

| Name | Symbol | Operands |
| - | - | - |
| Plus | `+` | `<Number> + <Number>` |
| Minus | `-` | `<Number> - <Number>` |
| Times | `*` | `<Number> * <Number>` |
| Divided by | `/` | `<Number> / <Number>` |
| Modulus | `%` | `<Number> % <Number>` |
| Left Shift | `<<` | `<Number> << <Number>` |
| Right Shift | `>>` | `<Number> >> <Number>` |
| Bitwise AND | `&` | `<Number> & <Number>` |
| Bitwise XOR | `^` | `<Number> ^ <Number>` |

### 2.2. Unary Operators

| Name | Symbol | Operands |
| - | - | - |
| Increment | `++` | `<Number>++` |
| Decrement | `--` | `<Number>--` |
| Bitwise NOT | `~` | `~<Number>` |

### 2.3. Assignation Operators

Any [binary](#21-binary-operators) single char  operator can be used like this:

`<Value> <Operator>= <Other Value>`

It applies the operator like this:

`<Value> = <Value> <Operator> <Other Value>`

> Example:
> 
> `x += 2`
> 
> Is the same as
> 
> `x = x + 2`

## 3. Functions

### 3.1. Declaration

#### 3.1.1. No Arguments Function

```
fn <name>(void): <return_type> {
	...
}
```

\<name> only contains `a-z`, `A-Z` or `_`

\<return_type> is any [native](#11-datatypes) or user-defined datatype or `void`

> Note:
> 
> The `void` keyword is mandatory, you will get an error if you forget it.

#### 3.1.2. Arguments Function

```
fn <name>([mut] <arg_name>: <arg_type>, ...): <return_type> {
	...
}
```

\<name> only contains `a-z`, `A-Z` or `_`

\[mut] is used to make a argument mutable

\<arg_name> only contains `a-z`, `A-Z` or `_`

\<arg_type> is any [native](#11-datatypes) or user-defined datatype

\<return_type> is any [native](#11-datatypes) or user-defined datatype or `void`

### 3.2. Call

#### 3.2.1. No Arguments Call

```
<name>(void);
```

\<name> is the name of the function to call

> Note:
> 
> The `void` keyword is mandatory, you will get an error if you forget it.

#### 3.2.2. Arguments Call

```
<name>(<arg>, ...)
```

\<name> is the name of the function to call

\<arg> is the name of the argument to pass, matching the function argument type 

## 4. Conditions

### 4.1. Logical Operators

#### 4.1.1. Binary Operators

| Name | Symbol | Operands |
| - | - | - |
| Equals | `==` | `<Any> == <Any>` |
| Different | `!=` | `<Any> - <Any>` |
| AND | `&&` | `<Any> && <Any>` |
| OR | `\|\|` | `<Any> \|\| <Any>` |
| Smaller than | `<` | `<Any> < <Any>` |
| Bigger than | `>` | `<Any> > <Any>` |
| Smaller than or equal to | `<=` | `<Any> <= <Any>` |
| Bigger than of equal to | `>=` | `<Any> >= <Any>` |
| XOR | `^^` | `<Any> ^^ <Any>` |

#### 4.1.2. Unary Operators

| Name | Symbol | Operands |
| - | - | - |
| NOT | `!` | `!<Any>` |

### 4.2. If Else

```
if(<condition>) {
	...
} else if(<other_condition>) {
	...
} else {
	...
}
```

\<condition> is the condition to match to enter the `if` block

\<other_condition> is the condition to match to enter the `else if` block

### 4.3. Match

```
match(<value>) {
	<case> => {
		...
		break;
	}
	default => {
		...
	}
	...
}
```

\<value> is the value to test

\<case> is the value to match to enter the following block of code

### 4.4. Ternaries

```
<condition> ? <value_if_true> : <value_if_false>;
```

\<condition> is the condition to test

\<value_if_true> is the value to return if the condition is true

\<value_if_false> is the value to return if the condition is false

## 5. Loops

### 5.1. For

```
for(<init_statement>; <condition>; <iteration_statement>) {
	...
}
```

\<init_statement> is the code executed before the loop

\<condition> is the condition checked before each iteration

\<init_statement> is the code executed before each iteration of the loop

### 5.2. While

```
while(<condition>) {
	...
}
```

\<condition> is the condition checked before each iteration

### 5.3. For : <iterable> ⚠️

```
for(<type> <name> : <iterable>) {
	...
}
```

\<type> is the type of the elements of the iterable

\<name> is the name of the element of the iterable

\<iterable> is the iterable to iterate through

## 6. Types

### 6.1. Declaration

```
type <name> {
	<member_name>: <member_type>;
}
```

\<name> only contains `a-z`, `A-Z` or `_`

\<member_name> only contains `a-z`, `A-Z` or `_`

\<member_type> is any [native](#11-datatypes) or user-defined datatype

### 6.2. Implementation

```
impl <type_name> {
	fn <method_name>(...): <method_type> {
		...
	}
}
```

\<type_name> is any [native](#11-datatypes) or user-defined datatype

\<method_name> only contains `a-z`, `A-Z` or `_`

\<method_type> is any [native](#11-datatypes) or user-defined datatype or `void`

#### 6.2.1. Internal Member Access ⚠️

```
impl <type_name> {
	<member_name>: <member_type>;
	
	... {
		this.<member_name> = ...
	}
}
```

\<type_name> is any [native](#11-datatypes) or user-defined datatype

\<member_name> only contains `a-z`, `A-Z` or `_`

\<member_type> is any [native](#11-datatypes) or user-defined datatype

> Note:
> 
> Use the `this` keyword with a dot (.) to access type members

#### 6.2.2. External Member Access ⚠️

```
let <var_name>: <class_name> = { ... };
<var_name>.<member_name> = ...
```

\<var_name> only contains `a-z`, `A-Z` or `_`

\<type_name> is the name of the type to instanciate

\<member_name> is the name of the type member to access

> Note:
> 
> Use the name of the instance with a dot (.) to access type members

### 6.3. Public / Private ⚠️

```
type <name> {
	@private
	...
	@public
	...
}
```
or
```
impl <type_name> {
	@private
	...
	@public
	...
}
```

\<name> only contains `a-z`, `A-Z` or `_`

\<type_name> is any [native](#11-datatypes) or user-defined datatype

### 6.4. Inheritance ⚠️

```
type <child_type> extends <parent_type> {
	...
}
```

\<child_type> only contains `a-z`, `A-Z` or `_`

\<parent_type> is any [native](#11-datatypes) or user-defined datatype

## 7. Codespaces ⚠️

### 7.1. Creation ⚠️

```
codespace <name> {
	...
}
```

\<name> only contains `a-z`, `A-Z` or `_`

#### 7.1.1. Using ⚠️

```
codespace <name> uses <other_codespace_name> {
	...
}
```

\<name> only contains `a-z`, `A-Z` or `_`

\<other_codespace_name> is the name of a codespace to use

> Note:
> 
> Using another codespace reduces the syntax from `<codespace>::<member>` to `member`, so be aware that this can raise conflicts

### 7.2. Importation ⚠️

#### 7.2.1. System Import ⚠️

```
use <system_codespace>;
```

\<system_codespace> is the name of the system codespace to import

#### 7.2.2. Custom Import ⚠️

```
use <codespace_name> from '<filename>.etp';
```

\<codespace_name> is the name of the custom codespace to import

\<filename> is the name of the file in which the custom codespace is

#### 7.2.3. Alias Import ⚠️

```
use <codespace_name> as <alias>;
```

\<codespace_name> is the name of the custom codespace to import

\<alias> only contains `a-z`, `A-Z` or `_`

### 7.3. Member Access ⚠️

```
<codespace>::<member>
```

## 8. Error Handling ⚠️

```
use ErrorHandling as ErrH;

try {
	...
} catch(<error_variable>: ErrH::Error) {
	...
}
```

\<error_name> only contains `a-z`, `A-Z` or `_`

## 9. Prescedence order

The higher an element is, the most prescedence it has (the first it is resolved)

1. Native Expressions (numbers, booleans, characters, strings)
2. Parenthesis Expressions
3. Function Calls
4. Multiplicative Expressions
5. Additive Expressions
6. Logical Expressions
7. Ternary Expressions