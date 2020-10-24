build: termbrot.c
	mkdir -p bin
	cc termbrot.c -lm -o bin/termbrot

clean: bin/*
	rm -r bin/*
