FROM ubuntu:22.04

RUN mkdir ~/keys
ADD ./dev/keys/server/server.crt .
ADD ./dev/keys/server/server.key .
ADD ./dev/keys/ca/ca.crt .
