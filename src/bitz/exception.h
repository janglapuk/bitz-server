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


#ifndef BITZ_EXCEPTION_H
#define BITZ_EXCEPTION_H

#include <exception>        // for exception class
#include <string>           // for std::string

namespace bitz {

	class Exception : public std::exception {
	public:
		Exception( const std::string &message, bool inclSystemMessage = false ) throw();
		virtual ~Exception() throw();

		virtual const char * what() const throw();

	private:
		std::string _message;
	};

} /* end of namespace bitz */

#endif /* !BITZ_EXCEPTION_H */

