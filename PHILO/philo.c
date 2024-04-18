#include "philo.h"

bool	exit_error(char *s)
{
	printf("%s\n", s);
	return (false);
}

int	error(void)
{
	printf("\033[1;33m");
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃            Please enter 4 or 5 arguments      ┃\n");
	printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("┃             [\033[1;36m1\033[1;33m] Number of philosophers\n");
	printf("┃             [\033[1;36m2\033[1;33m] Time to die\n");
	printf("┃             [\033[1;36m3\033[1;33m] Time to eat\n");
	printf("┃             [\033[1;36m4\033[1;33m] Time to sleep\n");
	printf("┃             [\033[1;36m5\033[1;33m] Number of meals\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n");
	return (0);
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

	if (!(ac == 5 || ac == 6))
		return (error());
	if (!init_args(&args, av, ac))
		return (1);
	init_forks(forks, _atoi(av[1]));
	if (!init_philos(&args, philos, &prog, forks))
		return (1);
	if (!init_thread(philos, forks, &prog))
		return (1);
	destroy_all(NULL, &prog, forks, philos);
}
