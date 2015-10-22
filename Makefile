EXE=language
CC=gcc

SRCPATH=./src
OBJPATH=./obj
BINPATH=./bin

OPTC=-g
OPTL=

OBJ1=main
OBJ2=parser
OBJ3=parserTest
OBJ4=transitionsTable
OBJ5=transitionsTableTest
OBJ= ${OBJPATH}/${OBJ1}.o ${OBJPATH}/${OBJ2}.o ${OBJPATH}/${OBJ3}.o ${OBJPATH}/${OBJ4}.o ${OBJPATH}/${OBJ5}.o

${BINPATH}/${EXE}: ${OBJ}
	${CC} ${OBJ} -o ${BINPATH}/${EXE} ${OPTL}

${OBJPATH}/%.o: ${SRCPATH}/%.c
	${CC} ${OPTC} -c -o $@ $<

clean:
	rm -f ${OBJPATH}/* ${BINPATH}/${EXE}
