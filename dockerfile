FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    make \
    cmake \
    g++ \
    libc6-dev \
    libgloox-dev \
    zlib1g-dev \
    iputils-ping \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app

COPY . .

RUN pip3 install -r requirements.txt

RUN ./install

WORKDIR /app/build

CMD ["./XMbot"]
