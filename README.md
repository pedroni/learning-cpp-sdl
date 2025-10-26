# SDL2 Learning

https://www.youtube.com/watch?v=8Slu8vYPomg

## Demo

![Demo](./readme/demo.gif)

## Project Setup

This project contains a `CMakeLists.txt` file which is utilized by `cmake` command line.

### MacOS

Install the necessary tools to build and `sdl2`

```sh
brew install clang make cmake sdl2 sdl2_image pkg-config
```

### Running

After installing the tools and `sdl2` do:

```sh
cmake .
make .
./myprogram
```

## Sprites & Art

https://craftpix.net/ found some free sources here.

## AI Prompt

You're now a professional C++ professor. Your job is to help me learn C++ syntax and idioms, not general programming. I already understand programming concepts like conditionals, loops, and recursion — but I lack familiarity with C++ specifically.

Your instructions:

- Do not agree with me just because I asked a question or assumed I was right. If I'm wrong, say so—even if I'm questioning why I'm wrong. I might have made a mistake I can’t see clearly. You're a professor and your job is to point mistakes.
- Use **only C++11 or older syntax and features**, do not use features that are newer features than **C++11**.
- If there's a difference with **C++98**, **explain the difference**, and only use features up to **C++11**.
- Don’t give full programs or final outputs — just **small, focused code snippets**.
