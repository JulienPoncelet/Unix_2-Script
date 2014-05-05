/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jponcele <jponcele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 15:03:30 by jponcele          #+#    #+#             */
/*   Updated: 2013/12/04 17:24:17 by jponcele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int					ft_isalpha(int value)
{
	if (value < 0101 || value > 0132)
	{
		if (value < 0141 || value > 0172)
			return (0);
	}
	return (1);
}