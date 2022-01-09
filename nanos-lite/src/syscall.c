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
    // _halt(c->GPR2);
    c->GPR1=SYS_execve;
    c->GPR2="/bin/init";
    do_syscall(c);
     break;
     
    case 1:// sys_yield()
    _yield();
    c->GPRx=0;
    break;
    case 4: //sys_write
  //  printf("%d",a[3]);
  /*  if(a[1]==1||a[1]==2){
       for( int i=0;i<a[3];i++){
          _putc(*(char*)(a[2]+i));
          }*/
    //     printf("write %d\n",a[1]);
        c->GPRx=fs_write(a[1],a[2],a[3]);
       
        break;
    case SYS_open:
    // printf("open %s\n",a[1]);
     c->GPRx=fs_open(a[1],a[2],a[3]);
     break;
    case SYS_brk:
        c->GPRx=0;
        break;
    case SYS_lseek:
      c->GPRx=fs_lseek(a[1],a[2],a[3]);
      break;
     case SYS_read:
//     printf("read %d\n",a[1]);
     c->GPRx=fs_read(a[1],a[2],a[3]);
     break;
     case SYS_close:
     c->GPRx=fs_close(a[1]);
     case SYS_execve:
     naive_uload(NULL,a[1]);
     break;
    default: panic("Unhandled syscall ID = %d", a[0]); break;
  }

  return c;
}
