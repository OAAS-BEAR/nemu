#include "common.h"
#include <amdev.h>

size_t serial_write(const void *buf, size_t offset, size_t len) {
     for(int i=0;i<len;i++)
      _putc(((char*)buf)[i]);
  return len;
}

#define NAME(key) \
  [_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [_KEY_NONE] = "NONE",
  _KEYS(NAME)
};

size_t events_read(void *buf, size_t offset, size_t len) {
  int key=read_key();
  if((key &0xfff)==_KEY_NONE)
    len=sprintf(buf,"t %d\n",uptime());
  else if(key&0x8000)
     len=sprintf(buf,"%s %s\n","kd", keyname[key&0xfff]);
  else
    len=sprintf(buf,"%s %s\n","ku", keyname[key&0xfff]);
     
  return len;
}

static char dispinfo[128] __attribute__((used)) = {};

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  len=sprintf(buf,dispinfo+offset);
  return len;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  int x=(offset/4)%screen_width();
  int y=(offset/4)/screen_width();
  draw_sync();
  draw_rect((uint32_t*)buf,x,y,len/4,1);
  return len;
}

size_t fbsync_write(const void *buf, size_t offset, size_t len) {
  draw_sync();
  return len;
}

void init_device() {
  Log("Initializing devices...");
  _ioe_init();
  sprintf(dispinfo,"WIDTH:%d\nHEIGHT:%d\n",screen_width(),screen_height());
  // TODO: print the string to array `dispinfo` with the format
  // described in the Navy-apps convention
}
