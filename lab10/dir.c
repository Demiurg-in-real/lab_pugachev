#include<dirent.h>
#include<stdio.h>
#include<sys/types.h>
int main(int argc, char* argv[])
{
	DIR *get;
	struct dirent *fuck;
	get=opendir("./");
	if (get != 0){//EACCES || get != EMFILE || get !=  ENFILE || get != ENOENT || get != ENOMEM || get != ENOTDIR){
		printf("Fuck\n");
		//return 0;
	}
	while( (fuck=readdir(get)) != NULL){
		if(fuck->d_name==".."){
			continue;
		}
		printf("%d - %s, its type: %d\n", fuck->d_ino, fuck->d_name[1], fuck->d_type);
	}

	return 0;
}
