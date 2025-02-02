all:
	g++ src/virtualMachine.c -o bin/virtualMachine

clean:
	rm output/virtualMachine