#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
static bool gen_success;

// this should be enough
static char buf[99999];
uint32_t choose(uint32_t num){
	return rand()%num;
}
void strcatt(char* buf, char*s){
	if(strlen(buf)+strlen(s)<99999)
		strcat(buf,s);
	else
	   gen_success=false;
}
void gen_num(){
	uint32_t value=rand()%20;
	char string[8];
	sprintf(string,"%u",value);
	strcatt(buf,string);
}
void gen_left(){
	strcatt(buf,"(");
}
void gen_right(){
	strcatt(buf,")");
}
void gen_operator(){
	switch(choose(4)){
		case 0:
		       	strcatt(buf,"+");
			break;
                case 1:
                        strcatt(buf,"-");
                        break;

                case 2:
                        strcatt(buf,"*");
                        break;

                case 3:
                        strcatt(buf,"/");
                        break;
/*
                case 4:
                        strcat(buf,"!=");
                        break;
                case 5:
                        strcat(buf,"==");
                        break;
                case 6:
                        strcat(buf,"&&");
                        break;*/
	}
}






static inline void gen_rand_expr() {
  switch(choose(3)){
	  case 0:
		  gen_num();
		  break;
	  case 1:
		  gen_left();
		  gen_rand_expr();
		  gen_right();
		  break;
	case 2:
		  gen_rand_expr();
		  gen_operator();
		  gen_rand_expr();
		  break;
  }
}

static char code_buf[99999];
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int h=0;
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf,0,99999);
    gen_success=true;
    gen_rand_expr();
    if(!gen_success)
	    continue;
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
  //  printf("%s",code_buf);
    fclose(fp);
 //      system("gcc /tmp/.code.c -o /tmp/.expr > out");
   FILE *f=popen("gcc -W /tmp/.code.c -o /tmp/.expr","r");
   if(f==NULL){
     exit(-1);
   :  }
    char warning[100];
    memset(warning,0,100);
    while(fgets(warning,sizeof(warning),f)!=NULL){
       printf("%d\n",strlen(warning));

       if(strlen(warning)!=0){
	    printf("%s",warning);
	    break;
    }
    }
  
    pclose(f);
    if(strlen(warning)!=0)
	    continue;
    
    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
//  printf("%d\n",h);
  return 0;
}
