#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]){
  if (argc == 0){
    return 1;
  }
  FILE *fptr = fopen(argv[1], "r+");
  uint8_t *fbyte;
  fseek(fptr, 0L, SEEK_END);
  int len = ftell(fptr);
  rewind(fptr);
  for (int i = 0; i < len; i++){
    printf("0x%02x ", *fbyte);
    fread(&fbyte, 1, 1, fptr);
    if (i % 4 == 0){
      printf("\n");
    }
  }
  fclose(fptr);
  return 0;
}
