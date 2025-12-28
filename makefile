TARGET := jkcal
SRC := $(wildcard *.c) # all cpp files
OBJDIR := obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o) # obj is all .o files, their names will be the source files but replace .cpp with .o


all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -o $(TARGET) $(OBJ) -lcjson

$(OBJDIR)/%.o: %.c # % matches any file name, %< is the dependency, $@ is the target
	gcc -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)