
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
#include <map>

using namespace std;



void analysis7()
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
    Int_t charge;
    
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
    
    
    TH1F *hist1 = new TH1F("hist1", "Total Multiplicity of Charged Particles (Detector Stage, Ca40-Ca40); No. of charged particles; No. of events", 100, 1, 100);
    
    map<int, int> pdgs;   //using map to print unique pdgs.
    
    int ttracks = 0; // ttracks indicates total no. of processed tracks.  // Just for checking :)
    int ncharge;
    
    
    while ((IT->NextEvent()))
    {
        cout << "Event " << ne_total << endl << endl;

        Int_t Nmctracks = mc_tracks->GetEntriesFast();
        
        ncharge = 0;
        
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

            pdg = mctrack->GetParticlePdg();                 pdgs[pdg]++;
            mass = mcparticle->GetMass();
            charge = mcparticle->GetCharge();                                                                    //Extracting charge of the particle using mcparticle object :)
            cout << "pdg=" << pdg << "  mass=" << mass << " charge="<< charge << endl;
            
            ttracks+=1;
            
            if (charge==1 || charge==-1) ncharge+=1;

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
                  

                }
            }
                   cout<<"\n";
        }
        
        
        //--------
        ne_total++;
        
        //Filling of histogram :)
        
        hist1->Fill(ncharge);
       
    }
    
    for(auto [pdg, n] : pdgs) {
        
        cout << pdg << " " << n << endl;
        
        }

    
    cout << "Total no. of processed tracks in Ca40-Ca40 collision = " << ttracks << endl;
    
    TCanvas *C1 = new TCanvas("Total Multiplicity of Charged Particles (Detector Stage, Ca40-Ca40)", "C1");
    
    hist1->SetLineWidth(3);
    hist1->SetStats(0);
    hist1->Draw();
   
}




