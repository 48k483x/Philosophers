NAME = philo
CFLAGS =  -Wall -Wextra -Werror -pthread
SRCS =  philo.c

$(NAME) :
	@cc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	@rm -rf $(NAME)

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)