#include "cpu/exec.h"

make_EHelper(ec){
  switch(decinfo.isa.instr.funct3){
     case 0:
         if(decinfo.isa.instr.funct7==0){
            uint32_t NO=reg_l(17);
            raise_intr(NO,cpu.pc);
            
           }
           else{
            rtl_j(cpu.sepc+4);
           }
            
           break;
      case 1:
           if(decinfo.isa.instr.csr==0x141) //sepc
           {
            rtl_mv(&s0,&cpu.sepc);
          rtl_lr(&cpu.sepc,id_src->reg,4);
         //   cpu.sepc=s0|s1; 
            
            rtl_sr(id_dest->reg,&s0,4);
            
            
           }
           else if(decinfo.isa.instr.csr==0x100) //SSTATUS
           {
          rtl_mv(&s0,&cpu.sstatus);
          rtl_lr(&cpu.sstatus,id_src->reg,4);
         //   cpu.sepc=s0|s1; 
            
            rtl_sr(id_dest->reg,&s0,4);
            
            
           }
           else if(decinfo.isa.instr.csr==0x142){ //SCAUSE
          rtl_mv(&s0,&cpu.scause);
          rtl_lr(&cpu.scause,id_src->reg,4);
         //   cpu.sepc=s0|s1; 
            
            rtl_sr(id_dest->reg,&s0,4);
            
            
           }
           else{ //STVEC
                   rtl_mv(&s0,&cpu.stvec);
              rtl_lr(&cpu.stvec,id_src->reg,4);
         //   cpu.sepc=s0|s1; 
            
            rtl_sr(id_dest->reg,&s0,4);
            
            
           
           }
           break;
       case 2:
            if(decinfo.isa.instr.csr==0x141) //sepc
           {
                       rtl_mv(&s0,&cpu.sepc);
            rtl_lr(&s1,id_src->reg,4);
            cpu.sepc=s0|s1; 
            rtl_sr(id_dest->reg,&s0,4);
            
            
           }
           else if(decinfo.isa.instr.csr==0x100) //SSTATUS
           {
            rtl_mv(&s0,&cpu.sstatus);
            rtl_lr(&s1,id_src->reg,4);
            cpu.sstatus=s0|s1; 
            rtl_sr(id_dest->reg,&s0,4);
            
                       
           }
           else if(decinfo.isa.instr.csr==0x142){ //SCAUSE
            rtl_mv(&s0,&cpu.scause);
            rtl_lr(&s1,id_src->reg,4);
            cpu.scause=s0|s1; 
            rtl_sr(id_dest->reg,&s0,4);
            
                   
           }
           else{ //STVEC
            rtl_mv(&s0,&cpu.stvec);
            rtl_lr(&s1,id_src->reg,4);
            cpu.stvec=s0|s1; 
            rtl_sr(id_dest->reg,&s0,4);
                       
           
           }      
           
           
           
           
           
           
          
           
           }

   }
