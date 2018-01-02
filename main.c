#include <stdio.h>


#include "lexical_syntax/ParsingNode.h"
#include "lexical_syntax/lex.yy.h"
#include "lexical_syntax/syntax.tab.h"
#include "semantic/semantic.h"
#include "intercode/IC.h"
#include "SPIM/spim.h"

static void ParsingFinalPhase(char* filename)
{
	if(!ParsingSwitch) 
	{
		printf("\033[31mParsing %s over(with syntax or lexical error).\033[0m\n", filename);
	}
	else
	{
		SyntaxOutput(ParsingRoot);
		printf("\033[32mParsing %s over(with no error).\033[0m\n", filename);
	}
}

static void SwitchInit()
{
    ParsingSwitch = SemanticSwitch = ICSwitch = true;
}

int main(int argc, char** argv)
{
	int i;
	if (argc <= 1)
	{
		printf("Please enter your c-minusminus file name.\n");
        return 1;
	}
	for (i = 1; i < argc; ++i)
	{
        SwitchInit();
		
		FILE* f = fopen(argv[i], "r");
		if (!f)
		{
			perror(argv[i]);
			return 1;
		}
		yyrestart(f);

#if YYDEBUG == 1
		yydebug = 1;
#endif
		yylineno = 1;
		//ParsingSwitch = true;

		// begin lexical and syntax analysis
		printf("Parsing %s begin...\n", argv[i]);
		yyparse();
		fclose(f);

		ParsingFinalPhase(argv[i]);

		// begin semantic analysis
		if(ParsingSwitch)
		{
			printf("Semantic analysis %s begin...\n", argv[i]);
			SemanticAnalysis(ParsingRoot);
			if(SemanticSwitch)
				printf("\033[32mSemantic analysis %s over(with no error).\033[0m\n", argv[i]);
			else
				printf("\033[31mSemantic analysis %s over(with semantic error).\033[0m\n", argv[i]);
		}

        if(SemanticSwitch)
        {
            printf("InterCode generation of %s begin...\n", argv[i]);
            char* codefile = (char*)malloc(strlen(argv[i]) + 3);
            strcpy(codefile, argv[i]);
            strcat(codefile, ".ir");
            InterCodeGenerator(codefile);
            if(ICSwitch)
                printf("\033[32mIntermediate code generation of %s over(with no error).\033[0m\n", argv[i]);
            else
                printf("\033[31mIntermediate code generation of %s over(with error).\033[0m\n", argv[i]);
        }


		if(ICSwitch)
		{
            printf("Machine Code generation of %s begin...\n", argv[i]);
            char* codefile = (char*)malloc(strlen(argv[i]) + 2);
            strcpy(codefile, argv[i]);
            strcat(codefile, ".s");
            MachineCodeGenerator(codefile);
            printf("\033[32mIntermediate code generation of %s over.\033[0m\n", argv[i]);
		}

        PostorderFreeParsingTree(ParsingRoot);
        printf("\n");

	}

	return 0;
}
