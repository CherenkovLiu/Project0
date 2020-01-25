target = test

objs = obj/test.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ -o $@ -c $<

main: $(objs)
	g++ -o $(target) $(objs)

run: $(target).exe
	./$(target)

auto:
	make
	make clean
	clear
	./$(target)

.PHONY: clean
clean:
	rm -rf obj