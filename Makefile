cxx_flags = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

solve: obj/main.o findRoots.o
	g++ main.o findRoots.o -o solve

obj/main.o: main.cpp
	g++ -c main.cpp $(cxx_flags)

findRoots.o: findRoots.cpp
	g++ -c findRoots.cpp $(cxx_flags)

tests: mainTest.o testSolver.o findRoots.o
	g++ mainTest.o testSolver.o findRoots.o -o tests

mainTest.o: main.cpp
	g++ -c main.cpp -D DEBUG -o mainTest.o $(cxx_flags)
testSolver.o: testSolver.cpp
	g++ -c testSolver.cpp $(cxx_flags)
