#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

extern char *optarg;
//function pointer
typedef void MYFUNC(char  *a, int b, int c);
char *filetype(unsigned char type) {
  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}

// reffered from https://code-vault.net/lesson/18ec1942c2da46840693efe9b526daa4
//https://www.youtube.com/watch?v=j9yL30R6npk

void filelist(const char* dirname, int count){
  ssize_t nbytes, buffer_size;
  char *buffer;
  struct stat buf; 
  char *ptr; 

  DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    //printf("Reading files in the mentioned directory: %s\n", dirname);
    struct dirent* dirent;

    while ((dirent = readdir(dir))!= NULL) {
        if (strcmp(filetype((*dirent).d_type), "directory")==0 && strcmp((*dirent).d_name, ".") != 0 && strcmp((*dirent).d_name, "..") != 0) 
        {
          //printf("[%d] %hhd %s %s\n",count, (*dirent).d_type, dirname, (*dirent).d_name);
          for(int i=0;i<count;i++){
            printf("\t");
          }
          printf("/%s\n", (*dirent).d_name);
          //count++;
            char path[1000] = { 0 };
            strcat(path, dirname);
            if(strcmp(dirname,"./")==0){

            }else{
                strcat(path, "/");
            }
            strcat(path, (*dirent).d_name);
            filelist(path,count+1);
        }else{
          if(strcmp((*dirent).d_name, ".")==0){
            continue;
          }else if(strcmp((*dirent).d_name, "..")==0){
            continue;
          }
          
          for(int i=0;i<count;i++){
            printf("\t");
          }

          printf("%s\n",(*dirent).d_name);

          // 4th point
          if(strcmp(filetype((*dirent).d_type), "symbolic link")==0){
            if (lstat((*dirent).d_name, &buf) < 0) { 
                //printf("lstat error"); 
                  //exit(-1);
              }

              if (S_ISLNK(buf.st_mode)) {
                  ptr = "symbolic link";
                  //printf("%s\n", ptr); 
                  buffer_size=buf.st_size;
                  //referred from https://linuxhint.com/c-read-link-function/
                  buffer = malloc(buffer_size);

                nbytes = readlink((*dirent).d_name, buffer, buffer_size);
                printf("\t%s link points to file (%s) \n", (*dirent).d_name, buffer);
                //exit(-1);
              }

          }
              
          //
          

        }
    }

    closedir(dir);

}

//5th Point i
void filedetails(char *dirname,long long val, int count, char *inval){
  //printf("%s is the directory\n", dirname);

  ///demo test ////
  ssize_t nbytes, buffer_size;
  char *buffer;
  struct stat buf; 
  char *ptr; 
  char *text;
  //char dirnamee[10];
  
  if(strcmp(dirname,"-S")==0){
    strcpy(dirname,"./");
     printf("%s\n", inval);
  }
  else if (strcmp(dirname,"-s")==0){
    strcpy(dirname,"./");
     printf("%s\n", inval);
    printf("value = %d\n", val);
  }else if(strcmp(dirname,"-f")==0){
    strcpy(dirname,"./");
    val=-1;
    printf("%s %d\n", inval, val);
  }

  DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    //printf("Reading files in the mentioned directory: %s\n", dirname);
    struct dirent* dirent;

    while ((dirent = readdir(dir))!= NULL) {
        if (strcmp(filetype((*dirent).d_type), "directory")==0 && strcmp((*dirent).d_name, ".") != 0 && strcmp((*dirent).d_name, "..") != 0) 
        {
          //printf("[%d] %hhd %s %s\n",count, (*dirent).d_type, dirname, (*dirent).d_name);
          if(strcmp(inval,"Null")!=0){
              //here right code from 5.3
              if(strstr((*dirent).d_name,inval)){
                if(val<0){
            for(int i=0;i<count;i++){
            printf("\t");
          }
            //printf("Hello i am 5.3\n");
            printf("/%s \n ", (*dirent).d_name);
          //5.1
          if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }
              //printf("Mode: %o (octal);  file size: %lld bytes;", (unsigned long)buf.st_mode, (long long) buf.st_size);
              //printf("last file access (%s)\n", ctime(&buf.st_atime));
          }else if((long long) buf.st_size<=val){
            for(int i=0;i<count;i++){
            printf("\t");
          }
            printf("/%s \n ", (*dirent).d_name);
          //5.1
          if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }
              //printf("Mode: %o (octal);  file size: %lld bytes;", (unsigned long)buf.st_mode, (long long) buf.st_size);
              //printf("last file access (%s)\n", ctime(&buf.st_atime));
          }
              }   
          }else{
            if((long long) buf.st_size<=val){
            for(int i=0;i<count;i++){
            printf("\t");
          }
            printf("/%s  ", (*dirent).d_name);
          //5.1
          if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }
              printf("Mode: %o (octal);  file size: %lld bytes;", (unsigned long)buf.st_mode, (long long) buf.st_size);
              printf("last file access (%s)\n", ctime(&buf.st_atime));

          }else if(val==0){

            for(int i=0;i<count;i++){
            printf("\t");
          }

            printf("/%s  ", (*dirent).d_name);
          //5.1
          if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }

              printf("Mode: %o (octal);  file size: %lld bytes;", (unsigned long)buf.st_mode, (long long) buf.st_size);
              printf("last file access (%s)\n", ctime(&buf.st_atime));

          }

          }          
              //5.1
          //count++;
            char path[1000] = { 0 };
            strcat(path, dirname);
            if(strcmp(dirname,"./")==0){

            }else{
                strcat(path, "/");
            }
            strcat(path, (*dirent).d_name);
            filedetails(path,val, count+1, inval); //recersive calls
        }        
        else{
          if(strcmp((*dirent).d_name, ".")==0){
            continue;
          }else if(strcmp((*dirent).d_name, "..")==0){
            continue;
          }

          // 5.3 files printing
          if(strcmp(inval,"Null")!=0){

            if(strstr((*dirent).d_name,inval)){
              if(val<0){

            for(int i=0;i<count;i++){
            printf("\t");
            }

            printf("(%s)   ",(*dirent).d_name);

          //5th point 
          //1.
              if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }

              //printf("Mode: %o (octal); file size: %lld bytes; last file access: (%s)\n", (unsigned long)buf.st_mode, (long long) buf.st_size, ctime(&buf.st_atime));
              //printf("Hello");
              printf("\n");

          }else if(buf.st_size<=val){
            //printf("the value is %d\n", buf.st_size);
            for(int i=0;i<count;i++){
            printf("\t");
            }
            //printf("valuueeee %d\n",val);
            printf("(%s)   ",(*dirent).d_name);

          //5th point 
          //1.
              if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }

              printf("Mode: %o (octal); file size: %lld bytes; last file access: (%s)\n", (unsigned long)buf.st_mode, (long long) buf.st_size, ctime(&buf.st_atime));
              //printf("Hello");

          }


            }
           
          }else{

            if((long long) buf.st_size<=val){

            for(int i=0;i<count;i++){
            printf("\t");
            }

            printf("(%s)   ",(*dirent).d_name);

          //5th point 
          //1.
              if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }

              printf("Mode: %o (octal); file size: %lld bytes; last file access: (%s)\n", (unsigned long)buf.st_mode, (long long) buf.st_size, ctime(&buf.st_atime));
              //printf("Hello");
              //printf("file size: %lld bytes; val=%lld\n", (long long) buf.st_size, val);
          }else if(val==0){
            //printf("the value is %d\n", buf.st_size);
            for(int i=0;i<count;i++){
            printf("\t");
            }
            //printf("valuueeee %d\n",val);
            printf("(%s)   ",(*dirent).d_name);

          //5th point 
          //1.
              if(lstat((*dirent).d_name, &buf)<0){
                //printf("lstat error\n");
                //continue;
              }

              printf("Mode: %o (octal); file size: %lld bytes; last file access: (%s)\n", (unsigned long)buf.st_mode, (long long) buf.st_size, ctime(&buf.st_atime));
              //printf("Hello");
              

          }
          }
          
          //printf("the final val is %d\n", (buf.st_size<=val) );   
              // 5.1
          
          //
        }    
        
    }

    closedir(dir);

  /////////////
  //exit(-1);
}

//8. point
void filedirlist(char *dirname, int count, int fflag){
    if(strcmp(dirname, "f")==0){
      strcpy(dirname, "./");
      printf("%d\n", fflag);
    }else if (strcmp(dirname, "d")==0){
      strcpy(dirname, "./");
      printf("%d\n", fflag);
    }

    ssize_t nbytes, buffer_size;
  char *buffer;
  struct stat buf; 
  char *ptr; 

  DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }

    //printf("Reading files in the mentioned directory: %s\n", dirname);
    struct dirent* dirent;

    while ((dirent = readdir(dir))!= NULL) {
        if (strcmp(filetype((*dirent).d_type), "directory")==0 && strcmp((*dirent).d_name, ".") != 0 && strcmp((*dirent).d_name, "..") != 0 ) 
        {
          //printf("[%d] %hhd %s %s\n",count, (*dirent).d_type, dirname, (*dirent).d_name);
          if(fflag==1){

          }else{
              for(int i=0;i<count;i++){
            printf("\t");
          }
          printf("/%s\n", (*dirent).d_name);
          }
          
          //count++;
            char path[1000] = { 0 };
            strcat(path, dirname);
            if(strcmp(dirname,"./")==0){

            }else{
                strcat(path, "/");
            }
            strcat(path, (*dirent).d_name);
            filedirlist(path,count+1, fflag);
        }else{
          if(strcmp((*dirent).d_name, ".")==0){
            continue;
          }else if(strcmp((*dirent).d_name, "..")==0){
            continue;
          }

          if(fflag==2){

          }else{
            for(int i=0;i<count;i++){
            printf("\t");
          }

          printf("%s\n",(*dirent).d_name);
            
          }
          
          // 4th point
          if(strcmp(filetype((*dirent).d_type), "symbolic link")==0){
            if (lstat((*dirent).d_name, &buf) < 0) { 
                //printf("lstat error"); 
                  //exit(-1);
              }

              if (S_ISLNK(buf.st_mode)) {
                  ptr = "symbolic link";
                  //printf("%s\n", ptr); 
                  buffer_size=buf.st_size;
                  //referred from https://linuxhint.com/c-read-link-function/
                  buffer = malloc(buffer_size);

                nbytes = readlink((*dirent).d_name, buffer, buffer_size);
                //printf("\t%s link points to file (%s) \n", (*dirent).d_name, buffer);
                //exit(-1);
              }

          }
              
          //
          

        }
    }

    closedir(dir);


}

// 8
void filedetails2(char *dirname, int count, MYFUNC *filedirlist){
    int fflag=0;
    printf("%s %d\n", dirname, count);
    printf("printed file2 function\n");
    if(strcmp(dirname, "f")==0){
      printf("true\n");
      fflag=1;
      filedirlist(dirname, count, fflag);
    }else if(strcmp(dirname, "d")==0){
      fflag=2;
      printf("d is printed");
      filedirlist(dirname, count, fflag);
    }
    exit(-1);
}

// Referred from  lecture 14th Review page no 192

//Main function
int main(int argc, char** argv){
  struct dirent *dirent;
  DIR *parentDir;

  struct stat buf; 
  char *ptr; 
  int c=0;

  ssize_t nbytes, buffer_size;
  char *buffer;

  char directry[100];

  char *invale= malloc(100);
  strcpy(invale, "Null");

  //if(strcmp(argv[1],"-S")==0){
    //strccpy(directory, "./");
    //filedetails(dirctory);
    //exit(-1);
  //}
  //5th point i
  if(argc>=2){
    if(strcmp(argv[1],"-S")==0){
      int count=1;
    
    strcpy(directry, "-S");
    printf("we have given argument as %s\n", directry);
    filedetails(directry,c, count, invale);
    //filedetails(argv, count);

    
    exit(-1);
  }else if(strcmp(argv[1],"-s")==0 || strcmp(argv[1],"-f")==0 || strcmp(argv[1],"-t")==0 || strcmp(argv[1],"-S")==0) {
    int flags, opt;                 //referred from https://man7.org/linux/man-pages/man3/getopt.3.html
    int  tfnd, ntimes;
    int count =1;
    long long nsecs;
    //printf("printed t value");
      strcpy(directry, argv[1]);
    nsecs = 0;
    tfnd = 0;
    flags = 0;
    ntimes=0;
  


    while ((opt = getopt(argc, argv, "S:s:f:t:")) != -1) {
               switch (opt) {
                case 'S':
                    flags = 1;
                    //nsecs = atoi(optarg);
                    tfnd = 1;

                    break;
               case 's':
                    flags = 1;
                    nsecs = atoi(optarg);
                    tfnd = 1;
                    break;
               case 'f':
                    //*invale
                    invale= strtok(optarg, " ");
                    ntimes = atoi(strtok(NULL," "));
                    //char intval[50]= strtok(NULL," ");
                    //nsecs = atoi(optarg);
                    tfnd = 1;
                    break;

              case 't':
                    //*invale
                    invale= strtok(optarg, "");
                    printf("t is printed");
                    filedetails2(invale, count, filedirlist);
                    //char intval[50]= strtok(NULL," ");
                    //nsecs = atoi(optarg);
                    tfnd = 3;
                    exit(-1);
                    break;
                  
                   //break;
               default: /* '?' */
                    fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                    argv[0]);
                   
                   exit(EXIT_FAILURE);
               }
      }
    
    printf("flags=%d; tfnd=%d; nsecs=%d; optind=%d ntimes=%d\n",
                   flags, tfnd, nsecs, optind, ntimes);
                   printf("invalue=%s\n", invale);

      //printf("%s : %s\n", argv[1], argv[2]);
      //printf("name argument = %s\n", argv[optind])
      
      filedetails(directry,nsecs, count, invale);

                   exit(-1);

  }
  }
  
  

  
  if(argc<2){
    //2. program is executed without any arguments, the program should print the file hierarchy starting with the current directory
    parentDir = opendir("./");
    strcpy(directry,"./");
    int count =1;
    printf("The current directory is %s\n", "./");
    while((dirent=readdir(parentDir))!=NULL){
    printf("[%d] %s : file type = %s\n", count, (*dirent).d_name, filetype((*dirent).d_type));
    if(strcmp(filetype((*dirent).d_type),"directory") ==0 && strcmp((*dirent).d_name, ".")!=0 && strcmp((*dirent).d_name, "..")!=0){
      
    }
    count++;
    }

  }else{

   
    parentDir = opendir(argv[1]);
    strcpy(directry,argv[1]);

  if (parentDir == NULL){
    printf("error opening the directory %s\n", argv[1]);
    //dirent = readdir(directry);
    
    exit(-1);
  }


  
  int count=1;
  printf("The provided directory is %s\n", argv[1]);
  // 1. take the directory name from where to start the file traversal as a command-line argument and print the file hierarchy starting with the directory
  while((dirent=readdir(parentDir))!=NULL){
    
    printf("[%d] %s : file type = %s\n", count, (*dirent).d_name, filetype((*dirent).d_type));
    if(strcmp(filetype((*dirent).d_type), "symbolic link")==0){
      printf("it is a symbolic link\n");

       // 4. point  
    
      if (lstat((*dirent).d_name, &buf) < 0) { 
          printf("lstat error"); 
          exit(-1);
      }

      if (S_ISLNK(buf.st_mode)) {
        ptr = "symbolic link";
        printf("%s\n", ptr); 
        buffer_size=buf.st_size+1;
        //referred from https://linuxhint.com/c-read-link-function/
        buffer = malloc(buffer_size);

        nbytes = readlink((*dirent).d_name, buffer, buffer_size);
        printf("%s link points to (%s)\n", (*dirent).d_name, buffer);
        //exit(-1);
      }

      
  //

    }
    count++;
  }

  }
  // 3.  other directories in the current directory then the directory name is first displayed on a separate line and then the files in that directory are listed one-per-line with one-tab indentation.

  printf("Printing all the files and files in sub-directory\n");
  printf("%s\n", directry);
  int count =1;
  filelist(directry, count);
  

  closedir(parentDir);


    return 0;
}
