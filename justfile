develop-installation:
    curl -fsSL https://get.docker.com -o get-docker.sh
    sudo sh ./get-docker.sh
    sudo groupadd docker && sudo usermod -aG docker $USER
    newgrp docker
    sudo chmod 666 /var/run/docker.sock

build-docker-builder:
    docker build -f dev/builder.Dockerfile . -t builder

build-docker-runner:
    docker build -f dev/runner.Dockerfile . -t runner

build:
    docker run -it --rm --volume .:/Workdir -w /Workdir --entrypoint ./build.sh builder

run-client:
    docker run --rm --volume .:/Workdir -w /Workdir --network="host" --entrypoint ./bin/Client runner

run-server:
    docker run -it --rm --volume .:/Workdir -w /Workdir --network="host" --entrypoint ./bin/Server runner
