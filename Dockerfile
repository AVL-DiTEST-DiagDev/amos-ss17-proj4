FROM resin/rpi-raspbian:jessie

RUN apt-get update && apt-get install -y --no-install-recommends build-essential git
#RUN apt-get install -y --no-install-recommends can-utils
RUN apt-get install -y --no-install-recommends raspberrypi-kernel-headers
RUN git clone https://github.com/hartkopp/can-isotp.git
RUN cd can-isotp
RUN make modules_install

# Install Lua
RUN apt-get install -y --no-install-recommends install lua5.2 liblua5.2-0 liblua5.2-dev
# Install Unit-Tests
RUN apt-get install -y --no-install-recommends install libcppunit-1.* libcppunit-dev

RUN make

