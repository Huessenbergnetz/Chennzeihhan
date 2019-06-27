#!/bin/bash

#for LANG in de en_GB fr zh_CN
for LANG in en
do
lupdate-qt5 -locations none -no-obsolete data sailfishos -ts translations/chennzeihhan_$LANG.ts
done

