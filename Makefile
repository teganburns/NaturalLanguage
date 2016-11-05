CXX = g++
CXXFLAGS += -std=c++11 -g
LDFLAGS += -L/usr/local/lib -ldl

LIBS=-lcurl
INC=-I /home/owner/Documents/Development/git/SMFL/include -I /usr/include -I /usr/local/include


CPP_TARGET=main



all: main_cpp

main_cpp: main.o
	$(CXX) $(CXXFLAGS) $(INC) $^ $(LDFLAGS) $(LIBS) -o $@


clean:
	$(RM) $(CPP_TARGET)_cpp main.o
