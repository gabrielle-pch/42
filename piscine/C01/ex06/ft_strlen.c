/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpochon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:56:33 by gpochon           #+#    #+#             */
/*   Updated: 2024/09/11 10:59:55 by gpochon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strlen(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[i] != '\0')
	{
		i++;
		n++;
	}
	return (n);
}
