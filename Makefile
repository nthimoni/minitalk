SRCDIR = src/
OBJDIR = bin/
INCDIR = include/
FTPATH = libft/
FTINC = $(FTPATH)include/
LIBFT = $(FTPATH)libft.a
######################################################################
SRCSER = serveur.c
SRCCLI = client.c
OBJSER = $(addprefix $(OBJDIR),$(SRCSER:.c=.o))
OBJCLI = $(addprefix $(OBJDIR),$(SRCCLI:.c=.o))
######################################################################
CC = clang -g
CFLAGS = #-Wall -Wextra -Werror
LINK = -lft
INCPATH = -I$(INCDIR) -I$(FTINC)
LIBPATH = -L$(FTPATH)
SERVER = server
CLIENT = client
######################################################################
all:  $(CLIENT) $(SERVER)

$(SERVER): $(LIBFT) $(OBJSER)
	$(CC) $(OBJSER) $(LIBPATH) $(LINK) -o $(SERVER)

$(CLIENT): $(LIBFT) $(OBJCLI)
	$(CC) $(OBJCLI) $(LIBPATH) $(LINK) -o $(CLIENT)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) $(INCPATH) $< -o $@

$(LIBFT):
	make -C $(FTPATH)

clean:
	rm -rf $(OBJSER)
	rm -rf $(OBJCLI)

fclean: clean
	#make fclean -C $(FTPATH)
	rm -f $(SERVER) $(CLIENT)

re: fclean $(SERVER) $(CLIENT)

.PHONY: all libft clean fclean re
