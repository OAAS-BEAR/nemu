#include "nemu.h"

const char *regsl[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

void isa_reg_display() {
}

uint32_t isa_reg_str2val(const char *s, bool *success) {
         if(strcmp(s,"$0")==0)
		 return cpu.gpr[0]._32;
	 else if(strcmp(s,"$ra")==0)
		 return cpu.gpr[1]._32;
	 else if(strcmp(s,"$sp")==0)
		 return cpu.gpr[2]._32;
         else if(strcmp(s,"$gp")==0)
                 return cpu.gpr[3]._32;
	 else if(strcmp(s,"$tp")==0)
                 return cpu.gpr[4]._32;
         else if(strcmp(s,"$t0")==0)
                 return cpu.gpr[5]._32;
	 else if(strcmp(s,"$t1")==0)
                 return cpu.gpr[6]._32;
         else if(strcmp(s,"$t2")==0)
                 return cpu.gpr[7]._32;
         else if(strcmp(s,"$s0")==0)
                 return cpu.gpr[8]._32;
         else if(strcmp(s,"$s1")==0)
                 return cpu.gpr[9]._32;
         else if(strcmp(s,"$a0")==0)
                 return cpu.gpr[10]._32;
         else if(strcmp(s,"$a1")==0)
                 return cpu.gpr[11]._32;
         else if(strcmp(s,"$a2")==0)
                 return cpu.gpr[12]._32;
         else if(strcmp(s,"$a3")==0)
                 return cpu.gpr[13]._32;
         else if(strcmp(s,"$a4")==0)
                 return cpu.gpr[14]._32;
         else if(strcmp(s,"$a5")==0)
                 return cpu.gpr[15]._32;
         else if(strcmp(s,"$a6")==0)
                 return cpu.gpr[16]._32;
         else if(strcmp(s,"$a7")==0)
                 return cpu.gpr[17]._32;
         else if(strcmp(s,"$s2")==0)
                 return cpu.gpr[18]._32;
         else if(strcmp(s,"$s3")==0)
                 return cpu.gpr[19]._32;
         else if(strcmp(s,"$s4")==0)
                 return cpu.gpr[20]._32;
         else if(strcmp(s,"$s5")==0)
                 return cpu.gpr[21]._32;
         else if(strcmp(s,"$s6")==0)
                 return cpu.gpr[22]._32;
         else if(strcmp(s,"$s7")==0)
                 return cpu.gpr[23]._32;
         else if(strcmp(s,"$s8")==0)
                 return cpu.gpr[24]._32;
         else if(strcmp(s,"$s9")==0)
                 return cpu.gpr[25]._32;
         else if(strcmp(s,"$s10")==0)
                 return cpu.gpr[26]._32;
         else if(strcmp(s,"$s11")==0)
                 return cpu.gpr[27]._32;
         else if(strcmp(s,"$t3")==0)
                 return cpu.gpr[28]._32;
         else if(strcmp(s,"$t4")==0)
                 return cpu.gpr[29]._32;
         else if(strcmp(s,"$t5")==0)
                 return cpu.gpr[30]._32;
         else if(strcmp(s,"$t6")==0)
                 return cpu.gpr[31]._32;
	 else{  
		 *success=false;
		 return -1;
	 }

}
