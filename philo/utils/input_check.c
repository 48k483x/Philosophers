#include "../philo.h"


int	*av_to_tab(int ac, char **av)
{
	int	*tab;
	int	i;

	tab = malloc(sizeof(int *) * (ac + 1));
	if (NULL == tab)
		return (NULL);
	i = 0;
	while (i < ac)
	{
		tab[i] = _atoi(av[i]);
		if (tab[i] < 0 || tab[i] > INT_MAX)
		{
			free(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}


bool    input_check(int ac, char **av, int *tab)
{
	(void)av;
    if (ac < 4 || ac > 5 )
		return (false);
	if (!tab)
		return (false);
	return (true);
}
