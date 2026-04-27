all: default

default:
	gcc -I src -Wall -Werror src/commands/*.c src/utils/*.c src/main.c -o Program/mcp
test:
	gcc -I src -Wall -Werror src/commands/*.c src/utils/*.c src/test.c -o Program/mcptest
release:
	gcc -I src -O2 src/commands/*.c src/utils/*.c src/main.c -o Program/mcp