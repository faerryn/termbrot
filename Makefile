build: termbrot

termbrot: termbrot.c
	cc termbrot.c -lm -o termbrot

clean: bin/*
	rm -r bin/*
