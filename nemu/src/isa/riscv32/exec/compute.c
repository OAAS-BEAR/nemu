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
   print_asm_template2(j);
 
}

make_EHelper(jr){
           vaddr_t n_pc=id_src->addr & 0xfffffffe;
           rtl_j(n_pc);
           
           vaddr_t r_pc=decinfo.seq_pc;
           rtl_sr(id_dest->reg,&r_pc,4);
           print_asm_template2(jr);
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
                print_asm_template2(addi);
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
                   print_asm_template2(slti);
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
                   print_asm_template2(sltiu);
                  break;
          case 4:
                imm=id_src2->val;
                imm=imm<<20>>20;
             //   result;                
                rtl_xor(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
               print_asm_template2(xori);
                break;    
                     
          case 6:
                imm=id_src2->val;
                imm=imm<<20>>20;
               // result;                
                rtl_or(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
               print_asm_template2(ori);
                break;                
          case 7:
                imm=id_src2->val;
                imm=imm<<20>>20;
              //  result;                
                rtl_and(&result,&imm,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
                print_asm_template2(andi);
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
                 print_asm_template2(beq);
               break;

        case 1:
              if(id_src->val!=id_src2->val)
                 rtl_j(id_dest->val+cpu.pc);
                 print_asm_template2(bne);
               break; 
        case 4:
              src=id_src->val;
              src2=id_src2->val;
              if(src<src2)
                rtl_j(id_dest->val+cpu.pc);
               print_asm_template2(blt); 
              break;
        case 5:
              src=id_src->val;
              src2=id_src2->val;
              if(src>src2)
                rtl_j(id_dest->val+cpu.pc);
                print_asm_template2(bge);
              break; 
        case 6:
              usrc=id_src->val;
              usrc2=id_src2->val;
              if(usrc<usrc2)
                rtl_j(id_dest->val+cpu.pc);
                print_asm_template2(bltu);
              break;
        case 7:
              usrc=id_src->val;
              usrc2=id_src2->val;
              if(usrc>usrc2)
                rtl_j(id_dest->val+cpu.pc);
                print_asm_template2(bgeu);
              break;  
              }
              }
              
              
make_EHelper(r){      
      uint32_t usrc;
      int result;
      int32_t src;
      int32_t src2;
      uint32_t usrc2;
      int shift;
      switch(decinfo.isa.instr.funct3){
          case 0:
                if(decinfo.isa.instr.funct7==0){              
                rtl_add(&result,&id_src2->val,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
                print_asm_template2(add);
                }
                else{
                 rtl_sub(&result,&id_src2->val,&id_src->val);
                 rtl_sr(id_dest->reg,&result,4);
                 print_asm_template2(sub);
                 }
               
                break;
          case 1:
                shift=id_src2->val & 0x0000001f;
                rtl_shl(&result,&id_src->val,&shift);
                rtl_sr(id_dest->reg,&result,4);
               print_asm_template2(sll);
                break;
          case 2:
                src=id_src->val;
                src2=id_src2->val;
                result=0;
                if(src<src2){
                   result =1;
                   rtl_sr(id_dest->reg,&result,4);
                   
                   }
                else{
                   rtl_sr(id_dest->reg,&result,4);
                   }
                   print_asm_template2(slt);
                  break; 
                   
          case 3:
                usrc=id_src->val;
                usrc2=id_src2->val;
                result=0;
                if(usrc<usrc2){
                   result =1;
                   rtl_sr(id_dest->reg,&result,4);
                   }
                else{
                   rtl_sr(id_dest->reg,&result,4);
                   }
                   print_asm_template2(sltu);
                  break; 
          case 4:             
                rtl_xor(&result,&id_src2->val,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
               print_asm_template2(xor);
                break;       
          case 5:
                if(decinfo.isa.instr.funct7==0){              
                shift=id_src2->val & 0x0000001f;
                rtl_shr(&result,&id_src->val,&shift);
                rtl_sr(id_dest->reg,&result,4);
              print_asm_template2(srl);
                }
                else{
                shift=id_src2->val & 0x0000001f;
                rtl_sar(&result,&id_src->val,&shift);
                rtl_sr(id_dest->reg,&result,4);
              print_asm_template2(sra);
                 }
                break;           
          case 6:             
                rtl_or(&result,&id_src2->val,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
               print_asm_template2(or);
                break;                
          case 7:          
                rtl_and(&result,&id_src2->val,&id_src->val);
                rtl_sr(id_dest->reg,&result,4);
               print_asm_template2(and);
                break;          
}

}
                               
           
