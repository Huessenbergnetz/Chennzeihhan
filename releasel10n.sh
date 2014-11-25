 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in de it nl_NL
do
lrelease chennzeihhan_$LANG.ts
done
