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
   rtl_add(&decinfo.jmp_pc,&id_src->val,&cpu.pc);
   rtl_j(decinfo.jmp_pc);
   Log("pc %x\n",decinfo.jmp_pc);
   vaddr_t r_pc=decinfo.seq_pc;
   rtl_sr(id_dest->reg,&r_pc,4);
 
}

make_EHelper(jr){
           vaddr_t n_pc=id_src->addr & 0xfffffffe;
           rtl_j(n_pc);
           
           vaddr_t r_pc=decinfo.seq_pc;
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
                result=0;                
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

make_EHelper(b){
      uint32_t usrc;
      int result;
      int32_t src;
      int32_t src2;
      uint32_t usrc2;
      switch(decinfo.isa.instr.funct3){
        case 0:
              if(id_src->val==id_src2->val)
                 rtl_j(id_dest->val+cpu.pc);
               break;

        case 1:
              if(id_src->val!=id_src2->val)
                 rtl_j(id_dest->val+cpu.pc);
               break; 
        case 4:
              src=id_src->val;
              src2=id_src2->val;
              if(src<src2)
                rtl_j(id_dest->val+cpu.pc);
              break;
        case 5:
              src=id_src->val;
              src2=id_src2->val;
              if(src>src2)
                rtl_j(id_dest->val+cpu.pc);
              break; 
        case 6:
              usrc=id_src->val;
              usrc2=id_src2->val;
              if(usrc<usrc2)
                rtl_j(id_dest->val+cpu.pc);
              break;
        case 7:
              usrc=id_src->val;
              usrc2=id_src2->val;
              if(usrc>usrc2)
                rtl_j(id_dest->val+cpu.pc);
              break;  
              }
              }
              
              
make_EHelper(r){      
     uint32_t usrc;
      int result;
      int32_t src;
      int32_t src2;
      uint32_t usrc2;
      switch(decinfo.isa.instr.funct3){
          case 0:
                                
                rtl_add(&result,&id_src2->val,&id_src->val);
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
                               
           
