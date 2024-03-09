#include "philo.h"

void  exit_with_message(char *message)
{
  printf("%s\n", message);
  return ;
}

int main(int ac, char *av[])
{
  (void)av;
  if (ac < 5 || ac > 6)
    exit_with_message("Usage: ./philo [args]");
}