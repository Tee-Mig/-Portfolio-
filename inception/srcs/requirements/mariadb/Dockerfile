FROM	alpine:3.18.3

RUN	apk update
RUN	apk add mariadb mariadb-client openrc

COPY	conf/my.cnf /etc/my.cnf.d/my.cnf
COPY	tools/setup_mariadb.sh .
RUN chmod +x	setup_mariadb.sh

RUN	openrc && touch /run/openrc/softlevel
RUN	etc/init.d/mariadb setup

ENTRYPOINT ["/bin/sh", "./setup_mariadb.sh"]
