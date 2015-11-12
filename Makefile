EXE=language
CC=gcc

SRCPATH=./src
OBJPATH=./obj
BINPATH=./bin

OPTC=-g
OPTL=

OBJ1=main
OBJ2=lexer
OBJ3=parser
OBJ4=transitionsTable
OBJ5=grammar
OBJ6=helper
OBJ= ${OBJPATH}/${OBJ1}.o ${OBJPATH}/${OBJ2}.o ${OBJPATH}/${OBJ3}.o ${OBJPATH}/${OBJ4}.o ${OBJPATH}/${OBJ5}.o ${OBJPATH}/${OBJ6}.o

${BINPATH}/${EXE}: ${OBJ}
	${CC} ${OBJ} -o ${BINPATH}/${EXE} ${OPTL}

${OBJPATH}/%.o: ${SRCPATH}/%.c
	${CC} ${OPTC} -c -o $@ $<

clean:
	rm -f ${OBJPATH}/* ${BINPATH}/${EXE}
