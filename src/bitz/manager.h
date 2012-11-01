/*
 *	bitz-server, An ICAP server implementation in C++
 *	Copyright (C) 2012	Uditha Atukorala
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef BITZ_MANAGER_H
#define BITZ_MANAGER_H

#include <string>              // for string type
#include <map>                 // for std::map
#include <unistd.h>            // pid_t, fork() etc.
#include <socket/socket.h>     // socket-library

#include "manager_exception.h"
#include "worker.h"
#include "request_handler.h"

#ifndef BITZ_MAX_WORKERS
#define BITZ_MAX_WORKERS 2
#endif

#ifndef BITZ_MAX_WORKER_REQUESTS
#define BITZ_MAX_WORKER_REQUESTS 100
#endif


namespace bitz {

	class Manager {
	public:

		struct worker_pool_t {
			pid_t worker_pid;
			unsigned int worker_id;
			Worker * worker;
		};

		struct manager_t {
			bool worker;
			unsigned int max_workers;
			unsigned int max_worker_requests;
			unsigned int workers_count;
			unsigned int worker_id;

			socketlibrary::TCPServerSocket * socket;
			worker_pool_t * worker_pool;
		};

		typedef std::map<std::string, RequestHandler *> req_handlers_t;


		/**
		*   Note: backlog = SOMAXCONN (from sys/socket.h)
		*/
		Manager( unsigned short port, const std::string &address = "", int backlog = 128 );

		/**
		*   deconstructor
		*/
		virtual ~Manager();

		virtual void spawn( unsigned int max_workers = BITZ_MAX_WORKERS, unsigned int max_worker_requests = BITZ_MAX_WORKER_REQUESTS ) throw( ManagerException );
		virtual void shutdown( bool graceful = true ) throw();
		virtual void reap_worker( pid_t worker_pid ) throw();
		virtual void manager_workers() throw();

	private:
		manager_t         _manager;
		req_handlers_t    _req_handlers;

		virtual void spawn_worker( unsigned int worker_id ) throw( ManagerException );

	};

} /* end of namespace bitz */

#endif /* !BITZ_MANAGER_H */

