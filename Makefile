CXX = g++
CCFLAGS = -std=c++17 -Wall -g

SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = src
INC_DIR = include

SOURCES = $(SRC_DIR)/Particle.cpp $(SRC_DIR)/Physics.cpp $(SRC_DIR)/Simulation.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = ParticleSimulation

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(SFML_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

