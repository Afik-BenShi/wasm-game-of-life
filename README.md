# Have you ever written C++ for your frontend?
This is a simple challange I took on myself. 
- Make a frontend webapp using ONLY C++.

I chose to imlement Conways game of life, a simple cellular automata with very cool emergent properties.
For example, [Conways Game of Life is Turing complete](https://www.youtube.com/watch?v=My8AsV7bA94).
Therefore, [you can apparently simulate Conways Game of Life inside Conways Game of Life](https://www.youtube.com/watch?v=xP5-iIeKXE8).

## But why would you do this to yourself? 
~~Becasue I love pain~~

But actually, a few reasons come to mind:
1. **Wasm is a cool new technology** I wanted to learn about, and what is a better way to learn other then doing an actual project.
2. **Summer vacation** is long and I wanted to keep my skills sharp (yes, I could have gone back to my project from last summer but I didn't want to).

And in the spirit of emergent properties, I wanted to use C at first as this was the last language I learned, but the compiler I used [Cheerp](https://leaningtech.com/cheerp/) had no C documentation.
Hence

3. I wanted to **learn a bit of C++**

## How to run?
Compile using Cheerp wasm compiler
```
/opt/cheerp/bin/clang++ index.cpp -o index.js -O3
```
Then use some server (I used vscode extension live server) to run index.html.
