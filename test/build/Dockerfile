# clang should be used in the Makefile, no gcc!

FROM		ubuntu:bionic

RUN			apt-get update -y && apt-get upgrade -y && apt-get -y install	clang-9	\
																			make	\
																			git

RUN			ln -sf $(which clang-9) /usr/bin/clang 

WORKDIR		/build

ENTRYPOINT	[ "make" ]
