FROM ubuntu:22.04

RUN mkdir ~/keys
ADD ./dev/keys/client/client.crt .
ADD ./dev/keys/client/client.key .
ADD ./dev/keys/ca/ca.crt .
