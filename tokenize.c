#include "sush.h"
#include <ctype.h>

char *read_line() {
  char *line = malloc(sizeof(char) * MAX_LINE_SIZE);
  fgets(line, MAX_LINE_SIZE, stdin);
  return line;
}

bool is_keyword(char *p, char *keyword) {
  return strncmp(p, keyword, strlen(keyword)) == 0;
}

// Create a new token and connect it to cur
Token *new_token(TokenKind kind, Token *cur, char *start, char*end) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->start = start;
  tok->end = end;
  tok->len = end - start + 1;
  cur->next = tok;
  return tok;
}

// Tokenize user input
Token *tokenize(char *line) {
  char *p = line;
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while (*p) {
    // 空白文字をスキップ
    if (isspace(*p)) {
      p++;
      continue;
    }

    if (is_keyword(p, "neko")) {
      cur = new_token(TK_NEKO, cur, p, p+3);
      p += 4;
      continue;
    }

    if (is_keyword(p, "take")) {
      cur = new_token(TK_TAKE, cur, p, p+3);
      p += 4;
      continue;
    }

    if (is_keyword(p, "omakase")) {
      cur = new_token(TK_OMAKASE, cur, p, p+6);
      p += 7;
      continue;
    }

    if (is_keyword(p, "oaiso")) {
      cur = new_token(TK_OAISO, cur, p, p+4);
      p += 5;
      continue;
    }

    if (isdigit(*p)) {
      char *start = p;
      int value = strtol(p, &p, 10);
      cur = new_token(TK_NUM, cur, start, --p);
      p++;
      cur->val = value;
      continue;
    }

    {
      char *start = p;
      while (*p != ' ' && *p != '\n') {
        p++;
      }
      cur = new_token(TK_STR, cur, start, --p);
      p++;
      continue;
    }

  }

  cur = new_token(TK_EOF, cur, p, p);
  cur->len = 0;

  return head.next; // head is a dummy node, so the next node is returned
}
