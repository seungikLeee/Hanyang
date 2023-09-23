#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  /*
  if(argc != 3){
    printf(2, "Usage: ln old new\n");
    exit();
  }
  if(link(argv[1], argv[2]) < 0)
    printf(2, "link %s %s: failed\n", argv[1], argv[2]);
  */
 
  if(argc != 4){
    printf(2, "Usage: ln old new\n");
    exit();
  }
  if(strcmp(argv[1], "-h")==0){
    //printf(1, "%s link!\n", argv[1]);
    if(link(argv[2], argv[3]) < 0)
      printf(2, "link %s %s: failed\n", argv[2], argv[3]);
  }
  if(strcmp(argv[1], "-s")==0){
    //printf(1, "%s link!\n", argv[1]);
    if(slink(argv[2], argv[3]) < 0)
      printf(2, "slink %s %s: failed\n", argv[2], argv[3]);
  }
  exit();
}
