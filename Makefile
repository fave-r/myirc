##
## Makefile for my_irc in /home/fave_r/rendu/PSU_2014_myirc
##
## Made by romaric
## Login   <fave_r@epitech.net>
##
## Started on  Mon Apr  6 10:58:19 2015 romaric
## Last update Wed Apr 22 14:45:17 2015 romaric
##

CC=		gcc

RM=		rm -f

INCLUDES=	-I./include

CFLAGS=		-W -Wall -Wextra

S_NAME=		server

C_NAME=		client

U_SRC=		utils/base_func.c			\
		utils/common_func.c 			\
		utils/get_next_line.c 			\
		utils/port_func.c 			\
		utils/str_func.c			\
		utils/stwt.c				\
		utils/xfunction.c			\
		utils/x_tcp.c				\
		utils/CircularBuffer/circular_buffer.c	\
		utils/CircularBuffer/get_value.c	\
		utils/CircularBuffer/read_cb.c

P_SRC=		utils/Parser/circular_linked_channel.c 	\
		utils/Parser/parser_conf.c

S_SRC=		src_server/main.c			\
		src_server/fd_func.c			\
		src_server/read_com.c			\
		src_server/while_serv.c			\
		src_server/commands/my_accept_file.c	\
		src_server/commands/my_join.c		\
		src_server/commands/my_list.c		\
		src_server/commands/my_msg.c		\
		src_server/commands/my_nick.c		\
		src_server/commands/my_part.c		\
		src_server/commands/my_send_file.c	\
		src_server/commands/my_users.c		\
		src_server/commands/my_user.c		\
		src_server/clone.c			\
		src_server/commands/my_hello.c		\
		src_server/commands/my_join_msg.c	\
		src_server/commands/my_part_msg.c	\
		src_server/commands/my_ping.c		\
		src_server/commands/my_pong.c		\
		src_server/commands/my_quit.c

C_SRC=		src_client/client.c			\
		src_client/common_func.c		\
		src_client/init_func.c			\
		src_client/read_socket.c		\
		src_client/read_stdin.c			\
		src_client/stdin-func/my_join.c		\
		src_client/stdin-func/my_list.c		\
		src_client/stdin-func/my_message.c	\
		src_client/stdin-func/my_msg.c		\
		src_client/stdin-func/my_nick.c		\
		src_client/stdin-func/my_part.c		\
		src_client/stdin-func/my_quit.c		\
		src_client/stdin-func/my_server.c	\
		src_client/stdin-func/my_users.c	\
		src_client/socket-func/my_code.c	\
		src_client/socket-func/my_error.c	\
		src_client/socket-func/my_join.c	\
		src_client/socket-func/my_nick.c	\
		src_client/socket-func/my_notice.c	\
		src_client/socket-func/my_part.c	\
		src_client/socket-func/my_ping.c	\
		src_client/socket-func/my_privmsg.c	\
		src_client/socket-func/my_quit.c

U_OBJ=		$(U_SRC:.c=.o)

P_OBJ=		$(P_SRC:.c=.o)

S_OBJ=		$(S_SRC:.c=.o)

C_OBJ=		$(C_SRC:.c=.o)

all:		$(U_OBJ) $(S_NAME) $(C_NAME)

serveur:	$(U_OBJ) $(S_NAME)

clients:	$(U_OBJ) $(C_NAME)

$(S_NAME):	$(U_OBJ) $(P_OBJ) $(S_OBJ)
		@echo -e "\033[32m[Building] \033[0;m" | tr -d '\n'
		$(CC) -o $@ $(U_OBJ) $(P_OBJ) $(S_OBJ) $(CFLAGS)

$(C_NAME):	$(U_OBJ) $(C_OBJ)
		@echo -e "\033[32m[Building] \033[0;m" | tr -d '\n'
		$(CC) -o $@ $(U_OBJ) $(C_OBJ) $(CFLAGS)

%.o:		%.c
		@echo -e "\033[33m[Doing object] \033[0;m" | tr -d '\n'
		$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
		@echo -e "\033[31m[Cleaning] \033[0;m" | tr -d '\n'
		$(RM) $(U_OBJ)
		@echo -e "\033[31m[Cleaning] \033[0;m" | tr -d '\n'
		$(RM) $(P_OBJ)
		@echo -e "\033[31m[Cleaning] \033[0;m" | tr -d '\n'
		$(RM) $(S_OBJ)
		@echo -e "\033[31m[Cleaning] \033[0;m" | tr -d '\n'
		$(RM) $(C_OBJ)

fclean:		clean
		@echo -e "\033[31m[Filecleaning] \033[0;m" | tr -d '\n'
		$(RM) $(S_NAME)
		@echo -e "\033[31m[Filecleaning] \033[0;m" | tr -d '\n'
		$(RM) $(C_NAME)

re:		fclean all

.PHONY:		all fclean re
