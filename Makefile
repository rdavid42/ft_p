SERVER_SRC_PATH			=	src/server/
CLIENT_SRC_PATH			=	src/client/
SHARED_SRC_PATH			=	src/shared/
OBJ_PATH				=	obj/
SERVER_OBJ_PATH			=	$(OBJ_PATH)server/
CLIENT_OBJ_PATH			=	$(OBJ_PATH)client/
SHARED_OBJ_PATH			=	$(OBJ_PATH)shared/

CLIENT_SRC				=	$(shell ls $(CLIENT_SRC_PATH) | grep .c$$)
CLIENT_OBJ				=	$(patsubst %.c, $(CLIENT_OBJ_PATH)%.o,$(CLIENT_SRC))

SERVER_SRC				=	$(shell ls $(SERVER_SRC_PATH) | grep .c$$)
SERVER_OBJ				=	$(patsubst %.c, $(SERVER_OBJ_PATH)%.o,$(SERVER_SRC))

SHARED_SRC				=	$(shell ls $(SHARED_SRC_PATH) | grep .c$$)
SHARED_OBJ				=	$(patsubst %.c, $(SHARED_OBJ_PATH)%.o,$(SHARED_SRC))

INCLUDE					=	-I./src/include

FLAGS					=	-Ofast -Wall -Wextra -Werror
CC						=	gcc
SERVER					=	serveur
CLIENT					=	client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SHARED_OBJ) $(SERVER_OBJ)
	@$(CC) $(SERVER_OBJ) $(SHARED_OBJ) $(FLAGS) $(INCLUDE) -o $(SERVER)

$(CLIENT): $(SHARED_OBJ) $(CLIENT_OBJ)
	@$(CC) $(CLIENT_OBJ) $(SHARED_OBJ) $(FLAGS) $(INCLUDE) -o $(CLIENT)

$(patsubst %, $(SERVER_OBJ_PATH)%,%.o): $(SERVER_SRC_PATH)$(notdir %.c)
	@mkdir -p $(SERVER_OBJ_PATH)
	@$(CC) -c $(FLAGS) $(INCLUDE) "$<" -o "$@"

$(patsubst %, $(CLIENT_OBJ_PATH)%,%.o): $(CLIENT_SRC_PATH)$(notdir %.c)
	@mkdir -p $(CLIENT_OBJ_PATH)
	@$(CC) -c $(FLAGS) $(INCLUDE) "$<" -o "$@"

$(patsubst %, $(SHARED_OBJ_PATH)%,%.o): $(SHARED_SRC_PATH)$(notdir %.c)
	@mkdir -p $(SHARED_OBJ_PATH)
	@$(CC) -c $(FLAGS) $(INCLUDE) "$<" -o "$@"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(OBJ_PATH)
	@rm -f $(SERVER)
	@rm -f $(CLIENT)

re: fclean all

.PHONY: clean fclean re
