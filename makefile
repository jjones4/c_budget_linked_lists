# the compiler: gcc for our C program, define as g++ for C++
CC = gcc

# compiler flags:
# -g			adds debugging information to the executable file
# -Wall			turns on most, but not all, compiler warnings
# -Wextra		additional warnings
# -O			used with Wall for strongest warnings
# -W			turn on additional compiler warnings
# -Wno-unused-result	turn off warnings for scanf's unused return value
# -pedantic		issue warnings required by C standard
# -ansi			turn off nonstandard C features; enable others
# -std=c89		compiler checks for c89 version

CFLAGS = -g -Wall -Wextra -O -W -pedantic -ansi -std=c89

# the build target executable:
TARGET = c_budget_linked_lists

all: $(TARGET)
  
$(TARGET): c_budget_linked_lists.o menus.o validation.o read_input.o crud_operations.o
	$(CC) $(CFLAGS) -o c_budget_linked_lists c_budget_linked_lists.o menus.o validation.o read_input.o crud_operations.o

c_budget_linked_lists.o: $(TARGET).c menus.c validation.c read_input.c crud_operations.c
	$(CC) $(CFLAGS) -c c_budget_linked_lists.c

crud_operations.o: crud_operations.c crud_operations.h
	$(CC) $(CFLAGS) -c crud_operations.c

menus.o: menus.c menus.h
	$(CC) $(CFLAGS) -c menus.c

validation.o: validation.c validation.h boolean.h
	$(CC) $(CFLAGS) -c validation.c

read_input.o: read_input.c read_input.h
	$(CC) $(CFLAGS) -c read_input.c
	
clean:
	$(RM) $(TARGET)

