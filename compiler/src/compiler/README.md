# Layers of compilation

Yaksha uses a multi step compiler.

## 1. Parsing
- Tokenization
- Parse to token soup (DSL Macro AST)
- Apply DSL macros
- Parse to AST
- Desugar - level 1

## 2. Parse structure
- Classes, functions, constants are extracted at this level
- Basic validation is done at this level

## 3. Type checking
- Type inference
- Type checking
- Update AST with type information

## 4. Usage analysis
- Determine usage of functions for simple dead code elimination

## 5. Code generation
- Desugar - level 2
- Generate code

## 6. Compile & link to a native binary
- Based on generated C code - find features and dependencies
- Compile to binary using C99 compiler
        