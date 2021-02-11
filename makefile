output: main.cpp table.cpp node.cpp
	g++ main.cpp table.cpp node.cpp -o output.exe
clean: 
	rm output.exe
