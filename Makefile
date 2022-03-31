EXE = torbit
CXX = g++
FLG = -std=c++14 

SRC = src
BLD = bld

# wildcard: current directory
CPP = ${wildcard ${SRC}/*.cpp} ${wildcard ${PSN}/*.cpp}
HPP = ${wildcard ${SRC}/include/*.hpp}
# patsubst: replacs *.cpp by *.o
OBJ = ${patsubst ${SRC}/%.cpp,${BLD}/%.o,${CPP}}

# target: dependency table (if changed, execute the following command)
# 	command...
# $< : first object in the dependency table
# $@ : target
${BLD}/%.o: ${SRC}/%.cpp ${HPP}
	${CXX} ${FLG} -c $< -o $@
${EXE}: ${OBJ}
	${CXX} ${OBJ} ${FLG} -o $@

clean:
	rm -f ${OBJ} ${EXE}
