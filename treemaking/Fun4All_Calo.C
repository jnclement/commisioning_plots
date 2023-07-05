#pragma once
#if ROOT_VERSION_CODE >= ROOT_VERSION(6,00,0)
#include <fun4all/SubsysReco.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>
#include <phool/recoConsts.h>
#include <fun4all/Fun4AllNoSyncDstInputManager.h>
#include <fun4all/Fun4AllDstInputManager.h>

#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllOutputManager.h>

// #include <calotowerbuilder/CaloTowerBuilder.h>
#include <caloreco/CaloTowerBuilder.h>
#include <caloreco/CaloWaveformProcessing.h>

#include <ffamodules/FlagHandler.h>
#include <ffamodules/HeadReco.h>
#include <ffamodules/SyncReco.h>
#include <ffamodules/CDBInterface.h>

// #include <runtowerinfo/RunTowerInfo.h>
#include <caloana/CaloAna.h>
#include <fun4all/Fun4AllDstOutputManager.h>
R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libfun4allraw.so)
R__LOAD_LIBRARY(libcalo_reco.so)
R__LOAD_LIBRARY(libcaloana.so)
R__LOAD_LIBRARY(libffamodules.so)
#endif

void Fun4All_Calo()
{


 

  Fun4AllServer *se = Fun4AllServer::instance();
  int verbosity = 0;

  se->Verbosity(verbosity);
  recoConsts *rc = recoConsts::instance();

 //===============
  // conditions DB flags
  //===============

  // global tag
  rc->set_StringFlag("CDB_GLOBALTAG","MDC2");
  // // 64 bit timestamp
  rc->set_uint64Flag("TIMESTAMP",6);


Fun4AllInputManager *intrue = new Fun4AllDstInputManager("DST_TOWERS");
 intrue->AddFile("/gpfs/mnt/gpfs02/sphenix/user/trinn/produced_data/run_14232/dsts_fast/00014232-0000.root");
 ///gpfs/mnt/gpfs02/sphenix/user/trinn/produced_data/run_9451/dsts_fast/00009451-0000.root");
se->registerInputManager(intrue);


 CaloAna *ca = new CaloAna("calomodule","tim_calo_tree.root");
// ca->SetOutputFileName("tim_calo_tree.root");
  // // choose CEMC, HCALIN or HCALOUT or whatever you named your
  // // calorimeter
  se->registerSubsystem(ca);






  se->run();
  se->End();

}
