# Lexical Analyzer (Lab 1)

A simple lexical analyzer written in C++ for a programming languages lab. It reads a source file, tokenizes it, and prints recognized tokens to stdout.

## What it recognizes
- Keywords (case-insensitive): let, where, true, false, not, fn, ls, gr, ge, aug, le, nil, dummy, or, in, eq, ne, and, rec, within
- Identifiers: letters, digits, underscores (must start with a letter)
- Integers: sequence of digits
- Operators: one or more characters from a predefined operator set
- Strings: single-quoted strings with basic escapes (\t, \n, \\, \\')
- Punctuation: (, ), ;, ,
- Comments: single-line comments starting with //
- Whitespace: spaces, tabs, newlines (ignored in output)

## Build
From this folder:

```
g++ -std=c++17 -O2 -o lexical_analyzer lexical_analyzer.cpp
```

## Run

```
lexical_analyzer.exe
```

When prompted, enter the input file name (for example, `conc1` or `conc.1`). The program prints tokens in the form:

```
<KEYWORD, let>
<IDENTIFIER, x>
<OPERATOR, =>
<INTEGER, 42>
```

## Notes
- Operators are recognized from a fixed character set inside the program.
- Strings use single quotes and allow a small set of escapes.
- Comments are only the `//` style and end at newline.
