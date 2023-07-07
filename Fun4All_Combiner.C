#include <fun4all/Fun4AllServer.h>
#include <fun4all/Fun4AllInputManager.h>
#include <fun4allraw/SinglePrdfInput.h>
#include <fun4allraw/Fun4AllPrdfInputManager.h>
#include <fun4allraw/Fun4AllPrdfInputPoolManager.h>
#include <fun4all/Fun4AllOutputManager.h>

#include <fun4allraw/Fun4AllEventOutputManager.h>

//#include <ffarawmodules/EventCombiner.h>
#include <ffarawmodules/EventNumberCheck.h>

R__LOAD_LIBRARY(libfun4all.so)
R__LOAD_LIBRARY(libfun4allraw.so)
R__LOAD_LIBRARY(libffarawmodules.so)
//9451
void Fun4All_Combiner(int nEvents = 0)
{
  infile00 = "seb00.list";
  infile01 = "seb01.list";
  infile02 = "seb02.list";
  infile03 = "seb03.list";
  infile04 = "seb04.list";
  infile05 = "seb05.list";
  infile06 = "seb06.list";
  infile07 = "West.list";
  infile08 = "East.list";
  infile09 = "mbd.list";
  infile10 = "zdc.list";
  vector<string> infile;
  infile.push_back(infile00);
  infile.push_back(infile01);
  infile.push_back(infile02);
  infile.push_back(infile03);
  infile.push_back(infile04);
  infile.push_back(infile05);
  infile.push_back(infile06);
  infile.push_back(infile07);
  infile.push_back(infile08);
  infile.push_back(infile09);
  infile.push_back(infile10);
  Fun4AllServer *se = Fun4AllServer::instance();
  //  EventCombiner *evtcomb = new EventCombiner();
  //  evtcomb->Verbosity(1);
  Fun4AllPrdfInputPoolManager *in = new Fun4AllPrdfInputPoolManager("Comb");
//  in->Verbosity(10);
  for (auto iter : infile)
  {
    in->AddPrdfInputList(iter);
  }
//  in->AddPrdfInputList("shortseb00.list");
//  in->AddPrdfInputList("shortseb01.list");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb00-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb01-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb02-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb02-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb03-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb04-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb05-00009451-0000.prdf");
  // in->AddPrdfInputFile("/sphenix/lustre01/sphnxpro/commissioning/emcal/beam/beam_seb07-00009451-0000.prdf");

  se->registerInputManager(in);

//  EventNumberCheck *evtchk = new EventNumberCheck();
//  evtchk->MyPrdfNode("PRDF");
//  se->registerSubsystem(evtchk);

  Fun4AllEventOutputManager *out = new Fun4AllEventOutputManager("EvtOut","/sphenix/user/jocl/projects/commissioning_plots/beam-%08d-%04d.prdf",20000);
//  out->DropPacket(21102);
  se->registerOutputManager(out);

  se->run(nEvents);

  se->End();
  delete se;
  gSystem->Exit(0);
}
