# compiler

This project is my attempt of compiler. At the moment I'm only interested in the lexer and parser,
because getting them working is an important part of another programs.

## Lexer
This is done using a state machine. It is a conscious re-inventing of the wheel (there are programs outside
that make the lexical analysis much better, i.e. flex), in order to learn and think about this kind of programs

The first part of the lexical analysis is completed. The program is able to read JSON tokens from a certain file

## Roadmap

* Intensive testing so errors can be detected and fixed
* Creation of the parser, generation of dynamic menus from a JSON file
* Building of a library
* Creation of a regex analyzer to add the transitions
