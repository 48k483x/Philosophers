#include "philo.h"

bool	exit_error(char *s)
{
	printf("%s\n", s);
	return (false);
}

void	init_prog(t_philo *philos, t_prog *prog)
{
	prog->death_flag = 0;
	prog->philo = philos;
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
}

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			philos[PHILOS_MAX];
	t_prog			prog;
	pthread_mutex_t	forks[PHILOS_MAX];

	if (!init_args(&args, av, ac))
		return (1);
	init_forks(forks, philos);
	if (!init_philos(&args, philos, &prog, forks))
		return (1);
	if (!init_thread(philos, forks, &prog))
		return (1);
	destroy_all(NULL, &prog, forks, philos);
}
