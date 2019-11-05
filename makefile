OBJ = main/main.o file_reader/file_reader.o plugboards/plugboard.o \
rotors/rotor.o
EXE = enigma
CXX = g++
CXXFLAGS = -Wall -Wextra -g -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp %/%.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clean
