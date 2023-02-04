#!/bin/sh

PROJ=~/supla
[ -e $PROJ ] || mkdir -p $PROJ
cd $PROJ
[ ! -e ./supla-espressif-esp ] && git clone https://github.com/SUPLA/supla-espressif-esp
docker run -v "$PROJ":/CProjects -it --device=/dev/ttyUSB0 devel/esp8266 /bin/bash
