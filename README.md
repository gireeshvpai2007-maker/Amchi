# Amchi

> **Bringing GSB Konkani, my mother tongue, into the world of programming — one compiler at a time.**

Amchi is a programming language inspired by **GSB Konkani**, my mother tongue, and built from scratch in **C++**.

The project explores what it takes to design and implement a programming language — from **lexing and parsing to abstract syntax trees and interpretation**, with compilation and code generation as long-term goals.

Amchi is not simply an attempt to replace English programming keywords with Konkani words. It is a technical and personal exploration of how **language, culture, and computer science** can come together.

---

## Why Amchi?

Programming languages are powerful ways of expressing ideas.

As a GSB Konkani speaker, I wanted to explore a simple question:

> **What if the language we speak at home could also be used to write programs?**

Amchi is my attempt to connect my **mother tongue, culture, and computer science** by building a programming language from the ground up.

The project is both a technical learning journey and a personal exploration of how language and technology can come together.

---

## A Simple Amchi Program

```amchi
kaam shuru() {
    ghe a = 10;
    ghe b = 20;

    dhake(a + b);
}

Output:

30

Program execution begins from the special function:

kaam shuru()
Language Keywords
Amchi Keyword	Meaning
ghe	Variable declaration
dhake	Output / Print
nimgi	Input
jallari	If
najallari	Else
javchvare	While
kaam	Function
vishay	Class
shuru	Program entry point
jaag	Address-of
Language Syntax
Variables
ghe name = "Gireesh";
ghe age = 19;

Variables are designed to use dynamic typing, where the runtime value determines the type.

Variable reassignment:

ghe a = 10;

a = 20;

Runtime type handling is currently being expanded as part of the runtime value system.

Output
dhake("Namaskar!");
dhake(10);

Example:

kaam shuru() {
    ghe name = "Gireesh";

    dhake(name);
}
Input

Planned input syntax:

nimgi >> age;
If / Else
jallari (age >= 18) {
    dhake("Adult");
}
najallari {
    dhake("Minor");
}
While Loop

Planned syntax:

ghe i = 1;

javchvare (i <= 5) {
    dhake(i);
    i = i + 1;
}
Functions

Planned function syntax:

kaam add(a, b) {
    dhake(a + b);
}

Function definitions do not end with a semicolon.

Classes

Planned class syntax:

vishay Student {
    ghe name;
    ghe age;
};

Class definitions end with a semicolon.

Objects

Planned object syntax:

Student s;

Parameterized construction:

Student s("Gireesh", 19);
Pointers

Planned pointer syntax:

ghe a = 10;
ghe *p = jaag(a);

dhake(*p);
Compiler Architecture

Amchi currently follows a traditional language-processing pipeline:

             Amchi Source Code
                     │
                     ▼
                   Lexer
                     │
                     ▼
                  Tokens
                     │
                     ▼
                   Parser
                     │
                     ▼
                    AST
                     │
                     ▼
                Interpreter
                     │
                     ▼
                   Output
1. Lexer

The lexer reads Amchi source code and converts it into a stream of tokens.

It handles concepts such as:

Keywords
Identifiers
Numbers
Strings
Operators
Parentheses
Braces
Assignment
Comments
2. Parser

Amchi uses a recursive-descent parser to transform tokens into a structured representation of the program.

Expression parsing follows operator precedence.

3. Abstract Syntax Tree

The parser builds an Abstract Syntax Tree (AST) representing the structure of the program.

The AST provides the foundation for interpretation and future code generation.

4. Interpreter

The interpreter walks the AST and executes the program.

Current interpreter functionality includes:

Variables
Arithmetic expressions
Comparisons
Logical expressions
Unary expressions
Conditional execution
String literals
Built-in output
5. Future Compiler

The long-term goal is to evolve Amchi beyond interpretation toward:

Amchi Source
     │
     ▼
   Lexer
     │
     ▼
   Parser
     │
     ▼
    AST
     │
     ▼
 Intermediate Representation
     │
     ▼
 Code Generation
     │
     ▼
 Executable / Bytecode
Project Structure
Amchi/
│
├── README.md
│
├── docs/
│   ├── language-spec.md
│   └── language-usage.md
│
├── examples/
│   └── *.amchi
│
├── src/
│   ├── ast/
│   ├── interpreter/
│   ├── lexer/
│   ├── parser/
│   └── main.cpp
│
└── tests/
Development Status
✅ Completed
 Language design
 Token system
 Lexer
 Recursive-descent parser
 Abstract Syntax Tree
 Basic interpreter
 Variables
 Variable reassignment
 Arithmetic expressions
 Comparison operators
 Logical operators
 If / Else
 String literals
 Built-in output
 Expression precedence
🚧 In Progress
 Runtime value system
 Proper boolean values
 Functions
 Function parameters and return values
 While loops
 Input
 Better runtime error handling
 Improved parser error messages
 Automated test suite
🔮 Planned
 Classes
 Objects
 Constructors
 Pointers
 Memory model
 Standard library
 Intermediate representation
 Bytecode / code generation
 Native compilation
Design Philosophy

Amchi is being developed around three ideas:

1. Learn by Building

Instead of only studying compiler theory, the project implements the concepts directly:

Theory
  ↓
Implementation
  ↓
Testing
  ↓
Understanding
2. Preserve Cultural Identity

Programming languages are usually designed around English terminology.

Amchi explores what programming could look like when the syntax is rooted in GSB Konkani.

3. Build the Language Properly

The goal is not just:

English keyword → Konkani keyword

The goal is to understand and implement the systems underneath:

Lexical analysis
Parsing
AST construction
Runtime values
Interpretation
Memory
Functions
Object systems
Compilation
Examples

Example programs will be maintained in the examples/ directory.

Example:

kaam shuru() {
    ghe a = 10;
    ghe b = 20;

    dhake(a + b);
}

Output:

30

More examples will be added as the language evolves.

Documentation
Language Specification
Formal syntax and language rules.
Language Usage Guide
Practical examples and usage.
Built With
C++
Data Structures & Algorithms
Compiler Construction Concepts
Object-Oriented Programming
Git
GitHub
Project Status

🚧 Early Development

Amchi currently has a working lexer, recursive-descent parser, AST, and basic interpreter.

The language is being developed incrementally, with each compiler component designed and tested independently.

The runtime system and higher-level language features are currently under development.

The Idea Behind Amchi

A language spoken at home can also be a language used to build things.

Amchi is my attempt to bring GSB Konkani into the world of programming languages while learning how programming languages and compilers work from the ground up.

This project is not only about building a compiler.

It is about exploring the intersection of:

Language · Identity · Culture · Technology

Author

Gireesh V Pai

BTech Computer Science & Engineering
MIT Manipal

GSB Konkani speaker

License

License information will be added as the project matures.


### One recommendation before you commit this

Make sure the **Completed** section exactly matches what is actually implemented in `src/`. In particular, don't claim functions, loops, booleans, input, classes, or pointers as implemented until the interpreter really supports them.

That accuracy will make Amchi look **far more professional** to someone who actually reads the source code.
