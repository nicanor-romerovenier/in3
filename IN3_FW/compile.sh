#!/bin/sh

if [ -z "$1" ]; then
    BUILD_DIR=$PWD/build
else
    BUILD_DIR=$1
fi

echo "Building in $BUILD_DIR"

if [ -z "${ARDUINO_INSTALL_DIR}" ]; then
  echo "ARDUINO_INSTALL_DIR is undefined. Example: $ export ARDUINO_INSTALL_DIR=/home/user/software/arduino-1.8.7"
  exit 1
else
  echo "ARDUINO_INSTALL_DIR=${ARDUINO_INSTALL_DIR}"
fi

if [ -z "${ARDUINO_PACKAGES_DIR}" ]; then
  echo "ARDUINO_PACKAGES_DIR is undefined. Example: $ export ARDUINO_PACKAGES_DIR=/home/user/.arduino15/packages"
  exit 1
else
  echo "ARDUINO_PACKAGES_DIR=${ARDUINO_PACKAGES_DIR}"
fi

if [ -z "${ARDUINO_SKETCH_DIR}" ]; then
  echo "ARDUINO_SKETCH_DIR is undefined. Example: $ export ARDUINO_SKETCH_DIR=/home/user/Arduino/"
  exit 1
else
  echo "ARDUINO_SKETCH_DIR=${ARDUINO_SKETCH_DIR}"
fi

if [ ! -d "build" ]; then
  mkdir build
fi

$ARDUINO_INSTALL_DIR/arduino-builder -compile -logger=machine -hardware $ARDUINO_INSTALL_DIR/hardware -hardware $ARDUINO_PACKAGES_DIR -hardware $ARDUINO_SKETCH_DIR/hardware -tools $ARDUINO_INSTALL_DIR/tools-builder -tools $ARDUINO_INSTALL_DIR/hardware/tools/avr -tools $ARDUINO_PACKAGES_DIR -built-in-libraries $ARDUINO_INSTALL_DIR/libraries -libraries $ARDUINO_SKETCH_DIR/libraries -fqbn=STM32:STM32F1:mapleMini:bootloader_version=original,cpu_speed=speed_72mhz,opt=osstd -vid-pid=0X1EAF_0X0004 -ide-version=10807 -build-path $BUILD_DIR -warnings=none -build-cache $BUILD_DIR -prefs=build.warn_data_percentage=75 -verbose IN3_FW.cpp
