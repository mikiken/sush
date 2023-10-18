#include "sush.h"
#include <time.h>

void neko(Token *cur) {
  if (cur->next->kind != TK_STR) {
    printf("\x1b[31mneko: Sumimasen! Please enter the file path.\n\x1b[0m");
    return;
  }

  cur = cur->next;

  while (cur->kind == TK_STR) {
    char *file_name = malloc(sizeof(char) * cur->len);
    memcpy(file_name, cur->start, cur->len);
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
      printf("\x1b[31mneko: Sumimasen! Cannot open the file...\n\x1b[0m");
      return;
    }
    char c;
    while ((c = fgetc(fp)) != EOF)
      printf("%c", c);
    fclose(fp);
    free(file_name);
    cur = cur->next;
  }

  return;
}

void take(Token *cur) {
  if (cur->next->kind != TK_STR) {
    printf("\x1b[31mtake: Sumimasen! Please enter the file path.\n\x1b[0m");
    return;
  }
  if (cur->next->next->kind != TK_STR) {
    printf("\x1b[31mtake: Please enter the word you want to find.\n\x1b[0m");
    return;
  }

  cur = cur->next;

  {
    char *file_name = malloc(sizeof(char) * cur->len);
    memcpy(file_name, cur->start, cur->len);
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL) {
      printf("\x1b[31mtake: Sumimasen! Cannot open the file...\n\x1b[0m");
      return;
    }
    cur = cur->next;
    char *word = malloc(sizeof(char) * cur->len);
    memcpy(word, cur->start, cur->len);

    char line[MAX_LINE_SIZE];
    bool is_match = false;
    while (fgets(line, MAX_LINE_SIZE, fp)) {
      if (strstr(line, word)) {
        printf("%s", line);
        is_match = true;
        continue;
      }
    }
    if (!is_match)
      printf("\x1b[31mtake: \"%s\" was not found in \"%s\".\n\x1b[0m", word, file_name);
    
    fclose(fp);
    free(file_name);
    free(word);
  }
  
  return;
}

void omakase(Token *cur) {
  if (cur->next->kind != TK_NUM) {
    printf("\x1b[31momakase: Please enter two integers a,b such as a < b.\n\x1b[0m");
    return;
  }

  int a = cur->next->val;
  int b = cur->next->next->val;

  if (a >= b) {
    printf("\x1b[31momakase: Please enter two integers a,b such as a < b.\n\x1b[0m");
    return;
  }

  srand((unsigned int)time(NULL));
  printf("%d\n", a + (int)(rand() * (b - a + 1.0) / (1.0 + RAND_MAX)));

  return;
}

void execute(Token *input_token) {
  Token *cur = input_token;

  switch (cur->kind) {
    case TK_NEKO:
      neko(cur);
      return;
    case TK_TAKE:
      take(cur);
      return;
    case TK_OMAKASE:
      omakase(cur);
      return;
    case TK_OAISO:
      is_loop = false;
      printf("\nAriarashita!\n\n");
      return;
    case TK_STR:
      printf("\x1b[31mSumimasen! I don't know that command...\n\x1b[0m");
      return;  
    default:
      return;
  }
}