#include <stdlib.h>
#include <unistd.h>


int main()
{
	pid_t z = fork();
	
	if (z){
		sleep(20);	
	//даёт время прописать ps и глянуть на зомби f-/-_-\-f Zzzz

	} else {
		exit(0);	
	}
	// нет wait - дочерний процесс достанется init, и тот его "прикончит"
	return 0;
}
