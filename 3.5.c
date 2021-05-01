#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
int pipefds[2];
int number;
int p;
int flag = 0;

if(pipe(pipefds) == -1){
perror("pipe");
exit(EXIT_FAILURE);
}

pid_t pid = fork();

if(pid == 0){

void sigint_handler(int sig);
if(signal(SIGINT,sigint_handler) == SIG_ERR){
perror("signal");
exit(1);
}

printf("Hi, please enter number to verify if its prime number or not:");
scanf("%d",&number);

close(pipefds[0]);
write(pipefds[1],&number,sizeof(number));
exit(EXIT_SUCCESS);
}
if (pid>0){
 wait(NULL);
 close(pipefds[1]);
 read(pipefds[0],&number,sizeof(number));

  for (p=2;p<=number/2;++p){

  if(number % p==0){
   flag =1;
   break;
   }
  }

if(number==1){
printf("1 is not a prime number.\n");
}
else{
 if(flag==0)
 printf("%d is a prime number.\n",number);
 else
 printf("%d is not.\n",number);
}

close(pipefds[0]);
}
return EXIT_SUCCESS;
}
void sigint_handler(int sig){
printf("Finished, thank you.\n");
}

