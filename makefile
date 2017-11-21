CFLAGS = -g \
		-O0 \
		-std=c11 \
		-Wall \
		-Wextra \
		-Wpedantic \
		-Werror \
		-Wno-unused-function \
		-Wno-sign-compare \
		-D_GNU_SOURCE



run: syntax lexical parser
	./parser test/samples/1.cmm

test1: syntax lexical parser
	./parser test/p1/*.cmm 

test2: syntax lexical parser
	./parser test/p2/*.cmm

compile: clean syntax lexical parser

debug: clean debug_compile

debug_compile: CFLAGS += -DYYDEBUG=1

debug_compile: compile

lexical:
	cd lexical_syntax && flex --header-file=lex.yy.h lexical.l

syntax:
	cd lexical_syntax && bison -d -v syntax.y

parser:
	gcc main.c lexical_syntax/syntax.tab.c lexical_syntax/lex.yy.c lexical_syntax/ParsingNode.c lexical_syntax/text.c semantic/semantic.c ${CFLAGS} -lfl -ly -o parser

clean:
	rm -f parser
