FROM rust:slim-bullseye AS stylua-builder
RUN cargo install --root=/opt/stylua --version=0.12.4 stylua

FROM mcr.microsoft.com/vscode/devcontainers/python:0-bullseye AS devcontainer
RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
        clang fonts-freefont-ttf libmagickwand-dev ruby \
    && pip install git+https://github.com/luarocks/hererocks pre-commit \
    && hererocks -l 5.1 -r 3.8.0 /usr/local \
    && echo busted luacheck penlight | xargs -n1 luarocks install \
    && luarocks install lpeg 1.0.2
COPY --from=stylua-builder /opt/stylua /usr/local
