JSON Compiler
=============

Overview
--------

This project is a **JSON Compiler** that performs **lexical, syntactic, and semantic analysis** on JSON input. It detects errors, generates an **Abstract Syntax Tree (AST)**, performs **semantic validation**, and produces an **Intermediate Representation (IR)** for further processing.

Features
--------

*   **Lexical Analysis**: Tokenizes JSON input and detects invalid tokens.
    
*   **Syntactic Analysis**: Constructs an **AST** and checks for structural errors.
    
*   **Semantic Analysis**: Detects logical errors such as duplicate keys, type mismatches, and invalid values.
    
*   **Intermediate Representation (IR)**: Converts valid JSON into an IR schema.
    
*   **Error Handling**: Displays detailed error messages for debugging.
    

Project Structure
-----------------

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   json-compiler/  │-- src/  │   ├── json_lexer.h        # Header file for lexical analysis  │   ├── json_lexer.cpp      # Implements lexical analysis  │   ├── json_parser.cpp     # Implements syntax analysis & AST generation  │   ├── json_semantic.cpp   # Implements semantic analysis  │   ├── json_ir.h           # Header file for IR generation  │   ├── json_ir.cpp         # Implements IR generation  │   ├── json_main.cpp       # Main entry point (tokenization, parsing, AST, IR)  │  │-- test/  │   ├── correct.json        # Sample correct JSON file  │   ├── wrong.json          # JSON file with lexical, syntax, and semantic errors  │  │-- README.md               # Project documentation  │-- Makefile                # Build automation   `

Installation & Compilation
--------------------------

### Prerequisites

*   C++ Compiler (**g++**, Clang, or MSVC)
    
*   Git (for version control)
    

### Build Instructions

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   g++ -o json_compiler json_main.cpp json_lexer.cpp json_parser.cpp json_semantic.cpp json_ir.cpp -std=c++17   `

### Run the Compiler

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   ./json_compiler   `

Sample Execution
----------------

### Input (wrong.json):

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   {    "name": "Alice",    "age": 25,    "age": 30,    "@invalidKey": "error",    "scores": [95, 88, 92, ]  }   `

### Output:

Plain textANTLR4BashCC#CSSCoffeeScriptCMakeDartDjangoDockerEJSErlangGitGoGraphQLGroovyHTMLJavaJavaScriptJSONJSXKotlinLaTeXLessLuaMakefileMarkdownMATLABMarkupObjective-CPerlPHPPowerShell.propertiesProtocol BuffersPythonRRubySass (Sass)Sass (Scss)SchemeSQLShellSwiftSVGTSXTypeScriptWebAssemblyYAMLXML`   Tokens:  Token({, Line: 1, Column: 0)  Token(name, Line: 2, Column: 3)  ...  Token(@invalidKey, Line: 7, Column: 3)  <-- Lexical Error  Token(], Line: 6, Column: 26)  Token(EOF, Line: 10, Column: 1)  Generated AST:  Object: {    name:   Value: Alice    age:   Value: 25    age:   Value: 30   <-- Semantic Error: Duplicate Key  }  Performing Semantic Analysis...  Semantic Error: Duplicate key 'age' found.  Generating Intermediate Representation (IR)...  IR Type: object  Properties: name age age isStudent scores @invalidKey   `

Contributing
------------

1.  Fork the repository
    
2.  Create a new branch (feature-new-feature)
    
3.  Commit changes
    
4.  Push to GitHub
    
5.  Submit a Pull Request
    

License
-------

This project is open-source under the **MIT License**.
