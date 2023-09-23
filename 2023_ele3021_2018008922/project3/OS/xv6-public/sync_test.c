#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

#define BLOCK_SIZE (512)
#define BLOCK_NUM (300)

int
main(int argc, char *argv[])
{
  int fd, i, r;
  char *path = "test_sync_file";
  char data[BLOCK_SIZE];

  printf(1, "start!!!!!\n");
  const int sz = sizeof(data);
  for (i = 0; i < sz; i++) {
      //printf(1,"data %d\n", i);
      data[i] = i;
  }

  fd = open(path, O_CREATE | O_RDWR);
  for(i = 0; i < BLOCK_NUM; i++){
    //printf(1,"print block %d\n", i);
    if ((r = write(fd, data, sizeof(data))) != sizeof(data)){
      printf(1, "write returned %d : failed\n", r);
      exit();
    }
  }
  sync();
  printf(1, "%d bytes written\n", BLOCK_NUM * BLOCK_SIZE);
  close(fd);
  exit();
}
