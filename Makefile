CFLAGS=-std=c11 -g -static
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)

sush: $(OBJS)
				$(CC) -o sush $(OBJS) $(LDFLAGS)

$(OBJS): sush.h

clean:
				rm -f 9cc *.o *~ tmp*

.PHONY: clean