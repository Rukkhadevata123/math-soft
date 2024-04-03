CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm
OBJS = main.o fractal.o

all: main input.png output.mp4

main: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

input.png: main
	./main 1024 1024 10
	for file in mandelbrot_*.bmp; do \
		convert "$$file" "$${file%.bmp}.png"; \
	done

output.mp4: input.png
	ffmpeg -framerate 60 -i mandelbrot_%03d.png -c:v libx264 -profile:v high -crf 18 -pix_fmt yuv420p output.mp4

clean:
	rm -f *.o main *.bmp *.png output.mp4

.PHONY: all clean