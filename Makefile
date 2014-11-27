CXX = g++
CXXFLAGS = -Wall -MMD -lX11
EXEC = ss5k
OBJECTS = main.o board.o square.o game.o window.o textdisplay.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
