/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_join.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelgharo <yelgharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:34:58 by yelgharo          #+#    #+#             */
/*   Updated: 2023/02/03 18:10:21 by yelgharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Ircserv.hpp"

bool	check_input(std::string s, client_t &clients, int &i, int index)
{
	int	j;
    int r;
	int condition;

	r = 0;
	if (index)
	{
		if (s == "")
			return (senderr("NICK", clients[i].second.get_fd(), 431), false);
		if (!validNick(s))
			return (senderr(s, clients[i].second.get_fd(), 432), false);
		if (!ifexist(clients, i, s))
			return (false);
	} 
	else if (!index) 
	{
		condition = 0;
		j = 0;
		while (s[j]) {
			while (s[j] && !isspace(s[j]))
				j++;
			while (s[j] && isspace(s[j]))
				j++;
			condition++;
            if (condition == 3)
			{
                r = j + 1;
                if (s[j] == ':')
				{
					std::string t = trim(s, r);
					if (t != "")
						return (clients[i].second.set_realname(t), true);
					condition--;
				}
			}
		}
		if (condition < 4)
			return (senderr("USER", clients[i].second.get_fd(), 461), false);
	}
	return (clients[i].second.set_realname(trimFront(s, r - 1)), true);
}

void	server_join(std::vector<client> &clients, std::string client_msg, int i)
{
	int		index ;

	index = client_msg.length();
	if (!client_msg.find("NICK"))
	{
		if (index > 5 && isspace(client_msg[4]))
		{
			std::string nick = trimFront(client_msg, 5);
			if (check_input(nick, clients, i, 1)) {
				clients[i].second.set_nickname(nick);
				std::string s = ":ft_irc NOTICE AUTH :You are registered with a nickname of \"" + nick + "\"\r\n";
				send(clients[i].second.get_fd(), s.c_str(), s.length(), 0);
			}
		}
		else if (clients[i].second.get_nickname().size())
			senderr("NICK", clients[i].second.get_fd(), 2);
		else
			senderr("NICK", clients[i].second.get_fd(), 461);
	}
	else if (!client_msg.find("USER") && clients[i].second.get_nickname().size())
	{
		if (index > 5 && isspace(client_msg[4]))
		{
			std::string _user = trim(client_msg, 5);
			if (check_input(_user, clients, i, 0)) {
				clients[i].second.set_username(trimFront(_user,0));
				std::string s = ":ft_irc NOTICE AUTH :You are registered with a username of \"" \
					+ clients[i].second.get_username() + "\" and real name \"" \
					+ clients[i].second.get_realname() + "\"\r\n";
				send(clients[i].second.get_fd(), s.c_str(), s.length(), 0);
			}
		}
		else
			senderr("USER", clients[i].second.get_fd(), 461);
	}
	if (clients[i].second.get_nickname().size() && clients[i].second.get_username().size()) {
		clients[i].second.set_is_complete(true);
		welcome_msg(clients[i].second);
	}
}
