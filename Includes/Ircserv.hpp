/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ircserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchbani <zchbani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:25:01 by yelgharo          #+#    #+#             */
/*   Updated: 2023/02/24 21:46:49 by zchbani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERV_HPP
# define IRCSERV_HPP

/*<------> INCLUDE Headers <------>*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream> 
#include <fcntl.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <arpa/inet.h>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>

#include "User.hpp"

/*<------> Forward Declaration <------>*/
class User;

/*<------> Alternate names for our data types <------>*/
typedef std::pair<pollfd, User>											client;
typedef std::pair<std::pair<std::string, std::string>, std::set<User> >	channel;
typedef std::vector<client>												client_t;
typedef std::map<std::pair<std::string, std::string>, std::set<User> >	channel_t;

/*<------> DEFINE Variables <------>*/
# define npos			std::string::npos
# define SERVER			"irc.1337.ma"
# define TIMEOUT		(60 * 60 * 1000)
# define BUFFER_SIZE	500
# define END			"\r\n"
# define BACKLOG 		1

/*<------> Define colors  <------>*/
# define PURPLE_BOLD	"\033[1;35m"
# define YELLOW_BOLD	"\033[1;33m"
# define GREEN_BOLD		"\033[1;32m"
# define BLUE_BOLD		"\033[1;34m"
# define RED_BOLD		"\033[1;31m"
# define PURPLE			"\033[35m"
# define YELLOW			"\033[33m"
# define GREEN			"\033[32m"
# define BLUE			"\033[34m"
# define RED			"\033[31m"
# define RST			"\033[0m"

/*<------> Channels and there keys <------>*/
struct s_list {
	
		std::list<std::string>	_channel;
		std::list<std::string>	_key;
};

/*<------> SET Used Functions <------>*/
int				first_in_check(char* s2, std::string s3);
int				getPort(char* s);
// int				tcp_server(int port);
int 			tcp_server(int port, struct addrinfo **p);

bool			channel_operations(client_t &clients, channel_t &channels, std::string msg, int i);
bool			check_input(std::string s, client_t &clients, int &i, int index);
bool			check_user_exist(std::set<User> users, std::string nick);
bool			ifexist(client_t &clients, int i, std::string s);
bool			validNick(std::string nick);

void			cmds_parsing(client_t &clients, channel_t &channels, std::string &msg, int i, std::string password);
void			user_authentification(client_t &clients, std::string input, std::string password, size_t i);
void			join_channels(client_t &clients, size_t i, channel_t &channels, std::string &msg);
void			server_join(std::vector<client> &clients, std::string client_msg, int i);
void			senderr(std::string cmd, int i, client_t &clients, int ern);
void			initialise_poll(std::vector<client> &clients, int fd_size);
void			accept_call(std::vector<client> &clients, int socket_fd, struct addrinfo *p);
void			loop_connections(int socket_fd, std::string password, struct addrinfo *p);

void			bot(client_t &clients, size_t i, std::string &name);
void			close_connection(client_t &clients, size_t i);
void			nickchange_msg(User user, std::string str);
void			tolowstr(std::string &s);
void			welcome_msg(User user);
void			close_connection(client_t &clients, client_t::iterator it);
void 			kick_from_channels(channel_t &channels, const std::string &nick);

std::string		kill_done(std::string nick, std::string reason);
std::string		kill_failed(std::string nick);
std::string		no_privileges(std::string nick);
std::string		rcv_msg(int client_fd, std::vector<client> &clients, size_t i, channel_t &channels);
std::string     channel_response(channel_t &channels, std::string channel_name, User &user);
std::string		reject_msg(std::string cmd, int ern, client_t &clients, int i);
std::string		take_nickname_from_msg(std::string msg);
std::string		trimFront(std::string s, int i);
std::string		trim(std::string s, int i);
std::string		ip_itostr(struct addrinfo  *addr_info);
std::string		msg_format(User &user);

/*<---> SET Mode channel (+/-o) Functions <--->*/
bool            is_there(User &user, std::string &name);
void			omode(client_t &clients, size_t i, channel_t &channels, std::string &msg, std::string &name);
void			o_mode(client_t &clients, size_t i, std::string &msg, std::string &name);
void	        b_mode(client_t &clients, size_t i, channel_t &channels, std::string &msg, std::string &name);

/*<---> BONUS <--->*/
std::string readFromFile(int fd, std::string searched_id);
std::string readFromFile(int fd, std::string searched_id);
void list(int fd);
void upload(int fd, std::string &msg);
void download(int fd, std::string &msg);
void exitFunc(int fd);
int writeToFile(int fd, std::string key, std::string value);
void transfer(client_t &clients, size_t i, int n, std::string &msg);
std::string path_management(int fd, std::string &msg, std::string &filename);

#endif
