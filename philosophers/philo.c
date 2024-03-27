#include "philo.h"

bool exit_error(char *s)
{
    printf("%s\n", s);
    return (false);
}

int main(int ac, char **av)
{
    t_args args;
    t_philo philos[PHILOS_MAX];

    if (!init_args(&args, av, ac))
        return (1);
    if (!init_philos(&args, philos))
        return (1);
    for(int i = 0; i < args.philos_num; i++)
        print_philo(philos[i]);
}
