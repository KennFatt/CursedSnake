CXX = clang++							# Compiler
CXX_FLAGS = -Wall -g -std=c++11			# Compiler flags
LIBRARY = ncurses 						# Required lib

OUT_EXECUTE_FOLDER = out 				# Output folder
OUT_OBJECT_FOLDER = out/obj 			# Output object folder
OUT_EXECUTE_FILE = cursedsnake_build 	# Execute file name

main.o: main.cpp
	${CXX} ${CXX_FLAGS} -c -o ${OUT_OBJECT_FOLDER}/$@ $<

clean:
	# Clear all object files.
	rm -rf out/obj/*.o