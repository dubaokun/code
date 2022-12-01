#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define MAXLINE 10

#define OPEN_MAX 100

#define LISTENQ 20

#define SERV_PORT 5555

#define INFTIM 1000


//�̳߳�������нṹ��

struct task{
  int fd;            //��Ҫ��д���ļ�������

  struct task *next; //��һ������

};

//���ڶ�д�������������洫�ݲ���

struct user_data{
  int fd;
  unsigned int n_size;
  char line[MAXLINE];
};

//�̵߳�������

void * readtask(void *args);

void * writetask(void *args);


//����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ������¼�

struct epoll_event ev,events[20];

int epfd;

pthread_mutex_t mutex;

pthread_cond_t cond1;

struct task *readhead=NULL,*readtail=NULL,*writehead=NULL;


void setnonblocking(int sock)
{
     int opts;
     opts=fcntl(sock,F_GETFL);
     if(opts<0)
     {
          perror("fcntl(sock,GETFL)");
          exit(1);
     }
    opts = opts|O_NONBLOCK;
     if(fcntl(sock,F_SETFL,opts)<0)
     {
          perror("fcntl(sock,SETFL,opts)");
          exit(1);
     }   
}


int main()
{
     int i, maxi, listenfd, connfd, sockfd,nfds;
     pthread_t tid1,tid2;
    
     struct task *new_task=NULL;
     struct user_data *rdata=NULL;
     socklen_t clilen;
    
     pthread_mutex_init(&mutex,NULL);
     pthread_cond_init(&cond1,NULL);
     //��ʼ�����ڶ��̳߳ص��߳�

     pthread_create(&tid1,NULL,readtask,NULL);
     pthread_create(&tid2,NULL,readtask,NULL);
    
     //�������ڴ���accept��epollר�õ��ļ�������   
     epfd=epoll_create(256);

     struct sockaddr_in clientaddr;
     struct sockaddr_in serveraddr;
     listenfd = socket(AF_INET, SOCK_STREAM, 0);
     //��socket����Ϊ��������ʽ

     setnonblocking(listenfd);
     //������Ҫ������¼���ص��ļ�������

     ev.data.fd=listenfd;
     //����Ҫ������¼�����

     ev.events=EPOLLIN|EPOLLET;
     //ע��epoll�¼�

     epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
    
     bzero(&serveraddr, sizeof(serveraddr));
     serveraddr.sin_family = AF_INET;
    
     char *local_addr="200.200.200.222";
     inet_aton(local_addr,&(serveraddr.sin_addr));//htons(SERV_PORT);
     serveraddr.sin_port=htons(SERV_PORT);
     bind(listenfd,(sockaddr *)&serveraddr, sizeof(serveraddr));
     listen(listenfd, LISTENQ);
    
     maxi = 0;
     for ( ; ; ) {
          //�ȴ�epoll�¼��ķ���

          nfds=epoll_wait(epfd,events,20,500);
          //�����������������¼�     
        for(i=0;i<nfds;++i)
        {
               if(events[i].data.fd==listenfd)
               {
                   
                    connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen);
                    if(connfd<0){
                      perror("connfd<0");
                      exit(1);
                   }
                    setnonblocking(connfd);
                   
                    char *str = inet_ntoa(clientaddr.sin_addr);
                    std::cout<<"connec_ from >>"<<str<<std::endl;
                    //�������ڶ��������ļ�������

                    ev.data.fd=connfd;
                    //��������ע��Ķ������¼�

                 ev.events=EPOLLIN|EPOLLET;
                    //ע��ev

                 epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
               }
            else if(events[i].events&EPOLLIN)
            {
                    printf("reading!\n");                
                    if ( (sockfd = events[i].data.fd) < 0) continue;
                    new_task=new task();
                    new_task->fd=sockfd;
                    new_task->next=NULL;
                    //����µĶ�����

                    pthread_mutex_lock(&mutex);
                    if(readhead==NULL)
                    {
                      readhead=new_task;
                      readtail=new_task;
                    }   
                    else

                    {   
                     readtail->next=new_task;
                      readtail=new_task;
                    }   
                   //�������еȴ�cond1�������߳�

                    pthread_cond_broadcast(&cond1);
                    pthread_mutex_unlock(&mutex);  
              }
               else if(events[i].events&EPOLLOUT)
               {   
              rdata=(struct user_data *)events[i].data.ptr;
                 sockfd = rdata->fd;
                 write(sockfd, rdata->line, rdata->n_size);
                 delete rdata;
                 //�������ڶ��������ļ�������

                 ev.data.fd=sockfd;
                 //��������ע��Ķ������¼�

               ev.events=EPOLLIN|EPOLLET;
                 //�޸�sockfd��Ҫ������¼�ΪEPOLIN

               epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
               }
                             
          }
         
     }
}

void * readtask(void *args)
{
   
   int fd=-1;
   unsigned int n;
   //���ڰѶ����������ݴ��ݳ�ȥ

   struct user_data *data = NULL;
   while(1){
        
        pthread_mutex_lock(&mutex);
        //�ȴ���������в�Ϊ��

        while(readhead==NULL)
             pthread_cond_wait(&cond1,&mutex);
        
        fd=readhead->fd;
        //���������ȡ��һ��������

        struct task *tmp=readhead;
        readhead = readhead->next;
        delete tmp;
        pthread_mutex_unlock(&mutex);
        data = new user_data();
        data->fd=fd;
        if ( (n = read(fd, data->line, MAXLINE)) < 0) {
           
           if (errno == ECONNRESET) {
             close(fd);
             
          } else

             std::cout<<"readline error"<<std::endl;
           if(data!=NULL)delete data;
        } else if (n == 0) {
            close(fd);
           printf("Client close connect!\n");
           if(data!=NULL)delete data;
        } else{
        
        data->n_size=n;
        //������Ҫ���ݳ�ȥ������

        ev.data.ptr=data;
        //��������ע���д�����¼�

        ev.events=EPOLLOUT|EPOLLET;
        //�޸�sockfd��Ҫ������¼�ΪEPOLLOUT

        epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
       }
   }
}
