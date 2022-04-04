FROM mcr.microsoft.com/vscode/devcontainers/python:0-bullseye

RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends libmagickwand-dev

RUN pip install git+https://github.com/luarocks/hererocks pre-commit \
    && hererocks -l 5.1 -r 3.8.0 /usr/local \
    && echo busted luacheck | xargs -n1 luarocks install
