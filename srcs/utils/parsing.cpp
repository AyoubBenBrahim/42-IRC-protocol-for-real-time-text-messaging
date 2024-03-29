/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 04:17:49 by yelgharo          #+#    #+#             */
/*   Updated: 2023/02/12 16:03:14 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/Ircserv.hpp"

bool	ifexist(client_t &clients, int i, std::string s)
{
	if (clients[i].second.get_nickname() == s)
		return (senderr(s, i, clients, 433), false);
	for (client_t::iterator it = clients.begin(); it != clients.end(); it++)
		if (s == it->second.get_nickname())
			return (senderr(s, i, clients, 436), false);
	return (true);
}

bool	changenick(client_t &clients, std::string &cmd, int i, int j)
{
	std::string tmp;
    std::string oldNick;

    oldNick = trimFront(cmd, 1);
    tolowstr(oldNick);
	if (!isspace(cmd[j - 1]) || !isspace(cmd[j + 4]))
		return (senderr("NICK", i, clients, 431), false);
	if (clients[i].second.get_nickname() == oldNick)
    
		if (!check_input(trimFront(cmd, j + 5), clients, i, 1))
			return (false);
	tmp = clients[i].second.get_nickname();
	clients[i].second.set_nickname(trimFront(cmd, j + 5));
	return (nickchange_msg(clients[i].second, tmp),true);
}

void	cmds_parsing(client_t &clients, channel_t &channels, \
	std::string &msg, int i, std::string password)
{
	std::string tmp;
	(void) channels;

	for (size_t	pos = msg.find(END); pos != npos; pos = msg.find(END))
	{
		if (pos == 0)
			std::cout << YELLOW << "WARNING" << RST <<std::endl;
		tmp = msg.substr(0, pos);
		msg.erase(0, pos + 2);
		if (!clients[i].second.get_is_complete())
		{
			if (!tmp.find("PASS"))
				user_authentification(clients, tmp, password, i);
			else if (clients[i].second.get_authentification())
				server_join(clients, tmp, i);
		} 
		else if (clients[i].second.get_is_complete())
		{
			if (!tmp.find("PASS"))
				senderr("PASS", i, clients, 462);
			else if (!tmp.find("USER"))
				senderr("USER", i, clients, 462);
			if (channel_operations(clients, channels, tmp, i))
				break;
		}
	}
}
