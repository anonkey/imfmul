/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/23 14:10:26 by exam              #+#    #+#             */
/*   Updated: 2014/10/23 15:29:28 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (*(s1 + i) == *(s2 + i) && *(s1 + i))
		++i;
	return ((int)(*(s1 + i) - *(s2 + i)));
}

int			ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void		ft_putendl(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

char		ft_add(char a, char b, int *carry)
{
	char	res;

	res = a + b - '0' + (char)*carry;	
	if (res > '9')
	{
		res -= (char)10;
		*carry = 1;
	}
	else
		*carry = 0;
	return (res);
}

char	*ft_infadd(char *res, char *op1, char *op2)
{
	int		len1;
	int		len2;
	int		carry;

	carry = 0;
	len1 = ft_strlen(op1);
	len2 = ft_strlen(op2);
	while (len1 > 0 && len2 > 0)
	{
		*res = ft_add(op1[--len1], op2[--len2], &carry);
		--res;
	}
	if (len1 == 0)
	{
		while (len2 > 0)
		{
			*res = ft_add('0', op2[--len2], &carry);
			--res;
		}
	}
	else
	{
		while (len1 > 0)
		{
			*res = ft_add(op1[--len1], '0', &carry);
			--res;
		}
	}
	if (carry)
		*res = '1';
	else
		++res;
	return (res);
}

char	*ft_mult(char *res, char *op1, char op2)
{
	int		len1;
	int		carry;
	int		tmp;

	len1 = ft_strlen(op1);
	carry = 0;
	while (len1 > 0)
	{
		tmp = (op2 - '0') * (op1[--len1] - '0') + carry;
		*res = (char)(tmp % 10) + '0';
		carry = tmp / 10; 
		--res;
	}	
	if (carry)
		*res = '0' + (char)carry;
	else
		++res;
	return (res);	
}

char	*ft_infmul(char *res, char *op1, char *op2)
{
	char	*buff;
	char	*tmp;
	char	*tmpres;
	int		len1;
	int		len2;
	int		len;
	int		i;

	len2 = ft_strlen(op2);
	len1 = ft_strlen(op1);
	len = len1 * 2 + 2;
	buff = (char *)malloc(sizeof(char) * (len + 1));
	*res = '0';
	tmpres = res;
	buff[len] = '\0';
	i = 0;
	while (len2 > 0)
	{
		if (i != 0)
			buff[len - i] = '0';
		tmp = ft_mult(buff + len - i++ - 1, op1, op2[--len2]);
		tmpres = ft_infadd(res, tmp, tmpres);
	}
	return (tmpres);
}


int		main(int argc, char **argv)
{
	int			sign;
	int			len1;
	int			len2;
	int			len;
	char	*buff;

	if (argc != 3)
		return (-1);
	sign = 0;
	if (argv[1][0] == '-')
	{
		argv[1]++;
		sign ^= 1;
	}
	if (argv[2][0] == '-')
	{
		argv[2]++;
		sign ^= 1;
	}
	len1 = ft_strlen(argv[1]);
	len2 = ft_strlen(argv[2]);
	len = len1 > len2 ? len1 * 2 + 2 : len2 * 2 + 2;
	buff = (char *)malloc(sizeof(char) * (len + 1));
	buff[len] = '\0';
	buff = ft_infmul(buff + len - 1, argv[1], argv[2]);
	if (sign && ft_strcmp(buff, "0"))
		write(1, "-", 1);
	while (*buff == '0' && buff[1])
	    ++buff;
	ft_putendl(buff);
	return (0);
}
