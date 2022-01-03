#include "monitor/watchpoint.h"
#include "monitor/expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL,* end=NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
    wp_pool[i].status=false;
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

WP * new_wp(char *str){
	if(free_==NULL){
		assert(0);
	}
        if(head==NULL){
		head=free_;
		head->status=true;
		free_=free_->next;
		head->next=NULL;
		
	}
	else{
	     end=head;
	     head=free_;
	     free_=free_->next;
	     head->next=end;
	     head->status=true;
	}
	strcpy(head->str,str);
	bool success=true;
        head->value=expr(str,&success);

	return head;
}
bool check_watchpoints(){
	WP* w=head;
	bool change=false;
	while(w!=NULL){
	      bool success=true;
              uint32_t newvalue=expr(w->str,&success);
	      if(newvalue!=w->value){
		      w->value=newvalue;
                      change=true;
	      }
	      w=w->next;
	}
	if(change){
		printf("the value of watchpoint changed\n");
	}
	return change;
}
void info_watch(){
	WP* w=head;
	while(w!=NULL){
		printf("watchpoint NO.%d %s: %8x\n",w->NO,w->str,w->value);
		w=w->next;
	}
}
void free_wp(int N){
       WP* wp=&wp_pool[N];
       WP* w=head;
       bool success=false;
       while(w!=NULL){
	       if(w==head){
                       if(w==wp){
			       head=head->next;
			       w->status=false;
			       end=free_;
			       free_=w;
			       free_->next=end;
			       success=true;
			       break;
		       }
	       }
	       if(w->next!=NULL){
		       if(w->next==wp){
			       w->next=wp->next;
			       wp->status=false;
			       end=free_;
			       free_=wp;
			       free_->next=end;
			       success=true;
			       break;
		       }
	}

	      w=w->next;
       }
    
       if(!success){
	       printf("fail to delete watchpoint\n");
       }
          
}
/* TODO: Implement the functionality of watchpoint */
