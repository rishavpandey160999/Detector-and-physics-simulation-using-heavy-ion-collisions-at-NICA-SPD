

	#include<iostream>

	#include<string>

	using namespace std;

	void particle2()

	{
		
	//        fstream ptr;
	//	ptr.open("particle_lists.oscar", ios::in);


		ifstream ptr("/home/rishavpandey/Desktop/JINR_DLNP/smash/build/data/C12_C12/particle_lists.oscar");
		
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
		int ncharge, nprotons, nantiprotons, nkaons_plus, nkaons_min, npie_plus, npie_min, ntotal; 
		double x, y, z, mass, p0, px, py, pz;
		float fprotons, fantiprotons, fkaons_plus, fkaons_min, fpie_plus, fpie_min;
		 

		ncharge = nprotons = nantiprotons = nkaons_plus = nkaons_min = npie_plus = npie_min = ntotal = 0;
		
		// Defining Histograms:
		
		TH1F *hist1 = new TH1F("hist1", "No. of proton distribution; No. of protons; No. of events", 100, 0, 100);
		TH1F *hist2 = new TH1F("hist2", "No. of antiprotons distribution; No. of antiprotons; No. of events", 100, 0, 100);
		TH1F *hist3 = new TH1F("hist3", "No. of positive pion distribution; No. of positive pions; No. of events", 100, 0, 100);
		TH1F *hist4 = new TH1F("hist4", "No. of negative pion distribution; No. of negative pions; No. of events", 100, 0, 100);
		TH1F *hist5 = new TH1F("hist5", "No. of positive kaon distribution; No. of positive kaons; No. of events", 100, 0, 100);
		TH1F *hist6 = new TH1F("hist6", "No. of negative kaon distribution; No. of negative kaons; No. of events", 100, 0, 100);
		
		TH1F *hist7 = new TH1F("hist7", "Fraction of proton distribution; Fraction of protons; No. of events", 100, 0, 1);
		TH1F *hist8 = new TH1F("hist8", "Fraction of antiprotons distribution; Fraction of antiprotons; No. of events", 100, 0, 1);
		TH1F *hist9 = new TH1F("hist9", "Fraction of positive pion distribution; Fraction of positive pions; No. of events", 100, 0, 1);
		TH1F *hist10 = new TH1F("hist10", "Fraction of negative pion distribution; Fraction of negative pions; No. of events", 100, 0, 1);
		TH1F *hist11 = new TH1F("hist11", "Fraction of positive kaon distribution; Fraction of positive kaons; No. of events", 100, 0, 1);
		TH1F *hist12 = new TH1F("hist12", "Fraction of negative kaon distribution; Fraction of negative kaons; No. of events", 100, 0, 1);
		
		
		
		while(!ptr.eof())
		
		{

	  ptr >> word >> word >> a >> word >> b;
	  
	  if(ptr.eof()) break;


	  for(int j=1; j<=b; j++)

	  {

	     ptr >> t >> x >> y >> z >> mass >> p0 >> px >> py >> pz >> pdg >> ID >> charge;

	 //cout << "Event " << a << " Track " << j << ":  t=" << t << "  x=" << x << "  y=" << y << "  z=" << z << "  mass=" << mass << "  p0=" << p0 << "  px=" << px << "  py=" << py << "  pz=" << pz << "  pdg=" << pdg << "  ID=" << ID << "  charge=" << charge << endl;    

	 if(charge==1 || charge==-1)      ncharge+=1;
         if(pdg==2212)                    nprotons+=1;
         if(pdg==-2212)                   nantiprotons+=1;
	 if(pdg==211)                     npie_plus+=1;
	 if(pdg==-211)                    npie_min+=1;
	 if(pdg==321)                     nkaons_plus+=1;
	 if(pdg==-321)                    nkaons_min+=1;
	 
	 ntotal+=1;


	}
	
	fprotons = (nprotons*1.0)/(ncharge);
	fantiprotons = (nantiprotons*1.0)/(ncharge);
	fpie_plus = (npie_plus*1.0)/(ncharge);
	fpie_min = (npie_min*1.0)/(ncharge);
	fkaons_plus = (nkaons_plus*1.0)/(ncharge);
	fkaons_min = (nkaons_min*1.0)/(ncharge);
	
	hist1->Fill(nprotons);
	hist2->Fill(nantiprotons);
	hist3->Fill(npie_plus);
	hist4->Fill(npie_min);
	hist5->Fill(nkaons_plus);
	hist6->Fill(nkaons_min);
	
	hist7->Fill(fprotons);
	hist8->Fill(fantiprotons);
	hist9->Fill(fpie_plus);
	hist10->Fill(fpie_min);
	hist11->Fill(fkaons_plus);
	hist12->Fill(fkaons_min);
	
	ncharge = nprotons = nantiprotons = nkaons_plus = nkaons_min = npie_plus = npie_min = 0;

          //getline(ptr, line);
	  
	  ptr >> word >> word >> word >> word >> word >> word >> word >> word >> word;
	  
	  if(a==99999) cout<<"File completed"<<endl;
	   

		}



		ptr.close();
			
		//Drawing of histograms:
		
		TCanvas *C1 = new TCanvas("No. of proton distribution", "C1");
		hist1->SetLineWidth(3);
		hist1->Draw();
		
		TCanvas *C2 = new TCanvas("No. of antiproton distribution", "C2");
		hist2->SetLineWidth(3);
		hist2->Draw();
		
		TCanvas *C3 = new TCanvas("No. of positive pion distribution", "C3");
		hist3->SetLineWidth(3);
		hist3->Draw();
		
		TCanvas *C4 = new TCanvas("No. of negative pion distribution", "C4");
		hist4->SetLineWidth(3);
		hist4->Draw();
		
		TCanvas *C5 = new TCanvas("No. of positive kaon distribution", "C5");
		hist5->SetLineWidth(3);
		hist5->Draw();
		
		TCanvas *C6 = new TCanvas("No. of nagative kaon distribution", "C6");
		hist6->SetLineWidth(3);
		hist6->Draw();
		
		TCanvas *C7 = new TCanvas("Fraction of proton distribution", "C7");
		hist7->SetLineWidth(3);
		hist7->Draw();
		
		TCanvas *C8 = new TCanvas("Fraction of antiproton distribution", "C8");
		hist8->SetLineWidth(3);
		hist8->Draw();
		
		TCanvas *C9 = new TCanvas("Fraction of positive pion distribution", "C9");
		hist9->SetLineWidth(3);
		hist9->Draw();
		
		TCanvas *C10 = new TCanvas("Fraction of negative pion distribution", "C10");
		hist10->SetLineWidth(3);
		hist10->Draw();
		
		TCanvas *C11 = new TCanvas("Fraction of positive kaon distribution", "C11");
		hist11->SetLineWidth(3);
		hist11->Draw();
		
		TCanvas *C12 = new TCanvas("Fraction of nagative kaon distribution", "C12");
		hist12->SetLineWidth(3);
		hist12->Draw();
		
		
		
		}

	}
