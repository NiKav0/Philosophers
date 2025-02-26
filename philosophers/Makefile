
NAME = philo
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = main.c utils.c timer.c printer.c threader.c \

OBJ = ${SRC:.c=.o}
CLEANER = rm -rf

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${FLAGS} ${SRC} -o ${NAME}

%.o: %.c
	${CC} -c $< -o $@

clean :
	${CLEANER} ${OBJ}

fclean :
	${CLEANER} ${OBJ} ${NAME}

re : fclean all
