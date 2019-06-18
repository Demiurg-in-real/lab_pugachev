#define _DEFAULT_SOURCE
       #include <dirent.h>
       #include <stdio.h>
       #include <stdlib.h>

       int
       main(void)
       {
           struct dirent **namelist;
           int n;

           n = scandir(".", &namelist, NULL, alphasort);
           if (n == -1) {
               perror("scandir");
               exit(EXIT_FAILURE);
           }

           while (n--) {
               printf("%s --- %08x\n", namelist[n]->d_name, namelist[n]->d_type);
               free(namelist[n]);
           }
           free(namelist);

           exit(EXIT_SUCCESS);
       }

