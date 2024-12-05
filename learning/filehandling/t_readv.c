#include <tlpi.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/stat.h>

/*
struct iovec{
    void *iov_base;
    ssize_t iov_len;
};
*/

int main(int argc, char *argv[]){
   int fd;
   struct iovec iov[3];
   struct stat box1;
   int x;
#define STRSIZE 100
   char str[STRSIZE];
   ssize_t numread, totreq;
   if(argc != 2 || strcmp(argv[1], "--help") == 0){
       perror("usage error");
       return 1; }
       //usageErr("%s file\n", argv[0]);

   fd = open(argv[1], O_RDONLY);
   if(fd == -1){
       perror("open");
       exit(EXIT_FAILURE); }

   totreq = 0;
   iov[0].iov_base = &box1;
   iov[0].iov_len = sizeof(struct stat);
   totreq += iov[0].iov_len;

   iov[1].iov_base = &x;
   iov[1].iov_len = sizeof(x);
   totreq += iov[1].iov_len;

   iov[2].iov_base = str;
   iov[2].iov_len = STRSIZE;
   totreq += iov[2].iov_len;

   numread = readv(fd, iov, 3);
   if(numread == -1) {
       perror("readv");
       exit(EXIT_FAILURE); }

   if(numread < totreq)
       printf("read fewer bytes than requested\n");

   printf("total bytes requested: %ld; bytes read: %ld\n", (long) totreq, (long) numread);
   exit(EXIT_SUCCESS);
}
