
#include <SpdMCParticle.h>
#include <SpdTrackMC.h>
#include <SpdMCTrack.h>

#include <SpdTrackFitPar.h>
#include <SpdVertexRC.h>

#include <SpdTrackFitPar.h>

#include <SpdAegMCHit.h>

#include "TFile.h"
#include "TTree.h"

#include "TVector3.h"
#include <cmath>

using namespace std;



void analysis4()
{

    SpdMCDataIterator *IT = 0;
    const SpdSetParSet *pars = 0;

    const TClonesArray *mc_particles = 0;
    const TClonesArray *mc_tracks = 0;

    const TClonesArray *particles_tof = 0;
    const TClonesArray *particles_ts = 0;
    const TClonesArray *particles_aeg = 0;


    IT = new SpdMCDataIterator();

    IT->AddSourceFile("reco_full.root");

    IT->ActivateBranch("MCParticles");
    IT->ActivateBranch("MCTracks");

    IT->ActivateBranch("TsParticles");
    IT->ActivateBranch("TofParticles");
    IT->ActivateBranch("AegParticles");



    IT->Init();

    //----------------------------------------------------------
    // Get data pointers
    pars = IT->GetParameters();

    mc_particles = IT->GetParticles();
    mc_tracks = IT->GetTracks();

    particles_ts = IT->GetTsParticles();
    particles_tof = IT->GetTofParticles();
    particles_aeg = IT->GetAegParticles();

   
   // TOF
    Int_t IdTof;
    Double_t TofMass2; // Mass-squared information from the Time-of-Flight system
    Double_t Momentum_tof; // momentum used for calculations [GeV/c]
    vector<Double_t> Distances_tof;  // distances (number of sigmas) : 0 - pion, 1- kaon, 2 - proton
    vector<Double_t> Likelihoods_tof; // likelihoods (gaussian): 0 - pion,  1 - kaon, 2 - proton
    vector<Double_t> PosteriorProbs_tof; // posteriors probability : 0 - pion, 1 - kaon, 2 - proton

    // STRAW
    Int_t  IdTs;
    Double_t dEdx; // truncated mean dE/dx [GeV/cm]
    Double_t Momentum_ts; // momentum used for calculations [GeV/c]
    vector<Double_t> Distances_ts;  // distances (number of sigmas) : 0 - pion, 1- kaon, 2 - proton
    vector<Double_t> Likelihoods_ts; // likelihoods (gaussian): 0 - pion,  1 - kaon, 2 - proton

    // Common for both TOF & STRAW TRACKER
    Double_t pdg; // PDG
    Double_t mass; // true mass
    Double_t pT;  // Transverse Momentum
    Double_t P; //Total Momentum


    cout << "====="
              << "N=" << mc_tracks->GetEntriesFast() << endl;

    int ne_total(0);
     
    // -------------------------------------------------------
    // -------------------------------------------------------

    // My Tasks:
    // loop over events
    // Fill histograms (X-axis is pareticle momentum):
    //   -- all paricles identfied as pi (211)
    //   -- pions identified as pions
    //   -- protons identified as pions
    //   -- kaons identified as pions
    
    
    TH1F *hist1 = new TH1F("hist1", "Correctly Identified Pions By TOF Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist2 = new TH1F("hist2", "Kaons Identified As Pions By TOF Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist3 = new TH1F("hist3", "Anti/Protons Identified As Pions By TOF Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist4 = new TH1F("hist4", "All Charged Particles Identified As Pions By TOF Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist9 = new TH1F("hist9", "Electrons/Positrons Identified As Pions By TOF Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist10 = new TH1F("hist10", "Muons Identified As Pions By TOF Detector; pT(GeV/c); Counts", 40, 0, 2);

    TH1F *hist5 = new TH1F("hist5", "Correctly Identified Pions By ST Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist6 = new TH1F("hist6", "Kaons Identified As Pions By ST Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist7 = new TH1F("hist7", "Anti/Protons Identified As Pions By ST Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist8 = new TH1F("hist8", "All Charged Particles Identified As Pions By ST Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist11 = new TH1F("hist11", "Electrons/Positrons Identified As Pions By ST Detector; pT(GeV/c); Counts", 40, 0, 2);
    TH1F *hist12 = new TH1F("hist12", "Muons Identified As Pions By ST Detector; pT(GeV/c); Counts", 40, 0, 2);
    
    
    int ttracks = 0; // ttracks indicates total no. of processed tracks.  // Just for checking :)
    
    
    while ((IT->NextEvent()))
    {
        cout << "Event " << ne_total << endl << endl;

        Int_t Nmctracks = mc_tracks->GetEntriesFast();
        
      //  if(ne_total==999) cout << Nmctracks << endl;
        
        for (int imctrack = 0; imctrack < Nmctracks; imctrack++)
        {

            SpdTrackMC *mctrack = (SpdTrackMC *)mc_tracks->At(imctrack);
            if (!mctrack)
                continue;


            SpdMCParticle *mcparticle = (SpdMCParticle *)mc_particles->At(mctrack->GetParticleId());
            if (!mcparticle)
                continue;

            cout << "Track " << mctrack->GetId() << endl;

            pdg = mctrack->GetParticlePdg();
            mass = mcparticle->GetMass();
            cout << "pdg=" << pdg << "  mass=" << mass << endl;

           //**************************************Calculating Momentum & Transverse Momentum of final particles just before identification************************************** 

            SpdTrackFitPar* fitpars = mctrack->GetFitPars();
            if (!fitpars) continue;
            SpdTrackState* laststate = fitpars->GetLastState();
            if (!laststate) continue;
            TVector3 p = laststate->GetMomentum();           // p denotes the spatial component of the momentum 4 vector. So, it will store values of px, py, and pz.

            pT = sqrt(pow(p.X(), 2) + pow(p.Y(), 2));                        // Calculating Transverse Momentum
            P =  sqrt(pow(p.X(), 2) + pow(p.Y(), 2) + pow(p.Z(), 2));        //  Calculating Total Momentum
            
            cout << "px=" << p.X() << " py=" << p.Y() << " pz=" << p.Z() << " pT=" << pT << " p=" << P << endl;

            //**************************************End of Calculation of Momentum & Transverse Momentum****************************************************************************

            ttracks+=1;

            // TOF
            IdTof = mcparticle->GetTofParticleId();
            if (IdTof != -1){
                
                SpdTofParticle *ftofparticle = (SpdTofParticle *)particles_tof->At(IdTof);
                if (ftofparticle){
                   
                    TofMass2 = ftofparticle->GetTofMass2();
                    
                    Momentum_tof = ftofparticle->GetMomentum();
                    Distances_tof = ftofparticle->GetDistances();
                    Likelihoods_tof = ftofparticle->GetLikelihoods();
                    PosteriorProbs_tof = ftofparticle->GetPosteriorProbs();
                   

                    cout << "tof: LK_pion=" << Likelihoods_tof[0] << " LK_kaon=" << Likelihoods_tof[1] << " LK_proton=" << Likelihoods_tof[2] << endl;
                    cout << "tof: Momentum=" << Momentum_tof << endl;
                    
                    long double max_val = Likelihoods_tof[0];
                    for(int i=0; i<3; i++)
                    {
                           if(Likelihoods_tof[i]> max_val) max_val = Likelihoods_tof[i];

                    }
                    
                    cout << "Max. LK_TOF = " << max_val << endl;
                    
                      //Condition for correctly identified pions by TOF detector;

                    if(max_val == Likelihoods_tof[0] && (pdg==211 || pdg==-211)) 

                    {
                        cout << "The final stage of particle was pion and was reconstructed as pion by TOF detector" << endl;
                        hist1->Fill(pT);

                    }  

                    //Condition for kaons identified as pions by TOF detector;

                    if(max_val == Likelihoods_tof[0] && (pdg==321 || pdg==-321)) 

                    {
                        cout << "The final stage of particle was kaon but reconstructed as pion by TOF detector" << endl;
                        hist2->Fill(pT);

                    }  

                    //Condition for protons identified as pions by TOF detector;

                    if(max_val == Likelihoods_tof[0] && (pdg==2212 || pdg==-2212)) 

                    {
                        cout << "The final stage of particle was proton(or antiproton) but reconstructed as pion by TOF detector" << endl;
                        hist3->Fill(pT);

                    } 

                    //Condition for all those particles which has been identified as pions by TOF, but in reality they could be some other charged particles also;

                    if(max_val == Likelihoods_tof[0]) 

                    {
                        hist4->Fill(pT);

                    }
                    
                    //Condition for Electrons/Positrons identified as pions by TOF detector;

                    if(max_val == Likelihoods_tof[0] && (pdg==11 || pdg==-11)) 

                    {
                        cout << "The final stage of particle was electron(or positron) but reconstructed as pion by TOF detector" << endl;
                        hist9->Fill(pT);

                    }  
                    
                    //Condition for muons identified as pions by TOF detector;

                    if(max_val == Likelihoods_tof[0] && (pdg==13 || pdg==-13)) 

                    {
                        cout << "The final stage of particle was muon but reconstructed as pion by TOF detector" << endl;
                        hist10->Fill(pT);

                    }     
                    
                }
            }

            // STRAW
            IdTs = mcparticle->GetTsParticleId();
            if (IdTs != -1){

                SpdTsParticle *ftsparticle = (SpdTsParticle *)particles_ts->At(IdTs);
                if (ftsparticle){

                    dEdx = ftsparticle->GetTruncMeandEdx();
                    
                    Momentum_ts = ftsparticle->GetMomentum();
                    Distances_ts = ftsparticle->GetDistances();
                    Likelihoods_ts = ftsparticle->GetLikelihoods();
                   

                    cout << "straw: LK_pion=" << Likelihoods_ts[0] << " LK_kaon=" << Likelihoods_ts[1] << " LK_proton=" << Likelihoods_ts[2] << endl;
                    cout << "straw: Momentum=" << Momentum_ts << endl;


                    long double max_val2 = Likelihoods_ts[0];
                    for(int i=0; i<3; i++)
                    {
                           if(Likelihoods_ts[i] > max_val2)              max_val2 = Likelihoods_ts[i];

                    }
                    
                       cout << "Max. LK_ST = " << max_val2 << endl;
                       
                      //Condition for correctly identified pions by ST detector;

                    if(max_val2 == Likelihoods_ts[0] && (pdg==211 || pdg==-211)) 

                    {
                        cout << "The final stage of particle was pion and was reconstructed as pion by ST detector" << endl;
                        hist5->Fill(pT);

                    }  

                    //Condition for kaons identified as pions by ST detector;

                    if(max_val2 == Likelihoods_ts[0] && (pdg==321 || pdg==-321)) 

                    {
                        cout << "The final stage of particle was kaon but reconstructed as pion by ST detector" << endl;
                        hist6->Fill(pT);

                    }  

                    //Condition for protons identified as pions by ST detector;

                    if(max_val2 == Likelihoods_ts[0] && (pdg==2212 || pdg==-2212)) 

                    {
                        cout << "The final stage of particle was proton(or antiproton) but reconstructed as pion by ST detector" << endl;
                        hist7->Fill(pT);

                    } 

                    //Condition for all those particles which has been identified as pions by ST, but in reality they could be some other charged particles also;

                    if(max_val2 == Likelihoods_ts[0]) 

                    {
                        hist8->Fill(pT);

                    }  
                    
                    //Condition for electrons(or positrons) identified as pions by ST detector;

                    if(max_val2 == Likelihoods_ts[0] && (pdg==11 || pdg==-11)) 

                    {
                        cout << "The final stage of particle was electron(or positron) but reconstructed as pion by ST detector" << endl;
                        hist11->Fill(pT);

                    } 
                    
                    //Condition for muons identified as pions by ST detector;

                    if(max_val2 == Likelihoods_ts[0] && (pdg==13 || pdg==-13)) 

                    {
                        cout << "The final stage of particle was muon but reconstructed as pion by ST detector" << endl;
                        hist12->Fill(pT);

                    } 

 

                }
            }

           

            cout<<"\n";
        }

        //--------
        ne_total++;
    }
    
    cout << "Total no. of processed tracks in C12-C12 collision = " << ttracks << endl;
    
   THStack *stack1 = new THStack("stack1", "Charged Particles Identified as Pions by TOF, C12-C12; pT(GeV/c); Counts");
   THStack *stack2 = new THStack("stack2", "Charged Particles Identified as Pions by ST, C12-C12; pT(GeV/c); Counts");

   stack1->Add(hist1);
   stack1->Add(hist2);
   stack1->Add(hist3);
   stack1->Add(hist4);
   stack1->Add(hist9);
   stack1->Add(hist10);

    stack2->Add(hist5);
    stack2->Add(hist6);
    stack2->Add(hist7);
    stack2->Add(hist8);
    stack2->Add(hist11);
    stack2->Add(hist12);


    TCanvas *C1 = new TCanvas("Charged Particles Identified as Pions by TOF, C12-C12", "C1");
    
    hist1->SetLineWidth(3);
    
    hist2->SetLineColor(2);
    hist2->SetLineStyle(2);
    hist2->SetLineWidth(3);

    hist3->SetLineColor(3);
    hist3->SetLineStyle(3);
    hist3->SetLineWidth(3);

    hist4->SetLineColor(28);
    hist4->SetLineStyle(7);
    hist4->SetLineWidth(3);
    
    hist9->SetLineColor(7);
    hist9->SetLineStyle(5);
    hist9->SetLineWidth(3);
    
    hist10->SetLineColor(46);
    hist10->SetLineStyle(9);
    hist10->SetLineWidth(3);
    
    stack1->Draw("nostack");


    TLegend* leg1 = new TLegend(0.75,0.75,0.9,0.9);

    leg1->AddEntry(hist1, "Pions identified as pions");
    leg1->AddEntry(hist2, "Kaons identified as pions");
    leg1->AddEntry(hist3, "Protons identified as pions");
    leg1->AddEntry(hist9, "Electrons identified as pions");
    leg1->AddEntry(hist10, "Muons identified as pions");
    leg1->AddEntry(hist4, "Charged particles identified as pions");
    leg1->Draw("same");



  TCanvas *C2 = new TCanvas("Charged Particles Identified as Pions by ST, C12-C12", "C2");
  
     hist5->SetLineWidth(3); 

     hist6->SetLineColor(2);
     hist6->SetLineStyle(2);
     hist6->SetLineWidth(3);
     

     hist7->SetLineColor(3);
     hist7->SetLineStyle(3);
     hist7->SetLineWidth(3);

     hist8->SetLineColor(28);
     hist8->SetLineStyle(7);
     hist8->SetLineWidth(3);
     
     hist11->SetLineColor(7);
     hist11->SetLineStyle(5);
     hist11->SetLineWidth(3);
    
     hist12->SetLineColor(46);
     hist12->SetLineStyle(9);
     hist12->SetLineWidth(3);

     TLegend* leg2 = new TLegend(0.4, 0.4, 0.6, 0.6);

     leg2->AddEntry(hist5, "Pions identified as pions");
     leg2->AddEntry(hist6, "Kaons identified as pions");
     leg2->AddEntry(hist7, "Protons identified as pions");
     leg2->AddEntry(hist11, "Electrons identified as pions");
     leg2->AddEntry(hist12, "Muons identified as pions");
     leg2->AddEntry(hist8, "Charged particles identified as pions");
     
      
     stack2->Draw("nostack");
     
     leg2->Draw("same");
}




