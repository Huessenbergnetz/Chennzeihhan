#!/bin/bash

pushd translations
for LANG in de it nl_NL
do
lrelease-qt5 chennzeihhan_$LANG.ts
done
popd
