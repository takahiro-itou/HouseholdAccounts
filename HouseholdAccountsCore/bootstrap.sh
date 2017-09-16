#! /bin/bash  -x

mkdir  -p  .Config

/usr/bin/env  bash  -x  setuplinks.sh

aclocal  -I  .Config  \
  &&  automake  --add-missing  --copy  --foreign  \
  &&  autoconf

