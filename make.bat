mkdir out
gcc -ISDL2src/include -LSDL2src/lib main.c -lmingw32 -lSDL2main -lSDL2 -o out/main.exe