#include "fs.h"

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  size_t offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};
extern events_read(void*, size_t,size_t);
extern size_t serial_write(const void *buf, size_t offset, size_t len);
size_t fbsync_write(const void *buf, size_t offset, size_t len);
size_t fb_write(const void *buf, size_t offset, size_t len);
size_t dispinfo_read(void *buf, size_t offset, size_t len);
size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

int fs_open(const char*filename,int flags,int mode);


size_t fs_write(int fd,const void*buf,size_t len);
size_t fd_read(int fd,void* buf,size_t len);
size_t fs_lseek(int fd,size_t offset,int whence);
int fs_close(int fd);
/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  {"stdin", 0, 0, invalid_read, invalid_write},
  {"stdout", 0, 0, invalid_read, serial_write},
  {"stderr", 0, 0, invalid_read, serial_write},
 // {"/dev/events",0xfffff,0,0,events_read,invalid_write},
  {"/dev/fb",0xfffff,0,0,invalid_read,fb_write},
  {"/dev/events",0xfffff,0,0,events_read,invalid_write},
  {"/dev/fbsync",0xfffff,0,0,invalid_read,fbsync_write},
  {"/proc/dispinfo",0xfffff,0,0,dispinfo_read,invalid_write},
  {"/dev/tty",0xfffff,0,0,invalid_read,serial_write},
#include "files.h"
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))
int fs_open(const char*filename,int flags,int mode){
  for(int i=0;i<NR_FILES;i++){
      if(strcmp(file_table[i].name,filename)==0){
          file_table[i].offset=0;
          return i;
          }
       }
      assert(0);
      }
 
int fs_close(int fd){
 return 0;
 }
 
size_t fs_read(int fd,void* buf,size_t len){
     size_t offset=file_table[fd].offset;
     size_t size=file_table[fd].size;
     size_t disk_offset=file_table[fd].disk_offset;
     size_t l;
      if(offset+len>size){
           len=size-offset;
           }
      if(file_table[fd].read==NULL)
       l= ramdisk_read(buf, offset+disk_offset, len);
      else
       len=file_table[fd].read(buf,offset+disk_offset,len);
      file_table[fd].offset+=len;
      return len;
      }
size_t fs_write(int fd,const void* buf,size_t len){
    if(fd==1||fd==2){
      return serial_write(buf,0,len);
       }
  
     size_t offset=file_table[fd].offset;
     size_t size=file_table[fd].size;
     size_t disk_offset=file_table[fd].disk_offset;
     size_t l;
      if(offset+len>size){
           len=size-offset;
           }
      if(file_table[fd].write==NULL)
       l=ramdisk_write(buf, offset+disk_offset, len);
      else
      len=file_table[fd].write(buf,offset+disk_offset,len);
      file_table[fd].offset+=len;
      return len;
      }
size_t fs_lseek(int fd,size_t offset,int whence){
        if(whence==SEEK_SET){
             file_table[fd].offset=offset;

          }
          else if(whence==SEEK_CUR){
          
            file_table[fd].offset+=offset;

}
else{
            file_table[fd].offset=offset+file_table[fd].size;
          }
          return file_table[fd].offset;
     }       
     
 
void init_fs() {
  // TODO: initialize the size of /dev/fb
  int size=screen_width()*screen_height()*4;
  file_table[FD_FB].size=size; 
}
