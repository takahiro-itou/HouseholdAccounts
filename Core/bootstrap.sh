#! /bin/bash  -x

mkdir  -p  .Config

/usr/bin/env  bash  -x  setuplinks.sh

aclocal  -I  .Config  \
  &&  autoheader      \
  &&  automake  --add-missing  --copy  --foreign  \
  &&  autoconf

