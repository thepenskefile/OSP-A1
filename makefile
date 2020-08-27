SOURCES=process.c queue.c scheduler.c clock.c scheduler_options.c
HEADERS=process.h queue.h scheduler.h clock.h scheduler_options.h utility.h
PROGRAM=scheduler
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)

all:
	gcc $(FLAGS) -o $(PROGRAM) $(SOURCES)

clean:
	rm $(PROGRAM)

archive:
	zip $(USER)-OSPA1T2 $(SOURCES) $(HEADERS) Makefile