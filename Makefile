
CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = vm
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES := $(call rwildcard, ${SOURCEDIR} ,*.cpp)
#SOURCES := main.cpp ./controller/TerminalController.cpp ./mode/NormalMode.cpp ./model/Model.cpp ./model/VMModel/cpp
OBJECTS = ${SOURCES:.cpp=.o}
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
