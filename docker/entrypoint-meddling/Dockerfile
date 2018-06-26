FROM alpine:latest

ENV HOST_UID=1000

COPY entrypoint.sh /usr/local/bin/

WORKDIR /home/build

ENTRYPOINT ["entrypoint.sh"]
