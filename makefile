all : bits bytes

bits : bits.c
	gcc -O3 -Wno-unused-result bits.c -o bits

bytes : bytes.c
	gcc -O3 -Wno-unused-result bytes.c -o bytes
