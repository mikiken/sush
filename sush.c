#include "sush.h"
bool is_loop;

void sush_loop() {
  is_loop = true;

  printf("\nIrasshaimase! sush ver. 1.0.0\n\n");
  do {
    printf("\x1b[32msush @\x1b[0m ");
    char *line = read_line();
    if (line) {
      Token *input_token = tokenize(line);
      execute(input_token);
    }
  } while (is_loop);

  return;
}

int main(int argc, char const *argv[]) {
  sush_loop();
  return 0;
}
