/*
 * =====================================================================================
 *
 *       Filename:  Send.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/02/10 16:46:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  dubaokun (1577), baokun.du@net263.com
 *        Company:  net263.com
 *
 * =====================================================================================
 */

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define MAXLINE 10
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 8888
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
	int i, maxi, listenfd, connfd, sockfd, epfd, nfds;
	ssize_t n;
	char line[MAXLINE];
	socklen_t clilen;
	
	struct epoll_event ev,events[20];
	epfd=epoll_create(256);
	struct sockaddr_in clientaddr;
	struct sockaddr_in serveraddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	//no block
	setnonblocking( listenfd);
	ev.data.fd = listenfd;
	ev.events = EPOLLIN;
	epoll_ctl( epfd, EPOLL_CTL_ADD, listenfd, &ev);
	bzero( &serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;

	char *local_addr="127.0.0.1";
	inet_aton( local_addr, &(serveraddr.sin_addr));//htons(SERV_PORT);
	serveraddr.sin_port=htons( SERV_PORT);
	bind( listenfd, (sockaddr *)&serveraddr, sizeof(serveraddr));
	listen( listenfd, LISTENQ);

	maxi = 0; 
	for ( ; ; ) 
	{
		nfds=epoll_wait( epfd, events, 20, 500); 
		for( i=0; i<nfds; ++i)
		{
			if( events[i].data.fd == listenfd)
			{
				connfd = accept( listenfd, (sockaddr *)&clientaddr, &clilen);
				if( connfd < 0)
				{
					perror( "connfd<0");
					exit( 1);
				}
				setnonblocking( connfd);
				char *str = inet_ntoa( clientaddr.sin_addr);
				std::cout << "connect from " << str << std::endl;
				// add
				ev.data.fd = connfd;
				ev.events = EPOLLIN;
				epoll_ctl( epfd, EPOLL_CTL_ADD, connfd, &ev);
				
				// add
				ev.data.fd = connfd;
				ev.events = EPOLLIN;
				epoll_ctl( epfd, EPOLL_CTL_ADD, connfd, &ev);
			
				// delete 
				epoll_ctl( epfd, EPOLL_CTL_DEL, connfd, &ev);
			}
			else if( events[i].events & EPOLLIN)
			{
				if (( sockfd = events[i].data.fd) < 0) 
				{
					continue;
				}
				std::cout << "Data Come!" << std::endl; 
				if (( n = read(sockfd, line, MAXLINE)) < 0) 
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
				
				std::cout << "Data is : " << line << std::endl;
				//epoll_ctl( epfd, EPOLL_CTL_DEL, sockfd, &ev);
				//epoll_ctl( epfd, EPOLL_CTL_DEL, sockfd + 2, &ev);
			}
			else if(events[i].events&EPOLLOUT)
			{    
				sockfd = events[i].data.fd;
				write(sockfd, line, n);
				//设置用于读操作的文件描述符
				ev.data.fd=sockfd;
				//设置用于注测的读操作事件
				ev.events=EPOLLIN|EPOLLET;
				//修改sockfd上要处理的事件为EPOLIN
				epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
			}
		}
	}
}
