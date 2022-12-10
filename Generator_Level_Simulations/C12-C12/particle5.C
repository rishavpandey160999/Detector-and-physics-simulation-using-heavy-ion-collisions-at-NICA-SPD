

		#include<iostream>

		#include<string>
		
		#include<cmath>

		using namespace std;

		void particle5()

		{
		
		        fstream ptr;
			ptr.open("/home/rishavpandey/Desktop/JINR_DLNP/smash/build/data/C12_C12/particle_lists.oscar", ios::in);


		//	ifstream ptr("particle_lists.oscar");
			
			if(!ptr)
			
			{
			
			    cout << "File not found" << endl;
			    
			}
			
			else{


			string line, word;
			getline(ptr, line);
			getline(ptr, line);
			getline(ptr, line);
			
		       	int a, b, t, pdg, ID, charge;
			
			double x, y, z, mass, p0, px, py, pz;
			
			float rapidity, pT, ptot;
			 

			// Defining Histograms:
			
			THStack *stack1 = new THStack("stack1", "Rapidity distribution of charged particles, C-12 + C-12; Rapidity of charged particles (y); No. of charged particles");
			
			TH1F *hist1 = new TH1F("hist1", "Rapidity distribution of charged particles, C-12 + C-12; Rapidity of charged particles (y); No. of charged particles", 100, -5, 5);
			TH1F *hist2 = new TH1F("hist2", " ", 100, -5, 5);
			TH1F *hist3 = new TH1F("hist3", " ", 100, -5, 5);
			TH1F *hist4 = new TH1F("hist4", "Transverse momentum distribution of protons, C-12 + C-12; Transverse momentum of protons (pT); No. of protons", 100, 0, 5);
			TH1F *hist5 = new TH1F("hist5", "Transverse momentum distribution of pions, C-12 + C-12; Transverse momentum of pions (pT); No. of pions", 100, 0, 5);
			TH1F *hist6 = new TH1F("hist6", "Transverse momentum distribution of kaons, C-12 + C-12; Transverse momentum of kaons (pT); No. of kaons", 100, 0, 5);
			TH1F *hist7 = new TH1F("hist7", "Total momentum distribution of protons, C-12 + C-12; Total momentum of protons (p); No. of protons", 100, 0, 5);
			TH1F *hist8 = new TH1F("hist8", "Total momentum distribution of pions, C-12 + C-12; Total momentum of pions (p); No. of pions", 100, 0, 5);
			TH1F *hist9 = new TH1F("hist9", "Total momentum distribution of kaons, C-12 + C-12; Total momentum of kaons (p); No. of kaons", 100, 0, 5);
			
			while(!ptr.eof())

			
			{

		  ptr >> word >> word >> a >> word >> b;
		  
		  if(ptr.eof()) 
		  {
		      break;
		  }


		 for(int j=1; j<=b; j++)

		  {

		     ptr >> t >> x >> y >> z >> mass >> p0 >> px >> py >> pz >> pdg >> ID >> charge;

		// cout << "Event " << a << " Track " << j << ":  t=" << t << "  x=" << x << "  y=" << y << "  z=" << z << "  mass=" << mass << "  p0=" << p0 << "  px=" << px << "  py=" << py << "  pz=" << pz << "  pdg=" << pdg << "  ID=" << ID << "  charge=" << charge << endl;    
		
		rapidity = (0.5)*log((p0+pz)/(p0-pz));            
		    
		pT = sqrt(pow(px,2)+pow(py,2)); 
		
		ptot = sqrt(pow(px,2)+pow(py,2)+pow(pz,2)); 


		
		 if(pdg==2212 || pdg==-2212)
		 {

		    hist1->Fill(rapidity);                    
		                           
		    if(rapidity>-0.5 && rapidity<0.5)  {hist4->Fill(pT); hist7->Fill(ptot);}
		    
	         }
	
		if(pdg==211 || pdg==-211)
		 {
		   
		     hist2->Fill(rapidity);
		     
		     if(rapidity>-0.5 && rapidity<0.5)  {hist5->Fill(pT); hist8->Fill(ptot);}
		       
	         }
	      
	         if(pdg==321 || pdg==-321)
		 {
		   
		     hist3->Fill(rapidity);
		     
		     if(rapidity>-0.5 && rapidity<0.5)  {hist6->Fill(pT); hist9->Fill(ptot);}
		       
	         }
	         
	         
		}
	

		  //getline(ptr, line);
		  
		  ptr >> word >> word >> word >> word >> word >> word >> word >> word >> word;
                            
                          if(a==99999) cout<<"File Completed"<<endl;		  

			}



			ptr.close();
			
			stack1 -> Add(hist1);
			stack1 -> Add(hist2);
			stack1 -> Add(hist3);
			
			//Drawing of histograms:
			
			TCanvas *C1 = new TCanvas("Rapidity distribution of charged particles, C-12 + C-12", "C1");
			hist1 -> SetLineWidth(3);
			//hist1 -> Draw();
			
			hist2 -> SetLineStyle(2);
			hist2 -> SetLineColor(2);
			hist2 -> SetLineWidth(3);
			//hist2 -> Draw("same");
			
			hist3 -> SetLineStyle(4);
			hist3 -> SetLineColor(3);
			hist3 -> SetLineWidth(3);
			//hist3 -> Draw("same");
			
			stack1 -> Draw("nostack");
			
			TLegend *leg1 = new TLegend(0.75, 0.75, 0.9, 0.9);
			leg1 -> AddEntry(hist1, "protons");
			leg1 -> AddEntry(hist2, "pions");
			leg1 -> AddEntry(hist3, "kaons");
			leg1 -> Draw("same");
			
			TCanvas *C2 = new TCanvas("Transverse momentum distribution of protons, C-12 + C-12", "C2");
			hist4 -> SetLineWidth(3);
			hist4 -> Draw();
			hist4 -> SetStats(0);
			
			TCanvas *C3 = new TCanvas("Transverse momentum distribution of pions, C-12 + C-12", "C3");
			hist5 -> SetLineWidth(3);
			hist5 -> Draw();
			hist5 -> SetStats(0);
			
			TCanvas *C4 = new TCanvas("Transverse momentum distribution of kaons, C-12 + C-12", "C4");
			hist6 -> SetLineWidth(3);
			hist6 -> Draw();
			hist6 -> SetStats(0);
			
			TCanvas *C5 = new TCanvas("Total momentum distribution of protons, C-12 + C-12", "C5");
			hist7 -> SetLineWidth(3);
			hist7 -> Draw();
			hist7 -> SetStats(0);
			
			TCanvas *C6 = new TCanvas("Total momentum distribution of pions, C-12 + C-12", "C6");
			hist8 -> SetLineWidth(3);
			hist8 -> Draw();
			hist8 -> SetStats(0);
			
			TCanvas *C7 = new TCanvas("Total momentum distribution of kaons, C-12 + C-12", "C7");
			hist9 -> SetLineWidth(3);
			hist9 -> Draw();
			hist9 -> SetStats(0);
			
			}

		}
