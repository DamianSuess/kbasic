#!/bin/bash
cd kbrun
sed -i -e 's,^#define KBC,//#define KBC,g' ../kbshared/define.h
sed -i -e 's,^#define IDE,//#define IDE,g' ../kbshared/define.h
sed -i -e 's,^//#define RUN,#define RUN,g' ../kbshared/define.h
rm moc*
qmake kbrun.pro
make -j4

cd ../kbc
sed -i -e 's,^//#define KBC,#define KBC,g' ../kbshared/define.h
sed -i -e 's,^#define IDE,//#define IDE,g' ../kbshared/define.h
sed -i -e 's,^#define RUN,//#define RUN,g' ../kbshared/define.h
rm kbc
cp -a ../kbshared kbc
aclocal
automake -a
autoconf
./configure --prefix=/usr --sysconfdir=/etc CXXFLAGS="-O2 -g0 -w"
cp -f %_bindir/libtool .
make -j4

cd ../kbide
sed -i -e 's,^#define KBC,//#define KBC,g' ../kbshared/define.h
sed -i -e 's,^//#define IDE,#define IDE,g' ../kbshared/define.h
sed -i -e 's,^#define RUN,//#define RUN,g' ../kbshared/define.h
rm moc*
qmake kbide.pro
make -j4


