#include "cpu/exec.h"

make_EHelper(ld) {

  switch (decinfo.width) {
    
    case 4: 
      rtl_lm(&s0, &id_src->addr, decinfo.width);
      rtl_sr(id_dest->reg, &s0, 4);
    print_asm_template2(lw); break;
    case 2: 
     if(decinfo.isa.instr.funct3==1){
     // lh
     rtl_lm(&s0,&id_src->addr,2);
     int result=s0;
     result=result<<16>>16;
     }
     else{
     // lhu
       rtl_lm(&s0, &id_src->addr, decinfo.width);
       rtl_sr(id_dest->reg, &s0, 4);
     
     print_asm_template2(lhu);
     }
     break;
    case 1: 
    if(decinfo.isa.instr.funct3==0){
    //lb
      rtl_lm(&s0,&id_src->addr,1);
     int result=s0;
     result=result<<24>>24;     
    
    }
    else{
    //lbu
        rtl_lm(&s0, &id_src->addr, decinfo.width);
       rtl_sr(id_dest->reg, &s0, 4);
        
    
     print_asm_template2(lbu);
    }    
    break;
    default: assert(0);
  }
}

make_EHelper(st) {
  rtl_sm(&id_src->addr, &id_dest->val, decinfo.width);

  switch (decinfo.width) {
    case 4: print_asm_template2(sw); break;
    case 2: print_asm_template2(sh); break;
    case 1: print_asm_template2(sb); break;
    default: assert(0);
  }
}
