void testcode()
{

  TFile* infile = TFile::Open("tim_calo_tree.root");
  TTree* tree = (TTree*)infile->Get("towerntup");

  std::vector<int> *etabin = {0};
  std::vector<int> *phibin = {0};
  std::vector<float> *energy = {0};
  std::vector<int> *time = {0};



  std::vector<int> *hcalin_etabin = {0};
  std::vector<int> *hcalin_phibin = {0};
  std::vector<float> *hcalin_energy = {0};
  std::vector<int> *hcalin_time = {0};

  std::vector<int> *hcalout_etabin = {0};
  std::vector<int> *hcalout_phibin = {0};
  std::vector<float> *hcalout_energy = {0};
  std::vector<int> *hcalout_time = {0};


  std::vector<int> *zdc_index = {0};
  std::vector<int> *zdc_side = {0};
  std::vector<float> *zdc_energy = {0};

  std::vector<int> *bbc_type = {0};
  std::vector<int> *bbc_side = {0};
  std::vector<float> *bbc_energy = {0};



  tree->SetBranchAddress("etabin",&etabin);
  tree->SetBranchAddress("phibin",&phibin);
  tree->SetBranchAddress("energy",&energy);
  tree->SetBranchAddress("time",&time);

  tree->SetBranchAddress("hcalin_etabin",&hcalin_etabin);
  tree->SetBranchAddress("hcalin_phibin",&hcalin_phibin);
  tree->SetBranchAddress("hcalin_energy",&hcalin_energy);
  tree->SetBranchAddress("hcalin_time",&hcalin_time);

  tree->SetBranchAddress("hcalout_etabin",&hcalout_etabin);
  tree->SetBranchAddress("hcalout_phibin",&hcalout_phibin);
  tree->SetBranchAddress("hcalout_energy",&hcalout_energy);
  tree->SetBranchAddress("hcalout_time",&hcalout_time);

  tree->SetBranchAddress("zdc_energy",&zdc_energy);
  tree->SetBranchAddress("zdc_index",&zdc_index);
  tree->SetBranchAddress("zdc_side",&zdc_side);

  tree->SetBranchAddress("bbc_energy",&bbc_energy);
  tree->SetBranchAddress("bbc_type",&bbc_type);
  tree->SetBranchAddress("bbc_side",&bbc_side);


  TH2D* h_emczdc_corr = new TH2D("h_emczdc_corr",";emcal;zdc",100,0,1,100,0,1);
  TH2D* h_emchcal_corr = new TH2D("h_emchcal_corr","emcal;ohcal",100,0,1,100,0,1);
  TH2D* h_emcmbd_corr = new TH2D("h_emcmbd_corr","emcal;mbd",100,0,1,100,0,1);
 TH1D* h_energy = new TH1D("h_energy","",1000,0,1000000);

  int nentries = tree->GetEntries();
  for (int i = 0; i < nentries;i++)
    {
      tree->GetEntry(i);
      int n_emctowers = energy->size();
      int n_hcaltowers = hcalin_energy->size();
      int n_zdctowers = zdc_energy->size();
      int n_mbdtowers = bbc_energy->size();

      float total_cemc = 0;
      float total_hcalin = 0;
      float total_hcalout = 0;
      float total_zdc = 0;
      float total_mbd = 0;

      for (int j = 0; j < n_emctowers;j++)
      	{
      	  if (energy->at(j) > 50 && energy->at(j) < 10000 && time->at(j) >12 && time->at(j) < 18 )
      	    {
      	      total_cemc += energy->at(j);
      	    }
      	}

      for (int j = 0; j < n_hcaltowers;j++)
      	{
      	  if (hcalin_energy->at(j) > 50 && hcalin_energy->at(j) < 10000 && hcalin_time->at(j) >13 && hcalin_time->at(j)< 18 )
      	    {
      	      total_hcalin += hcalin_energy->at(j);
      	    }
      	  if (hcalout_energy->at(j) > 50 && hcalout_energy->at(j) < 10000 && hcalout_time->at(j) >13 && hcalout_time->at(j) < 18 )
      	    {
      	      total_hcalout += hcalout_energy->at(j);
      	    }
      	}

      for (int j = 0; j < n_mbdtowers;j++)
      	{
	  if (bbc_type->at(j) == 1)
	    {
	      total_mbd += bbc_energy->at(j);
	    }

	}
      total_zdc+= zdc_energy->at(6);
      total_zdc+= zdc_energy->at(14);
      h_energy->Fill(total_mbd);
      h_emchcal_corr->Fill(total_cemc/350000,total_hcalout/25000);
      h_emczdc_corr->Fill(total_cemc/350000,total_zdc/9000);
      h_emcmbd_corr->Fill(total_cemc/350000,total_mbd/140000);

    }

  TCanvas*c0 = new TCanvas("c0","",700,500);

  h_energy->Draw("COLZ");
  TCanvas*c1 = new TCanvas("c1","",700,500);

  h_emchcal_corr->Draw("COLZ");

  TCanvas*c2 = new TCanvas("C2","",700,500);
  h_emczdc_corr->Draw("COLZ");

  TCanvas*c3 = new TCanvas("C3","",700,500);
  h_emcmbd_corr->Draw("COLZ");

}
