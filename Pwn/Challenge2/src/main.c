#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Globals
#define PORT 4444
char *messages[16] = {0};
int stored[16] = {0};
#define SIZE 1024
#define ARR_SIZE 1024

void challenge(FILE *in, FILE *out) {
  fprintf(
      out,
      "Welcome to the challenge! Commands: malloc/scanf/printf/free/quit.\n");
  char input[SIZE] = {0};
  int idx = 0;

  while (1) {
    if (fscanf(in, "%s", input) == EOF)
      break;
    if (strcmp(input, "quit") == 0)
      break;
    if (fscanf(in, "%d", &idx) == EOF)
      break;

    if ((idx < 0) || (idx > ARR_SIZE)) {
      fprintf(out, "Invalid index number\n");
      continue;
    }

    if (strcmp(input, "printf") == 0) {
      if (fprintf(out, "Message: %s\n", stored[idx] ? messages[idx] : "NONE") <
          0)
        break;
    } else if (strcmp(input, "malloc") == 0) {
      if (!stored[idx])
        messages[idx] = malloc(SIZE);
      stored[idx] = 1;
    } else if (strcmp(input, "free") == 0) {
      if (stored[idx])
        free(messages[idx]);
      stored[idx] = 0;
    } else if (strcmp(input, "scanf") == 0) {
      fscanf(in, "%1024s", stored[idx] ? messages[idx] : input);
    } else
      fprintf(out, "Wrong command %s %p\n", input, input);
  }
}

void *handle_connections(void *fd) {
  FILE *in = fdopen((int)fd, "r");
  FILE *out = fdopen((int)fd, "w");
  setvbuf(in, NULL, _IONBF, 0);
  setvbuf(out, NULL, _IONBF, 1);
  printf("Handling connection on fd: %d\n", (int)fd);
  challenge(in, out);
  printf("Closing connection on fd: %d\n", (int)fd);
  close((int)fd);
  pthread_exit(0);
}

int main() {

  // hanldiling the socket
  struct sockaddr_in addressInfo = {0};
  addressInfo.sin_family = AF_INET;
  addressInfo.sin_addr.s_addr = htonl(INADDR_ANY);
  addressInfo.sin_port = htons(PORT);

  // creating the socket
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("socket");
    return -1;
  }

  // setting sockopt
  int optval = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
    perror("setsockopt");
    close(fd);
    return -1;
  }

  // binding
  if (bind(fd, (struct sockaddr *)&addressInfo, sizeof(addressInfo)) == -1) {
    perror("bind");
    close(fd);
    return -1;
  }
  // listening
  if (listen(fd, 0) == -1) {
    perror("listen");
    close(fd);
    return -1;
  }
  printf("Listening on port %d\n", PORT);

  // the accept loop
  while (1) {
    pthread_t thread_id;
    long client_fd = accept(fd, NULL, NULL);
    pthread_create(&thread_id, NULL, handle_connections, (void *)client_fd);
  }
  return 0;
}
