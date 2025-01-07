all:
	# Create the directory 'output' if it does not already exist
	mkdir -p output
	g++ src/virtualMachine.c -o output/virtualMachine