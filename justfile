develop-installation:
    curl -fsSL https://get.docker.com -o get-docker.sh
    sudo sh ./get-docker.sh
    sudo groupadd docker && sudo usermod -aG docker $USER
    newgrp docker
    sudo chmod 666 /var/run/docker.sock
    sudo apt install openssl

setup:
    mkdir -p ./dev/keys

    mkdir -p ./dev/keys/ca
    openssl genrsa -out ./dev/keys/ca/ca.key 2048
    openssl req -x509 -new -nodes -key ./dev/keys/ca/ca.key -sha256 -days 1024 -out ./dev/keys/ca/ca.crt -subj "/CN=My Test CA"
    sudo chmod +r ./dev/keys/ca/*

    mkdir -p ./dev/keys/server
    openssl genrsa -out ./dev/keys/server/server.key 2048
    openssl req -new -key ./dev/keys/server/server.key -out ./dev/keys/server/server.csr -subj "/CN=localhost"
    openssl x509 -req -in ./dev/keys/server/server.csr -CA ./dev/keys/ca/ca.crt -CAkey ./dev/keys/ca/ca.key -CAcreateserial -out ./dev/keys/server/server.crt -days 365 -sha256
    sudo chmod +r ./dev/keys/server/*

    mkdir -p ./dev/keys/client
    openssl genrsa -out ./dev/keys/client/client.key 2048
    openssl req -new -key ./dev/keys/client/client.key -out ./dev/keys/client/client.csr -subj "/CN=Client"
    openssl x509 -req -in ./dev/keys/client/client.csr -CA ./dev/keys/ca/ca.crt -CAkey ./dev/keys/ca/ca.key -CAcreateserial -out ./dev/keys/client/client.crt -days 365 -sha256
    sudo chmod +r ./dev/keys/client/*

build-docker-builder:
    docker build -f dev/builder.Dockerfile . -t builder

build-docker-runner:
    just setup
    docker build -f dev/server_runner.Dockerfile . -t server_runner
    docker build -f dev/client_runner.Dockerfile . -t client_runner

build:
    docker run -it --rm --volume .:/Workdir -w /Workdir --entrypoint ./build.sh builder

run-client:
    docker run --rm --volume ./bin:/Workdir -w /Workdir --network="host" --entrypoint ./Client client_runner

run-server:
    docker run -it --rm --volume ./bin:/Workdir -w /Workdir --network="host" --entrypoint ./Server server_runner
