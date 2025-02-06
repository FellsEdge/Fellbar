# See LICENSE file for copywrite and license details

NAME = fellbar
SRC = ${NAME}.c
OBJ = ${SRC:.c=.o}

# paths

PREFIX = /usr
LIBS = -L/usr/lib -lX11

# compiler / linker
CC = cc

all: ${NAME}

${NAME}: ${OBJ}
	@${CC} fellbar.c -o ${NAME} ${LIBS}

clean:
	@echo cleaning
	@rm -f ${NAME} ${OBJ}

install: all
	@echo installing executable to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${NAME} ${DESTDIR}${PREFIX}/bin/${NAME}
	
uninstall:
	@echo removing executable from ${DESTDIR}${PREFIX}/bin
	@rm -f ${NAME} ${DESTDIR}${PREFIX}/bin/${NAME}

.PHONY: all clean install uninstall
