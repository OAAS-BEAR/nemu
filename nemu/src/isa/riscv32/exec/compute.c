#include "cpu/exec.h"

make_EHelper(lui) {
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(lui);
}


make_EHelper(aui){
  rtl_sr(id_dest->reg, &id_src->val, 4);

  print_asm_template2(aui);
  }
  
make_EHelper(j){
   rtl_add(&decinfo.jmp_pc,&id_src->val,&decinfo.seq_pc);
   rtl_j(decinfo.jmp_pc);
   vaddr_t r_pc=decinfo.seq_pc+4;
   rtl_sr(id_dest->reg,&r_pc,4);
 
}

make_EHelper(jr){
           vaddr_t n_pc=id_src->addr & 0xfffffffe;
           rtl_j(n_pc);
           
           vaddr_t r_pc=decinfo.seq_pc+4;
           rtl_sr(id_dest->reg,&r_pc,4);
         }
           
make_EHelper(ri){
      uint32_t uimm;
      int result;
      int32_t imm;
      int32_t r_value;
      uint32_t ur_value;
      switch(decinfo.isa.instr.funct3){
          case 0:
                imm=id_src2->val;
                imm=imm<<20>>20;
                result;                
                rtl_add(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
                break;
          case 2:
                imm=id_src2->val;
                imm=imm<<20>>20;
                
                r_value=id_src->val;
                result=0;
                if(r_value<imm){
                   result =1;
                   rtl_sr(id_dest->reg,&result,4);
                   }
                else{
                   rtl_sr(id_dest->reg,&result,4);
                   }
                  break; 
                   
          case 3:
                imm=id_src2->val;
                imm=imm<<20>>20;
                uimm=imm;
                ur_value=id_src->val;
                result=0;
                if(ur_value<uimm){
                   result =1;
                   rtl_sr(id_dest->reg,&result,4);
                   }
                else{
                   rtl_sr(id_dest->reg,&result,4);
                   }
                  break;
          case 4:
                imm=id_src2->val;
                imm=imm<<20>>20;
                result;                
                rtl_xor(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
                break;         
          case 6:
                imm=id_src2->val;
                imm=imm<<20>>20;
                result;                
                rtl_or(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
                break;                
          case 7:
                imm=id_src2->val;
                imm=imm<<20>>20;
                result;                
                rtl_and(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
                break;          
}

}


         
           
