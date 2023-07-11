#!/bin/bash
runtype="calib"
RN=21053
EMRANGE=0
HRANGE=0
MRANGE=0
ZRANGE=0
for seb in seb00 seb01 seb02 seb03 seb04 seb05 seb06 seb07
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/emcal/'$runtype'/'$runtype'_%s-%08d-0000.prdf' $seb $RN )"
    echo $fname > $seb".list"
    for subfile in $(seq 1 $EMRANGE)
    do
	fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/emcal/'$runtype'/'$runtype'_%s-%08d-%04d.prdf' $seb $RN $subfile )"
	echo $fname >> $seb".list"
    done
done

for side in West East
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/HCal/'$runtype'/'$runtype'_%s-%08d-0000.prdf' $side $RN )"
    echo $fname > $side".list"
    for subfile in $(seq 1 $HRANGE)
    do
        fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/HCal/'$runtype'/'$runtype'_%s-%08d-%04d.prdf' $side $RN $subfile )"
        echo $fname >> $side".list"
    done
done

fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/mbd/'$runtype'/'$runtype'_seb18-%08d-0000.prdf' $RN )"
echo $fname > "mbd.list"
for subfile in $(seq 1 $MRANGE)
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/mbd/'$runtype'/'$runtype'_seb18-%08d-%04d.prdf' $RN $subfile )"
    echo $fname >> "mbd.list"
done

fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/ZDC/'$runtype'/'$runtype'_seb14-%08d-0000.prdf' $RN )"
echo $fname > "zdc.list"
for subfile in $(seq 1 $ZRANGE)
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/ZDC/'$runtype'/'$runtype'_seb14-%08d-%04d.prdf' $RN $subfile )"
    echo $fname >> "zdc.list"
done
