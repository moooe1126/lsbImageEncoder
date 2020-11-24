#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include <math.h>

int str_length(const char* str){
/*get the length of a string including the null byte*/
  int i = 0;
  int count = 0;
  while((char)str[i] != '\0'){ //checks weather a char at a given place is a null bit
    count++;
    i++;
  }
  count++; //this is to account for the null byte at the end of a string
  return count;
}




int* string_to_bit_array(const char* str){
  /* converts string to int array of single digit bits and includes null byte*/
  int length = str_length(str);
  int bitSize = length*8; //1 char = 1 byte and their are 8 bits in a byte
  int* output = (int *)malloc(bitSize*sizeof(int)); //allocate the proper array size
  for(int i = 0; i<length; i++){
    int index = 0;
    int num = (int)str[i];
    while(index < 8){ //8 because there are 8 bits in an ascii value
      int bit = (num>>index)&1; //reads bits from least signifcant to most
      int position = (i*8)+(7-index); //gets correct position in output array for bit integer
      output[position] = bit; //sets position to bit
      index++;
    }
  }
  return output;
}

// shifts letters 
char* encrypt(int gkey, char* gData){
  int key = gkey;
  key = key % 255;

  char* data = gData;

  for (int i = 0; i < str_length(data) - 1; i++){
    data[i] = (data[i] + abs(key) );
  }
  return data;
}

int main(int argc, char* argv[]) {
  Image img_source;
  Image img_output;

  if(argv[1] == NULL){
    printf("filename needed as first argument\n");
    exit(1);
  }
  const char* src = argv[1]; //sets variable src to inputed filename

  if(argv[2] == NULL){
    printf("text to encode needed as secound argument");
    exit(1);
  }
  const char* msg = argv[2]; //gets msg to be hidden from input

  const char* outputname = "output.png";
  if(argv[3] != NULL){
    outputname = argv[3];
  }

  if(argv[4] != NULL){
    msg = encrypt(atoi(argv[4]), argv[2]);
  }
  
  Image_load(&img_source, src); //load image given by command line
  Image_create(&img_output, img_source.width, img_source.height, img_source.channels, true); //create output image of the same size
  
  int numberOfBits = str_length(msg)*8;
  int* bit_array = string_to_bit_array(msg); //this has to be freed later

  for(int i = 0; i<img_source.size; i++){
    if(i < numberOfBits){
      int new_data = (int)img_source.data[i];
      if(bit_array[i] == 0){
        new_data = new_data &(~1); //clear least signifcant bit
      }
      if(bit_array[i] == 1){
        new_data = 1|new_data; //set least signifcant bit
      }
      img_output.data[i] = (uint8_t)new_data; //set data after re casting it to a uint8_t
    }
    else{
      img_output.data[i] = img_source.data[i]; //otherwise just place the old data
    }
  }
  Image_save(&img_output, outputname);

  free(bit_array); //clean this up so its not on the heap forever
  

  return 0;
}