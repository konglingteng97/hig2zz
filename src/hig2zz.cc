// -*- C++ -*- //
//
// Description: Higgs -> ZZ* 
//
// Original Author:  JING Maoqiang <jingmq@ihep.ac.cn>
//         Created:  [2018-04-02 Mon 15:49] 
//         Inspired by CHEN Zhenxing's code 
//
// 

//
// system include files
//

// for MCParticle, collection and reconstruction
#include <EVENT/LCCollection.h>
#include <IMPL/LCCollectionVec.h>
#include <EVENT/LCFloatVec.h>
#include <EVENT/MCParticle.h>
#include <marlin/Processor.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/MCParticleImpl.h>
#include <EVENT/LCFloatVec.h>
#include <EVENT/LCParameters.h>

// for general definition
// #include <values.h>
#include <string>
#include <iostream>
#include <TFile.h> 
#include <TTree.h>
#include <TVector3.h>
#include <TRandom.h>
//#include <sstream>              
#include <cmath>
#include <vector>
#include <TMath.h>
#include <TLorentzVector.h>
//#include <stdexcept>
//#include <Rtypes.h>

class hig2zz  : public marlin::Processor {

	public:
		Processor*  newProcessor() { return new hig2zz ; }
		hig2zz();
		~hig2zz() {};

		void init();
		void processEvent( LCEvent * evt );
		void end();

	private:
		std::string FileName;
		std::string TreeName;

		LCCollection* col_MC;
		LCCollection* col_Reco;
		MCParticle *a1_MC;

		TFile *m_file;
		TTree *m_tree;

		int LeptonID, RecoPID, tmpPID, PhotonPID, ElectronPID, MuonPID, NeutrinoEPID, NeutrinoMuonPID, TauPID, NeutrinoTauPID, ZPID, HiggsPID;
		int nMC, nReco, NCandiP, NCandiM, NParent, NDaughter, DIndex;
		int OverWrite;
		float RecoEMax, RecoEMin, ZMass;
		int m_n_gamma, m_n_charged, m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm, m_n_Higgsdaughter, m_n_neutrino;
		unsigned int m_event;
		float m_p_neutral[4], m_p_photon[4], m_p_charged[4], m_p_leptonp[4], m_p_leptonm[4], m_p_dilepton[4], m_p_allrec[4], m_p_Higgs[4], m_p_Zdaughters[4], m_p_Zdaughterp[4], m_p_Zdaughterm[4], m_p_Higgsdaughters[4], m_p_Higgsdaughter1[4],m_p_Higgsdaughter2[4];
		float m_m_Higgs, m_m_visble, m_m_recoil, m_m_Z;
		float m_pt_photon, m_pt_dilepton;
		float RecoE;
		float RecoP[3];
		int m_event_type;
		float m_energy_visble, m_energy_neutrino;
		// float m_m_recoil[11];
		// float spreadfactor[11];
		float scale1, scale2;
		float currVisMass, currRecoilMass, currVisEnergy;
		float MinZThrDis;
		float m_phi_dilepton_1, m_phi_dilepton_2;
		float phi_p_tmp, phi_m_tmp;
		float m_cos_miss, m_cos_Z;
		float m_angle_dilepton;
		float m_delta_pt;
                float MCEn;
		int m_PID_Zdaughter, m_PID_HiggsDaughter, m_PID_Higgsdaughter[2], m_n_Zneutrino;
		// TLorentzVector P_P, P_M, P_T[11];

		TLorentzVector P_P, P_M, P_T, miss;
		std::vector<TLorentzVector> FourMom_ElectronP, FourMom_ElectronM, FourMom_ChargedP, FourMom_ChargedM, CandiP, CandiM;

		void book_tree();
		void saveNeutral( int nReco, LCCollection* colReco );
		void savePhoton( int nReco, LCCollection* colReco );
		void selectCharged( int nReco, LCCollection* colReco );
		void selectElectron( float RecoE, int RecoPID, TLorentzVector curr, ReconstructedParticle *a_Reco );
		void saveEventType( int m_n_leptonp, int m_n_leptonm, int m_n_chargedp, int m_n_chargedm );
		void saveEvent( int NCandiP, int NCandiM, std::vector<TLorentzVector> CandiP, std::vector<TLorentzVector> CandiM, float m_pt_photon );
		void saveRecInfo( TLorentzVector P_P, TLorentzVector P_M, float m_pt_photon );
		void saveHiggsMass( float *m_p_neutral, float *m_p_charged, float *m_p_dilepton );
		void saveMCInfo( int nMC, LCCollection* col_MC );
		void saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveHiggsdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC );
		void saveNeutrino( int NDaughter, int tmpPID, float MCEn );
		void variable_init();

  LCCollection* col_IsoLepton;
  int nIsoLepton;
  
  LCCollection* col_FastJet;
  int nFastJet;
  void saveFastJet( int FastJet, LCCollection* col_FastJet );
  int m_nfastjet;
  std::vector<float> *m_fastjet_px; 
  std::vector<float> *m_fastjet_py;
  std::vector<float> *m_fastjet_pz;
  std::vector<float> *m_fastjet_e;
  float m_invMass_FastJet;
  float m_absMom_FastJet;
  float m_totEne_FastJet;
  TLorentzVector P4_FastJet_1, P4_FastJet_2;
  float m_recoil_fast_jet;
  float m_recoil_fastjj_ll;

  LCCollection* col_LcfiJet;
  int nLcfiJet;
  void saveLcfiJet( int LcfiJet, LCCollection* col_LcfiJet );
  int m_nlcfijet;
  std::vector<float> *m_lcfijet_px; 
  std::vector<float> *m_lcfijet_py;
  std::vector<float> *m_lcfijet_pz;
  std::vector<float> *m_lcfijet_e;
  float m_invMass_LcfiJet;
  float m_absMom_LcfiJet;
  float m_totEne_LcfiJet;
  TLorentzVector P4_LcfiJet_1, P4_LcfiJet_2;
  float m_recoil_lcfi_jet;
  float m_recoil_lcfijj_ll;
};

hig2zz a_hig2inv_instance;

hig2zz::hig2zz()
     : Processor("hig2zz") {


	FileName="MCTruth.root";
		registerProcessorParameter( "TreeOutputFile" ,
			"The name of the file to which the ROOT tree will be written" ,
			FileName ,
			FileName);

	TreeName="MCPart";
		registerProcessorParameter( "TreeName" ,
			"The name of the ROOT tree" ,
			TreeName ,
			TreeName);

	LeptonID=13; // 11 for electron, 13 for muon
		registerProcessorParameter( "LeptonIDTag" ,
			"Lepton ID that will be used in this analysis." ,
			LeptonID ,
			LeptonID);

	OverWrite=0;
			registerProcessorParameter( "OverwriteFile" ,
			"If zero an already existing file will not be overwritten." ,
			OverWrite ,
			OverWrite);

	PhotonPID=22; // 22 for photon
		registerProcessorParameter( "PhotonPID" ,
			"Photon ID that will be used in this analysis." ,
			PhotonPID ,
			PhotonPID);

	RecoEMax=100;
		registerProcessorParameter( "RecoEMax" ,
			"Maximum energy of reconstructed particles." ,
			RecoEMax ,
			RecoEMax);

	RecoEMin=10; 
		registerProcessorParameter( "RecoEMin" ,
			"Minimum energy of reconstructed particles." ,
			RecoEMin ,
			RecoEMin);

	ZMass=91.2; 
		registerProcessorParameter( "ZMass" ,
			"Mass of Z Boson." ,
			ZMass ,
			ZMass);

	ElectronPID=11;
		registerProcessorParameter( "ElectronPID" ,
			"Electron ID that will be used in this analysis." ,
			ElectronPID ,
			ElectronPID);

	NeutrinoEPID=12;
		registerProcessorParameter( "NeutrinoEPID" ,
			"Electron neutrino ID that will be used in this analysis." ,
			NeutrinoEPID ,
			NeutrinoEPID);

	MuonPID=13;
		registerProcessorParameter( "MuonPID" ,
			"Muon ID that will be used in this analysis." ,
			MuonPID ,
			MuonPID);

	NeutrinoMuonPID=14;
		registerProcessorParameter( "NeutrinoMuonPID" ,
			"Muon neutrino ID that will be used in this analysis." ,
			NeutrinoMuonPID ,
			NeutrinoMuonPID);

	TauPID=15;
		registerProcessorParameter( "TauPID" ,
			"Tau ID that will be used in this analysis." ,
			TauPID ,
			TauPID);

	NeutrinoTauPID=16;
		registerProcessorParameter( "NeutrinoTauPID" ,
			"Tau neutrino ID that will be used in this analysis." ,
			NeutrinoTauPID ,
			NeutrinoTauPID);

	ZPID=23;
		registerProcessorParameter( "ZPID" ,
			"Z Boson ID that will be used in this analysis." ,
			ZPID ,
			ZPID);

	HiggsPID=25;
		registerProcessorParameter( "HiggsPID" ,
			"Higgs Boson ID that will be used in this analysis." ,
			HiggsPID ,
			HiggsPID);

}

void hig2zz::init() {

	book_tree();

}

void hig2zz::processEvent( LCEvent * evt ) {	

	if(evt){
		try{
			variable_init();

			// Save FastJet info.
			col_FastJet = evt->getCollection( "FastJets" );
			nFastJet = col_FastJet->getNumberOfElements();
			saveFastJet( nFastJet, col_FastJet ); 

			// Save LCFIplus Jet info.
			col_LcfiJet = evt->getCollection( "RefinedJets" );
			nLcfiJet = col_LcfiJet->getNumberOfElements();
			saveLcfiJet( nLcfiJet, col_LcfiJet ); 

			// Call IsolatedLepton info.
			col_IsoLepton = evt->getCollection( "IsoLeps" );
			nIsoLepton = col_IsoLepton->getNumberOfElements();

			col_MC = evt->getCollection( "MCParticle" );
			col_Reco = evt->getCollection( "ArborPFOs" );
			nMC = col_MC->getNumberOfElements();
			nReco = col_Reco->getNumberOfElements();
			m_event=evt->getEventNumber();

                        saveNeutral( nReco, col_Reco );
			savePhoton( nReco, col_Reco );
			//selectCharged( nReco, col_Reco );
			//saveEventType( m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm );

			selectCharged( nIsoLepton, col_IsoLepton );
			saveEventType( m_n_leptonp, m_n_leptonm, m_n_chargedp, m_n_chargedm );

			NCandiP = CandiP.size();
			NCandiM = CandiM.size();

			saveEvent( NCandiP, NCandiM, CandiP, CandiM, m_pt_photon );
			saveHiggsMass( m_p_neutral, m_p_charged, m_p_dilepton );
			saveMCInfo( nMC, col_MC );

			m_tree->Fill();
		}
		catch (lcio::DataNotAvailableException err) { }
	}

}	

void hig2zz::end() {

	if (m_tree) {
		TFile *tree_file = m_tree->GetCurrentFile(); //just in case we switched to a new file
		tree_file->Write();
		delete tree_file;
	}

}

void hig2zz::book_tree() {

	m_file=new TFile(FileName.c_str(),(OverWrite ? "RECREATE" : "UPDATE"));
	if (!m_file->IsOpen()) {
		delete m_file;
		m_file=new TFile(FileName.c_str(),"NEW");
	}
	m_tree = new TTree(TreeName.c_str(),TreeName.c_str());
	m_tree->Branch("m_event",&m_event,"m_event/I");
	m_tree->Branch("m_event_type",  &m_event_type,  "m_event_type/I");

	m_tree->Branch("m_p_neutral", m_p_neutral, "m_p_neutral[4]/F");
	m_tree->Branch("m_p_photon", m_p_photon, "m_p_photon[4]/F");
	m_tree->Branch("m_p_leptonp",  m_p_leptonp,  "m_p_lepton[4]/F");
	m_tree->Branch("m_p_leptonm",  m_p_leptonm,  "m_p_lepton[4]/F");
	m_tree->Branch("m_p_dilepton",  m_p_dilepton,  "m_p_dilepton[4]/F");
	m_tree->Branch("m_p_charged",  m_p_charged,  "m_p_charged[4]/F");
	m_tree->Branch("m_p_allrec",  m_p_allrec,  "m_p_allrec[4]/F");
	m_tree->Branch("m_p_Higgs",  m_p_Higgs,  "m_p_Higgs[4]/F");
	m_tree->Branch("m_p_Higgsdaughters",  m_p_Higgsdaughters,  "m_p_Higgsdaughters[4]/F");
	m_tree->Branch("m_p_Higgsdaughter1",  m_p_Higgsdaughter1,  "m_p_Higgsdaughter1[4]/F");
	m_tree->Branch("m_p_Higgsdaughter2",  m_p_Higgsdaughter2,  "m_p_Higgsdaughter2[4]/F");
	m_tree->Branch("m_p_Zdaughters",  m_p_Zdaughters,  "m_p_Zdaughters[4]/F");
	m_tree->Branch("m_p_Zdaughterp",  m_p_Zdaughterp,  "m_p_Zdaughterp[4]/F");
	m_tree->Branch("m_p_Zdaughterm",  m_p_Zdaughterm,  "m_p_Zdaughterm[4]/F");

	m_tree->Branch("m_pt_photon", &m_pt_photon, "m_pt_photon/F");
	m_tree->Branch("m_pt_dilepton",  &m_pt_dilepton,  "m_pt_dilepton/F");

	m_tree->Branch("m_n_charged",  &m_n_charged,  "m_n_charged/I");
	m_tree->Branch("m_n_gamma",  &m_n_gamma,  "m_n_gamma/I");
	m_tree->Branch("m_n_leptonp",  &m_n_leptonp,  "m_n_leptonp/I");
	m_tree->Branch("m_n_leptonm",  &m_n_leptonm,  "m_n_leptonm/I");
	m_tree->Branch("m_n_chargedp",  &m_n_chargedp,  "m_n_chargedp/I");
	m_tree->Branch("m_n_chargedm",  &m_n_chargedm,  "m_n_chargedm/I");
	m_tree->Branch("m_n_Higgsdaughter",  &m_n_Higgsdaughter,  "m_n_Higgsdaughter/I");
	m_tree->Branch("m_n_Zneutrino",  &m_n_Zneutrino,  "m_n_Zneutrino/I");
	m_tree->Branch("m_n_neutrino",  &m_n_neutrino,  "m_n_neutrino/I");

	m_tree->Branch("m_m_visble",  &m_m_visble,  "m_m_visble/F");
	// m_tree->Branch("m_m_recoil",  m_m_recoil,  "m_m_recoil[11]/F");
	m_tree->Branch("m_m_recoil",  &m_m_recoil,  "m_m_recoil/F");
	m_tree->Branch("m_m_Higgs",  &m_m_Higgs,  "m_m_Higgs/F");
	m_tree->Branch("m_m_Z",  &m_m_Z,  "m_m_Z/F");

	m_tree->Branch("m_phi_dilepton_1",  &m_phi_dilepton_1,  "m_phi_dilepton_1/F");
	m_tree->Branch("m_phi_dilepton_2",  &m_phi_dilepton_2,  "m_phi_dilepton_2/F");
	m_tree->Branch("m_cos_miss",  &m_cos_miss,  "m_cos_miss/F");
	m_tree->Branch("m_cos_Z",  &m_cos_Z,  "m_cos_Z/F");
	m_tree->Branch("m_angle_dilepton",  &m_angle_dilepton,  "m_angle_dilepton/F");
	m_tree->Branch("m_delta_pt",  &m_delta_pt,  "m_delta_pt/F");

	m_tree->Branch("m_PID_Zdaughter",  &m_PID_Zdaughter,  "m_PID_Zdaughter/I");
	m_tree->Branch("m_PID_HiggsDaughter",  &m_PID_HiggsDaughter,  "m_PID_HiggsDaughter/I");
	m_tree->Branch("m_PID_Higgsdaughter",  m_PID_Higgsdaughter,  "m_PID_Higgsdaughter[2]/I");

	m_tree->Branch("m_energy_neutrino",  &m_energy_neutrino,  "m_energy_neutrino/F");
	m_tree->Branch("m_energy_visble",  &m_energy_visble,  "m_energy_visble/F");

	m_tree->Branch("m_nfastjet",  &m_nfastjet,  "m_nfastjet/I");	
	m_tree->Branch("m_fastjet_px", &m_fastjet_px);
	m_tree->Branch("m_fastjet_py", &m_fastjet_py);
	m_tree->Branch("m_fastjet_pz", &m_fastjet_pz);
	m_tree->Branch("m_fastjet_e", &m_fastjet_e);
	m_tree->Branch("m_invMass_FastJet", &m_invMass_FastJet, "m_invMass_FastJet/F"); 
	m_tree->Branch("m_absMom_FastJet", &m_absMom_FastJet, "m_absMom_FastJet/F");
 	m_tree->Branch("m_totEne_FastJet", &m_totEne_FastJet, "m_totEne_FastJet/F"); 
	m_tree->Branch("m_recoil_fast_jet", &m_recoil_fast_jet, "m_recoil_fast_jet/F");
	m_tree->Branch("m_recoil_fastjj_ll", &m_recoil_fastjj_ll, "m_recoil_fastjj_ll/F");

	m_tree->Branch("m_nlcfijet",  &m_nlcfijet,  "m_nlcfijet/I");	
	m_tree->Branch("m_lcfijet_px", &m_lcfijet_px);
	m_tree->Branch("m_lcfijet_py", &m_lcfijet_py);
	m_tree->Branch("m_lcfijet_pz", &m_lcfijet_pz);
	m_tree->Branch("m_lcfijet_e", &m_lcfijet_e);
	m_tree->Branch("m_invMass_LcfiJet", &m_invMass_LcfiJet, "m_invMass_LcfiJet/F"); 
	m_tree->Branch("m_absMom_LcfiJet", &m_absMom_LcfiJet, "m_absMom_LcfiJet/F");
 	m_tree->Branch("m_totEne_LcfiJet", &m_totEne_LcfiJet, "m_totEne_LcfiJet/F"); 
	m_tree->Branch("m_recoil_lcfi_jet", &m_recoil_lcfi_jet, "m_recoil_lcfi_jet/F");
	m_tree->Branch("m_recoil_lcfijj_ll", &m_recoil_lcfijj_ll, "m_recoil_lcfijj_ll/F");
}

void hig2zz::variable_init() {

	m_n_charged = 0;
	m_n_leptonp = 0;
	m_n_leptonm = 0;
	m_n_chargedp = 0;
	m_n_chargedm = 0;
	m_n_gamma = 0;
	m_n_Zneutrino = 0;
	m_n_neutrino = 0;
	m_event_type = -1;
	m_energy_neutrino = 0.;
	MinZThrDis = 1.0E10;
	DIndex = 0;
	//TLorentzVector beamp(0,0,125.0,125.0);
	//TLorentzVector beamm(0,0,-125.0,125.0);
	TLorentzVector beamp(0,0,120.0,120.0);
	TLorentzVector beamm(0,0,-120.0,120.0);
	// float spreadfactor[11]={0.0,0.0004,0.0008,0.0012,0.0016,0.0020,0.0024,0.0028,0.0032,0.0036,0.0040};
	// for(int i=0; i<11; i++) {
	// 	scale1 = (gRandom->Gaus(1, spreadfactor[i]));
	// 	scale2 = (gRandom->Gaus(1, spreadfactor[i]));
	// 	P_T[i]=scale1*beamp+scale2*beamm;
	// }
	scale1 = (gRandom->Gaus(1, 0.0024));
	scale2 = (gRandom->Gaus(1, 0.0024));
	P_T=scale1*beamp+scale2*beamm;
	for(int i=0; i<4; i++) {
		m_p_neutral[i] = 0;
		m_p_Zdaughters[i] = 0;
		m_p_charged[i] = 0;
	}
	FourMom_ElectronM.clear();
	FourMom_ElectronP.clear();
	FourMom_ChargedP.clear();
	FourMom_ChargedM.clear();
	CandiP.clear();
	CandiM.clear();

	// For Jet info.
	m_nfastjet = 0;
	m_fastjet_px->clear();
	m_fastjet_py->clear();
	m_fastjet_pz->clear();
	m_fastjet_e->clear();
	m_invMass_FastJet = 0;
	m_absMom_FastJet = 0;
	m_totEne_FastJet = 0;
	m_recoil_fast_jet = 0;
	m_recoil_fastjj_ll = 0;
	for(int i=0; i<4; i++) {
	  P4_FastJet_1[i] = 0.0;
	  P4_FastJet_2[i] = 0.0;
	}
	m_nlcfijet = 0;
	m_lcfijet_px->clear();
	m_lcfijet_py->clear();
	m_lcfijet_pz->clear();
	m_lcfijet_e->clear();
	m_invMass_LcfiJet = 0;
	m_absMom_LcfiJet = 0;
	m_totEne_LcfiJet = 0;
	m_recoil_lcfi_jet = 0;
	m_recoil_lcfijj_ll = 0;
	for(int i=0; i<4; i++) {
	  P4_LcfiJet_1 = 0.0;
	  P4_LcfiJet_2 = 0.0;
	}
}

void hig2zz::saveFastJet( int nFastJet, LCCollection* col_FastJet ) {

  std::cout << "nFastJet = " << nFastJet << std::endl;
  m_nfastjet = nFastJet;
  for( int i = 0; i < nFastJet; i++) {

    ReconstructedParticle *reco_jet = dynamic_cast<EVENT::ReconstructedParticle *>(col_FastJet->getElementAt(i));
    m_fastjet_px->push_back( reco_jet->getMomentum()[0] );
    m_fastjet_py->push_back( reco_jet->getMomentum()[1] );
    m_fastjet_pz->push_back( reco_jet->getMomentum()[2] );
    m_fastjet_e->push_back( reco_jet->getEnergy() );
  }

  if( nFastJet == 2 ) {
    
    TLorentzVector jet1, jet2;
      
    ReconstructedParticle *reco_jet1 = dynamic_cast<EVENT::ReconstructedParticle *>(col_FastJet->getElementAt(0));
    ReconstructedParticle *reco_jet2 = dynamic_cast<EVENT::ReconstructedParticle *>(col_FastJet->getElementAt(1));
      
    jet1[0] = reco_jet1->getMomentum()[0];
    jet1[1] = reco_jet1->getMomentum()[1];
    jet1[2] = reco_jet1->getMomentum()[2];
    jet1[3] = reco_jet1->getEnergy();

    jet2[0] = reco_jet2->getMomentum()[0];
    jet2[1] = reco_jet2->getMomentum()[1];
    jet2[2] = reco_jet2->getMomentum()[2];
    jet2[3] = reco_jet2->getEnergy();

    m_invMass_FastJet = ( jet1 + jet2 ).M();
    m_absMom_FastJet = ( jet1 + jet2 ).P();
    m_totEne_FastJet = ( jet1 + jet2 ).E();

    P4_FastJet_1 = jet1;
    P4_FastJet_2 = jet2;
  }
}

void hig2zz::saveLcfiJet( int nLcfiJet, LCCollection* col_LcfiJet ) {

  std::cout << "nLcfiJet = " << nLcfiJet << std::endl;
  m_nlcfijet = nLcfiJet;
  for( int i = 0; i < nLcfiJet; i++) {

      ReconstructedParticle *reco_jet = dynamic_cast<EVENT::ReconstructedParticle *>(col_LcfiJet->getElementAt(i));
      m_lcfijet_px->push_back( reco_jet->getMomentum()[0] );
      m_lcfijet_py->push_back( reco_jet->getMomentum()[1] );
      m_lcfijet_pz->push_back( reco_jet->getMomentum()[2] );
      m_lcfijet_e->push_back( reco_jet->getEnergy() );
    }

  if( nLcfiJet == 2 ) {
    
    TLorentzVector jet1, jet2;
      
    ReconstructedParticle *reco_jet1 = dynamic_cast<EVENT::ReconstructedParticle *>(col_LcfiJet->getElementAt(0));
    ReconstructedParticle *reco_jet2 = dynamic_cast<EVENT::ReconstructedParticle *>(col_LcfiJet->getElementAt(1));
      
    jet1[0] = reco_jet1->getMomentum()[0];
    jet1[1] = reco_jet1->getMomentum()[1];
    jet1[2] = reco_jet1->getMomentum()[2];
    jet1[3] = reco_jet1->getEnergy();

    jet2[0] = reco_jet2->getMomentum()[0];
    jet2[1] = reco_jet2->getMomentum()[1];
    jet2[2] = reco_jet2->getMomentum()[2];
    jet2[3] = reco_jet2->getEnergy();

    m_invMass_LcfiJet = ( jet1 + jet2 ).M();
    m_absMom_LcfiJet = ( jet1 + jet2 ).P();
    m_totEne_LcfiJet = ( jet1 + jet2 ).E();

    P4_LcfiJet_1 = jet1;
    P4_LcfiJet_2 = jet2;
  }

}


void hig2zz::saveNeutral( int nReco, LCCollection* col_Reco ) {

	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		m_p_neutral[3] += a_Reco->getEnergy();
		m_p_neutral[0] += a_Reco->getMomentum()[0];
		m_p_neutral[1] += a_Reco->getMomentum()[1];
		m_p_neutral[2] += a_Reco->getMomentum()[2];
	}

}

void hig2zz::savePhoton( int nReco, LCCollection* col_Reco ) {

	float photone=-1.;
	int N_Gam=0;
	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()!=0) continue;
		if(a_Reco->getType()!=PhotonPID) continue;
		if(fabs(a_Reco->getMomentum()[2]/a_Reco->getEnergy())>0.995) continue; // acceptance of the detector
		N_Gam++;
		if(a_Reco->getEnergy()>photone) {
			photone = a_Reco->getEnergy();
			m_p_photon[3] = a_Reco->getEnergy();
			m_p_photon[0] = a_Reco->getMomentum()[0];
			m_p_photon[1] = a_Reco->getMomentum()[1];
			m_p_photon[2] = a_Reco->getMomentum()[2];
			m_pt_photon = sqrt(m_p_photon[0]*m_p_photon[0]+m_p_photon[1]*m_p_photon[1]);
		}
	}
	m_n_gamma = N_Gam;

}

void hig2zz::selectCharged( int nReco, LCCollection* col_Reco ) {

	int N_Charged = 0;
	for(int i = 0; i < nReco; i++) {
		ReconstructedParticle *a_Reco = dynamic_cast<EVENT::ReconstructedParticle *>(col_Reco->getElementAt(i));
		if(a_Reco->getCharge()==0) continue;
		RecoPID = a_Reco->getType();
		RecoE = a_Reco->getEnergy();
		RecoP[0] = a_Reco->getMomentum()[0];
		RecoP[1] = a_Reco->getMomentum()[1];
		RecoP[2] = a_Reco->getMomentum()[2];
		TLorentzVector curr(RecoP[0], RecoP[1], RecoP[2], RecoE);
		N_Charged++;
		for(int j = 0; j < 4; j++) {
			m_p_charged[j] += curr[j];
		}
		selectElectron( RecoE, RecoPID, curr, a_Reco );
	}
	m_n_charged = N_Charged;
	m_n_leptonp = FourMom_ElectronP.size();
	m_n_leptonm = FourMom_ElectronM.size();
	m_n_chargedp = FourMom_ChargedP.size();
	m_n_chargedm = FourMom_ChargedM.size();

}

void hig2zz::selectElectron( float RecoE, int RecoPID, TLorentzVector curr, ReconstructedParticle *a_Reco ) {

	if( RecoE > RecoEMin && RecoE < RecoEMax ) {  //0.4*sqrt(s) 
		if(abs(RecoPID) == LeptonID ) {
			if(RecoPID == LeptonID ) { 
				FourMom_ElectronM.push_back(curr);
			}
			else {
				FourMom_ElectronP.push_back(curr);
			}
		}
		else if( a_Reco->getCharge() > 0.5 ) {
			FourMom_ChargedP.push_back(curr);
		}
		else if( a_Reco->getCharge() < -0.5 ) {
			FourMom_ChargedM.push_back(curr);
		}
	}

}

void hig2zz::saveEventType( int m_n_leptonp, int m_n_leptonm, int m_n_chargedp, int m_n_chargedm ) {

	if( m_n_leptonp && m_n_leptonm ) {
		m_event_type = 0;
		CandiP = FourMom_ElectronP;
		CandiM = FourMom_ElectronM;
	}
	else if( m_n_leptonp == 0 && m_n_chargedp && m_n_leptonm ) {
		m_event_type = 1;
		CandiP = FourMom_ChargedP;
		CandiM = FourMom_ElectronM;
	}
	else if( m_n_leptonm == 0 && m_n_chargedm && m_n_leptonp ) {
		m_event_type = 2;
		CandiM = FourMom_ChargedM;
		CandiP = FourMom_ElectronP;
	}
	else if( m_n_leptonm == 0 && m_n_chargedm && m_n_chargedp && m_n_leptonp == 0 ) {
		m_event_type = 3;
		CandiM = FourMom_ChargedM;
		CandiP = FourMom_ChargedP;
	}

}

void hig2zz::saveEvent( int NCandiP, int NCandiM, std::vector<TLorentzVector> CandiP, std::vector<TLorentzVector> CandiM, float m_pt_photon ) {

	if( NCandiP > 0 && NCandiM > 0 ) {
		for(int i = 0; i < NCandiP; i++) {
			P_P = CandiP[i];
			for(int j = 0; j < NCandiM; j++) {
				P_M = CandiM[j];
				saveRecInfo( P_P, P_M, m_pt_photon );
			}
		}
	}

}

void hig2zz::saveRecInfo( TLorentzVector P_P, TLorentzVector P_M, float m_pt_photon ) {

  // For Higgs->ZZ
  m_recoil_fast_jet = ( P_T - P4_FastJet_1 - P4_FastJet_2).M(); 
  m_recoil_lcfi_jet = ( P_T - P4_LcfiJet_1 - P4_LcfiJet_2).M(); 

  m_recoil_fastjj_ll = ( P_T - P_P - P_M - P4_FastJet_1 - P4_FastJet_2).M(); 
  m_recoil_lcfijj_ll = ( P_T - P_P - P_M - P4_LcfiJet_1 - P4_LcfiJet_2).M(); 

	currVisMass = (P_P + P_M).M();
	currVisEnergy = P_P[3] + P_M[3];
	if(fabs(currVisMass - ZMass) < MinZThrDis) {
		MinZThrDis = fabs(currVisMass - ZMass);
		m_m_visble = currVisMass;
		m_energy_visble = currVisEnergy;
		// save recil mass
		// for(int i=0; i<11; i++) {
		// 	currRecoilMass = (P_T[i] - P_P - P_M).M();
		// 	m_m_recoil[i] = currRecoilMass;
		// }
		currRecoilMass = (P_T - P_P - P_M).M();
		m_m_recoil = currRecoilMass;
		// save lepton information
		if (m_event_type == 0) {
			for(int i=0; i<4; i++) {
				m_p_leptonp[i] = P_P[i];
				m_p_leptonm[i] = P_M[i];
				m_p_dilepton[i] = m_p_leptonp[i] + m_p_leptonm[i];
			}
			// save other information
			//TLorentzVector ecms(0,0,0,250);
			TLorentzVector ecms(0,0,0,240);
			m_phi_dilepton_1 = fabs(P_P.Phi()-P_M.Phi());
			miss = ecms - m_p_dilepton;
			m_cos_miss = miss.CosTheta();
			m_angle_dilepton = P_P.Angle(P_M.Vect())*180./3.1415926;
			m_pt_dilepton = sqrt(m_p_dilepton[0]*m_p_dilepton[0]+m_p_dilepton[1]*m_p_dilepton[1]);
			m_delta_pt = m_pt_dilepton - m_pt_photon;
			m_cos_Z = m_p_dilepton[2]/sqrt(m_p_dilepton[0]*m_p_dilepton[0]+m_p_dilepton[1]*m_p_dilepton[1]+m_p_dilepton[2]*m_p_dilepton[2]);
			phi_p_tmp = atan2(m_p_leptonp[1],m_p_leptonp[0])*180./3.14159265;
			phi_m_tmp = atan2(m_p_leptonm[1],m_p_leptonm[0])*180./3.14159265;
			if(m_p_leptonp[1] < 0) phi_p_tmp = phi_p_tmp + 360.;
			if(m_p_leptonm[1] < 0) phi_m_tmp = phi_m_tmp + 360.;
			m_phi_dilepton_2 = fabs(phi_p_tmp - phi_m_tmp);
			if (m_phi_dilepton_2 > 180) m_phi_dilepton_2 = 360. - m_phi_dilepton_2;
		}
	}

}

void hig2zz::saveHiggsMass( float *m_p_neutral, float *m_p_charged, float *m_p_dilepton ) {

	for(int i = 0; i < 4; i++) {
		m_p_allrec[i] = m_p_neutral[i] + m_p_charged[i];
		m_p_Higgs[i] = m_p_allrec[i] - m_p_dilepton[i];
	}
	m_m_Higgs = sqrt( m_p_Higgs[3] * m_p_Higgs[3] - m_p_Higgs[0] * m_p_Higgs[0] - m_p_Higgs[1] * m_p_Higgs[1] - m_p_Higgs[2] * m_p_Higgs[2] );

}

void hig2zz::saveMCInfo( int nMC, LCCollection* col_MC ) {

	for(int i = 0; i < nMC; i++) {
		a1_MC = dynamic_cast<EVENT::MCParticle *>(col_MC->getElementAt(i));
		tmpPID = a1_MC->getPDG();
		NParent = a1_MC->getParents().size();
		NDaughter = a1_MC->getDaughters().size();
		MCEn = a1_MC->getEnergy();
		saveZdaughter( NParent, NDaughter, tmpPID, MCEn, a1_MC );
		saveHiggsdaughter( NParent, NDaughter, tmpPID, MCEn, a1_MC );
		saveNeutrino( NDaughter, tmpPID, MCEn );
	}
	m_m_Z = sqrt(m_p_Zdaughters[3]*m_p_Zdaughters[3] - m_p_Zdaughters[0]*m_p_Zdaughters[0]- m_p_Zdaughters[1]*m_p_Zdaughters[1]- m_p_Zdaughters[2]*m_p_Zdaughters[2]);

}

void hig2zz::saveZdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC ) {

	if(NParent == 0 && NDaughter == 1 && abs(tmpPID) < 20 ) { //Including all Z decay
		m_PID_Zdaughter = abs(tmpPID);
		m_p_Zdaughters[3] += MCEn;
		m_p_Zdaughters[0] += a1_MC->getMomentum()[0];
		m_p_Zdaughters[1] += a1_MC->getMomentum()[1];
		m_p_Zdaughters[2] += a1_MC->getMomentum()[2];
		if( m_PID_Zdaughter < 6 || m_PID_Zdaughter == MuonPID || m_PID_Zdaughter == ElectronPID || m_PID_Zdaughter == TauPID ) {
			if(tmpPID > 0) {
				m_p_Zdaughterp[0] = a1_MC->getMomentum()[0];
				m_p_Zdaughterp[1] = a1_MC->getMomentum()[1];
				m_p_Zdaughterp[2] = a1_MC->getMomentum()[2];
				m_p_Zdaughterp[3] = MCEn;
			}
			else if(tmpPID < 0) {
				m_p_Zdaughterm[0] = a1_MC->getMomentum()[0];
				m_p_Zdaughterm[1] = a1_MC->getMomentum()[1];
				m_p_Zdaughterm[2] = a1_MC->getMomentum()[2];
				m_p_Zdaughterm[3] = MCEn;
			}
		}
	}

}

void hig2zz::saveHiggsdaughter( int NParent, int NDaughter, int tmpPID, float MCEn, MCParticle *a1_MC ) {

	if(tmpPID == HiggsPID && NDaughter > 1 && NParent !=0 ) { //Higgs
		m_n_Higgsdaughter = NDaughter;
		m_p_Higgsdaughters[3] = MCEn;
		m_p_Higgsdaughters[0] = a1_MC->getMomentum()[0];
		m_p_Higgsdaughters[1] = a1_MC->getMomentum()[1];
		m_p_Higgsdaughters[2] = a1_MC->getMomentum()[2];
		for(int i = 0; i < NDaughter; i++) { //NDaughter
			MCParticle *b_MC = a1_MC->getDaughters()[i];
			m_PID_HiggsDaughter = b_MC->getPDG();
			m_PID_Higgsdaughter[DIndex] = m_PID_HiggsDaughter;
			if(m_PID_HiggsDaughter < 6 || m_PID_HiggsDaughter == MuonPID || m_PID_HiggsDaughter == ElectronPID || m_PID_HiggsDaughter == TauPID ) {
				if(m_PID_HiggsDaughter > 0) {
					m_p_Higgsdaughter1[3] = b_MC->getEnergy();
					m_p_Higgsdaughter1[0] = b_MC->getMomentum()[0];
					m_p_Higgsdaughter1[1] = b_MC->getMomentum()[1];
					m_p_Higgsdaughter1[2] = b_MC->getMomentum()[2];
				}
				else if(m_PID_HiggsDaughter < 0) {
					m_p_Higgsdaughter2[3] = b_MC->getEnergy();
					m_p_Higgsdaughter2[0] = b_MC->getMomentum()[0];
					m_p_Higgsdaughter2[1] = b_MC->getMomentum()[1];
					m_p_Higgsdaughter2[2] = b_MC->getMomentum()[2];
				}
			}
			else if(DIndex == 0) {
				m_p_Higgsdaughter1[3] = b_MC->getEnergy();
				m_p_Higgsdaughter1[0] = b_MC->getMomentum()[0];
				m_p_Higgsdaughter1[1] = b_MC->getMomentum()[1];
				m_p_Higgsdaughter1[2] = b_MC->getMomentum()[2];
				DIndex = 1;
			}
			else if(DIndex == 1) {
				m_p_Higgsdaughter2[3] = b_MC->getEnergy();
				m_p_Higgsdaughter2[0] = b_MC->getMomentum()[0];
				m_p_Higgsdaughter2[1] = b_MC->getMomentum()[1];
				m_p_Higgsdaughter2[2] = b_MC->getMomentum()[2];
			}
			if(m_PID_HiggsDaughter==ZPID) {
				NDaughter = b_MC->getDaughters().size();
				for(int j=0; j<NDaughter; j++) {
					MCParticle *c_MC = b_MC->getDaughters()[j];
					if( abs(c_MC->getPDG())== NeutrinoEPID || abs(c_MC->getPDG())== NeutrinoMuonPID || abs(c_MC->getPDG())== NeutrinoTauPID ) {
						m_n_Zneutrino++;
					}
				}
			}
			m_PID_HiggsDaughter = abs(m_PID_HiggsDaughter);
		}
	}

}

void hig2zz::saveNeutrino( int NDaughter, int tmpPID, float MCEn ) {

	if(NDaughter == 0) {
		if( abs(tmpPID) == NeutrinoEPID || abs(tmpPID) == NeutrinoMuonPID || abs(tmpPID) == NeutrinoTauPID ) {
			m_n_neutrino++;
			m_energy_neutrino += MCEn;
		}
	}

}