# 🐳 Docker Cheatsheet

A quick reference guide to working with Docker — images, containers, volumes, networks, and more.

---

## 📦 **Docker Basics**

Docker is a virtualization software used to simplify the deployment of applications. It achives its goal with tow main concepts
**Images** and **Contaniers**.

```bash
# Check Docker version
docker --version

# Display system-wide information
docker info

# List all Docker CLI commands
docker --help
```

---

## 🔍 **Images**

These are files which declare all the dependencies, commands port, os, etc necessary to run an application. They can be shared across machines 
which makes the system reproducible.

```bash
# List all local images
docker images

# Search for an image on Docker Hub
docker search <image_name>

# Pull an image from Docker Hub
docker pull <image_name>:<tag>      # default tag = latest

# Remove an image
docker rmi <image_id>              # force remove: docker rmi -f <image_id>
```

---

## 🏃 **Containers**

A container is an instance of a running image which works as a lightweight virtual machine. 

```bash
# Run a container
docker run <image_name>                   # run interactively
docker run -it <image_name> /bin/bash     # start with shell access
docker run -d <image_name>                # run in detached (background) mode
docker run -p 8080:80 <image_name>        # map ports (host:container)
docker run --name my_container <image>    # assign a custom name

# List containers
docker ps              # running containers
docker ps -a           # all containers (including stopped ones)

# Start/Stop/Remove containers
docker start <container_id>
docker stop <container_id>
docker rm <container_id>           # remove stopped container

# View logs of a container
docker logs <container_id>

# Execute command inside running container
docker exec -it <container_id> /bin/bash
```

---

## 🏗 **Building Docker Images**

### Example Dockerfile

```dockerfile
# Use an official base image
FROM python:3.11-slim

# Set working directory
WORKDIR /app

# Copy project files
COPY requirements.txt .

# Install dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Copy rest of the code
COPY . .

# Expose a port (optional)
EXPOSE 8000

# Command to run the application
CMD ["python", "main.py"]
```

### Build and Run

```bash
# Build an image from Dockerfile
docker build -t my_image_name .

# Run container from custom image
docker run -it --rm -p 8000:8000 my_image_name
```

---

## 📂 **Volumes (Persistent Data)**

```bash
# Create a named volume
docker volume create my_volume

# List volumes
docker volume ls

# Run container with volume mounted
docker run -v my_volume:/app/data <image_name>
docker run -v $(pwd):/app <image_name>   # mount current dir
```

---

## 🌐 **Networking**

```bash
# List networks
docker network ls

# Create a network
docker network create my_network

# Run container and attach to network
docker run --network my_network <image_name>
```

---

## 🧹 **Cleanup**

```bash
# Remove all stopped containers
docker container prune

# Remove all unused images
docker image prune

# Remove all unused volumes
docker volume prune

# Remove EVERYTHING not used
docker system prune -a
```

---

## 🛠 **Docker Compose (Optional)**

`docker-compose.yml` example:

```yaml
version: "3.9"
services:
  web:
    build: .
    ports:
      - "5000:5000"
    volumes:
      - .:/app
    environment:
      - FLASK_ENV=development
```

Run with:

```bash
docker compose up        # start services
docker compose down      # stop and remove
docker compose build     # rebuild images
```

---

## 📌 **Tips**

* Always tag your images: `docker build -t myapp:1.0 .`
* Use `.dockerignore` to speed up builds and avoid copying unnecessary files.
* Prefer multi-stage builds to keep image sizes small.
* Use `--rm` to automatically remove containers after they stop.

---

