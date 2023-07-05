#include "CaloAna.h"

// G4Hits includes
#include <g4main/PHG4Hit.h>
#include <g4main/PHG4HitContainer.h>

// G4Cells includes
#include <g4detectors/PHG4Cell.h>
#include <g4detectors/PHG4CellContainer.h>

// Tower includes
#include <calobase/RawTower.h>
#include <calobase/RawTowerContainer.h>
#include <calobase/RawTowerGeom.h>
#include <calobase/RawTowerGeomContainer.h>
#include <calobase/TowerInfoContainerv1.h>
#include <calobase/TowerInfov1.h>
#include <calobase/TowerInfoDefs.h>

// Cluster includes
#include <calobase/RawCluster.h>
#include <calobase/RawClusterContainer.h>

#include <fun4all/Fun4AllHistoManager.h>
#include <fun4all/Fun4AllReturnCodes.h>

#include <phool/getClass.h>

#include <TFile.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TH2.h>

#include <Event/Event.h>
#include <Event/packet.h>
#include <cassert>
#include <sstream>
#include <string>

using namespace std;

CaloAna::CaloAna(const std::string& name, const std::string& filename)
  : SubsysReco(name)
  , detector("HCALIN")
  , outfilename(filename)
{
}

CaloAna::~CaloAna()
{
  delete hm;
  delete g4hitntuple;
  delete g4cellntuple;
  delete towerntuple;
  delete clusterntuple;
}

int CaloAna::Init(PHCompositeNode*)
{
  hm = new Fun4AllHistoManager(Name());
  // create and register your histos (all types) here
  // TH1 *h1 = new TH1F("h1",....)
  // hm->registerHisto(h1);
  outfile = new TFile(outfilename.c_str(), "RECREATE");

  towerntuple = new TTree("towerntup", "Towers");
  towerntuple->Branch("energy",&m_energy);
  towerntuple->Branch("etabin",&m_etabin);
  towerntuple->Branch("phibin",&m_phibin);
  towerntuple->Branch("time",&m_time);


  towerntuple->Branch("hcalin_energy",&m_hcalin_energy);
  towerntuple->Branch("hcalin_etabin",&m_hcalin_etabin);
  towerntuple->Branch("hcalin_phibin",&m_hcalin_phibin);
  towerntuple->Branch("hcalin_time",&m_time);

  towerntuple->Branch("hcalout_energy",&m_hcalout_energy);
  towerntuple->Branch("hcalout_etabin",&m_hcalout_etabin);
  towerntuple->Branch("hcalout_phibin",&m_hcalout_phibin);
  towerntuple->Branch("hcalout_time",&m_time);


  towerntuple->Branch("zdc_energy",&m_zdc_energy);
  towerntuple->Branch("zdc_index",&m_zdc_index);
  towerntuple->Branch("zdc_side",&m_zdc_side);

  towerntuple->Branch("bbc_energy",&m_bbc_energy);
  towerntuple->Branch("bbc_type",&m_bbc_type);
  towerntuple->Branch("bbc_side",&m_bbc_side);





  return 0;
}

int CaloAna::process_event(PHCompositeNode* topNode)
{

  process_towers(topNode);
  return Fun4AllReturnCodes::EVENT_OK;
}


int CaloAna::process_towers(PHCompositeNode* topNode)
{
  ostringstream nodename;
  ostringstream geonodename;

  nodename.str("");
  nodename << "TOWERS_CEMC_" << detector;
  geonodename.str("");
 
  {
    TowerInfoContainer* offlinetowers = findNode::getClass<TowerInfoContainerv1>(topNode, "TOWERS_CEMC");
    int size = offlinetowers->size(); //online towers should be the same!
    for (int channel = 0; channel < size;channel++)
      {
	TowerInfo* offlinetower = offlinetowers->get_tower_at_channel(channel);
	float offlineenergy = offlinetower->get_energy();
	unsigned int towerkey = offlinetowers->encode_key(channel);
	int ieta = offlinetowers->getTowerEtaBin(towerkey);
	int iphi = offlinetowers->getTowerPhiBin(towerkey);
	
	m_energy.push_back(offlineenergy);
	m_time.push_back(offlinetower->get_time());
	m_etabin.push_back(ieta);
	m_phibin.push_back(iphi);
      }
  }
  
  {
    TowerInfoContainer* offlinetowers = findNode::getClass<TowerInfoContainerv1>(topNode, "TOWERS_HCALIN");
    int size = offlinetowers->size(); //online towers should be the same!
    for (int channel = 0; channel < size;channel++)
      {
	TowerInfo* offlinetower = offlinetowers->get_tower_at_channel(channel);
	float offlineenergy = offlinetower->get_energy();
	unsigned int towerkey = offlinetowers->encode_key(channel);
	int ieta = offlinetowers->getTowerEtaBin(towerkey);
	int iphi = offlinetowers->getTowerPhiBin(towerkey);
	
	m_hcalin_energy.push_back(offlineenergy);
	m_hcalin_time.push_back(offlinetower->get_time());
	m_hcalin_etabin.push_back(ieta);
	m_hcalin_phibin.push_back(iphi);
      }
  }
  
  {
    TowerInfoContainer* offlinetowers = findNode::getClass<TowerInfoContainerv1>(topNode, "TOWERS_HCALOUT");
    int size = offlinetowers->size(); //online towers should be the same!
    for (int channel = 0; channel < size;channel++)
      {
	TowerInfo* offlinetower = offlinetowers->get_tower_at_channel(channel);
	float offlineenergy = offlinetower->get_energy();
	unsigned int towerkey = offlinetowers->encode_key(channel);
	int ieta = offlinetowers->getTowerEtaBin(towerkey);
	int iphi = offlinetowers->getTowerPhiBin(towerkey);
	
	m_hcalout_energy.push_back(offlineenergy);
	m_hcalout_time.push_back(offlinetower->get_time());
	m_hcalout_etabin.push_back(ieta);
	m_hcalout_phibin.push_back(iphi);
      }
  }


  {
    TowerInfoContainer* offlinetowers = findNode::getClass<TowerInfoContainerv1>(topNode, "TOWERS_MBD");
    int size = offlinetowers->size(); //online towers should be the same!
    for (int channel = 0; channel < size;channel++)
      {
	TowerInfo* offlinetower = offlinetowers->get_tower_at_channel(channel);
	float offlineenergy = offlinetower->get_energy();
	unsigned int towerkey = TowerInfoDefs::encode_mbd(channel);
	int side = TowerInfoDefs::get_mbd_side(towerkey);
	int type = TowerInfoDefs::get_mbd_type(towerkey);
	
	m_bbc_energy.push_back(offlineenergy);
	m_bbc_side.push_back(side);
	m_bbc_type.push_back(type);
      }
  }


  {
    TowerInfoContainer* offlinetowers = findNode::getClass<TowerInfoContainerv1>(topNode, "TOWERS_ZDC");
    int size = offlinetowers->size(); //online towers should be the same!
    for (int channel = 0; channel < size;channel++)
      {
	TowerInfo* offlinetower = offlinetowers->get_tower_at_channel(channel);
	float offlineenergy = offlinetower->get_energy();
	unsigned int towerkey = TowerInfoDefs::encode_zdc(channel);
	int side = TowerInfoDefs::get_zdc_side(towerkey);
	int index = TowerInfoDefs::get_zdc_module_index(towerkey);
	
	m_zdc_energy.push_back(offlineenergy);
	m_zdc_side.push_back(side);
	m_zdc_index.push_back(index);
      }
  }

  towerntuple->Fill();
  
  m_etabin.clear();
  m_phibin.clear();
  m_energy.clear();
  m_time.clear();

  m_hcalin_etabin.clear();
  m_hcalin_phibin.clear();
  m_hcalin_energy.clear();
  m_hcalin_time.clear();

  m_hcalout_etabin.clear();
  m_hcalout_phibin.clear();
  m_hcalout_energy.clear();
  m_hcalout_time.clear();

  m_zdc_energy.clear();
  m_zdc_index.clear();
  m_zdc_side.clear();


  m_bbc_energy.clear();
  m_bbc_type.clear();
  m_bbc_side.clear();





  
  return Fun4AllReturnCodes::EVENT_OK;
}

int CaloAna::End(PHCompositeNode* /*topNode*/)
{
  outfile->cd();
 
  towerntuple->Write();

  outfile->Write();
  outfile->Close();
  delete outfile;
  hm->dumpHistos(outfilename, "UPDATE");
  return 0;
}
