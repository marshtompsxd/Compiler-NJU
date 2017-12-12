cmake_minimum_required(VERSION 3.6)
project(Compiler)
include_directories(${CMAKE_CURRENT_BINARY_DIR} lexical_syntax semantic)

set(CMAKE_C_STANDARD 11)

find_package(FLEX)
find_package(BISON)
flex_target(Scanner lexical_syntax/lexical.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/lex.yy.h)
bison_target(Parser lexical_syntax/syntax.y ${CMAKE_CURRENT_BINARY_DIR}/syntax.tab.c COMPILE_FLAGS --defines=${CMAKE_CURRENT_BINARY_DIR}/syntax.tab.h)
add_flex_bison_dependency(Scanner Parser)

set(SOURCE_FILES ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS}
        lexical_syntax/lexical.l lexical_syntax/syntax.y lexical_syntax/ParsingNode.c lexical_syntax/text.c
        semantic/semantic.c semantic/check.h semantic/list.h semantic/symbol_table.h intercode/InterCode.c intercode/InterCode.h
        main.c intercode/IC.h common.h semantic/list.c semantic/check.c intercode/ICTable.c intercode/ICTable.h)
add_executable(cproject3 ${SOURCE_FILES})
target_link_libraries(cproject3 ${FLEX_LIBRARIES} ${BISON_LIBRARIES})