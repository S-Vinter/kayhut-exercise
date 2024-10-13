FROM ubuntu:22.04

COPY ./dev/builder.yml ./builder.yml

RUN apt-get update \
    && apt-get install pipx -y \
    && pipx install --include-deps ansible

ENV PATH=$PATH":/root/.local/bin"
RUN echo "[defaults]\n remote_tmp = /tmp" > /tmp/ansible.cfg

RUN ANSIBLE_CONFIG=/tmp/ansible.cfg ansible-playbook builder.yml
