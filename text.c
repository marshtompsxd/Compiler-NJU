#include <string.h>
#include "text.h"

static int HexStrToInt(char* text){
    int len = strlen(text);
    int i=2;
    int result = 0;
    while(i<len)
    {
        result*=16;
        char ch = text[i];
        if(ch>='0' && ch<='9')
            result+=ch-'0';
        else if(ch>='a' && ch<='f')
            result+=ch-'a'+10;
        else result+=ch-'A'+10;
        i++;
    }
    return result;
}

static int OctStrToInt(char* text){
    int len = strlen(text);
    int i=0;
    int result = 0;
    while(i<len)
    {
        result*=8;
        char ch = text[i];
        result+=ch-'0';
        i++;
    }
    return result;
}

static int DecStrToInt(char* text){
    int len = strlen(text);
    int i=0;
    int result = 0;
    while(i<len)
    {
        result*=10;
        char ch = text[i];
        result+=ch-'0';
        i++;
    }
    return result;   
}

int StrToInt(char* text){
    int len = strlen(text);
    if(text[0]=='0')
    {
        if(len==1)
            return 0;
        else if(text[1]=='x' || text[1]=='X')
            return HexStrToInt(text);
        else return OctStrToInt(text);
    }
    else return DecStrToInt(text);
}
