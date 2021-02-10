TARGET = sushi
OBJS = sushi.o sushi_read.o sushi_history.o

CFLAGS = -Wall -pedantic -Wextra -Wundef -Werror -Wno-unused -g \
	-Wno-unused-result

all: $(TARGET)

sushi: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) #-lefence

sushi.o: sushi.c sushi.h

sushi_read.o: sushi_read.c sushi.h

sushi_history.o: sushi_history.c sushi.h

clean:
	rm -f $(OBJS) $(TARGET)

vg: all
	clear
	valgrind --leak-check=full ./sushi
