# Amchi Language Specification

**Version:** 0.1  
**Status:** Initial Language Design

---

## 1. Overview

Amchi is a dynamically typed programming language inspired by **GSB Konkani**.

The language uses Roman-script Konkani keywords while maintaining a familiar programming syntax.

Amchi is being developed from scratch in **C++**.

This document defines the syntax and language rules currently agreed upon for Amchi.

The specification will evolve as the language develops.

---

# 2. Design Principles

Amchi follows these initial principles:

1. The language should have its own identity.
2. GSB Konkani terminology should be used for important language constructs.
3. Variables should use dynamic typing.
4. The syntax should remain readable and familiar to programmers.
5. The compiler/interpreter should be implemented from scratch.
6. Language features should be formally defined before implementation.

---

# 3. Keywords

The following keywords are reserved by Amchi.

| Keyword | Purpose |
|---|---|
| `ghe` | Variable declaration |
| `dhake` | Output |
| `nimgi` | Input |
| `jallari` | If |
| `najallari` | Else |
| `javchvare` | While |
| `kaam` | Function |
| `vishay` | Class |
| `shuru` | Program entry point |
| `jaag` | Address-of |

---

# 4. Basic Syntax

Amchi uses the following symbols:

| Symbol | Purpose |
|---|---|
| `{ }` | Code blocks |
| `( )` | Parameters, arguments and grouped expressions |
| `;` | Statement termination |
| `*` | Pointer declaration / dereference |
| `=` | Assignment |
| `>>` | Input operator |

---

# 5. Statements

Normal statements end with a semicolon.

Examples:

```amchi
ghe a = 10;

a = 20;

dhake(a);

nimgi >> a;
```

---

# 6. Variables

Variables are declared using the keyword `ghe`.

Syntax:

```text
ghe identifier = value;
```

Example:

```amchi
ghe age = 19;
ghe name = "Gireesh";
ghe pi = 3.14;
ghe active = true;
```

---

## 6.1 Dynamic Typing

Amchi does not require the programmer to explicitly specify a datatype.

The value assigned to the variable determines its initial type.

Example:

```amchi
ghe age = 19;
ghe name = "Gireesh";
ghe pi = 3.14;
ghe active = true;
```

Conceptually:

```text
19          → Number
"Gireesh"   → String
3.14        → Number
true        → Boolean
```

---

## 6.2 Declaration Without Initial Value

A variable can be declared without an initial value.

```amchi
ghe age;
```

The variable has no assigned value until it receives one.

---

## 6.3 Assignment

An existing variable can be assigned a new value.

```amchi
ghe a = 10;

a = 20;
```

Because Amchi is dynamically typed, reassignment may change the value's type.

Example:

```amchi
ghe a = 10;

a = "hello";
```

The exact runtime rules for type changes will be finalized during implementation.

---

# 7. Data Types

The initial Amchi design includes:

- Number
- String
- Boolean
- Null

Examples:

```amchi
ghe age = 19;
ghe name = "Gireesh";
ghe pi = 3.14;
ghe active = true;
```

Additional types may be added in future versions.

---

# 8. Output

Output is performed using the keyword `dhake`.

Syntax:

```text
dhake(expression);
```

Examples:

```amchi
dhake("Namaskar!");
dhake(age);
dhake(a + b);
```

---

# 9. Input

Input is performed using the keyword `nimgi`.

Syntax:

```text
nimgi >> identifier;
```

Example:

```amchi
ghe age;

nimgi >> age;

dhake(age);
```

The exact rules for converting input into runtime values will be defined during interpreter implementation.

---

# 10. Operators

## 10.1 Arithmetic Operators

The initial design supports:

```text
+
-
*
/
%
```

Example:

```amchi
ghe a = 10;
ghe b = 3;

dhake(a + b);
dhake(a - b);
dhake(a * b);
dhake(a / b);
dhake(a % b);
```

---

## 10.2 Comparison Operators

```text
==
!=
>
<
>=
<=
```

Example:

```amchi
jallari (age >= 18) {
    dhake("Adult");
}
```

---

## 10.3 Logical Operators

```text
&&
||
!
```

Example:

```amchi
jallari (age >= 18 && active) {
    dhake("Allowed");
}
```

---

# 11. Conditional Statements

## 11.1 If

The Amchi `if` construct uses `jallari`.

Syntax:

```text
jallari (condition) {
    statements
}
```

Example:

```amchi
jallari (age >= 18) {
    dhake("Adult");
}
```

---

## 11.2 Else

The Amchi `else` construct uses `najallari`.

Syntax:

```text
jallari (condition) {
    statements
}
najallari {
    statements
}
```

Example:

```amchi
jallari (age >= 18) {
    dhake("Adult");
}
najallari {
    dhake("Minor");
}
```

---

# 12. While Loop

The Amchi `while` loop uses `javchvare`.

Syntax:

```text
javchvare (condition) {
    statements
}
```

Example:

```amchi
ghe i = 1;

javchvare (i <= 5) {
    dhake(i);
    i = i + 1;
}
```

---

# 13. Functions

Functions are declared using `kaam`.

Syntax:

```text
kaam functionName(parameters) {
    statements
}
```

Example:

```amchi
kaam add(a, b) {
    dhake(a + b);
}
```

Functions can be called using:

```amchi
add(10, 20);
```

---

## 13.1 Function Definitions and Semicolons

Function definitions **do not end with a semicolon**.

Correct:

```amchi
kaam hello() {
    dhake("Hello");
}
```

Incorrect:

```amchi
kaam hello() {
    dhake("Hello");
};
```

This rule applies to:

- Normal functions
- Methods
- Constructors

---

# 14. Main Function

Every executable Amchi program begins execution from:

```amchi
kaam shuru() {
    statements
}
```

`shuru()` is a special function that acts as the program entry point.

An Amchi program must contain exactly one `shuru()` entry point.

Example:

```amchi
kaam shuru() {
    dhake("Namaskar!");
}
```

The `shuru()` function does not end with a semicolon.

---

# 15. Classes

Classes are declared using the keyword `vishay`.

Syntax:

```text
vishay ClassName {
    members
};
```

Example:

```amchi
vishay Student {
    ghe name;
    ghe age;
};
```

---

## 15.1 Class Semicolon

A class definition **must end with a semicolon**.

Correct:

```amchi
vishay Student {
    ghe name;
};
```

This is different from function definitions.

Function:

```amchi
kaam hello() {
    dhake("Hello");
}
```

Class:

```amchi
vishay Student {
    ghe name;
};
```

---

# 16. Objects

Objects are created using the class name followed by the object name.

Syntax:

```text
ClassName objectName;
```

Example:

```amchi
Student s;
```

---

# 17. Constructors

Constructors use the class name as the constructor name.

Example:

```amchi
vishay Student {

    ghe name;
    ghe age;

    kaam Student(n, a) {
        name = n;
        age = a;
    }
};
```

A parameterized object is created by providing values inside parentheses.

```amchi
Student s("Gireesh", 19);
```

The constructor receives:

```text
n = "Gireesh"
a = 19
```

---

# 18. Pointers

Amchi supports pointer syntax.

A pointer is declared using `*`.

The address of a variable is obtained using `jaag()`.

Example:

```amchi
ghe a = 10;

ghe *p = jaag(a);
```

Here:

```text
a
│
└── contains 10

p
│
└── contains the address of a
```

---

## 18.1 Address-of

The `jaag()` operation obtains the address of a variable.

Syntax:

```text
jaag(variable)
```

Example:

```amchi
ghe a = 10;

ghe *p = jaag(a);
```

---

## 18.2 Dereferencing

A pointer is dereferenced using `*`.

Example:

```amchi
ghe a = 10;

ghe *p = jaag(a);

dhake(*p);
```

Output:

```text
10
```

---

## 18.3 Modifying Through a Pointer

A pointer can be used to modify the value it points to.

```amchi
ghe a = 10;

ghe *p = jaag(a);

*p = 20;

dhake(a);
```

Output:

```text
20
```

The exact pointer safety and memory-management rules will be defined during runtime implementation.

---

# 19. Comments

## 19.1 Single-Line Comments

Single-line comments begin with `//`.

```amchi
// This is a comment

ghe a = 10;
```

---

## 19.2 Multi-Line Comments

Multi-line comments use `/*` and `*/`.

```amchi
/*
   This is a
   multi-line comment.
*/

ghe a = 10;
```

---

# 20. Identifiers

Identifiers are names used for variables, functions, classes and objects.

Examples:

```text
age
name
student
add
Student
```

Identifiers must not use reserved keywords.

For example:

```amchi
ghe ghe = 10;
```

is invalid because `ghe` is a reserved keyword.

The exact rules for valid identifier characters will be finalized during lexer implementation.

---

# 21. Complete Example

```amchi
kaam shuru() {

    ghe name;
    ghe age;

    dhake("Enter your name:");
    nimgi >> name;

    dhake("Enter your age:");
    nimgi >> age;

    jallari (age >= 18) {
        dhake(name);
        dhake("You are an adult.");
    }
    najallari {
        dhake(name);
        dhake("You are a minor.");
    }
}
```

---

# 22. Language Rules Summary

```text
Variable:
ghe a = 10;

Output:
dhake(a);

Input:
nimgi >> a;

If:
jallari (condition) {
}

Else:
najallari {
}

While:
javchvare (condition) {
}

Function:
kaam name(parameters) {
}

Main:
kaam shuru() {
}

Class:
vishay Name {
};

Object:
Name object;

Parameterized Object:
Name object(value1, value2);

Pointer:
ghe *p = jaag(a);

Dereference:
*p
```

---

# 23. Version 0.1 Scope

The following features are part of the initial language design:

- Dynamic variables
- Numbers
- Strings
- Boolean values
- Input
- Output
- Arithmetic expressions
- Comparison expressions
- Logical expressions
- If / Else
- While loops
- Functions
- Main function
- Classes
- Objects
- Constructors
- Pointers
- Comments

A feature listed in this specification may still be **unimplemented** in the compiler.

The implementation status will be tracked separately.

---

# 24. Future Language Features

Possible future additions include:

- For loops
- Arrays
- More string operations
- Return statements
- Function overloading
- Access modifiers
- Inheritance
- Polymorphism
- Exception handling
- Modules
- Standard library
- Better memory management
- Generics
- Compiler optimizations
- Native code generation

These are ideas for future versions and are **not part of the current language specification**.

---

# 25. Specification Status

**Amchi Language Specification v0.1**

Status:

🚧 **Design Stage**

This specification represents the current language design and may change as implementation reveals new requirements or ambiguities.

Major language changes should be documented and versioned.