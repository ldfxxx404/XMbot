# Use a base Ubuntu image
FROM ubuntu:22.04

# Install necessary dependencies including zlib1g-dev and Python 3
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

# Install Python libraries

# Set the working directory
WORKDIR /app

# Copy all project files into the container
COPY . .

RUN pip3 install -r requirements.txt

# Run the install script or build process
RUN ./install.sh

# Copy the built binary to a standard location
WORKDIR /app/build

# Set the command to run your application
CMD ["./XMbot"]
