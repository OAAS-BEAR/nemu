#include "nemu.h"


/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
uint32_t isa_reg_str2val(const char *s, bool *success);
enum {
  TK_NOTYPE = 256, TK_EQ,TK_REGIS,TK_DECIMAL,TK_HEXA,TK_PLUS,TK_MINUS,
  TK_DIVIDE,TK_NE,TK_MUL,TK_AND,TK_LEFT,TK_RIGHT,TK_EQUAL

  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", TK_PLUS},         // plus
  {"==", TK_EQ},         // equal
  {"\\*", TK_MUL},
  {"/",  TK_DIVIDE},
  {"-",  TK_MINUS},
  {"[0-9]+",TK_DECIMAL},
  {"!=",TK_NE},
  {"&&",TK_AND},
  {"0[xX][0-9a-fA-F]+",TK_HEXA},
  {"\\$(0|ra|sp|gp|tp|t[0-6]|s[0-9]|s10|s11|a[0-7])",TK_REGIS},
  {"\\(",TK_LEFT},
  {"\\)",TK_RIGHT},
  {"==",TK_EQUAL},

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
		case TK_NOTYPE:break;
		case TK_DECIMAL:
		case TK_HEXA:
                case TK_REGIS:
	              tokens[nr_token].type=rules[i].token_type;
		      strncpy(tokens[nr_token].str,substr_start,substr_len<=32?substr_len:32); 
		      printf("%s\n",tokens[nr_token].str);
                      nr_token++;
		      break;
                default:
		     tokens[nr_token].type=rules[i].token_type;
		     printf("%d\n",tokens[nr_token].type);
		     nr_token++;
		     

        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool check_match(int q,int p){
       int record=0;
       while(q<=p){
	       if(tokens[q].type==TK_LEFT){
		       record++;
	       }
	       else if(tokens[q].type==TK_RIGHT){
			record--;
			if(record<0){
			return false;
			}
	       else{
	       ;
	       }

	}
	q++;
	}
	if(record!=0){
	   return false;
	   }
        return true;
}

			


	    
bool check_parent(int q,int p){
     if(tokens[q].type==TK_LEFT&&tokens[p].type==TK_RIGHT){
	     return check_match(q,p);
     }
     else{
	     return false;
     }

}

int priority(int type){
        int p=10;
	switch(type){
		case TK_MUL: case TK_DIVIDE:
			p=2;
			break;
		case TK_PLUS: case TK_MINUS:
			p=1;
			break;
		}
	return p;
}

int main_operator(int q,int p){
    int num=q;
    int operator=-1;
    int operator_prio=10;
    int ignore=0;
    while(num<=p){
      if(tokens[num].type==TK_LEFT){
	      ignore++;
      }
      else if(tokens[num].type==TK_RIGHT){
	      ignore--;
      }
      else{
	      ;
      }


      int p=priority(tokens[num].type);
      if(p<=2&&ignore==0){
            if(p<=operator_prio){
	       operator=num;
               operator_prio=p;
	    }
      }
      num++;
    }
   return operator;    

}

uint32_t eval(int q, int p,bool * success){
	if(q>p){
		*success=false;
		return 0;
	}
	else if(q==p){
		        uint32_t value;
			switch(tokens[q].type){
			case TK_DECIMAL:
			        sscanf(tokens[q].str,"%d",&value);
				break;
			case TK_HEXA:
				sscanf(tokens[q].str,"%x",&value);
				break;
			case TK_REGIS:
                                value=isa_reg_str2val(tokens[q].str,success);
				break;
			default:
				*success=false;
				break;
	}
		    printf("get value:%d\n",value);
                    return value;
	}
	else if(check_parent(p,q)==true){
		return eval(p+1,q-1,success);
	}
	else{
	      int op=main_operator(q,p);
	      printf("main op at position %d\n",op);

	      if(op<0){
		      return 0;
		      *success=false;
	      }
              uint32_t val1=eval(q,op-1,success);
	      uint32_t val2=eval(op+1,p,success);
	        switch(tokens[op].type){
			case TK_PLUS:
				return val1+val2;
			case TK_MINUS:
				return val1-val2;
			case TK_MUL:
				return val1*val2;
			case TK_DIVIDE:
				return val1/val2;
			case TK_AND:
				return val1&&val2;
			case TK_NE:
				return val1!=val2;
			case TK_EQUAL:
				return val1==val2;
			default:
				assert(0);
		}
	}
}
uint32_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
   return eval(0,nr_token-1,success);
}
