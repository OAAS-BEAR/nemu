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
           flag=0;
           while(integer!=0){
             number[flag]=integer%10+'0';
             flag++;
             integer=integer/10;
             }
           for(count=flag-1;flag>=0;flag--){
              *t++=number[flag];
            }
            break;

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
                    integer=-integer;
                    }
               while(integer!=0){
                 int a=integer%16;
                  if(a<10)
                   number[flag++]=a+'0';
                  else
                   number[flag++]=a-10+'a';
                  integer=integer/16;
                  }
                  *t++='0';
                  *t++='x';
               for(count=flag;count>=0;count--){
               *t++=number[count];
                }
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
