FROM alpine:3.18.3

RUN apk update
RUN apk add nginx openssl

RUN openssl req -x509 -newkey rsa:2048 -nodes -days 365 \
  -keyout /etc/ssl/certs/key.pem -out /etc/ssl/certs/cert.pem\
  -subj '/C=FR/ST=Paris/L=Paris/O=42/OU=mfaucheu/CN=mfaucheu.42.fr'

COPY conf/nginx.conf /etc/nginx/

EXPOSE 443

ENTRYPOINT ["nginx", "-g", "daemon off;"]
