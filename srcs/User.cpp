/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:14:12 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/24 17:20:42 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(void)
	: nickname()
{
	return;
}

User::User(User const &src)
	: nickname()
{
	*this = src;
	return;
}

User::~User(void)
{
	return;
}

User &User::operator=(User const &rhs)
{
	if (this != &rhs)
	{
		this->nickname = rhs.nickname;
	}
	return (*this);
}
