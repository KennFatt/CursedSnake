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

all: main.o appdelegate.o vector2.o food.o snake.o
	${CXX} ${CXX_FLAGS} -o ${OUT_EXECUTE_FOLDER}/${OUT_EXECUTE_FILE} \
	${OUT_OBJECT_FOLDER}/*.o -l${LIBRARY}

snake.o: src/entity/snake.cpp src/entity/snake.h src/entity/entity.h src/math/facingdirection.h
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

food.o: src/entity/food.cpp src/entity/food.h src/entity/entity.h
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

vector2.o: src/math/vector2.cpp src/math/vector2.h
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

appdelegate.o: src/appdelegate.cpp src/appdelegate.h
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

main.o: main.cpp
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

clean:
	# Clear all object files.
	rm -rf out/obj/*.o