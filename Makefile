SERVER_NAME = server
CLIENT_NAME = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

SERVER_SRC = server.c libft.c 
CLIENT_SRC = client.c libft.c 

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME) : $(SERVER_SRC:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME) : $(CLIENT_SRC:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SERVER_SRC:.c=.o) $(CLIENT_SRC:.c=.o)

fclean: clean
	rm -f $(SERVER_NAME) $(CLIENT_NAME)
	
re: fclean all

.PHONY: all bonus clean fclean re