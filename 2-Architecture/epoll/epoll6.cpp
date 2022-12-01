/***************************************************************************
 *   Copyright (C) 2005 by senu                                            *
 *   senu@o2.pl                                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "net.h"

#define dbg


using namespace std;
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
// ClientSocket::ClientSocket)
// {
// 	user=NULL;
// 	auth=false;
// 	
//	
// }
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::decode(int fd, int a, int b)
{

	// err... currently there is 2 bytes in packet 'header', no bitwise operators (we need just 0.4 byte) 
	
	*debug << "Decoding message " << a << ' '<< b << W; 
	cUser * user = user_fds.find(fd);
	switch(a)
	{
		case 48:	//connection request
			*debug << "Connection request" << W;
			break;
			
		case 49: 	// got login in next bytes			
		 	user->name.assign(buff,1,len-1);				
			*debug << "Got login: " << user->name << W;
			break;
			
		case 50: 	// got passwds					
			user->passwd.assign(buff,1,len-1);
			*debug << "Got passwd: " << user->passwd << W;
			if(auth(user->name,user->passwd))
			{
				*debug << "User " << user->name << " logged in" << G;				
				accept_user(user->name,client);				
			}
			else
			{
				*debug << "Authorization failed (" << user->name << ")" << E;			
			}
			break;
			
		case 51: 	// message
			message.assign(buff,2,len-2);
			*debug << "Got message to ";
			if(b==48)			
				*debug << "channel: ";			
			else			
				*debug << "user " << b << ": ";
			*debug << message <<'"'<< W;			
			
			write(fd,message.c_str(),len-4);
			
			 
			
			break;
		case 52: 	// leave
			tmp_user = user_fds.find(fd);
			
			*debug << "User [" << tmp_user->name << " ] ip: [ " << inet_ntoa(client_address.sin_addr) << " ]" << W;
			remove_user(fd);			
			break;			
			
		case 56: 	// root command
			*log << "Got root command" << W;		
			switch(b)	
			{
				case 48:
				{
					*log << "Got root command: [ quit ]" << W;		
					die();					
				}
				case 56:
				{
					*log << "Got root command: [ printf_users ] users on server [ " << users.size << " ]" << W;		
					printf_users();
				
				}
			}
			
			
			
			break;			
	
	}

}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::start()
{
	if ((server_socket=socket(AF_INET,SOCK_STREAM,0))==-1)
     {
          *log << "Cannot create socket" << E;
          die();     	
     }
     
     server_address.sin_family    		=      	AF_INET;
     server_address.sin_port     		=       	htons(9001);
     server_address.sin_addr.s_addr	=		INADDR_ANY; 
     
     bind(server_socket,(struct sockaddr *)&server_address,sizeof(server_address)); 
     
     listen(server_socket,50);
     
  //  	fcntl(server_socket, F_SETFL, O_NONBLOCK);	
    	*log << "Awaiting connections" << G;

}
//-------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------
void cServer::main_loop() //very low level sockets, but very fast
{
	const int MAXEVENTS=50;
	const int INTERVAL=100;	
	
	int nfds, i;
	epollfd =0;
	
		
	epollfd=epoll_create(50);	
	if(epollfd <= 0 )
	{
		*log << "Cannot create epoll fd. Compile your glibc with linux-2.6 headers" << E;		
		die();
	}	
		
	client_size = sizeof(client_address);	
	
//	client = accept(server_socket, NULL,NULL);
	
	fcntl(client, F_SETFL, O_NONBLOCK);	
	ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
	ev.data.fd = server_socket;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_socket, &ev) < 0) 
	{
		*log << "Epoll set insertion error on server socket" << E;						
		die();
	}
	
	
	for(;;) 
	{
		nfds = epoll_wait(epollfd, events, MAXEVENTS, INTERVAL);		
		if(nfds<0)
		{
			*log << "Epoll_wait() returns -1. errno: " << errno << E;
		//	perror("Aw shit!");
			// TODO execute guard..
		}	
		for(i=0; i<nfds; i++) 
		{
			if(events[i].data.fd == server_socket) 
			{
				
			 	client = accept(server_socket, (struct sockaddr *)&client_address, &client_size);
			 	// 	client = accept(server_socket, NULL,NULL);
				if(client < 0)
				{
					*log << "Cannot accept() incoming connection: "<< inet_ntoa(client_address.sin_addr) << E;
					//perror("Aw shit!");
					continue;
				}
		
				*log << "Accepted connection from " << inet_ntoa(client_address.sin_addr) << G;
				fcntl(client, F_SETFL, O_NONBLOCK);	
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = client;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, client, &ev) < 0) 
				{
					*log << "Epoll set insertion error: " << client << E;						
					die();
				}
				create_user("",inet_ntoa(client_address.sin_addr),client);
				
			}
			else
			{	
				client = events[i].data.fd;
				getpeername(client,(struct sockaddr *)&client_address,&client_size);
				*debug << inet_ntoa(client_address.sin_addr) << W;
				len = read(events[i].data.fd, buff, 20);		
				if(len==0)
				{
					*log << "Closed connection with " << inet_ntoa(client_address.sin_addr) << W;
					remove_user(client);
				}
				else if(len<0) 
				{
					*log << "Connection problems to: " << inet_ntoa(client_address.sin_addr) << E;
				}		
				else
				{
					decode(client,buff[0], buff[1]);
				}
			}	
		}
	}
}
cLog * ClientSocket::log = NULL;
cServer * ClientSocket::server=NULL;
#ifdef dbg
	cLog * ClientSocket::debug = NULL;
#endif
cWarnLevel ClientSocket::G=0;
cWarnLevel ClientSocket::W=1;
cWarnLevel ClientSocket::E=2;
