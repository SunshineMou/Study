OBJECTS = calculator_ADT.o stack_ADT.o
APP = calculator
CROSS_COMPILER =
CC = $(CROSS_COMPILER)gcc

$(APP): $(OBJECTS)
		$(CC) -o $(APP) $(OBJECTS)

calculator_ADT.o: stack_ADT.h

stack_ADT.o: stack_ADT.h

clean:
		rm *.o
