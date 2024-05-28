/*
EPOLLOUT����ʾ��Ӧ���ļ�����������д�� 
EPOLLPRI����ʾ��Ӧ���ļ��������н��������ݿɶ����Ҳ�̫������ʲô��˼������������client�ر� socket�����������¼����� 
EPOLLERR����ʾ��Ӧ���ļ��������������� 
EPOLLHUP����ʾ��Ӧ���ļ����������Ҷϣ� 
EPOLLET����ʾ��Ӧ���ļ����������¼������� 
*/

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define MAXLINE 10
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5555
#define INFTIM 1000


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
     int i, maxi, listenfd, connfd, sockfd,epfd,nfds;
     ssize_t n;
     char line[MAXLINE];
     socklen_t clilen;
     //����epoll_event�ṹ��ı���,ev����ע���¼�,�������ڻش�Ҫ�������¼�
     struct epoll_event ev,events[20];
     //�������ڴ���accept��epollר�õ��ļ�������
     epfd=epoll_create(256);
     struct sockaddr_in clientaddr;
     struct sockaddr_in serveraddr;
     listenfd = socket(AF_INET, SOCK_STREAM, 0);
     //��socket����Ϊ��������ʽ
     setnonblocking(listenfd);
     //������Ҫ�������¼���ص��ļ�������
     ev.data.fd=listenfd;
     //����Ҫ�������¼�����
     ev.events=EPOLLIN|EPOLLET;
     //ע��epoll�¼�
     epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
     bzero(&serveraddr, sizeof(serveraddr));
     serveraddr.sin_family = AF_INET;

     char *local_addr="200.200.200.204";
     inet_aton(local_addr,&(serveraddr.sin_addr));//htons(SERV_PORT);
     serveraddr.sin_port=htons(SERV_PORT);
     bind(listenfd,(sockaddr *)&serveraddr, sizeof(serveraddr));
     listen(listenfd, LISTENQ);
     
     maxi = 0; 
     for ( ; ; ) 
     {
          //�ȴ�epoll�¼��ķ���
          nfds=epoll_wait(epfd,events,20,500);
          //�����������������¼�      
          for(i=0;i<nfds;++i)
          {
               if(events[i].data.fd==listenfd)
               {
                    connfd = accept(listenfd,(sockaddr *)&clientaddr, &clilen);
                    if(connfd<0)
                    {
                         perror("connfd<0");
                         exit(1);
                    }
                    setnonblocking(connfd);
                    char *str = inet_ntoa(clientaddr.sin_addr);
                    std::cout<<"connect from "<_u115 ?tr<<std::endl;
                    //�������ڶ��������ļ�������
                    ev.data.fd=connfd;
                    //��������ע��Ķ������¼�
                    ev.events=EPOLLIN|EPOLLET;
                    //ע��ev
                    epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
               }
               else if(events[i].events&EPOLLIN)
               {
                    if ( (sockfd = events[i].data.fd) < 0) 
                    {
                    	continue;
                    }
                    if ( (n = read(sockfd, line, MAXLINE)) < 0) 
                    {

                         if (errno == ECONNRESET)
                         {
                              close(sockfd);
                              events[i].data.fd = -1;
                         } 
                         else 
                         {
                              std::cout<<"readline error"<<std::endl;
                         }

                    } 
                    else if (n == 0) 
                    {
                         close(sockfd);
                         events[i].data.fd = -1;
                    }

                    //��������д�������ļ�������
                    ev.data.fd=sockfd;
                    //��������ע���д�����¼�
                    ev.events=EPOLLOUT|EPOLLET;
                    //�޸�sockfd��Ҫ�������¼�ΪEPOLLOUT
                    epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
               }
               else if(events[i].events&EPOLLOUT)
               {    
                    sockfd = events[i].data.fd;
                    write(sockfd, line, n);
                    //�������ڶ��������ļ�������
                    ev.data.fd=sockfd;
                    //��������ע��Ķ������¼�
                    ev.events=EPOLLIN|EPOLLET;
                    //�޸�sockfd��Ҫ�������¼�ΪEPOLIN
                    epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
               }
          }
     }
}