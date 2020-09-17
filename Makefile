CXX = gcc
CXXFLAGS = -Wall -march=native -Wextra -pedantic

BINS = cmdset

$(BINS): $(OBJ)
	$(CXX) src/cmdset.c $(CXXFLAGS) $^ -o $(BINS)

clean:
	rm -Rf $(BINS)

