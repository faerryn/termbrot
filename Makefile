bin/termbrot: termbrot.c
	mkdir -p bin
	cc termbrot.c -lm -o bin/termbrot
