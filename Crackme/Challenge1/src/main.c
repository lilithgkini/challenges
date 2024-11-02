#include <stdio.h>
#include <string.h>
#include <unistd.h>

char SECRET[38] = "\x83\x4a\x64\x91\x25\x59\xef\x06\xfd\xa4\x2c\x20\x03\x45"
                  "\xb7\x57\x8f\xc4\x49\x18\x50\x2e\x70\x16\xc6\x94\xf4\xf6"
                  "\x01\xe0\x7b\xfd\x68\xa1\xb8\x4f\xc0\x30";

int main() {
  unsigned char buf[38] = {0};
  printf("Enter the password:\n");

  // taking user input
  read(0, buf, 38);
  printf("\n");

  // mangling it

  // swap index 1 with 3
  char tmp = buf[3];
  buf[3] = buf[1];
  buf[1] = tmp;

  // xor modulo 2 with key 0x2aec
  for (int i = 0; i < 38; i++) {
    int mod = i % 2;
    switch (mod) {
    case 0:
      buf[i] = buf[i] ^ 0x2a;
      break;
    case 1:
      buf[i] = buf[i] ^ 0xec;
      break;
    }
  }

  // reverse
  for (int i = 0; i < 19; i++) {
    tmp = buf[i];
    buf[i] = buf[37 - i];
    buf[37 - i] = tmp;
  }

  // xor modulo 6 with key 0x011cb11c4cd5
  for (int i = 0; i < 38; i++) {
    int mod = i % 6;
    switch (mod) {
    case 0:
      buf[i] = buf[i] ^ 0x01;
      break;
    case 1:
      buf[i] = buf[i] ^ 0x1c;
      break;
    case 2:
      buf[i] = buf[i] ^ 0xb1;
      break;
    case 3:
      buf[i] = buf[i] ^ 0x1c;
      break;
    case 4:
      buf[i] = buf[i] ^ 0x4c;
      break;
    case 5:
      buf[i] = buf[i] ^ 0xd5;
      break;
    }
  }

  // xor modulo 3 with key 0x7384b7
  for (int i = 0; i < 38; i++) {
    int mod = i % 3;
    switch (mod) {
    case 0:
      buf[i] = buf[i] ^ 0x73;
      break;
    case 1:
      buf[i] = buf[i] ^ 0x84;
      break;
    case 2:
      buf[i] = buf[i] ^ 0xb7;
      break;
    }
  }

  // swap indexes 12 with 20
  tmp = buf[20];
  buf[20] = buf[12];
  buf[12] = tmp;

  // reverse
  for (int i = 0; i < 19; i++) {
    tmp = buf[i];
    buf[i] = buf[37 - i];
    buf[37 - i] = tmp;
  }

  // xor modulo 5 with key 0x29b3f159d5
  for (int i = 0; i < 38; i++) {
    int mod = i % 5;
    switch (mod) {
    case 0:
      buf[i] = buf[i] ^ 0x29;
      break;
    case 1:
      buf[i] = buf[i] ^ 0xb3;
      break;
    case 2:
      buf[i] = buf[i] ^ 0xf1;
      break;
    case 3:
      buf[i] = buf[i] ^ 0x59;
      break;
    case 4:
      buf[i] = buf[i] ^ 0xd5;
      break;
    }
  }

   // comparing it with the secret
  int cmp = memcmp(buf, SECRET, 38);
  if (!cmp) {
    printf("Correct password\n");
  } else {
    printf("Wrong password\n");
  }
  return 0;
}
