#! /usr/bin/env  bash  -x

##
##  コマンド定義。
##

LN_H='ln -f '
LN_S='ln -sf '
RM_F='rm -f '

##
##  シンボリックリンクの確認
##

${RM_F}  .Config/TestConf.txt
touch    .Config/TestConf.txt
${LN_S}  .Config/TestConf.txt  .Config/TestLink
if [ -L  .Config/TestLink ] ; then
    echo  'Symbolic Link Enabled.'
else
    echo  'Cannot Create Symbolic Link. Use Hard Link...'
    LN_S=${LN_H}
fi
${RM_F}  .Config/TestConf.txt  .Config/TestLink

##
##  ツールのバージョン確認
##
##  TODO
##  もし自動判定がうまくいかないようなら、
##  直接バージョン番号を変数に代入する。
##

amver=$(automake --version | head --lines=1 | sed -e 's/.*\s\([0-9\.]\+\)/\1/')
amvermajor=$(echo  ${amver} | cut  -d '.'  -f 1)
amverminor=$(echo  ${amver} | cut  -d '.'  -f 2)
if [ ${amvermajor} -gt 1 -o ${amverminor} -ge 13 ] ; then
  amtrgver=1.13
else
  amtrgver=1.12
fi
${RM_F}  .M4/InitAutoMake.m4
${LN_H}  .M4/InitAutoMake.${amtrgver}.m4  .M4/InitAutoMake.m4

##
##  定数宣言
##

testcommondir='.TestsConfig'

##
##
##

if [ ! -d  Lib/${testcommondir}/Tests ] ; then
    mkdir  -p  Lib/${testcommondir}/Tests
fi

if [ -d  Lib/${testcommondir}/Tests ] ; then
    (cd  Lib/${testcommondir}/Tests  \
      &&  ${RM_F}  Makefile.am       \
      &&  ${LN_S}  ../../Tests/.TestsCommon/Makefile.am)
    (cd  Lib/${testcommondir}/Tests  \
      &&  ${RM_F}  CMakeLists.txt    \
      &&  ${LN_S}  ../../Tests/.TestsCommon/CMakeLists.txt)
fi

for  dir  in  Common  ; do
    if [ -d Lib/${dir}/Tests ] ; then
        (cd  Lib/${dir}/Tests          \
          &&  ${RM_F}  Makefile.am     \
          &&  ${LN_H}  ../../${testcommondir}/Tests/Makefile.am)
        (cd  Lib/${dir}/Tests          \
          &&  ${RM_F}  CMakeLists.txt  \
          &&  ${LN_H}  ../../${testcommondir}/Tests/CMakeLists.txt)
    fi
done

