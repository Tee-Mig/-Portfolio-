#!/bin/sh
DB_DIR=/tmp/tmp.sql

echo "CREATE DATABASE $MARIADB_NAME;" > $DB_DIR
echo "CREATE USER '$MARIADB_USER'@'%' IDENTIFIED BY '$MARIADB_PASS';" >> $DB_DIR
echo "GRANT ALL PRIVILEGES ON $MARIADB_NAME.* TO '$MARIADB_USER'@'%';" >> $DB_DIR
echo "ALTER USER 'root'@'localhost' IDENTIFIED BY '$MARIADB_ROOT';" >> $DB_DIR
echo "FLUSH PRIVILEGES;" >> $DB_DIR

rc-service mariadb start
mariadb -u root < $DB_DIR
rc-service mariadb stop
mariadbd -u root
