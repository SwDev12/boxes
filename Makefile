all: boxes

boxes: boxes.c
	gcc boxes.c -Wall -Werror -Wextra -o0 -o boxes

clean: boxes
	rm boxes
