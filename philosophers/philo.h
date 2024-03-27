# ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/time.h>

#define PHILOS_MAX 300

// struct of philosophers
typedef struct s_philo
{
    pthread_t thread; 
    int id;
    int eating;
    int meals_eaten;
    size_t last_meal;
    size_t phil_death_time;
    size_t phil_eat_time;
    size_t phil_sleep_time;
    size_t start_time;
    int eat_times;
    int philos_num;
    int *dead;
    pthread_mutex_t r_fork;
    pthread_mutex_t l_fork;
    // pthread_mutex_t *write_lock;
    // pthread_mutex_t *dead_lock;
    // pthread_cond_t *meal_lock;
} t_philo;

typedef struct s_prog
{
    int death_flag;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
    pthread_mutex_t *write_lock;
} t_prog;

typedef struct s_args
{
    int philos_num;
    int philos_eat_time;
    int philos_sleep_time;
    int philos_die_time;
    int philos_eat_times;
} t_args;

void print_args(t_args args);
void print_philo(t_philo philo);
// utils.c functions
int _atoi(char *s);
int _isdigit(char c);
bool exit_error(char *s);
bool is_digit(char **av);
long get_time(void);

// init functions
bool init_args(t_args *args, char **av, int ac);
bool init_philos(t_args *args, t_philo *philos);

// routine functions
void eating(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);
void *philo_life(void *philo);

#endif // PHILO_H