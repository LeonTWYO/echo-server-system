# Use a lightweight base image
FROM debian:10-slim
# Update package lists and install necessary dependencies
RUN apt-get update \
    && apt-get install -y gcc \
    && rm -rf /var/lib/apt/lists/*
# Set the working directory inside the container
WORKDIR /source
# Copy the project files into the container
COPY . /source
RUN gcc -o ./server/server ./server/server.c
RUN gcc -o ./client/client ./client/client.c
# Expose port 8888 for the server
EXPOSE 8888
