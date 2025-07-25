#!/bin/bash
sed -i "s/listen = 127.0.0.1:9000/listen = 9000/g" /etc/php81/php-fpm.d/www.conf

while ! wp config create --allow-root --dbname=${MARIADB_NAME} --dbuser=${MARIADB_USER} --dbpass=${MARIADB_PASS} --dbhost=${MARIADB_NAME} --url=${WP_URL} --force
do
  sleep 1
  echo "waiting for creation.."
done

while ! wp core install --allow-root  --title=${WP_TITLE} --url=${WP_URL} --admin_user=${WP_ADMIN_NAME} --admin_password=${WP_ADMIN_PASS} --admin_email=${WP_ADMIN_EMAIL}
do
  sleep 1
  echo "waiting for config.."
done

wp user create ${WP_USER_NAME} ${WP_USER_EMAIL} --allow-root --user_pass=${WP_USER_PASS}

php-fpm81 -F
