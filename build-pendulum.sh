#! /bin/sh

cc -ggdb -Wall -Wextra pendulum.c -o pendulum.out -Wl,--copy-dt-needed-entries -lraylib 
