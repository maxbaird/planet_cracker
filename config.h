#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdbool.h>

#define FILE_NAME_LENGTH 64

typedef struct config{
  size_t MAX_WORD_LENGTH;
  size_t MAX_WORDS_PER_ROW;
  size_t WORD_COLUMNS_PER_ROW;
  bool SORT_ASCENDING;
  char LEXIS_FILE[FILE_NAME_LENGTH];
}Config;

Config getConfig();

#endif /* __CONFIG_H__ */
