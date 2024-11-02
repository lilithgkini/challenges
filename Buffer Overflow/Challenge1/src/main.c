#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int challenge() {
  int size = 0;
  char buf[32] = {0};
  printf("Welcome to the chalenge!\n");
  printf("\n");
  printf("Insert input size: \n");
  scanf("%d", &size);
  assert(size);

  printf("Insert input: \n");
  read(0, buf, size);

  printf("You said: %s\n", buf);
  char *found = strstr(buf, "BACKDOOR");
  if (found) {
    printf("Triggering the backdoor..\n\n");
    challenge();
  }
  printf("\nGoodbye..\n");
  return 0;
}

int main() {
  challenge();
  return 0;
}
