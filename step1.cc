#define step1_cxx
#include "step1.h"
#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <TH2.h>
#include <TF1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>
#include <TH3.h>

using namespace std;

// ----------------------------------------------------------------------------
// Define functions
// ----------------------------------------------------------------------------

bool comparepair( const std::pair<double,int> a, const std::pair<double,int> b) { return a.first > b.first; }

TRandom3 Rand;

const double MTOP  = 173.5;
const double MW    = 80.4; 

bool step1::applySF(bool& isTagged, float tag_SF, float tag_eff){
  
  bool newTag = isTagged;
  if (tag_SF == 1) return newTag; //no correction needed 

  //throw die
  float coin = Rand.Uniform(1.);    

  if(tag_SF > 1){  // use this if SF>1

    if( !isTagged ) {

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - tag_SF) / (1.0 - (tag_SF/tag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isTagged && coin > tag_SF ) {newTag = false;}

  }

  return newTag;
}

// ----------------------------------------------------------------------------
// MAIN EVENT LOOP
// ----------------------------------------------------------------------------

void step1::Loop() 
{
  
  // ----------------------------------------------------------------------------
  // Turn on input tree branches
  // ----------------------------------------------------------------------------

   if (inputTree == 0) return;
   
   inputTree->SetBranchStatus("*",0);

   //Event info
   inputTree->SetBranchStatus("event_CommonCalc",1);
   inputTree->SetBranchStatus("run_CommonCalc",1);
   inputTree->SetBranchStatus("lumi_CommonCalc",1);
   inputTree->SetBranchStatus("nPV_singleLepCalc",1);
   inputTree->SetBranchStatus("nTrueInteractions_singleLepCalc",1);
   inputTree->SetBranchStatus("MCWeight_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweightids_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweights_singleLepCalc",1);
   inputTree->SetBranchStatus("HTfromHEPUEP_singleLepCalc",1);
   
   //triggers
   inputTree->SetBranchStatus("vsSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersMu_singleLepCalc",1);
   
   //electrons **** ADD MORE/NEW ID BRANCHES *****
   inputTree->SetBranchStatus("elPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elEta_singleLepCalc",1);
   inputTree->SetBranchStatus("elPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("elEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("elMVAValue_singleLepCalc",1);
   inputTree->SetBranchStatus("elMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsTightBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsMediumBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsLooseBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsVetoBarrel_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsMediumEndCap_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsLooseEndCap_singleLepCalc",1);
   inputTree->SetBranchStatus("elIsVetoEndCap_singleLepCalc",1);

   
   //muons  **** ADD MORE/NEW ID BRANCHES *****
   inputTree->SetBranchStatus("muPt_singleLepCalc",1);
   inputTree->SetBranchStatus("muEta_singleLepCalc",1);
   inputTree->SetBranchStatus("muPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("muEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("muMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsTight_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsMedium_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsMediumPrompt_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsLoose_singleLepCalc",1);

   //missing et
   inputTree->SetBranchStatus("corr_met_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_met_phi_singleLepCalc",1);

   //boosted truth
   inputTree->SetBranchStatus("HadronicVHtPt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtID_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2E_JetSubCalc",1);

   //genParticles
   inputTree->SetBranchStatus("genPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("genStatus_singleLepCalc",1);
   inputTree->SetBranchStatus("genID_singleLepCalc",1);
   inputTree->SetBranchStatus("genMotherID_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEnergy_singleLepCalc",1);

   //JetSubCalc
   inputTree->SetBranchStatus("theJetHFlav_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPFlav_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetEta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetDeepCSVb_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetDeepCSVc_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetDeepCSVudsg_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetDeepCSVbb_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetBTag_JetSubCalc",1);

   inputTree->SetBranchStatus("theJetAK8Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Mass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Energy_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau1_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau2_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau3_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDropRaw_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDropCorr_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDrop_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDrop_JMSup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDrop_JMSdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDrop_JMRup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDrop_JMRdn_JetSubCalc",1);

   //DeepAK8
   inputTree->SetBranchStatus("dnn_B_DeepAK8Calc",1);
   inputTree->SetBranchStatus("dnn_J_DeepAK8Calc",1);
   inputTree->SetBranchStatus("dnn_W_DeepAK8Calc",1);
   inputTree->SetBranchStatus("dnn_Z_DeepAK8Calc",1);
   inputTree->SetBranchStatus("dnn_H_DeepAK8Calc",1);
   inputTree->SetBranchStatus("dnn_largest_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_largest_DeepAK8Calc",1);
   inputTree->SetBranchStatus("dnn_T_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_B_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_J_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_W_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_Z_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_H_DeepAK8Calc",1);
   inputTree->SetBranchStatus("decorr_T_DeepAK8Calc",1);

   //JetSubCalc
   inputTree->SetBranchStatus("maxProb_JetSubCalc",1);
   
   //top
   inputTree->SetBranchStatus("ttbarMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("allTopsPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("allTopsID_TTbarMassCalc",1);
   inputTree->SetBranchStatus("allTopsStatus_TTbarMassCalc",1);

   inputTree->SetBranchStatus("topEnergy_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEta_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPhi_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topID_TTbarMassCalc",1);

   //top W
   inputTree->SetBranchStatus("topWEnergy_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topWEta_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topWPhi_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topWPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topWID_TTbarMassCalc",1);

   //top b
   inputTree->SetBranchStatus("topbEnergy_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topbEta_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topbPhi_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topbPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topbID_TTbarMassCalc",1);

   inputTree->SetBranchStatus("isTT_TTbarMassCalc",1);
   
  // ----------------------------------------------------------------------------
  // Create output tree and define branches
  // ----------------------------------------------------------------------------
   
   // OUTPUT FILE
   outputFile->cd();
   TTree *outputTree = new TTree("ljmet","ljmet");



   // ***** EVERY NEW BRANCH NEEDS A LINE HERE ****
   outputTree->Branch("event_CommonCalc",&event_CommonCalc,"event_CommonCalc/L");
   outputTree->Branch("run_CommonCalc",&run_CommonCalc,"run_CommonCalc/I");
   outputTree->Branch("lumi_CommonCalc",&lumi_CommonCalc,"lumi_CommonCalc/I");
   outputTree->Branch("nPV_singleLepCalc",&nPV_singleLepCalc,"nPV_singleLepCalc/I");
   outputTree->Branch("nTrueInteractions_singleLepCalc",&nTrueInteractions_singleLepCalc,"nTrueInteractions_singleLepCalc/I");
   outputTree->Branch("isElectron",&isElectron,"isElectron/I");
   outputTree->Branch("isMuon",&isMuon,"isMuon/I");
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");
   outputTree->Branch("MCWeight_singleLepCalc",&MCWeight_singleLepCalc,"MCWeight_singleLepCalc/D");
   outputTree->Branch("renormWeights",&renormWeights);
   outputTree->Branch("pdfWeights",&pdfWeights);
   outputTree->Branch("pileupWeight",&pileupWeight,"pileupWeight/F");
   outputTree->Branch("pileupWeightUp",&pileupWeightUp,"pileupWeightUp/F");
   outputTree->Branch("pileupWeightDown",&pileupWeightDown,"pileupWeightDown/F");
   outputTree->Branch("HTSF_Pol",&HTSF_Pol,"HTSF_Pol/F");
   outputTree->Branch("HTSF_PolUp",&HTSF_PolUp,"HTSF_PolUp/F");
   outputTree->Branch("HTSF_PolDn",&HTSF_PolDn,"HTSF_PolDn/F");
   outputTree->Branch("ttbarMass_TTbarMassCalc",&ttbarMass_TTbarMassCalc,"ttbarMass_TTbarMassCalc/D");
   outputTree->Branch("isTT_TTbarMassCalc",&isTT_TTbarMassCalc,"isTT_TTbarMassCalc/I");
   outputTree->Branch("corr_met_singleLepCalc",&corr_met_singleLepCalc,"corr_met_singleLepCalc/D");
   outputTree->Branch("corr_met_phi_singleLepCalc",&corr_met_phi_singleLepCalc,"corr_met_phi_singleLepCalc/D");
   outputTree->Branch("leptonPt_singleLepCalc",&leptonPt_singleLepCalc,"leptonPt_singleLepCalc/F");
   outputTree->Branch("leptonEta_singleLepCalc",&leptonEta_singleLepCalc,"leptonEta_singleLepCalc/F");
   outputTree->Branch("leptonPhi_singleLepCalc",&leptonPhi_singleLepCalc,"leptonPhi_singleLepCalc/F");
   outputTree->Branch("leptonEnergy_singleLepCalc",&leptonEnergy_singleLepCalc,"leptonEnergy_singleLepCalc/F");
   outputTree->Branch("leptonMVAValue_singleLepCalc",&leptonMVAValue_singleLepCalc,"leptonMVAValue_singleLepCalc/F");
   outputTree->Branch("leptonMiniIso_singleLepCalc",&leptonMiniIso_singleLepCalc,"leptonMiniIso_singleLepCalc/F");
   outputTree->Branch("theJetPt_JetSubCalc_PtOrdered",&theJetPt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetEta_JetSubCalc_PtOrdered",&theJetEta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetPhi_JetSubCalc_PtOrdered",&theJetPhi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetEnergy_JetSubCalc_PtOrdered",&theJetEnergy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetDeepCSVb_JetSubCalc_PtOrdered",&theJetDeepCSVb_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetDeepCSVbb_JetSubCalc_PtOrdered",&theJetDeepCSVbb_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetDeepCSVc_JetSubCalc_PtOrdered",&theJetDeepCSVc_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetDeepCSVudsg_JetSubCalc_PtOrdered",&theJetDeepCSVudsg_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetHFlav_JetSubCalc_PtOrdered",&theJetHFlav_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetPFlav_JetSubCalc_PtOrdered",&theJetPFlav_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetBTag_JetSubCalc_PtOrdered",&theJetBTag_JetSubCalc_PtOrdered);
   outputTree->Branch("BJetLeadPt",&BJetLeadPt,"BJetLeadPt/F");
   outputTree->Branch("WJetLeadPt",&WJetLeadPt,"WJetLeadPt/F");
   outputTree->Branch("TJetLeadPt",&TJetLeadPt,"TJetLeadPt/F");
   outputTree->Branch("AK4HTpMETpLepPt",&AK4HTpMETpLepPt,"AK4HTpMETpLepPt/F");
   outputTree->Branch("AK4HT",&AK4HT,"AK4HT/F");
   outputTree->Branch("NJets_JetSubCalc",&NJets_JetSubCalc,"NJets_JetSubCalc/I");
   outputTree->Branch("NJetsCSV_JetSubCalc",&NJetsCSV_JetSubCalc,"NJetsCSV_JetSubCalc/I");
   outputTree->Branch("NJetsCSVwithSF_JetSubCalc",&NJetsCSVwithSF_JetSubCalc,"NJetsCSVwithSF_JetSubCalc/I");
   outputTree->Branch("topPt",&topPt,"topPt/F");
   outputTree->Branch("topPtGen",&topPtGen,"topPtGen/F");
   outputTree->Branch("topMass",&topMass,"topMass/F");
   outputTree->Branch("minMleppBjet",&minMleppBjet,"minMleppBjet/F");
   outputTree->Branch("minMleppJet",&minMleppJet,"mixnMleppJet/F");
   outputTree->Branch("genTopPt",&genTopPt,"genTopPt/F");
   outputTree->Branch("genAntiTopPt",&genAntiTopPt,"genAntiTopPt/F");
   outputTree->Branch("topPtWeight13TeV",&topPtWeight13TeV,"topPtWeight13TeV/F");
   outputTree->Branch("minDR_lepJet",&minDR_lepJet,"minDR_lepJet/F");
   outputTree->Branch("ptRel_lepJet",&ptRel_lepJet,"ptRel_lepJet/F");
   outputTree->Branch("MT_lepMet",&MT_lepMet,"MT_lepMet/F");
   outputTree->Branch("deltaR_lepJets",&deltaR_lepJets);
   outputTree->Branch("deltaR_lepBJets",&deltaR_lepBJets);
   outputTree->Branch("muIsLoose_singleLepCalc",&muIsLoose_singleLepCalc);
   outputTree->Branch("muIsMedium_singleLepCalc",&muIsMedium_singleLepCalc);
   outputTree->Branch("muIsMediumPrompt_singleLepCalc",&muIsMediumPrompt_singleLepCalc);
   outputTree->Branch("muIsTight_singleLepCalc",&muIsTight_singleLepCalc);
   outputTree->Branch("elIsTightBarrel_singleLepCalc",&elIsTightBarrel_singleLepCalc,"elIsTightBarrel_singleLepCalc/F");
   outputTree->Branch("elIsMediumBarrel_singleLepCalc",&elIsMediumBarrel_singleLepCalc,"elIsMediumBarrel_singleLepCalc/F");
   outputTree->Branch("elIsLooseBarrel_singleLepCalc",&elIsLooseBarrel_singleLepCalc,"elIsLooseBarrel_singleLepCalc/F");
   outputTree->Branch("elIsVetoBarrel_singleLepCalc",&elIsVetoBarrel_singleLepCalc,"elIsVetoBarrel_singleLepCalc/F");
   outputTree->Branch("elIsTightEndCap_singleLepCalc",&elIsTightEndCap_singleLepCalc,"elIsTightEndCap_singleLepCalc/F");
   outputTree->Branch("elIsMediumEndCap_singleLepCalc",&elIsMediumEndCap_singleLepCalc,"elIsMediumEndCap_singleLepCalc/F");
   outputTree->Branch("elIsLooseEndCap_singleLepCalc",&elIsLooseEndCap_singleLepCalc,"elIsLooseEndCap_singleLepCalc/F");
   outputTree->Branch("elIsVetoEndCap_singleLepCalc",&elIsVetoEndCap_singleLepCalc,"elIsVetoEndCap_singleLepCalc/F");
   outputTree->Branch("EGammaGsfSF",&EGammaGsfSF,"EGammaGsfSF/F");
   outputTree->Branch("lepIdSF",&lepIdSF,"lepIdSF/F");

   outputTree->Branch("HadronicVHtID_JetSubCalc",&HadronicVHtID_JetSubCalc);
   outputTree->Branch("HadronicVHtPt_JetSubCalc",&HadronicVHtPt_JetSubCalc);
   outputTree->Branch("HadronicVHtEta_JetSubCalc",&HadronicVHtEta_JetSubCalc);
   outputTree->Branch("HadronicVHtPhi_JetSubCalc",&HadronicVHtPhi_JetSubCalc);
   outputTree->Branch("HadronicVHtEnergy_JetSubCalc",&HadronicVHtEnergy_JetSubCalc);

   outputTree->Branch("theJetAK8Pt_JetSubCalc_PtOrdered",&theJetAK8Pt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Eta_JetSubCalc_PtOrdered",&theJetAK8Eta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Phi_JetSubCalc_PtOrdered",&theJetAK8Phi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Mass_JetSubCalc_PtOrdered",&theJetAK8Mass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Energy_JetSubCalc_PtOrdered",&theJetAK8Energy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDropRaw_JetSubCalc_PtOrdered",&theJetAK8SoftDropRaw_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDropCorr_JetSubCalc_PtOrdered",&theJetAK8SoftDropCorr_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDrop_JetSubCalc_PtOrdered",&theJetAK8SoftDrop_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered",&theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered);
   outputTree->Branch("theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered",&theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered);
   outputTree->Branch("theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered",&theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered);
   outputTree->Branch("theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered",&theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau1_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau1_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau2_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau2_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau3_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau3_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Wmatch_JetSubCalc_PtOrdered",&theJetAK8Wmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Tmatch_JetSubCalc_PtOrdered",&theJetAK8Tmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8MatchedPt_JetSubCalc_PtOrdered",&theJetAK8MatchedPt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Indx_Wtagged",&theJetAK8Indx_Wtagged);
   
   outputTree->Branch("BJetLeadPt",&BJetLeadPt,"BJetLeadPt/F");
   outputTree->Branch("WJetLeadPt",&WJetLeadPt,"WJetLeadPt/F");
   outputTree->Branch("TJetLeadPt",&TJetLeadPt,"TJetLeadPt/F");
   outputTree->Branch("NJetsAK8_JetSubCalc",&NJetsAK8_JetSubCalc,"NJetsAK8_JetSubCalc/I");
   outputTree->Branch("NPuppiWtagged_0p55",&NPuppiWtagged_0p55,"NPuppiWtagged_0p55/I");
   outputTree->Branch("NPuppiWtagged_0p55_notTtagged",&NPuppiWtagged_0p55_notTtagged,"NPuppiWtagged_0p55_notTtagged/I");
   outputTree->Branch("NJetsTtagged_0p81",&NJetsTtagged_0p81,"NJetsTtagged_0p81/I");
   outputTree->Branch("minDR_leadAK8otherAK8",&minDR_leadAK8otherAK8,"minDR_leadAK8otherAK8/F");
   outputTree->Branch("minDR_lepAK8",&minDR_lepAK8,"minDR_lepAK8/F");
   outputTree->Branch("deltaR_lepAK8s",&deltaR_lepAK8s);

   outputTree->Branch("genPt_singleLepCalc",&genPt_singleLepCalc);
   outputTree->Branch("genEta_singleLepCalc",&genEta_singleLepCalc);
   outputTree->Branch("genPhi_singleLepCalc",&genPhi_singleLepCalc);
   outputTree->Branch("genEnergy_singleLepCalc",&genEnergy_singleLepCalc);
   outputTree->Branch("genStatus_singleLepCalc",&genStatus_singleLepCalc);
   outputTree->Branch("genID_singleLepCalc",&genID_singleLepCalc);
   outputTree->Branch("genJetPt_singleLepCalc",&genJetPt_singleLepCalc);                  
   outputTree->Branch("genJetEta_singleLepCalc",&genJetEta_singleLepCalc);                     
   outputTree->Branch("genJetPhi_singleLepCalc",&genJetPhi_singleLepCalc);                  
   outputTree->Branch("genJetEnergy_singleLepCalc",&genJetEnergy_singleLepCalc);                  
      

   outputTree->Branch("topEnergy_TTbarMassCalc",&topEnergy_TTbarMassCalc);
   outputTree->Branch("topEta_TTbarMassCalc",&topEta_TTbarMassCalc);
   outputTree->Branch("topMass_TTbarMassCalc",&topMass_TTbarMassCalc);
   outputTree->Branch("topPhi_TTbarMassCalc",&topPhi_TTbarMassCalc);   
   outputTree->Branch("topPt_TTbarMassCalc",&topPt_TTbarMassCalc);      
   outputTree->Branch("topID_TTbarMassCalc",&topID_TTbarMassCalc);         

   outputTree->Branch("topWEnergy_TTbarMassCalc",&topWEnergy_TTbarMassCalc);
   outputTree->Branch("topWEta_TTbarMassCalc",&topWEta_TTbarMassCalc);
   outputTree->Branch("topWPhi_TTbarMassCalc",&topWPhi_TTbarMassCalc);
   outputTree->Branch("topWPt_TTbarMassCalc",&topWPt_TTbarMassCalc);   
   outputTree->Branch("topWID_TTbarMassCalc",&topWID_TTbarMassCalc);      

   outputTree->Branch("topbEnergy_TTbarMassCalc",&topbEnergy_TTbarMassCalc);
   outputTree->Branch("topbEta_TTbarMassCalc",&topbEta_TTbarMassCalc);
   outputTree->Branch("topbPhi_TTbarMassCalc",&topbPhi_TTbarMassCalc);
   outputTree->Branch("topbPt_TTbarMassCalc",&topbPt_TTbarMassCalc);   
   outputTree->Branch("topbID_TTbarMassCalc",&topbID_TTbarMassCalc);      


  // ----------------------------------------------------------------------------
  // Define and initialize objects / cuts / efficiencies
  // ----------------------------------------------------------------------------

   // basic cuts
   float metCut=20;
   float htCut=0;
   float lepPtCut=25;
   float elEtaCut=2.1;
   float muEtaCut=2.1;
   float jetEtaCut=2.4;
   float ak8EtaCut=2.4;
   float jetPtCut=30;
   int njetsCut=4;

   // counters
   int npass_trigger = 0;
   int npass_met     = 0;
   int npass_ht      = 0;
   int npass_Njets   = 0;
   int npass_lepPt   = 0;
   int npass_ElEta   = 0;
   int npass_MuEta   = 0;
   int npass_all     = 0;
   int Nelectrons    = 0;
   int Nmuons        = 0;

   // Lorentz vectors
   TLorentzVector jet_lv;
   TLorentzVector bjet_lv;
   TLorentzVector wjet1_lv;
   TLorentzVector tjet1_lv;
   TLorentzVector lepton_lv;
   TLorentzVector ak8_lv;

   // W tagging efficiencies. Assumes each signal mass uses the same pT bins but has unique values.
   std::vector<float> ptRangeTpTp, ptRangeTTbar;
   float ptminTTbar[12] = {175,200,250,300,350,400,450,500,550,600,700,800};
   for (int i=0;i<12;++i) ptRangeTTbar.push_back(ptminTTbar[i]);
   float ptminTpTp[14] = {175,200,250,300,350,400,450,500,550,600,700,800,1000,1200};
   for (int i=0;i<14;++i) ptRangeTpTp.push_back(ptminTpTp[i]);

   std::vector<std::vector<float>> SignalEff;
   std::vector<std::vector<float>> SignalEffPuppi;
   if(isTpTp){
     SignalEffPuppi = {//TpTp
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//700
       {0.626, 0.911, 0.936, 0.930, 0.925, 0.920, 0.914, 0.915, 0.909, 0.907, 0.898, 0.890, 0.878, 0.866},
       {0.622, 0.914, 0.940, 0.932, 0.925, 0.919, 0.914, 0.907, 0.908, 0.905, 0.899, 0.888, 0.878, 0.859},
       {0.619, 0.914, 0.938, 0.930, 0.927, 0.920, 0.918, 0.914, 0.908, 0.899, 0.900, 0.888, 0.884, 0.862},
       {0.618, 0.911, 0.937, 0.930, 0.925, 0.920, 0.918, 0.918, 0.910, 0.906, 0.899, 0.886, 0.872, 0.877},
       {0.637, 0.911, 0.943, 0.931, 0.922, 0.920, 0.918, 0.912, 0.906, 0.905, 0.898, 0.892, 0.877, 0.868},
       {0.621, 0.909, 0.938, 0.930, 0.927, 0.923, 0.916, 0.912, 0.912, 0.904, 0.901, 0.891, 0.881, 0.873},
       {0.641, 0.918, 0.935, 0.937, 0.924, 0.926, 0.917, 0.916, 0.914, 0.908, 0.903, 0.892, 0.884, 0.872},
       {0.606, 0.917, 0.940, 0.936, 0.925, 0.925, 0.916, 0.915, 0.911, 0.910, 0.903, 0.895, 0.883, 0.876},
       {0.650, 0.920, 0.935, 0.932, 0.929, 0.919, 0.918, 0.912, 0.911, 0.908, 0.900, 0.896, 0.887, 0.876},
       {0.615, 0.915, 0.940, 0.934, 0.925, 0.921, 0.918, 0.912, 0.909, 0.910, 0.902, 0.895, 0.887, 0.872},
       {0.627, 0.915, 0.938, 0.934, 0.929, 0.916, 0.912, 0.912, 0.911, 0.906, 0.901, 0.898, 0.887, 0.879},
     };
     SignalEff = {
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//700
       {0.491, 0.892, 0.935, 0.926, 0.915, 0.908, 0.899, 0.902, 0.893, 0.889, 0.873, 0.866, 0.839, 0.831},
       {0.484, 0.894, 0.937, 0.927, 0.915, 0.907, 0.902, 0.891, 0.892, 0.885, 0.877, 0.864, 0.839, 0.823},
       {0.490, 0.893, 0.936, 0.923, 0.918, 0.909, 0.904, 0.897, 0.887, 0.885, 0.882, 0.864, 0.854, 0.821},
       {0.463, 0.888, 0.936, 0.924, 0.916, 0.909, 0.908, 0.901, 0.895, 0.887, 0.875, 0.862, 0.841, 0.834},
       {0.491, 0.891, 0.937, 0.925, 0.914, 0.911, 0.903, 0.897, 0.889, 0.888, 0.876, 0.865, 0.846, 0.830},
       {0.481, 0.885, 0.932, 0.925, 0.915, 0.908, 0.903, 0.899, 0.893, 0.886, 0.879, 0.864, 0.852, 0.834},
       {0.489, 0.892, 0.933, 0.924, 0.914, 0.912, 0.907, 0.900, 0.897, 0.888, 0.879, 0.864, 0.849, 0.835},
       {0.468, 0.888, 0.928, 0.930, 0.917, 0.910, 0.901, 0.898, 0.894, 0.888, 0.879, 0.869, 0.851, 0.837},
       {0.487, 0.893, 0.930, 0.922, 0.915, 0.902, 0.901, 0.894, 0.894, 0.886, 0.877, 0.869, 0.853, 0.836},
       {0.461, 0.887, 0.931, 0.921, 0.910, 0.906, 0.900, 0.896, 0.891, 0.889, 0.878, 0.867, 0.854, 0.833},
       {0.461, 0.893, 0.929, 0.927, 0.912, 0.901, 0.895, 0.888, 0.892, 0.886, 0.877, 0.869, 0.851, 0.839},
     };
   }else if(isBpBp){
     SignalEffPuppi = {//BpBp
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//700
       {0.616, 0.919, 0.940, 0.933, 0.933, 0.924, 0.915, 0.915, 0.909, 0.903, 0.892, 0.871, 0.831, 0.795},
       {0.604, 0.919, 0.944, 0.937, 0.928, 0.926, 0.921, 0.916, 0.912, 0.909, 0.894, 0.876, 0.858, 0.830},
       {0.633, 0.915, 0.944, 0.935, 0.932, 0.930, 0.919, 0.917, 0.912, 0.905, 0.902, 0.890, 0.863, 0.839},
       {0.619, 0.918, 0.944, 0.938, 0.933, 0.927, 0.926, 0.919, 0.916, 0.909, 0.899, 0.893, 0.869, 0.856},
       {0.600, 0.914, 0.943, 0.937, 0.932, 0.927, 0.925, 0.918, 0.917, 0.914, 0.906, 0.892, 0.880, 0.857},
       {0.613, 0.912, 0.943, 0.940, 0.934, 0.925, 0.923, 0.920, 0.918, 0.914, 0.909, 0.897, 0.888, 0.864},
       {0.610, 0.919, 0.944, 0.938, 0.933, 0.927, 0.927, 0.921, 0.920, 0.913, 0.908, 0.900, 0.882, 0.873},
       {0.626, 0.911, 0.959, 0.935, 0.936, 0.929, 0.927, 0.922, 0.915, 0.911, 0.903, 0.902, 0.882, 0.870},
       {0.619, 0.925, 0.943, 0.941, 0.936, 0.927, 0.927, 0.920, 0.920, 0.914, 0.909, 0.900, 0.890, 0.880},
       {0.653, 0.924, 0.945, 0.934, 0.932, 0.934, 0.925, 0.923, 0.918, 0.912, 0.911, 0.901, 0.889, 0.877},
       {0.629, 0.924, 0.944, 0.945, 0.928, 0.929, 0.924, 0.923, 0.918, 0.915, 0.911, 0.902, 0.888, 0.886},
     };
     SignalEff = {
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//700
       {0.481, 0.894, 0.938, 0.927, 0.921, 0.914, 0.901, 0.900, 0.890, 0.885, 0.870, 0.846, 0.785, 0.789},
       {0.470, 0.896, 0.940, 0.930, 0.917, 0.913, 0.904, 0.900, 0.896, 0.887, 0.874, 0.848, 0.823, 0.783},
       {0.500, 0.898, 0.940, 0.927, 0.921, 0.917, 0.906, 0.900, 0.894, 0.885, 0.882, 0.863, 0.836, 0.789},
       {0.464, 0.888, 0.937, 0.929, 0.919, 0.912, 0.913, 0.904, 0.898, 0.890, 0.880, 0.864, 0.834, 0.819},
       {0.456, 0.886, 0.942, 0.927, 0.922, 0.912, 0.909, 0.906, 0.896, 0.894, 0.883, 0.866, 0.848, 0.810},
       {0.472, 0.891, 0.937, 0.929, 0.923, 0.913, 0.911, 0.903, 0.900, 0.894, 0.886, 0.869, 0.853, 0.822},
       {0.467, 0.892, 0.940, 0.928, 0.918, 0.911, 0.911, 0.908, 0.903, 0.893, 0.885, 0.874, 0.850, 0.834},
       {0.476, 0.880, 0.941, 0.923, 0.918, 0.912, 0.903, 0.906, 0.895, 0.889, 0.881, 0.871, 0.846, 0.834},
       {0.472, 0.892, 0.936, 0.924, 0.917, 0.910, 0.908, 0.904, 0.898, 0.892, 0.885, 0.874, 0.858, 0.839},
       {0.473, 0.889, 0.939, 0.926, 0.917, 0.911, 0.908, 0.899, 0.900, 0.891, 0.887, 0.875, 0.860, 0.835},
       {0.471, 0.888, 0.939, 0.929, 0.914, 0.914, 0.902, 0.899, 0.900, 0.894, 0.886, 0.873, 0.854, 0.846},
     };
   }else if(isXX){
     SignalEffPuppi = {
       {0.619, 0.915, 0.940, 0.936, 0.931, 0.928, 0.926, 0.916, 0.914, 0.906, 0.890, 0.864, 0.816, 0.772},
       {0.629, 0.920, 0.946, 0.939, 0.932, 0.931, 0.927, 0.925, 0.918, 0.914, 0.899, 0.878, 0.868, 0.833},
       {0.629, 0.917, 0.945, 0.939, 0.937, 0.933, 0.929, 0.924, 0.915, 0.916, 0.905, 0.889, 0.869, 0.839},
       {0.626, 0.919, 0.943, 0.939, 0.935, 0.935, 0.930, 0.927, 0.926, 0.917, 0.915, 0.899, 0.883, 0.869},
       {0.638, 0.919, 0.945, 0.940, 0.936, 0.936, 0.932, 0.928, 0.923, 0.922, 0.913, 0.904, 0.890, 0.870},
       {0.619, 0.916, 0.946, 0.939, 0.937, 0.934, 0.935, 0.931, 0.927, 0.920, 0.916, 0.905, 0.900, 0.872},
       {0.619, 0.915, 0.948, 0.943, 0.938, 0.932, 0.935, 0.931, 0.927, 0.923, 0.917, 0.907, 0.895, 0.872},
       {0.625, 0.920, 0.944, 0.941, 0.939, 0.937, 0.932, 0.933, 0.927, 0.925, 0.918, 0.909, 0.897, 0.884},
       {0.653, 0.922, 0.950, 0.942, 0.936, 0.936, 0.933, 0.932, 0.929, 0.925, 0.919, 0.914, 0.897, 0.883},
       {0.651, 0.924, 0.944, 0.939, 0.937, 0.935, 0.934, 0.930, 0.928, 0.927, 0.920, 0.913, 0.899, 0.890},
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//1700
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//1800
     };     
     SignalEff = {//X53X53
       {0.496, 0.895, 0.942, 0.933, 0.926, 0.922, 0.916, 0.908, 0.900, 0.889, 0.874, 0.844, 0.802, 0.759},
       {0.498, 0.900, 0.945, 0.936, 0.928, 0.927, 0.919, 0.917, 0.905, 0.902, 0.883, 0.860, 0.845, 0.790},
       {0.498, 0.896, 0.945, 0.936, 0.929, 0.927, 0.919, 0.916, 0.906, 0.903, 0.890, 0.868, 0.845, 0.792},
       {0.491, 0.893, 0.944, 0.936, 0.932, 0.927, 0.922, 0.918, 0.916, 0.903, 0.897, 0.883, 0.854, 0.831},
       {0.488, 0.893, 0.943, 0.936, 0.930, 0.930, 0.924, 0.919, 0.915, 0.911, 0.900, 0.886, 0.864, 0.832},
       {0.461, 0.890, 0.943, 0.935, 0.928, 0.926, 0.924, 0.918, 0.914, 0.906, 0.899, 0.884, 0.871, 0.840},
       {0.480, 0.893, 0.939, 0.940, 0.928, 0.927, 0.923, 0.921, 0.914, 0.910, 0.899, 0.888, 0.869, 0.841},
       {0.475, 0.897, 0.939, 0.935, 0.928, 0.927, 0.922, 0.920, 0.914, 0.912, 0.902, 0.891, 0.873, 0.850},
       {0.510, 0.894, 0.943, 0.936, 0.927, 0.928, 0.919, 0.922, 0.914, 0.909, 0.903, 0.894, 0.870, 0.851},
       {0.479, 0.899, 0.939, 0.931, 0.925, 0.925, 0.922, 0.917, 0.918, 0.911, 0.900, 0.891, 0.873, 0.858},
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//1700
       {1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000},//1800
     };
   }
   float TTbarEff[12] = {0.468, 0.882, 0.941, 0.928, 0.915, 0.903, 0.892, 0.878, 0.868, 0.853, 0.828, 0.796};
   float STtEff[12] = {0.437, 0.876, 0.941, 0.927, 0.914, 0.900, 0.890, 0.855, 0.864, 0.842, 0.827, 0.849};
   float STtWEff[12] = {0.453, 0.885, 0.948, 0.938, 0.930, 0.927, 0.921, 0.916, 0.920, 0.910, 0.895, 0.875};
   float WVEff[12] = {0.440, 0.882, 0.945, 0.937, 0.924, 0.926, 0.909, 0.913, 0.892, 0.902, 0.881, 0.870};

   float STtEffPuppi[12] = {0.520, 0.901, 0.946, 0.933, 0.923, 0.906, 0.889, 0.869, 0.882, 0.855, 0.841, 0.875};
   float STtWEffPuppi[12] = {0.543, 0.909, 0.952, 0.945, 0.940, 0.938, 0.932, 0.929, 0.933, 0.924, 0.916, 0.900};
   float TTbarEffPuppi[12] = {0.562, 0.905, 0.944, 0.934, 0.923, 0.912, 0.899, 0.888, 0.883, 0.872, 0.841, 0.816};
   float WVEffPuppi[12] = {0.527, 0.909, 0.954, 0.946, 0.939, 0.939, 0.922, 0.929, 0.910, 0.928, 0.901, 0.914};

   // Top tagging efficiencies
   std::vector<float> ptRangeTpTpTop, ptRangeTTbarTop;
   float ptminTTbarTop[9] = {400,450,500,550,600,700,800,1000,1200};
   for (int i=0;i<9;++i) ptRangeTTbarTop.push_back(ptminTTbarTop[i]);
   float ptminTpTpTop[9] = {400,450,500,550,600,700,800,1000,1200};//X53X53
   for (int i=0;i<9;++i) ptRangeTpTpTop.push_back(ptminTpTpTop[i]);
   float TTbarEffTop[9] = {0.710731908673,0.911246812099,0.946258231276,0.950948087531,0.952308954524,0.947643078335,0.94133549608,0.929334428924,0.924661246612};
   float STEffTop[9] = {0.691643703728,0.906228313671,0.941468696261,0.948002294016,0.947021636542,0.941775836972,0.933049300061,0.936046511628,0.933862433862};

   float SignalEffTop[10][9] = {//X53X53
     {0.724620303757,0.899211846191,0.936291859515,0.944579091937,0.94692371772,0.945789586458,0.935492651062,0.913173652695,0.90977443609},
     {0.720768101761,0.907892004154,0.937210055022,0.945094294581,0.944494920294,0.941136208077,0.93661971831,0.924356223176,0.930051813472},
     {0.724299065421,0.904784643301,0.937938576506,0.940539456533,0.944067043362,0.943750614613,0.939160329201,0.925230671333,0.920143884892},
     {0.723555888972,0.891038887845,0.93702487906,0.943868050013,0.9433296466,0.941325202647,0.933387610095,0.930462184874,0.920435510888},
     {0.706017891027,0.891839315242,0.929181103693,0.945251210149,0.946220930233,0.943065231159,0.936117240989,0.930840845279,0.918595371109},
     {0.706572416905,0.885974797664,0.923103809857,0.938941876579,0.943281477238,0.942451135188,0.935289623871,0.926310160428,0.918116871222},
     {0.703368526898,0.873433303491,0.920978890342,0.936481121716,0.942840429532,0.941648216482,0.935452396142,0.926339285714,0.913049112349},
     {0.687741686002,0.876234529316,0.917185109638,0.93502800517,0.93907257226,0.941280976676,0.929876038507,0.923884514436,0.91489965922},
     {0.675073181716,0.87130710477,0.909954158481,0.928911723494,0.937305146274,0.940579646213,0.932647997164,0.921526157947,0.91551008728},
     {0.679444301518,0.863857374392,0.909068746953,0.920785999386,0.932639746077,0.937310063385,0.933625327818,0.923361250175,0.914409413854}
     };
 
   // Pileup distributions -- 31Mar2018 Data vs RunIIFall17MC
   std::vector<std::vector<float>> pileupweight;
   std::vector<std::vector<float>> pileupweightUp;
   std::vector<std::vector<float>> pileupweightDn;
//    pileupweight = {
//      {2.627E-04, 2.950E-02, 3.845E-02, 6.129E-02, 7.067E-02, 1.038E-01, 1.276E-01, 1.488E-01, 1.050E-01, 3.197E-01, 4.811E-01, 6.165E-01, 6.699E-01, 7.030E-01, 7.332E-01, 7.987E-01, 8.958E-01, 9.917E-01, 1.083E+00, 1.145E+00, 1.204E+00, 1.252E+00, 1.292E+00, 1.325E+00, 1.342E+00, 1.346E+00, 1.351E+00, 1.358E+00, 1.368E+00, 1.355E+00, 1.323E+00, 1.260E+00, 1.197E+00, 1.133E+00, 1.057E+00, 9.937E-01, 9.487E-01, 9.072E-01, 8.591E-01, 8.169E-01, 8.251E-01, 8.610E-01, 9.336E-01, 1.047E+00, 1.193E+00, 1.356E+00, 1.538E+00, 1.612E+00, 1.625E+00, 1.577E+00, 1.402E+00, 1.210E+00, 1.006E+00, 7.882E-01, 5.993E-01, 4.287E-01, 3.047E-01, 2.107E-01, 1.456E-01, 1.024E-01, 7.315E-02, 5.335E-02, 4.065E-02, 3.040E-02, 2.403E-02, 1.784E-02, 1.262E-02, 1.095E-02, 9.353E-03, 8.596E-03, 7.320E-03, 6.155E-03, 6.241E-03, 4.710E-03, 3.440E-03, 2.819E-03, 2.363E-03, 1.809E-03, 1.251E-03, 4.036E-04},
//      {3.544E-04, 3.998E-02, 4.526E-02, 7.801E-02, 9.146E-02, 1.097E-01, 1.527E-01, 2.427E-01, 1.278E-01, 4.256E-01, 5.532E-01, 6.663E-01, 6.732E-01, 7.100E-01, 7.715E-01, 8.042E-01, 9.015E-01, 9.917E-01, 1.066E+00, 1.131E+00, 1.189E+00, 1.253E+00, 1.282E+00, 1.315E+00, 1.325E+00, 1.339E+00, 1.339E+00, 1.339E+00, 1.362E+00, 1.336E+00, 1.297E+00, 1.239E+00, 1.190E+00, 1.117E+00, 1.039E+00, 9.847E-01, 9.359E-01, 8.988E-01, 8.460E-01, 8.122E-01, 8.128E-01, 8.503E-01, 9.144E-01, 1.020E+00, 1.173E+00, 1.348E+00, 1.525E+00, 1.596E+00, 1.638E+00, 1.565E+00, 1.346E+00, 1.213E+00, 9.796E-01, 7.891E-01, 5.957E-01, 4.270E-01, 3.022E-01, 2.079E-01, 1.453E-01, 1.013E-01, 7.242E-02, 5.264E-02, 4.040E-02, 3.102E-02, 2.399E-02, 1.754E-02, 1.216E-02, 1.027E-02, 9.501E-03, 8.830E-03, 7.677E-03, 5.254E-03, 6.172E-03, 5.941E-03, 3.630E-03, 4.188E-03, 2.190E-03, 1.532E-03, 1.240E-03, 5.375E-04},
//      {1.749E-01, 4.172E+00, 3.462E+00, 2.677E+00, 1.657E+00, 1.475E+00, 1.255E+00, 1.247E+00, 6.000E-01, 1.423E+00, 1.498E+00, 1.492E+00, 1.325E+00, 1.164E+00, 1.082E+00, 1.052E+00, 1.083E+00, 1.127E+00, 1.163E+00, 1.191E+00, 1.212E+00, 1.241E+00, 1.255E+00, 1.270E+00, 1.274E+00, 1.273E+00, 1.272E+00, 1.268E+00, 1.278E+00, 1.250E+00, 1.223E+00, 1.171E+00, 1.111E+00, 1.036E+00, 9.706E-01, 9.104E-01, 8.681E-01, 8.332E-01, 7.862E-01, 7.510E-01, 7.602E-01, 7.926E-01, 8.584E-01, 9.577E-01, 1.096E+00, 1.256E+00, 1.416E+00, 1.494E+00, 1.526E+00, 1.468E+00, 1.336E+00, 1.152E+00, 9.528E-01, 7.484E-01, 5.701E-01, 4.122E-01, 2.880E-01, 1.984E-01, 1.374E-01, 9.694E-02, 6.917E-02, 5.072E-02, 3.857E-02, 2.990E-02, 2.407E-02, 1.711E-02, 1.255E-02, 1.081E-02, 9.624E-03, 8.906E-03, 8.153E-03, 8.132E-03, 7.845E-03, 7.748E-03, 6.232E-03, 5.267E-03, 5.608E-03, 6.070E-03, 6.121E-03, 6.164E-03},
//      {1.672E-01, 4.002E+00, 3.617E+00, 2.548E+00, 1.509E+00, 1.493E+00, 1.296E+00, 1.240E+00, 6.044E-01, 1.455E+00, 1.498E+00, 1.488E+00, 1.340E+00, 1.174E+00, 1.086E+00, 1.052E+00, 1.083E+00, 1.128E+00, 1.168E+00, 1.181E+00, 1.205E+00, 1.236E+00, 1.259E+00, 1.272E+00, 1.271E+00, 1.272E+00, 1.271E+00, 1.267E+00, 1.278E+00, 1.251E+00, 1.219E+00, 1.164E+00, 1.109E+00, 1.038E+00, 9.689E-01, 9.156E-01, 8.645E-01, 8.359E-01, 7.875E-01, 7.518E-01, 7.621E-01, 7.939E-01, 8.594E-01, 9.634E-01, 1.096E+00, 1.255E+00, 1.424E+00, 1.511E+00, 1.535E+00, 1.457E+00, 1.342E+00, 1.153E+00, 9.464E-01, 7.538E-01, 5.673E-01, 4.094E-01, 2.882E-01, 1.995E-01, 1.377E-01, 9.630E-02, 6.899E-02, 5.090E-02, 3.856E-02, 2.996E-02, 2.428E-02, 1.692E-02, 1.250E-02, 1.081E-02, 9.817E-03, 8.680E-03, 8.324E-03, 8.295E-03, 7.672E-03, 7.872E-03, 6.039E-03, 5.129E-03, 5.624E-03, 5.494E-03, 6.660E-03, 5.473E-03},
//      {2.758E-04, 2.979E-02, 4.481E-02, 7.384E-02, 6.863E-02, 1.116E-01, 1.301E-01, 1.552E-01, 1.058E-01, 3.333E-01, 5.015E-01, 6.410E-01, 6.712E-01, 7.089E-01, 7.387E-01, 8.027E-01, 9.054E-01, 9.982E-01, 1.086E+00, 1.149E+00, 1.200E+00, 1.257E+00, 1.302E+00, 1.324E+00, 1.342E+00, 1.344E+00, 1.353E+00, 1.352E+00, 1.366E+00, 1.349E+00, 1.320E+00, 1.250E+00, 1.194E+00, 1.130E+00, 1.055E+00, 9.941E-01, 9.461E-01, 9.058E-01, 8.535E-01, 8.164E-01, 8.234E-01, 8.614E-01, 9.270E-01, 1.046E+00, 1.190E+00, 1.357E+00, 1.530E+00, 1.580E+00, 1.623E+00, 1.552E+00, 1.396E+00, 1.203E+00, 9.963E-01, 7.804E-01, 5.990E-01, 4.260E-01, 3.034E-01, 2.091E-01, 1.455E-01, 1.023E-01, 7.260E-02, 5.320E-02, 4.007E-02, 3.055E-02, 2.303E-02, 1.753E-02, 1.254E-02, 1.085E-02, 8.972E-03, 8.785E-03, 7.276E-03, 6.235E-03, 5.168E-03, 6.401E-03, 3.540E-03, 3.876E-03, 2.529E-03, 1.391E-03, 1.006E-03, 5.000E-04},
//      {2.494E-04, 3.158E-02, 3.862E-02, 5.765E-02, 7.191E-02, 1.117E-01, 1.001E-01, 1.299E-01, 1.084E-01, 3.222E-01, 4.813E-01, 6.202E-01, 6.505E-01, 7.113E-01, 7.297E-01, 7.877E-01, 9.025E-01, 1.013E+00, 1.094E+00, 1.148E+00, 1.211E+00, 1.252E+00, 1.304E+00, 1.336E+00, 1.347E+00, 1.356E+00, 1.354E+00, 1.365E+00, 1.369E+00, 1.351E+00, 1.328E+00, 1.258E+00, 1.202E+00, 1.130E+00, 1.059E+00, 9.882E-01, 9.494E-01, 9.124E-01, 8.601E-01, 8.192E-01, 8.230E-01, 8.637E-01, 9.387E-01, 1.048E+00, 1.188E+00, 1.354E+00, 1.540E+00, 1.616E+00, 1.634E+00, 1.572E+00, 1.388E+00, 1.224E+00, 1.001E+00, 7.875E-01, 5.981E-01, 4.347E-01, 3.054E-01, 2.086E-01, 1.461E-01, 1.012E-01, 7.329E-02, 5.338E-02, 4.046E-02, 3.013E-02, 2.390E-02, 1.758E-02, 1.241E-02, 1.099E-02, 9.904E-03, 8.385E-03, 7.029E-03, 5.092E-03, 5.896E-03, 4.427E-03, 3.156E-03, 3.957E-03, 2.318E-03, 2.368E-03, 1.121E-03, 5.284E-04},
//      {2.960E-04, 4.661E-02, 5.142E-02, 7.836E-02, 7.650E-02, 1.158E-01, 1.384E-01, 1.598E-01, 1.298E-01, 4.088E-01, 5.108E-01, 6.759E-01, 7.111E-01, 7.069E-01, 7.569E-01, 8.221E-01, 9.024E-01, 9.951E-01, 1.083E+00, 1.143E+00, 1.196E+00, 1.243E+00, 1.290E+00, 1.319E+00, 1.335E+00, 1.333E+00, 1.349E+00, 1.351E+00, 1.349E+00, 1.339E+00, 1.312E+00, 1.253E+00, 1.187E+00, 1.126E+00, 1.046E+00, 9.803E-01, 9.405E-01, 9.074E-01, 8.515E-01, 8.155E-01, 8.172E-01, 8.621E-01, 9.268E-01, 1.040E+00, 1.184E+00, 1.351E+00, 1.528E+00, 1.601E+00, 1.645E+00, 1.555E+00, 1.395E+00, 1.202E+00, 1.009E+00, 7.834E-01, 5.907E-01, 4.264E-01, 3.005E-01, 2.080E-01, 1.442E-01, 1.016E-01, 7.377E-02, 5.274E-02, 4.028E-02, 2.943E-02, 2.345E-02, 1.733E-02, 1.304E-02, 1.089E-02, 9.218E-03, 8.375E-03, 7.196E-03, 4.961E-03, 5.212E-03, 4.817E-03, 2.602E-03, 3.627E-03, 2.491E-03, 2.361E-03, 6.611E-04, 6.415E-04},
//      {2.894E-04, 4.360E-02, 5.014E-02, 6.912E-02, 8.141E-02, 1.445E-01, 1.405E-01, 1.480E-01, 1.039E-01, 3.417E-01, 4.570E-01, 6.214E-01, 6.927E-01, 6.701E-01, 6.820E-01, 8.060E-01, 8.304E-01, 9.961E-01, 1.076E+00, 1.131E+00, 1.193E+00, 1.219E+00, 1.294E+00, 1.326E+00, 1.323E+00, 1.350E+00, 1.362E+00, 1.348E+00, 1.360E+00, 1.339E+00, 1.311E+00, 1.262E+00, 1.185E+00, 1.131E+00, 1.058E+00, 1.002E+00, 9.544E-01, 9.065E-01, 8.609E-01, 8.214E-01, 8.346E-01, 8.601E-01, 9.398E-01, 1.059E+00, 1.200E+00, 1.364E+00, 1.510E+00, 1.641E+00, 1.590E+00, 1.542E+00, 1.397E+00, 1.237E+00, 1.003E+00, 8.001E-01, 5.921E-01, 4.271E-01, 3.083E-01, 2.139E-01, 1.458E-01, 1.017E-01, 7.216E-02, 5.370E-02, 4.107E-02, 3.045E-02, 2.474E-02, 1.765E-02, 1.298E-02, 1.070E-02, 9.453E-03, 9.417E-03, 7.668E-03, 4.481E-03, 3.087E-03, 6.682E-03, 3.068E-03, 1.882E-03, 1.948E-03, 5.821E-03, 1.565E-03, 3.780E-04},
//      {1.800E-01, 3.572E+00, 3.238E+00, 2.501E+00, 1.587E+00, 1.524E+00, 1.259E+00, 1.234E+00, 6.249E-01, 1.469E+00, 1.489E+00, 1.493E+00, 1.332E+00, 1.168E+00, 1.077E+00, 1.050E+00, 1.085E+00, 1.129E+00, 1.164E+00, 1.190E+00, 1.213E+00, 1.238E+00, 1.258E+00, 1.270E+00, 1.275E+00, 1.274E+00, 1.272E+00, 1.267E+00, 1.276E+00, 1.252E+00, 1.223E+00, 1.169E+00, 1.110E+00, 1.035E+00, 9.696E-01, 9.107E-01, 8.679E-01, 8.329E-01, 7.873E-01, 7.513E-01, 7.580E-01, 7.947E-01, 8.584E-01, 9.582E-01, 1.093E+00, 1.255E+00, 1.420E+00, 1.496E+00, 1.525E+00, 1.468E+00, 1.336E+00, 1.156E+00, 9.496E-01, 7.491E-01, 5.688E-01, 4.106E-01, 2.897E-01, 1.987E-01, 1.380E-01, 9.650E-02, 6.927E-02, 5.094E-02, 3.836E-02, 2.994E-02, 2.412E-02, 1.694E-02, 1.244E-02, 1.079E-02, 9.658E-03, 8.864E-03, 8.303E-03, 8.066E-03, 7.846E-03, 7.957E-03, 6.113E-03, 5.381E-03, 5.472E-03, 5.358E-03, 5.970E-03, 6.237E-03},
//      {2.605E-04, 2.631E-02, 3.681E-02, 4.785E-02, 7.677E-02, 1.316E-01, 9.301E-02, 1.018E-01, 1.079E-01, 4.031E-01, 4.383E-01, 6.138E-01, 6.870E-01, 7.113E-01, 7.262E-01, 8.072E-01, 8.834E-01, 9.917E-01, 1.070E+00, 1.134E+00, 1.185E+00, 1.256E+00, 1.307E+00, 1.338E+00, 1.329E+00, 1.353E+00, 1.370E+00, 1.381E+00, 1.371E+00, 1.359E+00, 1.336E+00, 1.252E+00, 1.208E+00, 1.133E+00, 1.066E+00, 9.925E-01, 9.398E-01, 9.187E-01, 8.526E-01, 8.198E-01, 8.374E-01, 8.628E-01, 9.381E-01, 1.055E+00, 1.208E+00, 1.350E+00, 1.567E+00, 1.627E+00, 1.624E+00, 1.558E+00, 1.401E+00, 1.214E+00, 1.002E+00, 7.880E-01, 5.921E-01, 4.393E-01, 3.076E-01, 2.087E-01, 1.429E-01, 1.036E-01, 7.355E-02, 5.130E-02, 3.955E-02, 3.146E-02, 2.366E-02, 1.726E-02, 1.258E-02, 1.092E-02, 1.015E-02, 9.365E-03, 6.013E-03, 3.590E-03, 4.496E-03, 4.837E-03, 6.140E-03, 4.341E-03, 1.343E-03, 4.228E-03, 5.226E-04, 7.545E-04},
//      {2.607E-04, 2.222E-02, 4.369E-02, 5.655E-02, 7.639E-02, 9.580E-02, 1.022E-01, 1.921E-01, 1.312E-01, 3.306E-01, 5.204E-01, 6.816E-01, 6.607E-01, 6.635E-01, 7.260E-01, 7.893E-01, 9.209E-01, 1.004E+00, 1.098E+00, 1.158E+00, 1.206E+00, 1.268E+00, 1.289E+00, 1.328E+00, 1.341E+00, 1.340E+00, 1.358E+00, 1.349E+00, 1.383E+00, 1.356E+00, 1.331E+00, 1.242E+00, 1.211E+00, 1.133E+00, 1.049E+00, 9.995E-01, 9.512E-01, 9.076E-01, 8.579E-01, 8.202E-01, 8.377E-01, 8.753E-01, 9.439E-01, 1.041E+00, 1.193E+00, 1.341E+00, 1.525E+00, 1.574E+00, 1.593E+00, 1.569E+00, 1.366E+00, 1.206E+00, 1.021E+00, 7.956E-01, 6.034E-01, 4.278E-01, 3.102E-01, 2.086E-01, 1.461E-01, 1.031E-01, 7.383E-02, 5.028E-02, 4.112E-02, 3.090E-02, 2.154E-02, 1.732E-02, 1.306E-02, 1.068E-02, 9.153E-03, 8.133E-03, 6.713E-03, 5.319E-03, 3.989E-03, 8.444E-03, 1.941E-03, 4.946E-03, 2.976E-03, 3.784E-03, 5.910E-04, 2.521E-04},
//      {1.780E-01, 5.124E+00, 3.340E+00, 2.752E+00, 1.532E+00, 1.502E+00, 1.283E+00, 1.247E+00, 6.408E-01, 1.423E+00, 1.493E+00, 1.501E+00, 1.316E+00, 1.161E+00, 1.081E+00, 1.048E+00, 1.081E+00, 1.129E+00, 1.170E+00, 1.190E+00, 1.214E+00, 1.239E+00, 1.258E+00, 1.269E+00, 1.274E+00, 1.270E+00, 1.265E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.220E+00, 1.173E+00, 1.111E+00, 1.039E+00, 9.675E-01, 9.125E-01, 8.687E-01, 8.348E-01, 7.882E-01, 7.476E-01, 7.592E-01, 7.946E-01, 8.570E-01, 9.614E-01, 1.095E+00, 1.257E+00, 1.418E+00, 1.502E+00, 1.533E+00, 1.460E+00, 1.343E+00, 1.154E+00, 9.496E-01, 7.457E-01, 5.701E-01, 4.112E-01, 2.882E-01, 1.982E-01, 1.382E-01, 9.659E-02, 6.902E-02, 5.065E-02, 3.841E-02, 3.010E-02, 2.401E-02, 1.713E-02, 1.250E-02, 1.079E-02, 9.623E-03, 8.901E-03, 8.297E-03, 8.180E-03, 7.698E-03, 7.869E-03, 6.500E-03, 5.429E-03, 5.453E-03, 5.933E-03, 5.511E-03, 5.550E-03},
//      {1.829E-01, 3.581E+00, 3.653E+00, 2.510E+00, 1.605E+00, 1.528E+00, 1.253E+00, 1.264E+00, 6.156E-01, 1.469E+00, 1.500E+00, 1.473E+00, 1.340E+00, 1.166E+00, 1.074E+00, 1.057E+00, 1.075E+00, 1.127E+00, 1.169E+00, 1.188E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.272E+00, 1.272E+00, 1.272E+00, 1.270E+00, 1.266E+00, 1.275E+00, 1.250E+00, 1.224E+00, 1.167E+00, 1.110E+00, 1.039E+00, 9.682E-01, 9.119E-01, 8.667E-01, 8.359E-01, 7.903E-01, 7.499E-01, 7.578E-01, 7.936E-01, 8.595E-01, 9.557E-01, 1.098E+00, 1.254E+00, 1.419E+00, 1.500E+00, 1.529E+00, 1.462E+00, 1.339E+00, 1.152E+00, 9.470E-01, 7.516E-01, 5.683E-01, 4.100E-01, 2.894E-01, 1.993E-01, 1.372E-01, 9.685E-02, 6.914E-02, 5.076E-02, 3.851E-02, 2.990E-02, 2.414E-02, 1.714E-02, 1.249E-02, 1.084E-02, 9.637E-03, 8.826E-03, 8.251E-03, 7.945E-03, 7.913E-03, 7.839E-03, 6.205E-03, 5.395E-03, 5.376E-03, 5.855E-03, 5.805E-03, 5.727E-03},
//      {2.326E-04, 2.787E-02, 3.339E-02, 5.035E-02, 6.247E-02, 9.966E-02, 1.074E-01, 1.442E-01, 1.041E-01, 3.121E-01, 4.634E-01, 6.124E-01, 6.707E-01, 6.990E-01, 7.462E-01, 8.168E-01, 9.110E-01, 1.022E+00, 1.100E+00, 1.156E+00, 1.212E+00, 1.261E+00, 1.307E+00, 1.336E+00, 1.353E+00, 1.354E+00, 1.353E+00, 1.360E+00, 1.376E+00, 1.354E+00, 1.326E+00, 1.264E+00, 1.198E+00, 1.132E+00, 1.062E+00, 9.996E-01, 9.498E-01, 9.122E-01, 8.609E-01, 8.217E-01, 8.276E-01, 8.657E-01, 9.451E-01, 1.048E+00, 1.196E+00, 1.360E+00, 1.538E+00, 1.600E+00, 1.634E+00, 1.581E+00, 1.403E+00, 1.211E+00, 9.999E-01, 7.865E-01, 5.984E-01, 4.296E-01, 3.034E-01, 2.107E-01, 1.463E-01, 1.024E-01, 7.337E-02, 5.378E-02, 4.052E-02, 3.077E-02, 2.339E-02, 1.753E-02, 1.269E-02, 1.092E-02, 9.353E-03, 9.002E-03, 7.919E-03, 4.869E-03, 6.104E-03, 4.942E-03, 3.426E-03, 2.660E-03, 2.304E-03, 2.039E-03, 1.059E-03, 5.481E-04},
//      {2.328E-04, 3.090E-02, 4.163E-02, 4.817E-02, 5.984E-02, 9.593E-02, 1.055E-01, 1.605E-01, 1.151E-01, 3.110E-01, 4.780E-01, 6.027E-01, 6.617E-01, 6.884E-01, 7.227E-01, 7.992E-01, 8.973E-01, 1.001E+00, 1.085E+00, 1.149E+00, 1.217E+00, 1.260E+00, 1.303E+00, 1.342E+00, 1.352E+00, 1.359E+00, 1.367E+00, 1.366E+00, 1.386E+00, 1.359E+00, 1.335E+00, 1.267E+00, 1.203E+00, 1.130E+00, 1.060E+00, 9.983E-01, 9.556E-01, 9.185E-01, 8.634E-01, 8.242E-01, 8.302E-01, 8.673E-01, 9.375E-01, 1.051E+00, 1.194E+00, 1.359E+00, 1.540E+00, 1.593E+00, 1.626E+00, 1.570E+00, 1.398E+00, 1.220E+00, 9.918E-01, 7.834E-01, 5.988E-01, 4.256E-01, 3.069E-01, 2.102E-01, 1.467E-01, 1.022E-01, 7.271E-02, 5.372E-02, 4.035E-02, 3.002E-02, 2.315E-02, 1.791E-02, 1.267E-02, 1.052E-02, 9.544E-03, 8.520E-03, 8.017E-03, 6.324E-03, 6.082E-03, 5.663E-03, 2.850E-03, 3.110E-03, 2.375E-03, 1.463E-03, 1.312E-03, 4.850E-04},
//      {2.564E-04, 3.837E-02, 3.059E-02, 5.322E-02, 6.786E-02, 9.388E-02, 1.256E-01, 1.484E-01, 1.033E-01, 3.382E-01, 4.688E-01, 6.103E-01, 6.883E-01, 6.948E-01, 7.502E-01, 8.297E-01, 9.089E-01, 9.969E-01, 1.095E+00, 1.143E+00, 1.203E+00, 1.262E+00, 1.306E+00, 1.333E+00, 1.348E+00, 1.344E+00, 1.349E+00, 1.360E+00, 1.371E+00, 1.356E+00, 1.326E+00, 1.267E+00, 1.197E+00, 1.129E+00, 1.052E+00, 9.949E-01, 9.485E-01, 9.147E-01, 8.563E-01, 8.183E-01, 8.310E-01, 8.650E-01, 9.384E-01, 1.046E+00, 1.197E+00, 1.363E+00, 1.533E+00, 1.615E+00, 1.624E+00, 1.580E+00, 1.390E+00, 1.200E+00, 1.008E+00, 7.782E-01, 5.965E-01, 4.190E-01, 3.025E-01, 2.105E-01, 1.457E-01, 1.019E-01, 7.269E-02, 5.390E-02, 4.059E-02, 3.069E-02, 2.300E-02, 1.719E-02, 1.252E-02, 1.121E-02, 9.765E-03, 7.860E-03, 8.231E-03, 5.744E-03, 4.478E-03, 5.989E-03, 2.354E-03, 2.470E-03, 1.666E-03, 2.406E-03, 1.619E-03, 3.990E-04},
//      {3.098E-04, 2.532E-02, 7.010E-02, 5.975E-02, 5.345E-02, 7.526E-02, 8.972E-02, 1.506E-01, 1.019E-01, 4.177E-01, 4.905E-01, 6.736E-01, 7.624E-01, 7.185E-01, 8.202E-01, 7.980E-01, 8.954E-01, 1.013E+00, 1.087E+00, 1.149E+00, 1.210E+00, 1.250E+00, 1.304E+00, 1.345E+00, 1.342E+00, 1.349E+00, 1.356E+00, 1.341E+00, 1.364E+00, 1.326E+00, 1.323E+00, 1.231E+00, 1.202E+00, 1.088E+00, 1.043E+00, 9.859E-01, 9.468E-01, 9.123E-01, 8.560E-01, 8.090E-01, 8.177E-01, 8.259E-01, 9.266E-01, 1.030E+00, 1.172E+00, 1.328E+00, 1.537E+00, 1.607E+00, 1.641E+00, 1.598E+00, 1.403E+00, 1.203E+00, 1.024E+00, 7.923E-01, 5.926E-01, 4.400E-01, 3.034E-01, 2.112E-01, 1.464E-01, 1.046E-01, 7.418E-02, 5.522E-02, 3.982E-02, 2.936E-02, 2.511E-02, 1.870E-02, 1.296E-02, 9.903E-03, 9.423E-03, 9.231E-03, 6.472E-03, 7.884E-03, 4.329E-03, 2.418E-03, 3.861E-03, 2.891E-03, 5.423E-04, 6.677E-03, 4.057E-04, 3.023E-04},
//      {4.708E-04, 1.701E+00, -1.578E+00, 9.121E-01, 7.486E-01, 5.589E-01, 6.530E-01, 7.658E-01, 3.456E-01, 8.560E-01, 7.973E-01, 8.156E-01, 7.265E-01, 7.858E-01, 1.014E+00, 1.050E+00, 1.065E+00, 1.061E+00, 1.177E+00, 1.207E+00, 1.204E+00, 1.295E+00, 1.282E+00, 1.308E+00, 1.332E+00, 1.341E+00, 1.295E+00, 1.213E+00, 1.124E+00, 1.338E+00, 1.282E+00, 1.244E+00, 9.802E-01, 1.026E+00, 1.055E+00, 9.854E-01, 9.301E-01, 8.898E-01, 7.931E-01, 7.788E-01, 7.278E-01, 8.297E-01, 9.476E-01, 1.002E+00, 1.184E+00, 1.341E+00, 1.580E+00, 1.553E+00, 1.629E+00, 1.606E+00, 1.476E+00, 1.237E+00, 9.413E-01, 7.969E-01, 5.947E-01, 4.415E-01, 3.248E-01, 2.170E-01, 1.507E-01, 1.046E-01, 6.915E-02, 5.408E-02, 1.983E-02, 3.311E-02, 2.035E-02, 1.957E-02, 1.242E-02, 1.083E-02, 8.955E-03, 6.824E-03, 8.855E-03, 8.707E-03, 6.040E-03, 1.291E-02, 7.450E-03, 4.775E-03, 5.259E-03, 4.108E-03, 5.489E-03, 5.481E-03},
//      {2.406E-04, 3.385E-02, 3.578E-02, 5.432E-02, 6.220E-02, 9.562E-02, 1.249E-01, 1.405E-01, 1.066E-01, 3.192E-01, 4.762E-01, 6.200E-01, 6.800E-01, 7.151E-01, 7.432E-01, 7.980E-01, 8.981E-01, 1.007E+00, 1.090E+00, 1.145E+00, 1.208E+00, 1.252E+00, 1.304E+00, 1.329E+00, 1.345E+00, 1.349E+00, 1.354E+00, 1.362E+00, 1.372E+00, 1.359E+00, 1.325E+00, 1.259E+00, 1.200E+00, 1.133E+00, 1.059E+00, 9.963E-01, 9.505E-01, 9.115E-01, 8.607E-01, 8.247E-01, 8.266E-01, 8.668E-01, 9.347E-01, 1.045E+00, 1.196E+00, 1.369E+00, 1.551E+00, 1.602E+00, 1.626E+00, 1.571E+00, 1.409E+00, 1.217E+00, 1.005E+00, 7.886E-01, 6.010E-01, 4.290E-01, 3.019E-01, 2.112E-01, 1.465E-01, 1.022E-01, 7.362E-02, 5.391E-02, 4.057E-02, 3.021E-02, 2.415E-02, 1.752E-02, 1.257E-02, 1.084E-02, 9.528E-03, 8.775E-03, 7.496E-03, 5.919E-03, 5.381E-03, 5.185E-03, 4.161E-03, 3.090E-03, 1.867E-03, 1.701E-03, 9.188E-04, 5.315E-04},
//      {2.315E-01, 3.072E+00, 2.850E+00, 2.379E+00, 1.814E+00, 1.427E+00, 1.502E+00, 1.198E+00, 6.637E-01, 1.478E+00, 1.465E+00, 1.593E+00, 1.334E+00, 1.162E+00, 1.089E+00, 1.052E+00, 1.074E+00, 1.133E+00, 1.161E+00, 1.196E+00, 1.212E+00, 1.235E+00, 1.260E+00, 1.276E+00, 1.285E+00, 1.278E+00, 1.270E+00, 1.259E+00, 1.272E+00, 1.265E+00, 1.203E+00, 1.151E+00, 1.119E+00, 1.035E+00, 9.633E-01, 9.135E-01, 8.644E-01, 8.412E-01, 7.865E-01, 7.494E-01, 7.635E-01, 7.874E-01, 8.475E-01, 9.577E-01, 1.104E+00, 1.274E+00, 1.419E+00, 1.490E+00, 1.524E+00, 1.496E+00, 1.342E+00, 1.169E+00, 9.458E-01, 7.514E-01, 5.769E-01, 4.126E-01, 2.925E-01, 2.000E-01, 1.368E-01, 9.616E-02, 6.762E-02, 5.076E-02, 3.781E-02, 2.879E-02, 2.332E-02, 1.717E-02, 1.265E-02, 1.079E-02, 9.486E-03, 9.464E-03, 8.739E-03, 8.339E-03, 8.351E-03, 7.462E-03, 7.104E-03, 5.085E-03, 4.805E-03, 6.677E-03, 5.575E-03, 5.164E-03},
//      {2.174E-01, 2.227E+00, 2.479E+00, 2.328E+00, 1.704E+00, 1.940E+00, 1.549E+00, 1.289E+00, 5.517E-01, 1.441E+00, 1.490E+00, 1.434E+00, 1.362E+00, 1.171E+00, 1.073E+00, 1.050E+00, 1.080E+00, 1.120E+00, 1.159E+00, 1.167E+00, 1.210E+00, 1.239E+00, 1.259E+00, 1.290E+00, 1.269E+00, 1.256E+00, 1.265E+00, 1.263E+00, 1.287E+00, 1.244E+00, 1.225E+00, 1.178E+00, 1.111E+00, 1.037E+00, 9.787E-01, 9.073E-01, 8.541E-01, 8.298E-01, 7.933E-01, 7.530E-01, 7.696E-01, 7.966E-01, 8.582E-01, 9.675E-01, 1.092E+00, 1.266E+00, 1.416E+00, 1.513E+00, 1.557E+00, 1.461E+00, 1.341E+00, 1.135E+00, 9.446E-01, 7.411E-01, 5.572E-01, 4.133E-01, 2.920E-01, 1.992E-01, 1.383E-01, 9.723E-02, 6.830E-02, 5.173E-02, 3.840E-02, 3.008E-02, 2.393E-02, 1.743E-02, 1.259E-02, 1.057E-02, 9.381E-03, 8.891E-03, 8.430E-03, 7.669E-03, 8.314E-03, 8.597E-03, 6.436E-03, 6.161E-03, 5.354E-03, 5.808E-03, 7.759E-03, 4.967E-03},
//      {1.572E-01, 2.823E+00, 3.055E+00, 2.295E+00, 1.478E+00, 1.373E+00, 1.264E+00, 1.132E+00, 6.411E-01, 1.457E+00, 1.430E+00, 1.465E+00, 1.362E+00, 1.154E+00, 1.093E+00, 1.051E+00, 1.061E+00, 1.118E+00, 1.178E+00, 1.191E+00, 1.207E+00, 1.267E+00, 1.251E+00, 1.274E+00, 1.267E+00, 1.288E+00, 1.274E+00, 1.276E+00, 1.269E+00, 1.253E+00, 1.226E+00, 1.163E+00, 1.108E+00, 1.031E+00, 9.792E-01, 9.190E-01, 8.577E-01, 8.364E-01, 7.998E-01, 7.505E-01, 7.587E-01, 7.996E-01, 8.608E-01, 9.585E-01, 1.094E+00, 1.239E+00, 1.403E+00, 1.476E+00, 1.520E+00, 1.470E+00, 1.327E+00, 1.124E+00, 9.653E-01, 7.601E-01, 5.713E-01, 4.137E-01, 2.874E-01, 1.990E-01, 1.410E-01, 9.522E-02, 6.876E-02, 4.921E-02, 3.726E-02, 2.983E-02, 2.373E-02, 1.658E-02, 1.257E-02, 1.075E-02, 9.609E-03, 8.271E-03, 8.340E-03, 8.770E-03, 7.378E-03, 7.303E-03, 5.912E-03, 5.315E-03, 7.372E-03, 6.092E-03, 5.033E-03, 5.305E-03},
//      {2.160E-01, 2.263E+00, 1.119E+01, 2.336E+00, 1.736E+00, 1.510E+00, 1.077E+00, 1.176E+00, 7.053E-01, 1.423E+00, 1.569E+00, 1.440E+00, 1.375E+00, 1.159E+00, 1.075E+00, 1.069E+00, 1.062E+00, 1.133E+00, 1.158E+00, 1.204E+00, 1.216E+00, 1.240E+00, 1.263E+00, 1.282E+00, 1.286E+00, 1.287E+00, 1.260E+00, 1.280E+00, 1.266E+00, 1.247E+00, 1.234E+00, 1.178E+00, 1.121E+00, 1.030E+00, 9.682E-01, 9.054E-01, 8.685E-01, 8.296E-01, 7.917E-01, 7.498E-01, 7.487E-01, 7.899E-01, 8.571E-01, 9.687E-01, 1.098E+00, 1.254E+00, 1.410E+00, 1.492E+00, 1.542E+00, 1.455E+00, 1.350E+00, 1.139E+00, 9.516E-01, 7.482E-01, 5.658E-01, 4.106E-01, 2.926E-01, 1.957E-01, 1.395E-01, 9.392E-02, 6.780E-02, 5.034E-02, 3.757E-02, 3.000E-02, 2.382E-02, 1.738E-02, 1.216E-02, 1.105E-02, 9.388E-03, 8.357E-03, 8.885E-03, 8.099E-03, 7.050E-03, 6.724E-03, 6.228E-03, 4.828E-03, 5.222E-03, 5.245E-03, 7.617E-03, 7.289E-03},
//      {2.423E-01, 4.315E+00, 2.464E+00, 2.864E+00, 1.174E+00, 1.485E+00, 1.268E+00, 1.222E+00, 5.845E-01, 1.453E+00, 1.426E+00, 1.488E+00, 1.321E+00, 1.167E+00, 1.076E+00, 1.052E+00, 1.066E+00, 1.122E+00, 1.151E+00, 1.206E+00, 1.209E+00, 1.239E+00, 1.250E+00, 1.286E+00, 1.282E+00, 1.269E+00, 1.251E+00, 1.263E+00, 1.273E+00, 1.269E+00, 1.204E+00, 1.178E+00, 1.108E+00, 1.043E+00, 9.572E-01, 9.212E-01, 8.694E-01, 8.428E-01, 7.893E-01, 7.578E-01, 7.580E-01, 7.940E-01, 8.664E-01, 9.559E-01, 1.096E+00, 1.248E+00, 1.412E+00, 1.500E+00, 1.509E+00, 1.463E+00, 1.369E+00, 1.149E+00, 9.606E-01, 7.550E-01, 5.693E-01, 4.126E-01, 2.883E-01, 1.976E-01, 1.379E-01, 9.559E-02, 6.876E-02, 5.059E-02, 3.842E-02, 3.008E-02, 2.387E-02, 1.667E-02, 1.304E-02, 1.021E-02, 1.031E-02, 8.361E-03, 8.001E-03, 8.146E-03, 7.446E-03, 8.348E-03, 5.815E-03, 4.387E-03, 4.728E-03, 6.252E-03, 4.515E-03, 5.561E-03},
// {1.617E-01, 4.064E+00, 2.742E+00, 2.266E+00, 1.559E+00, 1.377E+00, 1.402E+00, 1.178E+00, 6.902E-01, 1.501E+00, 1.659E+00, 1.587E+00, 1.368E+00, 1.170E+00, 1.114E+00, 1.061E+00, 1.092E+00, 1.130E+00, 1.172E+00, 1.207E+00, 1.183E+00, 1.234E+00, 1.261E+00, 1.254E+00, 1.287E+00, 1.263E+00, 1.272E+00, 1.246E+00, 1.266E+00, 1.262E+00, 1.218E+00, 1.166E+00, 1.121E+00, 1.039E+00, 9.762E-01, 8.993E-01, 8.753E-01, 8.349E-01, 7.893E-01, 7.575E-01, 7.539E-01, 7.984E-01, 8.531E-01, 9.740E-01, 1.119E+00, 1.251E+00, 1.404E+00, 1.488E+00, 1.556E+00, 1.446E+00, 1.355E+00, 1.132E+00, 9.286E-01, 7.537E-01, 5.683E-01, 4.106E-01, 2.881E-01, 1.966E-01, 1.355E-01, 9.763E-02, 6.776E-02, 5.132E-02, 3.890E-02, 2.995E-02, 2.371E-02, 1.746E-02, 1.324E-02, 1.051E-02, 9.834E-03, 8.969E-03, 7.766E-03, 7.762E-03, 8.075E-03, 9.524E-03, 8.243E-03, 5.045E-03, 5.098E-03, 4.711E-03, 4.371E-03, 6.547E-03},
//      {3.073E-01, 2.023E+00, 2.628E+00, 2.467E+00, 1.432E+00, 1.146E+00, 1.139E+00, 1.750E+00, 5.444E-01, 1.307E+00, 1.464E+00, 1.483E+00, 1.358E+00, 1.188E+00, 1.069E+00, 1.036E+00, 1.110E+00, 1.127E+00, 1.156E+00, 1.209E+00, 1.195E+00, 1.237E+00, 1.262E+00, 1.289E+00, 1.287E+00, 1.264E+00, 1.262E+00, 1.249E+00, 1.281E+00, 1.250E+00, 1.228E+00, 1.186E+00, 1.097E+00, 1.033E+00, 9.705E-01, 9.052E-01, 8.553E-01, 8.536E-01, 7.986E-01, 7.560E-01, 7.652E-01, 8.156E-01, 8.463E-01, 9.698E-01, 1.088E+00, 1.243E+00, 1.417E+00, 1.469E+00, 1.544E+00, 1.439E+00, 1.331E+00, 1.134E+00, 9.276E-01, 7.655E-01, 5.659E-01, 4.075E-01, 2.903E-01, 1.991E-01, 1.353E-01, 9.565E-02, 6.819E-02, 5.082E-02, 3.936E-02, 2.947E-02, 2.426E-02, 1.780E-02, 1.251E-02, 1.031E-02, 1.034E-02, 9.703E-03, 8.115E-03, 7.457E-03, 6.907E-03, 6.714E-03, 5.733E-03, 7.032E-03, 5.893E-03, 4.560E-03, 7.615E-03, 4.148E-03},
//      {1.575E-01, 2.376E+00, 5.511E+00, 4.140E+00, 2.222E+00, 1.022E+00, 1.414E+00, 1.012E+00, 5.570E-01, 1.627E+00, 1.349E+00, 1.507E+00, 1.347E+00, 1.251E+00, 1.103E+00, 1.054E+00, 1.092E+00, 1.122E+00, 1.182E+00, 1.167E+00, 1.212E+00, 1.234E+00, 1.264E+00, 1.287E+00, 1.260E+00, 1.284E+00, 1.277E+00, 1.250E+00, 1.300E+00, 1.262E+00, 1.246E+00, 1.159E+00, 1.099E+00, 1.041E+00, 9.627E-01, 9.212E-01, 8.749E-01, 8.307E-01, 7.929E-01, 7.360E-01, 7.686E-01, 7.892E-01, 8.466E-01, 9.500E-01, 1.047E+00, 1.288E+00, 1.426E+00, 1.505E+00, 1.517E+00, 1.455E+00, 1.287E+00, 1.121E+00, 9.316E-01, 7.538E-01, 5.805E-01, 4.069E-01, 2.963E-01, 1.982E-01, 1.402E-01, 9.389E-02, 6.983E-02, 5.031E-02, 3.893E-02, 3.000E-02, 2.573E-02, 1.678E-02, 1.244E-02, 1.088E-02, 9.356E-03, 8.698E-03, 8.022E-03, 6.875E-03, 1.100E-02, 9.955E-03, 7.337E-03, 4.677E-03, 6.427E-03, 6.148E-03, 8.214E-03, 3.827E-03},
//      {1.870E-01, 4.744E+00, 3.217E+00, 2.383E+00, 1.802E+00, 1.486E+00, 1.329E+00, 1.205E+00, 6.102E-01, 1.495E+00, 1.516E+00, 1.478E+00, 1.319E+00, 1.164E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.130E+00, 1.165E+00, 1.189E+00, 1.212E+00, 1.236E+00, 1.258E+00, 1.271E+00, 1.271E+00, 1.272E+00, 1.272E+00, 1.268E+00, 1.277E+00, 1.253E+00, 1.221E+00, 1.169E+00, 1.109E+00, 1.039E+00, 9.688E-01, 9.133E-01, 8.658E-01, 8.371E-01, 7.900E-01, 7.512E-01, 7.587E-01, 7.925E-01, 8.574E-01, 9.586E-01, 1.093E+00, 1.257E+00, 1.420E+00, 1.493E+00, 1.527E+00, 1.462E+00, 1.338E+00, 1.155E+00, 9.495E-01, 7.493E-01, 5.703E-01, 4.107E-01, 2.901E-01, 1.994E-01, 1.376E-01, 9.651E-02, 6.895E-02, 5.073E-02, 3.841E-02, 2.999E-02, 2.412E-02, 1.701E-02, 1.244E-02, 1.072E-02, 9.630E-03, 8.829E-03, 8.312E-03, 8.101E-03, 7.724E-03, 7.905E-03, 6.299E-03, 5.287E-03, 5.476E-03, 5.776E-03, 5.866E-03, 6.320E-03},
//      {1.913E-01, 4.255E+00, 3.444E+00, 2.481E+00, 1.640E+00, 1.531E+00, 1.288E+00, 1.270E+00, 5.997E-01, 1.442E+00, 1.477E+00, 1.476E+00, 1.330E+00, 1.169E+00, 1.083E+00, 1.051E+00, 1.078E+00, 1.126E+00, 1.166E+00, 1.188E+00, 1.211E+00, 1.238E+00, 1.256E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.271E+00, 1.267E+00, 1.274E+00, 1.254E+00, 1.220E+00, 1.167E+00, 1.113E+00, 1.037E+00, 9.688E-01, 9.129E-01, 8.681E-01, 8.336E-01, 7.865E-01, 7.516E-01, 7.576E-01, 7.948E-01, 8.593E-01, 9.561E-01, 1.097E+00, 1.258E+00, 1.421E+00, 1.492E+00, 1.534E+00, 1.461E+00, 1.341E+00, 1.156E+00, 9.519E-01, 7.507E-01, 5.693E-01, 4.101E-01, 2.896E-01, 1.981E-01, 1.374E-01, 9.658E-02, 6.937E-02, 5.074E-02, 3.867E-02, 2.989E-02, 2.413E-02, 1.713E-02, 1.250E-02, 1.076E-02, 9.502E-03, 8.767E-03, 8.258E-03, 8.063E-03, 7.855E-03, 7.777E-03, 6.306E-03, 5.442E-03, 5.528E-03, 5.516E-03, 6.168E-03, 5.712E-03},
//      {1.898E-01, 4.165E+00, 3.239E+00, 2.648E+00, 1.610E+00, 1.494E+00, 1.289E+00, 1.238E+00, 6.235E-01, 1.438E+00, 1.486E+00, 1.484E+00, 1.339E+00, 1.165E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.129E+00, 1.168E+00, 1.188E+00, 1.213E+00, 1.239E+00, 1.262E+00, 1.272E+00, 1.272E+00, 1.269E+00, 1.273E+00, 1.266E+00, 1.276E+00, 1.250E+00, 1.221E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.687E-01, 9.137E-01, 8.687E-01, 8.352E-01, 7.870E-01, 7.480E-01, 7.602E-01, 7.922E-01, 8.591E-01, 9.607E-01, 1.091E+00, 1.255E+00, 1.415E+00, 1.496E+00, 1.528E+00, 1.460E+00, 1.339E+00, 1.154E+00, 9.493E-01, 7.497E-01, 5.703E-01, 4.105E-01, 2.896E-01, 1.985E-01, 1.373E-01, 9.672E-02, 6.940E-02, 5.067E-02, 3.834E-02, 3.009E-02, 2.403E-02, 1.718E-02, 1.255E-02, 1.087E-02, 9.529E-03, 8.865E-03, 8.370E-03, 7.970E-03, 7.921E-03, 7.850E-03, 6.155E-03, 5.393E-03, 5.518E-03, 5.859E-03, 5.714E-03, 6.418E-03},
//      {1.897E-01, 3.957E+00, 3.856E+00, 2.684E+00, 1.643E+00, 1.480E+00, 1.304E+00, 1.284E+00, 6.124E-01, 1.434E+00, 1.497E+00, 1.483E+00, 1.326E+00, 1.166E+00, 1.080E+00, 1.051E+00, 1.074E+00, 1.126E+00, 1.163E+00, 1.187E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.268E+00, 1.274E+00, 1.274E+00, 1.270E+00, 1.269E+00, 1.277E+00, 1.252E+00, 1.224E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.698E-01, 9.114E-01, 8.652E-01, 8.348E-01, 7.895E-01, 7.498E-01, 7.574E-01, 7.921E-01, 8.594E-01, 9.566E-01, 1.096E+00, 1.260E+00, 1.419E+00, 1.496E+00, 1.534E+00, 1.465E+00, 1.340E+00, 1.157E+00, 9.516E-01, 7.506E-01, 5.693E-01, 4.110E-01, 2.894E-01, 1.974E-01, 1.380E-01, 9.660E-02, 6.948E-02, 5.088E-02, 3.837E-02, 2.965E-02, 2.417E-02, 1.699E-02, 1.248E-02, 1.080E-02, 9.539E-03, 8.775E-03, 8.265E-03, 8.058E-03, 7.837E-03, 7.898E-03, 6.202E-03, 5.428E-03, 5.554E-03, 5.352E-03, 5.705E-03, 6.037E-03},
//      {1.899E-01, 3.543E+00, 3.519E+00, 2.642E+00, 1.581E+00, 1.495E+00, 1.296E+00, 1.289E+00, 6.150E-01, 1.486E+00, 1.474E+00, 1.479E+00, 1.324E+00, 1.167E+00, 1.074E+00, 1.054E+00, 1.080E+00, 1.133E+00, 1.165E+00, 1.186E+00, 1.215E+00, 1.238E+00, 1.261E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.268E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.223E+00, 1.171E+00, 1.109E+00, 1.036E+00, 9.682E-01, 9.106E-01, 8.671E-01, 8.343E-01, 7.894E-01, 7.523E-01, 7.561E-01, 7.949E-01, 8.588E-01, 9.588E-01, 1.095E+00, 1.253E+00, 1.420E+00, 1.494E+00, 1.534E+00, 1.461E+00, 1.336E+00, 1.154E+00, 9.528E-01, 7.531E-01, 5.697E-01, 4.117E-01, 2.903E-01, 1.985E-01, 1.375E-01, 9.617E-02, 6.911E-02, 5.078E-02, 3.842E-02, 2.983E-02, 2.402E-02, 1.707E-02, 1.242E-02, 1.086E-02, 9.659E-03, 8.759E-03, 8.298E-03, 8.003E-03, 7.673E-03, 7.920E-03, 6.423E-03, 5.314E-03, 5.516E-03, 5.349E-03, 5.832E-03, 5.663E-03},
//    };

 pileupweight = { // 69.2 mb
     { 2.835E-04, 4.399E-02, 4.817E-02, 6.416E-02, 6.566E-02, 1.137E-01, 1.327E-01, 1.748E-01, 1.153E-01, 3.682E-01, 4.893E-01, 6.327E-01, 6.937E-01, 7.157E-01, 7.351E-01, 8.159E-01, 8.876E-01, 1.006E+00, 1.086E+00, 1.145E+00, 1.208E+00, 1.252E+00, 1.295E+00, 1.326E+00, 1.329E+00, 1.351E+00, 1.349E+00, 1.354E+00, 1.364E+00, 1.348E+00, 1.321E+00, 1.261E+00, 1.191E+00, 1.125E+00, 1.056E+00, 9.903E-01, 9.451E-01, 9.121E-01, 8.587E-01, 8.164E-01, 8.142E-01, 8.557E-01, 9.305E-01, 1.044E+00, 1.188E+00, 1.347E+00, 1.527E+00, 1.576E+00, 1.627E+00, 1.561E+00, 1.363E+00, 1.222E+00, 1.004E+00, 7.747E-01, 5.955E-01, 4.290E-01, 3.002E-01, 2.099E-01, 1.454E-01, 1.015E-01, 7.117E-02, 5.287E-02, 4.043E-02, 3.071E-02, 2.376E-02, 1.749E-02, 1.254E-02, 1.029E-02, 1.006E-02, 8.396E-03, 7.763E-03, 5.241E-03, 6.290E-03, 5.725E-03, 2.761E-03, 2.530E-03, 1.811E-03, 1.530E-03, 6.849E-04, 3.797E-04}, // DYJetsMG.root
     { 3.544E-04, 3.998E-02, 4.526E-02, 7.801E-02, 9.146E-02, 1.097E-01, 1.527E-01, 2.427E-01, 1.278E-01, 4.256E-01, 5.532E-01, 6.663E-01, 6.732E-01, 7.100E-01, 7.715E-01, 8.042E-01, 9.015E-01, 9.917E-01, 1.066E+00, 1.131E+00, 1.189E+00, 1.253E+00, 1.282E+00, 1.315E+00, 1.325E+00, 1.339E+00, 1.339E+00, 1.339E+00, 1.362E+00, 1.336E+00, 1.297E+00, 1.239E+00, 1.190E+00, 1.117E+00, 1.039E+00, 9.847E-01, 9.359E-01, 8.988E-01, 8.460E-01, 8.122E-01, 8.128E-01, 8.503E-01, 9.144E-01, 1.020E+00, 1.173E+00, 1.348E+00, 1.525E+00, 1.596E+00, 1.638E+00, 1.565E+00, 1.346E+00, 1.213E+00, 9.796E-01, 7.891E-01, 5.957E-01, 4.270E-01, 3.022E-01, 2.079E-01, 1.453E-01, 1.013E-01, 7.242E-02, 5.264E-02, 4.040E-02, 3.102E-02, 2.399E-02, 1.754E-02, 1.216E-02, 1.027E-02, 9.501E-03, 8.830E-03, 7.677E-03, 5.254E-03, 6.172E-03, 5.941E-03, 3.630E-03, 4.188E-03, 2.190E-03, 1.532E-03, 1.240E-03, 5.375E-04}, // QCD1000.root
     { 1.749E-01, 4.172E+00, 3.462E+00, 2.677E+00, 1.657E+00, 1.475E+00, 1.255E+00, 1.247E+00, 6.000E-01, 1.423E+00, 1.498E+00, 1.492E+00, 1.325E+00, 1.164E+00, 1.082E+00, 1.052E+00, 1.083E+00, 1.127E+00, 1.163E+00, 1.191E+00, 1.212E+00, 1.241E+00, 1.255E+00, 1.270E+00, 1.274E+00, 1.273E+00, 1.272E+00, 1.268E+00, 1.278E+00, 1.250E+00, 1.223E+00, 1.171E+00, 1.111E+00, 1.036E+00, 9.706E-01, 9.104E-01, 8.681E-01, 8.332E-01, 7.862E-01, 7.510E-01, 7.602E-01, 7.926E-01, 8.584E-01, 9.577E-01, 1.096E+00, 1.256E+00, 1.416E+00, 1.494E+00, 1.526E+00, 1.468E+00, 1.336E+00, 1.152E+00, 9.528E-01, 7.484E-01, 5.701E-01, 4.122E-01, 2.880E-01, 1.984E-01, 1.374E-01, 9.694E-02, 6.917E-02, 5.072E-02, 3.857E-02, 2.990E-02, 2.407E-02, 1.711E-02, 1.255E-02, 1.081E-02, 9.624E-03, 8.906E-03, 8.153E-03, 8.132E-03, 7.845E-03, 7.748E-03, 6.232E-03, 5.267E-03, 5.608E-03, 6.070E-03, 6.121E-03, 6.164E-03}, // QCD1500.root
     { 1.672E-01, 4.002E+00, 3.617E+00, 2.548E+00, 1.509E+00, 1.493E+00, 1.296E+00, 1.240E+00, 6.044E-01, 1.455E+00, 1.498E+00, 1.488E+00, 1.340E+00, 1.174E+00, 1.086E+00, 1.052E+00, 1.083E+00, 1.128E+00, 1.168E+00, 1.181E+00, 1.205E+00, 1.236E+00, 1.259E+00, 1.272E+00, 1.271E+00, 1.272E+00, 1.271E+00, 1.267E+00, 1.278E+00, 1.251E+00, 1.219E+00, 1.164E+00, 1.109E+00, 1.038E+00, 9.689E-01, 9.156E-01, 8.645E-01, 8.359E-01, 7.875E-01, 7.518E-01, 7.621E-01, 7.939E-01, 8.594E-01, 9.634E-01, 1.096E+00, 1.255E+00, 1.424E+00, 1.511E+00, 1.535E+00, 1.457E+00, 1.342E+00, 1.153E+00, 9.464E-01, 7.538E-01, 5.673E-01, 4.094E-01, 2.882E-01, 1.995E-01, 1.377E-01, 9.630E-02, 6.899E-02, 5.090E-02, 3.856E-02, 2.996E-02, 2.428E-02, 1.692E-02, 1.250E-02, 1.081E-02, 9.817E-03, 8.680E-03, 8.324E-03, 8.295E-03, 7.672E-03, 7.872E-03, 6.039E-03, 5.129E-03, 5.624E-03, 5.494E-03, 6.660E-03, 5.473E-03}, // QCD2000.root
     { 2.758E-04, 2.979E-02, 4.481E-02, 7.384E-02, 6.863E-02, 1.116E-01, 1.301E-01, 1.552E-01, 1.058E-01, 3.333E-01, 5.015E-01, 6.410E-01, 6.712E-01, 7.089E-01, 7.387E-01, 8.027E-01, 9.054E-01, 9.982E-01, 1.086E+00, 1.149E+00, 1.200E+00, 1.257E+00, 1.302E+00, 1.324E+00, 1.342E+00, 1.344E+00, 1.353E+00, 1.352E+00, 1.366E+00, 1.349E+00, 1.320E+00, 1.250E+00, 1.194E+00, 1.130E+00, 1.055E+00, 9.941E-01, 9.461E-01, 9.058E-01, 8.535E-01, 8.164E-01, 8.234E-01, 8.614E-01, 9.270E-01, 1.046E+00, 1.190E+00, 1.357E+00, 1.530E+00, 1.580E+00, 1.623E+00, 1.552E+00, 1.396E+00, 1.203E+00, 9.963E-01, 7.804E-01, 5.990E-01, 4.260E-01, 3.034E-01, 2.091E-01, 1.455E-01, 1.023E-01, 7.260E-02, 5.320E-02, 4.007E-02, 3.055E-02, 2.303E-02, 1.753E-02, 1.254E-02, 1.085E-02, 8.972E-03, 8.785E-03, 7.276E-03, 6.235E-03, 5.168E-03, 6.401E-03, 3.540E-03, 3.876E-03, 2.529E-03, 1.391E-03, 1.006E-03, 5.000E-04}, // QCD300.root
     { 2.494E-04, 3.158E-02, 3.862E-02, 5.765E-02, 7.191E-02, 1.117E-01, 1.001E-01, 1.299E-01, 1.084E-01, 3.222E-01, 4.813E-01, 6.202E-01, 6.505E-01, 7.113E-01, 7.297E-01, 7.877E-01, 9.025E-01, 1.013E+00, 1.094E+00, 1.148E+00, 1.211E+00, 1.252E+00, 1.304E+00, 1.336E+00, 1.347E+00, 1.356E+00, 1.354E+00, 1.365E+00, 1.369E+00, 1.351E+00, 1.328E+00, 1.258E+00, 1.202E+00, 1.130E+00, 1.059E+00, 9.882E-01, 9.494E-01, 9.124E-01, 8.601E-01, 8.192E-01, 8.230E-01, 8.637E-01, 9.387E-01, 1.048E+00, 1.188E+00, 1.354E+00, 1.540E+00, 1.616E+00, 1.634E+00, 1.572E+00, 1.388E+00, 1.224E+00, 1.001E+00, 7.875E-01, 5.981E-01, 4.347E-01, 3.054E-01, 2.086E-01, 1.461E-01, 1.012E-01, 7.329E-02, 5.338E-02, 4.046E-02, 3.013E-02, 2.390E-02, 1.758E-02, 1.241E-02, 1.099E-02, 9.904E-03, 8.385E-03, 7.029E-03, 5.092E-03, 5.896E-03, 4.427E-03, 3.156E-03, 3.957E-03, 2.318E-03, 2.368E-03, 1.121E-03, 5.284E-04}, // QCD500.root
     { 2.960E-04, 4.661E-02, 5.142E-02, 7.836E-02, 7.650E-02, 1.158E-01, 1.384E-01, 1.598E-01, 1.298E-01, 4.088E-01, 5.108E-01, 6.759E-01, 7.111E-01, 7.069E-01, 7.569E-01, 8.221E-01, 9.024E-01, 9.951E-01, 1.083E+00, 1.143E+00, 1.196E+00, 1.243E+00, 1.290E+00, 1.319E+00, 1.335E+00, 1.333E+00, 1.349E+00, 1.351E+00, 1.349E+00, 1.339E+00, 1.312E+00, 1.253E+00, 1.187E+00, 1.126E+00, 1.046E+00, 9.803E-01, 9.405E-01, 9.074E-01, 8.515E-01, 8.155E-01, 8.172E-01, 8.621E-01, 9.268E-01, 1.040E+00, 1.184E+00, 1.351E+00, 1.528E+00, 1.601E+00, 1.645E+00, 1.555E+00, 1.395E+00, 1.202E+00, 1.009E+00, 7.834E-01, 5.907E-01, 4.264E-01, 3.005E-01, 2.080E-01, 1.442E-01, 1.016E-01, 7.377E-02, 5.274E-02, 4.028E-02, 2.943E-02, 2.345E-02, 1.733E-02, 1.304E-02, 1.089E-02, 9.218E-03, 8.375E-03, 7.196E-03, 4.961E-03, 5.212E-03, 4.817E-03, 2.602E-03, 3.627E-03, 2.491E-03, 2.361E-03, 6.611E-04, 6.415E-04}, // QCD700.root
     { 2.894E-04, 4.360E-02, 5.014E-02, 6.912E-02, 8.141E-02, 1.445E-01, 1.405E-01, 1.480E-01, 1.039E-01, 3.417E-01, 4.570E-01, 6.214E-01, 6.927E-01, 6.701E-01, 6.820E-01, 8.060E-01, 8.304E-01, 9.961E-01, 1.076E+00, 1.131E+00, 1.193E+00, 1.219E+00, 1.294E+00, 1.326E+00, 1.323E+00, 1.350E+00, 1.362E+00, 1.348E+00, 1.360E+00, 1.339E+00, 1.311E+00, 1.262E+00, 1.185E+00, 1.131E+00, 1.058E+00, 1.002E+00, 9.544E-01, 9.065E-01, 8.609E-01, 8.214E-01, 8.346E-01, 8.601E-01, 9.398E-01, 1.059E+00, 1.200E+00, 1.364E+00, 1.510E+00, 1.641E+00, 1.590E+00, 1.542E+00, 1.397E+00, 1.237E+00, 1.003E+00, 8.001E-01, 5.921E-01, 4.271E-01, 3.083E-01, 2.139E-01, 1.458E-01, 1.017E-01, 7.216E-02, 5.370E-02, 4.107E-02, 3.045E-02, 2.474E-02, 1.765E-02, 1.298E-02, 1.070E-02, 9.453E-03, 9.417E-03, 7.668E-03, 4.481E-03, 3.087E-03, 6.682E-03, 3.068E-03, 1.882E-03, 1.948E-03, 5.821E-03, 1.565E-03, 3.780E-04}, // STs.root
     { 1.800E-01, 3.572E+00, 3.238E+00, 2.501E+00, 1.587E+00, 1.524E+00, 1.259E+00, 1.234E+00, 6.249E-01, 1.469E+00, 1.489E+00, 1.493E+00, 1.332E+00, 1.168E+00, 1.077E+00, 1.050E+00, 1.085E+00, 1.129E+00, 1.164E+00, 1.190E+00, 1.213E+00, 1.238E+00, 1.258E+00, 1.270E+00, 1.275E+00, 1.274E+00, 1.272E+00, 1.267E+00, 1.276E+00, 1.252E+00, 1.223E+00, 1.169E+00, 1.110E+00, 1.035E+00, 9.696E-01, 9.107E-01, 8.679E-01, 8.329E-01, 7.873E-01, 7.513E-01, 7.580E-01, 7.947E-01, 8.584E-01, 9.582E-01, 1.093E+00, 1.255E+00, 1.420E+00, 1.496E+00, 1.525E+00, 1.468E+00, 1.336E+00, 1.156E+00, 9.496E-01, 7.491E-01, 5.688E-01, 4.106E-01, 2.897E-01, 1.987E-01, 1.380E-01, 9.650E-02, 6.927E-02, 5.094E-02, 3.836E-02, 2.994E-02, 2.412E-02, 1.694E-02, 1.244E-02, 1.079E-02, 9.658E-03, 8.864E-03, 8.303E-03, 8.066E-03, 7.846E-03, 7.957E-03, 6.113E-03, 5.381E-03, 5.472E-03, 5.358E-03, 5.970E-03, 6.237E-03}, // STt.root
     { 1.780E-01, 5.124E+00, 3.340E+00, 2.752E+00, 1.532E+00, 1.502E+00, 1.283E+00, 1.247E+00, 6.408E-01, 1.423E+00, 1.493E+00, 1.501E+00, 1.316E+00, 1.161E+00, 1.081E+00, 1.048E+00, 1.081E+00, 1.129E+00, 1.170E+00, 1.190E+00, 1.214E+00, 1.239E+00, 1.258E+00, 1.269E+00, 1.274E+00, 1.270E+00, 1.265E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.220E+00, 1.173E+00, 1.111E+00, 1.039E+00, 9.675E-01, 9.125E-01, 8.687E-01, 8.348E-01, 7.882E-01, 7.476E-01, 7.592E-01, 7.946E-01, 8.570E-01, 9.614E-01, 1.095E+00, 1.257E+00, 1.418E+00, 1.502E+00, 1.533E+00, 1.460E+00, 1.343E+00, 1.154E+00, 9.496E-01, 7.457E-01, 5.701E-01, 4.112E-01, 2.882E-01, 1.982E-01, 1.382E-01, 9.659E-02, 6.902E-02, 5.065E-02, 3.841E-02, 3.010E-02, 2.401E-02, 1.713E-02, 1.250E-02, 1.079E-02, 9.623E-03, 8.901E-03, 8.297E-03, 8.180E-03, 7.698E-03, 7.869E-03, 6.500E-03, 5.429E-03, 5.453E-03, 5.933E-03, 5.511E-03, 5.550E-03}, // STtb.root
     { 2.605E-04, 2.631E-02, 3.681E-02, 4.785E-02, 7.677E-02, 1.316E-01, 9.301E-02, 1.018E-01, 1.079E-01, 4.031E-01, 4.383E-01, 6.138E-01, 6.870E-01, 7.113E-01, 7.262E-01, 8.072E-01, 8.834E-01, 9.917E-01, 1.070E+00, 1.134E+00, 1.185E+00, 1.256E+00, 1.307E+00, 1.338E+00, 1.329E+00, 1.353E+00, 1.370E+00, 1.381E+00, 1.371E+00, 1.359E+00, 1.336E+00, 1.252E+00, 1.208E+00, 1.133E+00, 1.066E+00, 9.925E-01, 9.398E-01, 9.187E-01, 8.526E-01, 8.198E-01, 8.374E-01, 8.628E-01, 9.381E-01, 1.055E+00, 1.208E+00, 1.350E+00, 1.567E+00, 1.627E+00, 1.624E+00, 1.558E+00, 1.401E+00, 1.214E+00, 1.002E+00, 7.880E-01, 5.921E-01, 4.393E-01, 3.076E-01, 2.087E-01, 1.429E-01, 1.036E-01, 7.355E-02, 5.130E-02, 3.955E-02, 3.146E-02, 2.366E-02, 1.726E-02, 1.258E-02, 1.092E-02, 1.015E-02, 9.365E-03, 6.013E-03, 3.590E-03, 4.496E-03, 4.837E-03, 6.140E-03, 4.341E-03, 1.343E-03, 4.228E-03, 5.226E-04, 7.545E-04}, // STtWt.root
     { 2.607E-04, 2.222E-02, 4.369E-02, 5.655E-02, 7.639E-02, 9.580E-02, 1.022E-01, 1.921E-01, 1.312E-01, 3.306E-01, 5.204E-01, 6.816E-01, 6.607E-01, 6.635E-01, 7.260E-01, 7.893E-01, 9.209E-01, 1.004E+00, 1.098E+00, 1.158E+00, 1.206E+00, 1.268E+00, 1.289E+00, 1.328E+00, 1.341E+00, 1.340E+00, 1.358E+00, 1.349E+00, 1.383E+00, 1.356E+00, 1.331E+00, 1.242E+00, 1.211E+00, 1.133E+00, 1.049E+00, 9.995E-01, 9.512E-01, 9.076E-01, 8.579E-01, 8.202E-01, 8.377E-01, 8.753E-01, 9.439E-01, 1.041E+00, 1.193E+00, 1.341E+00, 1.525E+00, 1.574E+00, 1.593E+00, 1.569E+00, 1.366E+00, 1.206E+00, 1.021E+00, 7.956E-01, 6.034E-01, 4.278E-01, 3.102E-01, 2.086E-01, 1.461E-01, 1.031E-01, 7.383E-02, 5.028E-02, 4.112E-02, 3.090E-02, 2.154E-02, 1.732E-02, 1.306E-02, 1.068E-02, 9.153E-03, 8.133E-03, 6.713E-03, 5.319E-03, 3.989E-03, 8.444E-03, 1.941E-03, 4.946E-03, 2.976E-03, 3.784E-03, 5.910E-04, 2.521E-04}, // STtWtb.root
     { 2.406E-04, 3.385E-02, 3.578E-02, 5.432E-02, 6.220E-02, 9.562E-02, 1.249E-01, 1.405E-01, 1.066E-01, 3.192E-01, 4.762E-01, 6.200E-01, 6.800E-01, 7.151E-01, 7.432E-01, 7.980E-01, 8.981E-01, 1.007E+00, 1.090E+00, 1.145E+00, 1.208E+00, 1.252E+00, 1.304E+00, 1.329E+00, 1.345E+00, 1.349E+00, 1.354E+00, 1.362E+00, 1.372E+00, 1.359E+00, 1.325E+00, 1.259E+00, 1.200E+00, 1.133E+00, 1.059E+00, 9.963E-01, 9.505E-01, 9.115E-01, 8.607E-01, 8.247E-01, 8.266E-01, 8.668E-01, 9.347E-01, 1.045E+00, 1.196E+00, 1.369E+00, 1.551E+00, 1.602E+00, 1.626E+00, 1.571E+00, 1.409E+00, 1.217E+00, 1.005E+00, 7.886E-01, 6.010E-01, 4.290E-01, 3.019E-01, 2.112E-01, 1.465E-01, 1.022E-01, 7.362E-02, 5.391E-02, 4.057E-02, 3.021E-02, 2.415E-02, 1.752E-02, 1.257E-02, 1.084E-02, 9.528E-03, 8.775E-03, 7.496E-03, 5.919E-03, 5.381E-03, 5.185E-03, 4.161E-03, 3.090E-03, 1.867E-03, 1.701E-03, 9.188E-04, 5.315E-04}, // TThad.root
     { 2.326E-04, 2.787E-02, 3.339E-02, 5.035E-02, 6.247E-02, 9.966E-02, 1.074E-01, 1.442E-01, 1.041E-01, 3.121E-01, 4.634E-01, 6.124E-01, 6.707E-01, 6.990E-01, 7.462E-01, 8.168E-01, 9.110E-01, 1.022E+00, 1.100E+00, 1.156E+00, 1.212E+00, 1.261E+00, 1.307E+00, 1.336E+00, 1.353E+00, 1.354E+00, 1.353E+00, 1.360E+00, 1.376E+00, 1.354E+00, 1.326E+00, 1.264E+00, 1.198E+00, 1.132E+00, 1.062E+00, 9.996E-01, 9.498E-01, 9.122E-01, 8.609E-01, 8.217E-01, 8.276E-01, 8.657E-01, 9.451E-01, 1.048E+00, 1.196E+00, 1.360E+00, 1.538E+00, 1.600E+00, 1.634E+00, 1.581E+00, 1.403E+00, 1.211E+00, 9.999E-01, 7.865E-01, 5.984E-01, 4.296E-01, 3.034E-01, 2.107E-01, 1.463E-01, 1.024E-01, 7.337E-02, 5.378E-02, 4.052E-02, 3.077E-02, 2.339E-02, 1.753E-02, 1.269E-02, 1.092E-02, 9.353E-03, 9.002E-03, 7.919E-03, 4.869E-03, 6.104E-03, 4.942E-03, 3.426E-03, 2.660E-03, 2.304E-03, 2.039E-03, 1.059E-03, 5.481E-04}, // TT1L.root
     { 2.328E-04, 3.090E-02, 4.163E-02, 4.817E-02, 5.984E-02, 9.593E-02, 1.055E-01, 1.605E-01, 1.151E-01, 3.110E-01, 4.780E-01, 6.027E-01, 6.617E-01, 6.884E-01, 7.227E-01, 7.992E-01, 8.973E-01, 1.001E+00, 1.085E+00, 1.149E+00, 1.217E+00, 1.260E+00, 1.303E+00, 1.342E+00, 1.352E+00, 1.359E+00, 1.367E+00, 1.366E+00, 1.386E+00, 1.359E+00, 1.335E+00, 1.267E+00, 1.203E+00, 1.130E+00, 1.060E+00, 9.983E-01, 9.556E-01, 9.185E-01, 8.634E-01, 8.242E-01, 8.302E-01, 8.673E-01, 9.375E-01, 1.051E+00, 1.194E+00, 1.359E+00, 1.540E+00, 1.593E+00, 1.626E+00, 1.570E+00, 1.398E+00, 1.220E+00, 9.918E-01, 7.834E-01, 5.988E-01, 4.256E-01, 3.069E-01, 2.102E-01, 1.467E-01, 1.022E-01, 7.271E-02, 5.372E-02, 4.035E-02, 3.002E-02, 2.315E-02, 1.791E-02, 1.267E-02, 1.052E-02, 9.544E-03, 8.520E-03, 8.017E-03, 6.324E-03, 6.082E-03, 5.663E-03, 2.850E-03, 3.110E-03, 2.375E-03, 1.463E-03, 1.312E-03, 4.850E-04}, // TT2L.root
     { 1.829E-01, 3.581E+00, 3.653E+00, 2.510E+00, 1.605E+00, 1.528E+00, 1.253E+00, 1.264E+00, 6.156E-01, 1.469E+00, 1.500E+00, 1.473E+00, 1.340E+00, 1.166E+00, 1.074E+00, 1.057E+00, 1.075E+00, 1.127E+00, 1.169E+00, 1.188E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.272E+00, 1.272E+00, 1.272E+00, 1.270E+00, 1.266E+00, 1.275E+00, 1.250E+00, 1.224E+00, 1.167E+00, 1.110E+00, 1.039E+00, 9.682E-01, 9.119E-01, 8.667E-01, 8.359E-01, 7.903E-01, 7.499E-01, 7.578E-01, 7.936E-01, 8.595E-01, 9.557E-01, 1.098E+00, 1.254E+00, 1.419E+00, 1.500E+00, 1.529E+00, 1.462E+00, 1.339E+00, 1.152E+00, 9.470E-01, 7.516E-01, 5.683E-01, 4.100E-01, 2.894E-01, 1.993E-01, 1.372E-01, 9.685E-02, 6.914E-02, 5.076E-02, 3.851E-02, 2.990E-02, 2.414E-02, 1.714E-02, 1.249E-02, 1.084E-02, 9.637E-03, 8.826E-03, 8.251E-03, 7.945E-03, 7.913E-03, 7.839E-03, 6.205E-03, 5.395E-03, 5.376E-03, 5.855E-03, 5.805E-03, 5.727E-03}, // TTMtt1000.root
     { 2.564E-04, 3.837E-02, 3.059E-02, 5.322E-02, 6.786E-02, 9.388E-02, 1.256E-01, 1.484E-01, 1.033E-01, 3.382E-01, 4.688E-01, 6.103E-01, 6.883E-01, 6.948E-01, 7.502E-01, 8.297E-01, 9.089E-01, 9.969E-01, 1.095E+00, 1.143E+00, 1.203E+00, 1.262E+00, 1.306E+00, 1.333E+00, 1.348E+00, 1.344E+00, 1.349E+00, 1.360E+00, 1.371E+00, 1.356E+00, 1.326E+00, 1.267E+00, 1.197E+00, 1.129E+00, 1.052E+00, 9.949E-01, 9.485E-01, 9.147E-01, 8.563E-01, 8.183E-01, 8.310E-01, 8.650E-01, 9.384E-01, 1.046E+00, 1.197E+00, 1.363E+00, 1.533E+00, 1.615E+00, 1.624E+00, 1.580E+00, 1.390E+00, 1.200E+00, 1.008E+00, 7.782E-01, 5.965E-01, 4.190E-01, 3.025E-01, 2.105E-01, 1.457E-01, 1.019E-01, 7.269E-02, 5.390E-02, 4.059E-02, 3.069E-02, 2.300E-02, 1.719E-02, 1.252E-02, 1.121E-02, 9.765E-03, 7.860E-03, 8.231E-03, 5.744E-03, 4.478E-03, 5.989E-03, 2.354E-03, 2.470E-03, 1.666E-03, 2.406E-03, 1.619E-03, 3.990E-04}, // TTMtt700.root
     { 1.777E-01, 4.152E+00, 3.134E+00, 2.525E+00, 1.672E+00, 1.475E+00, 1.314E+00, 1.246E+00, 6.182E-01, 1.445E+00, 1.502E+00, 1.481E+00, 1.335E+00, 1.172E+00, 1.077E+00, 1.056E+00, 1.078E+00, 1.128E+00, 1.163E+00, 1.187E+00, 1.210E+00, 1.241E+00, 1.257E+00, 1.269E+00, 1.274E+00, 1.272E+00, 1.275E+00, 1.269E+00, 1.274E+00, 1.251E+00, 1.221E+00, 1.172E+00, 1.108E+00, 1.038E+00, 9.686E-01, 9.096E-01, 8.677E-01, 8.350E-01, 7.882E-01, 7.517E-01, 7.598E-01, 7.926E-01, 8.621E-01, 9.573E-01, 1.095E+00, 1.256E+00, 1.418E+00, 1.493E+00, 1.519E+00, 1.461E+00, 1.337E+00, 1.155E+00, 9.482E-01, 7.499E-01, 5.699E-01, 4.113E-01, 2.900E-01, 1.983E-01, 1.379E-01, 9.650E-02, 6.894E-02, 5.091E-02, 3.854E-02, 3.005E-02, 2.404E-02, 1.723E-02, 1.252E-02, 1.087E-02, 9.655E-03, 8.873E-03, 8.288E-03, 8.132E-03, 7.512E-03, 7.948E-03, 6.459E-03, 5.342E-03, 5.533E-03, 5.494E-03, 6.272E-03, 5.718E-03}, // ttW.root
     { 1.706E-01, 3.530E+00, 3.856E+00, 2.444E+00, 1.560E+00, 1.559E+00, 1.305E+00, 1.151E+00, 6.161E-01, 1.462E+00, 1.460E+00, 1.477E+00, 1.332E+00, 1.169E+00, 1.089E+00, 1.053E+00, 1.081E+00, 1.127E+00, 1.168E+00, 1.189E+00, 1.213E+00, 1.239E+00, 1.260E+00, 1.269E+00, 1.271E+00, 1.271E+00, 1.267E+00, 1.268E+00, 1.277E+00, 1.252E+00, 1.224E+00, 1.168E+00, 1.112E+00, 1.035E+00, 9.726E-01, 9.155E-01, 8.653E-01, 8.328E-01, 7.885E-01, 7.499E-01, 7.569E-01, 7.910E-01, 8.622E-01, 9.600E-01, 1.097E+00, 1.263E+00, 1.419E+00, 1.488E+00, 1.534E+00, 1.459E+00, 1.336E+00, 1.153E+00, 9.516E-01, 7.507E-01, 5.691E-01, 4.092E-01, 2.881E-01, 1.979E-01, 1.371E-01, 9.644E-02, 6.921E-02, 5.098E-02, 3.832E-02, 3.012E-02, 2.400E-02, 1.712E-02, 1.263E-02, 1.081E-02, 9.730E-03, 8.891E-03, 8.303E-03, 7.981E-03, 7.828E-03, 7.682E-03, 5.988E-03, 5.577E-03, 5.647E-03, 5.452E-03, 5.620E-03, 6.340E-03}, // ttZ.root
     { 2.629E-04, 3.050E-02, 3.890E-02, 6.312E-02, 7.966E-02, 8.978E-02, 1.220E-01, 1.564E-01, 1.403E-01, 3.331E-01, 4.831E-01, 7.230E-01, 6.684E-01, 6.902E-01, 7.569E-01, 8.120E-01, 9.160E-01, 9.935E-01, 1.107E+00, 1.147E+00, 1.205E+00, 1.275E+00, 1.308E+00, 1.340E+00, 1.357E+00, 1.334E+00, 1.338E+00, 1.374E+00, 1.364E+00, 1.327E+00, 1.328E+00, 1.268E+00, 1.172E+00, 1.140E+00, 1.057E+00, 1.000E+00, 9.372E-01, 9.072E-01, 8.622E-01, 8.166E-01, 8.278E-01, 8.347E-01, 9.259E-01, 1.027E+00, 1.198E+00, 1.365E+00, 1.532E+00, 1.601E+00, 1.664E+00, 1.586E+00, 1.423E+00, 1.201E+00, 9.999E-01, 8.071E-01, 5.876E-01, 4.368E-01, 3.066E-01, 2.078E-01, 1.453E-01, 1.008E-01, 7.283E-02, 5.322E-02, 4.061E-02, 3.022E-02, 2.276E-02, 1.655E-02, 1.240E-02, 1.027E-02, 8.813E-03, 8.502E-03, 7.074E-03, 3.975E-03, 4.932E-03, 3.915E-03, 5.159E-03, 3.200E-03, 3.571E-03, 1.294E-03, 5.620E-04, 2.589E-04}, // ttH.root
     { 2.287E-04, 2.292E-02, 3.389E-02, 5.589E-02, 7.345E-02, 9.506E-02, 1.567E-01, 1.679E-01, 1.027E-01, 3.358E-01, 5.043E-01, 5.718E-01, 7.089E-01, 7.301E-01, 7.766E-01, 8.208E-01, 9.466E-01, 1.003E+00, 1.090E+00, 1.158E+00, 1.203E+00, 1.254E+00, 1.304E+00, 1.321E+00, 1.364E+00, 1.320E+00, 1.336E+00, 1.364E+00, 1.384E+00, 1.363E+00, 1.327E+00, 1.235E+00, 1.180E+00, 1.133E+00, 1.038E+00, 9.921E-01, 9.512E-01, 8.981E-01, 8.557E-01, 8.188E-01, 8.226E-01, 8.653E-01, 9.360E-01, 1.043E+00, 1.196E+00, 1.390E+00, 1.552E+00, 1.611E+00, 1.653E+00, 1.593E+00, 1.397E+00, 1.211E+00, 1.016E+00, 8.021E-01, 5.913E-01, 4.259E-01, 3.059E-01, 2.099E-01, 1.442E-01, 1.030E-01, 7.447E-02, 5.361E-02, 3.887E-02, 3.212E-02, 2.586E-02, 1.842E-02, 1.320E-02, 1.090E-02, 9.167E-03, 9.412E-03, 7.134E-03, 6.695E-03, 8.357E-03, 8.256E-03, 6.384E-03, 3.223E-03, 5.739E-03, 5.987E-03, 5.793E-03, 5.615E-04}, // WW.root
     { 2.869E-04, 9.374E-03, 3.689E-02, 6.702E-02, 9.232E-02, 1.800E-01, 1.922E-01, 2.219E-01, 1.089E-01, 4.104E-01, 4.199E-01, 6.427E-01, 7.047E-01, 7.547E-01, 7.360E-01, 7.494E-01, 8.440E-01, 1.009E+00, 1.084E+00, 1.138E+00, 1.231E+00, 1.263E+00, 1.297E+00, 1.322E+00, 1.345E+00, 1.347E+00, 1.332E+00, 1.359E+00, 1.385E+00, 1.368E+00, 1.298E+00, 1.255E+00, 1.197E+00, 1.131E+00, 1.070E+00, 1.008E+00, 9.473E-01, 9.046E-01, 8.477E-01, 8.320E-01, 8.104E-01, 8.451E-01, 9.316E-01, 1.064E+00, 1.210E+00, 1.362E+00, 1.547E+00, 1.642E+00, 1.651E+00, 1.610E+00, 1.433E+00, 1.247E+00, 1.025E+00, 7.690E-01, 5.969E-01, 4.246E-01, 3.122E-01, 2.133E-01, 1.483E-01, 1.042E-01, 7.078E-02, 5.239E-02, 3.758E-02, 2.855E-02, 2.451E-02, 1.824E-02, 1.194E-02, 1.108E-02, 7.717E-03, 8.780E-03, 4.887E-03, 4.952E-03, 4.224E-03, 8.586E-03, 3.532E-03, 1.218E-03, 8.432E-04, 5.514E-03, 2.907E-04, 2.155E-04}, // WZ.root
     { 4.546E-04, 2.534E-02, 3.661E-02, 2.158E-01, 1.437E-01, 1.406E-01, 2.281E-01, 2.785E-01, 1.595E-01, 4.560E-01, 5.475E-01, 7.024E-01, 7.455E-01, 7.130E-01, 6.330E-01, 7.235E-01, 8.012E-01, 9.118E-01, 1.052E+00, 1.104E+00, 1.171E+00, 1.251E+00, 1.300E+00, 1.325E+00, 1.326E+00, 1.344E+00, 1.353E+00, 1.343E+00, 1.334E+00, 1.345E+00, 1.325E+00, 1.264E+00, 1.187E+00, 1.128E+00, 1.053E+00, 9.933E-01, 9.439E-01, 9.083E-01, 8.603E-01, 8.265E-01, 8.285E-01, 8.341E-01, 9.475E-01, 1.005E+00, 1.205E+00, 1.319E+00, 1.557E+00, 1.555E+00, 1.611E+00, 1.592E+00, 1.327E+00, 1.226E+00, 1.024E+00, 7.230E-01, 5.492E-01, 4.278E-01, 3.085E-01, 2.009E-01, 1.457E-01, 9.861E-02, 7.158E-02, 5.429E-02, 4.119E-02, 2.955E-02, 2.219E-02, 1.474E-02, 1.221E-02, 1.157E-02, 9.763E-03, 9.035E-03, 8.900E-03, 8.299E-03, 8.596E-03, 8.830E-03, 6.079E-03, 5.265E-03, 6.533E-03, 1.267E-03, 2.455E-03, 9.727E-05}, // ZZ.root
     { 1.737E-01, 1.055E+01, 4.352E+00, 2.942E+00, 1.548E+00, 1.589E+00, 1.295E+00, 1.292E+00, 6.233E-01, 1.440E+00, 1.506E+00, 1.584E+00, 1.330E+00, 1.196E+00, 1.075E+00, 1.060E+00, 1.067E+00, 1.127E+00, 1.156E+00, 1.184E+00, 1.208E+00, 1.230E+00, 1.244E+00, 1.289E+00, 1.282E+00, 1.267E+00, 1.274E+00, 1.255E+00, 1.291E+00, 1.243E+00, 1.215E+00, 1.156E+00, 1.104E+00, 1.046E+00, 9.638E-01, 9.099E-01, 8.666E-01, 8.356E-01, 7.955E-01, 7.521E-01, 7.623E-01, 7.873E-01, 8.549E-01, 9.447E-01, 1.093E+00, 1.253E+00, 1.434E+00, 1.507E+00, 1.528E+00, 1.446E+00, 1.327E+00, 1.148E+00, 9.370E-01, 7.509E-01, 5.741E-01, 4.201E-01, 2.926E-01, 1.973E-01, 1.392E-01, 9.638E-02, 7.009E-02, 5.182E-02, 3.903E-02, 3.123E-02, 2.462E-02, 1.788E-02, 1.248E-02, 1.042E-02, 9.927E-03, 9.133E-03, 8.077E-03, 8.021E-03, 7.964E-03, 7.882E-03, 6.734E-03, 5.201E-03, 5.570E-03, 6.242E-03, 4.751E-03, 5.440E-03}, // TpTp700.root
     { 1.875E-01, 4.242E+00, 2.624E+00, 2.240E+00, 1.587E+00, 1.455E+00, 1.372E+00, 1.061E+00, 5.604E-01, 1.342E+00, 1.505E+00, 1.511E+00, 1.339E+00, 1.188E+00, 1.120E+00, 1.043E+00, 1.090E+00, 1.126E+00, 1.159E+00, 1.179E+00, 1.210E+00, 1.231E+00, 1.259E+00, 1.265E+00, 1.280E+00, 1.279E+00, 1.280E+00, 1.261E+00, 1.269E+00, 1.263E+00, 1.216E+00, 1.158E+00, 1.117E+00, 1.042E+00, 9.759E-01, 9.145E-01, 8.574E-01, 8.281E-01, 7.890E-01, 7.517E-01, 7.487E-01, 7.954E-01, 8.684E-01, 9.680E-01, 1.090E+00, 1.249E+00, 1.407E+00, 1.487E+00, 1.537E+00, 1.485E+00, 1.334E+00, 1.161E+00, 9.685E-01, 7.463E-01, 5.761E-01, 4.040E-01, 2.921E-01, 1.990E-01, 1.370E-01, 9.548E-02, 6.825E-02, 5.148E-02, 3.840E-02, 3.014E-02, 2.454E-02, 1.696E-02, 1.267E-02, 1.055E-02, 9.746E-03, 8.898E-03, 8.372E-03, 8.391E-03, 7.481E-03, 7.044E-03, 5.584E-03, 5.658E-03, 4.883E-03, 4.657E-03, 4.368E-03, 5.942E-03}, // TpTp1000.root
     { 2.315E-01, 3.072E+00, 2.850E+00, 2.379E+00, 1.814E+00, 1.427E+00, 1.502E+00, 1.198E+00, 6.637E-01, 1.478E+00, 1.465E+00, 1.593E+00, 1.334E+00, 1.162E+00, 1.089E+00, 1.052E+00, 1.074E+00, 1.133E+00, 1.161E+00, 1.196E+00, 1.212E+00, 1.235E+00, 1.260E+00, 1.276E+00, 1.285E+00, 1.278E+00, 1.270E+00, 1.259E+00, 1.272E+00, 1.265E+00, 1.203E+00, 1.151E+00, 1.119E+00, 1.035E+00, 9.633E-01, 9.135E-01, 8.644E-01, 8.412E-01, 7.865E-01, 7.494E-01, 7.635E-01, 7.874E-01, 8.475E-01, 9.577E-01, 1.104E+00, 1.274E+00, 1.419E+00, 1.490E+00, 1.524E+00, 1.496E+00, 1.342E+00, 1.169E+00, 9.458E-01, 7.514E-01, 5.769E-01, 4.126E-01, 2.925E-01, 2.000E-01, 1.368E-01, 9.616E-02, 6.762E-02, 5.076E-02, 3.781E-02, 2.879E-02, 2.332E-02, 1.717E-02, 1.265E-02, 1.079E-02, 9.486E-03, 9.464E-03, 8.739E-03, 8.339E-03, 8.351E-03, 7.462E-03, 7.104E-03, 5.085E-03, 4.805E-03, 6.677E-03, 5.575E-03, 5.164E-03}, // TpTp1100.root
     { 2.174E-01, 2.227E+00, 2.479E+00, 2.328E+00, 1.704E+00, 1.940E+00, 1.549E+00, 1.289E+00, 5.517E-01, 1.441E+00, 1.490E+00, 1.434E+00, 1.362E+00, 1.171E+00, 1.073E+00, 1.050E+00, 1.080E+00, 1.120E+00, 1.159E+00, 1.167E+00, 1.210E+00, 1.239E+00, 1.259E+00, 1.290E+00, 1.269E+00, 1.256E+00, 1.265E+00, 1.263E+00, 1.287E+00, 1.244E+00, 1.225E+00, 1.178E+00, 1.111E+00, 1.037E+00, 9.787E-01, 9.073E-01, 8.541E-01, 8.298E-01, 7.933E-01, 7.530E-01, 7.696E-01, 7.966E-01, 8.582E-01, 9.675E-01, 1.092E+00, 1.266E+00, 1.416E+00, 1.513E+00, 1.557E+00, 1.461E+00, 1.341E+00, 1.135E+00, 9.446E-01, 7.411E-01, 5.572E-01, 4.133E-01, 2.920E-01, 1.992E-01, 1.383E-01, 9.723E-02, 6.830E-02, 5.173E-02, 3.840E-02, 3.008E-02, 2.393E-02, 1.743E-02, 1.259E-02, 1.057E-02, 9.381E-03, 8.891E-03, 8.430E-03, 7.669E-03, 8.314E-03, 8.597E-03, 6.436E-03, 6.161E-03, 5.354E-03, 5.808E-03, 7.759E-03, 4.967E-03}, // TpTp1200.root
     { 1.572E-01, 2.823E+00, 3.055E+00, 2.295E+00, 1.478E+00, 1.373E+00, 1.264E+00, 1.132E+00, 6.411E-01, 1.457E+00, 1.430E+00, 1.465E+00, 1.362E+00, 1.154E+00, 1.093E+00, 1.051E+00, 1.061E+00, 1.118E+00, 1.178E+00, 1.191E+00, 1.207E+00, 1.267E+00, 1.251E+00, 1.274E+00, 1.267E+00, 1.288E+00, 1.274E+00, 1.276E+00, 1.269E+00, 1.253E+00, 1.226E+00, 1.163E+00, 1.108E+00, 1.031E+00, 9.792E-01, 9.190E-01, 8.577E-01, 8.364E-01, 7.998E-01, 7.505E-01, 7.587E-01, 7.996E-01, 8.608E-01, 9.585E-01, 1.094E+00, 1.239E+00, 1.403E+00, 1.476E+00, 1.520E+00, 1.470E+00, 1.327E+00, 1.124E+00, 9.653E-01, 7.601E-01, 5.713E-01, 4.137E-01, 2.874E-01, 1.990E-01, 1.410E-01, 9.522E-02, 6.876E-02, 4.921E-02, 3.726E-02, 2.983E-02, 2.373E-02, 1.658E-02, 1.257E-02, 1.075E-02, 9.609E-03, 8.271E-03, 8.340E-03, 8.770E-03, 7.378E-03, 7.303E-03, 5.912E-03, 5.315E-03, 7.372E-03, 6.092E-03, 5.033E-03, 5.305E-03}, // TpTp1300.root
     { 2.160E-01, 2.263E+00, 1.119E+01, 2.336E+00, 1.736E+00, 1.510E+00, 1.077E+00, 1.176E+00, 7.053E-01, 1.423E+00, 1.569E+00, 1.440E+00, 1.375E+00, 1.159E+00, 1.075E+00, 1.069E+00, 1.062E+00, 1.133E+00, 1.158E+00, 1.204E+00, 1.216E+00, 1.240E+00, 1.263E+00, 1.282E+00, 1.286E+00, 1.287E+00, 1.260E+00, 1.280E+00, 1.266E+00, 1.247E+00, 1.234E+00, 1.178E+00, 1.121E+00, 1.030E+00, 9.682E-01, 9.054E-01, 8.685E-01, 8.296E-01, 7.917E-01, 7.498E-01, 7.487E-01, 7.899E-01, 8.571E-01, 9.687E-01, 1.098E+00, 1.254E+00, 1.410E+00, 1.492E+00, 1.542E+00, 1.455E+00, 1.350E+00, 1.139E+00, 9.516E-01, 7.482E-01, 5.658E-01, 4.106E-01, 2.926E-01, 1.957E-01, 1.395E-01, 9.392E-02, 6.780E-02, 5.034E-02, 3.757E-02, 3.000E-02, 2.382E-02, 1.738E-02, 1.216E-02, 1.105E-02, 9.388E-03, 8.357E-03, 8.885E-03, 8.099E-03, 7.050E-03, 6.724E-03, 6.228E-03, 4.828E-03, 5.222E-03, 5.245E-03, 7.617E-03, 7.289E-03}, // TpTp1400.root
     { 2.423E-01, 4.315E+00, 2.464E+00, 2.864E+00, 1.174E+00, 1.485E+00, 1.268E+00, 1.222E+00, 5.845E-01, 1.453E+00, 1.426E+00, 1.488E+00, 1.321E+00, 1.167E+00, 1.076E+00, 1.052E+00, 1.066E+00, 1.122E+00, 1.151E+00, 1.206E+00, 1.209E+00, 1.239E+00, 1.250E+00, 1.286E+00, 1.282E+00, 1.269E+00, 1.251E+00, 1.263E+00, 1.273E+00, 1.269E+00, 1.204E+00, 1.178E+00, 1.108E+00, 1.043E+00, 9.572E-01, 9.212E-01, 8.694E-01, 8.428E-01, 7.893E-01, 7.578E-01, 7.580E-01, 7.940E-01, 8.664E-01, 9.559E-01, 1.096E+00, 1.248E+00, 1.412E+00, 1.500E+00, 1.509E+00, 1.463E+00, 1.369E+00, 1.149E+00, 9.606E-01, 7.550E-01, 5.693E-01, 4.126E-01, 2.883E-01, 1.976E-01, 1.379E-01, 9.559E-02, 6.876E-02, 5.059E-02, 3.842E-02, 3.008E-02, 2.387E-02, 1.667E-02, 1.304E-02, 1.021E-02, 1.031E-02, 8.361E-03, 8.001E-03, 8.146E-03, 7.446E-03, 8.348E-03, 5.815E-03, 4.387E-03, 4.728E-03, 6.252E-03, 4.515E-03, 5.561E-03}, // TpTp1500.root
     { 1.617E-01, 4.064E+00, 2.742E+00, 2.266E+00, 1.559E+00, 1.377E+00, 1.402E+00, 1.178E+00, 6.902E-01, 1.501E+00, 1.659E+00, 1.587E+00, 1.368E+00, 1.170E+00, 1.114E+00, 1.061E+00, 1.092E+00, 1.130E+00, 1.172E+00, 1.207E+00, 1.183E+00, 1.234E+00, 1.261E+00, 1.254E+00, 1.287E+00, 1.263E+00, 1.272E+00, 1.246E+00, 1.266E+00, 1.262E+00, 1.218E+00, 1.166E+00, 1.121E+00, 1.039E+00, 9.762E-01, 8.993E-01, 8.753E-01, 8.349E-01, 7.893E-01, 7.575E-01, 7.539E-01, 7.984E-01, 8.531E-01, 9.740E-01, 1.119E+00, 1.251E+00, 1.404E+00, 1.488E+00, 1.556E+00, 1.446E+00, 1.355E+00, 1.132E+00, 9.286E-01, 7.537E-01, 5.683E-01, 4.106E-01, 2.881E-01, 1.966E-01, 1.355E-01, 9.763E-02, 6.776E-02, 5.132E-02, 3.890E-02, 2.995E-02, 2.371E-02, 1.746E-02, 1.324E-02, 1.051E-02, 9.834E-03, 8.969E-03, 7.766E-03, 7.762E-03, 8.075E-03, 9.524E-03, 8.243E-03, 5.045E-03, 5.098E-03, 4.711E-03, 4.371E-03, 6.547E-03}, // TpTp1600.root
     { 3.073E-01, 2.023E+00, 2.628E+00, 2.467E+00, 1.432E+00, 1.146E+00, 1.139E+00, 1.750E+00, 5.444E-01, 1.307E+00, 1.464E+00, 1.483E+00, 1.358E+00, 1.188E+00, 1.069E+00, 1.036E+00, 1.110E+00, 1.127E+00, 1.156E+00, 1.209E+00, 1.195E+00, 1.237E+00, 1.262E+00, 1.289E+00, 1.287E+00, 1.264E+00, 1.262E+00, 1.249E+00, 1.281E+00, 1.250E+00, 1.228E+00, 1.186E+00, 1.097E+00, 1.033E+00, 9.705E-01, 9.052E-01, 8.553E-01, 8.536E-01, 7.986E-01, 7.560E-01, 7.652E-01, 8.156E-01, 8.463E-01, 9.698E-01, 1.088E+00, 1.243E+00, 1.417E+00, 1.469E+00, 1.544E+00, 1.439E+00, 1.331E+00, 1.134E+00, 9.276E-01, 7.655E-01, 5.659E-01, 4.075E-01, 2.903E-01, 1.991E-01, 1.353E-01, 9.565E-02, 6.819E-02, 5.082E-02, 3.936E-02, 2.947E-02, 2.426E-02, 1.780E-02, 1.251E-02, 1.031E-02, 1.034E-02, 9.703E-03, 8.115E-03, 7.457E-03, 6.907E-03, 6.714E-03, 5.733E-03, 7.032E-03, 5.893E-03, 4.560E-03, 7.615E-03, 4.148E-03}, // TpTp1700.root
     { 1.575E-01, 2.376E+00, 5.511E+00, 4.140E+00, 2.222E+00, 1.022E+00, 1.414E+00, 1.012E+00, 5.570E-01, 1.627E+00, 1.349E+00, 1.507E+00, 1.347E+00, 1.251E+00, 1.103E+00, 1.054E+00, 1.092E+00, 1.122E+00, 1.182E+00, 1.167E+00, 1.212E+00, 1.234E+00, 1.264E+00, 1.287E+00, 1.260E+00, 1.284E+00, 1.277E+00, 1.250E+00, 1.300E+00, 1.262E+00, 1.246E+00, 1.159E+00, 1.099E+00, 1.041E+00, 9.627E-01, 9.212E-01, 8.749E-01, 8.307E-01, 7.929E-01, 7.360E-01, 7.686E-01, 7.892E-01, 8.466E-01, 9.500E-01, 1.047E+00, 1.288E+00, 1.426E+00, 1.505E+00, 1.517E+00, 1.455E+00, 1.287E+00, 1.121E+00, 9.316E-01, 7.538E-01, 5.805E-01, 4.069E-01, 2.963E-01, 1.982E-01, 1.402E-01, 9.389E-02, 6.983E-02, 5.031E-02, 3.893E-02, 3.000E-02, 2.573E-02, 1.678E-02, 1.244E-02, 1.088E-02, 9.356E-03, 8.698E-03, 8.022E-03, 6.875E-03, 1.100E-02, 9.955E-03, 7.337E-03, 4.677E-03, 6.427E-03, 6.148E-03, 8.214E-03, 3.827E-03}, // TpTp1800.root
     { 1.870E-01, 4.744E+00, 3.217E+00, 2.383E+00, 1.802E+00, 1.486E+00, 1.329E+00, 1.205E+00, 6.102E-01, 1.495E+00, 1.516E+00, 1.478E+00, 1.319E+00, 1.164E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.130E+00, 1.165E+00, 1.189E+00, 1.212E+00, 1.236E+00, 1.258E+00, 1.271E+00, 1.271E+00, 1.272E+00, 1.272E+00, 1.268E+00, 1.277E+00, 1.253E+00, 1.221E+00, 1.169E+00, 1.109E+00, 1.039E+00, 9.688E-01, 9.133E-01, 8.658E-01, 8.371E-01, 7.900E-01, 7.512E-01, 7.587E-01, 7.925E-01, 8.574E-01, 9.586E-01, 1.093E+00, 1.257E+00, 1.420E+00, 1.493E+00, 1.527E+00, 1.462E+00, 1.338E+00, 1.155E+00, 9.495E-01, 7.493E-01, 5.703E-01, 4.107E-01, 2.901E-01, 1.994E-01, 1.376E-01, 9.651E-02, 6.895E-02, 5.073E-02, 3.841E-02, 2.999E-02, 2.412E-02, 1.701E-02, 1.244E-02, 1.072E-02, 9.630E-03, 8.829E-03, 8.312E-03, 8.101E-03, 7.724E-03, 7.905E-03, 6.299E-03, 5.287E-03, 5.476E-03, 5.776E-03, 5.866E-03, 6.320E-03}, // WJ1200.root
     { 1.913E-01, 4.255E+00, 3.444E+00, 2.481E+00, 1.640E+00, 1.531E+00, 1.288E+00, 1.270E+00, 5.997E-01, 1.442E+00, 1.477E+00, 1.476E+00, 1.330E+00, 1.169E+00, 1.083E+00, 1.051E+00, 1.078E+00, 1.126E+00, 1.166E+00, 1.188E+00, 1.211E+00, 1.238E+00, 1.256E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.271E+00, 1.267E+00, 1.274E+00, 1.254E+00, 1.220E+00, 1.167E+00, 1.113E+00, 1.037E+00, 9.688E-01, 9.129E-01, 8.681E-01, 8.336E-01, 7.865E-01, 7.516E-01, 7.576E-01, 7.948E-01, 8.593E-01, 9.561E-01, 1.097E+00, 1.258E+00, 1.421E+00, 1.492E+00, 1.534E+00, 1.461E+00, 1.341E+00, 1.156E+00, 9.519E-01, 7.507E-01, 5.693E-01, 4.101E-01, 2.896E-01, 1.981E-01, 1.374E-01, 9.658E-02, 6.937E-02, 5.074E-02, 3.867E-02, 2.989E-02, 2.413E-02, 1.713E-02, 1.250E-02, 1.076E-02, 9.502E-03, 8.767E-03, 8.258E-03, 8.063E-03, 7.855E-03, 7.777E-03, 6.306E-03, 5.442E-03, 5.528E-03, 5.516E-03, 6.168E-03, 5.712E-03}, // WJ200.root
     { 1.898E-01, 4.165E+00, 3.239E+00, 2.648E+00, 1.610E+00, 1.494E+00, 1.289E+00, 1.238E+00, 6.235E-01, 1.438E+00, 1.486E+00, 1.484E+00, 1.339E+00, 1.165E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.129E+00, 1.168E+00, 1.188E+00, 1.213E+00, 1.239E+00, 1.262E+00, 1.272E+00, 1.272E+00, 1.269E+00, 1.273E+00, 1.266E+00, 1.276E+00, 1.250E+00, 1.221E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.687E-01, 9.137E-01, 8.687E-01, 8.352E-01, 7.870E-01, 7.480E-01, 7.602E-01, 7.922E-01, 8.591E-01, 9.607E-01, 1.091E+00, 1.255E+00, 1.415E+00, 1.496E+00, 1.528E+00, 1.460E+00, 1.339E+00, 1.154E+00, 9.493E-01, 7.497E-01, 5.703E-01, 4.105E-01, 2.896E-01, 1.985E-01, 1.373E-01, 9.672E-02, 6.940E-02, 5.067E-02, 3.834E-02, 3.009E-02, 2.403E-02, 1.718E-02, 1.255E-02, 1.087E-02, 9.529E-03, 8.865E-03, 8.370E-03, 7.970E-03, 7.921E-03, 7.850E-03, 6.155E-03, 5.393E-03, 5.518E-03, 5.859E-03, 5.714E-03, 6.418E-03}, // WJ2500.root
     { 1.897E-01, 3.957E+00, 3.856E+00, 2.684E+00, 1.643E+00, 1.480E+00, 1.304E+00, 1.284E+00, 6.124E-01, 1.434E+00, 1.497E+00, 1.483E+00, 1.326E+00, 1.166E+00, 1.080E+00, 1.051E+00, 1.074E+00, 1.126E+00, 1.163E+00, 1.187E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.268E+00, 1.274E+00, 1.274E+00, 1.270E+00, 1.269E+00, 1.277E+00, 1.252E+00, 1.224E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.698E-01, 9.114E-01, 8.652E-01, 8.348E-01, 7.895E-01, 7.498E-01, 7.574E-01, 7.921E-01, 8.594E-01, 9.566E-01, 1.096E+00, 1.260E+00, 1.419E+00, 1.496E+00, 1.534E+00, 1.465E+00, 1.340E+00, 1.157E+00, 9.516E-01, 7.506E-01, 5.693E-01, 4.110E-01, 2.894E-01, 1.974E-01, 1.380E-01, 9.660E-02, 6.948E-02, 5.088E-02, 3.837E-02, 2.965E-02, 2.417E-02, 1.699E-02, 1.248E-02, 1.080E-02, 9.539E-03, 8.775E-03, 8.265E-03, 8.058E-03, 7.837E-03, 7.898E-03, 6.202E-03, 5.428E-03, 5.554E-03, 5.352E-03, 5.705E-03, 6.037E-03}, // WJ400.root
     { 1.899E-01, 3.543E+00, 3.519E+00, 2.642E+00, 1.581E+00, 1.495E+00, 1.296E+00, 1.289E+00, 6.150E-01, 1.486E+00, 1.474E+00, 1.479E+00, 1.324E+00, 1.167E+00, 1.074E+00, 1.054E+00, 1.080E+00, 1.133E+00, 1.165E+00, 1.186E+00, 1.215E+00, 1.238E+00, 1.261E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.268E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.223E+00, 1.171E+00, 1.109E+00, 1.036E+00, 9.682E-01, 9.106E-01, 8.671E-01, 8.343E-01, 7.894E-01, 7.523E-01, 7.561E-01, 7.949E-01, 8.588E-01, 9.588E-01, 1.095E+00, 1.253E+00, 1.420E+00, 1.494E+00, 1.534E+00, 1.461E+00, 1.336E+00, 1.154E+00, 9.528E-01, 7.531E-01, 5.697E-01, 4.117E-01, 2.903E-01, 1.985E-01, 1.375E-01, 9.617E-02, 6.911E-02, 5.078E-02, 3.842E-02, 2.983E-02, 2.402E-02, 1.707E-02, 1.242E-02, 1.086E-02, 9.659E-03, 8.759E-03, 8.298E-03, 8.003E-03, 7.673E-03, 7.920E-03, 6.423E-03, 5.314E-03, 5.516E-03, 5.349E-03, 5.832E-03, 5.663E-03}, // WJ600.root
     { 1.711E-01, 3.600E+00, 3.097E+00, 2.605E+00, 1.589E+00, 1.439E+00, 1.297E+00, 1.250E+00, 6.091E-01, 1.445E+00, 1.499E+00, 1.471E+00, 1.332E+00, 1.165E+00, 1.075E+00, 1.055E+00, 1.080E+00, 1.127E+00, 1.166E+00, 1.190E+00, 1.212E+00, 1.240E+00, 1.261E+00, 1.271E+00, 1.275E+00, 1.275E+00, 1.271E+00, 1.265E+00, 1.274E+00, 1.250E+00, 1.222E+00, 1.170E+00, 1.106E+00, 1.038E+00, 9.693E-01, 9.130E-01, 8.674E-01, 8.346E-01, 7.890E-01, 7.505E-01, 7.591E-01, 7.919E-01, 8.587E-01, 9.597E-01, 1.092E+00, 1.260E+00, 1.417E+00, 1.489E+00, 1.528E+00, 1.462E+00, 1.335E+00, 1.156E+00, 9.473E-01, 7.489E-01, 5.693E-01, 4.120E-01, 2.903E-01, 1.985E-01, 1.383E-01, 9.635E-02, 6.923E-02, 5.101E-02, 3.853E-02, 2.984E-02, 2.410E-02, 1.704E-02, 1.249E-02, 1.076E-02, 9.659E-03, 8.827E-03, 8.296E-03, 7.973E-03, 7.932E-03, 8.048E-03, 6.384E-03, 5.142E-03, 5.646E-03, 5.484E-03, 5.501E-03, 6.078E-03} // WJ800.root
};

//    pileupweightUp = {  // 66016 ub
//      {2.627E-04, 2.950E-02, 3.845E-02, 6.129E-02, 7.067E-02, 1.038E-01, 1.276E-01, 1.488E-01, 1.050E-01, 3.197E-01, 4.811E-01, 6.165E-01, 6.699E-01, 7.030E-01, 7.332E-01, 7.987E-01, 8.958E-01, 9.917E-01, 1.083E+00, 1.145E+00, 1.204E+00, 1.252E+00, 1.292E+00, 1.325E+00, 1.342E+00, 1.346E+00, 1.351E+00, 1.358E+00, 1.368E+00, 1.355E+00, 1.323E+00, 1.260E+00, 1.197E+00, 1.133E+00, 1.057E+00, 9.937E-01, 9.487E-01, 9.072E-01, 8.591E-01, 8.169E-01, 8.251E-01, 8.610E-01, 9.336E-01, 1.047E+00, 1.193E+00, 1.356E+00, 1.538E+00, 1.612E+00, 1.625E+00, 1.577E+00, 1.402E+00, 1.210E+00, 1.006E+00, 7.882E-01, 5.993E-01, 4.287E-01, 3.047E-01, 2.107E-01, 1.456E-01, 1.024E-01, 7.315E-02, 5.335E-02, 4.065E-02, 3.040E-02, 2.403E-02, 1.784E-02, 1.262E-02, 1.095E-02, 9.353E-03, 8.596E-03, 7.320E-03, 6.155E-03, 6.241E-03, 4.710E-03, 3.440E-03, 2.819E-03, 2.363E-03, 1.809E-03, 1.251E-03, 4.036E-04},
//      {3.544E-04, 3.998E-02, 4.526E-02, 7.801E-02, 9.146E-02, 1.097E-01, 1.527E-01, 2.427E-01, 1.278E-01, 4.256E-01, 5.532E-01, 6.663E-01, 6.732E-01, 7.100E-01, 7.715E-01, 8.042E-01, 9.015E-01, 9.917E-01, 1.066E+00, 1.131E+00, 1.189E+00, 1.253E+00, 1.282E+00, 1.315E+00, 1.325E+00, 1.339E+00, 1.339E+00, 1.339E+00, 1.362E+00, 1.336E+00, 1.297E+00, 1.239E+00, 1.190E+00, 1.117E+00, 1.039E+00, 9.847E-01, 9.359E-01, 8.988E-01, 8.460E-01, 8.122E-01, 8.128E-01, 8.503E-01, 9.144E-01, 1.020E+00, 1.173E+00, 1.348E+00, 1.525E+00, 1.596E+00, 1.638E+00, 1.565E+00, 1.346E+00, 1.213E+00, 9.796E-01, 7.891E-01, 5.957E-01, 4.270E-01, 3.022E-01, 2.079E-01, 1.453E-01, 1.013E-01, 7.242E-02, 5.264E-02, 4.040E-02, 3.102E-02, 2.399E-02, 1.754E-02, 1.216E-02, 1.027E-02, 9.501E-03, 8.830E-03, 7.677E-03, 5.254E-03, 6.172E-03, 5.941E-03, 3.630E-03, 4.188E-03, 2.190E-03, 1.532E-03, 1.240E-03, 5.375E-04},
//      {1.749E-01, 4.172E+00, 3.462E+00, 2.677E+00, 1.657E+00, 1.475E+00, 1.255E+00, 1.247E+00, 6.000E-01, 1.423E+00, 1.498E+00, 1.492E+00, 1.325E+00, 1.164E+00, 1.082E+00, 1.052E+00, 1.083E+00, 1.127E+00, 1.163E+00, 1.191E+00, 1.212E+00, 1.241E+00, 1.255E+00, 1.270E+00, 1.274E+00, 1.273E+00, 1.272E+00, 1.268E+00, 1.278E+00, 1.250E+00, 1.223E+00, 1.171E+00, 1.111E+00, 1.036E+00, 9.706E-01, 9.104E-01, 8.681E-01, 8.332E-01, 7.862E-01, 7.510E-01, 7.602E-01, 7.926E-01, 8.584E-01, 9.577E-01, 1.096E+00, 1.256E+00, 1.416E+00, 1.494E+00, 1.526E+00, 1.468E+00, 1.336E+00, 1.152E+00, 9.528E-01, 7.484E-01, 5.701E-01, 4.122E-01, 2.880E-01, 1.984E-01, 1.374E-01, 9.694E-02, 6.917E-02, 5.072E-02, 3.857E-02, 2.990E-02, 2.407E-02, 1.711E-02, 1.255E-02, 1.081E-02, 9.624E-03, 8.906E-03, 8.153E-03, 8.132E-03, 7.845E-03, 7.748E-03, 6.232E-03, 5.267E-03, 5.608E-03, 6.070E-03, 6.121E-03, 6.164E-03},
//      {1.672E-01, 4.002E+00, 3.617E+00, 2.548E+00, 1.509E+00, 1.493E+00, 1.296E+00, 1.240E+00, 6.044E-01, 1.455E+00, 1.498E+00, 1.488E+00, 1.340E+00, 1.174E+00, 1.086E+00, 1.052E+00, 1.083E+00, 1.128E+00, 1.168E+00, 1.181E+00, 1.205E+00, 1.236E+00, 1.259E+00, 1.272E+00, 1.271E+00, 1.272E+00, 1.271E+00, 1.267E+00, 1.278E+00, 1.251E+00, 1.219E+00, 1.164E+00, 1.109E+00, 1.038E+00, 9.689E-01, 9.156E-01, 8.645E-01, 8.359E-01, 7.875E-01, 7.518E-01, 7.621E-01, 7.939E-01, 8.594E-01, 9.634E-01, 1.096E+00, 1.255E+00, 1.424E+00, 1.511E+00, 1.535E+00, 1.457E+00, 1.342E+00, 1.153E+00, 9.464E-01, 7.538E-01, 5.673E-01, 4.094E-01, 2.882E-01, 1.995E-01, 1.377E-01, 9.630E-02, 6.899E-02, 5.090E-02, 3.856E-02, 2.996E-02, 2.428E-02, 1.692E-02, 1.250E-02, 1.081E-02, 9.817E-03, 8.680E-03, 8.324E-03, 8.295E-03, 7.672E-03, 7.872E-03, 6.039E-03, 5.129E-03, 5.624E-03, 5.494E-03, 6.660E-03, 5.473E-03},
//      {2.758E-04, 2.979E-02, 4.481E-02, 7.384E-02, 6.863E-02, 1.116E-01, 1.301E-01, 1.552E-01, 1.058E-01, 3.333E-01, 5.015E-01, 6.410E-01, 6.712E-01, 7.089E-01, 7.387E-01, 8.027E-01, 9.054E-01, 9.982E-01, 1.086E+00, 1.149E+00, 1.200E+00, 1.257E+00, 1.302E+00, 1.324E+00, 1.342E+00, 1.344E+00, 1.353E+00, 1.352E+00, 1.366E+00, 1.349E+00, 1.320E+00, 1.250E+00, 1.194E+00, 1.130E+00, 1.055E+00, 9.941E-01, 9.461E-01, 9.058E-01, 8.535E-01, 8.164E-01, 8.234E-01, 8.614E-01, 9.270E-01, 1.046E+00, 1.190E+00, 1.357E+00, 1.530E+00, 1.580E+00, 1.623E+00, 1.552E+00, 1.396E+00, 1.203E+00, 9.963E-01, 7.804E-01, 5.990E-01, 4.260E-01, 3.034E-01, 2.091E-01, 1.455E-01, 1.023E-01, 7.260E-02, 5.320E-02, 4.007E-02, 3.055E-02, 2.303E-02, 1.753E-02, 1.254E-02, 1.085E-02, 8.972E-03, 8.785E-03, 7.276E-03, 6.235E-03, 5.168E-03, 6.401E-03, 3.540E-03, 3.876E-03, 2.529E-03, 1.391E-03, 1.006E-03, 5.000E-04},
//      {2.494E-04, 3.158E-02, 3.862E-02, 5.765E-02, 7.191E-02, 1.117E-01, 1.001E-01, 1.299E-01, 1.084E-01, 3.222E-01, 4.813E-01, 6.202E-01, 6.505E-01, 7.113E-01, 7.297E-01, 7.877E-01, 9.025E-01, 1.013E+00, 1.094E+00, 1.148E+00, 1.211E+00, 1.252E+00, 1.304E+00, 1.336E+00, 1.347E+00, 1.356E+00, 1.354E+00, 1.365E+00, 1.369E+00, 1.351E+00, 1.328E+00, 1.258E+00, 1.202E+00, 1.130E+00, 1.059E+00, 9.882E-01, 9.494E-01, 9.124E-01, 8.601E-01, 8.192E-01, 8.230E-01, 8.637E-01, 9.387E-01, 1.048E+00, 1.188E+00, 1.354E+00, 1.540E+00, 1.616E+00, 1.634E+00, 1.572E+00, 1.388E+00, 1.224E+00, 1.001E+00, 7.875E-01, 5.981E-01, 4.347E-01, 3.054E-01, 2.086E-01, 1.461E-01, 1.012E-01, 7.329E-02, 5.338E-02, 4.046E-02, 3.013E-02, 2.390E-02, 1.758E-02, 1.241E-02, 1.099E-02, 9.904E-03, 8.385E-03, 7.029E-03, 5.092E-03, 5.896E-03, 4.427E-03, 3.156E-03, 3.957E-03, 2.318E-03, 2.368E-03, 1.121E-03, 5.284E-04},
//      {2.960E-04, 4.661E-02, 5.142E-02, 7.836E-02, 7.650E-02, 1.158E-01, 1.384E-01, 1.598E-01, 1.298E-01, 4.088E-01, 5.108E-01, 6.759E-01, 7.111E-01, 7.069E-01, 7.569E-01, 8.221E-01, 9.024E-01, 9.951E-01, 1.083E+00, 1.143E+00, 1.196E+00, 1.243E+00, 1.290E+00, 1.319E+00, 1.335E+00, 1.333E+00, 1.349E+00, 1.351E+00, 1.349E+00, 1.339E+00, 1.312E+00, 1.253E+00, 1.187E+00, 1.126E+00, 1.046E+00, 9.803E-01, 9.405E-01, 9.074E-01, 8.515E-01, 8.155E-01, 8.172E-01, 8.621E-01, 9.268E-01, 1.040E+00, 1.184E+00, 1.351E+00, 1.528E+00, 1.601E+00, 1.645E+00, 1.555E+00, 1.395E+00, 1.202E+00, 1.009E+00, 7.834E-01, 5.907E-01, 4.264E-01, 3.005E-01, 2.080E-01, 1.442E-01, 1.016E-01, 7.377E-02, 5.274E-02, 4.028E-02, 2.943E-02, 2.345E-02, 1.733E-02, 1.304E-02, 1.089E-02, 9.218E-03, 8.375E-03, 7.196E-03, 4.961E-03, 5.212E-03, 4.817E-03, 2.602E-03, 3.627E-03, 2.491E-03, 2.361E-03, 6.611E-04, 6.415E-04},
//      {2.894E-04, 4.360E-02, 5.014E-02, 6.912E-02, 8.141E-02, 1.445E-01, 1.405E-01, 1.480E-01, 1.039E-01, 3.417E-01, 4.570E-01, 6.214E-01, 6.927E-01, 6.701E-01, 6.820E-01, 8.060E-01, 8.304E-01, 9.961E-01, 1.076E+00, 1.131E+00, 1.193E+00, 1.219E+00, 1.294E+00, 1.326E+00, 1.323E+00, 1.350E+00, 1.362E+00, 1.348E+00, 1.360E+00, 1.339E+00, 1.311E+00, 1.262E+00, 1.185E+00, 1.131E+00, 1.058E+00, 1.002E+00, 9.544E-01, 9.065E-01, 8.609E-01, 8.214E-01, 8.346E-01, 8.601E-01, 9.398E-01, 1.059E+00, 1.200E+00, 1.364E+00, 1.510E+00, 1.641E+00, 1.590E+00, 1.542E+00, 1.397E+00, 1.237E+00, 1.003E+00, 8.001E-01, 5.921E-01, 4.271E-01, 3.083E-01, 2.139E-01, 1.458E-01, 1.017E-01, 7.216E-02, 5.370E-02, 4.107E-02, 3.045E-02, 2.474E-02, 1.765E-02, 1.298E-02, 1.070E-02, 9.453E-03, 9.417E-03, 7.668E-03, 4.481E-03, 3.087E-03, 6.682E-03, 3.068E-03, 1.882E-03, 1.948E-03, 5.821E-03, 1.565E-03, 3.780E-04},
//      {1.800E-01, 3.572E+00, 3.238E+00, 2.501E+00, 1.587E+00, 1.524E+00, 1.259E+00, 1.234E+00, 6.249E-01, 1.469E+00, 1.489E+00, 1.493E+00, 1.332E+00, 1.168E+00, 1.077E+00, 1.050E+00, 1.085E+00, 1.129E+00, 1.164E+00, 1.190E+00, 1.213E+00, 1.238E+00, 1.258E+00, 1.270E+00, 1.275E+00, 1.274E+00, 1.272E+00, 1.267E+00, 1.276E+00, 1.252E+00, 1.223E+00, 1.169E+00, 1.110E+00, 1.035E+00, 9.696E-01, 9.107E-01, 8.679E-01, 8.329E-01, 7.873E-01, 7.513E-01, 7.580E-01, 7.947E-01, 8.584E-01, 9.582E-01, 1.093E+00, 1.255E+00, 1.420E+00, 1.496E+00, 1.525E+00, 1.468E+00, 1.336E+00, 1.156E+00, 9.496E-01, 7.491E-01, 5.688E-01, 4.106E-01, 2.897E-01, 1.987E-01, 1.380E-01, 9.650E-02, 6.927E-02, 5.094E-02, 3.836E-02, 2.994E-02, 2.412E-02, 1.694E-02, 1.244E-02, 1.079E-02, 9.658E-03, 8.864E-03, 8.303E-03, 8.066E-03, 7.846E-03, 7.957E-03, 6.113E-03, 5.381E-03, 5.472E-03, 5.358E-03, 5.970E-03, 6.237E-03},
//      {2.605E-04, 2.631E-02, 3.681E-02, 4.785E-02, 7.677E-02, 1.316E-01, 9.301E-02, 1.018E-01, 1.079E-01, 4.031E-01, 4.383E-01, 6.138E-01, 6.870E-01, 7.113E-01, 7.262E-01, 8.072E-01, 8.834E-01, 9.917E-01, 1.070E+00, 1.134E+00, 1.185E+00, 1.256E+00, 1.307E+00, 1.338E+00, 1.329E+00, 1.353E+00, 1.370E+00, 1.381E+00, 1.371E+00, 1.359E+00, 1.336E+00, 1.252E+00, 1.208E+00, 1.133E+00, 1.066E+00, 9.925E-01, 9.398E-01, 9.187E-01, 8.526E-01, 8.198E-01, 8.374E-01, 8.628E-01, 9.381E-01, 1.055E+00, 1.208E+00, 1.350E+00, 1.567E+00, 1.627E+00, 1.624E+00, 1.558E+00, 1.401E+00, 1.214E+00, 1.002E+00, 7.880E-01, 5.921E-01, 4.393E-01, 3.076E-01, 2.087E-01, 1.429E-01, 1.036E-01, 7.355E-02, 5.130E-02, 3.955E-02, 3.146E-02, 2.366E-02, 1.726E-02, 1.258E-02, 1.092E-02, 1.015E-02, 9.365E-03, 6.013E-03, 3.590E-03, 4.496E-03, 4.837E-03, 6.140E-03, 4.341E-03, 1.343E-03, 4.228E-03, 5.226E-04, 7.545E-04},
//      {2.607E-04, 2.222E-02, 4.369E-02, 5.655E-02, 7.639E-02, 9.580E-02, 1.022E-01, 1.921E-01, 1.312E-01, 3.306E-01, 5.204E-01, 6.816E-01, 6.607E-01, 6.635E-01, 7.260E-01, 7.893E-01, 9.209E-01, 1.004E+00, 1.098E+00, 1.158E+00, 1.206E+00, 1.268E+00, 1.289E+00, 1.328E+00, 1.341E+00, 1.340E+00, 1.358E+00, 1.349E+00, 1.383E+00, 1.356E+00, 1.331E+00, 1.242E+00, 1.211E+00, 1.133E+00, 1.049E+00, 9.995E-01, 9.512E-01, 9.076E-01, 8.579E-01, 8.202E-01, 8.377E-01, 8.753E-01, 9.439E-01, 1.041E+00, 1.193E+00, 1.341E+00, 1.525E+00, 1.574E+00, 1.593E+00, 1.569E+00, 1.366E+00, 1.206E+00, 1.021E+00, 7.956E-01, 6.034E-01, 4.278E-01, 3.102E-01, 2.086E-01, 1.461E-01, 1.031E-01, 7.383E-02, 5.028E-02, 4.112E-02, 3.090E-02, 2.154E-02, 1.732E-02, 1.306E-02, 1.068E-02, 9.153E-03, 8.133E-03, 6.713E-03, 5.319E-03, 3.989E-03, 8.444E-03, 1.941E-03, 4.946E-03, 2.976E-03, 3.784E-03, 5.910E-04, 2.521E-04},
//      {1.780E-01, 5.124E+00, 3.340E+00, 2.752E+00, 1.532E+00, 1.502E+00, 1.283E+00, 1.247E+00, 6.408E-01, 1.423E+00, 1.493E+00, 1.501E+00, 1.316E+00, 1.161E+00, 1.081E+00, 1.048E+00, 1.081E+00, 1.129E+00, 1.170E+00, 1.190E+00, 1.214E+00, 1.239E+00, 1.258E+00, 1.269E+00, 1.274E+00, 1.270E+00, 1.265E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.220E+00, 1.173E+00, 1.111E+00, 1.039E+00, 9.675E-01, 9.125E-01, 8.687E-01, 8.348E-01, 7.882E-01, 7.476E-01, 7.592E-01, 7.946E-01, 8.570E-01, 9.614E-01, 1.095E+00, 1.257E+00, 1.418E+00, 1.502E+00, 1.533E+00, 1.460E+00, 1.343E+00, 1.154E+00, 9.496E-01, 7.457E-01, 5.701E-01, 4.112E-01, 2.882E-01, 1.982E-01, 1.382E-01, 9.659E-02, 6.902E-02, 5.065E-02, 3.841E-02, 3.010E-02, 2.401E-02, 1.713E-02, 1.250E-02, 1.079E-02, 9.623E-03, 8.901E-03, 8.297E-03, 8.180E-03, 7.698E-03, 7.869E-03, 6.500E-03, 5.429E-03, 5.453E-03, 5.933E-03, 5.511E-03, 5.550E-03},
//      {1.829E-01, 3.581E+00, 3.653E+00, 2.510E+00, 1.605E+00, 1.528E+00, 1.253E+00, 1.264E+00, 6.156E-01, 1.469E+00, 1.500E+00, 1.473E+00, 1.340E+00, 1.166E+00, 1.074E+00, 1.057E+00, 1.075E+00, 1.127E+00, 1.169E+00, 1.188E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.272E+00, 1.272E+00, 1.272E+00, 1.270E+00, 1.266E+00, 1.275E+00, 1.250E+00, 1.224E+00, 1.167E+00, 1.110E+00, 1.039E+00, 9.682E-01, 9.119E-01, 8.667E-01, 8.359E-01, 7.903E-01, 7.499E-01, 7.578E-01, 7.936E-01, 8.595E-01, 9.557E-01, 1.098E+00, 1.254E+00, 1.419E+00, 1.500E+00, 1.529E+00, 1.462E+00, 1.339E+00, 1.152E+00, 9.470E-01, 7.516E-01, 5.683E-01, 4.100E-01, 2.894E-01, 1.993E-01, 1.372E-01, 9.685E-02, 6.914E-02, 5.076E-02, 3.851E-02, 2.990E-02, 2.414E-02, 1.714E-02, 1.249E-02, 1.084E-02, 9.637E-03, 8.826E-03, 8.251E-03, 7.945E-03, 7.913E-03, 7.839E-03, 6.205E-03, 5.395E-03, 5.376E-03, 5.855E-03, 5.805E-03, 5.727E-03},
//      {2.326E-04, 2.787E-02, 3.339E-02, 5.035E-02, 6.247E-02, 9.966E-02, 1.074E-01, 1.442E-01, 1.041E-01, 3.121E-01, 4.634E-01, 6.124E-01, 6.707E-01, 6.990E-01, 7.462E-01, 8.168E-01, 9.110E-01, 1.022E+00, 1.100E+00, 1.156E+00, 1.212E+00, 1.261E+00, 1.307E+00, 1.336E+00, 1.353E+00, 1.354E+00, 1.353E+00, 1.360E+00, 1.376E+00, 1.354E+00, 1.326E+00, 1.264E+00, 1.198E+00, 1.132E+00, 1.062E+00, 9.996E-01, 9.498E-01, 9.122E-01, 8.609E-01, 8.217E-01, 8.276E-01, 8.657E-01, 9.451E-01, 1.048E+00, 1.196E+00, 1.360E+00, 1.538E+00, 1.600E+00, 1.634E+00, 1.581E+00, 1.403E+00, 1.211E+00, 9.999E-01, 7.865E-01, 5.984E-01, 4.296E-01, 3.034E-01, 2.107E-01, 1.463E-01, 1.024E-01, 7.337E-02, 5.378E-02, 4.052E-02, 3.077E-02, 2.339E-02, 1.753E-02, 1.269E-02, 1.092E-02, 9.353E-03, 9.002E-03, 7.919E-03, 4.869E-03, 6.104E-03, 4.942E-03, 3.426E-03, 2.660E-03, 2.304E-03, 2.039E-03, 1.059E-03, 5.481E-04},
//      {2.328E-04, 3.090E-02, 4.163E-02, 4.817E-02, 5.984E-02, 9.593E-02, 1.055E-01, 1.605E-01, 1.151E-01, 3.110E-01, 4.780E-01, 6.027E-01, 6.617E-01, 6.884E-01, 7.227E-01, 7.992E-01, 8.973E-01, 1.001E+00, 1.085E+00, 1.149E+00, 1.217E+00, 1.260E+00, 1.303E+00, 1.342E+00, 1.352E+00, 1.359E+00, 1.367E+00, 1.366E+00, 1.386E+00, 1.359E+00, 1.335E+00, 1.267E+00, 1.203E+00, 1.130E+00, 1.060E+00, 9.983E-01, 9.556E-01, 9.185E-01, 8.634E-01, 8.242E-01, 8.302E-01, 8.673E-01, 9.375E-01, 1.051E+00, 1.194E+00, 1.359E+00, 1.540E+00, 1.593E+00, 1.626E+00, 1.570E+00, 1.398E+00, 1.220E+00, 9.918E-01, 7.834E-01, 5.988E-01, 4.256E-01, 3.069E-01, 2.102E-01, 1.467E-01, 1.022E-01, 7.271E-02, 5.372E-02, 4.035E-02, 3.002E-02, 2.315E-02, 1.791E-02, 1.267E-02, 1.052E-02, 9.544E-03, 8.520E-03, 8.017E-03, 6.324E-03, 6.082E-03, 5.663E-03, 2.850E-03, 3.110E-03, 2.375E-03, 1.463E-03, 1.312E-03, 4.850E-04},
//      {2.564E-04, 3.837E-02, 3.059E-02, 5.322E-02, 6.786E-02, 9.388E-02, 1.256E-01, 1.484E-01, 1.033E-01, 3.382E-01, 4.688E-01, 6.103E-01, 6.883E-01, 6.948E-01, 7.502E-01, 8.297E-01, 9.089E-01, 9.969E-01, 1.095E+00, 1.143E+00, 1.203E+00, 1.262E+00, 1.306E+00, 1.333E+00, 1.348E+00, 1.344E+00, 1.349E+00, 1.360E+00, 1.371E+00, 1.356E+00, 1.326E+00, 1.267E+00, 1.197E+00, 1.129E+00, 1.052E+00, 9.949E-01, 9.485E-01, 9.147E-01, 8.563E-01, 8.183E-01, 8.310E-01, 8.650E-01, 9.384E-01, 1.046E+00, 1.197E+00, 1.363E+00, 1.533E+00, 1.615E+00, 1.624E+00, 1.580E+00, 1.390E+00, 1.200E+00, 1.008E+00, 7.782E-01, 5.965E-01, 4.190E-01, 3.025E-01, 2.105E-01, 1.457E-01, 1.019E-01, 7.269E-02, 5.390E-02, 4.059E-02, 3.069E-02, 2.300E-02, 1.719E-02, 1.252E-02, 1.121E-02, 9.765E-03, 7.860E-03, 8.231E-03, 5.744E-03, 4.478E-03, 5.989E-03, 2.354E-03, 2.470E-03, 1.666E-03, 2.406E-03, 1.619E-03, 3.990E-04},
//      {3.098E-04, 2.532E-02, 7.010E-02, 5.975E-02, 5.345E-02, 7.526E-02, 8.972E-02, 1.506E-01, 1.019E-01, 4.177E-01, 4.905E-01, 6.736E-01, 7.624E-01, 7.185E-01, 8.202E-01, 7.980E-01, 8.954E-01, 1.013E+00, 1.087E+00, 1.149E+00, 1.210E+00, 1.250E+00, 1.304E+00, 1.345E+00, 1.342E+00, 1.349E+00, 1.356E+00, 1.341E+00, 1.364E+00, 1.326E+00, 1.323E+00, 1.231E+00, 1.202E+00, 1.088E+00, 1.043E+00, 9.859E-01, 9.468E-01, 9.123E-01, 8.560E-01, 8.090E-01, 8.177E-01, 8.259E-01, 9.266E-01, 1.030E+00, 1.172E+00, 1.328E+00, 1.537E+00, 1.607E+00, 1.641E+00, 1.598E+00, 1.403E+00, 1.203E+00, 1.024E+00, 7.923E-01, 5.926E-01, 4.400E-01, 3.034E-01, 2.112E-01, 1.464E-01, 1.046E-01, 7.418E-02, 5.522E-02, 3.982E-02, 2.936E-02, 2.511E-02, 1.870E-02, 1.296E-02, 9.903E-03, 9.423E-03, 9.231E-03, 6.472E-03, 7.884E-03, 4.329E-03, 2.418E-03, 3.861E-03, 2.891E-03, 5.423E-04, 6.677E-03, 4.057E-04, 3.023E-04},
//      {4.708E-04, 1.701E+00, -1.578E+00, 9.121E-01, 7.486E-01, 5.589E-01, 6.530E-01, 7.658E-01, 3.456E-01, 8.560E-01, 7.973E-01, 8.156E-01, 7.265E-01, 7.858E-01, 1.014E+00, 1.050E+00, 1.065E+00, 1.061E+00, 1.177E+00, 1.207E+00, 1.204E+00, 1.295E+00, 1.282E+00, 1.308E+00, 1.332E+00, 1.341E+00, 1.295E+00, 1.213E+00, 1.124E+00, 1.338E+00, 1.282E+00, 1.244E+00, 9.802E-01, 1.026E+00, 1.055E+00, 9.854E-01, 9.301E-01, 8.898E-01, 7.931E-01, 7.788E-01, 7.278E-01, 8.297E-01, 9.476E-01, 1.002E+00, 1.184E+00, 1.341E+00, 1.580E+00, 1.553E+00, 1.629E+00, 1.606E+00, 1.476E+00, 1.237E+00, 9.413E-01, 7.969E-01, 5.947E-01, 4.415E-01, 3.248E-01, 2.170E-01, 1.507E-01, 1.046E-01, 6.915E-02, 5.408E-02, 1.983E-02, 3.311E-02, 2.035E-02, 1.957E-02, 1.242E-02, 1.083E-02, 8.955E-03, 6.824E-03, 8.855E-03, 8.707E-03, 6.040E-03, 1.291E-02, 7.450E-03, 4.775E-03, 5.259E-03, 4.108E-03, 5.489E-03, 5.481E-03},
//      {2.406E-04, 3.385E-02, 3.578E-02, 5.432E-02, 6.220E-02, 9.562E-02, 1.249E-01, 1.405E-01, 1.066E-01, 3.192E-01, 4.762E-01, 6.200E-01, 6.800E-01, 7.151E-01, 7.432E-01, 7.980E-01, 8.981E-01, 1.007E+00, 1.090E+00, 1.145E+00, 1.208E+00, 1.252E+00, 1.304E+00, 1.329E+00, 1.345E+00, 1.349E+00, 1.354E+00, 1.362E+00, 1.372E+00, 1.359E+00, 1.325E+00, 1.259E+00, 1.200E+00, 1.133E+00, 1.059E+00, 9.963E-01, 9.505E-01, 9.115E-01, 8.607E-01, 8.247E-01, 8.266E-01, 8.668E-01, 9.347E-01, 1.045E+00, 1.196E+00, 1.369E+00, 1.551E+00, 1.602E+00, 1.626E+00, 1.571E+00, 1.409E+00, 1.217E+00, 1.005E+00, 7.886E-01, 6.010E-01, 4.290E-01, 3.019E-01, 2.112E-01, 1.465E-01, 1.022E-01, 7.362E-02, 5.391E-02, 4.057E-02, 3.021E-02, 2.415E-02, 1.752E-02, 1.257E-02, 1.084E-02, 9.528E-03, 8.775E-03, 7.496E-03, 5.919E-03, 5.381E-03, 5.185E-03, 4.161E-03, 3.090E-03, 1.867E-03, 1.701E-03, 9.188E-04, 5.315E-04},
//      {2.315E-01, 3.072E+00, 2.850E+00, 2.379E+00, 1.814E+00, 1.427E+00, 1.502E+00, 1.198E+00, 6.637E-01, 1.478E+00, 1.465E+00, 1.593E+00, 1.334E+00, 1.162E+00, 1.089E+00, 1.052E+00, 1.074E+00, 1.133E+00, 1.161E+00, 1.196E+00, 1.212E+00, 1.235E+00, 1.260E+00, 1.276E+00, 1.285E+00, 1.278E+00, 1.270E+00, 1.259E+00, 1.272E+00, 1.265E+00, 1.203E+00, 1.151E+00, 1.119E+00, 1.035E+00, 9.633E-01, 9.135E-01, 8.644E-01, 8.412E-01, 7.865E-01, 7.494E-01, 7.635E-01, 7.874E-01, 8.475E-01, 9.577E-01, 1.104E+00, 1.274E+00, 1.419E+00, 1.490E+00, 1.524E+00, 1.496E+00, 1.342E+00, 1.169E+00, 9.458E-01, 7.514E-01, 5.769E-01, 4.126E-01, 2.925E-01, 2.000E-01, 1.368E-01, 9.616E-02, 6.762E-02, 5.076E-02, 3.781E-02, 2.879E-02, 2.332E-02, 1.717E-02, 1.265E-02, 1.079E-02, 9.486E-03, 9.464E-03, 8.739E-03, 8.339E-03, 8.351E-03, 7.462E-03, 7.104E-03, 5.085E-03, 4.805E-03, 6.677E-03, 5.575E-03, 5.164E-03},
//      {2.174E-01, 2.227E+00, 2.479E+00, 2.328E+00, 1.704E+00, 1.940E+00, 1.549E+00, 1.289E+00, 5.517E-01, 1.441E+00, 1.490E+00, 1.434E+00, 1.362E+00, 1.171E+00, 1.073E+00, 1.050E+00, 1.080E+00, 1.120E+00, 1.159E+00, 1.167E+00, 1.210E+00, 1.239E+00, 1.259E+00, 1.290E+00, 1.269E+00, 1.256E+00, 1.265E+00, 1.263E+00, 1.287E+00, 1.244E+00, 1.225E+00, 1.178E+00, 1.111E+00, 1.037E+00, 9.787E-01, 9.073E-01, 8.541E-01, 8.298E-01, 7.933E-01, 7.530E-01, 7.696E-01, 7.966E-01, 8.582E-01, 9.675E-01, 1.092E+00, 1.266E+00, 1.416E+00, 1.513E+00, 1.557E+00, 1.461E+00, 1.341E+00, 1.135E+00, 9.446E-01, 7.411E-01, 5.572E-01, 4.133E-01, 2.920E-01, 1.992E-01, 1.383E-01, 9.723E-02, 6.830E-02, 5.173E-02, 3.840E-02, 3.008E-02, 2.393E-02, 1.743E-02, 1.259E-02, 1.057E-02, 9.381E-03, 8.891E-03, 8.430E-03, 7.669E-03, 8.314E-03, 8.597E-03, 6.436E-03, 6.161E-03, 5.354E-03, 5.808E-03, 7.759E-03, 4.967E-03},
//      {1.572E-01, 2.823E+00, 3.055E+00, 2.295E+00, 1.478E+00, 1.373E+00, 1.264E+00, 1.132E+00, 6.411E-01, 1.457E+00, 1.430E+00, 1.465E+00, 1.362E+00, 1.154E+00, 1.093E+00, 1.051E+00, 1.061E+00, 1.118E+00, 1.178E+00, 1.191E+00, 1.207E+00, 1.267E+00, 1.251E+00, 1.274E+00, 1.267E+00, 1.288E+00, 1.274E+00, 1.276E+00, 1.269E+00, 1.253E+00, 1.226E+00, 1.163E+00, 1.108E+00, 1.031E+00, 9.792E-01, 9.190E-01, 8.577E-01, 8.364E-01, 7.998E-01, 7.505E-01, 7.587E-01, 7.996E-01, 8.608E-01, 9.585E-01, 1.094E+00, 1.239E+00, 1.403E+00, 1.476E+00, 1.520E+00, 1.470E+00, 1.327E+00, 1.124E+00, 9.653E-01, 7.601E-01, 5.713E-01, 4.137E-01, 2.874E-01, 1.990E-01, 1.410E-01, 9.522E-02, 6.876E-02, 4.921E-02, 3.726E-02, 2.983E-02, 2.373E-02, 1.658E-02, 1.257E-02, 1.075E-02, 9.609E-03, 8.271E-03, 8.340E-03, 8.770E-03, 7.378E-03, 7.303E-03, 5.912E-03, 5.315E-03, 7.372E-03, 6.092E-03, 5.033E-03, 5.305E-03},
//      {2.160E-01, 2.263E+00, 1.119E+01, 2.336E+00, 1.736E+00, 1.510E+00, 1.077E+00, 1.176E+00, 7.053E-01, 1.423E+00, 1.569E+00, 1.440E+00, 1.375E+00, 1.159E+00, 1.075E+00, 1.069E+00, 1.062E+00, 1.133E+00, 1.158E+00, 1.204E+00, 1.216E+00, 1.240E+00, 1.263E+00, 1.282E+00, 1.286E+00, 1.287E+00, 1.260E+00, 1.280E+00, 1.266E+00, 1.247E+00, 1.234E+00, 1.178E+00, 1.121E+00, 1.030E+00, 9.682E-01, 9.054E-01, 8.685E-01, 8.296E-01, 7.917E-01, 7.498E-01, 7.487E-01, 7.899E-01, 8.571E-01, 9.687E-01, 1.098E+00, 1.254E+00, 1.410E+00, 1.492E+00, 1.542E+00, 1.455E+00, 1.350E+00, 1.139E+00, 9.516E-01, 7.482E-01, 5.658E-01, 4.106E-01, 2.926E-01, 1.957E-01, 1.395E-01, 9.392E-02, 6.780E-02, 5.034E-02, 3.757E-02, 3.000E-02, 2.382E-02, 1.738E-02, 1.216E-02, 1.105E-02, 9.388E-03, 8.357E-03, 8.885E-03, 8.099E-03, 7.050E-03, 6.724E-03, 6.228E-03, 4.828E-03, 5.222E-03, 5.245E-03, 7.617E-03, 7.289E-03},
//      {2.423E-01, 4.315E+00, 2.464E+00, 2.864E+00, 1.174E+00, 1.485E+00, 1.268E+00, 1.222E+00, 5.845E-01, 1.453E+00, 1.426E+00, 1.488E+00, 1.321E+00, 1.167E+00, 1.076E+00, 1.052E+00, 1.066E+00, 1.122E+00, 1.151E+00, 1.206E+00, 1.209E+00, 1.239E+00, 1.250E+00, 1.286E+00, 1.282E+00, 1.269E+00, 1.251E+00, 1.263E+00, 1.273E+00, 1.269E+00, 1.204E+00, 1.178E+00, 1.108E+00, 1.043E+00, 9.572E-01, 9.212E-01, 8.694E-01, 8.428E-01, 7.893E-01, 7.578E-01, 7.580E-01, 7.940E-01, 8.664E-01, 9.559E-01, 1.096E+00, 1.248E+00, 1.412E+00, 1.500E+00, 1.509E+00, 1.463E+00, 1.369E+00, 1.149E+00, 9.606E-01, 7.550E-01, 5.693E-01, 4.126E-01, 2.883E-01, 1.976E-01, 1.379E-01, 9.559E-02, 6.876E-02, 5.059E-02, 3.842E-02, 3.008E-02, 2.387E-02, 1.667E-02, 1.304E-02, 1.021E-02, 1.031E-02, 8.361E-03, 8.001E-03, 8.146E-03, 7.446E-03, 8.348E-03, 5.815E-03, 4.387E-03, 4.728E-03, 6.252E-03, 4.515E-03, 5.561E-03},
//      {1.617E-01, 4.064E+00, 2.742E+00, 2.266E+00, 1.559E+00, 1.377E+00, 1.402E+00, 1.178E+00, 6.902E-01, 1.501E+00, 1.659E+00, 1.587E+00, 1.368E+00, 1.170E+00, 1.114E+00, 1.061E+00, 1.092E+00, 1.130E+00, 1.172E+00, 1.207E+00, 1.183E+00, 1.234E+00, 1.261E+00, 1.254E+00, 1.287E+00, 1.263E+00, 1.272E+00, 1.246E+00, 1.266E+00, 1.262E+00, 1.218E+00, 1.166E+00, 1.121E+00, 1.039E+00, 9.762E-01, 8.993E-01, 8.753E-01, 8.349E-01, 7.893E-01, 7.575E-01, 7.539E-01, 7.984E-01, 8.531E-01, 9.740E-01, 1.119E+00, 1.251E+00, 1.404E+00, 1.488E+00, 1.556E+00, 1.446E+00, 1.355E+00, 1.132E+00, 9.286E-01, 7.537E-01, 5.683E-01, 4.106E-01, 2.881E-01, 1.966E-01, 1.355E-01, 9.763E-02, 6.776E-02, 5.132E-02, 3.890E-02, 2.995E-02, 2.371E-02, 1.746E-02, 1.324E-02, 1.051E-02, 9.834E-03, 8.969E-03, 7.766E-03, 7.762E-03, 8.075E-03, 9.524E-03, 8.243E-03, 5.045E-03, 5.098E-03, 4.711E-03, 4.371E-03, 6.547E-03},
//      {3.073E-01, 2.023E+00, 2.628E+00, 2.467E+00, 1.432E+00, 1.146E+00, 1.139E+00, 1.750E+00, 5.444E-01, 1.307E+00, 1.464E+00, 1.483E+00, 1.358E+00, 1.188E+00, 1.069E+00, 1.036E+00, 1.110E+00, 1.127E+00, 1.156E+00, 1.209E+00, 1.195E+00, 1.237E+00, 1.262E+00, 1.289E+00, 1.287E+00, 1.264E+00, 1.262E+00, 1.249E+00, 1.281E+00, 1.250E+00, 1.228E+00, 1.186E+00, 1.097E+00, 1.033E+00, 9.705E-01, 9.052E-01, 8.553E-01, 8.536E-01, 7.986E-01, 7.560E-01, 7.652E-01, 8.156E-01, 8.463E-01, 9.698E-01, 1.088E+00, 1.243E+00, 1.417E+00, 1.469E+00, 1.544E+00, 1.439E+00, 1.331E+00, 1.134E+00, 9.276E-01, 7.655E-01, 5.659E-01, 4.075E-01, 2.903E-01, 1.991E-01, 1.353E-01, 9.565E-02, 6.819E-02, 5.082E-02, 3.936E-02, 2.947E-02, 2.426E-02, 1.780E-02, 1.251E-02, 1.031E-02, 1.034E-02, 9.703E-03, 8.115E-03, 7.457E-03, 6.907E-03, 6.714E-03, 5.733E-03, 7.032E-03, 5.893E-03, 4.560E-03, 7.615E-03, 4.148E-03},
//      {1.575E-01, 2.376E+00, 5.511E+00, 4.140E+00, 2.222E+00, 1.022E+00, 1.414E+00, 1.012E+00, 5.570E-01, 1.627E+00, 1.349E+00, 1.507E+00, 1.347E+00, 1.251E+00, 1.103E+00, 1.054E+00, 1.092E+00, 1.122E+00, 1.182E+00, 1.167E+00, 1.212E+00, 1.234E+00, 1.264E+00, 1.287E+00, 1.260E+00, 1.284E+00, 1.277E+00, 1.250E+00, 1.300E+00, 1.262E+00, 1.246E+00, 1.159E+00, 1.099E+00, 1.041E+00, 9.627E-01, 9.212E-01, 8.749E-01, 8.307E-01, 7.929E-01, 7.360E-01, 7.686E-01, 7.892E-01, 8.466E-01, 9.500E-01, 1.047E+00, 1.288E+00, 1.426E+00, 1.505E+00, 1.517E+00, 1.455E+00, 1.287E+00, 1.121E+00, 9.316E-01, 7.538E-01, 5.805E-01, 4.069E-01, 2.963E-01, 1.982E-01, 1.402E-01, 9.389E-02, 6.983E-02, 5.031E-02, 3.893E-02, 3.000E-02, 2.573E-02, 1.678E-02, 1.244E-02, 1.088E-02, 9.356E-03, 8.698E-03, 8.022E-03, 6.875E-03, 1.100E-02, 9.955E-03, 7.337E-03, 4.677E-03, 6.427E-03, 6.148E-03, 8.214E-03, 3.827E-03},
//      {1.870E-01, 4.744E+00, 3.217E+00, 2.383E+00, 1.802E+00, 1.486E+00, 1.329E+00, 1.205E+00, 6.102E-01, 1.495E+00, 1.516E+00, 1.478E+00, 1.319E+00, 1.164E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.130E+00, 1.165E+00, 1.189E+00, 1.212E+00, 1.236E+00, 1.258E+00, 1.271E+00, 1.271E+00, 1.272E+00, 1.272E+00, 1.268E+00, 1.277E+00, 1.253E+00, 1.221E+00, 1.169E+00, 1.109E+00, 1.039E+00, 9.688E-01, 9.133E-01, 8.658E-01, 8.371E-01, 7.900E-01, 7.512E-01, 7.587E-01, 7.925E-01, 8.574E-01, 9.586E-01, 1.093E+00, 1.257E+00, 1.420E+00, 1.493E+00, 1.527E+00, 1.462E+00, 1.338E+00, 1.155E+00, 9.495E-01, 7.493E-01, 5.703E-01, 4.107E-01, 2.901E-01, 1.994E-01, 1.376E-01, 9.651E-02, 6.895E-02, 5.073E-02, 3.841E-02, 2.999E-02, 2.412E-02, 1.701E-02, 1.244E-02, 1.072E-02, 9.630E-03, 8.829E-03, 8.312E-03, 8.101E-03, 7.724E-03, 7.905E-03, 6.299E-03, 5.287E-03, 5.476E-03, 5.776E-03, 5.866E-03, 6.320E-03},
//      {1.913E-01, 4.255E+00, 3.444E+00, 2.481E+00, 1.640E+00, 1.531E+00, 1.288E+00, 1.270E+00, 5.997E-01, 1.442E+00, 1.477E+00, 1.476E+00, 1.330E+00, 1.169E+00, 1.083E+00, 1.051E+00, 1.078E+00, 1.126E+00, 1.166E+00, 1.188E+00, 1.211E+00, 1.238E+00, 1.256E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.271E+00, 1.267E+00, 1.274E+00, 1.254E+00, 1.220E+00, 1.167E+00, 1.113E+00, 1.037E+00, 9.688E-01, 9.129E-01, 8.681E-01, 8.336E-01, 7.865E-01, 7.516E-01, 7.576E-01, 7.948E-01, 8.593E-01, 9.561E-01, 1.097E+00, 1.258E+00, 1.421E+00, 1.492E+00, 1.534E+00, 1.461E+00, 1.341E+00, 1.156E+00, 9.519E-01, 7.507E-01, 5.693E-01, 4.101E-01, 2.896E-01, 1.981E-01, 1.374E-01, 9.658E-02, 6.937E-02, 5.074E-02, 3.867E-02, 2.989E-02, 2.413E-02, 1.713E-02, 1.250E-02, 1.076E-02, 9.502E-03, 8.767E-03, 8.258E-03, 8.063E-03, 7.855E-03, 7.777E-03, 6.306E-03, 5.442E-03, 5.528E-03, 5.516E-03, 6.168E-03, 5.712E-03},
//      {1.898E-01, 4.165E+00, 3.239E+00, 2.648E+00, 1.610E+00, 1.494E+00, 1.289E+00, 1.238E+00, 6.235E-01, 1.438E+00, 1.486E+00, 1.484E+00, 1.339E+00, 1.165E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.129E+00, 1.168E+00, 1.188E+00, 1.213E+00, 1.239E+00, 1.262E+00, 1.272E+00, 1.272E+00, 1.269E+00, 1.273E+00, 1.266E+00, 1.276E+00, 1.250E+00, 1.221E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.687E-01, 9.137E-01, 8.687E-01, 8.352E-01, 7.870E-01, 7.480E-01, 7.602E-01, 7.922E-01, 8.591E-01, 9.607E-01, 1.091E+00, 1.255E+00, 1.415E+00, 1.496E+00, 1.528E+00, 1.460E+00, 1.339E+00, 1.154E+00, 9.493E-01, 7.497E-01, 5.703E-01, 4.105E-01, 2.896E-01, 1.985E-01, 1.373E-01, 9.672E-02, 6.940E-02, 5.067E-02, 3.834E-02, 3.009E-02, 2.403E-02, 1.718E-02, 1.255E-02, 1.087E-02, 9.529E-03, 8.865E-03, 8.370E-03, 7.970E-03, 7.921E-03, 7.850E-03, 6.155E-03, 5.393E-03, 5.518E-03, 5.859E-03, 5.714E-03, 6.418E-03},
//      {1.897E-01, 3.957E+00, 3.856E+00, 2.684E+00, 1.643E+00, 1.480E+00, 1.304E+00, 1.284E+00, 6.124E-01, 1.434E+00, 1.497E+00, 1.483E+00, 1.326E+00, 1.166E+00, 1.080E+00, 1.051E+00, 1.074E+00, 1.126E+00, 1.163E+00, 1.187E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.268E+00, 1.274E+00, 1.274E+00, 1.270E+00, 1.269E+00, 1.277E+00, 1.252E+00, 1.224E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.698E-01, 9.114E-01, 8.652E-01, 8.348E-01, 7.895E-01, 7.498E-01, 7.574E-01, 7.921E-01, 8.594E-01, 9.566E-01, 1.096E+00, 1.260E+00, 1.419E+00, 1.496E+00, 1.534E+00, 1.465E+00, 1.340E+00, 1.157E+00, 9.516E-01, 7.506E-01, 5.693E-01, 4.110E-01, 2.894E-01, 1.974E-01, 1.380E-01, 9.660E-02, 6.948E-02, 5.088E-02, 3.837E-02, 2.965E-02, 2.417E-02, 1.699E-02, 1.248E-02, 1.080E-02, 9.539E-03, 8.775E-03, 8.265E-03, 8.058E-03, 7.837E-03, 7.898E-03, 6.202E-03, 5.428E-03, 5.554E-03, 5.352E-03, 5.705E-03, 6.037E-03},
//      {1.899E-01, 3.543E+00, 3.519E+00, 2.642E+00, 1.581E+00, 1.495E+00, 1.296E+00, 1.289E+00, 6.150E-01, 1.486E+00, 1.474E+00, 1.479E+00, 1.324E+00, 1.167E+00, 1.074E+00, 1.054E+00, 1.080E+00, 1.133E+00, 1.165E+00, 1.186E+00, 1.215E+00, 1.238E+00, 1.261E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.268E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.223E+00, 1.171E+00, 1.109E+00, 1.036E+00, 9.682E-01, 9.106E-01, 8.671E-01, 8.343E-01, 7.894E-01, 7.523E-01, 7.561E-01, 7.949E-01, 8.588E-01, 9.588E-01, 1.095E+00, 1.253E+00, 1.420E+00, 1.494E+00, 1.534E+00, 1.461E+00, 1.336E+00, 1.154E+00, 9.528E-01, 7.531E-01, 5.697E-01, 4.117E-01, 2.903E-01, 1.985E-01, 1.375E-01, 9.617E-02, 6.911E-02, 5.078E-02, 3.842E-02, 2.983E-02, 2.402E-02, 1.707E-02, 1.242E-02, 1.086E-02, 9.659E-03, 8.759E-03, 8.298E-03, 8.003E-03, 7.673E-03, 7.920E-03, 6.423E-03, 5.314E-03, 5.516E-03, 5.349E-03, 5.832E-03, 5.663E-03},
//    };

 pileupweightUp = { // 69.2 + 4.6%
     { 2.746E-04, 3.800E-02, 3.945E-02, 6.450E-02, 5.656E-02, 1.007E-01, 1.282E-01, 1.600E-01, 9.290E-02, 2.390E-01, 3.489E-01, 4.406E-01, 5.268E-01, 5.542E-01, 5.641E-01, 6.175E-01, 6.675E-01, 7.750E-01, 8.711E-01, 9.498E-01, 1.031E+00, 1.097E+00, 1.160E+00, 1.206E+00, 1.218E+00, 1.241E+00, 1.244E+00, 1.264E+00, 1.296E+00, 1.306E+00, 1.305E+00, 1.271E+00, 1.224E+00, 1.180E+00, 1.130E+00, 1.079E+00, 1.043E+00, 1.014E+00, 9.572E-01, 9.059E-01, 8.888E-01, 9.052E-01, 9.405E-01, 1.001E+00, 1.086E+00, 1.194E+00, 1.345E+00, 1.420E+00, 1.540E+00, 1.589E+00, 1.520E+00, 1.511E+00, 1.388E+00, 1.202E+00, 1.037E+00, 8.357E-01, 6.502E-01, 5.015E-01, 3.800E-01, 2.872E-01, 2.160E-01, 1.706E-01, 1.374E-01, 1.090E-01, 8.734E-02, 6.595E-02, 4.809E-02, 3.973E-02, 3.881E-02, 3.216E-02, 2.939E-02, 1.958E-02, 2.321E-02, 2.095E-02, 1.007E-02, 9.249E-03, 6.678E-03, 5.725E-03, 2.615E-03, 1.486E-03}, // DYJetsMG.root
     { 3.433E-04, 3.454E-02, 3.707E-02, 7.843E-02, 7.878E-02, 9.718E-02, 1.476E-01, 2.221E-01, 1.030E-01, 2.762E-01, 3.946E-01, 4.640E-01, 5.113E-01, 5.498E-01, 5.919E-01, 6.086E-01, 6.780E-01, 7.641E-01, 8.550E-01, 9.381E-01, 1.015E+00, 1.099E+00, 1.149E+00, 1.196E+00, 1.214E+00, 1.229E+00, 1.235E+00, 1.251E+00, 1.294E+00, 1.295E+00, 1.282E+00, 1.249E+00, 1.222E+00, 1.172E+00, 1.113E+00, 1.073E+00, 1.033E+00, 9.993E-01, 9.431E-01, 9.012E-01, 8.873E-01, 8.995E-01, 9.242E-01, 9.785E-01, 1.072E+00, 1.194E+00, 1.344E+00, 1.437E+00, 1.551E+00, 1.594E+00, 1.501E+00, 1.501E+00, 1.355E+00, 1.225E+00, 1.037E+00, 8.318E-01, 6.545E-01, 4.967E-01, 3.796E-01, 2.866E-01, 2.198E-01, 1.698E-01, 1.373E-01, 1.101E-01, 8.817E-02, 6.614E-02, 4.662E-02, 3.968E-02, 3.667E-02, 3.382E-02, 2.906E-02, 1.962E-02, 2.278E-02, 2.174E-02, 1.324E-02, 1.531E-02, 8.076E-03, 5.732E-03, 4.735E-03, 2.103E-03}, // QCD1000.root
     { 1.694E-01, 3.604E+00, 2.835E+00, 2.691E+00, 1.428E+00, 1.307E+00, 1.213E+00, 1.141E+00, 4.834E-01, 9.236E-01, 1.068E+00, 1.039E+00, 1.006E+00, 9.011E-01, 8.298E-01, 7.959E-01, 8.148E-01, 8.686E-01, 9.329E-01, 9.882E-01, 1.035E+00, 1.088E+00, 1.124E+00, 1.155E+00, 1.167E+00, 1.168E+00, 1.174E+00, 1.183E+00, 1.213E+00, 1.211E+00, 1.209E+00, 1.180E+00, 1.142E+00, 1.087E+00, 1.039E+00, 9.923E-01, 9.580E-01, 9.264E-01, 8.764E-01, 8.333E-01, 8.299E-01, 8.384E-01, 8.677E-01, 9.186E-01, 1.002E+00, 1.113E+00, 1.247E+00, 1.345E+00, 1.444E+00, 1.494E+00, 1.490E+00, 1.425E+00, 1.318E+00, 1.161E+00, 9.929E-01, 8.030E-01, 6.238E-01, 4.741E-01, 3.591E-01, 2.743E-01, 2.100E-01, 1.636E-01, 1.311E-01, 1.061E-01, 8.847E-02, 6.451E-02, 4.810E-02, 4.175E-02, 3.714E-02, 3.411E-02, 3.086E-02, 3.037E-02, 2.895E-02, 2.835E-02, 2.272E-02, 1.925E-02, 2.068E-02, 2.272E-02, 2.337E-02, 2.412E-02}, // QCD1500.root
     { 1.620E-01, 3.457E+00, 2.962E+00, 2.561E+00, 1.300E+00, 1.323E+00, 1.252E+00, 1.134E+00, 4.869E-01, 9.444E-01, 1.069E+00, 1.036E+00, 1.017E+00, 9.092E-01, 8.329E-01, 7.962E-01, 8.147E-01, 8.688E-01, 9.369E-01, 9.801E-01, 1.029E+00, 1.083E+00, 1.129E+00, 1.157E+00, 1.164E+00, 1.168E+00, 1.172E+00, 1.182E+00, 1.214E+00, 1.212E+00, 1.205E+00, 1.173E+00, 1.139E+00, 1.088E+00, 1.038E+00, 9.980E-01, 9.540E-01, 9.294E-01, 8.779E-01, 8.341E-01, 8.319E-01, 8.399E-01, 8.686E-01, 9.241E-01, 1.002E+00, 1.112E+00, 1.254E+00, 1.361E+00, 1.453E+00, 1.484E+00, 1.496E+00, 1.426E+00, 1.309E+00, 1.170E+00, 9.880E-01, 7.975E-01, 6.242E-01, 4.768E-01, 3.597E-01, 2.725E-01, 2.094E-01, 1.642E-01, 1.310E-01, 1.064E-01, 8.922E-02, 6.381E-02, 4.794E-02, 4.177E-02, 3.789E-02, 3.325E-02, 3.151E-02, 3.098E-02, 2.831E-02, 2.880E-02, 2.202E-02, 1.875E-02, 2.074E-02, 2.056E-02, 2.543E-02, 2.142E-02}, // QCD2000.root
     { 2.672E-04, 2.574E-02, 3.670E-02, 7.423E-02, 5.911E-02, 9.888E-02, 1.257E-01, 1.420E-01, 8.521E-02, 2.163E-01, 3.577E-01, 4.463E-01, 5.098E-01, 5.489E-01, 5.668E-01, 6.074E-01, 6.810E-01, 7.691E-01, 8.707E-01, 9.530E-01, 1.025E+00, 1.102E+00, 1.167E+00, 1.204E+00, 1.229E+00, 1.234E+00, 1.249E+00, 1.262E+00, 1.298E+00, 1.307E+00, 1.305E+00, 1.260E+00, 1.227E+00, 1.185E+00, 1.130E+00, 1.084E+00, 1.044E+00, 1.007E+00, 9.514E-01, 9.059E-01, 8.988E-01, 9.113E-01, 9.370E-01, 1.004E+00, 1.088E+00, 1.202E+00, 1.348E+00, 1.423E+00, 1.536E+00, 1.580E+00, 1.557E+00, 1.488E+00, 1.378E+00, 1.211E+00, 1.043E+00, 8.298E-01, 6.572E-01, 4.998E-01, 3.801E-01, 2.896E-01, 2.204E-01, 1.717E-01, 1.362E-01, 1.084E-01, 8.464E-02, 6.609E-02, 4.806E-02, 4.190E-02, 3.462E-02, 3.365E-02, 2.754E-02, 2.329E-02, 1.907E-02, 2.342E-02, 1.291E-02, 1.417E-02, 9.327E-03, 5.206E-03, 3.842E-03, 1.956E-03}, // QCD300.root
     { 2.416E-04, 2.728E-02, 3.163E-02, 5.796E-02, 6.194E-02, 9.897E-02, 9.667E-02, 1.189E-01, 8.736E-02, 2.091E-01, 3.433E-01, 4.319E-01, 4.940E-01, 5.508E-01, 5.599E-01, 5.961E-01, 6.788E-01, 7.806E-01, 8.777E-01, 9.527E-01, 1.034E+00, 1.097E+00, 1.168E+00, 1.215E+00, 1.234E+00, 1.245E+00, 1.249E+00, 1.274E+00, 1.300E+00, 1.308E+00, 1.312E+00, 1.268E+00, 1.235E+00, 1.185E+00, 1.134E+00, 1.077E+00, 1.048E+00, 1.014E+00, 9.588E-01, 9.090E-01, 8.984E-01, 9.137E-01, 9.489E-01, 1.006E+00, 1.086E+00, 1.200E+00, 1.357E+00, 1.456E+00, 1.547E+00, 1.600E+00, 1.548E+00, 1.515E+00, 1.384E+00, 1.222E+00, 1.042E+00, 8.469E-01, 6.616E-01, 4.986E-01, 3.816E-01, 2.865E-01, 2.225E-01, 1.722E-01, 1.375E-01, 1.069E-01, 8.782E-02, 6.631E-02, 4.759E-02, 4.244E-02, 3.822E-02, 3.212E-02, 2.661E-02, 1.902E-02, 2.176E-02, 1.620E-02, 1.151E-02, 1.447E-02, 8.548E-03, 8.861E-03, 4.279E-03, 2.068E-03}, // QCD500.root
     { 2.868E-04, 4.027E-02, 4.212E-02, 7.878E-02, 6.589E-02, 1.026E-01, 1.337E-01, 1.462E-01, 1.046E-01, 2.653E-01, 3.643E-01, 4.706E-01, 5.401E-01, 5.474E-01, 5.807E-01, 6.221E-01, 6.787E-01, 7.667E-01, 8.683E-01, 9.483E-01, 1.021E+00, 1.090E+00, 1.156E+00, 1.199E+00, 1.223E+00, 1.224E+00, 1.244E+00, 1.262E+00, 1.281E+00, 1.297E+00, 1.297E+00, 1.263E+00, 1.220E+00, 1.181E+00, 1.120E+00, 1.069E+00, 1.038E+00, 1.009E+00, 9.492E-01, 9.048E-01, 8.920E-01, 9.120E-01, 9.368E-01, 9.971E-01, 1.083E+00, 1.197E+00, 1.346E+00, 1.442E+00, 1.558E+00, 1.583E+00, 1.555E+00, 1.487E+00, 1.395E+00, 1.216E+00, 1.029E+00, 8.306E-01, 6.510E-01, 4.971E-01, 3.768E-01, 2.874E-01, 2.239E-01, 1.702E-01, 1.369E-01, 1.045E-01, 8.620E-02, 6.536E-02, 5.000E-02, 4.206E-02, 3.557E-02, 3.208E-02, 2.724E-02, 1.853E-02, 1.923E-02, 1.762E-02, 9.488E-03, 1.326E-02, 9.188E-03, 8.836E-03, 2.524E-03, 2.510E-03}, // QCD700.root
     { 2.804E-04, 3.766E-02, 4.106E-02, 6.948E-02, 7.013E-02, 1.280E-01, 1.357E-01, 1.355E-01, 8.374E-02, 2.217E-01, 3.260E-01, 4.327E-01, 5.261E-01, 5.189E-01, 5.233E-01, 6.099E-01, 6.246E-01, 7.674E-01, 8.628E-01, 9.382E-01, 1.018E+00, 1.069E+00, 1.160E+00, 1.206E+00, 1.211E+00, 1.240E+00, 1.256E+00, 1.259E+00, 1.292E+00, 1.297E+00, 1.296E+00, 1.272E+00, 1.217E+00, 1.186E+00, 1.133E+00, 1.093E+00, 1.053E+00, 1.008E+00, 9.596E-01, 9.115E-01, 9.110E-01, 9.098E-01, 9.499E-01, 1.016E+00, 1.097E+00, 1.209E+00, 1.330E+00, 1.478E+00, 1.505E+00, 1.570E+00, 1.558E+00, 1.530E+00, 1.387E+00, 1.242E+00, 1.031E+00, 8.321E-01, 6.678E-01, 5.112E-01, 3.810E-01, 2.878E-01, 2.191E-01, 1.733E-01, 1.396E-01, 1.081E-01, 9.093E-02, 6.657E-02, 4.975E-02, 4.134E-02, 3.648E-02, 3.607E-02, 2.903E-02, 1.674E-02, 1.139E-02, 2.445E-02, 1.119E-02, 6.881E-03, 7.184E-03, 2.179E-02, 5.974E-03, 1.479E-03}, // STs.root
     { 1.744E-01, 3.086E+00, 2.652E+00, 2.514E+00, 1.367E+00, 1.350E+00, 1.217E+00, 1.129E+00, 5.035E-01, 9.533E-01, 1.062E+00, 1.040E+00, 1.012E+00, 9.044E-01, 8.261E-01, 7.949E-01, 8.160E-01, 8.697E-01, 9.335E-01, 9.872E-01, 1.036E+00, 1.086E+00, 1.127E+00, 1.155E+00, 1.168E+00, 1.169E+00, 1.173E+00, 1.183E+00, 1.212E+00, 1.213E+00, 1.209E+00, 1.178E+00, 1.140E+00, 1.086E+00, 1.038E+00, 9.926E-01, 9.578E-01, 9.260E-01, 8.777E-01, 8.336E-01, 8.275E-01, 8.407E-01, 8.676E-01, 9.191E-01, 9.994E-01, 1.112E+00, 1.251E+00, 1.348E+00, 1.443E+00, 1.495E+00, 1.489E+00, 1.430E+00, 1.313E+00, 1.162E+00, 9.906E-01, 7.999E-01, 6.275E-01, 4.749E-01, 3.606E-01, 2.731E-01, 2.103E-01, 1.643E-01, 1.304E-01, 1.063E-01, 8.864E-02, 6.386E-02, 4.771E-02, 4.167E-02, 3.727E-02, 3.395E-02, 3.143E-02, 3.013E-02, 2.895E-02, 2.911E-02, 2.229E-02, 1.967E-02, 2.018E-02, 2.005E-02, 2.279E-02, 2.441E-02}, // STt.root
     { 1.724E-01, 4.426E+00, 2.736E+00, 2.767E+00, 1.319E+00, 1.331E+00, 1.239E+00, 1.141E+00, 5.163E-01, 9.236E-01, 1.065E+00, 1.045E+00, 9.995E-01, 8.990E-01, 8.296E-01, 7.932E-01, 8.127E-01, 8.700E-01, 9.384E-01, 9.872E-01, 1.036E+00, 1.087E+00, 1.128E+00, 1.154E+00, 1.167E+00, 1.166E+00, 1.167E+00, 1.181E+00, 1.210E+00, 1.214E+00, 1.206E+00, 1.182E+00, 1.142E+00, 1.090E+00, 1.036E+00, 9.946E-01, 9.587E-01, 9.281E-01, 8.786E-01, 8.296E-01, 8.288E-01, 8.405E-01, 8.662E-01, 9.221E-01, 1.001E+00, 1.114E+00, 1.249E+00, 1.353E+00, 1.451E+00, 1.486E+00, 1.498E+00, 1.427E+00, 1.313E+00, 1.157E+00, 9.930E-01, 8.011E-01, 6.242E-01, 4.737E-01, 3.611E-01, 2.733E-01, 2.095E-01, 1.634E-01, 1.305E-01, 1.069E-01, 8.825E-02, 6.459E-02, 4.791E-02, 4.169E-02, 3.714E-02, 3.410E-02, 3.140E-02, 3.055E-02, 2.840E-02, 2.879E-02, 2.370E-02, 1.985E-02, 2.011E-02, 2.221E-02, 2.104E-02, 2.172E-02}, // STtb.root
     { 2.524E-04, 2.272E-02, 3.015E-02, 4.811E-02, 6.613E-02, 1.166E-01, 8.986E-02, 9.320E-02, 8.697E-02, 2.616E-01, 3.126E-01, 4.274E-01, 5.218E-01, 5.508E-01, 5.572E-01, 6.109E-01, 6.644E-01, 7.641E-01, 8.579E-01, 9.410E-01, 1.011E+00, 1.101E+00, 1.171E+00, 1.217E+00, 1.217E+00, 1.242E+00, 1.264E+00, 1.290E+00, 1.302E+00, 1.316E+00, 1.320E+00, 1.262E+00, 1.242E+00, 1.188E+00, 1.142E+00, 1.082E+00, 1.037E+00, 1.021E+00, 9.504E-01, 9.096E-01, 9.141E-01, 9.127E-01, 9.483E-01, 1.012E+00, 1.105E+00, 1.196E+00, 1.381E+00, 1.466E+00, 1.537E+00, 1.586E+00, 1.562E+00, 1.502E+00, 1.386E+00, 1.223E+00, 1.031E+00, 8.557E-01, 6.664E-01, 4.988E-01, 3.733E-01, 2.933E-01, 2.233E-01, 1.655E-01, 1.344E-01, 1.117E-01, 8.697E-02, 6.509E-02, 4.821E-02, 4.217E-02, 3.917E-02, 3.587E-02, 2.276E-02, 1.341E-02, 1.659E-02, 1.770E-02, 2.239E-02, 1.587E-02, 4.953E-03, 1.582E-02, 1.995E-03, 2.952E-03}, // STtWt.root
     { 2.525E-04, 1.920E-02, 3.578E-02, 5.685E-02, 6.580E-02, 8.489E-02, 9.872E-02, 1.758E-01, 1.057E-01, 2.146E-01, 3.711E-01, 4.746E-01, 5.018E-01, 5.138E-01, 5.571E-01, 5.973E-01, 6.926E-01, 7.738E-01, 8.806E-01, 9.605E-01, 1.030E+00, 1.112E+00, 1.155E+00, 1.208E+00, 1.228E+00, 1.230E+00, 1.253E+00, 1.260E+00, 1.313E+00, 1.313E+00, 1.316E+00, 1.252E+00, 1.244E+00, 1.189E+00, 1.123E+00, 1.089E+00, 1.050E+00, 1.009E+00, 9.563E-01, 9.101E-01, 9.144E-01, 9.259E-01, 9.541E-01, 9.984E-01, 1.090E+00, 1.188E+00, 1.343E+00, 1.418E+00, 1.508E+00, 1.597E+00, 1.524E+00, 1.492E+00, 1.412E+00, 1.235E+00, 1.051E+00, 8.334E-01, 6.719E-01, 4.986E-01, 3.816E-01, 2.919E-01, 2.241E-01, 1.622E-01, 1.398E-01, 1.097E-01, 7.918E-02, 6.530E-02, 5.009E-02, 4.123E-02, 3.532E-02, 3.115E-02, 2.541E-02, 1.987E-02, 1.472E-02, 3.089E-02, 7.077E-03, 1.808E-02, 1.098E-02, 1.416E-02, 2.256E-03, 9.865E-04}, // STtWtb.root
     { 2.331E-04, 2.924E-02, 2.930E-02, 5.461E-02, 5.358E-02, 8.473E-02, 1.206E-01, 1.285E-01, 8.591E-02, 2.072E-01, 3.396E-01, 4.317E-01, 5.165E-01, 5.538E-01, 5.703E-01, 6.039E-01, 6.755E-01, 7.756E-01, 8.745E-01, 9.504E-01, 1.031E+00, 1.098E+00, 1.169E+00, 1.209E+00, 1.232E+00, 1.238E+00, 1.249E+00, 1.272E+00, 1.303E+00, 1.316E+00, 1.310E+00, 1.269E+00, 1.233E+00, 1.188E+00, 1.134E+00, 1.086E+00, 1.049E+00, 1.013E+00, 9.595E-01, 9.150E-01, 9.024E-01, 9.170E-01, 9.448E-01, 1.002E+00, 1.093E+00, 1.213E+00, 1.367E+00, 1.443E+00, 1.539E+00, 1.599E+00, 1.571E+00, 1.506E+00, 1.389E+00, 1.224E+00, 1.047E+00, 8.358E-01, 6.540E-01, 5.047E-01, 3.828E-01, 2.893E-01, 2.235E-01, 1.739E-01, 1.379E-01, 1.072E-01, 8.874E-02, 6.606E-02, 4.820E-02, 4.185E-02, 3.677E-02, 3.361E-02, 2.837E-02, 2.211E-02, 1.986E-02, 1.897E-02, 1.517E-02, 1.130E-02, 6.888E-03, 6.366E-03, 3.508E-03, 2.080E-03}, // TThad.root
     { 2.254E-04, 2.407E-02, 2.735E-02, 5.062E-02, 5.381E-02, 8.831E-02, 1.038E-01, 1.319E-01, 8.389E-02, 2.025E-01, 3.305E-01, 4.264E-01, 5.094E-01, 5.412E-01, 5.726E-01, 6.181E-01, 6.852E-01, 7.875E-01, 8.823E-01, 9.591E-01, 1.035E+00, 1.106E+00, 1.172E+00, 1.215E+00, 1.239E+00, 1.243E+00, 1.248E+00, 1.270E+00, 1.306E+00, 1.312E+00, 1.311E+00, 1.274E+00, 1.231E+00, 1.188E+00, 1.138E+00, 1.090E+00, 1.048E+00, 1.014E+00, 9.596E-01, 9.117E-01, 9.035E-01, 9.157E-01, 9.553E-01, 1.005E+00, 1.094E+00, 1.205E+00, 1.355E+00, 1.441E+00, 1.547E+00, 1.610E+00, 1.564E+00, 1.498E+00, 1.383E+00, 1.221E+00, 1.042E+00, 8.369E-01, 6.572E-01, 5.034E-01, 3.822E-01, 2.897E-01, 2.227E-01, 1.735E-01, 1.377E-01, 1.092E-01, 8.597E-02, 6.611E-02, 4.864E-02, 4.217E-02, 3.610E-02, 3.448E-02, 2.998E-02, 1.819E-02, 2.252E-02, 1.808E-02, 1.249E-02, 9.724E-03, 8.496E-03, 7.632E-03, 4.044E-03, 2.145E-03}, // TT1L.root
     { 2.255E-04, 2.669E-02, 3.410E-02, 4.843E-02, 5.155E-02, 8.500E-02, 1.020E-01, 1.469E-01, 9.271E-02, 2.018E-01, 3.409E-01, 4.197E-01, 5.025E-01, 5.331E-01, 5.545E-01, 6.048E-01, 6.748E-01, 7.715E-01, 8.701E-01, 9.533E-01, 1.039E+00, 1.105E+00, 1.168E+00, 1.221E+00, 1.239E+00, 1.248E+00, 1.261E+00, 1.275E+00, 1.316E+00, 1.316E+00, 1.319E+00, 1.277E+00, 1.236E+00, 1.186E+00, 1.135E+00, 1.088E+00, 1.055E+00, 1.021E+00, 9.625E-01, 9.145E-01, 9.063E-01, 9.175E-01, 9.476E-01, 1.008E+00, 1.092E+00, 1.204E+00, 1.357E+00, 1.435E+00, 1.539E+00, 1.598E+00, 1.558E+00, 1.508E+00, 1.372E+00, 1.216E+00, 1.043E+00, 8.292E-01, 6.647E-01, 5.023E-01, 3.832E-01, 2.891E-01, 2.207E-01, 1.733E-01, 1.371E-01, 1.066E-01, 8.507E-02, 6.755E-02, 4.859E-02, 4.064E-02, 3.683E-02, 3.264E-02, 3.035E-02, 2.362E-02, 2.244E-02, 2.072E-02, 1.039E-02, 1.137E-02, 8.760E-03, 5.474E-03, 5.010E-03, 1.898E-03}, // TT2L.root
     { 1.772E-01, 3.094E+00, 2.992E+00, 2.524E+00, 1.382E+00, 1.354E+00, 1.211E+00, 1.157E+00, 4.959E-01, 9.533E-01, 1.070E+00, 1.026E+00, 1.017E+00, 9.031E-01, 8.242E-01, 7.996E-01, 8.086E-01, 8.686E-01, 9.374E-01, 9.855E-01, 1.035E+00, 1.086E+00, 1.129E+00, 1.157E+00, 1.165E+00, 1.168E+00, 1.172E+00, 1.182E+00, 1.211E+00, 1.211E+00, 1.210E+00, 1.176E+00, 1.141E+00, 1.090E+00, 1.037E+00, 9.940E-01, 9.564E-01, 9.293E-01, 8.809E-01, 8.321E-01, 8.272E-01, 8.395E-01, 8.688E-01, 9.167E-01, 1.004E+00, 1.111E+00, 1.250E+00, 1.351E+00, 1.447E+00, 1.488E+00, 1.493E+00, 1.425E+00, 1.310E+00, 1.166E+00, 9.898E-01, 7.988E-01, 6.268E-01, 4.762E-01, 3.586E-01, 2.741E-01, 2.099E-01, 1.638E-01, 1.309E-01, 1.061E-01, 8.872E-02, 6.462E-02, 4.790E-02, 4.185E-02, 3.719E-02, 3.381E-02, 3.123E-02, 2.968E-02, 2.920E-02, 2.868E-02, 2.262E-02, 1.972E-02, 1.983E-02, 2.191E-02, 2.216E-02, 2.241E-02}, // TTMtt1000.root
     { 2.484E-04, 3.314E-02, 2.505E-02, 5.351E-02, 5.845E-02, 8.319E-02, 1.214E-01, 1.358E-01, 8.326E-02, 2.195E-01, 3.344E-01, 4.249E-01, 5.228E-01, 5.380E-01, 5.756E-01, 6.279E-01, 6.836E-01, 7.680E-01, 8.780E-01, 9.480E-01, 1.027E+00, 1.106E+00, 1.170E+00, 1.213E+00, 1.235E+00, 1.234E+00, 1.244E+00, 1.270E+00, 1.302E+00, 1.314E+00, 1.311E+00, 1.277E+00, 1.230E+00, 1.185E+00, 1.127E+00, 1.084E+00, 1.047E+00, 1.017E+00, 9.545E-01, 9.079E-01, 9.071E-01, 9.150E-01, 9.486E-01, 1.003E+00, 1.094E+00, 1.208E+00, 1.351E+00, 1.455E+00, 1.537E+00, 1.608E+00, 1.550E+00, 1.484E+00, 1.394E+00, 1.208E+00, 1.039E+00, 8.163E-01, 6.552E-01, 5.030E-01, 3.807E-01, 2.884E-01, 2.207E-01, 1.739E-01, 1.380E-01, 1.090E-01, 8.454E-02, 6.481E-02, 4.800E-02, 4.329E-02, 3.769E-02, 3.011E-02, 3.116E-02, 2.145E-02, 1.653E-02, 2.191E-02, 8.582E-03, 9.030E-03, 6.145E-03, 9.005E-03, 6.180E-03, 1.561E-03}, // TTMtt700.root
     { 1.721E-01, 3.587E+00, 2.567E+00, 2.539E+00, 1.440E+00, 1.307E+00, 1.270E+00, 1.140E+00, 4.981E-01, 9.379E-01, 1.071E+00, 1.031E+00, 1.014E+00, 9.073E-01, 8.261E-01, 7.991E-01, 8.105E-01, 8.694E-01, 9.324E-01, 9.846E-01, 1.033E+00, 1.088E+00, 1.127E+00, 1.155E+00, 1.167E+00, 1.168E+00, 1.177E+00, 1.184E+00, 1.210E+00, 1.212E+00, 1.207E+00, 1.181E+00, 1.139E+00, 1.089E+00, 1.037E+00, 9.914E-01, 9.576E-01, 9.284E-01, 8.787E-01, 8.341E-01, 8.294E-01, 8.385E-01, 8.714E-01, 9.182E-01, 1.001E+00, 1.113E+00, 1.249E+00, 1.345E+00, 1.438E+00, 1.488E+00, 1.491E+00, 1.428E+00, 1.311E+00, 1.164E+00, 9.926E-01, 8.013E-01, 6.281E-01, 4.739E-01, 3.604E-01, 2.731E-01, 2.093E-01, 1.642E-01, 1.310E-01, 1.067E-01, 8.836E-02, 6.496E-02, 4.798E-02, 4.200E-02, 3.726E-02, 3.399E-02, 3.137E-02, 3.037E-02, 2.772E-02, 2.908E-02, 2.355E-02, 1.953E-02, 2.041E-02, 2.056E-02, 2.395E-02, 2.238E-02}, // ttW.root
     { 1.653E-01, 3.049E+00, 3.158E+00, 2.457E+00, 1.344E+00, 1.382E+00, 1.261E+00, 1.053E+00, 4.963E-01, 9.488E-01, 1.041E+00, 1.028E+00, 1.011E+00, 9.054E-01, 8.352E-01, 7.969E-01, 8.128E-01, 8.683E-01, 9.366E-01, 9.867E-01, 1.035E+00, 1.087E+00, 1.129E+00, 1.154E+00, 1.165E+00, 1.167E+00, 1.169E+00, 1.184E+00, 1.213E+00, 1.213E+00, 1.210E+00, 1.177E+00, 1.142E+00, 1.086E+00, 1.042E+00, 9.978E-01, 9.549E-01, 9.259E-01, 8.790E-01, 8.321E-01, 8.262E-01, 8.368E-01, 8.715E-01, 9.208E-01, 1.003E+00, 1.120E+00, 1.250E+00, 1.341E+00, 1.452E+00, 1.486E+00, 1.490E+00, 1.426E+00, 1.316E+00, 1.165E+00, 9.911E-01, 7.971E-01, 6.239E-01, 4.728E-01, 3.581E-01, 2.729E-01, 2.101E-01, 1.645E-01, 1.302E-01, 1.069E-01, 8.822E-02, 6.455E-02, 4.843E-02, 4.176E-02, 3.755E-02, 3.406E-02, 3.143E-02, 2.981E-02, 2.888E-02, 2.811E-02, 2.183E-02, 2.039E-02, 2.083E-02, 2.040E-02, 2.145E-02, 2.481E-02}, // ttZ.root
     { 2.547E-04, 2.635E-02, 3.186E-02, 6.346E-02, 6.862E-02, 7.956E-02, 1.178E-01, 1.431E-01, 1.130E-01, 2.162E-01, 3.445E-01, 5.035E-01, 5.077E-01, 5.344E-01, 5.807E-01, 6.145E-01, 6.889E-01, 7.654E-01, 8.876E-01, 9.516E-01, 1.029E+00, 1.118E+00, 1.172E+00, 1.219E+00, 1.243E+00, 1.225E+00, 1.235E+00, 1.283E+00, 1.295E+00, 1.285E+00, 1.313E+00, 1.278E+00, 1.204E+00, 1.196E+00, 1.132E+00, 1.090E+00, 1.034E+00, 1.009E+00, 9.611E-01, 9.061E-01, 9.037E-01, 8.830E-01, 9.359E-01, 9.849E-01, 1.096E+00, 1.210E+00, 1.349E+00, 1.442E+00, 1.575E+00, 1.614E+00, 1.587E+00, 1.486E+00, 1.383E+00, 1.252E+00, 1.023E+00, 8.509E-01, 6.642E-01, 4.966E-01, 3.796E-01, 2.852E-01, 2.211E-01, 1.717E-01, 1.380E-01, 1.073E-01, 8.364E-02, 6.239E-02, 4.754E-02, 3.967E-02, 3.401E-02, 3.257E-02, 2.678E-02, 1.485E-02, 1.820E-02, 1.432E-02, 1.881E-02, 1.170E-02, 1.317E-02, 4.844E-03, 2.146E-03, 1.013E-03}, // ttH.root
     { 2.216E-04, 1.980E-02, 2.775E-02, 5.618E-02, 6.327E-02, 8.423E-02, 1.514E-01, 1.537E-01, 8.270E-02, 2.179E-01, 3.597E-01, 3.981E-01, 5.384E-01, 5.653E-01, 5.959E-01, 6.212E-01, 7.120E-01, 7.728E-01, 8.739E-01, 9.605E-01, 1.027E+00, 1.100E+00, 1.168E+00, 1.202E+00, 1.249E+00, 1.211E+00, 1.233E+00, 1.273E+00, 1.314E+00, 1.320E+00, 1.312E+00, 1.245E+00, 1.213E+00, 1.188E+00, 1.111E+00, 1.081E+00, 1.050E+00, 9.985E-01, 9.539E-01, 9.085E-01, 8.980E-01, 9.153E-01, 9.461E-01, 1.000E+00, 1.093E+00, 1.232E+00, 1.367E+00, 1.451E+00, 1.565E+00, 1.621E+00, 1.557E+00, 1.498E+00, 1.405E+00, 1.245E+00, 1.030E+00, 8.297E-01, 6.626E-01, 5.017E-01, 3.767E-01, 2.916E-01, 2.260E-01, 1.730E-01, 1.321E-01, 1.140E-01, 9.504E-02, 6.945E-02, 5.060E-02, 4.209E-02, 3.538E-02, 3.605E-02, 2.700E-02, 2.501E-02, 3.084E-02, 3.021E-02, 2.328E-02, 1.178E-02, 2.117E-02, 2.241E-02, 2.212E-02, 2.197E-03}, // WW.root
     { 2.780E-04, 8.098E-03, 3.021E-02, 6.737E-02, 7.952E-02, 1.595E-01, 1.857E-01, 2.031E-01, 8.771E-02, 2.663E-01, 2.995E-01, 4.475E-01, 5.352E-01, 5.844E-01, 5.648E-01, 5.671E-01, 6.348E-01, 7.772E-01, 8.690E-01, 9.440E-01, 1.051E+00, 1.107E+00, 1.162E+00, 1.202E+00, 1.232E+00, 1.236E+00, 1.229E+00, 1.268E+00, 1.315E+00, 1.325E+00, 1.283E+00, 1.265E+00, 1.230E+00, 1.187E+00, 1.146E+00, 1.099E+00, 1.045E+00, 1.006E+00, 9.449E-01, 9.232E-01, 8.846E-01, 8.940E-01, 9.416E-01, 1.021E+00, 1.107E+00, 1.207E+00, 1.362E+00, 1.479E+00, 1.563E+00, 1.639E+00, 1.598E+00, 1.543E+00, 1.417E+00, 1.193E+00, 1.040E+00, 8.271E-01, 6.762E-01, 5.097E-01, 3.874E-01, 2.947E-01, 2.148E-01, 1.690E-01, 1.277E-01, 1.013E-01, 9.006E-02, 6.879E-02, 4.579E-02, 4.281E-02, 2.978E-02, 3.363E-02, 1.850E-02, 1.849E-02, 1.559E-02, 3.141E-02, 1.288E-02, 4.452E-03, 3.110E-03, 2.063E-02, 1.110E-03, 8.433E-04}, // WZ.root
     { 4.404E-04, 2.189E-02, 2.998E-02, 2.170E-01, 1.238E-01, 1.246E-01, 2.204E-01, 2.548E-01, 1.285E-01, 2.959E-01, 3.905E-01, 4.891E-01, 5.662E-01, 5.521E-01, 4.857E-01, 5.475E-01, 6.026E-01, 7.025E-01, 8.437E-01, 9.157E-01, 9.996E-01, 1.097E+00, 1.165E+00, 1.205E+00, 1.215E+00, 1.234E+00, 1.248E+00, 1.254E+00, 1.267E+00, 1.303E+00, 1.309E+00, 1.274E+00, 1.219E+00, 1.183E+00, 1.128E+00, 1.083E+00, 1.042E+00, 1.010E+00, 9.590E-01, 9.171E-01, 9.045E-01, 8.824E-01, 9.577E-01, 9.642E-01, 1.102E+00, 1.169E+00, 1.371E+00, 1.401E+00, 1.525E+00, 1.621E+00, 1.480E+00, 1.516E+00, 1.417E+00, 1.122E+00, 9.566E-01, 8.333E-01, 6.682E-01, 4.800E-01, 3.807E-01, 2.790E-01, 2.173E-01, 1.752E-01, 1.400E-01, 1.049E-01, 8.155E-02, 5.558E-02, 4.681E-02, 4.468E-02, 3.768E-02, 3.461E-02, 3.369E-02, 3.100E-02, 3.172E-02, 3.230E-02, 2.216E-02, 1.925E-02, 2.410E-02, 4.743E-03, 9.372E-03, 3.806E-04}, // ZZ.root
     { 1.683E-01, 9.118E+00, 3.564E+00, 2.958E+00, 1.334E+00, 1.408E+00, 1.251E+00, 1.182E+00, 5.021E-01, 9.346E-01, 1.074E+00, 1.103E+00, 1.010E+00, 9.259E-01, 8.248E-01, 8.020E-01, 8.028E-01, 8.682E-01, 9.274E-01, 9.827E-01, 1.032E+00, 1.079E+00, 1.115E+00, 1.173E+00, 1.175E+00, 1.164E+00, 1.176E+00, 1.172E+00, 1.226E+00, 1.204E+00, 1.201E+00, 1.165E+00, 1.134E+00, 1.097E+00, 1.032E+00, 9.918E-01, 9.563E-01, 9.290E-01, 8.867E-01, 8.345E-01, 8.321E-01, 8.328E-01, 8.642E-01, 9.061E-01, 9.994E-01, 1.110E+00, 1.263E+00, 1.358E+00, 1.446E+00, 1.472E+00, 1.480E+00, 1.420E+00, 1.296E+00, 1.165E+00, 9.999E-01, 8.184E-01, 6.337E-01, 4.715E-01, 3.637E-01, 2.727E-01, 2.128E-01, 1.672E-01, 1.327E-01, 1.109E-01, 9.047E-02, 6.741E-02, 4.784E-02, 4.023E-02, 3.831E-02, 3.498E-02, 3.057E-02, 2.996E-02, 2.939E-02, 2.884E-02, 2.456E-02, 1.901E-02, 2.054E-02, 2.336E-02, 1.814E-02, 2.129E-02}, // TpTp700.root
     { 1.816E-01, 3.665E+00, 2.149E+00, 2.252E+00, 1.367E+00, 1.290E+00, 1.325E+00, 9.709E-01, 4.515E-01, 8.712E-01, 1.073E+00, 1.052E+00, 1.017E+00, 9.196E-01, 8.591E-01, 7.895E-01, 8.197E-01, 8.676E-01, 9.293E-01, 9.786E-01, 1.033E+00, 1.079E+00, 1.128E+00, 1.151E+00, 1.172E+00, 1.174E+00, 1.181E+00, 1.177E+00, 1.206E+00, 1.224E+00, 1.202E+00, 1.167E+00, 1.148E+00, 1.093E+00, 1.045E+00, 9.968E-01, 9.462E-01, 9.207E-01, 8.796E-01, 8.340E-01, 8.173E-01, 8.414E-01, 8.778E-01, 9.285E-01, 9.967E-01, 1.107E+00, 1.239E+00, 1.340E+00, 1.455E+00, 1.512E+00, 1.488E+00, 1.436E+00, 1.339E+00, 1.158E+00, 1.003E+00, 7.870E-01, 6.327E-01, 4.756E-01, 3.580E-01, 2.702E-01, 2.072E-01, 1.661E-01, 1.305E-01, 1.070E-01, 9.020E-02, 6.394E-02, 4.857E-02, 4.074E-02, 3.761E-02, 3.408E-02, 3.169E-02, 3.134E-02, 2.761E-02, 2.577E-02, 2.036E-02, 2.069E-02, 1.801E-02, 1.743E-02, 1.668E-02, 2.325E-02}, // TpTp1000.root
     { 2.243E-01, 2.654E+00, 2.334E+00, 2.392E+00, 1.563E+00, 1.265E+00, 1.451E+00, 1.096E+00, 5.347E-01, 9.591E-01, 1.045E+00, 1.109E+00, 1.013E+00, 8.996E-01, 8.355E-01, 7.965E-01, 8.081E-01, 8.730E-01, 9.315E-01, 9.924E-01, 1.035E+00, 1.083E+00, 1.129E+00, 1.161E+00, 1.178E+00, 1.173E+00, 1.172E+00, 1.175E+00, 1.208E+00, 1.225E+00, 1.189E+00, 1.159E+00, 1.150E+00, 1.086E+00, 1.032E+00, 9.957E-01, 9.539E-01, 9.352E-01, 8.767E-01, 8.315E-01, 8.334E-01, 8.330E-01, 8.566E-01, 9.186E-01, 1.009E+00, 1.129E+00, 1.250E+00, 1.342E+00, 1.442E+00, 1.523E+00, 1.497E+00, 1.447E+00, 1.308E+00, 1.166E+00, 1.005E+00, 8.039E-01, 6.337E-01, 4.779E-01, 3.574E-01, 2.721E-01, 2.053E-01, 1.638E-01, 1.285E-01, 1.022E-01, 8.569E-02, 6.474E-02, 4.848E-02, 4.168E-02, 3.661E-02, 3.625E-02, 3.308E-02, 3.115E-02, 3.082E-02, 2.730E-02, 2.590E-02, 1.859E-02, 1.772E-02, 2.499E-02, 2.129E-02, 2.020E-02}, // TpTp1100.root
     { 2.106E-01, 1.924E+00, 2.030E+00, 2.340E+00, 1.468E+00, 1.719E+00, 1.496E+00, 1.179E+00, 4.445E-01, 9.348E-01, 1.063E+00, 9.988E-01, 1.034E+00, 9.068E-01, 8.234E-01, 7.943E-01, 8.123E-01, 8.627E-01, 9.299E-01, 9.686E-01, 1.033E+00, 1.086E+00, 1.129E+00, 1.173E+00, 1.162E+00, 1.153E+00, 1.167E+00, 1.179E+00, 1.222E+00, 1.205E+00, 1.211E+00, 1.187E+00, 1.142E+00, 1.088E+00, 1.048E+00, 9.889E-01, 9.426E-01, 9.226E-01, 8.844E-01, 8.355E-01, 8.402E-01, 8.427E-01, 8.674E-01, 9.280E-01, 9.988E-01, 1.122E+00, 1.247E+00, 1.363E+00, 1.474E+00, 1.488E+00, 1.495E+00, 1.404E+00, 1.306E+00, 1.150E+00, 9.705E-01, 8.050E-01, 6.325E-01, 4.759E-01, 3.613E-01, 2.751E-01, 2.073E-01, 1.669E-01, 1.305E-01, 1.068E-01, 8.796E-02, 6.574E-02, 4.827E-02, 4.084E-02, 3.620E-02, 3.406E-02, 3.191E-02, 2.864E-02, 3.068E-02, 3.145E-02, 2.347E-02, 2.252E-02, 1.975E-02, 2.174E-02, 2.962E-02, 1.943E-02}, // TpTp1200.root
     { 1.523E-01, 2.439E+00, 2.502E+00, 2.307E+00, 1.273E+00, 1.217E+00, 1.221E+00, 1.036E+00, 5.165E-01, 9.453E-01, 1.020E+00, 1.020E+00, 1.034E+00, 8.935E-01, 8.389E-01, 7.957E-01, 7.980E-01, 8.616E-01, 9.450E-01, 9.884E-01, 1.030E+00, 1.111E+00, 1.121E+00, 1.159E+00, 1.161E+00, 1.182E+00, 1.176E+00, 1.191E+00, 1.205E+00, 1.213E+00, 1.212E+00, 1.173E+00, 1.139E+00, 1.081E+00, 1.049E+00, 1.002E+00, 9.466E-01, 9.299E-01, 8.915E-01, 8.328E-01, 8.282E-01, 8.458E-01, 8.701E-01, 9.194E-01, 1.001E+00, 1.098E+00, 1.236E+00, 1.329E+00, 1.438E+00, 1.497E+00, 1.479E+00, 1.391E+00, 1.335E+00, 1.180E+00, 9.951E-01, 8.059E-01, 6.225E-01, 4.756E-01, 3.683E-01, 2.694E-01, 2.087E-01, 1.588E-01, 1.266E-01, 1.059E-01, 8.720E-02, 6.254E-02, 4.819E-02, 4.152E-02, 3.708E-02, 3.168E-02, 3.157E-02, 3.276E-02, 2.723E-02, 2.672E-02, 2.156E-02, 1.943E-02, 2.719E-02, 2.280E-02, 1.922E-02, 2.076E-02}, // TpTp1300.root
     { 2.093E-01, 1.955E+00, 9.168E+00, 2.349E+00, 1.495E+00, 1.338E+00, 1.040E+00, 1.076E+00, 5.682E-01, 9.235E-01, 1.119E+00, 1.003E+00, 1.045E+00, 8.971E-01, 8.249E-01, 8.091E-01, 7.984E-01, 8.729E-01, 9.288E-01, 9.994E-01, 1.038E+00, 1.087E+00, 1.132E+00, 1.166E+00, 1.178E+00, 1.182E+00, 1.163E+00, 1.195E+00, 1.202E+00, 1.208E+00, 1.220E+00, 1.187E+00, 1.152E+00, 1.080E+00, 1.037E+00, 9.869E-01, 9.585E-01, 9.223E-01, 8.825E-01, 8.320E-01, 8.173E-01, 8.356E-01, 8.663E-01, 9.292E-01, 1.004E+00, 1.112E+00, 1.242E+00, 1.344E+00, 1.459E+00, 1.481E+00, 1.505E+00, 1.409E+00, 1.316E+00, 1.161E+00, 9.854E-01, 7.999E-01, 6.339E-01, 4.678E-01, 3.645E-01, 2.658E-01, 2.058E-01, 1.624E-01, 1.277E-01, 1.065E-01, 8.755E-02, 6.555E-02, 4.663E-02, 4.267E-02, 3.623E-02, 3.201E-02, 3.363E-02, 3.025E-02, 2.602E-02, 2.460E-02, 2.271E-02, 1.765E-02, 1.926E-02, 1.963E-02, 2.908E-02, 2.852E-02}, // TpTp1400.root
     { 2.348E-01, 3.728E+00, 2.018E+00, 2.879E+00, 1.011E+00, 1.316E+00, 1.225E+00, 1.119E+00, 4.709E-01, 9.432E-01, 1.017E+00, 1.036E+00, 1.003E+00, 9.033E-01, 8.257E-01, 7.965E-01, 8.014E-01, 8.643E-01, 9.231E-01, 1.000E+00, 1.032E+00, 1.086E+00, 1.121E+00, 1.169E+00, 1.175E+00, 1.165E+00, 1.154E+00, 1.179E+00, 1.209E+00, 1.229E+00, 1.190E+00, 1.188E+00, 1.138E+00, 1.094E+00, 1.025E+00, 1.004E+00, 9.594E-01, 9.370E-01, 8.798E-01, 8.409E-01, 8.275E-01, 8.399E-01, 8.757E-01, 9.169E-01, 1.002E+00, 1.106E+00, 1.243E+00, 1.351E+00, 1.429E+00, 1.490E+00, 1.527E+00, 1.421E+00, 1.328E+00, 1.172E+00, 9.914E-01, 8.037E-01, 6.246E-01, 4.722E-01, 3.603E-01, 2.705E-01, 2.087E-01, 1.632E-01, 1.306E-01, 1.068E-01, 8.774E-02, 6.288E-02, 5.001E-02, 3.944E-02, 3.977E-02, 3.202E-02, 3.029E-02, 3.043E-02, 2.748E-02, 3.054E-02, 2.120E-02, 1.604E-02, 1.744E-02, 2.340E-02, 1.724E-02, 2.176E-02}, // TpTp1500.root
     { 1.566E-01, 3.511E+00, 2.246E+00, 2.278E+00, 1.343E+00, 1.220E+00, 1.354E+00, 1.078E+00, 5.560E-01, 9.739E-01, 1.183E+00, 1.105E+00, 1.039E+00, 9.057E-01, 8.551E-01, 8.030E-01, 8.216E-01, 8.706E-01, 9.400E-01, 1.002E+00, 1.009E+00, 1.082E+00, 1.130E+00, 1.141E+00, 1.179E+00, 1.159E+00, 1.173E+00, 1.163E+00, 1.202E+00, 1.222E+00, 1.204E+00, 1.175E+00, 1.151E+00, 1.090E+00, 1.046E+00, 9.802E-01, 9.660E-01, 9.283E-01, 8.798E-01, 8.405E-01, 8.230E-01, 8.446E-01, 8.623E-01, 9.343E-01, 1.023E+00, 1.109E+00, 1.236E+00, 1.340E+00, 1.473E+00, 1.473E+00, 1.511E+00, 1.400E+00, 1.284E+00, 1.170E+00, 9.897E-01, 7.999E-01, 6.240E-01, 4.698E-01, 3.540E-01, 2.763E-01, 2.057E-01, 1.656E-01, 1.322E-01, 1.063E-01, 8.714E-02, 6.585E-02, 5.075E-02, 4.058E-02, 3.795E-02, 3.435E-02, 2.940E-02, 2.899E-02, 2.980E-02, 3.485E-02, 3.006E-02, 1.845E-02, 1.880E-02, 1.763E-02, 1.669E-02, 2.562E-02}, // TpTp1600.root
     { 2.977E-01, 1.748E+00, 2.152E+00, 2.481E+00, 1.233E+00, 1.015E+00, 1.100E+00, 1.601E+00, 4.386E-01, 8.484E-01, 1.044E+00, 1.032E+00, 1.031E+00, 9.199E-01, 8.199E-01, 7.843E-01, 8.351E-01, 8.682E-01, 9.269E-01, 1.003E+00, 1.020E+00, 1.085E+00, 1.131E+00, 1.173E+00, 1.179E+00, 1.160E+00, 1.164E+00, 1.166E+00, 1.216E+00, 1.210E+00, 1.214E+00, 1.196E+00, 1.127E+00, 1.083E+00, 1.039E+00, 9.867E-01, 9.439E-01, 9.491E-01, 8.902E-01, 8.389E-01, 8.354E-01, 8.628E-01, 8.554E-01, 9.302E-01, 9.948E-01, 1.102E+00, 1.248E+00, 1.323E+00, 1.461E+00, 1.465E+00, 1.484E+00, 1.402E+00, 1.283E+00, 1.188E+00, 9.855E-01, 7.939E-01, 6.287E-01, 4.759E-01, 3.535E-01, 2.707E-01, 2.070E-01, 1.640E-01, 1.338E-01, 1.046E-01, 8.914E-02, 6.711E-02, 4.797E-02, 3.984E-02, 3.990E-02, 3.717E-02, 3.072E-02, 2.785E-02, 2.549E-02, 2.456E-02, 2.090E-02, 2.571E-02, 2.173E-02, 1.707E-02, 2.907E-02, 1.623E-02}, // TpTp1700.root
     { 1.526E-01, 2.053E+00, 4.513E+00, 4.162E+00, 1.914E+00, 9.058E-01, 1.366E+00, 9.259E-01, 4.488E-01, 1.056E+00, 9.620E-01, 1.049E+00, 1.023E+00, 9.690E-01, 8.464E-01, 7.974E-01, 8.210E-01, 8.648E-01, 9.480E-01, 9.687E-01, 1.034E+00, 1.082E+00, 1.133E+00, 1.170E+00, 1.155E+00, 1.179E+00, 1.178E+00, 1.167E+00, 1.235E+00, 1.222E+00, 1.232E+00, 1.168E+00, 1.129E+00, 1.092E+00, 1.031E+00, 1.004E+00, 9.656E-01, 9.236E-01, 8.838E-01, 8.166E-01, 8.390E-01, 8.349E-01, 8.558E-01, 9.112E-01, 9.572E-01, 1.142E+00, 1.256E+00, 1.355E+00, 1.436E+00, 1.481E+00, 1.435E+00, 1.386E+00, 1.288E+00, 1.170E+00, 1.011E+00, 7.926E-01, 6.417E-01, 4.737E-01, 3.663E-01, 2.657E-01, 2.120E-01, 1.623E-01, 1.323E-01, 1.065E-01, 9.456E-02, 6.326E-02, 4.770E-02, 4.204E-02, 3.611E-02, 3.331E-02, 3.037E-02, 2.568E-02, 4.057E-02, 3.642E-02, 2.675E-02, 1.710E-02, 2.370E-02, 2.301E-02, 3.136E-02, 1.498E-02}, // TpTp1800.root
     { 1.812E-01, 4.098E+00, 2.634E+00, 2.396E+00, 1.552E+00, 1.317E+00, 1.284E+00, 1.103E+00, 4.916E-01, 9.699E-01, 1.081E+00, 1.029E+00, 1.002E+00, 9.015E-01, 8.253E-01, 7.943E-01, 8.123E-01, 8.706E-01, 9.341E-01, 9.864E-01, 1.034E+00, 1.084E+00, 1.128E+00, 1.156E+00, 1.165E+00, 1.168E+00, 1.173E+00, 1.184E+00, 1.212E+00, 1.214E+00, 1.207E+00, 1.178E+00, 1.140E+00, 1.089E+00, 1.038E+00, 9.955E-01, 9.555E-01, 9.307E-01, 8.806E-01, 8.335E-01, 8.282E-01, 8.383E-01, 8.666E-01, 9.195E-01, 9.992E-01, 1.114E+00, 1.251E+00, 1.345E+00, 1.446E+00, 1.489E+00, 1.492E+00, 1.429E+00, 1.313E+00, 1.163E+00, 9.933E-01, 8.001E-01, 6.284E-01, 4.764E-01, 3.594E-01, 2.731E-01, 2.093E-01, 1.637E-01, 1.305E-01, 1.065E-01, 8.865E-02, 6.412E-02, 4.768E-02, 4.140E-02, 3.716E-02, 3.382E-02, 3.146E-02, 3.026E-02, 2.850E-02, 2.892E-02, 2.297E-02, 1.933E-02, 2.020E-02, 2.162E-02, 2.240E-02, 2.473E-02}, // WJ1200.root
     { 1.854E-01, 3.676E+00, 2.821E+00, 2.494E+00, 1.412E+00, 1.357E+00, 1.244E+00, 1.162E+00, 4.832E-01, 9.356E-01, 1.053E+00, 1.028E+00, 1.010E+00, 9.051E-01, 8.312E-01, 7.957E-01, 8.109E-01, 8.678E-01, 9.351E-01, 9.859E-01, 1.033E+00, 1.086E+00, 1.125E+00, 1.156E+00, 1.167E+00, 1.170E+00, 1.173E+00, 1.183E+00, 1.209E+00, 1.215E+00, 1.206E+00, 1.176E+00, 1.143E+00, 1.088E+00, 1.038E+00, 9.951E-01, 9.580E-01, 9.268E-01, 8.767E-01, 8.340E-01, 8.271E-01, 8.408E-01, 8.686E-01, 9.171E-01, 1.003E+00, 1.115E+00, 1.252E+00, 1.344E+00, 1.452E+00, 1.488E+00, 1.495E+00, 1.430E+00, 1.316E+00, 1.165E+00, 9.915E-01, 7.988E-01, 6.272E-01, 4.734E-01, 3.591E-01, 2.733E-01, 2.106E-01, 1.637E-01, 1.314E-01, 1.061E-01, 8.868E-02, 6.458E-02, 4.794E-02, 4.155E-02, 3.667E-02, 3.358E-02, 3.126E-02, 3.012E-02, 2.899E-02, 2.845E-02, 2.299E-02, 1.990E-02, 2.039E-02, 2.064E-02, 2.355E-02, 2.235E-02}, // WJ200.root
     { 1.839E-01, 3.598E+00, 2.653E+00, 2.662E+00, 1.387E+00, 1.324E+00, 1.245E+00, 1.133E+00, 5.023E-01, 9.332E-01, 1.060E+00, 1.033E+00, 1.017E+00, 9.017E-01, 8.255E-01, 7.944E-01, 8.123E-01, 8.701E-01, 9.369E-01, 9.856E-01, 1.036E+00, 1.086E+00, 1.131E+00, 1.157E+00, 1.166E+00, 1.165E+00, 1.175E+00, 1.182E+00, 1.211E+00, 1.211E+00, 1.207E+00, 1.180E+00, 1.140E+00, 1.089E+00, 1.037E+00, 9.960E-01, 9.587E-01, 9.286E-01, 8.773E-01, 8.299E-01, 8.298E-01, 8.380E-01, 8.684E-01, 9.215E-01, 9.972E-01, 1.113E+00, 1.247E+00, 1.347E+00, 1.447E+00, 1.486E+00, 1.493E+00, 1.427E+00, 1.313E+00, 1.164E+00, 9.933E-01, 7.997E-01, 6.274E-01, 4.745E-01, 3.587E-01, 2.737E-01, 2.107E-01, 1.635E-01, 1.303E-01, 1.068E-01, 8.833E-02, 6.480E-02, 4.810E-02, 4.198E-02, 3.677E-02, 3.396E-02, 3.168E-02, 2.977E-02, 2.923E-02, 2.872E-02, 2.244E-02, 1.972E-02, 2.035E-02, 2.193E-02, 2.182E-02, 2.511E-02}, // WJ2500.root
     { 1.838E-01, 3.418E+00, 3.158E+00, 2.698E+00, 1.415E+00, 1.312E+00, 1.260E+00, 1.175E+00, 4.934E-01, 9.305E-01, 1.068E+00, 1.033E+00, 1.007E+00, 9.027E-01, 8.285E-01, 7.956E-01, 8.078E-01, 8.673E-01, 9.330E-01, 9.846E-01, 1.034E+00, 1.086E+00, 1.130E+00, 1.154E+00, 1.167E+00, 1.169E+00, 1.172E+00, 1.185E+00, 1.213E+00, 1.213E+00, 1.210E+00, 1.181E+00, 1.140E+00, 1.088E+00, 1.039E+00, 9.934E-01, 9.549E-01, 9.281E-01, 8.801E-01, 8.320E-01, 8.268E-01, 8.380E-01, 8.687E-01, 9.175E-01, 1.002E+00, 1.117E+00, 1.250E+00, 1.347E+00, 1.452E+00, 1.492E+00, 1.494E+00, 1.431E+00, 1.316E+00, 1.165E+00, 9.914E-01, 8.006E-01, 6.269E-01, 4.717E-01, 3.605E-01, 2.734E-01, 2.109E-01, 1.642E-01, 1.304E-01, 1.053E-01, 8.881E-02, 6.408E-02, 4.785E-02, 4.172E-02, 3.681E-02, 3.361E-02, 3.129E-02, 3.010E-02, 2.892E-02, 2.889E-02, 2.262E-02, 1.984E-02, 2.049E-02, 2.003E-02, 2.178E-02, 2.362E-02}, // WJ400.root
     { 1.840E-01, 3.061E+00, 2.882E+00, 2.656E+00, 1.362E+00, 1.324E+00, 1.252E+00, 1.180E+00, 4.954E-01, 9.640E-01, 1.052E+00, 1.030E+00, 1.006E+00, 9.036E-01, 8.237E-01, 7.976E-01, 8.125E-01, 8.732E-01, 9.347E-01, 9.840E-01, 1.037E+00, 1.085E+00, 1.130E+00, 1.156E+00, 1.166E+00, 1.170E+00, 1.170E+00, 1.181E+00, 1.210E+00, 1.214E+00, 1.209E+00, 1.180E+00, 1.140E+00, 1.087E+00, 1.037E+00, 9.926E-01, 9.569E-01, 9.276E-01, 8.799E-01, 8.347E-01, 8.254E-01, 8.409E-01, 8.681E-01, 9.197E-01, 1.001E+00, 1.110E+00, 1.251E+00, 1.346E+00, 1.452E+00, 1.487E+00, 1.489E+00, 1.428E+00, 1.318E+00, 1.169E+00, 9.923E-01, 8.020E-01, 6.287E-01, 4.743E-01, 3.593E-01, 2.721E-01, 2.098E-01, 1.638E-01, 1.306E-01, 1.059E-01, 8.828E-02, 6.437E-02, 4.763E-02, 4.193E-02, 3.728E-02, 3.355E-02, 3.141E-02, 2.989E-02, 2.831E-02, 2.898E-02, 2.342E-02, 1.943E-02, 2.034E-02, 2.002E-02, 2.226E-02, 2.216E-02}, // WJ600.root
     { 1.658E-01, 3.110E+00, 2.537E+00, 2.618E+00, 1.368E+00, 1.275E+00, 1.253E+00, 1.144E+00, 4.908E-01, 9.375E-01, 1.069E+00, 1.024E+00, 1.012E+00, 9.021E-01, 8.249E-01, 7.980E-01, 8.126E-01, 8.685E-01, 9.351E-01, 9.875E-01, 1.034E+00, 1.087E+00, 1.130E+00, 1.156E+00, 1.168E+00, 1.170E+00, 1.173E+00, 1.181E+00, 1.210E+00, 1.211E+00, 1.208E+00, 1.179E+00, 1.137E+00, 1.089E+00, 1.038E+00, 9.952E-01, 9.573E-01, 9.280E-01, 8.795E-01, 8.327E-01, 8.286E-01, 8.378E-01, 8.680E-01, 9.205E-01, 9.989E-01, 1.117E+00, 1.249E+00, 1.341E+00, 1.446E+00, 1.489E+00, 1.488E+00, 1.430E+00, 1.310E+00, 1.162E+00, 9.915E-01, 8.026E-01, 6.287E-01, 4.745E-01, 3.612E-01, 2.726E-01, 2.102E-01, 1.646E-01, 1.310E-01, 1.059E-01, 8.859E-02, 6.427E-02, 4.789E-02, 4.155E-02, 3.728E-02, 3.381E-02, 3.140E-02, 2.978E-02, 2.927E-02, 2.945E-02, 2.328E-02, 1.880E-02, 2.082E-02, 2.053E-02, 2.100E-02, 2.378E-02} // WJ800.root
};
   
  //  pileupweightDn = { // this is 72383
//      {2.627E-04, 2.950E-02, 3.845E-02, 6.129E-02, 7.067E-02, 1.038E-01, 1.276E-01, 1.488E-01, 1.050E-01, 3.197E-01, 4.811E-01, 6.165E-01, 6.699E-01, 7.030E-01, 7.332E-01, 7.987E-01, 8.958E-01, 9.917E-01, 1.083E+00, 1.145E+00, 1.204E+00, 1.252E+00, 1.292E+00, 1.325E+00, 1.342E+00, 1.346E+00, 1.351E+00, 1.358E+00, 1.368E+00, 1.355E+00, 1.323E+00, 1.260E+00, 1.197E+00, 1.133E+00, 1.057E+00, 9.937E-01, 9.487E-01, 9.072E-01, 8.591E-01, 8.169E-01, 8.251E-01, 8.610E-01, 9.336E-01, 1.047E+00, 1.193E+00, 1.356E+00, 1.538E+00, 1.612E+00, 1.625E+00, 1.577E+00, 1.402E+00, 1.210E+00, 1.006E+00, 7.882E-01, 5.993E-01, 4.287E-01, 3.047E-01, 2.107E-01, 1.456E-01, 1.024E-01, 7.315E-02, 5.335E-02, 4.065E-02, 3.040E-02, 2.403E-02, 1.784E-02, 1.262E-02, 1.095E-02, 9.353E-03, 8.596E-03, 7.320E-03, 6.155E-03, 6.241E-03, 4.710E-03, 3.440E-03, 2.819E-03, 2.363E-03, 1.809E-03, 1.251E-03, 4.036E-04},
//      {3.544E-04, 3.998E-02, 4.526E-02, 7.801E-02, 9.146E-02, 1.097E-01, 1.527E-01, 2.427E-01, 1.278E-01, 4.256E-01, 5.532E-01, 6.663E-01, 6.732E-01, 7.100E-01, 7.715E-01, 8.042E-01, 9.015E-01, 9.917E-01, 1.066E+00, 1.131E+00, 1.189E+00, 1.253E+00, 1.282E+00, 1.315E+00, 1.325E+00, 1.339E+00, 1.339E+00, 1.339E+00, 1.362E+00, 1.336E+00, 1.297E+00, 1.239E+00, 1.190E+00, 1.117E+00, 1.039E+00, 9.847E-01, 9.359E-01, 8.988E-01, 8.460E-01, 8.122E-01, 8.128E-01, 8.503E-01, 9.144E-01, 1.020E+00, 1.173E+00, 1.348E+00, 1.525E+00, 1.596E+00, 1.638E+00, 1.565E+00, 1.346E+00, 1.213E+00, 9.796E-01, 7.891E-01, 5.957E-01, 4.270E-01, 3.022E-01, 2.079E-01, 1.453E-01, 1.013E-01, 7.242E-02, 5.264E-02, 4.040E-02, 3.102E-02, 2.399E-02, 1.754E-02, 1.216E-02, 1.027E-02, 9.501E-03, 8.830E-03, 7.677E-03, 5.254E-03, 6.172E-03, 5.941E-03, 3.630E-03, 4.188E-03, 2.190E-03, 1.532E-03, 1.240E-03, 5.375E-04},
//      {1.749E-01, 4.172E+00, 3.462E+00, 2.677E+00, 1.657E+00, 1.475E+00, 1.255E+00, 1.247E+00, 6.000E-01, 1.423E+00, 1.498E+00, 1.492E+00, 1.325E+00, 1.164E+00, 1.082E+00, 1.052E+00, 1.083E+00, 1.127E+00, 1.163E+00, 1.191E+00, 1.212E+00, 1.241E+00, 1.255E+00, 1.270E+00, 1.274E+00, 1.273E+00, 1.272E+00, 1.268E+00, 1.278E+00, 1.250E+00, 1.223E+00, 1.171E+00, 1.111E+00, 1.036E+00, 9.706E-01, 9.104E-01, 8.681E-01, 8.332E-01, 7.862E-01, 7.510E-01, 7.602E-01, 7.926E-01, 8.584E-01, 9.577E-01, 1.096E+00, 1.256E+00, 1.416E+00, 1.494E+00, 1.526E+00, 1.468E+00, 1.336E+00, 1.152E+00, 9.528E-01, 7.484E-01, 5.701E-01, 4.122E-01, 2.880E-01, 1.984E-01, 1.374E-01, 9.694E-02, 6.917E-02, 5.072E-02, 3.857E-02, 2.990E-02, 2.407E-02, 1.711E-02, 1.255E-02, 1.081E-02, 9.624E-03, 8.906E-03, 8.153E-03, 8.132E-03, 7.845E-03, 7.748E-03, 6.232E-03, 5.267E-03, 5.608E-03, 6.070E-03, 6.121E-03, 6.164E-03},
//      {1.672E-01, 4.002E+00, 3.617E+00, 2.548E+00, 1.509E+00, 1.493E+00, 1.296E+00, 1.240E+00, 6.044E-01, 1.455E+00, 1.498E+00, 1.488E+00, 1.340E+00, 1.174E+00, 1.086E+00, 1.052E+00, 1.083E+00, 1.128E+00, 1.168E+00, 1.181E+00, 1.205E+00, 1.236E+00, 1.259E+00, 1.272E+00, 1.271E+00, 1.272E+00, 1.271E+00, 1.267E+00, 1.278E+00, 1.251E+00, 1.219E+00, 1.164E+00, 1.109E+00, 1.038E+00, 9.689E-01, 9.156E-01, 8.645E-01, 8.359E-01, 7.875E-01, 7.518E-01, 7.621E-01, 7.939E-01, 8.594E-01, 9.634E-01, 1.096E+00, 1.255E+00, 1.424E+00, 1.511E+00, 1.535E+00, 1.457E+00, 1.342E+00, 1.153E+00, 9.464E-01, 7.538E-01, 5.673E-01, 4.094E-01, 2.882E-01, 1.995E-01, 1.377E-01, 9.630E-02, 6.899E-02, 5.090E-02, 3.856E-02, 2.996E-02, 2.428E-02, 1.692E-02, 1.250E-02, 1.081E-02, 9.817E-03, 8.680E-03, 8.324E-03, 8.295E-03, 7.672E-03, 7.872E-03, 6.039E-03, 5.129E-03, 5.624E-03, 5.494E-03, 6.660E-03, 5.473E-03},
//      {2.758E-04, 2.979E-02, 4.481E-02, 7.384E-02, 6.863E-02, 1.116E-01, 1.301E-01, 1.552E-01, 1.058E-01, 3.333E-01, 5.015E-01, 6.410E-01, 6.712E-01, 7.089E-01, 7.387E-01, 8.027E-01, 9.054E-01, 9.982E-01, 1.086E+00, 1.149E+00, 1.200E+00, 1.257E+00, 1.302E+00, 1.324E+00, 1.342E+00, 1.344E+00, 1.353E+00, 1.352E+00, 1.366E+00, 1.349E+00, 1.320E+00, 1.250E+00, 1.194E+00, 1.130E+00, 1.055E+00, 9.941E-01, 9.461E-01, 9.058E-01, 8.535E-01, 8.164E-01, 8.234E-01, 8.614E-01, 9.270E-01, 1.046E+00, 1.190E+00, 1.357E+00, 1.530E+00, 1.580E+00, 1.623E+00, 1.552E+00, 1.396E+00, 1.203E+00, 9.963E-01, 7.804E-01, 5.990E-01, 4.260E-01, 3.034E-01, 2.091E-01, 1.455E-01, 1.023E-01, 7.260E-02, 5.320E-02, 4.007E-02, 3.055E-02, 2.303E-02, 1.753E-02, 1.254E-02, 1.085E-02, 8.972E-03, 8.785E-03, 7.276E-03, 6.235E-03, 5.168E-03, 6.401E-03, 3.540E-03, 3.876E-03, 2.529E-03, 1.391E-03, 1.006E-03, 5.000E-04},
//      {2.494E-04, 3.158E-02, 3.862E-02, 5.765E-02, 7.191E-02, 1.117E-01, 1.001E-01, 1.299E-01, 1.084E-01, 3.222E-01, 4.813E-01, 6.202E-01, 6.505E-01, 7.113E-01, 7.297E-01, 7.877E-01, 9.025E-01, 1.013E+00, 1.094E+00, 1.148E+00, 1.211E+00, 1.252E+00, 1.304E+00, 1.336E+00, 1.347E+00, 1.356E+00, 1.354E+00, 1.365E+00, 1.369E+00, 1.351E+00, 1.328E+00, 1.258E+00, 1.202E+00, 1.130E+00, 1.059E+00, 9.882E-01, 9.494E-01, 9.124E-01, 8.601E-01, 8.192E-01, 8.230E-01, 8.637E-01, 9.387E-01, 1.048E+00, 1.188E+00, 1.354E+00, 1.540E+00, 1.616E+00, 1.634E+00, 1.572E+00, 1.388E+00, 1.224E+00, 1.001E+00, 7.875E-01, 5.981E-01, 4.347E-01, 3.054E-01, 2.086E-01, 1.461E-01, 1.012E-01, 7.329E-02, 5.338E-02, 4.046E-02, 3.013E-02, 2.390E-02, 1.758E-02, 1.241E-02, 1.099E-02, 9.904E-03, 8.385E-03, 7.029E-03, 5.092E-03, 5.896E-03, 4.427E-03, 3.156E-03, 3.957E-03, 2.318E-03, 2.368E-03, 1.121E-03, 5.284E-04},
//      {2.960E-04, 4.661E-02, 5.142E-02, 7.836E-02, 7.650E-02, 1.158E-01, 1.384E-01, 1.598E-01, 1.298E-01, 4.088E-01, 5.108E-01, 6.759E-01, 7.111E-01, 7.069E-01, 7.569E-01, 8.221E-01, 9.024E-01, 9.951E-01, 1.083E+00, 1.143E+00, 1.196E+00, 1.243E+00, 1.290E+00, 1.319E+00, 1.335E+00, 1.333E+00, 1.349E+00, 1.351E+00, 1.349E+00, 1.339E+00, 1.312E+00, 1.253E+00, 1.187E+00, 1.126E+00, 1.046E+00, 9.803E-01, 9.405E-01, 9.074E-01, 8.515E-01, 8.155E-01, 8.172E-01, 8.621E-01, 9.268E-01, 1.040E+00, 1.184E+00, 1.351E+00, 1.528E+00, 1.601E+00, 1.645E+00, 1.555E+00, 1.395E+00, 1.202E+00, 1.009E+00, 7.834E-01, 5.907E-01, 4.264E-01, 3.005E-01, 2.080E-01, 1.442E-01, 1.016E-01, 7.377E-02, 5.274E-02, 4.028E-02, 2.943E-02, 2.345E-02, 1.733E-02, 1.304E-02, 1.089E-02, 9.218E-03, 8.375E-03, 7.196E-03, 4.961E-03, 5.212E-03, 4.817E-03, 2.602E-03, 3.627E-03, 2.491E-03, 2.361E-03, 6.611E-04, 6.415E-04},
//      {2.894E-04, 4.360E-02, 5.014E-02, 6.912E-02, 8.141E-02, 1.445E-01, 1.405E-01, 1.480E-01, 1.039E-01, 3.417E-01, 4.570E-01, 6.214E-01, 6.927E-01, 6.701E-01, 6.820E-01, 8.060E-01, 8.304E-01, 9.961E-01, 1.076E+00, 1.131E+00, 1.193E+00, 1.219E+00, 1.294E+00, 1.326E+00, 1.323E+00, 1.350E+00, 1.362E+00, 1.348E+00, 1.360E+00, 1.339E+00, 1.311E+00, 1.262E+00, 1.185E+00, 1.131E+00, 1.058E+00, 1.002E+00, 9.544E-01, 9.065E-01, 8.609E-01, 8.214E-01, 8.346E-01, 8.601E-01, 9.398E-01, 1.059E+00, 1.200E+00, 1.364E+00, 1.510E+00, 1.641E+00, 1.590E+00, 1.542E+00, 1.397E+00, 1.237E+00, 1.003E+00, 8.001E-01, 5.921E-01, 4.271E-01, 3.083E-01, 2.139E-01, 1.458E-01, 1.017E-01, 7.216E-02, 5.370E-02, 4.107E-02, 3.045E-02, 2.474E-02, 1.765E-02, 1.298E-02, 1.070E-02, 9.453E-03, 9.417E-03, 7.668E-03, 4.481E-03, 3.087E-03, 6.682E-03, 3.068E-03, 1.882E-03, 1.948E-03, 5.821E-03, 1.565E-03, 3.780E-04},
//      {1.800E-01, 3.572E+00, 3.238E+00, 2.501E+00, 1.587E+00, 1.524E+00, 1.259E+00, 1.234E+00, 6.249E-01, 1.469E+00, 1.489E+00, 1.493E+00, 1.332E+00, 1.168E+00, 1.077E+00, 1.050E+00, 1.085E+00, 1.129E+00, 1.164E+00, 1.190E+00, 1.213E+00, 1.238E+00, 1.258E+00, 1.270E+00, 1.275E+00, 1.274E+00, 1.272E+00, 1.267E+00, 1.276E+00, 1.252E+00, 1.223E+00, 1.169E+00, 1.110E+00, 1.035E+00, 9.696E-01, 9.107E-01, 8.679E-01, 8.329E-01, 7.873E-01, 7.513E-01, 7.580E-01, 7.947E-01, 8.584E-01, 9.582E-01, 1.093E+00, 1.255E+00, 1.420E+00, 1.496E+00, 1.525E+00, 1.468E+00, 1.336E+00, 1.156E+00, 9.496E-01, 7.491E-01, 5.688E-01, 4.106E-01, 2.897E-01, 1.987E-01, 1.380E-01, 9.650E-02, 6.927E-02, 5.094E-02, 3.836E-02, 2.994E-02, 2.412E-02, 1.694E-02, 1.244E-02, 1.079E-02, 9.658E-03, 8.864E-03, 8.303E-03, 8.066E-03, 7.846E-03, 7.957E-03, 6.113E-03, 5.381E-03, 5.472E-03, 5.358E-03, 5.970E-03, 6.237E-03},
//      {2.605E-04, 2.631E-02, 3.681E-02, 4.785E-02, 7.677E-02, 1.316E-01, 9.301E-02, 1.018E-01, 1.079E-01, 4.031E-01, 4.383E-01, 6.138E-01, 6.870E-01, 7.113E-01, 7.262E-01, 8.072E-01, 8.834E-01, 9.917E-01, 1.070E+00, 1.134E+00, 1.185E+00, 1.256E+00, 1.307E+00, 1.338E+00, 1.329E+00, 1.353E+00, 1.370E+00, 1.381E+00, 1.371E+00, 1.359E+00, 1.336E+00, 1.252E+00, 1.208E+00, 1.133E+00, 1.066E+00, 9.925E-01, 9.398E-01, 9.187E-01, 8.526E-01, 8.198E-01, 8.374E-01, 8.628E-01, 9.381E-01, 1.055E+00, 1.208E+00, 1.350E+00, 1.567E+00, 1.627E+00, 1.624E+00, 1.558E+00, 1.401E+00, 1.214E+00, 1.002E+00, 7.880E-01, 5.921E-01, 4.393E-01, 3.076E-01, 2.087E-01, 1.429E-01, 1.036E-01, 7.355E-02, 5.130E-02, 3.955E-02, 3.146E-02, 2.366E-02, 1.726E-02, 1.258E-02, 1.092E-02, 1.015E-02, 9.365E-03, 6.013E-03, 3.590E-03, 4.496E-03, 4.837E-03, 6.140E-03, 4.341E-03, 1.343E-03, 4.228E-03, 5.226E-04, 7.545E-04},
//      {2.607E-04, 2.222E-02, 4.369E-02, 5.655E-02, 7.639E-02, 9.580E-02, 1.022E-01, 1.921E-01, 1.312E-01, 3.306E-01, 5.204E-01, 6.816E-01, 6.607E-01, 6.635E-01, 7.260E-01, 7.893E-01, 9.209E-01, 1.004E+00, 1.098E+00, 1.158E+00, 1.206E+00, 1.268E+00, 1.289E+00, 1.328E+00, 1.341E+00, 1.340E+00, 1.358E+00, 1.349E+00, 1.383E+00, 1.356E+00, 1.331E+00, 1.242E+00, 1.211E+00, 1.133E+00, 1.049E+00, 9.995E-01, 9.512E-01, 9.076E-01, 8.579E-01, 8.202E-01, 8.377E-01, 8.753E-01, 9.439E-01, 1.041E+00, 1.193E+00, 1.341E+00, 1.525E+00, 1.574E+00, 1.593E+00, 1.569E+00, 1.366E+00, 1.206E+00, 1.021E+00, 7.956E-01, 6.034E-01, 4.278E-01, 3.102E-01, 2.086E-01, 1.461E-01, 1.031E-01, 7.383E-02, 5.028E-02, 4.112E-02, 3.090E-02, 2.154E-02, 1.732E-02, 1.306E-02, 1.068E-02, 9.153E-03, 8.133E-03, 6.713E-03, 5.319E-03, 3.989E-03, 8.444E-03, 1.941E-03, 4.946E-03, 2.976E-03, 3.784E-03, 5.910E-04, 2.521E-04},
//      {1.780E-01, 5.124E+00, 3.340E+00, 2.752E+00, 1.532E+00, 1.502E+00, 1.283E+00, 1.247E+00, 6.408E-01, 1.423E+00, 1.493E+00, 1.501E+00, 1.316E+00, 1.161E+00, 1.081E+00, 1.048E+00, 1.081E+00, 1.129E+00, 1.170E+00, 1.190E+00, 1.214E+00, 1.239E+00, 1.258E+00, 1.269E+00, 1.274E+00, 1.270E+00, 1.265E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.220E+00, 1.173E+00, 1.111E+00, 1.039E+00, 9.675E-01, 9.125E-01, 8.687E-01, 8.348E-01, 7.882E-01, 7.476E-01, 7.592E-01, 7.946E-01, 8.570E-01, 9.614E-01, 1.095E+00, 1.257E+00, 1.418E+00, 1.502E+00, 1.533E+00, 1.460E+00, 1.343E+00, 1.154E+00, 9.496E-01, 7.457E-01, 5.701E-01, 4.112E-01, 2.882E-01, 1.982E-01, 1.382E-01, 9.659E-02, 6.902E-02, 5.065E-02, 3.841E-02, 3.010E-02, 2.401E-02, 1.713E-02, 1.250E-02, 1.079E-02, 9.623E-03, 8.901E-03, 8.297E-03, 8.180E-03, 7.698E-03, 7.869E-03, 6.500E-03, 5.429E-03, 5.453E-03, 5.933E-03, 5.511E-03, 5.550E-03},
//      {1.829E-01, 3.581E+00, 3.653E+00, 2.510E+00, 1.605E+00, 1.528E+00, 1.253E+00, 1.264E+00, 6.156E-01, 1.469E+00, 1.500E+00, 1.473E+00, 1.340E+00, 1.166E+00, 1.074E+00, 1.057E+00, 1.075E+00, 1.127E+00, 1.169E+00, 1.188E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.272E+00, 1.272E+00, 1.272E+00, 1.270E+00, 1.266E+00, 1.275E+00, 1.250E+00, 1.224E+00, 1.167E+00, 1.110E+00, 1.039E+00, 9.682E-01, 9.119E-01, 8.667E-01, 8.359E-01, 7.903E-01, 7.499E-01, 7.578E-01, 7.936E-01, 8.595E-01, 9.557E-01, 1.098E+00, 1.254E+00, 1.419E+00, 1.500E+00, 1.529E+00, 1.462E+00, 1.339E+00, 1.152E+00, 9.470E-01, 7.516E-01, 5.683E-01, 4.100E-01, 2.894E-01, 1.993E-01, 1.372E-01, 9.685E-02, 6.914E-02, 5.076E-02, 3.851E-02, 2.990E-02, 2.414E-02, 1.714E-02, 1.249E-02, 1.084E-02, 9.637E-03, 8.826E-03, 8.251E-03, 7.945E-03, 7.913E-03, 7.839E-03, 6.205E-03, 5.395E-03, 5.376E-03, 5.855E-03, 5.805E-03, 5.727E-03},
//      {2.326E-04, 2.787E-02, 3.339E-02, 5.035E-02, 6.247E-02, 9.966E-02, 1.074E-01, 1.442E-01, 1.041E-01, 3.121E-01, 4.634E-01, 6.124E-01, 6.707E-01, 6.990E-01, 7.462E-01, 8.168E-01, 9.110E-01, 1.022E+00, 1.100E+00, 1.156E+00, 1.212E+00, 1.261E+00, 1.307E+00, 1.336E+00, 1.353E+00, 1.354E+00, 1.353E+00, 1.360E+00, 1.376E+00, 1.354E+00, 1.326E+00, 1.264E+00, 1.198E+00, 1.132E+00, 1.062E+00, 9.996E-01, 9.498E-01, 9.122E-01, 8.609E-01, 8.217E-01, 8.276E-01, 8.657E-01, 9.451E-01, 1.048E+00, 1.196E+00, 1.360E+00, 1.538E+00, 1.600E+00, 1.634E+00, 1.581E+00, 1.403E+00, 1.211E+00, 9.999E-01, 7.865E-01, 5.984E-01, 4.296E-01, 3.034E-01, 2.107E-01, 1.463E-01, 1.024E-01, 7.337E-02, 5.378E-02, 4.052E-02, 3.077E-02, 2.339E-02, 1.753E-02, 1.269E-02, 1.092E-02, 9.353E-03, 9.002E-03, 7.919E-03, 4.869E-03, 6.104E-03, 4.942E-03, 3.426E-03, 2.660E-03, 2.304E-03, 2.039E-03, 1.059E-03, 5.481E-04},
//      {2.328E-04, 3.090E-02, 4.163E-02, 4.817E-02, 5.984E-02, 9.593E-02, 1.055E-01, 1.605E-01, 1.151E-01, 3.110E-01, 4.780E-01, 6.027E-01, 6.617E-01, 6.884E-01, 7.227E-01, 7.992E-01, 8.973E-01, 1.001E+00, 1.085E+00, 1.149E+00, 1.217E+00, 1.260E+00, 1.303E+00, 1.342E+00, 1.352E+00, 1.359E+00, 1.367E+00, 1.366E+00, 1.386E+00, 1.359E+00, 1.335E+00, 1.267E+00, 1.203E+00, 1.130E+00, 1.060E+00, 9.983E-01, 9.556E-01, 9.185E-01, 8.634E-01, 8.242E-01, 8.302E-01, 8.673E-01, 9.375E-01, 1.051E+00, 1.194E+00, 1.359E+00, 1.540E+00, 1.593E+00, 1.626E+00, 1.570E+00, 1.398E+00, 1.220E+00, 9.918E-01, 7.834E-01, 5.988E-01, 4.256E-01, 3.069E-01, 2.102E-01, 1.467E-01, 1.022E-01, 7.271E-02, 5.372E-02, 4.035E-02, 3.002E-02, 2.315E-02, 1.791E-02, 1.267E-02, 1.052E-02, 9.544E-03, 8.520E-03, 8.017E-03, 6.324E-03, 6.082E-03, 5.663E-03, 2.850E-03, 3.110E-03, 2.375E-03, 1.463E-03, 1.312E-03, 4.850E-04},
//      {2.564E-04, 3.837E-02, 3.059E-02, 5.322E-02, 6.786E-02, 9.388E-02, 1.256E-01, 1.484E-01, 1.033E-01, 3.382E-01, 4.688E-01, 6.103E-01, 6.883E-01, 6.948E-01, 7.502E-01, 8.297E-01, 9.089E-01, 9.969E-01, 1.095E+00, 1.143E+00, 1.203E+00, 1.262E+00, 1.306E+00, 1.333E+00, 1.348E+00, 1.344E+00, 1.349E+00, 1.360E+00, 1.371E+00, 1.356E+00, 1.326E+00, 1.267E+00, 1.197E+00, 1.129E+00, 1.052E+00, 9.949E-01, 9.485E-01, 9.147E-01, 8.563E-01, 8.183E-01, 8.310E-01, 8.650E-01, 9.384E-01, 1.046E+00, 1.197E+00, 1.363E+00, 1.533E+00, 1.615E+00, 1.624E+00, 1.580E+00, 1.390E+00, 1.200E+00, 1.008E+00, 7.782E-01, 5.965E-01, 4.190E-01, 3.025E-01, 2.105E-01, 1.457E-01, 1.019E-01, 7.269E-02, 5.390E-02, 4.059E-02, 3.069E-02, 2.300E-02, 1.719E-02, 1.252E-02, 1.121E-02, 9.765E-03, 7.860E-03, 8.231E-03, 5.744E-03, 4.478E-03, 5.989E-03, 2.354E-03, 2.470E-03, 1.666E-03, 2.406E-03, 1.619E-03, 3.990E-04},
//      {3.098E-04, 2.532E-02, 7.010E-02, 5.975E-02, 5.345E-02, 7.526E-02, 8.972E-02, 1.506E-01, 1.019E-01, 4.177E-01, 4.905E-01, 6.736E-01, 7.624E-01, 7.185E-01, 8.202E-01, 7.980E-01, 8.954E-01, 1.013E+00, 1.087E+00, 1.149E+00, 1.210E+00, 1.250E+00, 1.304E+00, 1.345E+00, 1.342E+00, 1.349E+00, 1.356E+00, 1.341E+00, 1.364E+00, 1.326E+00, 1.323E+00, 1.231E+00, 1.202E+00, 1.088E+00, 1.043E+00, 9.859E-01, 9.468E-01, 9.123E-01, 8.560E-01, 8.090E-01, 8.177E-01, 8.259E-01, 9.266E-01, 1.030E+00, 1.172E+00, 1.328E+00, 1.537E+00, 1.607E+00, 1.641E+00, 1.598E+00, 1.403E+00, 1.203E+00, 1.024E+00, 7.923E-01, 5.926E-01, 4.400E-01, 3.034E-01, 2.112E-01, 1.464E-01, 1.046E-01, 7.418E-02, 5.522E-02, 3.982E-02, 2.936E-02, 2.511E-02, 1.870E-02, 1.296E-02, 9.903E-03, 9.423E-03, 9.231E-03, 6.472E-03, 7.884E-03, 4.329E-03, 2.418E-03, 3.861E-03, 2.891E-03, 5.423E-04, 6.677E-03, 4.057E-04, 3.023E-04},
//      {4.708E-04, 1.701E+00, -1.578E+00, 9.121E-01, 7.486E-01, 5.589E-01, 6.530E-01, 7.658E-01, 3.456E-01, 8.560E-01, 7.973E-01, 8.156E-01, 7.265E-01, 7.858E-01, 1.014E+00, 1.050E+00, 1.065E+00, 1.061E+00, 1.177E+00, 1.207E+00, 1.204E+00, 1.295E+00, 1.282E+00, 1.308E+00, 1.332E+00, 1.341E+00, 1.295E+00, 1.213E+00, 1.124E+00, 1.338E+00, 1.282E+00, 1.244E+00, 9.802E-01, 1.026E+00, 1.055E+00, 9.854E-01, 9.301E-01, 8.898E-01, 7.931E-01, 7.788E-01, 7.278E-01, 8.297E-01, 9.476E-01, 1.002E+00, 1.184E+00, 1.341E+00, 1.580E+00, 1.553E+00, 1.629E+00, 1.606E+00, 1.476E+00, 1.237E+00, 9.413E-01, 7.969E-01, 5.947E-01, 4.415E-01, 3.248E-01, 2.170E-01, 1.507E-01, 1.046E-01, 6.915E-02, 5.408E-02, 1.983E-02, 3.311E-02, 2.035E-02, 1.957E-02, 1.242E-02, 1.083E-02, 8.955E-03, 6.824E-03, 8.855E-03, 8.707E-03, 6.040E-03, 1.291E-02, 7.450E-03, 4.775E-03, 5.259E-03, 4.108E-03, 5.489E-03, 5.481E-03},
//      {2.406E-04, 3.385E-02, 3.578E-02, 5.432E-02, 6.220E-02, 9.562E-02, 1.249E-01, 1.405E-01, 1.066E-01, 3.192E-01, 4.762E-01, 6.200E-01, 6.800E-01, 7.151E-01, 7.432E-01, 7.980E-01, 8.981E-01, 1.007E+00, 1.090E+00, 1.145E+00, 1.208E+00, 1.252E+00, 1.304E+00, 1.329E+00, 1.345E+00, 1.349E+00, 1.354E+00, 1.362E+00, 1.372E+00, 1.359E+00, 1.325E+00, 1.259E+00, 1.200E+00, 1.133E+00, 1.059E+00, 9.963E-01, 9.505E-01, 9.115E-01, 8.607E-01, 8.247E-01, 8.266E-01, 8.668E-01, 9.347E-01, 1.045E+00, 1.196E+00, 1.369E+00, 1.551E+00, 1.602E+00, 1.626E+00, 1.571E+00, 1.409E+00, 1.217E+00, 1.005E+00, 7.886E-01, 6.010E-01, 4.290E-01, 3.019E-01, 2.112E-01, 1.465E-01, 1.022E-01, 7.362E-02, 5.391E-02, 4.057E-02, 3.021E-02, 2.415E-02, 1.752E-02, 1.257E-02, 1.084E-02, 9.528E-03, 8.775E-03, 7.496E-03, 5.919E-03, 5.381E-03, 5.185E-03, 4.161E-03, 3.090E-03, 1.867E-03, 1.701E-03, 9.188E-04, 5.315E-04},
//      {2.315E-01, 3.072E+00, 2.850E+00, 2.379E+00, 1.814E+00, 1.427E+00, 1.502E+00, 1.198E+00, 6.637E-01, 1.478E+00, 1.465E+00, 1.593E+00, 1.334E+00, 1.162E+00, 1.089E+00, 1.052E+00, 1.074E+00, 1.133E+00, 1.161E+00, 1.196E+00, 1.212E+00, 1.235E+00, 1.260E+00, 1.276E+00, 1.285E+00, 1.278E+00, 1.270E+00, 1.259E+00, 1.272E+00, 1.265E+00, 1.203E+00, 1.151E+00, 1.119E+00, 1.035E+00, 9.633E-01, 9.135E-01, 8.644E-01, 8.412E-01, 7.865E-01, 7.494E-01, 7.635E-01, 7.874E-01, 8.475E-01, 9.577E-01, 1.104E+00, 1.274E+00, 1.419E+00, 1.490E+00, 1.524E+00, 1.496E+00, 1.342E+00, 1.169E+00, 9.458E-01, 7.514E-01, 5.769E-01, 4.126E-01, 2.925E-01, 2.000E-01, 1.368E-01, 9.616E-02, 6.762E-02, 5.076E-02, 3.781E-02, 2.879E-02, 2.332E-02, 1.717E-02, 1.265E-02, 1.079E-02, 9.486E-03, 9.464E-03, 8.739E-03, 8.339E-03, 8.351E-03, 7.462E-03, 7.104E-03, 5.085E-03, 4.805E-03, 6.677E-03, 5.575E-03, 5.164E-03},
//      {2.174E-01, 2.227E+00, 2.479E+00, 2.328E+00, 1.704E+00, 1.940E+00, 1.549E+00, 1.289E+00, 5.517E-01, 1.441E+00, 1.490E+00, 1.434E+00, 1.362E+00, 1.171E+00, 1.073E+00, 1.050E+00, 1.080E+00, 1.120E+00, 1.159E+00, 1.167E+00, 1.210E+00, 1.239E+00, 1.259E+00, 1.290E+00, 1.269E+00, 1.256E+00, 1.265E+00, 1.263E+00, 1.287E+00, 1.244E+00, 1.225E+00, 1.178E+00, 1.111E+00, 1.037E+00, 9.787E-01, 9.073E-01, 8.541E-01, 8.298E-01, 7.933E-01, 7.530E-01, 7.696E-01, 7.966E-01, 8.582E-01, 9.675E-01, 1.092E+00, 1.266E+00, 1.416E+00, 1.513E+00, 1.557E+00, 1.461E+00, 1.341E+00, 1.135E+00, 9.446E-01, 7.411E-01, 5.572E-01, 4.133E-01, 2.920E-01, 1.992E-01, 1.383E-01, 9.723E-02, 6.830E-02, 5.173E-02, 3.840E-02, 3.008E-02, 2.393E-02, 1.743E-02, 1.259E-02, 1.057E-02, 9.381E-03, 8.891E-03, 8.430E-03, 7.669E-03, 8.314E-03, 8.597E-03, 6.436E-03, 6.161E-03, 5.354E-03, 5.808E-03, 7.759E-03, 4.967E-03},
//      {1.572E-01, 2.823E+00, 3.055E+00, 2.295E+00, 1.478E+00, 1.373E+00, 1.264E+00, 1.132E+00, 6.411E-01, 1.457E+00, 1.430E+00, 1.465E+00, 1.362E+00, 1.154E+00, 1.093E+00, 1.051E+00, 1.061E+00, 1.118E+00, 1.178E+00, 1.191E+00, 1.207E+00, 1.267E+00, 1.251E+00, 1.274E+00, 1.267E+00, 1.288E+00, 1.274E+00, 1.276E+00, 1.269E+00, 1.253E+00, 1.226E+00, 1.163E+00, 1.108E+00, 1.031E+00, 9.792E-01, 9.190E-01, 8.577E-01, 8.364E-01, 7.998E-01, 7.505E-01, 7.587E-01, 7.996E-01, 8.608E-01, 9.585E-01, 1.094E+00, 1.239E+00, 1.403E+00, 1.476E+00, 1.520E+00, 1.470E+00, 1.327E+00, 1.124E+00, 9.653E-01, 7.601E-01, 5.713E-01, 4.137E-01, 2.874E-01, 1.990E-01, 1.410E-01, 9.522E-02, 6.876E-02, 4.921E-02, 3.726E-02, 2.983E-02, 2.373E-02, 1.658E-02, 1.257E-02, 1.075E-02, 9.609E-03, 8.271E-03, 8.340E-03, 8.770E-03, 7.378E-03, 7.303E-03, 5.912E-03, 5.315E-03, 7.372E-03, 6.092E-03, 5.033E-03, 5.305E-03},
//      {2.160E-01, 2.263E+00, 1.119E+01, 2.336E+00, 1.736E+00, 1.510E+00, 1.077E+00, 1.176E+00, 7.053E-01, 1.423E+00, 1.569E+00, 1.440E+00, 1.375E+00, 1.159E+00, 1.075E+00, 1.069E+00, 1.062E+00, 1.133E+00, 1.158E+00, 1.204E+00, 1.216E+00, 1.240E+00, 1.263E+00, 1.282E+00, 1.286E+00, 1.287E+00, 1.260E+00, 1.280E+00, 1.266E+00, 1.247E+00, 1.234E+00, 1.178E+00, 1.121E+00, 1.030E+00, 9.682E-01, 9.054E-01, 8.685E-01, 8.296E-01, 7.917E-01, 7.498E-01, 7.487E-01, 7.899E-01, 8.571E-01, 9.687E-01, 1.098E+00, 1.254E+00, 1.410E+00, 1.492E+00, 1.542E+00, 1.455E+00, 1.350E+00, 1.139E+00, 9.516E-01, 7.482E-01, 5.658E-01, 4.106E-01, 2.926E-01, 1.957E-01, 1.395E-01, 9.392E-02, 6.780E-02, 5.034E-02, 3.757E-02, 3.000E-02, 2.382E-02, 1.738E-02, 1.216E-02, 1.105E-02, 9.388E-03, 8.357E-03, 8.885E-03, 8.099E-03, 7.050E-03, 6.724E-03, 6.228E-03, 4.828E-03, 5.222E-03, 5.245E-03, 7.617E-03, 7.289E-03},
//      {2.423E-01, 4.315E+00, 2.464E+00, 2.864E+00, 1.174E+00, 1.485E+00, 1.268E+00, 1.222E+00, 5.845E-01, 1.453E+00, 1.426E+00, 1.488E+00, 1.321E+00, 1.167E+00, 1.076E+00, 1.052E+00, 1.066E+00, 1.122E+00, 1.151E+00, 1.206E+00, 1.209E+00, 1.239E+00, 1.250E+00, 1.286E+00, 1.282E+00, 1.269E+00, 1.251E+00, 1.263E+00, 1.273E+00, 1.269E+00, 1.204E+00, 1.178E+00, 1.108E+00, 1.043E+00, 9.572E-01, 9.212E-01, 8.694E-01, 8.428E-01, 7.893E-01, 7.578E-01, 7.580E-01, 7.940E-01, 8.664E-01, 9.559E-01, 1.096E+00, 1.248E+00, 1.412E+00, 1.500E+00, 1.509E+00, 1.463E+00, 1.369E+00, 1.149E+00, 9.606E-01, 7.550E-01, 5.693E-01, 4.126E-01, 2.883E-01, 1.976E-01, 1.379E-01, 9.559E-02, 6.876E-02, 5.059E-02, 3.842E-02, 3.008E-02, 2.387E-02, 1.667E-02, 1.304E-02, 1.021E-02, 1.031E-02, 8.361E-03, 8.001E-03, 8.146E-03, 7.446E-03, 8.348E-03, 5.815E-03, 4.387E-03, 4.728E-03, 6.252E-03, 4.515E-03, 5.561E-03},
//      {1.617E-01, 4.064E+00, 2.742E+00, 2.266E+00, 1.559E+00, 1.377E+00, 1.402E+00, 1.178E+00, 6.902E-01, 1.501E+00, 1.659E+00, 1.587E+00, 1.368E+00, 1.170E+00, 1.114E+00, 1.061E+00, 1.092E+00, 1.130E+00, 1.172E+00, 1.207E+00, 1.183E+00, 1.234E+00, 1.261E+00, 1.254E+00, 1.287E+00, 1.263E+00, 1.272E+00, 1.246E+00, 1.266E+00, 1.262E+00, 1.218E+00, 1.166E+00, 1.121E+00, 1.039E+00, 9.762E-01, 8.993E-01, 8.753E-01, 8.349E-01, 7.893E-01, 7.575E-01, 7.539E-01, 7.984E-01, 8.531E-01, 9.740E-01, 1.119E+00, 1.251E+00, 1.404E+00, 1.488E+00, 1.556E+00, 1.446E+00, 1.355E+00, 1.132E+00, 9.286E-01, 7.537E-01, 5.683E-01, 4.106E-01, 2.881E-01, 1.966E-01, 1.355E-01, 9.763E-02, 6.776E-02, 5.132E-02, 3.890E-02, 2.995E-02, 2.371E-02, 1.746E-02, 1.324E-02, 1.051E-02, 9.834E-03, 8.969E-03, 7.766E-03, 7.762E-03, 8.075E-03, 9.524E-03, 8.243E-03, 5.045E-03, 5.098E-03, 4.711E-03, 4.371E-03, 6.547E-03},
//      {3.073E-01, 2.023E+00, 2.628E+00, 2.467E+00, 1.432E+00, 1.146E+00, 1.139E+00, 1.750E+00, 5.444E-01, 1.307E+00, 1.464E+00, 1.483E+00, 1.358E+00, 1.188E+00, 1.069E+00, 1.036E+00, 1.110E+00, 1.127E+00, 1.156E+00, 1.209E+00, 1.195E+00, 1.237E+00, 1.262E+00, 1.289E+00, 1.287E+00, 1.264E+00, 1.262E+00, 1.249E+00, 1.281E+00, 1.250E+00, 1.228E+00, 1.186E+00, 1.097E+00, 1.033E+00, 9.705E-01, 9.052E-01, 8.553E-01, 8.536E-01, 7.986E-01, 7.560E-01, 7.652E-01, 8.156E-01, 8.463E-01, 9.698E-01, 1.088E+00, 1.243E+00, 1.417E+00, 1.469E+00, 1.544E+00, 1.439E+00, 1.331E+00, 1.134E+00, 9.276E-01, 7.655E-01, 5.659E-01, 4.075E-01, 2.903E-01, 1.991E-01, 1.353E-01, 9.565E-02, 6.819E-02, 5.082E-02, 3.936E-02, 2.947E-02, 2.426E-02, 1.780E-02, 1.251E-02, 1.031E-02, 1.034E-02, 9.703E-03, 8.115E-03, 7.457E-03, 6.907E-03, 6.714E-03, 5.733E-03, 7.032E-03, 5.893E-03, 4.560E-03, 7.615E-03, 4.148E-03},
//      {1.575E-01, 2.376E+00, 5.511E+00, 4.140E+00, 2.222E+00, 1.022E+00, 1.414E+00, 1.012E+00, 5.570E-01, 1.627E+00, 1.349E+00, 1.507E+00, 1.347E+00, 1.251E+00, 1.103E+00, 1.054E+00, 1.092E+00, 1.122E+00, 1.182E+00, 1.167E+00, 1.212E+00, 1.234E+00, 1.264E+00, 1.287E+00, 1.260E+00, 1.284E+00, 1.277E+00, 1.250E+00, 1.300E+00, 1.262E+00, 1.246E+00, 1.159E+00, 1.099E+00, 1.041E+00, 9.627E-01, 9.212E-01, 8.749E-01, 8.307E-01, 7.929E-01, 7.360E-01, 7.686E-01, 7.892E-01, 8.466E-01, 9.500E-01, 1.047E+00, 1.288E+00, 1.426E+00, 1.505E+00, 1.517E+00, 1.455E+00, 1.287E+00, 1.121E+00, 9.316E-01, 7.538E-01, 5.805E-01, 4.069E-01, 2.963E-01, 1.982E-01, 1.402E-01, 9.389E-02, 6.983E-02, 5.031E-02, 3.893E-02, 3.000E-02, 2.573E-02, 1.678E-02, 1.244E-02, 1.088E-02, 9.356E-03, 8.698E-03, 8.022E-03, 6.875E-03, 1.100E-02, 9.955E-03, 7.337E-03, 4.677E-03, 6.427E-03, 6.148E-03, 8.214E-03, 3.827E-03},
//      {1.870E-01, 4.744E+00, 3.217E+00, 2.383E+00, 1.802E+00, 1.486E+00, 1.329E+00, 1.205E+00, 6.102E-01, 1.495E+00, 1.516E+00, 1.478E+00, 1.319E+00, 1.164E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.130E+00, 1.165E+00, 1.189E+00, 1.212E+00, 1.236E+00, 1.258E+00, 1.271E+00, 1.271E+00, 1.272E+00, 1.272E+00, 1.268E+00, 1.277E+00, 1.253E+00, 1.221E+00, 1.169E+00, 1.109E+00, 1.039E+00, 9.688E-01, 9.133E-01, 8.658E-01, 8.371E-01, 7.900E-01, 7.512E-01, 7.587E-01, 7.925E-01, 8.574E-01, 9.586E-01, 1.093E+00, 1.257E+00, 1.420E+00, 1.493E+00, 1.527E+00, 1.462E+00, 1.338E+00, 1.155E+00, 9.495E-01, 7.493E-01, 5.703E-01, 4.107E-01, 2.901E-01, 1.994E-01, 1.376E-01, 9.651E-02, 6.895E-02, 5.073E-02, 3.841E-02, 2.999E-02, 2.412E-02, 1.701E-02, 1.244E-02, 1.072E-02, 9.630E-03, 8.829E-03, 8.312E-03, 8.101E-03, 7.724E-03, 7.905E-03, 6.299E-03, 5.287E-03, 5.476E-03, 5.776E-03, 5.866E-03, 6.320E-03},
//      {1.913E-01, 4.255E+00, 3.444E+00, 2.481E+00, 1.640E+00, 1.531E+00, 1.288E+00, 1.270E+00, 5.997E-01, 1.442E+00, 1.477E+00, 1.476E+00, 1.330E+00, 1.169E+00, 1.083E+00, 1.051E+00, 1.078E+00, 1.126E+00, 1.166E+00, 1.188E+00, 1.211E+00, 1.238E+00, 1.256E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.271E+00, 1.267E+00, 1.274E+00, 1.254E+00, 1.220E+00, 1.167E+00, 1.113E+00, 1.037E+00, 9.688E-01, 9.129E-01, 8.681E-01, 8.336E-01, 7.865E-01, 7.516E-01, 7.576E-01, 7.948E-01, 8.593E-01, 9.561E-01, 1.097E+00, 1.258E+00, 1.421E+00, 1.492E+00, 1.534E+00, 1.461E+00, 1.341E+00, 1.156E+00, 9.519E-01, 7.507E-01, 5.693E-01, 4.101E-01, 2.896E-01, 1.981E-01, 1.374E-01, 9.658E-02, 6.937E-02, 5.074E-02, 3.867E-02, 2.989E-02, 2.413E-02, 1.713E-02, 1.250E-02, 1.076E-02, 9.502E-03, 8.767E-03, 8.258E-03, 8.063E-03, 7.855E-03, 7.777E-03, 6.306E-03, 5.442E-03, 5.528E-03, 5.516E-03, 6.168E-03, 5.712E-03},
//      {1.898E-01, 4.165E+00, 3.239E+00, 2.648E+00, 1.610E+00, 1.494E+00, 1.289E+00, 1.238E+00, 6.235E-01, 1.438E+00, 1.486E+00, 1.484E+00, 1.339E+00, 1.165E+00, 1.076E+00, 1.050E+00, 1.080E+00, 1.129E+00, 1.168E+00, 1.188E+00, 1.213E+00, 1.239E+00, 1.262E+00, 1.272E+00, 1.272E+00, 1.269E+00, 1.273E+00, 1.266E+00, 1.276E+00, 1.250E+00, 1.221E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.687E-01, 9.137E-01, 8.687E-01, 8.352E-01, 7.870E-01, 7.480E-01, 7.602E-01, 7.922E-01, 8.591E-01, 9.607E-01, 1.091E+00, 1.255E+00, 1.415E+00, 1.496E+00, 1.528E+00, 1.460E+00, 1.339E+00, 1.154E+00, 9.493E-01, 7.497E-01, 5.703E-01, 4.105E-01, 2.896E-01, 1.985E-01, 1.373E-01, 9.672E-02, 6.940E-02, 5.067E-02, 3.834E-02, 3.009E-02, 2.403E-02, 1.718E-02, 1.255E-02, 1.087E-02, 9.529E-03, 8.865E-03, 8.370E-03, 7.970E-03, 7.921E-03, 7.850E-03, 6.155E-03, 5.393E-03, 5.518E-03, 5.859E-03, 5.714E-03, 6.418E-03},
//      {1.897E-01, 3.957E+00, 3.856E+00, 2.684E+00, 1.643E+00, 1.480E+00, 1.304E+00, 1.284E+00, 6.124E-01, 1.434E+00, 1.497E+00, 1.483E+00, 1.326E+00, 1.166E+00, 1.080E+00, 1.051E+00, 1.074E+00, 1.126E+00, 1.163E+00, 1.187E+00, 1.212E+00, 1.238E+00, 1.260E+00, 1.268E+00, 1.274E+00, 1.274E+00, 1.270E+00, 1.269E+00, 1.277E+00, 1.252E+00, 1.224E+00, 1.171E+00, 1.110E+00, 1.038E+00, 9.698E-01, 9.114E-01, 8.652E-01, 8.348E-01, 7.895E-01, 7.498E-01, 7.574E-01, 7.921E-01, 8.594E-01, 9.566E-01, 1.096E+00, 1.260E+00, 1.419E+00, 1.496E+00, 1.534E+00, 1.465E+00, 1.340E+00, 1.157E+00, 9.516E-01, 7.506E-01, 5.693E-01, 4.110E-01, 2.894E-01, 1.974E-01, 1.380E-01, 9.660E-02, 6.948E-02, 5.088E-02, 3.837E-02, 2.965E-02, 2.417E-02, 1.699E-02, 1.248E-02, 1.080E-02, 9.539E-03, 8.775E-03, 8.265E-03, 8.058E-03, 7.837E-03, 7.898E-03, 6.202E-03, 5.428E-03, 5.554E-03, 5.352E-03, 5.705E-03, 6.037E-03},
//      {1.899E-01, 3.543E+00, 3.519E+00, 2.642E+00, 1.581E+00, 1.495E+00, 1.296E+00, 1.289E+00, 6.150E-01, 1.486E+00, 1.474E+00, 1.479E+00, 1.324E+00, 1.167E+00, 1.074E+00, 1.054E+00, 1.080E+00, 1.133E+00, 1.165E+00, 1.186E+00, 1.215E+00, 1.238E+00, 1.261E+00, 1.271E+00, 1.273E+00, 1.274E+00, 1.268E+00, 1.265E+00, 1.274E+00, 1.253E+00, 1.223E+00, 1.171E+00, 1.109E+00, 1.036E+00, 9.682E-01, 9.106E-01, 8.671E-01, 8.343E-01, 7.894E-01, 7.523E-01, 7.561E-01, 7.949E-01, 8.588E-01, 9.588E-01, 1.095E+00, 1.253E+00, 1.420E+00, 1.494E+00, 1.534E+00, 1.461E+00, 1.336E+00, 1.154E+00, 9.528E-01, 7.531E-01, 5.697E-01, 4.117E-01, 2.903E-01, 1.985E-01, 1.375E-01, 9.617E-02, 6.911E-02, 5.078E-02, 3.842E-02, 2.983E-02, 2.402E-02, 1.707E-02, 1.242E-02, 1.086E-02, 9.659E-03, 8.759E-03, 8.298E-03, 8.003E-03, 7.673E-03, 7.920E-03, 6.423E-03, 5.314E-03, 5.516E-03, 5.349E-03, 5.832E-03, 5.663E-03},
//    };


   pileupweightDn = { // 69.2 - 4.6%
     { 2.964E-04, 4.867E-02, 6.284E-02, 6.202E-02, 7.567E-02, 1.268E-01, 1.384E-01, 1.958E-01, 1.665E-01, 5.472E-01, 7.142E-01, 8.790E-01, 9.067E-01, 9.409E-01, 9.795E-01, 1.100E+00, 1.176E+00, 1.276E+00, 1.326E+00, 1.354E+00, 1.388E+00, 1.403E+00, 1.429E+00, 1.453E+00, 1.453E+00, 1.467E+00, 1.443E+00, 1.421E+00, 1.400E+00, 1.354E+00, 1.299E+00, 1.213E+00, 1.120E+00, 1.035E+00, 9.561E-01, 8.881E-01, 8.437E-01, 8.165E-01, 7.802E-01, 7.657E-01, 8.014E-01, 8.916E-01, 1.022E+00, 1.185E+00, 1.355E+00, 1.493E+00, 1.596E+00, 1.514E+00, 1.409E+00, 1.203E+00, 9.275E-01, 7.324E-01, 5.311E-01, 3.636E-01, 2.499E-01, 1.626E-01, 1.038E-01, 6.701E-02, 4.331E-02, 2.848E-02, 1.901E-02, 1.358E-02, 1.009E-02, 7.522E-03, 5.775E-03, 4.256E-03, 3.079E-03, 2.558E-03, 2.538E-03, 2.145E-03, 1.999E-03, 1.352E-03, 1.613E-03, 1.450E-03, 6.862E-04, 6.135E-04, 4.263E-04, 3.482E-04, 1.501E-04, 7.989E-05}, // DYJetsMG.root
     { 3.706E-04, 4.424E-02, 5.904E-02, 7.542E-02, 1.054E-01, 1.223E-01, 1.593E-01, 2.719E-01, 1.845E-01, 6.325E-01, 8.076E-01, 9.257E-01, 8.799E-01, 9.334E-01, 1.028E+00, 1.084E+00, 1.194E+00, 1.258E+00, 1.301E+00, 1.338E+00, 1.365E+00, 1.405E+00, 1.415E+00, 1.441E+00, 1.449E+00, 1.453E+00, 1.433E+00, 1.406E+00, 1.398E+00, 1.342E+00, 1.275E+00, 1.192E+00, 1.118E+00, 1.028E+00, 9.414E-01, 8.831E-01, 8.355E-01, 8.046E-01, 7.687E-01, 7.617E-01, 7.999E-01, 8.860E-01, 1.004E+00, 1.158E+00, 1.337E+00, 1.494E+00, 1.594E+00, 1.533E+00, 1.419E+00, 1.206E+00, 9.159E-01, 7.274E-01, 5.183E-01, 3.703E-01, 2.500E-01, 1.618E-01, 1.045E-01, 6.636E-02, 4.327E-02, 2.843E-02, 1.935E-02, 1.352E-02, 1.008E-02, 7.599E-03, 5.830E-03, 4.268E-03, 2.985E-03, 2.556E-03, 2.398E-03, 2.256E-03, 1.977E-03, 1.355E-03, 1.583E-03, 1.505E-03, 9.021E-04, 1.016E-03, 5.155E-04, 3.486E-04, 2.718E-04, 1.131E-04}, // QCD1000.root
     { 1.829E-01, 4.616E+00, 4.516E+00, 2.588E+00, 1.910E+00, 1.645E+00, 1.309E+00, 1.397E+00, 8.664E-01, 2.115E+00, 2.187E+00, 2.072E+00, 1.732E+00, 1.530E+00, 1.441E+00, 1.418E+00, 1.435E+00, 1.431E+00, 1.420E+00, 1.409E+00, 1.393E+00, 1.391E+00, 1.385E+00, 1.392E+00, 1.393E+00, 1.382E+00, 1.362E+00, 1.330E+00, 1.311E+00, 1.256E+00, 1.202E+00, 1.126E+00, 1.045E+00, 9.534E-01, 8.791E-01, 8.165E-01, 7.750E-01, 7.459E-01, 7.143E-01, 7.043E-01, 7.482E-01, 8.259E-01, 9.425E-01, 1.087E+00, 1.250E+00, 1.392E+00, 1.480E+00, 1.435E+00, 1.321E+00, 1.131E+00, 9.092E-01, 6.908E-01, 5.041E-01, 3.512E-01, 2.393E-01, 1.562E-01, 9.963E-02, 6.334E-02, 4.093E-02, 2.721E-02, 1.848E-02, 1.303E-02, 9.626E-03, 7.324E-03, 5.850E-03, 4.162E-03, 3.080E-03, 2.689E-03, 2.429E-03, 2.276E-03, 2.099E-03, 2.097E-03, 2.012E-03, 1.962E-03, 1.549E-03, 1.277E-03, 1.320E-03, 1.382E-03, 1.342E-03, 1.297E-03}, // QCD1500.root
     { 1.749E-01, 4.427E+00, 4.718E+00, 2.463E+00, 1.739E+00, 1.665E+00, 1.352E+00, 1.389E+00, 8.727E-01, 2.163E+00, 2.187E+00, 2.068E+00, 1.751E+00, 1.544E+00, 1.446E+00, 1.419E+00, 1.435E+00, 1.431E+00, 1.426E+00, 1.398E+00, 1.384E+00, 1.386E+00, 1.390E+00, 1.394E+00, 1.389E+00, 1.381E+00, 1.360E+00, 1.329E+00, 1.312E+00, 1.256E+00, 1.198E+00, 1.119E+00, 1.042E+00, 9.549E-01, 8.777E-01, 8.212E-01, 7.718E-01, 7.483E-01, 7.155E-01, 7.050E-01, 7.501E-01, 8.273E-01, 9.436E-01, 1.094E+00, 1.250E+00, 1.391E+00, 1.488E+00, 1.452E+00, 1.329E+00, 1.123E+00, 9.133E-01, 6.914E-01, 5.007E-01, 3.537E-01, 2.381E-01, 1.551E-01, 9.969E-02, 6.369E-02, 4.099E-02, 2.703E-02, 1.843E-02, 1.307E-02, 9.621E-03, 7.340E-03, 5.899E-03, 4.117E-03, 3.069E-03, 2.690E-03, 2.478E-03, 2.218E-03, 2.144E-03, 2.139E-03, 1.968E-03, 1.994E-03, 1.501E-03, 1.244E-03, 1.324E-03, 1.251E-03, 1.460E-03, 1.152E-03}, // QCD2000.root
     { 2.884E-04, 3.296E-02, 5.845E-02, 7.139E-02, 7.909E-02, 1.244E-01, 1.357E-01, 1.738E-01, 1.527E-01, 4.953E-01, 7.321E-01, 8.905E-01, 8.773E-01, 9.319E-01, 9.842E-01, 1.082E+00, 1.199E+00, 1.267E+00, 1.325E+00, 1.359E+00, 1.379E+00, 1.410E+00, 1.437E+00, 1.451E+00, 1.467E+00, 1.459E+00, 1.448E+00, 1.419E+00, 1.402E+00, 1.355E+00, 1.298E+00, 1.203E+00, 1.122E+00, 1.040E+00, 9.555E-01, 8.915E-01, 8.447E-01, 8.109E-01, 7.754E-01, 7.657E-01, 8.104E-01, 8.976E-01, 1.018E+00, 1.188E+00, 1.357E+00, 1.504E+00, 1.599E+00, 1.517E+00, 1.405E+00, 1.195E+00, 9.501E-01, 7.210E-01, 5.271E-01, 3.662E-01, 2.514E-01, 1.614E-01, 1.050E-01, 6.677E-02, 4.332E-02, 2.872E-02, 1.940E-02, 1.367E-02, 9.998E-03, 7.483E-03, 5.596E-03, 4.265E-03, 3.077E-03, 2.698E-03, 2.264E-03, 2.245E-03, 1.874E-03, 1.608E-03, 1.325E-03, 1.621E-03, 8.798E-04, 9.400E-04, 5.954E-04, 3.166E-04, 2.206E-04, 1.052E-04}, // QCD300.root
     { 2.608E-04, 3.494E-02, 5.037E-02, 5.574E-02, 8.287E-02, 1.245E-01, 1.044E-01, 1.455E-01, 1.566E-01, 4.788E-01, 7.026E-01, 8.616E-01, 8.502E-01, 9.351E-01, 9.723E-01, 1.062E+00, 1.195E+00, 1.286E+00, 1.336E+00, 1.358E+00, 1.391E+00, 1.403E+00, 1.439E+00, 1.464E+00, 1.473E+00, 1.472E+00, 1.449E+00, 1.432E+00, 1.405E+00, 1.356E+00, 1.305E+00, 1.210E+00, 1.130E+00, 1.040E+00, 9.592E-01, 8.862E-01, 8.476E-01, 8.168E-01, 7.815E-01, 7.683E-01, 8.100E-01, 9.000E-01, 1.031E+00, 1.190E+00, 1.354E+00, 1.501E+00, 1.610E+00, 1.552E+00, 1.415E+00, 1.211E+00, 9.448E-01, 7.341E-01, 5.295E-01, 3.696E-01, 2.510E-01, 1.648E-01, 1.057E-01, 6.661E-02, 4.350E-02, 2.842E-02, 1.958E-02, 1.371E-02, 1.010E-02, 7.380E-03, 5.807E-03, 4.279E-03, 3.047E-03, 2.733E-03, 2.499E-03, 2.143E-03, 1.810E-03, 1.313E-03, 1.512E-03, 1.121E-03, 7.844E-04, 9.596E-04, 5.457E-04, 5.389E-04, 2.457E-04, 1.112E-04}, // QCD500.root
     { 3.096E-04, 5.157E-02, 6.708E-02, 7.576E-02, 8.816E-02, 1.292E-01, 1.443E-01, 1.790E-01, 1.875E-01, 6.075E-01, 7.457E-01, 9.389E-01, 9.295E-01, 9.294E-01, 1.008E+00, 1.108E+00, 1.195E+00, 1.263E+00, 1.322E+00, 1.352E+00, 1.374E+00, 1.393E+00, 1.424E+00, 1.445E+00, 1.460E+00, 1.448E+00, 1.443E+00, 1.418E+00, 1.385E+00, 1.344E+00, 1.290E+00, 1.206E+00, 1.116E+00, 1.036E+00, 9.476E-01, 8.792E-01, 8.396E-01, 8.122E-01, 7.737E-01, 7.648E-01, 8.043E-01, 8.983E-01, 1.018E+00, 1.180E+00, 1.350E+00, 1.497E+00, 1.597E+00, 1.538E+00, 1.425E+00, 1.198E+00, 9.490E-01, 7.206E-01, 5.338E-01, 3.676E-01, 2.479E-01, 1.616E-01, 1.040E-01, 6.641E-02, 4.295E-02, 2.850E-02, 1.971E-02, 1.355E-02, 1.005E-02, 7.210E-03, 5.699E-03, 4.217E-03, 3.202E-03, 2.709E-03, 2.326E-03, 2.140E-03, 1.853E-03, 1.279E-03, 1.337E-03, 1.220E-03, 6.467E-04, 8.795E-04, 5.865E-04, 5.374E-04, 1.449E-04, 1.350E-04}, // QCD700.root
     { 3.027E-04, 4.823E-02, 6.540E-02, 6.682E-02, 9.383E-02, 1.611E-01, 1.465E-01, 1.658E-01, 1.501E-01, 5.078E-01, 6.672E-01, 8.632E-01, 9.054E-01, 8.810E-01, 9.086E-01, 1.087E+00, 1.100E+00, 1.264E+00, 1.313E+00, 1.338E+00, 1.370E+00, 1.367E+00, 1.428E+00, 1.453E+00, 1.446E+00, 1.466E+00, 1.457E+00, 1.415E+00, 1.396E+00, 1.345E+00, 1.289E+00, 1.214E+00, 1.114E+00, 1.041E+00, 9.582E-01, 8.989E-01, 8.520E-01, 8.115E-01, 7.822E-01, 7.704E-01, 8.214E-01, 8.962E-01, 1.032E+00, 1.202E+00, 1.368E+00, 1.512E+00, 1.578E+00, 1.576E+00, 1.377E+00, 1.188E+00, 9.508E-01, 7.416E-01, 5.306E-01, 3.755E-01, 2.485E-01, 1.619E-01, 1.067E-01, 6.829E-02, 4.343E-02, 2.854E-02, 1.928E-02, 1.380E-02, 1.025E-02, 7.460E-03, 6.012E-03, 4.295E-03, 3.185E-03, 2.663E-03, 2.386E-03, 2.406E-03, 1.975E-03, 1.156E-03, 7.917E-04, 1.693E-03, 7.626E-04, 4.564E-04, 4.586E-04, 1.325E-03, 3.430E-04, 7.954E-05}, // STs.root
     { 1.882E-01, 3.952E+00, 4.224E+00, 2.418E+00, 1.829E+00, 1.699E+00, 1.314E+00, 1.382E+00, 9.023E-01, 2.183E+00, 2.173E+00, 2.075E+00, 1.741E+00, 1.535E+00, 1.435E+00, 1.416E+00, 1.437E+00, 1.432E+00, 1.421E+00, 1.408E+00, 1.394E+00, 1.389E+00, 1.388E+00, 1.392E+00, 1.394E+00, 1.383E+00, 1.361E+00, 1.329E+00, 1.310E+00, 1.258E+00, 1.202E+00, 1.125E+00, 1.043E+00, 9.528E-01, 8.783E-01, 8.167E-01, 7.748E-01, 7.456E-01, 7.154E-01, 7.046E-01, 7.461E-01, 8.281E-01, 9.425E-01, 1.088E+00, 1.246E+00, 1.391E+00, 1.484E+00, 1.437E+00, 1.320E+00, 1.131E+00, 9.091E-01, 6.931E-01, 5.024E-01, 3.515E-01, 2.387E-01, 1.556E-01, 1.002E-01, 6.345E-02, 4.110E-02, 2.708E-02, 1.851E-02, 1.309E-02, 9.572E-03, 7.335E-03, 5.861E-03, 4.121E-03, 3.055E-03, 2.684E-03, 2.437E-03, 2.265E-03, 2.138E-03, 2.080E-03, 2.012E-03, 2.015E-03, 1.519E-03, 1.305E-03, 1.288E-03, 1.220E-03, 1.309E-03, 1.312E-03}, // STt.root
     { 1.861E-01, 5.669E+00, 4.357E+00, 2.661E+00, 1.765E+00, 1.675E+00, 1.338E+00, 1.397E+00, 9.253E-01, 2.115E+00, 2.179E+00, 2.085E+00, 1.720E+00, 1.526E+00, 1.441E+00, 1.413E+00, 1.431E+00, 1.433E+00, 1.428E+00, 1.408E+00, 1.395E+00, 1.390E+00, 1.389E+00, 1.391E+00, 1.393E+00, 1.379E+00, 1.354E+00, 1.328E+00, 1.308E+00, 1.259E+00, 1.200E+00, 1.128E+00, 1.044E+00, 9.562E-01, 8.764E-01, 8.183E-01, 7.755E-01, 7.473E-01, 7.162E-01, 7.012E-01, 7.472E-01, 8.279E-01, 9.409E-01, 1.091E+00, 1.249E+00, 1.394E+00, 1.482E+00, 1.443E+00, 1.327E+00, 1.125E+00, 9.143E-01, 6.918E-01, 5.023E-01, 3.499E-01, 2.393E-01, 1.558E-01, 9.969E-02, 6.328E-02, 4.116E-02, 2.711E-02, 1.844E-02, 1.301E-02, 9.584E-03, 7.374E-03, 5.835E-03, 4.168E-03, 3.068E-03, 2.685E-03, 2.429E-03, 2.274E-03, 2.136E-03, 2.109E-03, 1.974E-03, 1.993E-03, 1.616E-03, 1.317E-03, 1.284E-03, 1.350E-03, 1.208E-03, 1.168E-03}, // STtb.root
     { 2.724E-04, 2.910E-02, 4.802E-02, 4.626E-02, 8.848E-02, 1.467E-01, 9.702E-02, 1.141E-01, 1.559E-01, 5.990E-01, 6.398E-01, 8.527E-01, 8.980E-01, 9.351E-01, 9.676E-01, 1.088E+00, 1.170E+00, 1.258E+00, 1.306E+00, 1.342E+00, 1.361E+00, 1.409E+00, 1.442E+00, 1.466E+00, 1.453E+00, 1.469E+00, 1.466E+00, 1.449E+00, 1.407E+00, 1.364E+00, 1.313E+00, 1.204E+00, 1.136E+00, 1.042E+00, 9.655E-01, 8.901E-01, 8.390E-01, 8.224E-01, 7.747E-01, 7.688E-01, 8.242E-01, 8.990E-01, 1.030E+00, 1.198E+00, 1.377E+00, 1.496E+00, 1.638E+00, 1.563E+00, 1.406E+00, 1.200E+00, 9.532E-01, 7.279E-01, 5.302E-01, 3.698E-01, 2.485E-01, 1.665E-01, 1.064E-01, 6.664E-02, 4.255E-02, 2.909E-02, 1.965E-02, 1.318E-02, 9.869E-03, 7.707E-03, 5.750E-03, 4.200E-03, 3.087E-03, 2.716E-03, 2.562E-03, 2.393E-03, 1.548E-03, 9.258E-04, 1.153E-03, 1.225E-03, 1.526E-03, 1.053E-03, 3.162E-04, 9.623E-04, 1.145E-04, 1.587E-04}, // STtWt.root
     { 2.726E-04, 2.459E-02, 5.699E-02, 5.467E-02, 8.803E-02, 1.068E-01, 1.066E-01, 2.151E-01, 1.894E-01, 4.913E-01, 7.596E-01, 9.469E-01, 8.635E-01, 8.723E-01, 9.673E-01, 1.064E+00, 1.220E+00, 1.275E+00, 1.340E+00, 1.370E+00, 1.386E+00, 1.422E+00, 1.423E+00, 1.455E+00, 1.466E+00, 1.455E+00, 1.453E+00, 1.416E+00, 1.420E+00, 1.361E+00, 1.309E+00, 1.195E+00, 1.139E+00, 1.043E+00, 9.499E-01, 8.964E-01, 8.492E-01, 8.125E-01, 7.795E-01, 7.692E-01, 8.244E-01, 9.120E-01, 1.036E+00, 1.182E+00, 1.360E+00, 1.486E+00, 1.594E+00, 1.512E+00, 1.380E+00, 1.209E+00, 9.299E-01, 7.231E-01, 5.403E-01, 3.734E-01, 2.532E-01, 1.621E-01, 1.073E-01, 6.661E-02, 4.350E-02, 2.895E-02, 1.973E-02, 1.292E-02, 1.026E-02, 7.570E-03, 5.235E-03, 4.214E-03, 3.207E-03, 2.655E-03, 2.310E-03, 2.078E-03, 1.729E-03, 1.372E-03, 1.023E-03, 2.139E-03, 4.824E-04, 1.200E-03, 7.006E-04, 8.612E-04, 1.296E-04, 5.305E-05}, // STtWtb.root
     { 2.516E-04, 3.745E-02, 4.667E-02, 5.252E-02, 7.168E-02, 1.066E-01, 1.302E-01, 1.573E-01, 1.540E-01, 4.744E-01, 6.952E-01, 8.614E-01, 8.888E-01, 9.401E-01, 9.903E-01, 1.076E+00, 1.190E+00, 1.277E+00, 1.331E+00, 1.355E+00, 1.387E+00, 1.404E+00, 1.439E+00, 1.457E+00, 1.471E+00, 1.465E+00, 1.449E+00, 1.430E+00, 1.409E+00, 1.364E+00, 1.303E+00, 1.211E+00, 1.128E+00, 1.043E+00, 9.595E-01, 8.935E-01, 8.486E-01, 8.159E-01, 7.820E-01, 7.734E-01, 8.135E-01, 9.032E-01, 1.026E+00, 1.186E+00, 1.363E+00, 1.517E+00, 1.621E+00, 1.539E+00, 1.408E+00, 1.210E+00, 9.588E-01, 7.298E-01, 5.315E-01, 3.701E-01, 2.522E-01, 1.626E-01, 1.045E-01, 6.743E-02, 4.363E-02, 2.869E-02, 1.967E-02, 1.385E-02, 1.012E-02, 7.401E-03, 5.868E-03, 4.263E-03, 3.086E-03, 2.695E-03, 2.405E-03, 2.242E-03, 1.930E-03, 1.526E-03, 1.380E-03, 1.313E-03, 1.034E-03, 7.494E-04, 4.397E-04, 3.871E-04, 2.014E-04, 1.118E-04}, // TThad.root
     { 2.433E-04, 3.083E-02, 4.356E-02, 4.868E-02, 7.199E-02, 1.111E-01, 1.120E-01, 1.615E-01, 1.504E-01, 4.638E-01, 6.765E-01, 8.507E-01, 8.766E-01, 9.189E-01, 9.942E-01, 1.101E+00, 1.207E+00, 1.297E+00, 1.343E+00, 1.368E+00, 1.393E+00, 1.414E+00, 1.443E+00, 1.464E+00, 1.479E+00, 1.470E+00, 1.448E+00, 1.427E+00, 1.412E+00, 1.360E+00, 1.304E+00, 1.216E+00, 1.126E+00, 1.042E+00, 9.624E-01, 8.965E-01, 8.479E-01, 8.166E-01, 7.822E-01, 7.706E-01, 8.146E-01, 9.020E-01, 1.038E+00, 1.189E+00, 1.364E+00, 1.507E+00, 1.608E+00, 1.537E+00, 1.415E+00, 1.218E+00, 9.548E-01, 7.261E-01, 5.290E-01, 3.691E-01, 2.511E-01, 1.628E-01, 1.050E-01, 6.726E-02, 4.356E-02, 2.873E-02, 1.960E-02, 1.382E-02, 1.011E-02, 7.537E-03, 5.685E-03, 4.266E-03, 3.114E-03, 2.716E-03, 2.361E-03, 2.300E-03, 2.039E-03, 1.256E-03, 1.565E-03, 1.252E-03, 8.515E-04, 6.450E-04, 5.424E-04, 4.641E-04, 2.322E-04, 1.153E-04}, // TT1L.root
     { 2.434E-04, 3.418E-02, 5.431E-02, 4.657E-02, 6.896E-02, 1.070E-01, 1.101E-01, 1.798E-01, 1.662E-01, 4.622E-01, 6.978E-01, 8.373E-01, 8.649E-01, 9.050E-01, 9.629E-01, 1.078E+00, 1.188E+00, 1.271E+00, 1.324E+00, 1.359E+00, 1.398E+00, 1.413E+00, 1.438E+00, 1.471E+00, 1.478E+00, 1.476E+00, 1.463E+00, 1.433E+00, 1.422E+00, 1.364E+00, 1.312E+00, 1.219E+00, 1.131E+00, 1.040E+00, 9.600E-01, 8.953E-01, 8.531E-01, 8.222E-01, 7.845E-01, 7.730E-01, 8.171E-01, 9.037E-01, 1.029E+00, 1.193E+00, 1.362E+00, 1.506E+00, 1.610E+00, 1.530E+00, 1.408E+00, 1.210E+00, 9.511E-01, 7.311E-01, 5.247E-01, 3.677E-01, 2.513E-01, 1.613E-01, 1.062E-01, 6.711E-02, 4.368E-02, 2.868E-02, 1.943E-02, 1.380E-02, 1.007E-02, 7.354E-03, 5.625E-03, 4.359E-03, 3.111E-03, 2.617E-03, 2.409E-03, 2.177E-03, 2.065E-03, 1.631E-03, 1.560E-03, 1.434E-03, 7.085E-04, 7.542E-04, 5.592E-04, 3.329E-04, 2.876E-04, 1.020E-04}, // TT2L.root
     { 1.912E-01, 3.962E+00, 4.766E+00, 2.427E+00, 1.849E+00, 1.704E+00, 1.307E+00, 1.416E+00, 8.888E-01, 2.183E+00, 2.190E+00, 2.046E+00, 1.751E+00, 1.533E+00, 1.431E+00, 1.425E+00, 1.424E+00, 1.431E+00, 1.427E+00, 1.405E+00, 1.392E+00, 1.389E+00, 1.391E+00, 1.394E+00, 1.391E+00, 1.381E+00, 1.359E+00, 1.329E+00, 1.309E+00, 1.255E+00, 1.204E+00, 1.123E+00, 1.044E+00, 9.567E-01, 8.770E-01, 8.179E-01, 7.737E-01, 7.483E-01, 7.181E-01, 7.033E-01, 7.458E-01, 8.269E-01, 9.437E-01, 1.085E+00, 1.252E+00, 1.390E+00, 1.483E+00, 1.440E+00, 1.324E+00, 1.126E+00, 9.113E-01, 6.907E-01, 5.010E-01, 3.527E-01, 2.385E-01, 1.554E-01, 1.001E-01, 6.362E-02, 4.087E-02, 2.718E-02, 1.847E-02, 1.304E-02, 9.610E-03, 7.325E-03, 5.866E-03, 4.170E-03, 3.067E-03, 2.695E-03, 2.432E-03, 2.255E-03, 2.125E-03, 2.049E-03, 2.029E-03, 1.986E-03, 1.542E-03, 1.308E-03, 1.266E-03, 1.333E-03, 1.273E-03, 1.205E-03}, // TTMtt1000.root
     { 2.682E-04, 4.244E-02, 3.991E-02, 5.145E-02, 7.820E-02, 1.047E-01, 1.310E-01, 1.663E-01, 1.492E-01, 5.026E-01, 6.844E-01, 8.478E-01, 8.997E-01, 9.133E-01, 9.995E-01, 1.119E+00, 1.204E+00, 1.265E+00, 1.336E+00, 1.352E+00, 1.382E+00, 1.415E+00, 1.441E+00, 1.461E+00, 1.473E+00, 1.459E+00, 1.443E+00, 1.427E+00, 1.408E+00, 1.362E+00, 1.304E+00, 1.219E+00, 1.126E+00, 1.039E+00, 9.529E-01, 8.922E-01, 8.467E-01, 8.188E-01, 7.780E-01, 7.674E-01, 8.178E-01, 9.013E-01, 1.030E+00, 1.187E+00, 1.364E+00, 1.510E+00, 1.602E+00, 1.551E+00, 1.406E+00, 1.217E+00, 9.459E-01, 7.194E-01, 5.331E-01, 3.652E-01, 2.503E-01, 1.588E-01, 1.046E-01, 6.720E-02, 4.339E-02, 2.861E-02, 1.942E-02, 1.385E-02, 1.013E-02, 7.519E-03, 5.590E-03, 4.182E-03, 3.074E-03, 2.788E-03, 2.464E-03, 2.008E-03, 2.120E-03, 1.481E-03, 1.149E-03, 1.517E-03, 5.850E-04, 5.990E-04, 3.923E-04, 5.477E-04, 3.548E-04, 8.395E-05}, // TTMtt700.root
     { 1.858E-01, 4.593E+00, 4.089E+00, 2.441E+00, 1.927E+00, 1.645E+00, 1.371E+00, 1.396E+00, 8.927E-01, 2.148E+00, 2.192E+00, 2.057E+00, 1.745E+00, 1.540E+00, 1.435E+00, 1.424E+00, 1.427E+00, 1.432E+00, 1.419E+00, 1.404E+00, 1.390E+00, 1.392E+00, 1.388E+00, 1.391E+00, 1.392E+00, 1.382E+00, 1.365E+00, 1.331E+00, 1.307E+00, 1.256E+00, 1.200E+00, 1.128E+00, 1.042E+00, 9.551E-01, 8.774E-01, 8.157E-01, 7.746E-01, 7.475E-01, 7.162E-01, 7.050E-01, 7.478E-01, 8.259E-01, 9.466E-01, 1.087E+00, 1.249E+00, 1.393E+00, 1.482E+00, 1.434E+00, 1.316E+00, 1.126E+00, 9.101E-01, 6.921E-01, 5.016E-01, 3.519E-01, 2.392E-01, 1.559E-01, 1.003E-01, 6.331E-02, 4.108E-02, 2.709E-02, 1.842E-02, 1.308E-02, 9.617E-03, 7.361E-03, 5.843E-03, 4.191E-03, 3.072E-03, 2.705E-03, 2.437E-03, 2.267E-03, 2.134E-03, 2.097E-03, 1.926E-03, 2.013E-03, 1.605E-03, 1.296E-03, 1.303E-03, 1.250E-03, 1.375E-03, 1.203E-03}, // ttW.root
     { 1.785E-01, 3.905E+00, 5.030E+00, 2.363E+00, 1.798E+00, 1.739E+00, 1.361E+00, 1.289E+00, 8.896E-01, 2.173E+00, 2.132E+00, 2.051E+00, 1.740E+00, 1.537E+00, 1.450E+00, 1.420E+00, 1.431E+00, 1.430E+00, 1.426E+00, 1.407E+00, 1.393E+00, 1.390E+00, 1.391E+00, 1.391E+00, 1.390E+00, 1.380E+00, 1.356E+00, 1.330E+00, 1.311E+00, 1.257E+00, 1.204E+00, 1.124E+00, 1.045E+00, 9.530E-01, 8.810E-01, 8.210E-01, 7.725E-01, 7.455E-01, 7.164E-01, 7.033E-01, 7.449E-01, 8.242E-01, 9.466E-01, 1.090E+00, 1.250E+00, 1.400E+00, 1.483E+00, 1.430E+00, 1.328E+00, 1.124E+00, 9.092E-01, 6.911E-01, 5.034E-01, 3.523E-01, 2.388E-01, 1.551E-01, 9.965E-02, 6.317E-02, 4.082E-02, 2.707E-02, 1.849E-02, 1.310E-02, 9.563E-03, 7.378E-03, 5.833E-03, 4.165E-03, 3.101E-03, 2.689E-03, 2.456E-03, 2.272E-03, 2.138E-03, 2.058E-03, 2.008E-03, 1.946E-03, 1.488E-03, 1.352E-03, 1.330E-03, 1.241E-03, 1.232E-03, 1.334E-03}, // ttZ.root
     { 2.749E-04, 3.375E-02, 5.075E-02, 6.102E-02, 9.180E-02, 1.001E-01, 1.272E-01, 1.752E-01, 2.026E-01, 4.950E-01, 7.052E-01, 1.004E+00, 8.737E-01, 9.073E-01, 1.008E+00, 1.095E+00, 1.213E+00, 1.261E+00, 1.351E+00, 1.357E+00, 1.385E+00, 1.429E+00, 1.444E+00, 1.468E+00, 1.483E+00, 1.449E+00, 1.432E+00, 1.442E+00, 1.400E+00, 1.332E+00, 1.306E+00, 1.220E+00, 1.101E+00, 1.050E+00, 9.572E-01, 8.969E-01, 8.367E-01, 8.121E-01, 7.834E-01, 7.659E-01, 8.147E-01, 8.697E-01, 1.017E+00, 1.166E+00, 1.366E+00, 1.513E+00, 1.601E+00, 1.538E+00, 1.441E+00, 1.222E+00, 9.685E-01, 7.203E-01, 5.290E-01, 3.788E-01, 2.466E-01, 1.655E-01, 1.061E-01, 6.635E-02, 4.327E-02, 2.828E-02, 1.946E-02, 1.367E-02, 1.013E-02, 7.404E-03, 5.530E-03, 4.026E-03, 3.044E-03, 2.555E-03, 2.224E-03, 2.172E-03, 1.822E-03, 1.025E-03, 1.265E-03, 9.916E-04, 1.282E-03, 7.759E-04, 8.409E-04, 2.946E-04, 1.232E-04, 5.447E-05}, // ttH.root
     { 2.392E-04, 2.535E-02, 4.420E-02, 5.403E-02, 8.465E-02, 1.060E-01, 1.635E-01, 1.881E-01, 1.482E-01, 4.991E-01, 7.362E-01, 7.943E-01, 9.265E-01, 9.598E-01, 1.035E+00, 1.107E+00, 1.254E+00, 1.273E+00, 1.330E+00, 1.370E+00, 1.382E+00, 1.406E+00, 1.439E+00, 1.448E+00, 1.491E+00, 1.433E+00, 1.430E+00, 1.431E+00, 1.421E+00, 1.368E+00, 1.305E+00, 1.188E+00, 1.110E+00, 1.043E+00, 9.399E-01, 8.897E-01, 8.492E-01, 8.039E-01, 7.775E-01, 7.679E-01, 8.096E-01, 9.016E-01, 1.028E+00, 1.184E+00, 1.363E+00, 1.541E+00, 1.622E+00, 1.547E+00, 1.431E+00, 1.227E+00, 9.506E-01, 7.261E-01, 5.374E-01, 3.764E-01, 2.482E-01, 1.614E-01, 1.058E-01, 6.703E-02, 4.294E-02, 2.892E-02, 1.990E-02, 1.377E-02, 9.700E-03, 7.869E-03, 6.284E-03, 4.481E-03, 3.240E-03, 2.711E-03, 2.313E-03, 2.405E-03, 1.837E-03, 1.727E-03, 2.143E-03, 2.091E-03, 1.587E-03, 7.816E-04, 1.351E-03, 1.363E-03, 1.270E-03, 1.181E-04}, // WW.root
     { 3.000E-04, 1.037E-02, 4.812E-02, 6.479E-02, 1.064E-01, 2.007E-01, 2.005E-01, 2.486E-01, 1.572E-01, 6.099E-01, 6.130E-01, 8.929E-01, 9.211E-01, 9.922E-01, 9.807E-01, 1.010E+00, 1.118E+00, 1.280E+00, 1.323E+00, 1.346E+00, 1.414E+00, 1.416E+00, 1.431E+00, 1.448E+00, 1.471E+00, 1.462E+00, 1.426E+00, 1.426E+00, 1.421E+00, 1.373E+00, 1.276E+00, 1.207E+00, 1.125E+00, 1.041E+00, 9.691E-01, 9.041E-01, 8.457E-01, 8.098E-01, 7.702E-01, 7.803E-01, 7.976E-01, 8.806E-01, 1.023E+00, 1.208E+00, 1.380E+00, 1.510E+00, 1.617E+00, 1.577E+00, 1.430E+00, 1.241E+00, 9.751E-01, 7.476E-01, 5.422E-01, 3.609E-01, 2.505E-01, 1.609E-01, 1.080E-01, 6.809E-02, 4.416E-02, 2.923E-02, 1.891E-02, 1.346E-02, 9.378E-03, 6.994E-03, 5.955E-03, 4.439E-03, 2.932E-03, 2.757E-03, 1.947E-03, 2.243E-03, 1.258E-03, 1.277E-03, 1.083E-03, 2.175E-03, 8.778E-04, 2.953E-04, 1.985E-04, 1.255E-03, 6.371E-05, 4.534E-05}, // WZ.root
     { 4.754E-04, 2.803E-02, 4.775E-02, 2.087E-01, 1.657E-01, 1.568E-01, 2.380E-01, 3.119E-01, 2.303E-01, 6.776E-01, 7.993E-01, 9.758E-01, 9.744E-01, 9.374E-01, 8.435E-01, 9.754E-01, 1.061E+00, 1.157E+00, 1.284E+00, 1.306E+00, 1.345E+00, 1.403E+00, 1.434E+00, 1.452E+00, 1.450E+00, 1.459E+00, 1.448E+00, 1.410E+00, 1.370E+00, 1.350E+00, 1.302E+00, 1.216E+00, 1.115E+00, 1.038E+00, 9.541E-01, 8.908E-01, 8.427E-01, 8.130E-01, 7.817E-01, 7.751E-01, 8.154E-01, 8.691E-01, 1.040E+00, 1.141E+00, 1.374E+00, 1.462E+00, 1.627E+00, 1.494E+00, 1.395E+00, 1.227E+00, 9.032E-01, 7.350E-01, 5.420E-01, 3.393E-01, 2.305E-01, 1.621E-01, 1.067E-01, 6.413E-02, 4.339E-02, 2.768E-02, 1.913E-02, 1.395E-02, 1.028E-02, 7.239E-03, 5.392E-03, 3.586E-03, 2.997E-03, 2.877E-03, 2.464E-03, 2.309E-03, 2.292E-03, 2.140E-03, 2.204E-03, 2.236E-03, 1.511E-03, 1.277E-03, 1.538E-03, 2.884E-04, 5.381E-04, 2.047E-05}, // ZZ.root
     { 1.817E-01, 1.168E+01, 5.677E+00, 2.844E+00, 1.784E+00, 1.772E+00, 1.351E+00, 1.447E+00, 9.000E-01, 2.140E+00, 2.198E+00, 2.200E+00, 1.738E+00, 1.572E+00, 1.432E+00, 1.429E+00, 1.414E+00, 1.430E+00, 1.412E+00, 1.401E+00, 1.388E+00, 1.380E+00, 1.373E+00, 1.413E+00, 1.402E+00, 1.376E+00, 1.364E+00, 1.317E+00, 1.325E+00, 1.249E+00, 1.194E+00, 1.112E+00, 1.038E+00, 9.623E-01, 8.730E-01, 8.160E-01, 7.736E-01, 7.480E-01, 7.227E-01, 7.053E-01, 7.502E-01, 8.203E-01, 9.387E-01, 1.072E+00, 1.246E+00, 1.388E+00, 1.498E+00, 1.448E+00, 1.323E+00, 1.114E+00, 9.031E-01, 6.882E-01, 4.957E-01, 3.524E-01, 2.410E-01, 1.592E-01, 1.012E-01, 6.300E-02, 4.145E-02, 2.705E-02, 1.873E-02, 1.331E-02, 9.740E-03, 7.650E-03, 5.982E-03, 4.350E-03, 3.063E-03, 2.591E-03, 2.505E-03, 2.334E-03, 2.080E-03, 2.069E-03, 2.043E-03, 1.996E-03, 1.674E-03, 1.261E-03, 1.311E-03, 1.421E-03, 1.042E-03, 1.145E-03}, // TpTp700.root
     { 1.961E-01, 4.693E+00, 3.423E+00, 2.165E+00, 1.829E+00, 1.623E+00, 1.431E+00, 1.188E+00, 8.092E-01, 1.995E+00, 2.197E+00, 2.099E+00, 1.750E+00, 1.561E+00, 1.492E+00, 1.407E+00, 1.444E+00, 1.429E+00, 1.414E+00, 1.395E+00, 1.390E+00, 1.380E+00, 1.389E+00, 1.387E+00, 1.399E+00, 1.389E+00, 1.370E+00, 1.323E+00, 1.303E+00, 1.268E+00, 1.196E+00, 1.114E+00, 1.050E+00, 9.590E-01, 8.840E-01, 8.201E-01, 7.654E-01, 7.413E-01, 7.169E-01, 7.049E-01, 7.369E-01, 8.288E-01, 9.535E-01, 1.099E+00, 1.243E+00, 1.384E+00, 1.470E+00, 1.429E+00, 1.331E+00, 1.144E+00, 9.079E-01, 6.958E-01, 5.124E-01, 3.503E-01, 2.418E-01, 1.531E-01, 1.011E-01, 6.354E-02, 4.080E-02, 2.680E-02, 1.823E-02, 1.322E-02, 9.581E-03, 7.384E-03, 5.964E-03, 4.126E-03, 3.110E-03, 2.624E-03, 2.460E-03, 2.274E-03, 2.156E-03, 2.164E-03, 1.919E-03, 1.784E-03, 1.388E-03, 1.372E-03, 1.150E-03, 1.060E-03, 9.575E-04, 1.250E-03}, // TpTp1000.root
     { 2.421E-01, 3.399E+00, 3.718E+00, 2.300E+00, 2.091E+00, 1.592E+00, 1.567E+00, 1.341E+00, 9.583E-01, 2.196E+00, 2.139E+00, 2.213E+00, 1.743E+00, 1.527E+00, 1.451E+00, 1.419E+00, 1.423E+00, 1.438E+00, 1.418E+00, 1.415E+00, 1.392E+00, 1.385E+00, 1.391E+00, 1.399E+00, 1.405E+00, 1.387E+00, 1.359E+00, 1.321E+00, 1.305E+00, 1.270E+00, 1.183E+00, 1.107E+00, 1.052E+00, 9.529E-01, 8.726E-01, 8.193E-01, 7.717E-01, 7.530E-01, 7.146E-01, 7.028E-01, 7.514E-01, 8.205E-01, 9.305E-01, 1.087E+00, 1.258E+00, 1.412E+00, 1.483E+00, 1.431E+00, 1.319E+00, 1.153E+00, 9.135E-01, 7.011E-01, 5.003E-01, 3.526E-01, 2.421E-01, 1.564E-01, 1.012E-01, 6.385E-02, 4.073E-02, 2.699E-02, 1.807E-02, 1.304E-02, 9.435E-03, 7.052E-03, 5.666E-03, 4.177E-03, 3.104E-03, 2.684E-03, 2.394E-03, 2.418E-03, 2.250E-03, 2.151E-03, 2.142E-03, 1.890E-03, 1.766E-03, 1.233E-03, 1.131E-03, 1.520E-03, 1.222E-03, 1.086E-03}, // TpTp1100.root
     { 2.274E-01, 2.464E+00, 3.234E+00, 2.251E+00, 1.963E+00, 2.163E+00, 1.615E+00, 1.444E+00, 7.966E-01, 2.141E+00, 2.176E+00, 1.993E+00, 1.780E+00, 1.540E+00, 1.430E+00, 1.415E+00, 1.431E+00, 1.421E+00, 1.415E+00, 1.381E+00, 1.390E+00, 1.389E+00, 1.390E+00, 1.414E+00, 1.387E+00, 1.364E+00, 1.354E+00, 1.325E+00, 1.321E+00, 1.250E+00, 1.205E+00, 1.133E+00, 1.045E+00, 9.548E-01, 8.865E-01, 8.137E-01, 7.625E-01, 7.428E-01, 7.208E-01, 7.062E-01, 7.575E-01, 8.301E-01, 9.422E-01, 1.098E+00, 1.245E+00, 1.404E+00, 1.480E+00, 1.453E+00, 1.348E+00, 1.126E+00, 9.126E-01, 6.806E-01, 4.997E-01, 3.478E-01, 2.339E-01, 1.566E-01, 1.010E-01, 6.358E-02, 4.118E-02, 2.729E-02, 1.825E-02, 1.329E-02, 9.582E-03, 7.369E-03, 5.816E-03, 4.242E-03, 3.090E-03, 2.630E-03, 2.368E-03, 2.272E-03, 2.171E-03, 1.978E-03, 2.132E-03, 2.177E-03, 1.600E-03, 1.494E-03, 1.260E-03, 1.322E-03, 1.701E-03, 1.045E-03}, // TpTp1200.root
     { 1.644E-01, 3.123E+00, 3.986E+00, 2.219E+00, 1.704E+00, 1.531E+00, 1.319E+00, 1.268E+00, 9.258E-01, 2.165E+00, 2.087E+00, 2.035E+00, 1.780E+00, 1.517E+00, 1.457E+00, 1.418E+00, 1.405E+00, 1.419E+00, 1.438E+00, 1.409E+00, 1.386E+00, 1.420E+00, 1.381E+00, 1.396E+00, 1.386E+00, 1.398E+00, 1.364E+00, 1.339E+00, 1.302E+00, 1.258E+00, 1.206E+00, 1.119E+00, 1.042E+00, 9.488E-01, 8.870E-01, 8.242E-01, 7.657E-01, 7.487E-01, 7.267E-01, 7.039E-01, 7.467E-01, 8.331E-01, 9.451E-01, 1.088E+00, 1.248E+00, 1.374E+00, 1.467E+00, 1.418E+00, 1.316E+00, 1.133E+00, 9.029E-01, 6.741E-01, 5.107E-01, 3.567E-01, 2.398E-01, 1.568E-01, 9.943E-02, 6.354E-02, 4.198E-02, 2.673E-02, 1.837E-02, 1.264E-02, 9.297E-03, 7.306E-03, 5.766E-03, 4.035E-03, 3.086E-03, 2.674E-03, 2.425E-03, 2.113E-03, 2.148E-03, 2.262E-03, 1.892E-03, 1.850E-03, 1.470E-03, 1.289E-03, 1.736E-03, 1.386E-03, 1.103E-03, 1.116E-03}, // TpTp1300.root
     { 2.259E-01, 2.503E+00, 1.460E+01, 2.258E+00, 2.001E+00, 1.683E+00, 1.123E+00, 1.317E+00, 1.018E+00, 2.115E+00, 2.290E+00, 2.001E+00, 1.798E+00, 1.523E+00, 1.432E+00, 1.442E+00, 1.406E+00, 1.438E+00, 1.414E+00, 1.425E+00, 1.396E+00, 1.390E+00, 1.394E+00, 1.405E+00, 1.406E+00, 1.398E+00, 1.349E+00, 1.343E+00, 1.299E+00, 1.252E+00, 1.214E+00, 1.133E+00, 1.054E+00, 9.478E-01, 8.770E-01, 8.120E-01, 7.754E-01, 7.426E-01, 7.193E-01, 7.032E-01, 7.369E-01, 8.230E-01, 9.410E-01, 1.100E+00, 1.252E+00, 1.390E+00, 1.473E+00, 1.433E+00, 1.335E+00, 1.121E+00, 9.185E-01, 6.828E-01, 5.034E-01, 3.511E-01, 2.375E-01, 1.556E-01, 1.012E-01, 6.249E-02, 4.154E-02, 2.636E-02, 1.811E-02, 1.293E-02, 9.374E-03, 7.349E-03, 5.789E-03, 4.230E-03, 2.986E-03, 2.748E-03, 2.369E-03, 2.135E-03, 2.288E-03, 2.089E-03, 1.808E-03, 1.703E-03, 1.548E-03, 1.171E-03, 1.230E-03, 1.194E-03, 1.670E-03, 1.534E-03}, // TpTp1400.root
     { 2.534E-01, 4.774E+00, 3.214E+00, 2.769E+00, 1.353E+00, 1.656E+00, 1.323E+00, 1.369E+00, 8.440E-01, 2.160E+00, 2.081E+00, 2.068E+00, 1.726E+00, 1.534E+00, 1.434E+00, 1.419E+00, 1.411E+00, 1.424E+00, 1.405E+00, 1.426E+00, 1.388E+00, 1.389E+00, 1.380E+00, 1.409E+00, 1.402E+00, 1.378E+00, 1.339E+00, 1.325E+00, 1.307E+00, 1.274E+00, 1.184E+00, 1.134E+00, 1.041E+00, 9.602E-01, 8.671E-01, 8.262E-01, 7.761E-01, 7.544E-01, 7.171E-01, 7.107E-01, 7.460E-01, 8.273E-01, 9.512E-01, 1.085E+00, 1.249E+00, 1.383E+00, 1.475E+00, 1.440E+00, 1.307E+00, 1.127E+00, 9.317E-01, 6.889E-01, 5.082E-01, 3.543E-01, 2.389E-01, 1.564E-01, 9.975E-02, 6.308E-02, 4.107E-02, 2.683E-02, 1.837E-02, 1.300E-02, 9.587E-03, 7.369E-03, 5.801E-03, 4.057E-03, 3.202E-03, 2.540E-03, 2.601E-03, 2.136E-03, 2.060E-03, 2.101E-03, 1.910E-03, 2.114E-03, 1.445E-03, 1.064E-03, 1.113E-03, 1.423E-03, 9.898E-04, 1.170E-03}, // TpTp1500.root
     { 1.691E-01, 4.496E+00, 3.577E+00, 2.191E+00, 1.797E+00, 1.535E+00, 1.462E+00, 1.319E+00, 9.965E-01, 2.230E+00, 2.421E+00, 2.204E+00, 1.788E+00, 1.538E+00, 1.485E+00, 1.431E+00, 1.447E+00, 1.434E+00, 1.431E+00, 1.428E+00, 1.359E+00, 1.384E+00, 1.392E+00, 1.374E+00, 1.407E+00, 1.371E+00, 1.361E+00, 1.308E+00, 1.299E+00, 1.267E+00, 1.197E+00, 1.122E+00, 1.053E+00, 9.560E-01, 8.843E-01, 8.065E-01, 7.815E-01, 7.474E-01, 7.171E-01, 7.104E-01, 7.420E-01, 8.319E-01, 9.367E-01, 1.106E+00, 1.275E+00, 1.387E+00, 1.467E+00, 1.429E+00, 1.347E+00, 1.114E+00, 9.222E-01, 6.787E-01, 4.913E-01, 3.537E-01, 2.385E-01, 1.556E-01, 9.965E-02, 6.276E-02, 4.035E-02, 2.740E-02, 1.810E-02, 1.318E-02, 9.708E-03, 7.336E-03, 5.762E-03, 4.249E-03, 3.249E-03, 2.613E-03, 2.482E-03, 2.292E-03, 2.000E-03, 2.002E-03, 2.071E-03, 2.412E-03, 2.049E-03, 1.224E-03, 1.200E-03, 1.072E-03, 9.581E-04, 1.377E-03}, // TpTp1600.root
     { 3.213E-01, 2.238E+00, 3.428E+00, 2.385E+00, 1.650E+00, 1.278E+00, 1.188E+00, 1.960E+00, 7.860E-01, 1.943E+00, 2.136E+00, 2.060E+00, 1.775E+00, 1.562E+00, 1.424E+00, 1.397E+00, 1.471E+00, 1.430E+00, 1.411E+00, 1.430E+00, 1.373E+00, 1.387E+00, 1.393E+00, 1.413E+00, 1.407E+00, 1.372E+00, 1.351E+00, 1.310E+00, 1.314E+00, 1.255E+00, 1.208E+00, 1.141E+00, 1.031E+00, 9.504E-01, 8.791E-01, 8.118E-01, 7.635E-01, 7.642E-01, 7.256E-01, 7.090E-01, 7.532E-01, 8.499E-01, 9.292E-01, 1.101E+00, 1.240E+00, 1.378E+00, 1.481E+00, 1.411E+00, 1.337E+00, 1.109E+00, 9.057E-01, 6.796E-01, 4.907E-01, 3.592E-01, 2.375E-01, 1.545E-01, 1.004E-01, 6.358E-02, 4.029E-02, 2.685E-02, 1.822E-02, 1.306E-02, 9.822E-03, 7.220E-03, 5.894E-03, 4.330E-03, 3.072E-03, 2.566E-03, 2.609E-03, 2.479E-03, 2.090E-03, 1.923E-03, 1.771E-03, 1.701E-03, 1.425E-03, 1.705E-03, 1.387E-03, 1.038E-03, 1.669E-03, 8.726E-04}, // TpTp1700.root
     { 1.647E-01, 2.629E+00, 7.189E+00, 4.002E+00, 2.561E+00, 1.140E+00, 1.475E+00, 1.133E+00, 8.043E-01, 2.417E+00, 1.969E+00, 2.093E+00, 1.760E+00, 1.645E+00, 1.470E+00, 1.421E+00, 1.446E+00, 1.424E+00, 1.443E+00, 1.381E+00, 1.392E+00, 1.383E+00, 1.395E+00, 1.410E+00, 1.378E+00, 1.394E+00, 1.367E+00, 1.311E+00, 1.335E+00, 1.267E+00, 1.225E+00, 1.115E+00, 1.033E+00, 9.579E-01, 8.720E-01, 8.262E-01, 7.811E-01, 7.436E-01, 7.204E-01, 6.902E-01, 7.564E-01, 8.223E-01, 9.296E-01, 1.078E+00, 1.194E+00, 1.428E+00, 1.491E+00, 1.445E+00, 1.314E+00, 1.121E+00, 8.760E-01, 6.718E-01, 4.929E-01, 3.538E-01, 2.436E-01, 1.542E-01, 1.025E-01, 6.329E-02, 4.176E-02, 2.635E-02, 1.866E-02, 1.292E-02, 9.715E-03, 7.350E-03, 6.253E-03, 4.082E-03, 3.054E-03, 2.707E-03, 2.361E-03, 2.222E-03, 2.066E-03, 1.773E-03, 2.820E-03, 2.522E-03, 1.824E-03, 1.134E-03, 1.513E-03, 1.399E-03, 1.800E-03, 8.053E-04}, // TpTp1800.root
     { 1.956E-01, 5.248E+00, 4.196E+00, 2.304E+00, 2.077E+00, 1.657E+00, 1.386E+00, 1.350E+00, 8.810E-01, 2.221E+00, 2.212E+00, 2.054E+00, 1.725E+00, 1.530E+00, 1.433E+00, 1.415E+00, 1.431E+00, 1.434E+00, 1.422E+00, 1.406E+00, 1.392E+00, 1.386E+00, 1.389E+00, 1.392E+00, 1.390E+00, 1.381E+00, 1.361E+00, 1.331E+00, 1.310E+00, 1.258E+00, 1.201E+00, 1.125E+00, 1.043E+00, 9.559E-01, 8.776E-01, 8.191E-01, 7.730E-01, 7.494E-01, 7.178E-01, 7.045E-01, 7.467E-01, 8.257E-01, 9.414E-01, 1.088E+00, 1.246E+00, 1.393E+00, 1.485E+00, 1.435E+00, 1.322E+00, 1.127E+00, 9.104E-01, 6.925E-01, 5.023E-01, 3.517E-01, 2.394E-01, 1.557E-01, 1.004E-01, 6.365E-02, 4.097E-02, 2.709E-02, 1.842E-02, 1.303E-02, 9.584E-03, 7.348E-03, 5.862E-03, 4.138E-03, 3.053E-03, 2.666E-03, 2.430E-03, 2.256E-03, 2.140E-03, 2.089E-03, 1.981E-03, 2.002E-03, 1.566E-03, 1.282E-03, 1.289E-03, 1.315E-03, 1.286E-03, 1.330E-03}, // WJ1200.root
     { 2.001E-01, 4.707E+00, 4.493E+00, 2.398E+00, 1.889E+00, 1.708E+00, 1.343E+00, 1.422E+00, 8.659E-01, 2.142E+00, 2.156E+00, 2.050E+00, 1.738E+00, 1.537E+00, 1.443E+00, 1.418E+00, 1.428E+00, 1.429E+00, 1.423E+00, 1.406E+00, 1.391E+00, 1.389E+00, 1.386E+00, 1.393E+00, 1.392E+00, 1.384E+00, 1.361E+00, 1.330E+00, 1.307E+00, 1.260E+00, 1.200E+00, 1.123E+00, 1.046E+00, 9.546E-01, 8.776E-01, 8.187E-01, 7.750E-01, 7.462E-01, 7.146E-01, 7.049E-01, 7.457E-01, 8.282E-01, 9.435E-01, 1.085E+00, 1.250E+00, 1.394E+00, 1.485E+00, 1.434E+00, 1.329E+00, 1.126E+00, 9.123E-01, 6.931E-01, 5.036E-01, 3.523E-01, 2.389E-01, 1.554E-01, 1.002E-01, 6.324E-02, 4.093E-02, 2.711E-02, 1.854E-02, 1.303E-02, 9.649E-03, 7.323E-03, 5.864E-03, 4.167E-03, 3.069E-03, 2.676E-03, 2.398E-03, 2.240E-03, 2.127E-03, 2.079E-03, 2.015E-03, 1.970E-03, 1.567E-03, 1.320E-03, 1.302E-03, 1.255E-03, 1.352E-03, 1.202E-03}, // WJ200.root
     { 1.985E-01, 4.608E+00, 4.225E+00, 2.560E+00, 1.855E+00, 1.666E+00, 1.344E+00, 1.387E+00, 9.003E-01, 2.137E+00, 2.169E+00, 2.061E+00, 1.750E+00, 1.531E+00, 1.433E+00, 1.415E+00, 1.431E+00, 1.433E+00, 1.426E+00, 1.405E+00, 1.394E+00, 1.389E+00, 1.393E+00, 1.393E+00, 1.391E+00, 1.378E+00, 1.363E+00, 1.328E+00, 1.309E+00, 1.256E+00, 1.201E+00, 1.127E+00, 1.043E+00, 9.551E-01, 8.775E-01, 8.195E-01, 7.756E-01, 7.476E-01, 7.150E-01, 7.015E-01, 7.482E-01, 8.255E-01, 9.433E-01, 1.091E+00, 1.243E+00, 1.391E+00, 1.479E+00, 1.437E+00, 1.323E+00, 1.125E+00, 9.113E-01, 6.918E-01, 5.022E-01, 3.519E-01, 2.394E-01, 1.556E-01, 1.002E-01, 6.339E-02, 4.089E-02, 2.715E-02, 1.854E-02, 1.302E-02, 9.568E-03, 7.373E-03, 5.841E-03, 4.182E-03, 3.080E-03, 2.704E-03, 2.405E-03, 2.265E-03, 2.155E-03, 2.055E-03, 2.031E-03, 1.988E-03, 1.530E-03, 1.308E-03, 1.299E-03, 1.334E-03, 1.253E-03, 1.350E-03}, // WJ2500.root
     { 1.984E-01, 4.378E+00, 5.029E+00, 2.594E+00, 1.893E+00, 1.651E+00, 1.360E+00, 1.439E+00, 8.843E-01, 2.131E+00, 2.186E+00, 2.060E+00, 1.733E+00, 1.533E+00, 1.439E+00, 1.418E+00, 1.423E+00, 1.429E+00, 1.420E+00, 1.404E+00, 1.392E+00, 1.388E+00, 1.391E+00, 1.390E+00, 1.393E+00, 1.383E+00, 1.360E+00, 1.332E+00, 1.311E+00, 1.257E+00, 1.203E+00, 1.127E+00, 1.043E+00, 9.549E-01, 8.785E-01, 8.174E-01, 7.724E-01, 7.473E-01, 7.174E-01, 7.032E-01, 7.454E-01, 8.254E-01, 9.436E-01, 1.086E+00, 1.250E+00, 1.396E+00, 1.484E+00, 1.437E+00, 1.328E+00, 1.129E+00, 9.116E-01, 6.936E-01, 5.034E-01, 3.523E-01, 2.389E-01, 1.558E-01, 1.001E-01, 6.302E-02, 4.109E-02, 2.711E-02, 1.856E-02, 1.307E-02, 9.576E-03, 7.264E-03, 5.873E-03, 4.135E-03, 3.064E-03, 2.687E-03, 2.407E-03, 2.242E-03, 2.128E-03, 2.078E-03, 2.010E-03, 2.000E-03, 1.542E-03, 1.316E-03, 1.308E-03, 1.218E-03, 1.251E-03, 1.270E-03}, // WJ400.root
     { 1.986E-01, 3.920E+00, 4.591E+00, 2.554E+00, 1.822E+00, 1.667E+00, 1.351E+00, 1.444E+00, 8.880E-01, 2.208E+00, 2.152E+00, 2.055E+00, 1.731E+00, 1.534E+00, 1.430E+00, 1.421E+00, 1.431E+00, 1.438E+00, 1.423E+00, 1.403E+00, 1.396E+00, 1.388E+00, 1.392E+00, 1.393E+00, 1.391E+00, 1.383E+00, 1.357E+00, 1.328E+00, 1.308E+00, 1.259E+00, 1.203E+00, 1.126E+00, 1.043E+00, 9.538E-01, 8.770E-01, 8.167E-01, 7.741E-01, 7.469E-01, 7.172E-01, 7.055E-01, 7.441E-01, 8.282E-01, 9.429E-01, 1.088E+00, 1.248E+00, 1.389E+00, 1.484E+00, 1.435E+00, 1.328E+00, 1.125E+00, 9.090E-01, 6.919E-01, 5.041E-01, 3.534E-01, 2.391E-01, 1.560E-01, 1.004E-01, 6.336E-02, 4.095E-02, 2.699E-02, 1.846E-02, 1.305E-02, 9.589E-03, 7.309E-03, 5.837E-03, 4.154E-03, 3.050E-03, 2.701E-03, 2.438E-03, 2.238E-03, 2.137E-03, 2.064E-03, 1.968E-03, 2.006E-03, 1.596E-03, 1.289E-03, 1.299E-03, 1.217E-03, 1.278E-03, 1.191E-03}, // WJ600.root
     { 1.790E-01, 3.982E+00, 4.040E+00, 2.518E+00, 1.831E+00, 1.604E+00, 1.353E+00, 1.400E+00, 8.796E-01, 2.147E+00, 2.188E+00, 2.043E+00, 1.741E+00, 1.531E+00, 1.432E+00, 1.422E+00, 1.431E+00, 1.430E+00, 1.423E+00, 1.408E+00, 1.392E+00, 1.390E+00, 1.391E+00, 1.393E+00, 1.394E+00, 1.384E+00, 1.360E+00, 1.327E+00, 1.308E+00, 1.255E+00, 1.202E+00, 1.126E+00, 1.040E+00, 9.558E-01, 8.780E-01, 8.188E-01, 7.744E-01, 7.471E-01, 7.169E-01, 7.038E-01, 7.471E-01, 8.252E-01, 9.428E-01, 1.089E+00, 1.246E+00, 1.397E+00, 1.481E+00, 1.430E+00, 1.323E+00, 1.127E+00, 9.084E-01, 6.930E-01, 5.012E-01, 3.515E-01, 2.389E-01, 1.561E-01, 1.004E-01, 6.339E-02, 4.117E-02, 2.704E-02, 1.850E-02, 1.310E-02, 9.615E-03, 7.310E-03, 5.857E-03, 4.148E-03, 3.066E-03, 2.676E-03, 2.438E-03, 2.255E-03, 2.136E-03, 2.056E-03, 2.034E-03, 2.039E-03, 1.587E-03, 1.247E-03, 1.329E-03, 1.248E-03, 1.206E-03, 1.279E-03} // WJ800.root
};
   // Polynominals for WJets HT scaling
   TF1 *poly2 = new TF1("poly2","max([6],[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x)",100,5000);
   poly2->SetParameter(0,    0.998174);  
   poly2->SetParameter(1, 8.40861e-05); 
   poly2->SetParameter(2,-6.63274e-07);
   poly2->SetParameter(3, 4.09272e-10); 
   poly2->SetParameter(4,-9.50233e-14); 
   poly2->SetParameter(5, 7.59648e-18); 
   poly2->SetParameter(6,0.402806);
   
   TF1 *poly2U = new TF1("poly2U","max([6],[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x)",100,5000);
   poly2U->SetParameter(0,    0.998164);  
   poly2U->SetParameter(1, 8.51652e-05); 
   poly2U->SetParameter(2,-6.62919e-07);
   poly2U->SetParameter(3,  4.1205e-10); 
   poly2U->SetParameter(4,-9.57795e-14); 
   poly2U->SetParameter(5, 7.67371e-18); 
   poly2U->SetParameter(6,0.454456);
   
   TF1 *poly2D = new TF1("poly2D","max([6],[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x + [5]*x*x*x*x*x)",100,5000);
   poly2D->SetParameter(0,    0.998183);  
   poly2D->SetParameter(1, 8.30069e-05); 
   poly2D->SetParameter(2,-6.63629e-07);
   poly2D->SetParameter(3, 4.06495e-10); 
   poly2D->SetParameter(4,-9.42671e-14); 
   poly2D->SetParameter(5, 7.51924e-18); 
   poly2D->SetParameter(6,0.351156);

   
  // ----------------------------------------------------------------------------
  // RUN THE EVENT LOOP
  // ----------------------------------------------------------------------------

   cout << "RUN CONFIG: isMC = " << isMC << endl;
   cout << "isSig = " << isSig << ", SigMass = " << SigMass << endl;
   cout << "For W's: isTT = " << isTT << ", isSTt = " << isSTt << ", isSTtW = " << isSTtW << endl;
   cout << "Fot jets & PDF: isTOP = " << isTOP << ", isMadgraphBkg = " << isMadgraphBkg << endl;
   cout << "Pileup index: " << pileupIndex << endl;
   
   Long64_t nentries = inputTree->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = inputTree->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) != 1) continue;
      
      //      if (ientry > 5000) continue;
      
      if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;

      // ----------------------------------------------------------------------------
      // Filter input file by mass or decay
      // ----------------------------------------------------------------------------

      if(isTTincMtt0to700 && ttbarMass_TTbarMassCalc >= 700.) continue;
      if(isTTincMtt0to1000 && ttbarMass_TTbarMassCalc >= 1000.) continue;
      if(isTTincMtt700to1000 && (ttbarMass_TTbarMassCalc < 700. || ttbarMass_TTbarMassCalc >= 1000.)) continue;
      if(isTTincMtt1000toInf && ttbarMass_TTbarMassCalc < 1000.) continue;

      // ----------------------------------------------------------------------------
      // Assign as electron or muon event
      // ----------------------------------------------------------------------------
      // **** If we had saveLooseLeps == True in TTsinglelep_MC_cfg.py then this needs work!
      // **** Choose an electron and muon ID for "tight" and find events with only 1 tight el or mu by that definition
      isElectron = 0;
      isMuon = 0;
      if(elPt_singleLepCalc->size()==0 && muPt_singleLepCalc->size()==0){std::cout << "got no leptons, something wrong" << std::endl; continue;}
      if(elPt_singleLepCalc->size()>0 && muPt_singleLepCalc->size()>0) std::cout << "got el and mu, something wrong" << std::endl;
      if(elPt_singleLepCalc->size()>1 || muPt_singleLepCalc->size()>1) std::cout << "got more than one el or mu, something wrong" << std::endl;
      if(elPt_singleLepCalc->size()>0 && muPt_singleLepCalc->size()==0) {isElectron = 1; isMuon = 0;}
      if(elPt_singleLepCalc->size()==0 && muPt_singleLepCalc->size()>0) {isElectron = 0; isMuon = 1;}
      if(isElectron==0 && isMuon==0){std::cout << "got no leptons, something wrong" << std::endl; continue;}

      if(isSM && isElectron == 1) continue;
      if(isSE && isMuon == 1) continue;

      double leppt = 0;
      double lepeta = 0;
      if(isElectron){leppt = elPt_singleLepCalc->at(0); lepeta = elEta_singleLepCalc->at(0);}
      if(isMuon){leppt = muPt_singleLepCalc->at(0); lepeta = muEta_singleLepCalc->at(0);}

      // ----------------------------------------------------------------------------
      // Pileup weight calculation
      // ----------------------------------------------------------------------------

      pileupWeight = 1.0;
      pileupWeightUp = 1.0;
      pileupWeightDown = 1.0;
	
      if(isMC){
	if(nTrueInteractions_singleLepCalc > 79) nTrueInteractions_singleLepCalc = 79;
	if(nTrueInteractions_singleLepCalc < 0) nTrueInteractions_singleLepCalc = 0;
	if(pileupIndex < 1 || pileupIndex > 39){
	  std::cout << "I don't know this pileup sample, using TTToSemiLeptonic's" << std::endl;
	  pileupIndex = 14;
	}
	pileupWeight = pileupweight[pileupIndex-1][nTrueInteractions_singleLepCalc];
	pileupWeightUp = pileupweightUp[pileupIndex-1][nTrueInteractions_singleLepCalc];
	pileupWeightDown = pileupweightDn[pileupIndex-1][nTrueInteractions_singleLepCalc];
      }

      // ----------------------------------------------------------------------------
      // Assign Lepton scale factor or efficiency weights, save trigger pass/fail
      // ----------------------------------------------------------------------------

      DataPastTrigger = 0;
      MCPastTrigger = 0;
      EGammaGsfSF = 1.0;
      lepIdSF = 1.0;

      // *** SAM, put some if the WPTight triggers in these strings, check other names, same below in Data section
      if(isMC){ //MC triggers check
	if(isElectron){
	  std::string string_a = "Ele15_IsoVVVL_PFHT450";
	  std::string string_b = "Ele15_IsoVVVL_PFHT450_PFMET50";
	  std::string string_c = "Ele50_IsoVVVL_PFHT450";
	  std::string string_d = "Ele15_IsoVVVL_PFHT600";
	  std::string string_ORa = "Ele35_WPTight_Gsf";
	  std::string string_ORb = "Ele38_WPTight_Gsf";
	  for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
	    if(vsSelMCTriggersEl_singleLepCalc->at(itrig).find(string_a) != std::string::npos && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	    if(vsSelMCTriggersEl_singleLepCalc->at(itrig).find(string_b) != std::string::npos && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
            if(vsSelMCTriggersEl_singleLepCalc->at(itrig).find(string_c) != std::string::npos && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
            if(vsSelMCTriggersEl_singleLepCalc->at(itrig).find(string_d) != std::string::npos && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	    if(vsSelMCTriggersEl_singleLepCalc->at(itrig).find(string_ORa) != std::string::npos && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	    if(vsSelMCTriggersEl_singleLepCalc->at(itrig).find(string_ORb) != std::string::npos && viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	  }
	  // Gsf Tracking scale factor: http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/RECO/passingRECO/egammaEffi.txt_egammaPlots.pdf
	  if (leppt < 45) {
	    if (lepeta < -2.0) EGammaGsfSF = 0.977;
	    else if (lepeta < -1.566) EGammaGsfSF = 0.982;
	    else if (lepeta < -1.442) EGammaGsfSF = 0.948;
	    else if (lepeta < -1.0) EGammaGsfSF = 0.969;
	    else if (lepeta < -0.5) EGammaGsfSF = 0.977;
	    else if (lepeta < 0.5) EGammaGsfSF = 0.970;
	    else if (lepeta < 1.0) EGammaGsfSF = 0.972;
	    else if (lepeta < 1.442) EGammaGsfSF = 0.970;
	    else if (lepeta < 1.566) EGammaGsfSF = 0.958;
	    else EGammaGsfSF = 0.980; }
	  else if (leppt < 75) {
	    if (lepeta < -2.0) EGammaGsfSF = 0.984;
	    else if (lepeta < -1.566) EGammaGsfSF = 0.982;
	    else if (lepeta < -1.442) EGammaGsfSF = 0.971;
	    else if (lepeta < -1.0) EGammaGsfSF = 0.976;
	    else if (lepeta < 0.0) EGammaGsfSF = 0.980;
	    else if (lepeta < 0.5) EGammaGsfSF = 0.978;
	    else if (lepeta < 1.0) EGammaGsfSF = 0.979;
	    else if (lepeta < 1.442) EGammaGsfSF = 0.977;
	    else if (lepeta < 1.566) EGammaGsfSF = 0.964;
	    else if (lepeta < 2.0) EGammaGsfSF = 0.983;
	    else EGammaGsfSF = 0.984; }
	  else if (leppt < 100) {
	    if (lepeta < -1.566) EGammaGsfSF = 0.997;
	    else if (lepeta < -1.442) EGammaGsfSF = 1.003;
	    else if (lepeta < -1.0) EGammaGsfSF = 0.996;
	    else if (lepeta < 1.0) EGammaGsfSF = 0.992;
	    else if (lepeta < 1.442) EGammaGsfSF = 0.996;
	    else if (lepeta < 1.566) EGammaGsfSF = 1.003;
	    else EGammaGsfSF = 0.997; }
	  else {
	    if (lepeta < -1.566) EGammaGsfSF = 0.990;
	    else if (lepeta < -1.442) EGammaGsfSF = 1.010;
	    else if (lepeta < -1.0) EGammaGsfSF = 0.985;
	    else if (lepeta < -0.5) EGammaGsfSF = 0.988;
	    else if (lepeta < 0.5) EGammaGsfSF = 0.994;
	    else if (lepeta < 1.0) EGammaGsfSF = 0.988;
	    else if (lepeta < 1.442) EGammaGsfSF = 0.985;
	    else if (lepeta < 1.566) EGammaGsfSF = 1.010;
	    else EGammaGsfSF = 0.990; }

	  if (leppt < 20) {
	    if (lepeta < -2.0) lepIdSF = 0.900;
	    else if (lepeta < -1.566) lepIdSF = 0.950;
	    else if (lepeta < -1.442) lepIdSF = 1.000;
	    else if (lepeta < -0.8) lepIdSF = 0.973;
	    else if (lepeta < 0.0) lepIdSF = 0.989;
	    else if (lepeta < 0.8) lepIdSF = 0.991;
	    else if (lepeta < 1.442) lepIdSF = 0.995;
	    else if (lepeta < 1.566) lepIdSF = 1.000;
	    else if (lepeta < 2.0) lepIdSF = 0.972;
	    else lepIdSF = 0.885; }
	  else if (leppt < 35) {
	    if (lepeta < -2.0) lepIdSF = 0.891;
	    else if (lepeta < -1.566) lepIdSF = 0.908;
	    else if (lepeta < -1.442) lepIdSF = 1.000;
	    else if (lepeta < -0.8) lepIdSF = 0.934;
	    else if (lepeta < 0.0) lepIdSF = 0.958;
	    else if (lepeta < 0.8) lepIdSF = 0.961;
	    else if (lepeta < 1.442) lepIdSF = 0.943;
	    else if (lepeta < 1.566) lepIdSF = 1.000;
	    else if (lepeta < 2.0) lepIdSF = 0.913;
	    else lepIdSF = 0.884; }
	  else if (leppt < 50) {
	    if (lepeta < -2.0) lepIdSF = 0.916;
	    else if (lepeta < -1.566) lepIdSF = 0.934;
	    else if (lepeta < -1.442) lepIdSF = 1.000;
	    else if (lepeta < -0.8) lepIdSF = 0.944;
	    else if (lepeta < 0.0) lepIdSF = 0.958;
	    else if (lepeta < 0.8) lepIdSF = 0.959;
	    else if (lepeta < 1.442) lepIdSF = 0.948;
	    else if (lepeta < 1.566) lepIdSF = 1.000;
	    else if (lepeta < 2.0) lepIdSF = 0.937;
	    else lepIdSF = 0.912; }
	  else if (leppt < 100) {
	    if (lepeta < -2.0) lepIdSF = 0.921;
	    else if (lepeta < -1.566) lepIdSF = 0.941;
	    else if (lepeta < -1.442) lepIdSF = 1.000;
	    else if (lepeta < -0.8) lepIdSF = 0.947;
	    else if (lepeta < 0.0) lepIdSF = 0.962;
	    else if (lepeta < 0.8) lepIdSF = 0.960;
	    else if (lepeta < 1.442) lepIdSF = 0.951;
	    else if (lepeta < 1.566) lepIdSF = 1.000;
	    else if (lepeta < 2.0) lepIdSF = 0.949;
	    else lepIdSF = 0.918; }
	  else if (leppt < 200) {
	    if (lepeta < -2.0) lepIdSF = 0.965;
	    else if (lepeta < -1.566) lepIdSF = 0.970;
	    else if (lepeta < -1.442) lepIdSF = 1.000;
	    else if (lepeta < -0.8) lepIdSF = 0.972;
	    else if (lepeta < 0.0) lepIdSF = 0.981;
	    else if (lepeta < 0.8) lepIdSF = 0.979;
	    else if (lepeta < 1.442) lepIdSF = 0.973;
	    else if (lepeta < 1.566) lepIdSF = 1.000;
	    else if (lepeta < 2.0) lepIdSF = 0.984;
	    else lepIdSF = 0.971; }
	  else {
	    if (lepeta < -2.0) lepIdSF = 0.947;
	    else if (lepeta < -1.566) lepIdSF = 0.997;
	    else if (lepeta < -1.442) lepIdSF = 1.000;
	    else if (lepeta < -0.8) lepIdSF = 0.996;
	    else if (lepeta < 0.0) lepIdSF = 0.973;
	    else if (lepeta < 0.8) lepIdSF = 0.970;
	    else if (lepeta < 1.442) lepIdSF = 0.951;
	    else if (lepeta < 1.566) lepIdSF = 1.000;
	    else if (lepeta < 2.0) lepIdSF = 0.966;
	    else lepIdSF = 0.924; }
	}
	if(isMuon){
	  // ***** SAM, check these names, same below in Data section
	  std::string string_a = "Mu15_IsoVVVL_PFHT450";
	  std::string string_b = "Mu15_IsoVVVL_PFHT450_PFMET50";
	  std::string string_c = "Mu15_IsoVVVL_PFHT450_CaloBTagCSV_4p5";
	  std::string string_d = "Mu50_IsoVVVL_PFHT450";
	  std::string string_e = "Mu15_IsoVVVL_PFHT600";
	  std::string string_ORb = "Mu50";
	  std::string string_ORc = "TkMu50";
	  for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
	    if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_a) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	    if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_b) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
            if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_c) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
            if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_d) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
            if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_e) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	    if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_ORb) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	    if(vsSelMCTriggersMu_singleLepCalc->at(itrig).find(string_ORc) != std::string::npos && viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) MCPastTrigger = 1;
	  }
	  // Cut based tight id
	  if (fabs(lepeta) < 2.10 && fabs(lepeta) > 1.20) {
	    if (leppt < 25.0 && leppt > 20.0) lepIdSF = 0.9924252719877384;
	    else if (leppt < 60.0 && leppt > 50.0) lepIdSF = 0.9906364222943529;
	    else if (leppt < 30.0 && leppt > 25.0) lepIdSF = 0.9890884461284933;
	    else if (leppt < 120.0 && leppt > 60.0) lepIdSF = 0.9920464322143979;
	    else if (leppt < 40.0 && leppt > 30.0) lepIdSF = 0.9946469069883841;
	    else if (leppt < 50.0 && leppt > 40.0) lepIdSF = 0.9926528825155183; }
	  else if (fabs(lepeta) < 2.40 && leppt > 2.10) {
	    if (leppt < 25.0 && leppt > 20.0) lepIdSF = 0.9758095839531763;
	    else if (leppt < 60.0 && leppt > 50.0) lepIdSF = 0.9673568416097894;
	    else if (leppt < 30.0 && leppt > 25.0) lepIdSF = 0.9745153594179884;
	    else if (leppt < 120.0 && leppt > 60.0) lepIdSF = 0.9766311856731202;
	    else if (leppt < 40.0 && leppt > 30.0) lepIdSF = 0.9787410500158746;
	    else if (leppt < 50.0 && leppt > 40.0) lepIdSF = 0.978189122919501; }
	  else if (fabs(lepeta) < 1.20 && fabs(lepeta) > 0.90) {
	    if (leppt < 25.0 && leppt > 20.0) lepIdSF = 0.9927389275515244;
	    else if (leppt < 60.0 && leppt > 50.0) lepIdSF = 0.9839056384760008;
	    else if (leppt < 30.0 && leppt > 25.0) lepIdSF = 0.985063939762512;
	    else if (leppt < 120.0 && leppt > 60.0) lepIdSF = 0.984060403143468;
	    else if (leppt < 40.0 && leppt > 30.0) lepIdSF = 0.9865359464182247;
	    else if (leppt < 50.0 && leppt > 40.0) lepIdSF = 0.984913093101493; }
	  else if (fabs(lepeta) < 0.90 && fabs(lepeta) > 0.0) {
	    if (leppt < 25.0 && leppt > 20.0) lepIdSF = 0.9910777627756951;
	    else if (leppt < 60.0 && leppt > 50.0) lepIdSF = 0.9855545160334763;
	    else if (leppt < 30.0 && leppt > 25.0) lepIdSF = 0.987410468262084;
	    else if (leppt < 120.0 && leppt > 60.0) lepIdSF = 0.9898057377093389;
	    else if (leppt < 40.0 && leppt > 30.0) lepIdSF = 0.9907753279135898;
	    else if (leppt < 50.0 && leppt > 40.0) lepIdSF = 0.9892483588952047; }
	}
	DataPastTrigger = 1;
      }
      else{ //Data triggers check
	if(isElectron){
	  std::string string_a = "Ele15_IsoVVVL_PFHT450";
	  std::string string_b = "Ele15_IsoVVVL_PFHT450_PFMET50";
	  std::string string_c = "Ele50_IsoVVVL_PFHT450";
	  std::string string_d = "Ele15_IsoVVVL_PFHT600";
	  std::string string_ORa = "Ele35_WPTight_Gsf";
	  std::string string_ORb = "Ele38_WPTight_Gsf";
	  for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
	    if(vsSelTriggersEl_singleLepCalc->at(itrig).find(string_a) != std::string::npos && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	    if(vsSelTriggersEl_singleLepCalc->at(itrig).find(string_b) != std::string::npos && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
            if(vsSelTriggersEl_singleLepCalc->at(itrig).find(string_c) != std::string::npos && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
            if(vsSelTriggersEl_singleLepCalc->at(itrig).find(string_d) != std::string::npos && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	    if(vsSelTriggersEl_singleLepCalc->at(itrig).find(string_ORa) != std::string::npos && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	    if(vsSelTriggersEl_singleLepCalc->at(itrig).find(string_ORb) != std::string::npos && viSelTriggersEl_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	  }
	}



	if(isMuon){
	  std::string string_a = "Mu15_IsoVVVL_PFHT450";
	  std::string string_b = "Mu15_IsoVVVL_PFHT450_PFMET50";
	  std::string string_c = "Mu15_IsoVVVL_PFHT450_CaloBTagCSV_4p5";
	  std::string string_d = "Mu50_IsoVVVL_PFHT450";
	  std::string string_e = "Mu15_IsoVVVL_PFHT600";
	  std::string string_ORb = "Mu50";
	  std::string string_ORc = "TkMu50";
	  for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
	    if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_a) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	    if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_b) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
            if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_c) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
            if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_d) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
            if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_e) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	    if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_ORb) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	    if(vsSelTriggersMu_singleLepCalc->at(itrig).find(string_ORc) != std::string::npos && viSelTriggersMu_singleLepCalc->at(itrig) > 0) DataPastTrigger = 1;
	  }
	}
	MCPastTrigger = 1;
      }
      
      if(isMC && MCPastTrigger) npass_trigger+=1;
      if(!isMC && DataPastTrigger) npass_trigger+=1;

      // ----------------------------------------------------------------------------
      // Generator-level HT correction
      // ----------------------------------------------------------------------------      

      HTSF_Pol = 1;
      HTSF_PolUp = 1;
      HTSF_PolDn = 1;

      if(isMadgraphBkg){
	// Piece-wise splice with a flat line. Uncertainty from upper/lower error bar fits
	HTSF_Pol = poly2->Eval(HTfromHEPUEP_singleLepCalc);
	HTSF_PolUp = poly2U->Eval(HTfromHEPUEP_singleLepCalc);
	HTSF_PolDn = poly2D->Eval(HTfromHEPUEP_singleLepCalc);
      }

      // ----------------------------------------------------------------------------
      // Loop over AK4 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------

      NJets_JetSubCalc = 0;
      AK4HT = 0;
      vector<pair<double,int>> jetptindpair;

      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc->size(); ijet++){

	// ----------------------------------------------------------------------------
	// Basic cuts
	// ----------------------------------------------------------------------------

	if(theJetPt_JetSubCalc->at(ijet) < jetPtCut || fabs(theJetEta_JetSubCalc->at(ijet)) > jetEtaCut) continue;

	if(isMC){
	  // ----------------------------------------------------------------------------
	  // Counts and pt ordering pair
	  // ----------------------------------------------------------------------------

	  jetptindpair.push_back(std::make_pair(theJetPt_JetSubCalc->at(ijet),ijet));
	  NJets_JetSubCalc+=1;
	  AK4HT+=theJetPt_JetSubCalc->at(ijet);
	  
	}else{
	  jetptindpair.push_back(std::make_pair(theJetPt_JetSubCalc->at(ijet),ijet));
	  NJets_JetSubCalc+=1;
	  AK4HT+=theJetPt_JetSubCalc->at(ijet);
	}
      }
	
      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK4 vectors
      // ----------------------------------------------------------------------------
      //****** ANY OTHER NEW JET VECTOR (DeepCSV?) to order by pT go here


      std::sort(jetptindpair.begin(), jetptindpair.end(), comparepair);
      theJetPt_JetSubCalc_PtOrdered.clear();
      theJetEta_JetSubCalc_PtOrdered.clear();
      theJetPhi_JetSubCalc_PtOrdered.clear();
      theJetEnergy_JetSubCalc_PtOrdered.clear();
      theJetDeepCSVb_JetSubCalc_PtOrdered.clear();
      theJetDeepCSVbb_JetSubCalc_PtOrdered.clear();
      theJetDeepCSVc_JetSubCalc_PtOrdered.clear();
      theJetDeepCSVudsg_JetSubCalc_PtOrdered.clear();
      theJetHFlav_JetSubCalc_PtOrdered.clear();
      theJetPFlav_JetSubCalc_PtOrdered.clear();
      theJetBTag_JetSubCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetptindpair.size(); ijet++){
      	theJetPt_JetSubCalc_PtOrdered.push_back(theJetPt_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetEta_JetSubCalc_PtOrdered.push_back(theJetEta_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetPhi_JetSubCalc_PtOrdered.push_back(theJetPhi_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetEnergy_JetSubCalc_PtOrdered.push_back(theJetEnergy_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetDeepCSVb_JetSubCalc_PtOrdered.push_back(theJetDeepCSVb_JetSubCalc->at(jetptindpair[ijet].second));
		theJetDeepCSVbb_JetSubCalc_PtOrdered.push_back(theJetDeepCSVbb_JetSubCalc->at(jetptindpair[ijet].second));
		theJetDeepCSVc_JetSubCalc_PtOrdered.push_back(theJetDeepCSVc_JetSubCalc->at(jetptindpair[ijet].second));
		theJetDeepCSVudsg_JetSubCalc_PtOrdered.push_back(theJetDeepCSVudsg_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetHFlav_JetSubCalc_PtOrdered.push_back(theJetHFlav_JetSubCalc->at(jetptindpair[ijet].second));
      	theJetPFlav_JetSubCalc_PtOrdered.push_back(theJetPFlav_JetSubCalc->at(jetptindpair[ijet].second));
		theJetBTag_JetSubCalc_PtOrdered.push_back(theJetBTag_JetSubCalc->at(jetptindpair[ijet].second));
      }


      // ----------------------------------------------------------------------------
      // Lepton 4-vectors, calculate MT and electron trigger presel value
      // ----------------------------------------------------------------------------

      // Set lepton 4-vectors
      double lepM;
      double lepphi;
      if (isMuon){ 
	lepM = 0.105658367;
	lepphi = muPhi_singleLepCalc->at(0);
	lepton_lv.SetPtEtaPhiM(muPt_singleLepCalc->at(0),muEta_singleLepCalc->at(0),muPhi_singleLepCalc->at(0),lepM);
      }
      else{
	lepM = 0.00051099891;
	lepphi = elPhi_singleLepCalc->at(0);
	lepton_lv.SetPtEtaPhiM(elPt_singleLepCalc->at(0),elEta_singleLepCalc->at(0),elPhi_singleLepCalc->at(0),lepM);
      }      
      MT_lepMet = sqrt(2*leppt*corr_met_singleLepCalc*(1 - cos(lepphi - corr_met_phi_singleLepCalc)));

      // ----------------------------------------------------------------------------
      // Loop over AK8 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------

      NJetsAK8_JetSubCalc = 0;
      vector<pair<double,int>> jetak8ptindpair;      
      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc->size(); ijet++){

        // ----------------------------------------------------------------------------                                  
        // Basic cuts                                                                                                    
        // ----------------------------------------------------------------------------                                  
	
        if(fabs(theJetAK8Eta_JetSubCalc->at(ijet)) > ak8EtaCut) continue;
        if(theJetAK8NjettinessTau1_JetSubCalc->at(ijet)==0) continue;
        if(theJetAK8NjettinessTau2_JetSubCalc->at(ijet)==0) continue;

        // ----------------------------------------------------------------------------                                  
        // Counter and pt ordering pair                                                                                  
        // ----------------------------------------------------------------------------                                  
	
        NJetsAK8_JetSubCalc += 1;
        jetak8ptindpair.push_back(std::make_pair(theJetAK8Pt_JetSubCalc->at(ijet),ijet));
	
      }
            
      // ----------------------------------------------------------------------------
      // Apply kinematic cuts
      // ----------------------------------------------------------------------------
	                
      int isPastHTCut = 0;
      if(AK4HT >= htCut){npass_ht+=1;isPastHTCut=1;}
      
      int isPastMETcut = 0;
      if(corr_met_singleLepCalc > metCut){npass_met+=1;isPastMETcut=1;}

      int isPastLepPtCut = 0;
      if(leppt > lepPtCut){npass_lepPt+=1;isPastLepPtCut=1;}
      
      int isPastElEtaCut = 0;
      int isPastMuEtaCut = 0;
      if(isElectron && fabs(lepeta) < elEtaCut){npass_ElEta+=1;isPastElEtaCut=1;}
      if(isMuon && fabs(lepeta) < muEtaCut){npass_MuEta+=1;isPastMuEtaCut=1;}
      if(isElectron){Nelectrons+=1;}
      if(isMuon){Nmuons+=1;}
      
      int isPastNjetsCut = 0;
      if(NJets_JetSubCalc >= njetsCut){npass_Njets+=1;isPastNjetsCut=1;}

      // ----------------------------------------------------------------------------
      // Skip failing events
      // ----------------------------------------------------------------------------
            
      if(!(isPastMETcut && isPastHTCut && isPastNjetsCut && isPastLepPtCut && (isPastElEtaCut || isPastMuEtaCut))) continue;
      npass_all+=1;
      
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /////////////// ONLY ON SELECTED EVENTS ////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////      

      AK4HTpMETpLepPt = 0; //ST
      AK4HTpMETpLepPt = AK4HT + corr_met_singleLepCalc + leppt;
      
      // ----------------------------------------------------------------------------
      // Combine lepton variables into one set
      // ----------------------------------------------------------------------------

      // ******** MAYBE NEED SOME OTHERS?
      if(isElectron){
	leptonPt_singleLepCalc = leppt;
	leptonEta_singleLepCalc = lepeta;
	leptonPhi_singleLepCalc = elPhi_singleLepCalc->at(0);
	leptonEnergy_singleLepCalc = elEnergy_singleLepCalc->at(0);
	leptonMiniIso_singleLepCalc = elMiniIso_singleLepCalc->at(0);
	leptonMVAValue_singleLepCalc = elMVAValue_singleLepCalc->at(0);
      }
      if(isMuon){
	leptonPt_singleLepCalc = leppt;
	leptonEta_singleLepCalc = lepeta;
	leptonPhi_singleLepCalc = muPhi_singleLepCalc->at(0);
	leptonEnergy_singleLepCalc = muEnergy_singleLepCalc->at(0);
	leptonMiniIso_singleLepCalc = muMiniIso_singleLepCalc->at(0);
	leptonMVAValue_singleLepCalc = -99.9;
      }

      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK8 vectors 
      // ----------------------------------------------------------------------------



      // **** LOTS MORE TO ORDER PROBABLY. OR MAYBE WE DON'T NEED TO ORDER AT ALL.....
      //Pt ordering for AK8
      std::sort(jetak8ptindpair.begin(), jetak8ptindpair.end(), comparepair);

      theJetAK8Pt_JetSubCalc_PtOrdered.clear();
      theJetAK8Eta_JetSubCalc_PtOrdered.clear();
      theJetAK8Phi_JetSubCalc_PtOrdered.clear();
      theJetAK8Energy_JetSubCalc_PtOrdered.clear();
      theJetAK8Mass_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDropRaw_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDropCorr_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDrop_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered.clear();
      theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered.clear();
      theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered.clear();
      theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered.clear();
      theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.clear();
      theJetAK8Indx_Wtagged.clear();

      for(unsigned int ijet=0; ijet < jetak8ptindpair.size(); ijet++){
      	theJetAK8Pt_JetSubCalc_PtOrdered.push_back(theJetAK8Pt_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Eta_JetSubCalc_PtOrdered.push_back(theJetAK8Eta_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Phi_JetSubCalc_PtOrdered.push_back(theJetAK8Phi_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Energy_JetSubCalc_PtOrdered.push_back(theJetAK8Energy_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Mass_JetSubCalc_PtOrdered.push_back(theJetAK8Mass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDropRaw_JetSubCalc_PtOrdered.push_back(theJetAK8SoftDropRaw_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDropCorr_JetSubCalc_PtOrdered.push_back(theJetAK8SoftDropCorr_JetSubCalc->at(jetak8ptindpair[ijet].second));
		theJetAK8SoftDrop_JetSubCalc_PtOrdered.push_back(theJetAK8SoftDrop_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered.push_back(theJetAK8SoftDrop_JMRup_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered.push_back(theJetAK8SoftDrop_JMRdn_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered.push_back(theJetAK8SoftDrop_JMSup_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered.push_back(theJetAK8SoftDrop_JMSdn_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau1_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau2_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau3_JetSubCalc->at(jetak8ptindpair[ijet].second));
      }

      // ----------------------------------------------------------------------------
      // AK8 Jet - lepton associations, Top and W taggging
      // ----------------------------------------------------------------------------

      NPuppiWtagged_0p55 = 0;
      NPuppiWtagged_0p55_notTtagged = 0;
      NJetsTtagged_0p81 = 0;
      deltaR_lepAK8s.clear();
      minDR_lepAK8 = 1000;
      minDR_leadAK8otherAK8 = 1000;
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 1) minDR_lepAK8 = -99.0;      
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 2) minDR_leadAK8otherAK8 = -99.0;
      WJetLeadPt = -99.0;
      TJetLeadPt = -99.0;

      theJetAK8Wmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Tmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8MatchedPt_JetSubCalc_PtOrdered.clear();
      theJetAK8Truth_JetSubCalc_PtOrdered.clear();

      wjet1_lv.SetPtEtaPhiM(0,0,0,0);
      tjet1_lv.SetPtEtaPhiM(0,0,0,0);
      ak8_lv.SetPtEtaPhiM(0,0,0,0);
      TLorentzVector leadak8;
      leadak8.SetPtEtaPhiM(0,0,0,0);

      for(int i = 0; i < 8; i++){
	NPuppiWtagged_0p55_shifts.push_back(0);
	NPuppiWtagged_0p55_notTtagged_shifts.push_back(0);
	NJetsTtagged_0p81_shifts.push_back(0);
      }
      
      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc_PtOrdered.size(); ijet++){

	// ----------------------------------------------------------------------------
	// AK8 - lepton and AK8 -- AK8 associations
	// ----------------------------------------------------------------------------
	
	ak8_lv.SetPtEtaPhiE(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),theJetAK8Energy_JetSubCalc_PtOrdered.at(ijet));
	if(ijet == 0) leadak8 = ak8_lv;
	deltaR_lepAK8s.push_back(lepton_lv.DeltaR(ak8_lv));
	if(lepton_lv.DeltaR(ak8_lv) < minDR_lepAK8) minDR_lepAK8 = lepton_lv.DeltaR(ak8_lv);
	if(ijet > 0){
	  float tempdr = leadak8.DeltaR(ak8_lv);
	  if(tempdr < minDR_leadAK8otherAK8){
	    minDR_leadAK8otherAK8 = tempdr;
	  }
	}

	// ----------------------------------------------------------------------------
	// W & top tagging on MC
	// ----------------------------------------------------------------------------
	
	float tau21 = theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.at(ijet);
	float tau32 = theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet);

	float massSD = theJetAK8SoftDropCorr_JetSubCalc_PtOrdered.at(ijet);
	float massSD_JMSup = theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered.at(ijet);
	float massSD_JMSdn = theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered.at(ijet);
	float massSD_JMRup = theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered.at(ijet);
	float massSD_JMRdn = theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered.at(ijet);

	// ------------------------------------------------------------------------------------------------------------------
	// MC Calculation first
	// ------------------------------------------------------------------------------------------------------------------

	if(isMC){
	  
	  // ------------------------------------------------------------------------------------------------------------------
	  // TRUTH MATCHING
	  // ------------------------------------------------------------------------------------------------------------------
	  float minDR = 1000;
	  float matchedPt= -99;
	  int matchedID = 0;
	  bool isWmatched = false;
	  bool isTmatched = false;
	  TLorentzVector trueW,d1,d2,d3;

	  for(unsigned int iW = 0; iW < HadronicVHtPt_JetSubCalc->size(); iW++){
	    trueW.SetPtEtaPhiE(HadronicVHtPt_JetSubCalc->at(iW),HadronicVHtEta_JetSubCalc->at(iW),HadronicVHtPhi_JetSubCalc->at(iW),HadronicVHtEnergy_JetSubCalc->at(iW));

	    if(ak8_lv.DeltaR(trueW) < minDR){
	      minDR = ak8_lv.DeltaR(trueW);
	      matchedPt = HadronicVHtPt_JetSubCalc->at(iW);
	      matchedID = abs(HadronicVHtID_JetSubCalc->at(iW));	      
	      d1.SetPtEtaPhiE(HadronicVHtD0Pt_JetSubCalc->at(iW),HadronicVHtD0Eta_JetSubCalc->at(iW),HadronicVHtD0Phi_JetSubCalc->at(iW),HadronicVHtD0E_JetSubCalc->at(iW));
	      d2.SetPtEtaPhiE(HadronicVHtD1Pt_JetSubCalc->at(iW),HadronicVHtD1Eta_JetSubCalc->at(iW),HadronicVHtD1Phi_JetSubCalc->at(iW),HadronicVHtD1E_JetSubCalc->at(iW));
	      d3.SetPtEtaPhiE(HadronicVHtD2Pt_JetSubCalc->at(iW),HadronicVHtD2Eta_JetSubCalc->at(iW),HadronicVHtD2Phi_JetSubCalc->at(iW),HadronicVHtD2E_JetSubCalc->at(iW));
	    }
   	  }	 
	  
	  bool WallDsInJet = false;
	  bool TallDsInJet = false;
	  if(matchedID != 6 && ak8_lv.DeltaR(d1) < 0.8 && ak8_lv.DeltaR(d2) < 0.8) WallDsInJet = true;
	  if(matchedID == 6 && ak8_lv.DeltaR(d1) < 0.8 && ak8_lv.DeltaR(d2) < 0.8 && ak8_lv.DeltaR(d3) < 0.8) TallDsInJet = true;
	  if(minDR < 0.8 && matchedID == 24 && WallDsInJet) isWmatched = true;
	  if(minDR < 0.8 && matchedID == 6 && TallDsInJet) isTmatched = true;

	  theJetAK8Wmatch_JetSubCalc_PtOrdered.push_back(isWmatched);
	  theJetAK8Tmatch_JetSubCalc_PtOrdered.push_back(isTmatched);
	  if(isWmatched || isTmatched) theJetAK8MatchedPt_JetSubCalc_PtOrdered.push_back(matchedPt);
	  else theJetAK8MatchedPt_JetSubCalc_PtOrdered.push_back(-99.0);

	  if(isTmatched && matchedPt > 400) theJetAK8Truth_JetSubCalc_PtOrdered.push_back(1);
	  if(isWmatched && matchedPt > 200) theJetAK8Truth_JetSubCalc_PtOrdered.push_back(4);

	  // ------------------------------------------------------------------------------------------------------------------
	  // TOP TAGGING
	  // ------------------------------------------------------------------------------------------------------------------
	  float topTau81SF = 1.0;
	  float topTau81SFup = 1.0;
	  float topTau81SFdn = 1.0;
	  double topTau81Eff = 1.0;
	  if(isTmatched && matchedPt >= 400){	    
	    // VALUES FOR 76X FROM PAS
	    topTau81SF = 1.00;//0.96;
	    topTau81SFup = 1.00;//1.04;
	    topTau81SFdn = 1.00;//0.88;
	    
	    // Use matched T to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
	    if(isSig){
	      int bin = (std::upper_bound(ptRangeTpTpTop.begin(), ptRangeTpTpTop.end(), matchedPt)-ptRangeTpTpTop.begin())-1;
	      topTau81Eff = SignalEffTop[SigMass][bin];
	    }else{
	      int bin = (std::upper_bound(ptRangeTTbarTop.begin(), ptRangeTTbarTop.end(), matchedPt)-ptRangeTTbarTop.begin())-1;
	      if(isTT) topTau81Eff = TTbarEffTop[bin]; // ttbar
	      else if(isTTTT) topTau81Eff = TTbarEffTop[bin]; // using ttbar while TTTT is missing
	      else topTau81Eff = STEffTop[bin]; // ST
	    }
	  }
	  
	  // Set the initial tagged/untagged state
	  bool isTtagged = (massSD > 105) && (massSD < 220) && (tau32 < 0.81) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400);
	  bool isTtagged_JMSup = (massSD_JMSup > 105) && (massSD_JMSup < 220) && (tau32 < 0.81) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400);
	  bool isTtagged_JMSdn = (massSD_JMSdn > 105) && (massSD_JMSdn < 220) && (tau32 < 0.81) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400);
	  bool isTtagged_JMRup = (massSD_JMRup > 105) && (massSD_JMRup < 220) && (tau32 < 0.81) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400);
	  bool isTtagged_JMRdn = (massSD_JMRdn > 105) && (massSD_JMRdn < 220) && (tau32 < 0.81) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400);

	  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
	  int tag_topTau81 = applySF(isTtagged,topTau81SF,topTau81Eff);
	  int tag_topTau81up = applySF(isTtagged,topTau81SFup,topTau81Eff);
	  int tag_topTau81dn = applySF(isTtagged,topTau81SFdn,topTau81Eff);
	  int tag_topTau81_JMSup = applySF(isTtagged_JMSup,topTau81SF,topTau81Eff);
	  int tag_topTau81_JMSdn = applySF(isTtagged_JMSdn,topTau81SF,topTau81Eff);
	  int tag_topTau81_JMRup = applySF(isTtagged_JMRup,topTau81SF,topTau81Eff);
	  int tag_topTau81_JMRdn = applySF(isTtagged_JMRdn,topTau81SF,topTau81Eff);
 
	  // Now increase the tag count in the right variable	  
	  NJetsTtagged_0p81 += tag_topTau81;
	  NJetsTtagged_0p81_shifts[0] += tag_topTau81up;
	  NJetsTtagged_0p81_shifts[1] += tag_topTau81dn;
	  NJetsTtagged_0p81_shifts[2] += tag_topTau81_JMSup;
	  NJetsTtagged_0p81_shifts[3] += tag_topTau81_JMSdn;
	  NJetsTtagged_0p81_shifts[4] += tag_topTau81_JMRup;
	  NJetsTtagged_0p81_shifts[5] += tag_topTau81_JMRdn;

	  // ------------------------------------------------------------------------------------------------------------------
	  // W TAGGING
	  // ------------------------------------------------------------------------------------------------------------------

	  float Ptau0p55SF = 1.0;
	  float Ptau0p55SFup = 1.0;
	  float Ptau0p55SFdn = 1.0;
	  float Ptaupt0p55SFup = 1.0;
	  float Ptaupt0p55SFdn = 1.0;
	  double Ptau0p55Eff = 1.0;
	  if(isWmatched && matchedPt >= 175 && massSD > 65 && massSD < 105 && theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200){	    
	    // VALUES FOR 80X from TWiki
	    Ptau0p55SF = 1.00; //1.03;
	    Ptau0p55SFup = 1.00; //1.03+0.14;
	    Ptau0p55SFdn = 1.00; //1.03-0.14;
	    Ptaupt0p55SFup = 1.00; //1.03+0.041*log(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet)/200);
	    Ptaupt0p55SFdn = 1.00; //1.03-0.041*log(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet)/200);
	    
	    // Use matched W to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
	    if(isSig){
	      int bin = (std::upper_bound(ptRangeTpTp.begin(), ptRangeTpTp.end(), matchedPt)-ptRangeTpTp.begin())-1;
	      Ptau0p55Eff = SignalEffPuppi[SigMass][bin];
	    }else{
	      int bin = (std::upper_bound(ptRangeTTbar.begin(), ptRangeTTbar.end(), matchedPt)-ptRangeTTbar.begin())-1;
	      if(isTT){
		Ptau0p55Eff = TTbarEffPuppi[bin]; // ttbar
	      }
	      else if(isTTTT){
		Ptau0p55Eff = TTbarEffPuppi[bin]; // using ttbar while TTTT is missing
	      }
	      else if(isSTt){
		Ptau0p55Eff = STtEffPuppi[bin]; // single top (s and t channel had 0 boosted tops)
	      }
	      else if(isSTtW){
		Ptau0p55Eff = STtWEffPuppi[bin]; // single top (s and t channel had 0 boosted tops)
	      }
	      else{
		Ptau0p55Eff = WVEffPuppi[bin]; // WW, WZ, etc. 
	      }
	    }
	  }
	  
	  // Set the initial tagged/untagged state
	  bool isPWtagged = (massSD > 65) && (massSD < 105) && (tau21 < 0.45) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200);
	  if(isPWtagged) { theJetAK8Indx_Wtagged.push_back(ijet); }
	  bool isPWtagged_JMSup = (massSD_JMSup > 65) && (massSD_JMSup < 105) && (tau21 < 0.45) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200);
	  bool isPWtagged_JMSdn = (massSD_JMSdn > 65) && (massSD_JMSdn < 105) && (tau21 < 0.45) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200);
	  bool isPWtagged_JMRup = (massSD_JMRup > 65) && (massSD_JMRup < 105) && (tau21 < 0.45) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200);
	  bool isPWtagged_JMRdn = (massSD_JMRdn > 65) && (massSD_JMRdn < 105) && (tau21 < 0.45) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200);
 
	  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
	  int tag_Ptau0p55 = applySF(isPWtagged,Ptau0p55SF,Ptau0p55Eff);
 	  int tag_Ptau0p55up = applySF(isPWtagged,Ptau0p55SFup,Ptau0p55Eff);
	  int tag_Ptau0p55dn = applySF(isPWtagged,Ptau0p55SFdn,Ptau0p55Eff);
	  int tag_Ptau0p55_JMSup = applySF(isPWtagged_JMSup,Ptau0p55SF,Ptau0p55Eff);
	  int tag_Ptau0p55_JMSdn = applySF(isPWtagged_JMSdn,Ptau0p55SF,Ptau0p55Eff);
	  int tag_Ptau0p55_JMRup = applySF(isPWtagged_JMRup,Ptau0p55SF,Ptau0p55Eff);
	  int tag_Ptau0p55_JMRdn = applySF(isPWtagged_JMRdn,Ptau0p55SF,Ptau0p55Eff);
 	  int tag_Ptaupt0p55up = applySF(isPWtagged,Ptaupt0p55SFup,Ptau0p55Eff);
	  int tag_Ptaupt0p55dn = applySF(isPWtagged,Ptaupt0p55SFdn,Ptau0p55Eff);
	  
	  // Now increase the tag count in the right variable	  
	  NPuppiWtagged_0p55 += tag_Ptau0p55;
	  NPuppiWtagged_0p55_shifts[0] += tag_Ptau0p55up;
	  NPuppiWtagged_0p55_shifts[1] += tag_Ptau0p55dn;
	  NPuppiWtagged_0p55_shifts[2] += tag_Ptau0p55_JMSup;
	  NPuppiWtagged_0p55_shifts[3] += tag_Ptau0p55_JMSdn;
	  NPuppiWtagged_0p55_shifts[4] += tag_Ptau0p55_JMRup;
	  NPuppiWtagged_0p55_shifts[5] += tag_Ptau0p55_JMRdn;
	  NPuppiWtagged_0p55_shifts[6] += tag_Ptaupt0p55up;
	  NPuppiWtagged_0p55_shifts[7] += tag_Ptaupt0p55dn;

	  if(tag_Ptau0p55){NPuppiWtagged_0p55_notTtagged += tag_Ptau0p55-tag_topTau81;}
	  if(tag_Ptau0p55up){NPuppiWtagged_0p55_notTtagged_shifts[0] += tag_Ptau0p55up-tag_topTau81up;}
	  if(tag_Ptau0p55dn){NPuppiWtagged_0p55_notTtagged_shifts[1] += tag_Ptau0p55dn-tag_topTau81dn;}
	  if(tag_Ptau0p55_JMSup){NPuppiWtagged_0p55_notTtagged_shifts[2] += tag_Ptau0p55_JMSup-tag_topTau81;}//_JMSup
	  if(tag_Ptau0p55_JMSdn){NPuppiWtagged_0p55_notTtagged_shifts[3] += tag_Ptau0p55_JMSdn-tag_topTau81;}//_JMSdn
	  if(tag_Ptau0p55_JMRup){NPuppiWtagged_0p55_notTtagged_shifts[4] += tag_Ptau0p55_JMRup-tag_topTau81;}//_JMRup
	  if(tag_Ptau0p55_JMRdn){NPuppiWtagged_0p55_notTtagged_shifts[5] += tag_Ptau0p55_JMRdn-tag_topTau81;}//_JMRdn
	  if(tag_Ptaupt0p55up){NPuppiWtagged_0p55_notTtagged_shifts[6] += tag_Ptaupt0p55up-tag_topTau81up;}
	  if(tag_Ptaupt0p55dn){NPuppiWtagged_0p55_notTtagged_shifts[7] += tag_Ptaupt0p55dn-tag_topTau81dn;}
	  
	//
	}//end of isMC
	// ------------------------------------------------------------------------------------------------------------------
	// DATA Calculation second
	// ------------------------------------------------------------------------------------------------------------------
	else{
	  theJetAK8Wmatch_JetSubCalc_PtOrdered.push_back(0);
	  theJetAK8Tmatch_JetSubCalc_PtOrdered.push_back(0);
	  
	  bool isWtagged = (massSD > 65) && (massSD < 105) && (tau21 < 0.55) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 200);
	  if(isWtagged) { theJetAK8Indx_Wtagged.push_back(ijet); }
	  bool isTtagged = (massSD > 105) && (massSD < 220) && (tau32 < 0.81) && (theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet) >= 400);
	  
	  NPuppiWtagged_0p55 += isWtagged;
	  if(isWtagged){NPuppiWtagged_0p55_notTtagged += isWtagged-isTtagged;}
	  if(NPuppiWtagged_0p55 == 1){
	    WJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
	  }
	}
      }

      // ----------------------------------------------------------------------------
      // 13TeV Top pT reweighting -- TTbarMassCalc top vectors are the wrong tops....
      // ----------------------------------------------------------------------------
      
      genTopPt = -999;
      genAntiTopPt = -999;
      topPtWeight13TeV = 1.0;
      
      if(isTT){
	int top1index = -1;
	int top2index = -1;
	for(unsigned int itop=0; itop < allTopsStatus_TTbarMassCalc->size(); itop++){
	  if(allTopsStatus_TTbarMassCalc->at(itop) != 62) continue;
	  if(top1index < 0){
	    top1index = itop;
	    continue;
	  }
	  if(top2index < 0){
	    top2index = itop;
	    continue;
	  }
	}

	float SFtop1 = TMath::Exp(0.0615-0.0005*allTopsPt_TTbarMassCalc->at(top1index));
	float SFtop2 = TMath::Exp(0.0615-0.0005*allTopsPt_TTbarMassCalc->at(top2index));
	topPtWeight13TeV = TMath::Sqrt(SFtop1*SFtop2);

	if(allTopsID_TTbarMassCalc->at(top1index) == 6){
	  genTopPt = allTopsPt_TTbarMassCalc->at(top1index);
	  genAntiTopPt = allTopsPt_TTbarMassCalc->at(top2index);
	}
	else{
	  genAntiTopPt = allTopsPt_TTbarMassCalc->at(top1index);
	  genTopPt = allTopsPt_TTbarMassCalc->at(top2index);
	}
      }
      
      // ----------------------------------------------------------------------------
      // AK4 Jet - lepton associations
      // ----------------------------------------------------------------------------

      NJetsCSV_JetSubCalc = 0;
      NJetsCSVwithSF_JetSubCalc = 0;
      BJetLeadPt = -99;
      minMleppBjet = 1e8;
      minMleppJet = 1e8;
      minDR_lepJet = 1e8;
      ptRel_lepJet = -99;
      deltaR_lepJets.clear();
      deltaR_lepBJets.clear();

      for(unsigned int ijet=0; ijet < theJetPt_JetSubCalc_PtOrdered.size(); ijet++){
        jet_lv.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered.at(ijet),theJetEta_JetSubCalc_PtOrdered.at(ijet),theJetPhi_JetSubCalc_PtOrdered.at(ijet),theJetEnergy_JetSubCalc_PtOrdered.at(ijet));
	if((lepton_lv + jet_lv).M() < minMleppJet) {
	  minMleppJet = fabs((lepton_lv + jet_lv).M());
	}

	deltaR_lepJets.push_back(lepton_lv.DeltaR(jet_lv));

        // FOR NOW DON'T USE THE SCALE FACTORS               **** NEED TO CHANGE TO DEEPCSV probb + probbb > 0.4941                          
	if(theJetDeepCSVb_JetSubCalc_PtOrdered.at(ijet) + theJetDeepCSVbb_JetSubCalc_PtOrdered.at(ijet) > 0.4941){
          NJetsCSV_JetSubCalc += 1;
        }
	// OK, we're back to using SFs
	if(theJetBTag_JetSubCalc_PtOrdered.at(ijet) == 1){
	  NJetsCSVwithSF_JetSubCalc += 1;
          if(theJetPt_JetSubCalc_PtOrdered.at(ijet) > BJetLeadPt) BJetLeadPt = theJetPt_JetSubCalc_PtOrdered.at(ijet);
          deltaR_lepBJets.push_back(lepton_lv.DeltaR(jet_lv));
	  
          if((lepton_lv + jet_lv).M() < minMleppBjet) {
            minMleppBjet = fabs( (lepton_lv + jet_lv).M() );
          }

	}

 	if(deltaR_lepJets[ijet] < minDR_lepJet) {
	  minDR_lepJet = deltaR_lepJets[ijet];
	  ptRel_lepJet = lepton_lv.P()*(jet_lv.Vect().Cross(lepton_lv.Vect()).Mag()/jet_lv.P()/lepton_lv.P());
	}
      }

      // ----------------------------------------------------------------------------
      // PDF and Matrix Element energy scale weights
      // ----------------------------------------------------------------------------

      std::vector<double> renorm;
      std::vector<double> pdf;
      renormWeights.clear();
      pdfWeights.clear();
      if(isSig){
	// SEEMS TO APPLY TO ALL B2G MG+PYTHIA SIGNALS. LEADING ORDER 4-FLAVOR PDF
	for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
	  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
	    if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
	    renorm.push_back(LHEweights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) > 111 && LHEweightids_singleLepCalc->at(i) < 212){
	    pdf.push_back(LHEweights_singleLepCalc->at(i));	    
	    pdfWeights.push_back(LHEweights_singleLepCalc->at(i));	    
	  }
	}
      }
      else if(isMadgraphBkg){
	// SEEMS TO APPLY TO OTHER MG+PYTHIA BACKGROUNDS. LEADING ORDER 5-FLAVOR PDF
	for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
	  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
	    if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
	    renorm.push_back(LHEweights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) > 10 && LHEweightids_singleLepCalc->at(i) < 111){
	    pdf.push_back(LHEweights_singleLepCalc->at(i));
	    pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	}
      }
      else{
	// SEEMS TO APPLY TO ALL POWHEG AND MC@NLO BACKGROUNDS. NLO PDFs
	for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
	  if(LHEweightids_singleLepCalc->at(i) > 1001 && LHEweightids_singleLepCalc->at(i) < 1010){
	    if(LHEweightids_singleLepCalc->at(i) == 1006 || LHEweightids_singleLepCalc->at(i) == 1008) continue;
	    renorm.push_back(LHEweights_singleLepCalc->at(i));
	    renormWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) > 2000 && LHEweightids_singleLepCalc->at(i) < 2101){
	    pdf.push_back(LHEweights_singleLepCalc->at(i));
	    pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	  if(LHEweightids_singleLepCalc->at(i) == 2101 || LHEweightids_singleLepCalc->at(i) == 2102){
	    alphaSWeights.push_back(LHEweights_singleLepCalc->at(i));
	  }
	}
      }

      if(renormWeights.size() == 0){
	if(isVV){
	  renormWeights.push_back(0.85);
	  renormWeights.push_back(1.15);
	  renormWeights.push_back(0.85);
	  renormWeights.push_back(0.85);
	  renormWeights.push_back(1.15);
	  renormWeights.push_back(1.15);
	}else if(isSTt || isSTtW){
	  renormWeights.push_back(0.84);
	  renormWeights.push_back(1.16);
	  renormWeights.push_back(0.84);
	  renormWeights.push_back(0.84);
	  renormWeights.push_back(1.16);
	  renormWeights.push_back(1.16);
	}else{
	  for(int irn = 0; irn < 6; irn++){
	    renormWeights.push_back(1.0);
	  }
	}
      }
      if(pdfWeights.size() == 0){
	for(int ipdf = 0; ipdf < 100; ipdf++){
	  pdfWeights.push_back(1.0);
	}
      }

      // ----------------------------------------------------------------------------
      // DONE!! Write the tree
      // ----------------------------------------------------------------------------
      
      outputTree->Fill();
   }
   std::cout<<"Nelectrons      = "<<Nelectrons<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ElEta   = "<<npass_ElEta<<" / "<<nentries<<std::endl;
   std::cout<<"Nmuons          = "<<Nmuons<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MuEta   = "<<npass_MuEta<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_Trigger = "<<npass_trigger<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MET     = "<<npass_met<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_lepPt   = "<<npass_lepPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_HT      = "<<npass_ht<<" / "<<nentries<<std::endl;
   std::cout<<"npass_Njets     = "<<npass_Njets<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL     = "<<npass_all<<" / "<<nentries<<std::endl;

   outputTree->Write();

}
