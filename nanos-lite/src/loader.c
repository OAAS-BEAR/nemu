#include "proc.h"
#include <elf.h>
#include "fs.h"
#ifdef __ISA_AM_NATIVE__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Phdr Elf32_Phdr
#endif

static uintptr_t loader(PCB *pcb, const char *filename) {
  //TODO();
 // FILE* fp=fopen(filename,"r+");
 int fd=fs_open(filename,0,0);
  Elf_Ehdr p;
  fs_read(fd,&p,sizeof(p));
  Elf_Phdr pp;
  for(int i=0;i<p.e_phnum;i++){
     fs_lseek(fd,p.e_phoff+i*p.e_phentsize,SEEK_SET);
     fs_read(fd,&pp,sizeof(pp));
     if(pp.p_type==PT_LOAD){
       fs_lseek(fd,pp.p_offset,SEEK_SET);
       fs_read(fd,(void*)pp.p_vaddr,pp.p_filesz);
       memset(pp.p_vaddr+pp.p_filesz,0,pp.p_memsz-pp.p_filesz);
       }
       }
       
     
     
  
  return p.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %x", entry);
  ((void(*)())entry) ();
}

void context_kload(PCB *pcb, void *entry) {
  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _kcontext(stack, entry, NULL);
}

void context_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);

  _Area stack;
  stack.start = pcb->stack;
  stack.end = stack.start + sizeof(pcb->stack);

  pcb->cp = _ucontext(&pcb->as, stack, stack, (void *)entry, NULL);
}
