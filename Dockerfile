FROM debian:latest

RUN apt update && apt install -y \
      curl \
      vim \
      gcc-mipsel-linux-gnu \
      openssh-server \
      qemu-user-static \
      gdb-multiarch
# Qemu statics are installed at /usr/bin/qemu-mipsel-static

# Compiling AFL++
RUN apt install -y git make build-essential clang ninja-build pkg-config libglib2.0-dev libpixman-1-dev
RUN git clone https://github.com/AFLplusplus/AFLplusplus /AFLplusplus
WORKDIR /AFLplusplus
RUN make all
WORKDIR /AFLplusplus/qemu_mode
RUN CPU_TARGET=mipsel ./build_qemu_support.sh

RUN echo "#!/bin/bash\n\nsleep infinity" >> /entry.sh
RUN chmod +x /entry.sh

WORKDIR /share
ENTRYPOINT [ "/entry.sh" ]

# docker build -t fuzz .
# docker run -d --rm -v $PWD/:/share --name fuzz fuzz