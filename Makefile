# Compiler
CXX = clang++
# Compiler flags
CXX_FLAGS = -Wall -g -std=c++11
# Required lib
LIBRARY = ncurses

# Output folder
OUT_EXECUTE_FOLDER = out
# Output object folder
OUT_OBJECT_FOLDER = out/obj
# Execute file name
OUT_EXECUTE_FILE = cursedsnake_build

all: main.o appdelegate.o
	${CXX} ${CXX_FLAGS} -o ${OUT_EXECUTE_FOLDER}/${OUT_EXECUTE_FILE} \
	${OUT_OBJECT_FOLDER}/*.o -l${LIBRARY}

appdelegate.o: src/appdelegate.cpp src/appdelegate.h
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

main.o: main.cpp
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

clean:
	# Clear all object files.
	rm -rf out/obj/*.o