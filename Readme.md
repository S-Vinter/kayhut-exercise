# Disguised Process Malware

This workspace contains an implementation of a malware which run on a different target and disguise itself to an innocent program.
The malware sends it's name (hardcoded for now, but it's really not a big deal to get the process name using some command) to a remote
server, using https (boost's library implementation) for encrypting the communication.

I tested my code on ubuntu-image docker (to be sure it's completed), and used justfile as my command runner (which is like makefile written in rust).

## For Downloading requirements (mainly docker)
```bash
    just develop-installation
```

## For building the code:

```bash
    just build-docker-builder
    just build
    just build-docker-runner
```

or:
```bash
    just build-all
```
(promise I won't judge)

## For running the processes:
On parallel (I wanted to mock different computers):

```bash
    just run-server
    just run-client
```

##
yep, I know it's a very bad practice to put your private key on a remote (probably not friendly) computer, it's just for the sake
of the exercise. In real malwares (I assume) you have better resources for using a better certification method :)

##
Async is the best
