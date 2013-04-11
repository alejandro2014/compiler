#Script created automatically on Wed Apr 10 21:55:16 BST 2013
#If you want to add parameters, modify the file auto.conf

EXE=language
CC=gcc

MAINDIR=/home/alejandro/programs/javaCompiler
SRCPATH=${MAINDIR}/src
OBJPATH=${MAINDIR}/obj
BINPATH=${MAINDIR}/bin

OPTC=
OPTL=

OBJ1=main
OBJ2=parser
OBJ3=parserTest
OBJ4=transitionsTable
OBJ5=transitionsTableTest
OBJ= ${OBJPATH}/${OBJ1}.o ${OBJPATH}/${OBJ2}.o ${OBJPATH}/${OBJ3}.o ${OBJPATH}/${OBJ4}.o ${OBJPATH}/${OBJ5}.o

${BINPATH}/${EXE}: ${OBJ}
	${CC} ${OBJ} -o ${BINPATH}/${EXE} ${OPTL}

${OBJPATH}/main.o: ${SRCPATH}/main.c
	${CC} -c ${SRCPATH}/main.c -o ${OBJPATH}/main.o ${OPTC}

${OBJPATH}/parser.o: ${SRCPATH}/parser.c
	${CC} -c ${SRCPATH}/parser.c -o ${OBJPATH}/parser.o ${OPTC}

${OBJPATH}/parserTest.o: ${SRCPATH}/parserTest.c
	${CC} -c ${SRCPATH}/parserTest.c -o ${OBJPATH}/parserTest.o ${OPTC}

${OBJPATH}/transitionsTable.o: ${SRCPATH}/transitionsTable.c
	${CC} -c ${SRCPATH}/transitionsTable.c -o ${OBJPATH}/transitionsTable.o ${OPTC}

${OBJPATH}/transitionsTableTest.o: ${SRCPATH}/transitionsTableTest.c
	${CC} -c ${SRCPATH}/transitionsTableTest.c -o ${OBJPATH}/transitionsTableTest.o ${OPTC}
clean:
	rm -f ${OBJPATH}/* ${BINPATH}/${EXE}
