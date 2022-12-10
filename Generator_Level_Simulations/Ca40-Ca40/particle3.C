

	#include<iostream>

	#include<string>

	using namespace std;

	void particle3()

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
		int ncharge, npcharge, nncharge;   // ncharge->No. of charged tracks.   npcharge->No. of positive charged tracks.    nncharge->No. of negative charged tracks.
		double x, y, z, mass, p0, px, py, pz;
		
		ncharge = npcharge = nncharge = 0;
		
		// Defining Histograms:
		
		TH1F *hist1 = new TH1F("hist1", "Total Multiplicity of Positively Charged Particles, Ca-40 + Ca-40; No. of positively charged particles; No. of events", 100, 0, 100);
		TH1F *hist2 = new TH1F("hist2", "Total Multiplicity of Negatively Charged Particles, Ca-40 + Ca-40; No. of negatively charged particles; No. of events", 100, 0, 100);
		TH1F *hist3 = new TH1F("hist3", "Total Multiplicity of Charged Particles, Ca-40 + Ca-40; No. of charged particles; No. of events", 100, 0, 100);

		
		while(!ptr.eof())
		
		{

	  ptr >> word >> word >> a >> word >> b;
	  
	  if(ptr.eof()) break;


	  for(int j=1; j<=b; j++)

	  {

	     ptr >> t >> x >> y >> z >> mass >> p0 >> px >> py >> pz >> pdg >> ID >> charge;

	 //cout << "Event " << a << " Track " << j << ":  t=" << t << "  x=" << x << "  y=" << y << "  z=" << z << "  mass=" << mass << "  p0=" << p0 << "  px=" << px << "  py=" << py << "  pz=" << pz << "  pdg=" << pdg << "  ID=" << ID << "  charge=" << charge << endl;    

	 if(charge==1 || charge==-1)      ncharge+=1;
     if(charge==1)                    npcharge+=1;
	 if(charge==-1)                   nncharge+=1;

	}
	
	//Filling of histogram :)

	hist1->Fill(npcharge);
	hist2->Fill(nncharge);
	hist3->Fill(ncharge);
	
	ncharge = npcharge = nncharge = 0;

          //getline(ptr, line);
	  
	  ptr >> word >> word >> word >> word >> word >> word >> word >> word >> word;
	  
	  if(a==99999) cout<<"File completed"<<endl;
	   

		}

		ptr.close();
			
		//Drawing of histograms:
		
		TCanvas *C1 = new TCanvas("Total Multiplicity of Positively Charged Particles, Ca-40 + Ca-40", "C1");
		hist1->SetLineWidth(3);
		hist1->Draw();
	  	hist1->SetStats(0);
		
		TCanvas *C2 = new TCanvas("Total Multiplicity of Negatively Charged Particles, Ca-40 + Ca-40", "C2");
		hist2->SetLineWidth(3);
		hist2->Draw();
		hist2->SetStats(0);
		
		TCanvas *C3 = new TCanvas("Total Multiplicity of Charged Particles, Ca-40 + Ca-40", "C3");
		hist3->SetLineWidth(3);
		hist3->Draw();
		hist3->SetStats(0);
		
		}

	}
