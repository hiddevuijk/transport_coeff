test.exe: main.cpp  diffusion.h system.h multi_diffusion.h
	g++ main.cpp -std=c++11 -Wall -Werror  -o test.exe -g



.PHONY : clean
clean:
	rm test.exe

