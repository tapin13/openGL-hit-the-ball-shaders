CC=gcc
LDLIBS=-lglfw  -lGLEW -lGL -lm

all: hittheball

hittheball: hittheball.o wall.o bat.o ball.o matrixMath.o loadShader.o
	$(CC) loadShader.o matrixMath.o wall.o bat.o ball.o hittheball.o  $(LDLIBS) -o hittheball

hittheball.o: hittheball.c
	$(CC) $(LDLIBS) -c hittheball.c

wall.o: wall.c
	$(CC) $(LDLIBS) -c wall.c
	
bat.o: bat.c
	$(CC) $(LDLIBS) -c bat.c
	
ball.o: ball.c
	$(CC) $(LDLIBS) -c ball.c
	
matrixMath.o: common/matrixMath.c
	$(CC) $(LDLIBS) -c common/matrixMath.c
	
loadShader.o: common/loadShader.c
	$(CC) $(LDLIBS) -c common/loadShader.c
	
clean:
	rm -f *.o hittheball
	
.PHONY: all clean