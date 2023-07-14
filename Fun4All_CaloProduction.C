#ifndef FUN4ALL_CALOPRODUCTION_C
#define FUN4ALL_CALOPRODUCTION_C

#include <caloreco/CaloTowerBuilder.h>
#include <caloreco/CaloWaveformProcessing.h>

#include <ffamodules/FlagHandler.h>
#include <ffamodules/HeadReco.h>
#include <ffamodules/SyncReco.h>
#include <ffamodules/CDBInterface.h>

#include <fun4allraw/Fun4AllPrdfInputManager.h>

#include <fun4all/Fun4AllDstOutputManager.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4all/Fun4AllServer.h>
#include <fun4all/SubsysReco.h>

#include <caloana/CaloAna.h>
#include <phool/recoConsts.h>



R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libfun4allraw.so)
R__LOAD_LIBRARY(libcalo_reco.so)
R__LOAD_LIBRARY(libffamodules.so)
R__LOAD_LIBRARY(libcaloana.so)
void Fun4All_CaloProduction(const std::string &fname = "/sphenix/lustre01/sphnxpro/commissioning/aligned/beam-00014232-0002.prdf", const int rn = 0, const int subfile = 0, int nskip = 0, int nevents = 0)
{ 
  Fun4AllServer *se = Fun4AllServer::instance();
  se->Verbosity(0);
  recoConsts *rc = recoConsts::instance();
  //===============
  // conditions DB flags
  //===============
  rc->set_StringFlag("CDB_GLOBALTAG","MDC2");
  rc->set_uint64Flag("TIMESTAMP",6);
  const string outfile = "run" + to_string(rn)+"file"+to_string(subfile)+"test.root";
  /*
  CaloTowerBuilder *ca = new CaloTowerBuilder();
  ca->set_detector_type(CaloTowerBuilder::CEMC);
  ca->set_nsamples(31);
  ca->set_processing_type(CaloWaveformProcessing::FAST);
  se->registerSubsystem(ca);

  CaloTowerBuilder *ca1 = new CaloTowerBuilder();
  ca1->set_detector_type(CaloTowerBuilder::HCALIN);
  ca1->set_nsamples(31);
  ca1->set_processing_type(CaloWaveformProcessing::FAST);
  se->registerSubsystem(ca1);
  */
  CaloTowerBuilder *ca2 = new CaloTowerBuilder();
  ca2->set_detector_type(CaloTowerBuilder::HCALOUT);
  ca2->set_nsamples(31);
  ca2->set_processing_type(CaloWaveformProcessing::FAST);
  se->registerSubsystem(ca2);
  CaloTowerBuilder *ca3 = new CaloTowerBuilder();
  ca3->set_detector_type(CaloTowerBuilder::MBD);
  ca3->set_nsamples(31);
  ca3->set_processing_type(CaloWaveformProcessing::FAST);
  se->registerSubsystem(ca3);
  /*
  CaloTowerBuilder *ca4 = new CaloTowerBuilder();
  ca4->set_detector_type(CaloTowerBuilder::ZDC);
  ca4->set_nsamples(31);
  ca4->set_processing_type(CaloWaveformProcessing::FAST);
  se->registerSubsystem(ca4);
  */
  string outname = "output" + to_string(rn) + "file" + to_string(subfile) + ".root";
  CaloAna* caloana = new CaloAna("ana",outname.c_str());
  se->registerSubsystem(caloana);
  Fun4AllInputManager *in = new Fun4AllPrdfInputManager("in");
  in->fileopen(fname);
  se->registerInputManager(in);

  Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT", outfile);
  se->registerOutputManager(out);


  se->skip(nskip);
  se->run(nevents);
  //CDBInterface::instance()->Print(); // print used DB files
  se->End();
  se->PrintTimer();
  gSystem->Exit(0);
}

#endif
