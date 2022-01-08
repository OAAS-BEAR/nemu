#include "common.h"
#include "syscall.h"

_Context* do_syscall(_Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1]=c->GPR2;
  a[2]=c->GPR3;
  a[3]=c->GPR4;
  switch (a[0]) {
    case 0://sys_exit()
     _halt(c->GPR2);
     break;
     
    case 1:// sys_yield()
    _yield();
    c->GPRx=0;
    break;
    case 4: //sys_write
    if(a[1]==1||a[1]==2){
       for( int i=0;i<a[3];i++){
          _putc(*(char*)(a[2]+i));
          }
        c->GPRx=a[3];
        }
        break;
    case SYS_brk:
        c->GPRx=0;
        break;
    
    default: panic("Unhandled syscall ID = %d", a[0]); break;
  }

  return c;
}
