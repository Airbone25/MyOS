char* video = (char*)0xB8000;

int row = 0;
int col = 0;

void putchar(char c){
  if(c == '\n'){
    col = 0;
    row++;
    return;
  }
  if(col>=80){
    col = 0;
    row++;
  }
  int pos = ((row*80)+col)*2;
  video[pos] = c;
  video[pos+1] = 0x07;
  col++;
}

void print(const char* s){
  while(*s){
    putchar(*s++);
  }
}

void kernel_main(){
	for(int i=0;i<30;i++)
    print("Hello\n");
  print("This is MyOS");
	while(1);
}
