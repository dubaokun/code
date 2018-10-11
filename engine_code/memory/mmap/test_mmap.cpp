#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/mman.h>  
#include <sys/stat.h>  

typedef struct{  
  char name[20];  
  short age;  
  float score;  
  char sex;  
}student;  

bool init_file(int count)
{
	int fd=open("user.dat",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
	student st;
	for(int i = 0; i < count; ++i)
	{
		memset(&st, 0x00, sizeof(student));
		snprintf(st.name, 20, "name%d", i);
		st.age = i;
		st.score = 1.0;
		st.sex = '1';
		write(fd, &st, sizeof(student));
	}
	close(fd);
}

int main()  
{  
	init_file(8);

	student *p,*pend;    
	//打开文件描述符号  
	int fd;  
	/*打开文件*/  
	fd=open("user.dat",O_RDWR);  
    if(fd==-1){//文件不存在  
        fd=open("user.dat",O_RDWR|O_CREAT,0666);  
        if(fd==-1){  
            printf("打开或创建文件失败:%m\n");  
            exit(-1);  
        }  
    } 
 
  	//打开文件ok，可以进行下一步操作  
  	printf("open ok!\n");    

  	//获取文件的大小，映射一块和文件大小一样的内存空间，如果文件比较大，可以分多次，一边处理一边映射；  
  	struct stat st; //定义文件信息结构体  

  	/*取得文件大小*/  
  	int r=fstat(fd,&st);  
  	if(r==-1){  
      	printf("获取文件大小失败:%m\n");  
      	close(fd);  
      	exit(-1);  
  	}
  
  int len=st.st_size;      
  /*把文件映射成虚拟内存地址*/  
  p=(student *)mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);      
  if(p==NULL || p==(void*)-1){  
      printf("映射失败:%m\n");  
      close(fd);  
      exit(-1);  
  }  


  /*定位到文件开始*/  
  pend=p;   
  /*通过内存读取记录*/  
  int i=0;  
  while(i<(len/sizeof(student)))  
  {  
    printf("index [%d]\n",i);  
    printf("name=%s\n",p[i].name);  
    printf("age=%d\n",p[i].age);  
    printf("score=%f\n",p[i].score);  
    printf("sex=%c\n",p[i].sex);  
    i++;  
  }    
  /*卸载映射*/  
  munmap(p,len);  
  /*关闭文件*/      
  close(fd);      
}  
