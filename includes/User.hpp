/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:39:02 by anclarma          #+#    #+#             */
/*   Updated: 2022/06/24 16:51:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User
{
	private:

	public:
		std::string	nickname;

		User(void);
		User(User const &src);
		virtual ~User(void);

		User &operator=(User const &rhs);
};

#endif
