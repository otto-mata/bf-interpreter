/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblochet <tblochet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:01:13 by tblochet          #+#    #+#             */
/*   Updated: 2024/12/06 21:14:48 by tblochet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

void	ft_bzero(void *mem, unsigned long sz)
{
	while (sz--)
		*(unsigned char *)mem = 0;
}

int	matching_bracket_frwd(char const *code)
{
	int	i;
	int	lvl;

	i = 0;
	lvl = 0;
	while (code[i])
	{
		if (code[i] == '[')
			lvl++;
		else if (lvl == 0 && code[i] == ']')
			return (i);
		if (code[i] == ']')
			lvl--;
		i++;
	}
	return (-1);
}

int	matching_bracket_bkwd(char const *code, int m)
{
	int	i;
	int	lvl;

	i = m - 1;
	lvl = 0;
	while (i > 0)
	{
		if (code[i] == ']')
			lvl++;
		else if (lvl == 0 && code[i] == '[')
			return (i);
		if (code[i] == '[')
			lvl--;
		i--;
	}
	return (-1);
}

void	bf(char const *code)
{
	uint8_t	band[8192];
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_bzero(band, 8192);
	while (code[j])
	{
		if (code[j] == '>')
			i++;
		else if (code[j] == '<')
			i--;
		else if (code[j] == '+')
			band[i]++;
		else if (code[j] == '-')
			band[i]--;
		else if (code[j] == '.')
			write(1, &band[i], 1);
		else if (code[j] == '[' && !band[i])
			j += matching_bracket_frwd(&code[j + 1]) + 1;
		else if (code[j] == ']' && band[i])
			j = matching_bracket_bkwd(code, j);
		j++;
	}
}

int	main(int argc, char const *argv[])
{
	if (argc < 2)
		return (1);
	bf(argv[1]);
	return (0);
}
