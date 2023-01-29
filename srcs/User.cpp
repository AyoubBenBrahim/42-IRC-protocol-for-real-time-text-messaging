/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchbani <zchbani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:00:18 by yelgharo          #+#    #+#             */
/*   Updated: 2023/01/29 05:51:17 by zchbani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/User.hpp"

User::User(void) : _is_complete(false), _authentification(false) { }
User::User(std::string str) : _nickname(str), _is_complete(false) { }

std::string	User::get_nickname(void)            const { return (_nickname); }
std::string User::get_user(void)                const { return (_user); }
std::string User::get_ip(void)                  const { return (_ip); }
int         User::get_fd(void)                  const { return (_fd); }
bool        User::get_authentification(void)    const { return (_authentification); }
bool        User::get_is_complete(void)         const { return (_is_complete); }

void        User::set_nickname(const std::string nickname)          { _nickname = nickname; }
void		User::set_user(const std::string user)			        { _user = user; }
void        User::set_ip(const std::string ip)                      { _ip = ip; }
void        User::set_fd(int fd)                                    { _fd = fd; }
void        User::set_authentification(const bool authentification) { _authentification = authentification; }
void        User::set_is_complete(const bool is_complete)           { _is_complete = is_complete; }