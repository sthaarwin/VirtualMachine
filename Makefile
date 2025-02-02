all:
	g++ src/virtualMachine.c -o output/virtualMachine

clean:
	rm output/virtualMachine