#include <stdio.h>
#include <stdlib.h>
#include "Image.h"

struct string{
  int size;
  char* head;
};


void _double_string(struct string* str){
  str->head = realloc(str->head, str->size*2);
  str->size *= 2;
}
int intPow(int base, int exp){
  int output = base;
  if(exp == 0){
    return 1;
  }
  for(int i = 1; i<exp; i++){
    output = output*base;
  }
  return output;
}

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

struct string* init_string(char* str){
  struct string* output = (struct string*)malloc(sizeof(struct string)); //allocates string struct on heap
  
  output->size = str_length(str)*sizeof(char)*2;
  output->head = (char *)malloc(output->size);
  int len = str_length(str);
  for(int i = 0; i<len; i++){
    output->head[i] = str[i];
  }
  return output;
}
void addChar(struct string* str, char letter){
  int length = str_length(str->head);

  int new_size = length+sizeof(letter); 
  //resize to prevent segfault
  while(new_size > str->size){
    _double_string(str);
  }
  str->head[length-1] = letter;
  str->head[length] = '\0';
}
void stringAppend(struct string* str, const char* _concat_string){
  int length1 = str_length(str->head); //length of inital string
  int length2 = str_length(_concat_string); //length of appended string
  
  int new_size = (length1+length2);
  new_size = new_size - 1; //this adjusts for null char
  new_size = new_size*sizeof(char);
  while(new_size > str->size){ //prevents seg faults by multible checks
    _double_string(str);
  }
  int starting_point = length1-1; //the minus one makes sure to overwrite old null bit;
  for(int i = 0; i<length2; i++){
    str->head[starting_point] = _concat_string[i];
    starting_point++;
  }
}

void print(struct string* str){
  printf("%s",str->head);
  printf("\n");
  printf("%d", str->size);
}




int main(int argc, char* argv[]) {
  Image img;

  if(argv[1] == NULL){
    printf("filename needed as first argument\n");
    exit(1);
  }
  const char* src = argv[1]; //sets variable src to inputed filename
  Image_load(&img, src); //load image given by command line
  int output = 0;
  struct string* text = init_string("");

  for(int i = 0; i<img.size; i++){ //loop through image data
    int pixel = (int) img.data[i];
    if(i> 0 && i%8 == 0){ //one bit is read
      if(output == 0){ //output having the decimal value of 0 would be the same as a null byte
        break; //so exit
      }
      addChar(text, (char)output); //add char to dynamically sized string struct
      output = 0; //reset charictor counter once 8 bits have been read
    }
    if((pixel&1) == 1){ //check to see if bit is a one
      output+=intPow(2, 8-((i%8)+1)); //add 2^position in string
    }
  }
  printf("%s", text->head);
}