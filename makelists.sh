#!/bin/bash

RN=20508
EMRANGE=10
HRANGE=7
MRANGE=1
ZRANGE=0
for seb in seb00 seb01 seb02 seb03 seb04 seb05 seb06
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_%s-%08d-0000.prdf' $seb $RN )"
    echo $fname > $seb".list"
    for subfile in $(seq 1 $EMRANGE)
    do
	fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_%s-%08d-%04d.prdf' $seb $RN $subfile )"
	echo $fname >> $seb".list"
    done
done

for side in West East
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/HCal/beam/beam_%s-%08d-0000.prdf' $side $RN )"
    echo $fname > $side".list"
    for subfile in $(seq 1 $HRANGE)
    do
        fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/HCal/beam/beam_%s-%08d-%04d.prdf' $side $RN $subfile )"
        echo $fname >> $side".list"
    done
done

fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/mbd/beam/beam_seb18-%08d-0000.prdf' $RN )"
echo $fname > "mbd.list"
for subfile in $(seq 1 $MRANGE)
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/mbd/beam/beam_seb18-%08d-%04d.prdf' $RN $subfile )"
    echo $fname >> "mbd.list"
done

fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/ZDC/beam/beam_seb14-%08d-0000.prdf' $RN )"
echo $fname > "zdc.list"
for subfile in $(seq 1 $ZRANGE)
do
    fname="$( printf '/sphenix/lustre01/sphnxpro/commissioning/ZDC/beam/beam_seb14-%08d-%04d.prdf' $RN $subfile )"
    echo $fname >> "zdc.list"
done
