CC    := gcc
CFLAG :=  -g -o
INPUT := ./in.txt
TARGET  := ./main

all: compute main
	$(TARGET) < $(INPUT)

main:
	$(CC) ./main.c $(CFLAG) $(TARGET)

compute:
	$(CC) ./compute.c $(CFLAG) ./compute

clean:
	rm $(TARGET) ./compute
