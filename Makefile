all:
	g++ src/axvm.c src/axasmlexer.c -o bin/axvm

parser:
	g++ src/axasmlexer.c src/axasmparser.c src/axasm.c -o bin/axasm

clean:
	rm bin/axvm 