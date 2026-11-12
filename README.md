# Lexical Analyzer

A C-based lexical analyzer that reads a source file and identifies different tokens in the C programming language.

## Overview

This project analyzes C source code and classifies tokens based on their type. It identifies keywords, identifiers, constants, operators, special characters, and comments while tracking their corresponding line numbers.

## Features

- Keyword identification
- Identifier detection
- Integer and floating-point constants
- Character and string constants
- Operator identification
- Special character detection
- Single-line and multi-line comment handling
- Preprocessor directive handling (`#include`)
- Line number tracking
- Missing bracket error detection

## Technologies Used

- Programming Language: C
- Concepts: Strings, Arrays, Functions, File Handling
- Standard: C11
- Compiler: GCC

## Compilation

```bash
gcc -Wall -Wextra -std=c11 main.c keyword.c operator.c special.c -o lexer
```

## Usage

Run the lexical analyzer using:

```bash
./lexer sample.c
```

Replace `sample.c` with the name of the C source file you want to analyze.

## Project Structure

- `main.c` – Main program and file processing
- `keyword.c`, `keyword.h` – Keyword identification
- `operator.c`, `operator.h` – Operator identification
- `special.c`, `special.h` – Special character identification
- `sample.c` – Sample input file

## Author

Junaid Gadagkar
