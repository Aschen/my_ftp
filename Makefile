##
## Makefile for  in /home/maret_a/Projets/Ftp
## 
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
## 
## Started on  08/04/2014 14:52
##

CC	=	gcc

CFLAGS	=	-Wall -Wextra  -W -Isrv/include -Icli/include -Icommon/include -lpthread

SRV_SRC	=	srv/sources/main.c \
		common/sources/error.c \
		common/sources/log.c \
		srv/sources/server.c \
		srv/sources/server_handle.c \
		srv/sources/server_commands.c \
		srv/sources/commands_1.c \
		srv/sources/commands_2.c \
		srv/sources/commands_3.c \
		srv/sources/commands_4.c \

SRV_OBJ	=	$(SRV_SRC:.c=.o)

SERVER	=	serveur


CLI_SRC	=	cli/sources/main.c \
		common/sources/error.c \
		common/sources/log.c \
		cli/sources/client.c \
		cli/sources/client_handle.c \
		cli/sources/client_commands.c \
		cli/sources/commands_1.c \
		cli/sources/commands_2.c \

CLI_OBJ	=	$(CLI_SRC:.c=.o)

CLIENT	=	client


all:	$(SERVER) $(CLIENT)

$(SERVER):	$(SRV_OBJ)
		$(CC) -o $(SERVER) $(SRV_OBJ) -lpthread

$(CLIENT):	$(CLI_OBJ)
		$(CC) -o $(CLIENT) $(CLI_OBJ) -lpthread

clean:
	rm -f $(SRV_OBJ)
	rm -f $(CLI_OBJ)

fclean:	clean
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: fclean all

.PHONY:	all client server common clean fclean re