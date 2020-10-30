#include <stdio.h>
#include <stdlib.h>
#include "Image.h"

int main(int argc, char* argv[]){
  Image img;
  const char* src = argv[1];
  Image_load(&img, src);

  for(int i = 0; i<img.size; i++){
    printf("%d\n", (int)img.data[i]);
  }

  return 0;
}