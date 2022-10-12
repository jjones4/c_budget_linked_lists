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
TARGET = c_budget_dynamic_strings

all: $(TARGET)
  
$(TARGET): c_budget_dynamic_strings.o c_budget_menus.o c_budget_validation.o c_budget_read_input.o c_budget_crud_operations.o
	$(CC) $(CFLAGS) -o c_budget_dynamic_strings c_budget_dynamic_strings.o c_budget_menus.o c_budget_validation.o c_budget_read_input.o c_budget_crud_operations.o

c_budget.o: $(TARGET).c c_budget_menus.c c_budget_validation.c c_budget_read_input.c c_budget_crud_operations.c
	$(CC) $(CFLAGS) -c c_budget_dynamic_strings.c

c_budget_crud_operations.o: c_budget_crud_operations.c c_budget_crud_operations.h
	$(CC) $(CFLAGS) -c c_budget_crud_operations.c

c_budget_menus.o: c_budget_menus.c c_budget_menus.h
	$(CC) $(CFLAGS) -c c_budget_menus.c

c_budget_validation.o: c_budget_validation.c c_budget_validation.h boolean.h
	$(CC) $(CFLAGS) -c c_budget_validation.c

c_budget_read_input.o: c_budget_read_input.c c_budget_read_input.h
	$(CC) $(CFLAGS) -c c_budget_read_input.c
	
clean:
	$(RM) $(TARGET)

