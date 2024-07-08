# This Dockerfile is used to build a custom image with OpenSSL 1.1.1, as the school subject is based on this version.

FROM debian:bullseye-slim@sha256:34b63f55a4b193ad03c5ddb4b3f8546c797763ed708f0df5309ecb9507d15179

RUN apt-get update && apt-get install -y \
    wget \
    build-essential \
    checkinstall \
    zlib1g-dev && \
    rm -rf /var/lib/apt/lists/*

RUN wget https://www.openssl.org/source/openssl-1.1.1.tar.gz && \
    tar -xf openssl-1.1.1.tar.gz && \
    cd openssl-1.1.1 && \
    ./config && \
    make -j 4 && make install

CMD [ "/bin/bash" ]

