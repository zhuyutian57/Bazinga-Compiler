# C++ Compiler

This is a simple C++ compiler. I try to implement all functions that should be included in C++(basic grammars). The produce of this project will be a translator(C++), without back end.

## 1.Architecture

![Translator Architecture](./images/architecture.png)

- **Symbol Table**:  Manage variables' informations during translation
- **Lexer**:  Arrange characters  from source codes(cpp files) and produce token stream.$Token:<token-name,token-type>$
- **Parser**: Analyze the structure of token stream based on Context-Free Grammar and LALR(1) algorithm. 
- **Semantic Analyzer**: Include type checking and calculating variables' attributes.  
- **Intermediate Code Generator**: Generate a code representation which is similar to the target code such as low-level or machine-like representation.  
- **Back End**: Code optimizing code generating. They are out of this project.

## 2.Symbol Table

​	

## 3.Lexer

## 4.Parser

## 5.Semantic Analyzer

## 6.Intermediate Code Generator