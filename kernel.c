char* video = (char*)0xB8000;

void print(const char* s){
  for(int i=0;s[i] != 0;i++){
    video[i*2] = s[i];
    video[i*2+1] = 0x07;
  }
}

void kernel_main(){
	
	print("Hello World From MyOS");
	print("Welcome");
	while(1);
}
