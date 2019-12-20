all : bits bytes

bits : bits.c
	gcc -O3 -Wno-unused-result bits.c -o bits

bytes : bytes.c
	gcc -O3 -Wno-unused-result bytes.c -o bytes


benchmarks :
	@echo 'Benchmarks up to'
	@cat ./bornesup
	@echo 'Benchmarking bits :'
	@time -p ./bits >/dev/null <./bornesup
	@echo 'Benchmarking bytes :'
	@time -p ./bytes >/dev/null <./bornesup
