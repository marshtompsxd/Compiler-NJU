#include "text.h"
#include "../common.h"
#include <string.h>

int StrToInt(char *text) {
  long len = strlen(text);
  if (text[0] == '0') {
    if (len == 1)
      return 0;
    else if (text[1] == 'x' || text[1] == 'X')
      return (int)strtol(text, NULL, 16);
    else
      return (int)strtol(text, NULL, 8);
  } else
    return (int)strtol(text, NULL, 10);
}
