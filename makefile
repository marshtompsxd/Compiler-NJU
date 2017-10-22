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
	./parser test/1.cmm

test: syntax lexical parser
	./parser test/samples/*.cmm 

ta : syntax lexical parser
	./parser test/A/*.cmm

tb : syntax lexical parser
	./parser test/B/*.cmm

compile: clean syntax lexical parser

debug: clean debug_compile

debug_compile: CFLAGS += -DYYDEBUG=1

debug_compile: compile

lexical:
	flex --header-file=lex.yy.h lexical.l

syntax:
	bison -d -v syntax.y

parser:
	gcc main.c syntax.tab.c lex.yy.c ParsingNode.c text.c ${CFLAGS} -lfl -ly -o parser

clean:
	rm -f parser
