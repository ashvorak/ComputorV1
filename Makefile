# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/18 16:20:34 by oshvorak          #+#    #+#              #
#    Updated: 2019/05/14 20:38:00 by oshvorak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = computor

CC = g++

CFLAGS = -Wall -Wextra -Werror -std=c++11

SRC = 	./src/main.cpp ./src/Parser.cpp ./src/ErrorManager.cpp ./src/Solver.cpp

OBJS =	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)

.cpp.o:
	@$(CC) $(CFLAGS) -c $<  -o $@

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
