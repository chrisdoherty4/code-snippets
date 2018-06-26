#!/bin/bash

set -e

echo 'export PS1="\\u@docker:\\w$ "' > /tmp/init
echo 'export HOME="/home/build"' >> /tmp/init

ENTRYSCRIPT=""
if [ "$#" -gt 0 ]; then 
    echo "$@" > /tmp/command
    ENTRYSCRIPT="/tmp/command"
fi

# If we're not root or no USER_ID is specified then just execute the script.
if [ "$( id -u )" != "0" ] || [ -z "$USER_ID" ]; then
    exec /bin/bash --init-file /tmp/init $ENTRYSCRIPT
fi

# Default GID to UID if GROUP_ID var not specified.
if [ -z "$GROUP_ID" ]; then
    GROUP_ID="$USER_ID"
fi

groupadd -o -g $GROUP_ID build
useradd -M -N -o \
    -d /home/build \
    -g build \
    -G root,sudo \
    -u $USER_ID \
    -s /bin/bash \
    build
chown build:build /home/build

echo 'export USER="build"' >> /tmp/init

# The goal is to run the $ENTRYSCRIPT in a new process as the new build user 
# that, when exited, will exit the container.
#
# Because the process created with su -c does not get assumed by the current 
# controlling tty1 we need to pass over to a new controlling tty else we loose 
# job control (we use su to run the $ENTRYSCRIPT as new build user)
#
# To achieve this we run the `script` command thus moving us from tty1 to tty2.
#
# Adding exec infront of su ensures exiting the new tty2 bash process will also 
# exit the tty1 process.
#
# The important part of this command is `/bin/bash --init-file ...` and the 
# fact it is running as the newly created "build" user with a controlled UID/GID.
exec su -c "script -q -c '/bin/bash --init-file /tmp/init $ENTRYSCRIPT' /dev/null" build
