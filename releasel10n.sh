 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in de nl_NL
do
lrelease chennzeihhan_$LANG.ts
done
