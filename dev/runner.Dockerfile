FROM ubuntu:22.04

RUN apt-get update && apt install openssl

RUN mkdir -p ~/keys
COPY ./dev/openssl.conf ./openssl.conf

RUN openssl genrsa -out ~/keys/crt.key 2048 \
    && openssl req -new -key ~/keys/crt.key -out ~/keys/crt.csr -config ./openssl.conf \
    && openssl x509 -req -days 365 -in ~/keys/crt.csr -signkey ~/keys/crt.key -out ~/keys/crt.crt