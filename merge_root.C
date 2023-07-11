#include "TApplication.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TRandom2.h"
#include "TMath.h"
#include <utility>  // for std::pair
#include <cstdio>
#include <iostream>
#include "TGraph.h"
#include "TTree.h"
#include "TLegend.h"
#include "TLatex.h"
#include "stdlib.h"
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <TMinuit.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TString.h>
#include <TAxis.h>
#include <TLine.h>
#include <TFile.h>
#include <algorithm>
#include "TChain.h"

int merge_root(int nlow, int nup)
{
  TChain ch("towerntup");
  string filename;
  string base = "output/evt/output20508file";
  string ext = ".root";
  for(int i=nlow; i<nup; i++)
    {
      cout << "File " << i << endl;
      filename = base;
      filename += to_string(i);
      filename += ext;
      const char *alsofile = filename.c_str();
      try
	{
	  ch.Add(alsofile);
	}
      catch(...)
	{
	  continue;
	}
    }
  filename = "results/run20508_" + to_string(nlow)+ "_" + to_string(nup) + ext;
  cout << filename << endl;
  ch.Merge(filename.c_str());
  cout << "Merged." << endl;
  return 0;
}
