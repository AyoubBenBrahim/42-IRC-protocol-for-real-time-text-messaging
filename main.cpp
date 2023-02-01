/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:24:50 by yelgharo          #+#    #+#             */
/*   Updated: 2023/02/01 06:05:41 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/Ircserv.hpp"

int main(int argc, char **argv) {	
	int	port;
	int socket_fd;

	if (argc != 3)
		return (std::cerr << RED_BOLD << " ERROR;\n" << RED \
			<< "\t:./ircserv <port> <password>" << RST << std::endl, 1);
	port = getPort(argv[1]);
	if (port < 1 || port > 65535)
		return (std::cerr << RED_BOLD << "ERROR;\n\tInvalid port number" << \
			RST << std::endl, 1);
	socket_fd = tcp_server(port);
	if(!strlen(argv[2]))
		return (std::cerr << RED_BOLD << "ERROR;\n\tInvalid password" << RST \
			<< std::endl, 1);
	loop_connections(socket_fd, argv[2]);
	return (0);
}


// Need to add a "guest" mode : which is when a client connect to the server be 
// treated as guest till he finish all the authentication steps (PASS, NICK & USER).