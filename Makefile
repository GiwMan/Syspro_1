CXX= g++ -std=c++11

CXXFLAGS = -Wall -g

diseaseMonitor: diseaseMonitor.o \
	Patient.o \
	Hashing.o \
	Date.o \
	AVL.o \
	helper_functions.o 

	$(CXX) $(CXXFLAGS) -o diseaseMonitor \
diseaseMonitor.o Patient.o Hashing.o Date.o \
AVL.o helper_functions.o 

Date.o : Date.h
Patient.o : Patient.h Date.h
Hashing.o : Hashing.h Patient.h AVL.h
AVL.o : AVL.h Patient.h 
helper_functions.o : helper_functions.h Patient.h AVL.h Hashing.h 


clean:
	$(RM) diseaseMonitor *.o