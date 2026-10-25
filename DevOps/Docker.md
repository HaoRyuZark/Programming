# Docker

**Docker** is a virtualization software which uses **containers** for running applications instead
of a full **virtual machine**.

It used for all kinds of scenarios like: running applications in a sandbox, running CI/CD-pipelines,
dev-containers, etc.

---

## Containers

**Containers** are isolated processes which consist on an app and everything they need like libraries, runtimes, etc.
They share the host kernel, but they have their own file-system, network and process tree as well as resource limits.

> Containers are a series of layers of images like: alpine-linux -> postgress -> node -> our application

---

## Images & Dockerfiles

An **image** is template used to create containers. They are created from a **dockerfile** which is where we declare the properties
of the image, their runtimes, OS, etc.

> To look for images and containers go to [Docker Hub](https://hub.docker.com/)

---

## Volumes

A **volume** is a docker-managed persistence which lives outside the container.

---

## Commands

The following is a list of the most common commands used in docker.

### Set Up Docker

### General

- `docker version`
  - **Function**: Shows client and server (daemon) versions.
  - **Flags**:
    - `-f, --format <tpl>`: Go-template output.
  - **Example Usage**: `docker version` / `docker version -f '{{.Server.Version}}'`

- `docker info`
  - **Function**: Displays system-wide info: storage driver, number of containers/images, runtimes, root dir, swarm status.
  - **Example Usage**: `docker info`

- `docker [command] --help`
  - **Function**: Shows help for any command or subcommand.
  - **Example Usage**: `docker run --help` / `docker container --help`

- `docker login [flags] [server]`
  - **Function**: Authenticates to a registry. Credentials are saved in `~/.docker/config.json` (or a credential helper).
  - **Flags**:
    - `-u, --username <user>`: Username.
    - `-p, --password <pw>`: Password (insecure; shows in shell history).
    - `--password-stdin`: Read password from stdin (preferred, use in scripts/CI).
  - **Parameters**:
    - `[server]` _(optional)_: Registry host; defaults to Docker Hub.
  - **Example Usage**: `echo "$TOKEN" | docker login ghcr.io -u myuser --password-stdin`

- `docker logout [server]`
  - **Function**: Removes stored credentials for a registry.
  - **Example Usage**: `docker logout ghcr.io`

- `docker context <subcommand>`
  - **Function**: Manages saved Docker endpoints (local/remote hosts).
  - **Subcommands**:
    - `ls`: List contexts.
    - `create <name> --docker "host=ssh://user@host"`: Create a remote context.
    - `use <name>`: Switch the active context.
    - `rm <name>`: Delete a context.
  - **Example Usage**: `docker context create prod --docker "host=ssh://deploy@10.0.0.5"` then `docker --context prod ps`

- `docker events [flags]`
  - **Function**: Streams real-time daemon events (container start/die, image pull, etc.).
  - **Flags**:
    - `--filter <k=v>`: Filter (e.g. `type=container`, `event=die`).
    - `--since <time>` / `--until <time>`: Time window.
    - `-f, --format <tpl>`: Go template.
  - **Example Usage**: `docker events --filter event=die`

### Images

- `docker pull [flags] <image>[:tag|@digest]`
  - **Function**: Downloads an image from a registry.
  - **Flags**:
    - `-a, --all-tags`: Pull every tag of the repository.
    - `--platform <os/arch>`: Pull for a specific platform (e.g. `linux/arm64`).
    - `-q, --quiet`: Suppress progress output.
  - **Parameters**:
    - `<image>` _(required)_: Image name.
  - **Example Usage**: `docker pull postgres:16` / `docker pull --platform linux/amd64 nginx`

- `docker push [flags] <image>[:tag]`
  - **Function**: Uploads an image to a registry (you must be logged in and the name must include your namespace/registry).
  - **Flags**:
    - `-a, --all-tags`: Push all tags.
  - **Example Usage**: `docker push myuser/myapp:1.0`

- `docker images [flags] [repository[:tag]]` (same as `docker image ls`)
  - **Function**: Lists local images.
  - **Flags**:
    - `-a, --all`: Include intermediate/untagged layers.
    - `-q, --quiet`: Only image IDs.
    - `--digests`: Show digests.
    - `--filter <k=v>`: e.g. `dangling=true`, `reference=nginx*`, `before=<image>`.
    - `--format <tpl>`: Custom output.
  - **Example Usage**: `docker images --filter dangling=true` / `docker images --format "{{.Repository}}:{{.Tag}} {{.Size}}"`

- `docker rmi [flags] <image>...` (same as `docker image rm`)
  - **Function**: Removes one or more images.
  - **Flags**:
    - `-f, --force`: Force removal (even if used by stopped containers).
    - `--no-prune`: Don't delete untagged parent layers.
  - **Parameters**:
    - `<image>...` _(required)_: Name, ID or `name:tag`.
  - **Example Usage**: `docker rmi nginx:1.25` / `docker rmi $(docker images -q)`

- `docker tag <source> <target>`
  - **Function**: Creates an additional name (tag) for an existing image. Does not copy data.
  - **Example Usage**: `docker tag myapp:latest ghcr.io/me/myapp:1.0.0`

- `docker build [flags] <context>`
  - **Function**: Builds an image from a Dockerfile and a build context.
  - **Flags**:
    - `-t, --tag <name:tag>`: Name/tag the image (repeatable).
    - `-f, --file <path>`: Dockerfile path (default `<context>/Dockerfile`).
    - `--build-arg <KEY=VAL>`: Set an `ARG` value.
    - `--target <stage>`: Stop at a named stage of a multi-stage build.
    - `--no-cache`: Ignore the build cache.
    - `--pull`: Always try to pull newer base images.
    - `--platform <os/arch>`: Target platform.
    - `--progress <plain|auto|tty>`: Output style (`plain` shows full logs).
    - `--secret id=<id>,src=<file>`: Mount a build-time secret (not stored in layers).
    - `--ssh default`: Forward SSH agent for private git clones.
    - `--cache-from` / `--cache-to`: External cache sources/destinations.
    - `--label <k=v>`: Add metadata.
    - `--load` / `--push`: (buildx) Load result into local images / push to registry.
  - **Parameters**:
    - `<context>` _(required)_: Path, URL or `-` (stdin). Usually `.`.
  - **Example Usage**: `docker build -t myapp:1.0 .` / `docker build -f docker/Dockerfile.prod --build-arg VERSION=2 -t myapp:prod .`

- `docker buildx build [flags] <context>`
  - **Function**: BuildKit-powered build with multi-platform support.
  - **Flags**: Same as `docker build`, plus:
    - `--platform <list>`: Comma-separated platforms.
    - `--push`: Push straight to registry (needed for multi-arch manifests).
  - **Example Usage**: `docker buildx build --platform linux/amd64,linux/arm64 -t me/app:1.0 --push .`

- `docker buildx <subcommand>`
  - **Function**: Manage builders.
  - **Subcommands**: `ls` (list builders), `create --use` (create + select a builder), `inspect`, `rm`, `prune` (clear build cache).
  - **Example Usage**: `docker buildx create --name multi --use`

- `docker image inspect [flags] <image>`
  - **Function**: Shows low-level JSON metadata (layers, env, entrypoint, exposed ports, labels).
  - **Flags**:
    - `-f, --format <tpl>`: Extract fields.
  - **Example Usage**: `docker image inspect -f '{{.Config.Env}}' nginx`

- `docker history [flags] <image>`
  - **Function**: Shows the layers of an image and the instruction/size of each.
  - **Flags**:
    - `--no-trunc`: Show full commands.
    - `-H, --human=false`: Raw sizes.
  - **Example Usage**: `docker history --no-trunc myapp:1.0`

- `docker search [flags] <term>`
  - **Function**: Searches Docker Hub.
  - **Flags**:
    - `--filter is-official=true`: Only official images.
    - `--limit <n>`: Max results.
  - **Example Usage**: `docker search --filter is-official=true redis`

- `docker save [flags] <image>...`
  - **Function**: Exports one or more images (with layers and tags) to a tar archive. For moving images between machines offline.
  - **Flags**:
    - `-o, --output <file>`: Write to file instead of stdout.
  - **Example Usage**: `docker save -o myapp.tar myapp:1.0` / `docker save myapp:1.0 | gzip > myapp.tgz`

- `docker load [flags]`
  - **Function**: Loads images from a tar archive created by `docker save`.
  - **Flags**:
    - `-i, --input <file>`: Read from file instead of stdin.
  - **Example Usage**: `docker load -i myapp.tar`

- `docker export <container> -o <file>` / `docker import <file> [name:tag]`
  - **Function**: `export` dumps a **container's filesystem** as a flat tar (no layers/metadata). `import` creates an image from such a tarball.
  - **Example Usage**: `docker export web -o web-fs.tar` then `docker import web-fs.tar web-flat:1`

- `docker image prune [flags]`
  - **Function**: Removes unused images.
  - **Flags**:
    - `-a, --all`: Remove all images not used by any container (not just dangling).
    - `--filter "until=24h"`: Only older than a time.
    - `-f, --force`: No confirmation prompt.
  - **Example Usage**: `docker image prune -a --filter "until=168h"`

- `docker manifest <subcommand>` _(experimental CLI, still widely used)_
  - **Function**: Inspect/create multi-arch manifest lists.
  - **Example Usage**: `docker manifest inspect nginx:latest`

- `docker scout <subcommand>`
  - **Function**: Analyzes images for vulnerabilities and gives base-image recommendations (Docker Scout).
  - **Subcommands**: `quickview`, `cves`, `recommendations`, `compare`.
  - **Example Usage**: `docker scout cves myapp:1.0`

### Containers

- `docker pull [flags] <image>[:tag|@digest]`
  - **Function**: Downloads an image from a registry.
  - **Flags**:
    - `-a, --all-tags`: Pull every tag of the repository.
    - `--platform <os/arch>`: Pull for a specific platform (e.g. `linux/arm64`).
    - `-q, --quiet`: Suppress progress output.
  - **Parameters**:
    - `<image>` _(required)_: Image name.
  - **Example Usage**: `docker pull postgres:16` / `docker pull --platform linux/amd64 nginx`

- `docker push [flags] <image>[:tag]`
  - **Function**: Uploads an image to a registry (you must be logged in and the name must include your namespace/registry).
  - **Flags**:
    - `-a, --all-tags`: Push all tags.
  - **Example Usage**: `docker push myuser/myapp:1.0`

- `docker images [flags] [repository[:tag]]` (same as `docker image ls`)
  - **Function**: Lists local images.
  - **Flags**:
    - `-a, --all`: Include intermediate/untagged layers.
    - `-q, --quiet`: Only image IDs.
    - `--digests`: Show digests.
    - `--filter <k=v>`: e.g. `dangling=true`, `reference=nginx*`, `before=<image>`.
    - `--format <tpl>`: Custom output.
  - **Example Usage**: `docker images --filter dangling=true` / `docker images --format "{{.Repository}}:{{.Tag}} {{.Size}}"`

- `docker rmi [flags] <image>...` (same as `docker image rm`)
  - **Function**: Removes one or more images.
  - **Flags**:
    - `-f, --force`: Force removal (even if used by stopped containers).
    - `--no-prune`: Don't delete untagged parent layers.
  - **Parameters**:
    - `<image>...` _(required)_: Name, ID or `name:tag`.
  - **Example Usage**: `docker rmi nginx:1.25` / `docker rmi $(docker images -q)`

- `docker tag <source> <target>`
  - **Function**: Creates an additional name (tag) for an existing image. Does not copy data.
  - **Example Usage**: `docker tag myapp:latest ghcr.io/me/myapp:1.0.0`

- `docker build [flags] <context>`
  - **Function**: Builds an image from a Dockerfile and a build context.
  - **Flags**:
    - `-t, --tag <name:tag>`: Name/tag the image (repeatable).
    - `-f, --file <path>`: Dockerfile path (default `<context>/Dockerfile`).
    - `--build-arg <KEY=VAL>`: Set an `ARG` value.
    - `--target <stage>`: Stop at a named stage of a multi-stage build.
    - `--no-cache`: Ignore the build cache.
    - `--pull`: Always try to pull newer base images.
    - `--platform <os/arch>`: Target platform.
    - `--progress <plain|auto|tty>`: Output style (`plain` shows full logs).
    - `--secret id=<id>,src=<file>`: Mount a build-time secret (not stored in layers).
    - `--ssh default`: Forward SSH agent for private git clones.
    - `--cache-from` / `--cache-to`: External cache sources/destinations.
    - `--label <k=v>`: Add metadata.
    - `--load` / `--push`: (buildx) Load result into local images / push to registry.
  - **Parameters**:
    - `<context>` _(required)_: Path, URL or `-` (stdin). Usually `.`.
  - **Example Usage**: `docker build -t myapp:1.0 .` / `docker build -f docker/Dockerfile.prod --build-arg VERSION=2 -t myapp:prod .`

- `docker buildx build [flags] <context>`
  - **Function**: BuildKit-powered build with multi-platform support.
  - **Flags**: Same as `docker build`, plus:
    - `--platform <list>`: Comma-separated platforms.
    - `--push`: Push straight to registry (needed for multi-arch manifests).
  - **Example Usage**: `docker buildx build --platform linux/amd64,linux/arm64 -t me/app:1.0 --push .`

- `docker buildx <subcommand>`
  - **Function**: Manage builders.
  - **Subcommands**: `ls` (list builders), `create --use` (create + select a builder), `inspect`, `rm`, `prune` (clear build cache).
  - **Example Usage**: `docker buildx create --name multi --use`

- `docker image inspect [flags] <image>`
  - **Function**: Shows low-level JSON metadata (layers, env, entrypoint, exposed ports, labels).
  - **Flags**:
    - `-f, --format <tpl>`: Extract fields.
  - **Example Usage**: `docker image inspect -f '{{.Config.Env}}' nginx`

- `docker history [flags] <image>`
  - **Function**: Shows the layers of an image and the instruction/size of each.
  - **Flags**:
    - `--no-trunc`: Show full commands.
    - `-H, --human=false`: Raw sizes.
  - **Example Usage**: `docker history --no-trunc myapp:1.0`

- `docker search [flags] <term>`
  - **Function**: Searches Docker Hub.
  - **Flags**:
    - `--filter is-official=true`: Only official images.
    - `--limit <n>`: Max results.
  - **Example Usage**: `docker search --filter is-official=true redis`

- `docker save [flags] <image>...`
  - **Function**: Exports one or more images (with layers and tags) to a tar archive. For moving images between machines offline.
  - **Flags**:
    - `-o, --output <file>`: Write to file instead of stdout.
  - **Example Usage**: `docker save -o myapp.tar myapp:1.0` / `docker save myapp:1.0 | gzip > myapp.tgz`

- `docker load [flags]`
  - **Function**: Loads images from a tar archive created by `docker save`.
  - **Flags**:
    - `-i, --input <file>`: Read from file instead of stdin.
  - **Example Usage**: `docker load -i myapp.tar`

- `docker export <container> -o <file>` / `docker import <file> [name:tag]`
  - **Function**: `export` dumps a **container's filesystem** as a flat tar (no layers/metadata). `import` creates an image from such a tarball.
  - **Example Usage**: `docker export web -o web-fs.tar` then `docker import web-fs.tar web-flat:1`

- `docker image prune [flags]`
  - **Function**: Removes unused images.
  - **Flags**:
    - `-a, --all`: Remove all images not used by any container (not just dangling).
    - `--filter "until=24h"`: Only older than a time.
    - `-f, --force`: No confirmation prompt.
  - **Example Usage**: `docker image prune -a --filter "until=168h"`

- `docker manifest <subcommand>` _(experimental CLI, still widely used)_
  - **Function**: Inspect/create multi-arch manifest lists.
  - **Example Usage**: `docker manifest inspect nginx:latest`

- `docker scout <subcommand>`
  - **Function**: Analyzes images for vulnerabilities and gives base-image recommendations (Docker Scout).
  - **Subcommands**: `quickview`, `cves`, `recommendations`, `compare`.
  - **Example Usage**: `docker scout cves myapp:1.0`

- `docker run <options> <container>`
  - **Function**: Creates a new container from an image and starts it.
  - **Options**:
    - `-d`: Runs the container in the background (detached mode).
    - `-it`: Runs interactively with a terminal.
    - `--name <name>`: Assigns a container name.
    - `-p <host_port>:<container_port>`: Maps a host port to a container port.
    - `-v <host_path>:<container_path>`: Mounts a host directory or file into the container.
    - `--mount <mount_options>`: Specifies a mount explicitly.
    - `-e <key>=<value>`: Sets an environment variable.
    - `--env-file <file>`: Loads environment variables from a file.
    - `--network <network>`: Connects the container to a network.
    - `--restart <policy>`: Configures the restart policy (`no`, `always`, `unless-stopped`, `on-failure`).
    - `--rm`: Automatically removes the container when it exits.
    - `--entrypoint <command>`: Overrides the image's entrypoint.
    - `--memory <limit>`: Limits memory usage.
    - `--cpus <limit>`: Limits CPU usage.
  - **Example Usage**:
    - `docker run --name mycontainer myimage:latest`: Creates and starts a container.
    - `docker run -d --name web -p 8080:80 nginx`: Runs Nginx in the background and maps host port 8080 to container port 80.
    - `docker run -it --rm ubuntu:24.04 bash`: Starts a temporary interactive Ubuntu container.

- `docker create <options> <container>`
  - **Function**: Creates a container without starting it.
  - **Options**:
    - `--name <name>`: Assigns a name.
    - `-p <host_port>:<container_port>`: Configures port mapping.
    - `-v <host_path>:<container_path>`: Configures a volume mount.
  - **Example Usage**: `docker create --name mycontainer myimage:latest`

- `docker start <options> <container>`
  - **Function**: Starts an existing, previously created container.
  - **Options**:
    - `-a`: Attaches to the container's output.
    - `-i`: Keeps standard input open.
  - **Example Usage**: `docker start mycontainer`

- `docker restart <options> <container>`
  - **Function**: Stops and starts an existing container.
  - **Example Usage**: `docker restart mycontainer`

- `docker ps`
  - **Function**: Lists containers.
  - **Options**:
    - `-a`: Includes stopped containers.
    - `-q`: Prints only container IDs.
    - `--filter <filter>`: Filters results.
    - `--format <format>`: Customizes output.
  - **Example Usage**: `docker ps -a`

- `docker inspect <container>`
  - **Function**: Displays detailed container configuration and state.
  - **Example Usage**: `docker inspect mycontainer`

- `docker stats`
  - **Function**: Displays live CPU, memory, network, and I/O statistics.
  - **Options**:
    - `--no-stream`: Prints one snapshot instead of continuously updating.
  - **Example Usage**: `docker stats mycontainer`

- `docker port <container>`
  - **Function**: Lists the container's published port mappings.
  - **Example Usage**: `docker port mycontainer`

- `docker exec`
  - **Function**: Runs a command inside an already-running container.
  - **Options**:
    - `-it`: Opens an interactive terminal.
    - `-u <user>`: Runs the command as a specified user.
    - `-w <path>`: Sets the working directory.
    - `-e <key>=<value>`: Sets an environment variable for the executed command.
  - **Example Usage**:
    - `docker exec -it mycontainer bash`: Opens a Bash shell.
    - `docker exec -it mycontainer sh`: Opens a shell when Bash is unavailable.
    - `docker exec mycontainer ls -la /app`: Lists files inside the container.

- `docker attach <container>`
  - **Function**: Attaches your terminal to the container's main process streams.
  - **Example Usage**: `docker attach mycontainer`

- `docker cp`
  - **Function**: Copies files between the host and a container.
  - **Example Usage**:
    - `docker cp ./file.txt mycontainer:/tmp/file.txt`
    - `docker cp mycontainer:/tmp/output.txt ./output.txt`

- `docker logs <container>`
  - **Function**: Displays the container's standard output and error logs.
  - **Options**:
    - `-f`: Follows logs in real time.
    - `--tail <n>`: Displays only the last `n` lines.
    - `--since <duration>`: Shows logs since a specified time.
    - `-t`: Adds timestamps.
  - **Example Usage**: `docker logs -f --tail 100 mycontainer`

- `docker top <container>`
  - **Function**: Lists processes running inside the container.
  - **Example Usage**: `docker top mycontainer`

- `docker diff <container>`
  - **Function**: Shows filesystem changes made to the container's writable layer.
  - **Example Usage**: `docker diff mycontainer`

- `docker stop <container>`
  - **Function**: Gracefully stops a running container, then forces termination after the timeout if necessary.
  - **Options**:
    - `-t <seconds>`: Sets the timeout before forced termination.
  - **Example Usage**: `docker stop mycontainer`

- `docker kill <container>`
  - **Function**: Immediately sends a signal to terminate the container's main process.
  - **Options**:
    - `-s <signal>`: Specifies the signal to send.
  - **Example Usage**: `docker kill mycontainer`

- `docker rm <container>`
  - **Function**: Removes a stopped container.
  - **Options**:
    - `-f`: Force-removes a running container.
    - `-v`: Also removes anonymous volumes associated with the container.
  - **Example Usage**: `docker rm mycontainer`

- `docker rename <old_name> <new_name>`
  - **Function**: Renames a container.
  - **Example Usage**: `docker rename mycontainer mycontainer-old`

- `docker volume`
  - **Function**: Manages persistent storage volumes.
  - **Subcommands**:
    - `ls`: Lists volumes.
    - `create <name>`: Creates a volume.
    - `inspect <name>`: Displays volume details.
    - `rm <name>`: Removes an unused volume.
    - `prune`: Removes unused volumes.
  - **Example Usage**: `docker volume create postgres_data`

- `docker network`
  - **Function**: Manages container networks.
  - **Subcommands**:
    - `ls`: Lists networks.
    - `create <name>`: Creates a network.
    - `inspect <name>`: Displays network configuration.
    - `connect <network> <container>`: Connects a container to a network.
    - `disconnect <network> <container>`: Disconnects a container from a network.
    - `rm <network>`: Removes an unused network.
  - **Example Usage**: `docker network create app_network`

- `docker container prune`
  - **Function**: Removes all stopped containers after confirmation.
  - **Example Usage**: `docker container prune`

- `docker image prune`
  - **Function**: Removes unused images.
  - **Options**:
    - `-a`: Removes all images not referenced by any container.
  - **Example Usage**: `docker image prune -a`

- `docker system df`
  - **Function**: Shows Docker disk usage.
  - **Example Usage**: `docker system df`

- `docker system prune`
  - **Function**: Removes unused Docker resources, including stopped containers, unused networks, and dangling images.
  - **Options**:
    - `-a`: Also removes all unused images, not just dangling ones.
    - `--volumes`: Also prunes eligible unused volumes.
  - **Example Usage**: `docker system prune`

## 9. A typical workflow

If you already have an image and want to create and run a container:

```
# 1. Check available images
docker images

# 2. Create and start a container
docker run -d --name mycontainer myimage:latest

# 3. Verify it is running
docker ps

# 4. Read its logs
docker logs -f mycontainer

# 5. Open a shell inside it (if it has a shell)
docker exec -it mycontainer sh

# 6. Exit the shell, then stop the container
docker stop mycontainer

# 7. Remove the container when no longer needed
docker rm mycontainer
```

Remember: an image is a template; a container is an instance of that image. `docker run` creates and starts a new container, whereas `docker start` starts an existing one.

- `docker run`

- `docker container run <options> <image> [command]`

### Volumes

- **Storage types at a glance**
  - **Volume** (`-v myvol:/data`): Managed by Docker in `/var/lib/docker/volumes`. Portable, backup-friendly, works with volume drivers. Preferred for persistent data.
  - **Bind mount** (`-v /host/path:/data`): Direct host path. Great for dev; depends on host layout; permissions can clash.
  - **tmpfs** (`--tmpfs /tmp`): RAM only, gone on stop.
  - **Anonymous volume** (`-v /data`): Unnamed volume; easy to orphan.

- `docker volume create [flags] [name]`
  - **Function**: Creates a named volume.
  - **Flags**:
    - `-d, --driver <name>`: Volume driver (default `local`).
    - `-o, --opt <k=v>`: Driver options (e.g. NFS/CIFS settings).
    - `--label <k=v>`: Metadata.
  - **Example Usage**: `docker volume create pgdata`

- `docker volume ls [flags]`
  - **Function**: Lists volumes.
  - **Flags**: `-q`, `--filter dangling=true`, `--format <tpl>`.
  - **Example Usage**: `docker volume ls -f dangling=true`

- `docker volume inspect <volume>...`
  - **Function**: Shows volume details, including its host `Mountpoint`.
  - **Example Usage**: `docker volume inspect pgdata`

- `docker volume rm [flags] <volume>...`
  - **Function**: Deletes volumes (must not be in use). **Data is lost.**
  - **Flags**: `-f, --force`.
  - **Example Usage**: `docker volume rm pgdata`

- `docker volume prune [flags]`
  - **Function**: Removes all unused local volumes. Add `-a` to include named ones not in use.
  - **Flags**: `-a, --all`, `-f, --force`, `--filter`.
  - **Example Usage**: `docker volume prune`

- **Mount syntax comparison**
  - `-v pgdata:/var/lib/postgresql/data` (named volume)
  - `-v "$(pwd)/conf":/etc/app:ro` (bind mount, read-only)
  - `--mount type=volume,src=pgdata,dst=/var/lib/postgresql/data`
  - `--mount type=bind,src="$(pwd)",dst=/app`
  - `--mount type=tmpfs,dst=/cache,tmpfs-size=64m`
  - `-v` auto-creates missing host paths (as root-owned dirs); `--mount` errors instead, which is safer.

- **Backup a volume**: `docker run --rm -v pgdata:/data -v "$(pwd)":/backup alpine tar czf /backup/pgdata.tgz -C /data .`
- **Restore a volume**: `docker run --rm -v pgdata:/data -v "$(pwd)":/backup alpine tar xzf /backup/pgdata.tgz -C /data`
- **Share data between containers**: Mount the same volume in both, or `--volumes-from <container>`.

### Networking

We can create networks to connect containers together.

**Network drivers**

- `bridge`: Default. Private network on the host; containers talk via IPs, and via **names on user-defined bridges**.
  - `host`: Container shares the host's network stack (no port mapping needed, no isolation). Linux only (Docker Desktop has limited support).
  - `none`: No networking (only loopback).
  - `overlay`: Multi-host networking for Swarm.
  - `macvlan`: Gives containers their own MAC/IP on the physical LAN.

- `docker network create [flags] <name>`
  - **Function**: Creates a network.
  - **Flags**:
    - `-d, --driver <driver>`: Default `bridge`.
    - `--subnet <cidr>` / `--gateway <ip>` / `--ip-range <cidr>`: IP configuration.
    - `--internal`: No external access (isolated).
    - `--attachable`: Allow standalone containers to attach to an overlay network.
    - `--ipv6`: Enable IPv6.
  - **Example Usage**: `docker network create --subnet 172.30.0.0/16 appnet`

- `docker network ls [flags]`
  - **Function**: Lists networks.
  - **Flags**: `-q`, `--filter driver=bridge`, `--format <tpl>`.
  - **Example Usage**: `docker network ls`

- `docker network inspect [flags] <network>...`
  - **Function**: Shows config and connected containers with their IPs.
  - **Example Usage**: `docker network inspect appnet`

- `docker network connect [flags] <network> <container>`
  - **Function**: Attaches a running container to a network.
  - **Flags**:
    - `--alias <name>`: DNS alias.
    - `--ip <addr>`: Static IP.
  - **Example Usage**: `docker network connect --alias db appnet postgres1`

- `docker network disconnect [flags] <network> <container>`
  - **Function**: Detaches a container from a network.
  - **Flags**: `-f, --force`.
  - **Example Usage**: `docker network disconnect appnet postgres1`

- `docker network rm <network>...` / `docker network prune`
  - **Function**: Remove specific / all unused networks.
  - **Example Usage**: `docker network prune -f`

- **Port publishing patterns**
  - `-p 8080:80`: All host interfaces, port 8080 -> container 80.
  - `-p 127.0.0.1:8080:80`: Only reachable from the host itself (safer).
  - `-p 80`: Random host port to container 80 (see with `docker port`).
  - `-p 5000-5010:5000-5010`: Port range.
  - Note: Published ports can bypass host firewalls like `ufw` because Docker edits iptables directly. Bind to `127.0.0.1` for local-only services.

- **Container-to-container communication**
  - Put both on the same **user-defined** network, then use the container/service name as hostname: `postgres://db:5432`.
  - Use the **container port** (not the published host port) when talking container-to-container.
  - Reach the host from a container: `host.docker.internal` (Docker Desktop; on Linux add `--add-host=host.docker.internal:host-gateway`).

### System Maintenance & Cleanup

- `docker system df [flags]`
  - **Function**: Shows disk usage by images, containers, volumes and build cache.
  - **Flags**: `-v, --verbose`.
  - **Example Usage**: `docker system df -v`

- `docker system prune [flags]`
  - **Function**: Removes stopped containers, unused networks, dangling images and dangling build cache.
  - **Flags**:
    - `-a, --all`: Also remove all unused images.
    - `--volumes`: Also remove unused volumes (**destroys data**).
    - `--filter "until=24h"`: Only older objects.
    - `-f, --force`: Skip confirmation.
  - **Example Usage**: `docker system prune -a --volumes -f`

- `docker builder prune [flags]`
  - **Function**: Clears the build cache.
  - **Flags**: `-a, --all`, `--keep-storage <size>`, `--filter until=<time>`.
  - **Example Usage**: `docker builder prune -a`

- **One-liners**
  - Stop all running containers: `docker stop $(docker ps -q)`
  - Remove all containers: `docker rm -f $(docker ps -aq)`
  - Remove all images: `docker rmi -f $(docker images -aq)`
  - Remove dangling images only: `docker image prune`
  - Show container IPs: `docker inspect -f '{{.Name}} {{range .NetworkSettings.Networks}}{{.IPAddress}} {{end}}' $(docker ps -q)`

---

## Docker Files

A **Dockerfile** is read top to bottom. Each instruction creates a step (and usually a layer) that is cached. If a step changes,
**all following steps are re-run**, so order instructions from least-changing to most-changing.

- `FROM [--platform=<p>] <image>[:tag] [AS <name>]`
  - **Function**: Sets the base image and starts a new build stage. Must be the first instruction (only `ARG` may precede it).
  - **Notes**: `FROM scratch` = empty image. Named stages enable multi-stage builds.
  - **Example Usage**: `FROM node:22-alpine AS build`

- `RUN <command>` / `RUN ["exec", "arg"]`
  - **Function**: Executes a command at **build time** and commits the result as a layer.
  - **Forms**: _shell form_ (`RUN apt-get update`, runs via `/bin/sh -c`) and _exec form_ (`RUN ["/bin/bash", "-c", "echo hi"]`).
  - **Flags (BuildKit)**:
    - `--mount=type=cache,target=<dir>`: Persistent cache for package managers (not in final image).
    - `--mount=type=secret,id=<id>`: Use a secret without leaking it into layers.
    - `--mount=type=bind,source=<s>,target=<t>`: Temporary bind mount from the context.
    - `--network=none`: Run without network.
  - **Example Usage**: `RUN apt-get update && apt-get install -y --no-install-recommends curl && rm -rf /var/lib/apt/lists/*`
  - **Tip**: Chain commands with `&&` and clean up in the same `RUN`, otherwise the deleted files still exist in earlier layers.

- `CMD ["exec", "arg"]` / `CMD command arg` / `CMD ["arg1"]`
  - **Function**: Default command run when the container starts. **Easily overridden** by arguments to `docker run`. Only the last `CMD` counts.
  - **Forms**: exec form (preferred, no shell, receives signals directly), shell form, or as default parameters to `ENTRYPOINT`.
  - **Example Usage**: `CMD ["node", "server.js"]`

- `ENTRYPOINT ["exec", "arg"]`
  - **Function**: Defines the fixed executable of the container. Arguments from `docker run <image> args` or `CMD` are **appended** to it. Override with `--entrypoint`.
  - **Example Usage**: `ENTRYPOINT ["python", "app.py"]` + `CMD ["--port", "8000"]`
  - **CMD vs ENTRYPOINT**: Use `ENTRYPOINT` for "this container is this program", `CMD` for default arguments or a replaceable default command.

- `COPY [--chown=<u:g>] [--chmod=<mode>] [--from=<stage|image>] <src>... <dest>`
  - **Function**: Copies files from the build context (or another stage) into the image.
  - **Flags**:
    - `--from=<stage>`: Copy from an earlier stage or another image (multi-stage builds).
    - `--chown=user:group`: Set ownership.
    - `--link`: Faster, more cache-friendly copy.
  - **Example Usage**: `COPY package*.json ./` / `COPY --from=build /app/dist /usr/share/nginx/html`

- `ADD <src>... <dest>`
  - **Function**: Like `COPY`, but also extracts local tar archives and can fetch URLs. Prefer `COPY` unless you need those extras.
  - **Example Usage**: `ADD rootfs.tar.gz /`

- `WORKDIR <path>`
  - **Function**: Sets the working directory for following `RUN`, `CMD`, `ENTRYPOINT`, `COPY`, `ADD`. Creates it if missing. Prefer over `RUN cd`.
  - **Example Usage**: `WORKDIR /app`

- `ENV <key>=<value> ...`
  - **Function**: Sets environment variables available at build **and** runtime (persist in the image).
  - **Example Usage**: `ENV NODE_ENV=production PORT=3000`

- `ARG <name>[=<default>]`
  - **Function**: Defines a **build-time-only** variable, set with `--build-arg`. Not available at runtime (unless copied to `ENV`). Don't put secrets here; they're visible in `docker history`.
  - **Example Usage**: `ARG VERSION=1.0` then `docker build --build-arg VERSION=2.0 .`
  - **Scope note**: An `ARG` before `FROM` is only usable in `FROM` lines unless re-declared after.

- `EXPOSE <port>[/protocol]`
  - **Function**: **Documents** the port the app listens on. Does not publish it. You still need `-p` / `-P`.
  - **Example Usage**: `EXPOSE 8080/tcp`

- `VOLUME ["/path"]`
  - **Function**: Declares a mount point that will be backed by an (anonymous) volume if none is given at runtime. Marks data as externally persistent.
  - **Example Usage**: `VOLUME ["/var/lib/mysql"]`

- `USER <user>[:<group>]`
  - **Function**: Sets the user for following instructions and the container runtime. Run as non-root for security.
  - **Example Usage**: `RUN useradd -m app` then `USER app`

- `LABEL <key>=<value> ...`
  - **Function**: Adds metadata (OCI standard keys like `org.opencontainers.image.source`).
  - **Example Usage**: `LABEL org.opencontainers.image.source="https://github.com/me/app"`

- `HEALTHCHECK [options] CMD <command>` / `HEALTHCHECK NONE`
  - **Function**: Tells Docker how to test if the app is healthy. Status appears in `docker ps` (`healthy`/`unhealthy`).
  - **Options**: `--interval=30s`, `--timeout=3s`, `--start-period=10s`, `--retries=3`.
  - **Example Usage**: `HEALTHCHECK --interval=30s CMD curl -f http://localhost:8080/health || exit 1`

- `SHELL ["executable", "params"]`
  - **Function**: Changes the default shell used for shell-form instructions.
  - **Example Usage**: `SHELL ["/bin/bash", "-eo", "pipefail", "-c"]`

- `STOPSIGNAL <signal>`
  - **Function**: Sets the signal sent by `docker stop` (default `SIGTERM`).
  - **Example Usage**: `STOPSIGNAL SIGQUIT`

- `ONBUILD <instruction>`
  - **Function**: Registers a trigger that runs when this image is used as a base in another build. Rarely needed.

- `# syntax=docker/dockerfile:1`
  - **Function**: Parser directive on the very first line to pin the Dockerfile frontend version (enables latest BuildKit features).

- **`.dockerignore`**
  - **Function**: Lists paths excluded from the build context. Speeds up builds and prevents leaking secrets.
  - **Example**:

```
    .git
    node_modules
    *.log
    .env
    Dockerfile
    docker-compose*.yml
```

### Example: Multi-Stage Dockerfile (Node app)

```dockerfile
# ---- Build stage ----

FROM node:22-alpine AS build

# Where the application will run
WORKDIR /app

# Copying file which contains the names of the dependencies
COPY package*.json ./

# Mount cache
RUN --mount=type=cache,target=/root/.npm npm ci

COPY . .

# Build project
RUN npm run build

# ---- Runtime stage ----

# Base image
FROM node:22-alpine

# Set up enviroement vars
ENV NODE_ENV=production

WORKDIR /app

COPY --from=build /app/dist ./dist

COPY --from=build /app/package*.json ./

# Run to set up
RUN npm ci --omit=dev && npm cache clean --force

# User
USER node

# Port
EXPOSE 3000

HEALTHCHECK CMD wget -qO- http://localhost:3000/health || exit 1

# Command to run the application [command, args]
CMD ["node", "dist/server.js"]
```

### Dockerfile Best Practices

- Use small, specific base images (`-slim`, `-alpine`, distroless) and **pin versions** (`node:22.11-alpine`, or a digest).

- Copy dependency manifests first, install, **then** copy source, so the dependency layer stays cached.

- Use **multi-stage builds** to keep compilers and dev tools out of the final image.

- Combine related `RUN` steps and clean caches in the same layer.

- Run as a **non-root** user.

- Prefer **exec form** for `CMD`/`ENTRYPOINT` so signals (`SIGTERM`) reach your app.

- Never bake secrets into images (`ENV`, `ARG`, `COPY .env`). Use build secrets or runtime env/secret mounts.

- One main process per container.

- Always keep a `.dockerignore`.

---

## Docker Compose

**Compose** describes a multi-container app in a `compose.yaml` file (also accepted: `compose.yml`, `docker-compose.yml`).
One command creates the network, volumes and all containers.

**Example**:

```yaml
version" "5.1
services:
  migux_server:
    build:
    ports:
      - "3000:3000"
    links:
      - migux_s
  migux_frontend:
     image: angular
     ports:
      - "4000:5000"
     environment:
      - USER_VERG='aman'
```

### Core Concepts

- **Project**: A named group of resources. The name defaults to the directory name; override with `-p` or the top-level `name:` key.

- **Service**: A definition of a container (image/build + config). A service can have several replicas/containers.

- **Default network**: Compose creates `<project>_default`; services reach each other by **service name**.

- **Resource naming**: Created objects are prefixed with the project name (e.g. `myapp-web-1`, `myapp_pgdata`).

- **Declarative**: Re-running `up` only recreates services whose config changed.

### Compose CLI Commands

- `docker compose up [flags] [service...]`
  - **Function**: Builds (if needed), creates, starts and attaches to services.
  - **Flags**:
    - `-d, --detach`: Run in the background.
    - `--build`: Rebuild images before starting.
    - `--no-build`: Don't build, use existing images.
    - `--force-recreate`: Recreate containers even if config is unchanged.
    - `--no-recreate`: Keep existing containers.
    - `--remove-orphans`: Remove containers for services no longer in the file.
    - `--scale <svc>=<n>`: Run n instances of a service.
    - `--wait`: Wait until services are running/healthy (use with `-d`).
    - `--pull <always|missing|never>`: Image pull policy.
    - `--abort-on-container-exit`: Stop everything when one container stops.
    - `--exit-code-from <svc>`: Return that service's exit code (CI).
    - `-V, --renew-anon-volumes`: Recreate anonymous volumes.
    - `--watch`: Watch files and sync/rebuild (see `develop.watch`).
  - **Parameters**:
    - `[service...]` _(optional)_: Only start these services (and their dependencies).
  - **Example Usage**: `docker compose up -d --build` / `docker compose up -d --scale worker=3`

- `docker compose down [flags]`
  - **Function**: Stops and removes containers and networks of the project.
  - **Flags**:
    - `-v, --volumes`: Also remove named volumes (**deletes data**).
    - `--rmi <all|local>`: Also remove images.
    - `--remove-orphans`: Remove orphan containers.
    - `-t, --timeout <sec>`: Shutdown timeout.
  - **Example Usage**: `docker compose down` / `docker compose down -v --rmi local`

- `docker compose ps [flags] [service...]`
  - **Function**: Lists the project's containers.
  - **Flags**: `-a, --all`, `-q`, `--services`, `--status <status>`, `--format <fmt>`.
  - **Example Usage**: `docker compose ps -a`

- `docker compose logs [flags] [service...]`
  - **Function**: Shows aggregated logs.
  - **Flags**: `-f, --follow`, `--tail <n>`, `-t, --timestamps`, `--since <t>`, `--no-log-prefix`.
  - **Example Usage**: `docker compose logs -f --tail 50 web`

- `docker compose exec [flags] <service> <command>`
  - **Function**: Runs a command in a **running** service container (TTY allocated by default).
  - **Flags**: `-d`, `-e <K=V>`, `-u <user>`, `-w <dir>`, `-T` (disable TTY, for scripts), `--index <n>` (which replica).
  - **Example Usage**: `docker compose exec db psql -U postgres`

- `docker compose run [flags] <service> [command]`
  - **Function**: Starts a **new one-off** container for a service (e.g. migrations, tests). Doesn't publish ports unless `--service-ports`.
  - **Flags**: `--rm` (remove afterward), `-e`, `-v`, `-p`, `--no-deps` (skip dependencies), `--entrypoint`, `-u`, `-T`, `--service-ports`, `-d`.
  - **Example Usage**: `docker compose run --rm web npm test`

- `docker compose build [flags] [service...]`
  - **Function**: Builds or rebuilds images for services with a `build:` section.
  - **Flags**: `--no-cache`, `--pull`, `--build-arg <K=V>`, `--push`, `-q`, `--parallel` (default).
  - **Example Usage**: `docker compose build --no-cache api`

- `docker compose pull [service...]` / `docker compose push [service...]`
  - **Function**: Pull or push service images.
  - **Flags (pull)**: `--ignore-pull-failures`, `--include-deps`, `-q`.
  - **Example Usage**: `docker compose pull` / `docker compose push api`

- `docker compose start|stop|restart [service...]`
  - **Function**: Starts / stops / restarts **existing** containers without recreating them.
  - **Flags**: `-t, --timeout <sec>` (stop/restart).
  - **Example Usage**: `docker compose restart web`

- `docker compose pause|unpause [service...]`
  - **Function**: Freezes/resumes services.

- `docker compose kill [flags] [service...]`
  - **Function**: Force-stops containers.
  - **Flags**: `-s, --signal <sig>`.

- `docker compose rm [flags] [service...]`
  - **Function**: Removes stopped service containers.
  - **Flags**: `-f` (no prompt), `-s` (stop first), `-v` (remove anonymous volumes).
  - **Example Usage**: `docker compose rm -sf web`

- `docker compose config [flags]`
  - **Function**: Validates and prints the **fully resolved** config (after merging files and interpolating variables). Great for debugging.
  - **Flags**: `-q` (validate only), `--services`, `--volumes`, `--profiles`, `--format json`, `--no-interpolate`.
  - **Example Usage**: `docker compose config` / `docker compose -f compose.yaml -f compose.prod.yaml config`

- `docker compose top [service...]`
  - **Function**: Shows running processes of services.

- `docker compose images [service...]`
  - **Function**: Lists images used by created containers.

- `docker compose port <service> <private-port>`
  - **Function**: Shows the public port bound to a service port.
  - **Example Usage**: `docker compose port web 80`

- `docker compose cp <src> <dest>`
  - **Function**: Copies files between a service container and the host (`service:/path`).
  - **Example Usage**: `docker compose cp web:/app/log.txt ./log.txt`

- `docker compose ls [flags]`
  - **Function**: Lists Compose projects running on the host.
  - **Flags**: `-a, --all` (include stopped).
  - **Example Usage**: `docker compose ls`

- `docker compose events` / `docker compose watch` / `docker compose wait` / `docker compose stats`
  - **Function**: Stream container events / watch files and sync or rebuild (`develop.watch`) / block until services stop / live resource usage.
  - **Example Usage**: `docker compose watch`

- **Global flags** (go **before** the subcommand)
  - `-f, --file <path>`: Use a specific compose file (repeatable; later files override earlier).
  - `-p, --project-name <name>`: Set project name.
  - `--env-file <path>`: Env file for interpolation (default `.env`).
  - `--profile <name>`: Enable a profile.
  - `--project-directory <dir>`: Base dir for relative paths.
  - `--parallel <n>`: Limit concurrent operations.
  - **Example Usage**: `docker compose -f compose.yaml -f compose.prod.yaml -p shop --profile debug up -d`

### Compose File Syntax

#### Top-level keys

- `name:` Project name (optional).
- `services:` The containers to run. **Required.**
- `volumes:` Named volumes definitions.
- `networks:` Network definitions.
- `configs:` / `secrets:` Config files and secrets definitions.
- `include:` Pull in other compose files.
- (The old `version:` key is obsolete and ignored; omit it.)

#### Service keys

- `image: <name[:tag]>`
  - **Function**: Image to run/pull. Combined with `build`, it names the built image.
  - **Example**: `image: postgres:16`

- `build:`
  - **Function**: Build the image from a Dockerfile instead of pulling.
  - **Short form**: `build: ./api`
  - **Long form keys**:
    - `context:` Path/URL of the build context.
    - `dockerfile:` Dockerfile path relative to context.
    - `args:` Build arguments (map or list).
    - `target:` Stage of a multi-stage build.
    - `cache_from:` / `cache_to:` External caches.
    - `platforms:` Build for multiple platforms.
    - `secrets:` Build secrets.
    - `ssh:` SSH agent forwarding.

- **Example**:

```yaml
build:
  context: ./api
  dockerfile: Dockerfile.dev
  args:
    NODE_VERSION: "22"
  target: dev
```

- `container_name: <name>`
  - **Function**: Fixed container name. Prevents scaling; usually best avoided.

- `command: <string|list>`
  - **Function**: Overrides the image's `CMD`.
  - **Example**: `command: ["npm", "run", "dev"]`

- `entrypoint: <string|list>`
  - **Function**: Overrides the image's `ENTRYPOINT`.

- `ports:`
  - **Function**: Publish ports (`HOST:CONTAINER`). **Quote** them so YAML doesn't misread `22:22` as base-60.
  - **Example**:

```yaml
ports:
  - "8080:80"
  - "127.0.0.1:5432:5432"
  - "5353:53/udp"
```

- `expose:`
  - **Function**: Make a port reachable by other services on the network only (not the host).
  - **Example**: `expose: ["3000"]`

- `environment:`
  - **Function**: Set env vars (map or list). Values without `=`/value pass through from the shell.
  - **Example**:

```yaml
environment:
  POSTGRES_USER: app
  POSTGRES_PASSWORD: ${DB_PASSWORD}
  DEBUG:
```

- `env_file:`
  - **Function**: Load env vars from files (later ones override earlier).
  - **Example**: `env_file: [.env, .env.local]`

- `volumes:`
  - **Function**: Mount named volumes, bind mounts or tmpfs.
  - **Short syntax**: `<source>:<target>[:ro]`
  - **Long syntax keys**: `type` (`volume|bind|tmpfs`), `source`, `target`, `read_only`, `bind.create_host_path`, `volume.nocopy`, `tmpfs.size`.
  - **Example**:

```yaml
volumes:
  - pgdata:/var/lib/postgresql/data
  - ./src:/app/src
  - ./nginx.conf:/etc/nginx/nginx.conf:ro
  - type: tmpfs
    target: /cache
```

- `networks:`
  - **Function**: Attach the service to networks, optionally with aliases or static IPs.
  - **Example**:

```yaml
networks:
  backend:
    aliases: [database]
```

- `depends_on:`
  - **Function**: Controls start order and readiness.
  - **Short form**: list of services (start order only).
  - **Long form conditions**: `service_started` (default), `service_healthy` (waits for healthcheck), `service_completed_successfully` (one-shot job finished). Also `restart: true` and `required: false`.
  - **Example**:

```yaml
depends_on:
  db:
    condition: service_healthy
  migrate:
    condition: service_completed_successfully
```

- `healthcheck:`
  - **Function**: Defines how to test a container's health.
  - **Keys**: `test`, `interval`, `timeout`, `retries`, `start_period`, `start_interval`, `disable`.
  - **Example**:

```yaml
healthcheck:
  test: ["CMD-SHELL", "pg_isready -U postgres"]
  interval: 10s
  timeout: 5s
  retries: 5
```

- `restart: <policy>`
  - **Function**: `no` | `always` | `on-failure[:n]` | `unless-stopped`.
  - **Example**: `restart: unless-stopped`

- `profiles: [<name>...]`
  - **Function**: Service only starts when its profile is enabled (`--profile debug` or `COMPOSE_PROFILES=debug`). Services without profiles always start.
  - **Example**: `profiles: ["debug"]`

- `deploy:`
  - **Function**: Resource limits/reservations and replicas (honored by Compose for `resources` and `replicas`).
  - **Example**:

```yaml
deploy:
  replicas: 2
  resources:
    limits:
      cpus: "0.50"
      memory: 512M
```

- `user:` / `working_dir:` / `hostname:` / `init:` / `read_only:` / `tty:` / `stdin_open:`
  - **Function**: Equivalent to the matching `docker run` flags (`-u`, `-w`, `--hostname`, `--init`, `--read-only`, `-t`, `-i`).

- `cap_add:` / `cap_drop:` / `security_opt:` / `privileged:` / `devices:` / `sysctls:` / `ulimits:`
  - **Function**: Low-level security/system tuning, same meaning as in `docker run`.

- `extra_hosts:`
  - **Function**: Add `/etc/hosts` entries.
  - **Example**: `extra_hosts: ["host.docker.internal:host-gateway"]`

- `dns:` / `dns_search:` / `network_mode:` / `labels:` / `logging:` / `stop_grace_period:` / `stop_signal:`
  - **Function**: DNS settings, network mode (`host`, `service:<name>`), metadata, log driver/options, shutdown timing.
  - **Example**:

```yaml
logging:
  driver: json-file
  options:
    max-size: "10m"
    max-file: "3"
```

- `secrets:` / `configs:` (service level)
  - **Function**: Grant the service access to a top-level secret/config, mounted as a file under `/run/secrets/<name>` (secrets) or a chosen path (configs).
  - **Example**:

```yaml
services:
  app:
    secrets: [db_password]
secrets:
  db_password:
    file: ./secrets/db_password.txt
```

- `extends:`
  - **Function**: Reuse a service definition from another file/service.
  - **Example**:

```yaml
extends:
  file: common.yaml
  service: base-app
```

- `develop: watch:`
  - **Function**: Rules for `docker compose watch` / `up --watch`: `action: sync` (copy files in), `rebuild` (rebuild image), `sync+restart`.
  - **Example**:

```yaml
develop:
  watch:
    - action: sync
      path: ./src
      target: /app/src
    - action: rebuild
      path: package.json
```

#### Top-level `volumes:`

- **Function**: Declare named volumes (can set driver, options, `external: true` to use a pre-existing one).
- **Example**:

```yaml
volumes:
  pgdata:
  shared:
    external: true
  nfsdata:
    driver: local
    driver_opts:
      type: nfs
      o: addr=10.0.0.2,rw
      device: ":/exports/data"
```

#### Top-level `networks:`

- **Function**: Declare custom networks (driver, `internal`, `ipam`, `external`).
- **Example**:

```yaml
networks:
  frontend:
  backend:
    internal: true
```

#### Variable interpolation

- `${VAR}`: Value of `VAR` (empty if unset).

- `${VAR:-default}`: Default if unset **or empty**. `${VAR-default}`: default if unset only.

- `${VAR:?error msg}`: Fail with error if unset or empty.

- `${VAR:+alt}`: Use `alt` only if `VAR` is set.

- `$$`: Literal `$`.

- Values come from: shell environment > `--env-file` / project `.env` file. A `.env` file in the project directory is read automatically for interpolation (this is separate from `env_file:`, which injects variables into containers).

#### YAML helpers

- **Anchors & merge keys** to avoid repetition, plus `x-` extension fields:

```yaml
x-common: &common
  restart: unless-stopped
  logging:
    driver: json-file

services:
  web:
    <<: *common
    image: nginx
  api:
    <<: *common
    image: myapi
```

#### Multiple files / overrides

- `compose.yaml` + `compose.override.yaml` are merged **automatically** by `docker compose up`. Convention: base file = production-ish defaults, override = dev tweaks (bind mounts, debug ports).

- Explicit: `docker compose -f compose.yaml -f compose.prod.yaml up -d` (later files win; maps are merged, lists like `ports` are appended).

- `include:` embeds other Compose files as sub-projects:

```yaml
include:
  - ./monitoring/compose.yaml
```

### Full Example: Web + API + DB + Cache

```yaml
name: shop

services:
  web:
    image: nginx:1.27-alpine
    ports:
      - "80:80"
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf:ro
    depends_on:
      api:
        condition: service_healthy
    networks: [frontend]
    restart: unless-stopped

  api:
    build:
      context: ./api
      target: runtime
    environment:
      DATABASE_URL: postgres://app:${DB_PASSWORD}@db:5432/shop
      REDIS_URL: redis://cache:6379
    depends_on:
      db:
        condition: service_healthy
      cache:
        condition: service_started
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:3000/health"]
      interval: 15s
      retries: 3
    networks: [frontend, backend]
    restart: unless-stopped

  db:
    image: postgres:16
    environment:
      POSTGRES_USER: app
      POSTGRES_PASSWORD: ${DB_PASSWORD:?DB_PASSWORD is required}
      POSTGRES_DB: shop
    volumes:
      - pgdata:/var/lib/postgresql/data
    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U app -d shop"]
      interval: 10s
      timeout: 5s
      retries: 5
    networks: [backend]

  cache:
    image: redis:7-alpine
    networks: [backend]

  adminer:
    image: adminer
    profiles: ["debug"]
    ports:
      - "127.0.0.1:8081:8080"
    networks: [backend]

volumes:
  pgdata:

networks:
  frontend:
  backend:
    internal: true
```

Run it: `echo "DB_PASSWORD=s3cret" > .env && docker compose up -d --build`

---

## Troubleshooting Quick Reference

- **Container exits immediately**
  - Cause: Main process finished or crashed. Check `docker logs <c>` and `docker inspect -f '{{.State.ExitCode}}' <c>`. A container needs a long-running foreground process (don't daemonize inside it).

- **`port is already allocated`**
  - Cause: Host port in use. Find with `ss -ltnp | grep :8080` (Linux) or change the left side of `-p`.

- **`permission denied` on `/var/run/docker.sock` (Linux)**
  - Fix: `sudo usermod -aG docker $USER` then log out/in. (Group membership is root-equivalent.)

- **Can't reach a service from another container**
  - Check both are on the same **user-defined** network, use the service/container name, and the **container** port (not the published one). Ensure the app binds to `0.0.0.0`, not `127.0.0.1`.

- **Can't reach container from host**
  - Check `docker port <c>`, that you published the port, and the app listens on `0.0.0.0`.

- **Changes to code not showing up**
  - Rebuild: `docker compose up -d --build`, or use bind mounts / `develop.watch`. For stubborn caching use `--no-cache`.

- **Bind-mounted files have wrong owner (Linux)**
  - Run with `--user $(id -u):$(id -g)` or fix ownership with `chown`.

- **Exit code 137**
  - Killed, often out-of-memory. Check `docker inspect -f '{{.State.OOMKilled}}' <c>`; raise `--memory` or fix leaks.

- **Disk full**
  - `docker system df`, then prune (Workflow 10). Also check large container logs: set `max-size`/`max-file` on the `json-file` log driver.

- **`no matching manifest for linux/arm64`** (Apple Silicon)
  - Image lacks an arm64 build. Use `--platform linux/amd64` (runs under emulation, slower) or find an arm64-compatible image.

- **Compose `depends_on` but app still fails at start**
  - `depends_on` only waits for container _start_ by default. Add a `healthcheck` and `condition: service_healthy`, or have the app retry connections.

- **Env var not applied in Compose**
  - Use `docker compose config` to see the final resolved file. Remember: `.env` = interpolation for the compose file; `env_file:` / `environment:` = injection into the container.

---

## How to Containerize An Application? 


1. Identify the dependencies of your application like node, packages, etc. 

2. Write the docker file(s)

**Example**:

```dockerfile
FROM node 

WORKDIR /app

COPY ["package*.json", "./"]

RUN npm install 

COPY . . 

ENV PORT=8000

EXPOSE 8080 

CMD ["npm", "start"]
```

> And more if needed 

3. Build the docker image(s) `docker build -t migu/demoapp:1.0 .`

4. If we want to use multiple then we would use compose to connect the different containers together.

