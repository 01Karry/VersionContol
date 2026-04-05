all: default

default:
	gcc -I src -Wall -Werror src/commands/*.c src/utils/*.c src/main.c -o mcp