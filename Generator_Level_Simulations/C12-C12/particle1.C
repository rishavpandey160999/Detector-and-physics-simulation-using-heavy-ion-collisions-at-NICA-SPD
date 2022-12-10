

		#include<iostream>

		#include<string>
		
		#include<cmath>

		using namespace std;

		void particle1()

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
			
			THStack *stack1 = new THStack("stack1", "Rapidity distribution of charged particles; Rapidity of charged particles (y); No. of charged particles");
			THStack *stack2 = new THStack("stack2", "Transverse Momentum distribution of charged particles; Transverse momentum of charged particles (pT); No. of charged particles");
			THStack *stack3 = new THStack("stack3", "Total Momentum distribution of charged particles; Total momentum of charged particles (p); No. of charged particles");
			
			TH1F *hist1 = new TH1F("hist1", "Rapidity distribution of charged particles; Rapidity of charged particles (y); No. of charged particles", 100, -5, 5);
			TH1F *hist2 = new TH1F("hist2", " ", 100, -5, 5);
			TH1F *hist3 = new TH1F("hist3", " ", 100, -5, 5);
			TH1F *hist4 = new TH1F("hist4", " ", 100, -5, 5);
			TH1F *hist5 = new TH1F("hist5", " ", 100, -5, 5);
			TH1F *hist6 = new TH1F("hist6", " ", 100, -5, 5);
			TH1F *hist7 = new TH1F("hist7", "Transverse momentum distribution of charged particles; Transverse momentum of charged particles (pT); No. of charged particles", 100, 0, 5);
			TH1F *hist8 = new TH1F("hist8", " ", 100, 0, 5);
			TH1F *hist9 = new TH1F("hist9", " ", 100, 0, 5);
			TH1F *hist10 = new TH1F("hist10", " ", 100, 0, 5);
			TH1F *hist11 = new TH1F("hist11", " ", 100, 0, 5);
			TH1F *hist12 = new TH1F("hist12", " ", 100, 0, 5);
			TH1F *hist13 = new TH1F("hist13", "Total momentum distribution of charged particles; Total momentum of charged particles (p); No. of charged particles", 100, 0, 5);
			TH1F *hist14 = new TH1F("hist14", " ", 100, 0, 5);
			TH1F *hist15 = new TH1F("hist15", " ", 100, 0, 5);
			TH1F *hist16 = new TH1F("hist16", " ", 100, 0, 5);
			TH1F *hist17 = new TH1F("hist17", " ", 100, 0, 5);
			TH1F *hist18 = new TH1F("hist18", " ", 100, 0, 5);
			
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


		
		 if(pdg==2212)
		 {

		    hist1->Fill(rapidity);                    
		                           
		    if(rapidity>-0.5 && rapidity<0.5)  {hist7->Fill(pT); hist13->Fill(ptot);}
		    
	         }
	         
	         if(pdg==-2212)
		 {

		    hist2->Fill(rapidity);                    
		                           
		    if(rapidity>-0.5 && rapidity<0.5)  {hist8->Fill(pT); hist14->Fill(ptot);}
		    
	         }			 
		
		if(pdg==211)
		 {
		   
		     hist3->Fill(rapidity);
		     
		     if(rapidity>-0.5 && rapidity<0.5)  {hist9->Fill(pT); hist15->Fill(ptot);}
		       
	         }
	         
	         if(pdg==-211)
		 {
		   
		     hist4->Fill(rapidity);
		     
		     if(rapidity>-0.5 && rapidity<0.5)  {hist10->Fill(pT); hist16->Fill(ptot);}
		       
	         }
	         
	         if(pdg==321)
		 {
		   
		     hist5->Fill(rapidity);
		     
		     if(rapidity>-0.5 && rapidity<0.5)  {hist11->Fill(pT); hist17->Fill(ptot);}
		       
	         }
	         
	         if(pdg==-321)
		 {
		   
		     hist6->Fill(rapidity);
		     
		     if(rapidity>-0.5 && rapidity<0.5)  {hist12->Fill(pT); hist18->Fill(ptot);}
		       
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
			stack1 -> Add(hist4);
			stack1 -> Add(hist5);
			stack1 -> Add(hist6);
			
			stack2 -> Add(hist7);
			stack2 -> Add(hist8);
			stack2 -> Add(hist9);
			stack2 -> Add(hist10);
			stack2 -> Add(hist11);
			stack2 -> Add(hist12);
			
			stack3 -> Add(hist13);
			stack3 -> Add(hist14);
			stack3 -> Add(hist15);
			stack3 -> Add(hist16);
			stack3 -> Add(hist17);
			stack3 -> Add(hist18);
					
	
			//Drawing of histograms:
			
			TCanvas *C1 = new TCanvas("Rapidity distribution of charged particles", "C1");
			
			hist1 -> SetLineWidth(3);
			//hist1 -> Draw();
			
			hist2 -> SetLineStyle(2);
			hist2 -> SetLineColor(2);
			hist2 -> SetLineWidth(3);
			//hist2 -> Draw("same");
			
			hist3 -> SetLineStyle(3);
			hist3 -> SetLineColor(3);
			hist3 -> SetLineWidth(3);
			//hist3 -> Draw("same");
			
			hist4 -> SetLineStyle(7);
			hist4 -> SetLineColor(6);
			hist4 -> SetLineWidth(3);
			//hist4 -> Draw("same");
			
			hist5 -> SetLineStyle(5);
			hist5 -> SetLineColor(7);
			hist5 -> SetLineWidth(3);
			//hist5 -> Draw("same");
			
			hist6 -> SetLineStyle(9);
			hist6 -> SetLineColor(8);
			hist6 -> SetLineWidth(3);
			//hist6 -> Draw("same");
			
			stack1 -> Draw("nostack");
			
			TLegend *leg1 = new TLegend(0.75, 0.75, 0.9, 0.9);
			leg1 -> AddEntry(hist1, "protons");
			leg1 -> AddEntry(hist2, "antiprotons");
			leg1 -> AddEntry(hist3, "pions+");
			leg1 -> AddEntry(hist4, "pions-");
			leg1 -> AddEntry(hist5, "kaons+");
			leg1 -> AddEntry(hist6, "kaons-");
			leg1 -> Draw("same");
			
			TCanvas *C2 = new TCanvas("Transverse momentum distribution of charged particles", "C2");
			
			hist7 -> SetLineWidth(3);
			//hist7 -> Draw();
			
			hist8 -> SetLineStyle(2);
			hist8 -> SetLineColor(2);
			hist8 -> SetLineWidth(3);
			//hist8 -> Draw("same");
			
			hist9 -> SetLineStyle(3);
			hist9 -> SetLineColor(3);
			hist9 -> SetLineWidth(3);
			//hist9 -> Draw("same");
			
			hist10 -> SetLineStyle(7);
			hist10 -> SetLineColor(6);
			hist10 -> SetLineWidth(3);
			//hist10 -> Draw("same");
			
			hist11 -> SetLineStyle(5);
			hist11 -> SetLineColor(7);
			hist11 -> SetLineWidth(3);
			//hist11 -> Draw("same");
			
			hist12 -> SetLineStyle(9);
			hist12 -> SetLineColor(8);
			hist12 -> SetLineWidth(3);
			//hist12 -> Draw("same");
			
			stack2 -> Draw("nostack");
			
			TLegend *leg2 = new TLegend(0.75, 0.75, 0.9, 0.9);
			leg2 -> AddEntry(hist7, "protons");
			leg2 -> AddEntry(hist8, "antiprotons");
			leg2 -> AddEntry(hist9, "pions+");
			leg2 -> AddEntry(hist10, "pions-");
			leg2 -> AddEntry(hist11, "kaons+");
			leg2 -> AddEntry(hist12, "kaons-");
			leg2 -> Draw("same");
			
			TCanvas *C3 = new TCanvas("Total momentum distribution of charged particles", "C3");
			
			hist13 -> SetLineWidth(3);
			
			hist14 -> SetLineStyle(2);
			hist14 -> SetLineColor(2);
			hist14 -> SetLineWidth(3);
			
			
			hist15 -> SetLineStyle(3);
			hist15 -> SetLineColor(3);
			hist15 -> SetLineWidth(3);
			
			
			hist16 -> SetLineStyle(7);
			hist16 -> SetLineColor(6);
			hist16 -> SetLineWidth(3);
			
			hist17 -> SetLineStyle(5);
			hist17 -> SetLineColor(7);
			hist17 -> SetLineWidth(3);
			
			hist18 -> SetLineStyle(9);
			hist18 -> SetLineColor(8);
			hist18 -> SetLineWidth(3);
			
			stack3 -> Draw("nostack");
			
			TLegend *leg3 = new TLegend(0.75, 0.75, 0.9, 0.9);
			leg3 -> AddEntry(hist13, "protons");
			leg3 -> AddEntry(hist14, "antiprotons");
			leg3 -> AddEntry(hist15, "pions+");
			leg3 -> AddEntry(hist16, "pions-");
			leg3 -> AddEntry(hist17, "kaons+");
			leg3 -> AddEntry(hist18, "kaons-");
			leg3 -> Draw("same");
			
			
			}

		}
