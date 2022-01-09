#include "klib.h"
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap,fmt);
  char s[1000];
  int ll=vsprintf(s,fmt,ap);
  va_end(ap);
  int i=0;
  while(s[i]!='\0'){
  _putc(s[i]);
  i++;
  }
  return ll;
 // return 0;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
    char *t=out;
    char*s;
    while(*fmt!='\0'){
    char number[20];
    int flag=0;
    int count=0;
    int integer;
        if(*fmt!='%'){
         *t=*fmt;
         t++;
         fmt++;
         }
       else{          
         switch(*(++fmt)){
            case 'x':
                integer=va_arg(ap,int);
                if(integer==0){
                 *t++='0';
                 *t++='x';
                 *t++='0';
                  break;
                     }
                if(integer<0){
                   *t++='-';
                   *t++-'0';
                   *t++='x';
                    integer=-integer;
                    }
               while(integer!=0){
                  int mode=integer%16;
                  integer=integer/16;
                  char ss=mode<10? mode+'0':mode-10+'a';
                  number[flag++]=ss;
                  }
           for(count=0;count<=flag-1;count++)
           *t++=number[flag-1-count];
               break;
         
          case 's':
             s=va_arg(ap,char*);
             while(*s!='\0')
             *t++=*s++;
              
              break;

          case 'd':
           integer=va_arg(ap,int);
           if(integer==0){
            *t++='0';
            break;
           }
           if(integer<0){
           *t++='-';
            integer=-integer;
            }
           while(integer!=0){
             number[flag]=integer%10+'0';
             integer=integer/10;
             flag++;
             }
           for(count=0;count<=flag-1;count++)
           *t++=number[flag-1-count];
            
            break;
                }
              fmt++;
            }
       }
    *t='\0';

    return t-out;
}

int sprintf(char *out, const char *fmt, ...) {
 va_list ap;
 va_start(ap,fmt);
 int length=vsprintf(out,fmt,ap);
 va_end(ap);
 return length;


}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  return 0;
}

#endif
