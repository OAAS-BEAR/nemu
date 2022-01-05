#include "klib.h"

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t l=0;
  while(*s!=0){
    l++;
    s++;
    }
  return l;
}

char *strcpy(char* dst,const char* src) {
  char * cur=dst;
  while(*src!=0){
    *dst=*src;
    dst++;
    src++;
    }
    *dst='\0';
  return cur;
}

char* strncpy(char* dst, const char* src, size_t n) {
  char * cur=dst;
  while((n--)&&((*dst++ =*src++)!='\0'));
  if(n>0){
   while(--n){
   *dst++='\0';
   }
   }
  return cur;
}

char* strcat(char* dst, const char* src) {
  char * cur=dst;
  while(*dst)
   dst++;
  while((*dst++ = *src++)!='\0')
  ;
  
  return cur;
}

int strcmp(const char* s1, const char* s2) {

  while(*s1 ==*s2){
  if(*s1=='\0')
     return 0;
   s1++;
   s2++;
     }
   if((*s1-*s2)>0)
   return 1;
  return -1;
}

int strncmp(const char* s1, const char* s2, size_t n) {
  unsigned char c1,c2;
  while(n){
  c1=*s1++;
  c2=*s2++;
  if(c1!=c2)
  return c1<c2? -1:1;
  if(!c1)
  break;
  n--;
  }
  return 0;
}

void* memset(void* v,int c,size_t n) { 
   char * cur=v;
   while(n--){
   *cur++=c;
   }
  return v;
}

void* memcpy(void* out, const void* in, size_t n) {
    char *tmp=out;
    const char *s=in;
    while(n--){
    *tmp++ = *s++;
    }
    return out;
}

int memcmp(const void* s1, const void* s2, size_t n){
  unsigned char * su1,*su2;
  int res=0;
  for(su1=s1,su2=s2;n>0;++su1,++su2,n--){
  if((res=*su1-*su2)!=0)
    break;
    }
   return res;
   
  
  

}

#endif
