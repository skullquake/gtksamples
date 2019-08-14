CXX=g++
CXXFLAGS=\
	 `pkg-config --cflags gtk+-2.0`
LIBS=\
	 `pkg-config --libs gtk+-2.0`
SRC=./src/a.cpp
BIN=./bin/a
$(BIN):$(SRC)
	mkdir -p $(@D)
	$(CXX)\
		$(CXXFLAGS)\
		$(SRC)\
		$(LIBS)\
		-o $(BIN)
.phony:\
	run\
	clean
run:
	$(BIN)
clean:
	rm $(BIN)
