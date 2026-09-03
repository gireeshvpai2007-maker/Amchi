# Amchi

> **Bringing GSB Konkani, my mother tongue, into the world of programming — one compiler at a time.**

Amchi is a programming language inspired by **GSB Konkani**, my mother tongue, and built from scratch in **C++**.

Amchi is an exploration of bringing a language rooted in our culture into the world of computer science. The goal is not simply to replace English programming keywords with Konkani words, but to understand and build the systems behind a programming language — including **lexing, parsing, abstract syntax trees, interpretation, memory, and eventually compilation**.

---

## Why Amchi?

Programming languages are powerful ways of expressing ideas.

As a GSB Konkani speaker, I wanted to explore a simple question:

> **What if the language we speak at home could also be used to write programs?**

Amchi is my attempt to connect my **mother tongue, culture, and computer science** by building a programming language from scratch.

The project is both a technical learning journey and a personal exploration of how language and technology can come together.

---

## A Simple Amchi Program

```amchi
kaam shuru() {
    ghe a = 10;
    ghe b = 20;

    dhake(a + b);
}
```

Output:

```text
30
```

The program begins execution from the special function:

```amchi
kaam shuru()
```

---

## Language Keywords

| Amchi Keyword | Meaning |
|---|---|
| `ghe` | Variable declaration |
| `dhake` | Output / Print |
| `nimgi` | Input |
| `jallari` | If |
| `najallari` | Else |
| `javchvare` | While |
| `kaam` | Function |
| `vishay` | Class |
| `shuru` | Program entry point |
| `jaag` | Address-of |

---

## Language Design

Amchi is designed to be **dynamically typed**.

The programmer does not explicitly specify the datatype of a variable.

```amchi
ghe age = 19;
ghe name = "Gireesh";
ghe pi = 3.14;
ghe student = true;
```

The value determines the type.

Variables can also be reassigned:

```amchi
ghe a = 10;

a = 20;
```

The exact runtime type system will evolve as the interpreter is implemented.

---

## Core Syntax

### Variables

```amchi
ghe name = "Gireesh";
ghe age = 19;
```

### Output

```amchi
dhake("Namaskar!");
dhake(age);
```

### Input

```amchi
nimgi >> age;
```

### If / Else

```amchi
jallari (age >= 18) {
    dhake("Adult");
}
najallari {
    dhake("Minor");
}
```

### While

```amchi
ghe i = 1;

javchvare (i <= 5) {
    dhake(i);
    i = i + 1;
}
```

### Function

```amchi
kaam add(a, b) {
    dhake(a + b);
}
```

Function definitions **do not end with a semicolon**.

### Class

```amchi
vishay Student {
    ghe name;
    ghe age;
};
```

Class definitions **end with a semicolon**.

### Object

```amchi
Student s;
```

Parameterized construction:

```amchi
Student s("Gireesh", 19);
```

### Pointer

```amchi
ghe a = 10;
ghe *p = jaag(a);

dhake(*p);
```

---

## Compiler Architecture

The initial Amchi implementation is planned around the following pipeline:

```text
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
```

The long-term goal is to evolve this into a complete compiler pipeline with code generation.

---

## Project Structure

```text
Amchi/
│
├── README.md
│
├── docs/
│   ├── language-spec.md
│   └── language-usage.md
│
├── examples/
│
├── src/
│   ├── ast/
│   ├── interpreter/
│   ├── lexer/
│   ├── parser/
│   └── main.cpp
│
└── tests/
```

---

## Development Status

### ✅ Completed
- [x] Language design
- [x] Token system
- [x] Lexer
- [x] Recursive-descent parser
- [x] AST
- [x] Basic interpreter
- [x] Variables
- [x] Arithmetic expressions
- [x] Comparisons
- [x] If/else
- [x] String literals
- [x] Built-in output

### 🚧 In Progress
- [ ] Runtime value system
- [ ] Functions
- [ ] Loops
- [ ] Better error reporting
- [ ] Test suite

### 🔮 Planned
- [ ] Classes
- [ ] Objects
- [ ] Pointers
- [ ] Standard library
- [ ] Bytecode/code generation

## Planned Features

- [ ] Dynamic variables
- [ ] Numbers
- [ ] Strings
- [ ] Boolean values
- [ ] Arithmetic operators
- [ ] Comparison operators
- [ ] Logical operators
- [ ] Input and output
- [ ] Conditional statements
- [ ] While loops
- [ ] Functions
- [ ] Classes
- [ ] Objects
- [ ] Constructors
- [ ] Pointers
- [ ] Abstract Syntax Tree
- [ ] Interpreter
- [ ] Error handling
- [ ] Standard library
- [ ] Compiler / code generation

The checklist will be updated as features are actually implemented.

---

## Documentation

- **[Language Specification](docs/language-spec.md)** — Formal rules and syntax of Amchi.
- **[Language Usage Guide](docs/language-usage.md)** — Practical examples and usage.

---

## Built With

- **C++**
- Data Structures and Algorithms
- Compiler Construction Concepts
- Git
- GitHub

---

## Project Status

🚧 **Early Development**

Amchi is currently in the language-design and compiler-development stage.

The language specification is being established before implementation begins. Features will be implemented incrementally, with each major compiler component developed and tested independently.

---

## The Idea Behind Amchi

> **A language spoken at home can also be a language used to build things.**

Amchi is my attempt to bring **GSB Konkani** into the world of programming languages while learning how programming languages and compilers work from the ground up.

This project is not only about building a compiler.

It is about exploring the intersection of **language, identity, culture, and technology**.

---

## Author

**Gireesh V Pai**

BTech Computer Science & Engineering  
MIT Manipal

GSB Konkani speaker

---

## License

License information will be added as the project matures.
