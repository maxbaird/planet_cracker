#ifndef __LEXIS_H__
#define __LEXIS_H__

#include <stdbool.h>

void loadLexis();
bool isWord(char *letters, size_t length);
void unloadLexis();

#endif /* __LEXIS_H__ */
