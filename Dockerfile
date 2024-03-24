FROM ubuntu:22.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y g++ vim cmake git gdb

WORKDIR /workspace/latte
