# JSON Compiler

## Overview

This project is a **JSON Compiler** that performs **lexical, syntactic, and semantic analysis** on JSON input. It detects errors, generates an **Abstract Syntax Tree (AST)**, performs **semantic validation**, and produces an **Intermediate Representation (IR)** for further processing.

![Alt text]([https://example.com/image.png](https://preview.redd.it/dogrvclkll0a1.png?auto=webp&s=72e05d2cea869d6b1218193a947efb316c1c01b0))

## Features

- **Lexical Analysis**: Tokenizes JSON input and detects invalid tokens.
- **Syntactic Analysis**: Constructs an **AST** and checks for structural errors.
- **Semantic Analysis**: Detects logical errors such as duplicate keys, type mismatches, and invalid values.
- **Intermediate Representation (IR)**: Converts valid JSON into an IR schema.
- **Error Handling**: Displays detailed error messages for debugging.

---

## Project Structure
```plaintext
📦 json-compiler 
├── 📜 json_main.cpp     > Main entry point of the compiler 
├── 📜 json_lexer.h      > Header file for lexical analysis 
├── 📜 json_lexer.cpp    > Implements lexical analysis 
├── 📜 json_parser.cpp   > Implements syntax analysis & AST generation 
├── 📜 json_semantic.cpp > Implements semantic analysis 
├── 📜 json_ir.h         > Header file for IR generation 
├── 📜 json_ir.cpp       > Implements IR generation 
├── 📜 input.json        > Sample input JSON file 
├── 📜 wrong.json        > JSON file with lexical, syntax, and semantic errors 
├── 📜 README.md         > Project documentation 
└── 📜 Makefile          > Build automation
```

---

## Installation & Compilation

### Prerequisites
- C++ Compiler (**g++**, Clang, or MSVC)
- Git (for version control)

### Build Instructions
```sh
g++ -o json_compiler json_main.cpp json_lexer.cpp json_parser.cpp json_semantic.cpp json_ir.cpp -std=c++17
```

## Compilation
```sh
./json_compiler
```

---

## Add Sample Input & Output

Show an example input JSON and compiler output using JSON and code blocks.
## Sample Execution

### Input (`wrong.json`):
```json
{
  "name": "Alice",
  "age": 25,
  "age": 30,
  "@invalidKey": "error",
  "scores": [95, 88, 92, ]
}
```
### Output
```yaml
Tokens:
Token({, Line: 1, Column: 0)
Token(name, Line: 2, Column: 3)
...
Token(@invalidKey, Line: 7, Column: 3)  <-- Lexical Error
Token(], Line: 6, Column: 26)
Token(EOF, Line: 10, Column: 1)

Generated AST:
Object: {
  name:   Value: Alice
  age:   Value: 25
  age:   Value: 30   <-- Semantic Error: Duplicate Key
}

Performing Semantic Analysis...
Semantic Error: Duplicate key 'age' found.

Generating Intermediate Representation (IR)...
IR Type: object
Properties: name age age isStudent scores @invalidKey
```

---

## License

This project is open-source under the **MIT License**.

