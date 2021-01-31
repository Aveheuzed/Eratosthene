all : bits bytes rbits

bits : bits.c
	gcc -O3 -Wno-unused-result bits.c -o bits

rbits : rbits.c
	gcc -O3 -Wno-unused-result rbits.c -o rbits

bytes : bytes.c
	gcc -O3 -Wno-unused-result bytes.c -o bytes


benchmarks : all
	@echo 'Benchmarks up to'
	@cat ./bornesup
	@echo 'Benchmarking bits :'
	@time -p ./bits >/dev/null <./bornesup
	@echo 'Benchmarking rbits :'
	@time -p ./rbits >/dev/null <./bornesup
	@echo 'Benchmarking bytes :'
	@time -p ./bytes >/dev/null <./bornesup
