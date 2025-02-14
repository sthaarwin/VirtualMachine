all:
	g++ src/axvm.c src/axasmlexer.c -o bin/axvm

clean:
	rm bin/axvm 