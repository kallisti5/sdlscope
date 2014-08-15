#!/bin/bash

clang++ main.cpp scopelogic.cpp -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL -lSDL -lpthread -lm -o sdlscope
