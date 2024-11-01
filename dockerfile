# Use a base Ubuntu image
FROM ubuntu:22.04

# Install necessary dependencies including zlib1g-dev
RUN apt-get update && apt-get install -y \
    make \
    cmake \
    g++ \
    libc6-dev \
    libgloox-dev \
    zlib1g-dev \
    iputils-ping \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy all project files into the container
COPY . .

# Run the install script or build process
RUN ./install.sh
# Copy the built binary to a standard location
WORKDIR /app/build

# Set the command to run your application
CMD ["./XMbot"]
