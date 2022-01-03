#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
WP * new_wp(char *str);
void info_watch();
void free_wp(int N);
void isa_reg_display();
void cpu_exec(uint64_t);
uint32_t expr(char *e, bool *success);
/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}
static int cmd_p(char* args){
	bool success=true;
	uint32_t value=expr(args,&success);
	if(success){
		printf(" the value of expression is %d\n",value);
	}
	else{
		printf(" fail to get the value of expression\n");
	}
	return 0;
}
static int cmd_q(char *args){
  return -1;
}
static int cmd_si(char*args){
	int num=0;
        sscanf(args,"%d",&num);
        cpu_exec(num);
	printf("current PC:%08x\n",cpu.pc);
	return 0;
}
static int cmd_info(char*args){
	if(strcmp(args,"r")==0){
              isa_reg_display();
	}
	else{
	    info_watch();
	}
	return 0;
}
static int cmd_x(char*args){
	    bool success=true;
            char* token=strtok(args," ");
	    char *arg = args + strlen(token) + 1;
	    uint32_t value=expr(arg,&success);
	    if(success){
	           int num;
		   sscanf(token,"%d",&num);
                   for(int i=0;i<num;i++){
	                  uint32_t this_read=paddr_read(value+4*i,4);
			  printf("memory 0x%8x:  0x%8x\n",value+4*i,this_read);
                          			  
		   }        
	}

	return 0;
}

static int cmd_w(char*args){
	new_wp(args);
	return 0;
}
static int cmd_d(char*args){
	int num;
	sscanf(args,"%d",&num);
        free_wp(num);
	return 0;
}
static int cmd_help(char *args);

static struct {
  char *name;
  char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si","dan bu zhi xing", cmd_si},
  { "info", "print the state of program", cmd_info},
  { "p",  "calculate the value of expression", cmd_p},
  { "x", "scan memory", cmd_x},
  { "w", "set monitor point", cmd_w},
  { "d", "delete monitor point", cmd_d}

  /* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void ui_mainloop(int is_batch_mode) {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef HAS_IOE
    extern void sdl_clear_event_queue(void);
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}
