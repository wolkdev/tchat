CXX=g++
CXXFLAGS=
SRC=aiostream.cpp main.cpp
OBJ=$(SRC:.cpp=.o)

ifeq ($(OS), Windows_NT)

	LDFLAGS=-Lgxxnet -lgxxnet -lwsock32 -lws2_32
	RMCMD=del
	EXEC=tchat.exe

else

	LDFLAGS=-Lgxxnet -lgxxnet
	RMCMD=rm -rf
	EXEC=tchat

endif

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $(EXEC) $^ $(LDFLAGS)

aiostream.o: aiostream.hpp

%.o: %.cpp
	$(CXX) -g -o $@ -c $< $(CXXFLAGS)

.PHONY: clean

clean:
	@$(RMCMD) *.o