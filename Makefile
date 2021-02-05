
comparador_out= comparador
coordinador_out= coordinador

comparador_headers = funciones.h
comparador_source  = $(comparador_headers:.h=.c) comparador.c
comparador_objects = $(comparador_source:.c=.o)	

coordinador_headers = funciones.h
coordinador_source  = $(coordinador_headers:.h=.c) coordinador.c
coordinador_objects = $(coordinador_source:.c=.o)		

CC     = gcc
CFLAGS = -Wall

depends = .depends

build : $(coordinador_out) 
build : $(comparador_out)

$(coordinador_out) : $(coordinador_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm		

$(comparador_out) : $(comparador_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm


$(objects) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(coordinador_source) $(coordinador_headers)
	@$(CC) -MM $(coordinador_source) > $@


clean :
	$(RM) $(coordinador_out) $(coordinador_objects) $(zipfile) $(depends)

.PHONY : build zip clean

sinclude $(depends)
