#!/bin/bash

CMD="/bin/bash"

if [[ "x$@" != "x" ]]; then
    CMD="$CMD -c $@"
fi

if [ $( id -u ) != "0" ]; then
    exec $CMD
fi

addgroup --gid $HOST_UID build
adduser \
    --gecos "" \
    --disabled-password \
    --home /home/build \
    --no-create-home \
    --shell /bin/bash \
    --uid $HOST_UID \
    --ingroup build \
    build
chown build:build /home/build 

export PS1="\U:\w$ "
export HOME="/home/build"
export USER="build"

echo "Running command in container: $CMD"
exec sudo -u build "$CMD"
