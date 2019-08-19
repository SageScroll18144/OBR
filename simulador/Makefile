src = $(wildcard src/*.c)
obj = $(src:.c=.o)

LDFLAGS = -lSDL2 -lm

main: $(obj)
	$(CC) -Wall -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) main
