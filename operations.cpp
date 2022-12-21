#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

struct Operations
{
  int a;
  int b;
  std::string op;
  int index;
};

void* routine(void* arg)
{
  int result;
  Operations* operation = (Operations*) arg;
  if(operation -> op == "s")
  {
	  result = operation -> a + operation -> b;
  }
  else if(operation -> op == "m")
  {
	  result = operation -> a * operation -> b;
  }
  else if(operation -> op == "ss")
  {
	  result = (operation -> a * operation -> a) + (operation -> b * operation -> b);
  }
  else
  {
     std::cout << "No such operation!\n";
  }
  std::string res;
  res = std::to_string(operation -> a) + " " + operation -> op + " " + std::to_string(operation -> b) + " = " + std::to_string(result);
  std::string file = "out_";
  file += std::to_string(operation -> index);
  int fd = open(file.c_str(), O_RDWR | O_CREAT, 0644);
  write(fd, res.c_str(), res.size());
  close(fd);
  ++(operation -> index);
  return NULL;
}

int main(){

int n;
std::cin>>n;
pthread_t ptid[n];
Operations operations [n];
for(int i=0;i<n;++i)
{
  operations[i].index = i + 1;	
  std::cin>>operations[i].a>>operations[i].b>>operations[i].op;
  int th = pthread_create(&ptid[i], NULL,routine, &operations[i]);

  if(th != 0)
  {
	  std::cerr<<"Could not create thread"<<" ";
	  return th;
  }
  pthread_join(ptid[i], NULL);
}
  pthread_exit(NULL);
}
