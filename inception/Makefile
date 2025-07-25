NAME = inception
VOLUME_PATH = /home/mfaucheu/data
SRCS = srcs/docker-compose.yml

all:		$(NAME)


$(NAME):
	mkdir -p $(addsuffix /wp_data, $(VOLUME_PATH))
	mkdir -p $(addsuffix /mariadb_data, $(VOLUME_PATH))
	docker-compose -f $(SRCS) up -d --build

clean:
	docker-compose -f $(SRCS) stop

fclean:
	docker-compose -f $(SRCS) down

ffclean:
	#docker stop $$(docker ps -aq)
	docker system prune -af
	sudo rm -rf $(addsuffix /*, $(addsuffix /wp_data, $(VOLUME_PATH)))
	sudo rm -rf $(addsuffix /*, $(addsuffix /mariadb_data, $(VOLUME_PATH)))
	sudo docker rm -f $$(sudo docker ps -aq)
	sudo docker volume rm -f $$(sudo docker volume ls -q)
	sudo docker rmi -f nginx_img wp_img mariadb_img

re: fclean all

.PHONY:	all clean fclean ffclean re
