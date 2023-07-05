NFILES=$2

for i in `seq 0 $NFILES` ; do
    mv output${1}file${i}.root output/evt/
done
root -q 'merge_root.C('$NFILES')'
