Sim: Sim.o VehicleBase.o FileReader.o Animator.o
	g++ -g -Wall -std=c++17 -o Sim Sim.cpp VehicleBase.cpp FileReader.cpp Animator.o

FileReader.o: FileReader.cpp VehicleBase.cpp FileReader.h
	g++ -Wall -std=c++17 -c FileReader.cpp

VehicleBase.o: VehicleBase.cpp VehicleBase.h
	g++ -Wall -std=c++17 -c VehicleBase.cpp

Animator.o: Animator.cpp Animator.h
	g++ -Wall -std=c++17 -c Animator.cpp

clean:
	/bin/rm -f *.o Sim