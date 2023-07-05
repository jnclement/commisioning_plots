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
void Fun4All_Combiner(int nEvents = 0,
//			     const string &input_file00 = "/sphenix/lustre01/sphnxpro/commissioning/HCal/cosmics/cosmics_East-00008830-0000.prdf",
//		      const string &input_file01 = "/sphenix/lustre01/sphnxpro/commissioning/HCal/cosmics/cosmics_West-00008830-0000.prdf")
		      const string &input_file00 = "seb03.list",
		      const string &input_file01 = "seb04.list",
		      const string &input_file02 = "seb06.list",
		      const string &input_file03 = "seb07.list",
		      const string &input_file04 = "mbd.list",
		      const string &input_file05 = "zdc.list",
		      const string &input_file06 = "West.list")
{
  vector<string> infile;
  infile.push_back(input_file00);
  infile.push_back(input_file01);
  infile.push_back(input_file02);
  infile.push_back(input_file03);
  infile.push_back(input_file04);
  infile.push_back(input_file05);
  infile.push_back(input_file06);
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