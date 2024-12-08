TARGET = bin/final
SRC = $(wildcard src/*.c)

# Patsubst will execute a pattern substitution and convert all src/\*.c to obj/\*.o
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*

# $? represents a list of all input files given as a target
# $< represents a single file given as a target
# $@ represents the target of the rule
$(TARGET): $(OBJ)
	gcc -o $@ $?

obj/%.o: src/%.c
	gcc -c $< -o $@ -Include
