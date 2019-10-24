CC ?= gcc
CFLAGS = -O2 -flto

SRC=main.c rngd_linux.c

feeder: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o feeder $(SRC)

.PHONY: clean

clean:
	rm -f feeder
