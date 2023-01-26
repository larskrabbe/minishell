#!/bin/bash

# get USER, HOME and DISPLAY and then completely clear environment
U=$USER
H=$HOME
D=$DISPLAY

for i in $(env | awk -F"=" '{print $1}') ; do
unset $i ; done

# set USER, HOME and DISPLAY and set minimal path.
export USER=$U
export HOME=$H
export DISPLAY=$D

# initial path
export PATH=/usr/kerberos/bin:/bin:/usr/bin:/usr/bin/X11:/usr/local/bin