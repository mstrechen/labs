all: compile cleanup run

compile: yacc lex clang

run:
	./build/calculator.out

yacc:
	yacc -d lab1.y

lex:
	lex -o lex.yy.c lab1.l

clang:
	clang++ --std=c++11 \
		-Wno-writable-strings \
		-Wno-deprecated \
		lex.yy.c y.tab.c -o build/calculator.out -ly -ll 

cleanup:
	rm lex.yy.c y.tab.c y.tab.h