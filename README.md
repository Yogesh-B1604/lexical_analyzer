# C Lexical Analyzer

A modular **Lexical Analyzer implemented in C** that scans C source files, identifies and classifies lexical tokens, tracks source-code line numbers, and generates a detailed token summary.

The project demonstrates practical understanding of **C programming, file handling, string processing, pointers, command-line arguments, tokenization, and compiler fundamentals**.

---

## Overview

The C Lexical Analyzer reads a C source file character by character and identifies different types of lexical tokens based on their patterns.

For each recognized token, the analyzer displays:

- Source-code line number
- Token type
- Token value

After scanning the complete source file, the analyzer generates a token summary containing the number of tokens detected in each category.

---

## Features

- C source-file analysis using command-line arguments
- Keyword identification
- Identifier identification
- Integer number detection
- Floating-point number detection
- String literal detection
- Character literal detection
- Single-line comment detection
- Multi-line comment detection
- Header file detection
- Preprocessor directive detection
- Arithmetic operator detection
- Relational operator detection
- Logical operator detection
- Bitwise operator detection
- Assignment operator detection
- Increment and decrement operator detection
- Pointer-related operator detection
- Special symbol detection
- Line-number tracking
- Unknown character detection
- Token frequency counting
- Formatted token summary generation

---

## Supported Token Categories

| Token Category | Examples |
|---|---|
| Keywords | `int`, `float`, `char`, `if`, `else`, `while`, `return`, `struct`, `enum` |
| Identifiers | `main`, `count`, `student`, `calculate_area` |
| Numbers | `10`, `123`, `3.14`, `95.5` |
| String Literals | `"Hello World"` |
| Character Literals | `'A'`, `'\n'` |
| Arithmetic Operators | `+`, `-`, `*`, `/`, `%` |
| Relational Operators | `==`, `!=`, `<`, `>`, `<=`, `>=` |
| Logical Operators | `&&`, `||`, `!` |
| Bitwise Operators | `&`, `|`, `^`, `~`, `<<`, `>>` |
| Assignment Operators | `=`, `+=`, `-=`, `*=`, `/=`, `%=` |
| Increment/Decrement | `++`, `--` |
| Pointer/Structure Operators | `*`, `&`, `->` |
| Special Symbols | `(`, `)`, `{`, `}`, `[`, `]`, `;`, `,`, `:` |
| Comments | `// comment`, `/* comment */` |
| Header Files | `#include <stdio.h>` |
| Preprocessor Directives | `#define MAX_SIZE 100` |

---

## Project Architecture

```text
                    C Source File
                          |
                          v
                 +------------------+
                 |  Character Scan  |
                 +------------------+
                          |
                          v
                 +------------------+
                 |  Token Detection |
                 +------------------+
                          |
          +---------------+---------------+
          |               |               |
          v               v               v
      Keywords       Identifiers       Literals
          |               |               |
          +---------------+---------------+
                          |
                          v
                 Operators / Symbols
                 Comments / Headers
                 Preprocessors
                          |
                          v
                  Token Classification
                          |
                          v
                    Token Counters
                          |
                          v
                    Token Summary
