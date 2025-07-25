FROM	alpine:3.18.3

RUN	apk update
RUN	apk add php81 \
	php81-fpm \
	php81-curl \
	php81-dom \
	php81-exif \
	php81-fileinfo \
	php81-common \
	php81-intl \
	php81-mbstring \
	php81-xml \
	php81-zip \
	php81-phar \
	php81-json \
	php81-mysqli \
	php81-openssl \
	php81-cli \
	php81-gd \
	mariadb-client

WORKDIR	/var/html/wordpress

RUN	wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN	chmod +x wp-cli.phar
RUN	mv wp-cli.phar /usr/local/bin/wp

RUN	wp core download --allow-root --path=/var/html/wordpress

COPY	tools/install_wp.sh setup.sh
RUN	chmod +x setup.sh

ENTRYPOINT ["/bin/sh", "./setup.sh"]
