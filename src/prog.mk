${PROG}:${OFILES}
	$(IBMRATIONAL) ${CPP} ${DEBUG} ${LFLAGS} ${LIBS} ${OFILES} -o $@

%.o:%.cpp
	${CPP} ${DEBUG} ${DEFS} ${CFLAGS} ${INCLUDES} -c $< -o $@



clean:
	${RM} *~
	${RM} *.o
	${RM} -r ${PROG}
	${RM} -r ${OFILES}


