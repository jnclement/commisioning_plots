#!/bin/bash

source /opt/sphenix/core/bin/sphenix_setup.sh -n
source /opt/sphenix/core/bin/setup_local.sh /sphenix/user/jocl/projects/testinstall
export HOME=/sphenix/u/jocl

NLOW=$1
NLO=$(( 10*NLOW ))
NUP=$((NLO + 10))
root -b -q 'merge_root.C('$NLO','$NUP')'
