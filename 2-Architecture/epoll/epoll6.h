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
 
// libSockets
/*#include <Socket.h>
#include <SocketHandler.h>
#include <TcpSocket.h>
#include <Utility.h>
#include <ListenSocket.h>
 
*/





#include "cserver.h"

#define dbg
class ClientSocket 
{
   public:
   	void OnRawData();
	void OnAccept();	
	void decode(int, int);	
	static cLog * log;
#ifdef dbg	
	static cLog * debug;
#endif	
	static cWarnLevel G,W,E;
	static cServer *server;	
	
   protected:
   	char buff[100]; 
	
	bool auth;
	
};
