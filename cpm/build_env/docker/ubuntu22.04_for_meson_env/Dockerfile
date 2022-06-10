FROM ubuntu:22.04

RUN apt-get update -y
RUN apt-get install wget -y
RUN apt-get install build-essential -y
RUN apt-get install -y autogen

RUN apt install python3-pip -y
RUN pip3 install meson

RUN apt install ninja-build -y
RUN apt-get install git -y