target = main

objs = obj/main.o

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc -o $@ -c $<

main: $(objs)
	gcc -o $(target) $(objs)

run: $(target)
	./$(target)

.PHONY: clean
clean:
	rm -rf obj