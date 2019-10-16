all : bits bytes

bits : bits.c
	gcc bits.c -o bits

bytes : bytes.c
	gcc bytes.c -o bytes
