CC=gcc
CF=-Wall -Wextra
LF=
TARGET=mkuf2

SRC=$(wildcard *.c)
INC=$(wildcard *.h)
OBJ=$(SRC:.c=.o)


$(TARGET): $(OBJ)
	@echo " Compile" $@
	@$(CC) $(OBJ) -o $@ $(LF)

%.o : %.c $(INC)
	@echo " Compile" $<
	@$(CC) $(CF) -c -o $@ $<

clean:
	@echo " Clean"
	@rm -f *.o
	@rm -f $(TARGET)

