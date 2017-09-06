CXX = g++
CXXFLAGS += -std=c++11 -g
LDFLAGS += -L/usr/local/lib -ldl

LIBS=-lcurl
INC=-I /home/owner/Documents/Development/git/SMFL/include -I /usr/include -I /usr/local/include


CPP_TARGET=main



all: main_cpp

main_cpp:
	$(CXX) $(CXXFLAGS) $(INC) $(LDFLAGS) $(LIBS) $(CPP_TARGET).cpp -o $(CPP_TARGET)


clean:
	$(RM) $(CPP_TARGET)
