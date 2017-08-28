Driver.o: *.c
	gcc -o made *.c
run: Driver.o
	./made
clean:
	rm -f made *.txt
