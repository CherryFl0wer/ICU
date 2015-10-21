CC=clang
  
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS=

SRC1= db.c  
OBJ1= ${SRC1:.c=.o} 

all: db

db:${OBJ1}
	${CC} ${OBJ1} ${CFLAGS} ${LDLIBS} -o db

clean:
	rm -f db
	rm -f *.o *~
