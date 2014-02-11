 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in de
do
lrelease chennzeihhan_$LANG.ts
done
