

	#include<iostream>

	#include<string>

	using namespace std;

	void particle6()

	{
		
	//        fstream ptr;
	//	ptr.open("particle_lists.oscar", ios::in);


		ifstream ptr("/home/rishavpandey/Desktop/JINR_DLNP/smash/build/data/Ca40_Ca40/particle_lists.oscar");
		
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
		int ncharge, nprotons, nkaons, npions, ntotal; 
		double x, y, z, mass, p0, px, py, pz;
		float fprotons, fkaons, fpions;
		 

		ncharge = nprotons = nkaons = npions = ntotal = 0;
		
		// Defining Histograms:
		
		TH1F *hist1 = new TH1F("hist1", "Multiplicity of protons, Ca-40 + Ca-40; No. of protons; No. of events", 100, 0, 100);
		TH1F *hist2 = new TH1F("hist2", "Multiplicity of pions, Ca-40 + Ca-40; No. of pions; No. of events", 100, 0, 100);	
		TH1F *hist3 = new TH1F("hist3", "Multiplicity of kaons, Ca-40 + Ca-40; No. of kaons; No. of events", 100, 0, 100);
		
		
		TH1F *hist4 = new TH1F("hist4", "Fraction of proton distribution, Ca-40 + Ca-40; Fraction of protons; No. of events", 100, 0, 1);
		TH1F *hist5 = new TH1F("hist5", "Fraction of pion distribution, Ca-40 + Ca-40; Fraction of pions; No. of events", 100, 0, 1);
		TH1F *hist6 = new TH1F("hist6", "Fraction of kaon distribution, Ca-40 + Ca-40; Fraction of kaons; No. of events", 100, 0, 1);

		
		
		
		while(!ptr.eof())
		
		{

	  ptr >> word >> word >> a >> word >> b;
	  
	  if(ptr.eof()) break;


	  for(int j=1; j<=b; j++)

	  {

	     ptr >> t >> x >> y >> z >> mass >> p0 >> px >> py >> pz >> pdg >> ID >> charge;

	 //cout << "Event " << a << " Track " << j << ":  t=" << t << "  x=" << x << "  y=" << y << "  z=" << z << "  mass=" << mass << "  p0=" << p0 << "  px=" << px << "  py=" << py << "  pz=" << pz << "  pdg=" << pdg << "  ID=" << ID << "  charge=" << charge << endl;    

	 if(charge==1 || charge==-1)      ncharge+=1;
         if(pdg==2212 || pdg==-2212)      nprotons+=1;
	 if(pdg==211 || pdg==-211)        npions+=1;
	 if(pdg==321 || pdg==-321)        nkaons+=1;
	 
	 
	 ntotal+=1;


	}
	
	fprotons = (nprotons*1.0)/(ncharge);
	fpions = (npions*1.0)/(ncharge);
	fkaons = (nkaons*1.0)/(ncharge);
	
	hist1->Fill(nprotons);
	hist2->Fill(npions);
 	hist3->Fill(nkaons);
	
	hist4->Fill(fprotons);
	hist5->Fill(fpions);
	hist6->Fill(fkaons);
	
	ncharge = nprotons = nkaons = npions = 0;

          //getline(ptr, line);
	  
	  ptr >> word >> word >> word >> word >> word >> word >> word >> word >> word;
	  
	  if(a==99999) cout<<"File completed"<<endl;
	   

		}



		ptr.close();
			
		//Drawing of histograms:
		
		TCanvas *C1 = new TCanvas("Multiplicity of protons, Ca-40 + Ca-40", "C1");
		hist1->SetLineWidth(3);
		hist1->Draw();
		hist1->SetStats(0);
		
		TCanvas *C2 = new TCanvas("Multiplicity of pions, Ca-40 + Ca-40", "C2");
		hist2->SetLineWidth(3);
		hist2->Draw();
		hist2->SetStats(0);
		
		TCanvas *C3 = new TCanvas("Multiplicity of kaons, Ca-40 + Ca-40", "C3");
		hist3->SetLineWidth(3);
		hist3->Draw();
		hist3->SetStats(0);
		
		TCanvas *C4 = new TCanvas("Fraction of proton distribution, Ca-40 + Ca-40", "C4");
		hist4->SetLineWidth(3);
		hist4->Draw();
		hist4->SetStats(0);
		
		TCanvas *C5 = new TCanvas("Fraction of pion distribution, Ca-40 + Ca-40", "C5");
		hist5->SetLineWidth(3);
		hist5->Draw();
		hist5->SetStats(0);
		
		TCanvas *C6 = new TCanvas("Fraction of kaon distribution, Ca-40 + Ca-40", "C6");
		hist6->SetLineWidth(3);
		hist6->Draw();
		hist6->SetStats(0);
		
		}

	}
