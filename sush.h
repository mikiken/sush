#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum TokenKind TokenKind;

enum TokenKind {
  TK_NEKO,    // cat
  TK_TAKE,    // grep
  TK_OMAKASE, // print random number between a and b
  TK_OAISO,   // exit
  TK_NUM,     // number
  TK_STR,     // string
  TK_EOF,     // terminal
};

typedef struct Token Token;

struct Token {
  TokenKind kind;
  char *start;
  char *end;
  int len;
  int val;
  Token *next;
};

#define MAX_LINE_SIZE 1024

char *read_line();
Token *tokenize();

extern bool is_loop;
void execute(Token *input_token);