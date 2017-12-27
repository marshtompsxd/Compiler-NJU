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



run: syntax lexical compiler
	./compiler test/lab4/1.cmm

test: syntax lexical compiler
	cd test/lab4/ && ../../compiler `ls *.cmm | sort -n`

compile: clean syntax lexical compiler

debug: clean debug_compile

debug_compile: CFLAGS += -DYYDEBUG=1

debug_compile: compile

lexical:
	cd lexical_syntax && flex --header-file=lex.yy.h lexical.l

syntax:
	cd lexical_syntax && bison -d -v syntax.y

compiler:
	gcc main.c lexical_syntax/syntax.tab.c lexical_syntax/lex.yy.c lexical_syntax/ParsingNode.c lexical_syntax/text.c \
	semantic/semantic.c semantic/list.c semantic/check.c intercode/ICTable.c intercode/InterCode.c intercode/optimization.c ${CFLAGS} -lfl -ly -o compiler

clean:
	rm -f compiler
