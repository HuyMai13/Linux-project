CFLAGS = gcc -g
OBJ = cs3423p8Driver.o cs3423p8.o errExit.o
INCLUDES = cs3423p8.h

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c ${INCLUDES}
	${CFLAGS} -c $< 

%.o: %.cpp
	${CFLAGS} -c $<

# Build p1 based on the required .o files
pell: ${OBJ}
	${CFLAGS} -o pell ${OBJ}

clean:
	rm ${OBJ}