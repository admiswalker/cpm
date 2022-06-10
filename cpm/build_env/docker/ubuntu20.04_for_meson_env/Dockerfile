FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get install wget -y
RUN apt-get install build-essential -y
RUN apt-get install -y autogen

RUN apt install python3-pip -y
RUN pip3 install meson

RUN apt install ninja-build -y
RUN apt-get install git -y