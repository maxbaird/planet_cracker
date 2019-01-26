#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"
#include "board.h"
#include "blitzkrieg.h"

#define RESET       "\033[0m"              /* Reset to default */
#define BLACK       "\033[30m"             /* Black */
#define RED         "\033[31m"             /* Red */
#define GREEN       "\033[32m"             /* Green */
#define YELLOW      "\033[33m"             /* Yellow */
#define BLUE        "\033[34m"             /* Blue */
#define MAGENTA     "\033[35m"             /* Magenta */
#define CYAN        "\033[36m"             /* Cyan */
#define WHITE       "\033[37m"             /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define WORDS_PER_ROW 10

static size_t padding(size_t len){
  return (MAX_WORD_LEN - len) + 2;
}

static void printColumnHeaders(size_t start, size_t end){
  size_t i = 0;
  char str[8] = {'\0'};

  for(i = start; i < end; i++){
    sprintf(str, "[%zu]", i+1);
    fprintf(stdout, BOLDCYAN"[%zu]%*s"RESET, i+1, (int)padding(strlen(str)),"");
    memset(str, 0, sizeof str);
  }
  fprintf(stdout, "\n");
}

static size_t getLongestColumn(size_t start, size_t end, WordColumn *wc){
  size_t i = 0;
  size_t idx = 0;

  for(i = start; i < end; i++){
    if(wc[i].wordCount > idx){
      idx = wc[i].wordCount;
    }
  }
  return idx; //Return the index of the longest column
}

static int compareWords(const void *w1, const void *w2){
  Word *word1 = (Word *)w1;
  Word *word2 = (Word *)w2;

  return (int)word2->len - (int)word1->len;
}

static void sortColumns(size_t boardSize, WordColumn *wc){
  size_t i = 0;

  for(i = 0; i < boardSize; i++){
    qsort(wc->words, wc->wordCount, sizeof(Word), compareWords);
    wc++;
  }
}

void printWords(Board *board, WordColumn *wc, size_t colsPerLine){
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  size_t numPrintedRows = 0;
  size_t longestColumn = 0;
  size_t boardSize = getBoardSize(board);
  size_t colHeaderStart = 0;
  size_t colHeaderEnd = colHeaderStart + colsPerLine;

  sortColumns(boardSize, wc); //Print longest words first

  for(i = 0; i < boardSize; i+=colsPerLine){
    printColumnHeaders(colHeaderStart, colHeaderEnd);

    //This is later used as a loop control to ensure that
    //all words of the longest column is printed
    longestColumn = getLongestColumn(colHeaderStart, colHeaderEnd, wc);
    numPrintedRows = 0;

    for(j = 0; j < longestColumn; j++){
      if(numPrintedRows == WORDS_PER_ROW){ //Reprint column headers if necessary
        numPrintedRows = 0;
        fprintf(stdout, "\n"); //Go to new line before reprinting column headers
        printColumnHeaders(colHeaderStart, colHeaderEnd);
      }

      numPrintedRows++;

      //This loops prints a word under each column
      for(k = colHeaderStart; k < colHeaderEnd; k++){
        if(wc[k].wordCount > j){
          size_t len = strlen(wc[k].words[j].word);
          fprintf(stdout, "%s%*s", wc[k].words[j].word, (k==(colHeaderEnd)-1) ? 0: (int)padding(len),"");
        }else{//If the current column has no more words, print nothing
          fprintf(stdout, "%*s", (int)padding(0),"");
        }
      }
      fprintf(stdout, "\n"); //Move to new line to print another row of words
    }
    fprintf(stdout, "\n"); //Force remaining of columns onto new line

    colHeaderStart += colsPerLine; //More start column up by number of columns to print per line
    colHeaderEnd = colHeaderStart + colsPerLine; //Move end column up also
    colHeaderEnd = colHeaderEnd >= boardSize ? boardSize : colHeaderEnd; //Keep the end to the size of the board
  }
}
