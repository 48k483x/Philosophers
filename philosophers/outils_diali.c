#include "philo.h"

void print_args(t_args args) {
    // for (int i = 1; i <= args.philos_num; i++)
    //     printf("Philosopher %d\n", i);
    printf("philos_num: %d\n", args.philos_num);
    printf("philos_eat_time: %d\n", args.philos_eat_time);
    printf("philos_sleep_time: %d\n", args.philos_sleep_time);
    printf("philos_die_time: %d\n", args.philos_die_time);
    printf("philos_eat_times: %d\n", args.philos_eat_times);
}

void print_philo(t_philo philo) {
    printf("Philo id: %d\n", philo.id);
    printf("Philo is_eating: %d\n", philo.eating);
    printf("Philo last_eat: %ld\n", philo.last_meal);
    printf("Philo eat times: %d\n", philo.eat_times);
    printf("Philo meals eaten: %d\n", philo.meals_eaten);
    printf("\n");
}