#!/bin/bash
# file name: firstcondor.sh

source /opt/sphenix/core/bin/sphenix_setup.sh -n
source /opt/sphenix/core/bin/setup_local.sh /sphenix/user/jocl/projects/testinstall
export HOME=/sphenix/u/jocl
fname="$( printf /sphenix/lustre01/sphnxpro/commissioning/aligned/beam-%08d-%04d.prdf ${1} ${2} )"
root -q "Fun4All_CaloProduction.C(\"$fname\",${1},${2})"
