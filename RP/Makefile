
SENSOR=bmp180
FUNCTIONS=functions

all:
	gcc -Wall -c $(FUNCTIONS).c -o $(FUNCTIONS).o -lm
	gcc -Wall -c $(SENSOR).c -o $(SENSOR).o -lm
	gcc -Wall $(FUNCTIONS).o $(SENSOR).o lcd_bmp.c -o lcd_bmp -lm

clean:
	rm *.o > /dev/null 2>&1 &
