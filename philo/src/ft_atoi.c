/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seozkan <seozkan@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:12:35 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/16 15:38:47 by seozkan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Alternative to ft_atoi, which provides no proper error handling. This 
function will handle overflows and underflows as well as 
invalid input through errno. 
The variable endptr allows to easily index multiple numbers 
in the same string.*/
