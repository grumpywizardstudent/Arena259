CXX      = g++
CXXFLAGS = -std=c++17
SRC      = ./src/*.cpp
CREATURES = ./src/creatures/*.cpp
TARGET   = ./arena
build: clean $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) $(CREATURES) -o $(TARGET)

clean:
	rm -f $(TARGET)
