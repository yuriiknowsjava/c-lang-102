#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/* By default, C has 3 file descriptors
    0 - stdin
    1 - stdout
    2 - stderr

    so file descriptor is just an integer
    */
int main(int argc, char *argv[])
{
    char *fName = "./out/myfile-632535432";
    if (argc >= 2)
    {
        fName = argv[1];
    }
    
    // you can combine multiple flags with bitwise OR
    // 0644 - in octal specifying file permissions
    int fd = open(fName, O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open");
        return -2;
    }
    printf("The file descriptor is %d\n", fd);
    char *mydata = "Hello there file!\n";
    write(fd, mydata, strlen(mydata));
    close(fd);

    int fd2 = open(fName, O_RDWR);
    struct stat statStruct = {0};
    if (fstat(fd2, &statStruct) < 0)
    {
        perror("fstat");
        return -1;
    }
    printf("File size in %ld bytes\n", statStruct.st_size);
    close(fd2);
    return 0;
}
