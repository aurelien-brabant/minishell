# Debian is used because we need standard glibc support
FROM debian:buster 
 
RUN apt -y update 		\
	&& apt -y upgrade	\
	&& apt -y install	\
	wget				\
	bzip2				\
	make				\
	clang				\
	libbsd-dev			\
	locales

# Locale configuration for UTF-8 tests

RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && locale-gen
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8    

# Download criterion binaries

WORKDIR /tmp

RUN wget https://github.com/Snaipe/Criterion/releases/download/v2.3.3/criterion-v2.3.3-linux-x86_64.tar.bz2

RUN tar -xvf criterion*tar.bz2	\
	&& rm -rf criterion*tar.bz2

RUN cd criterion*								\
	&& cp -r include/* /usr/include/criterion	\
	&& cp -r lib/* /usr/lib

# the libft repository should be mounted at runtime at /libft

WORKDIR /libft

CMD [ "make", "test" ]
