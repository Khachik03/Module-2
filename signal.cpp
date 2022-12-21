#include <iostream>

#include <unistd.h>

#include <signal.h>

#include <sys/wait.h>




int main()
{

 pid_t pid = fork();
 if(pid == -1)
            return 1;
 
 if(pid == 0)
 {
        int ppid = getppid();  
        kill(ppid, SIGKILL);
        std::cout<<"Father is  ";
 }

 else
 {
 	int st;
 	wait(&st);
 	std::cout<<"Something is wrong";

 }

}
