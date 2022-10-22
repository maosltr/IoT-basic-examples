FROM ubuntu:22.04

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install -y git 
RUN apt-get install -y cmake
RUN apt-get install -y gcc
RUN apt-get install -y g++

RUN mkdir -p /home/env
RUN cd /home/env \
&& git clone https://github.com/eclipse-cyclonedds/cyclonedds.git \
&& cd cyclonedds \
&& mkdir build \
&& cd build \
&& cmake .. \
&& cmake --build . \
&& cmake --build . --target install

RUN cd /home/env \
&& git clone https://github.com/eclipse-cyclonedds/cyclonedds-cxx.git \
&& cd cyclonedds-cxx \
&& mkdir build \
&& cd build \
&& cmake .. \
&& cmake --build . \
&& cmake --build . --target install
