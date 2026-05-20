# Dev Containers

**Dev containers** are a wya of doing development in which the development environment is containerized using a software like 
Docker. This allows for a consistent development environment across different machines, security, and easy setup.

## Set up

### Extension

The dev container extension is available in the Visual Studio Code marketplace. 

### Folder structure

Inside your project at the root level, create a folder called `.devcontainer`. Inside this folder, you will need to create two files: `devcontainer.json` and `Dockerfile`.

```txt
my-project/
├── .devcontainer/
│   ├── devcontainer.json
│   └── Dockerfile
├── src/
└── ...
```

### devcontainer.json

The `devcontainer.json` file is where you define the configuration for your development container. Here is an example of what it might look like:

```json
{
    "image": "mcr.microsoft.com/vscode/devcontainers/python:3.8",
    "settings": {
        "terminal.integrated.shell.linux": "/bin/bash"
    },
    "extensions": [
        "ms-python.python",
        "ms-python.vscode-pylance"
    ],
    "postCreateCommand": "pip install -r requirements.txt",
    "features": {
        "ghcr.io/devcontainers/features/docker-in-docker:1": {},
        "ghcr.io/devcontainers/features/common-utils:2": {
            "configureZhsAsDefaultShell": true
        }
    }
}
```

The key properties in this file include:

- `image`: The base Docker image to use for the development container. In this example, we are using a Python 3.8 image provided by Microsoft.
- `settings`: This allows you to specify any Visual Studio Code settings that should be applied when the container is created.
- `extensions`: A list of Visual Studio Code extensions that should be installed in the container.
- `postCreateCommand`: A command that will be run after the container is created. In this example, we are installing the dependencies listed in a `requirements.txt` file.
- `features`: A list of features that should be added to the container. Features are reusable components that can be shared across different projects.
- `forwardPorts`: A list of ports that should be forwarded from the container to the host machine. This is useful for running web applications or other services inside the container.

### Features

Features are a way to add additional functionality to your development container. They are reusable components that can be shared across different projects. 

### Dockerfile

In the case, when we are not using a base image, we need to define a `Dockerfile` that specifies how to build the development container. Here is an example of what it might look like:

```Dockerfile
FROM mcr.microsoft.com/vscode/devcontainers/python:3.8
# Install any additional dependencies here
RUN apt-get update && apt-get install -y \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*
```     

### Running

To run the container we use the command in the command palette: 

```txt
remote-containers: Reopen in Container
```