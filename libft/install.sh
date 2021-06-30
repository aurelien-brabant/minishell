#!/bin/sh

INSTALL_ARCHIVE_PATH=/usr/local/lib
INSTALL_INCLUDE_PATH=/usr/local/include/

INCLUDE_DIR=./include/libft
ARCHIVE=libft.a

make

cp -r $INCLUDE_DIR $INSTALL_INCLUDE_PATH
cp -r $ARCHIVE $INSTALL_ARCHIVE_PATH

echo "libft installation done."
