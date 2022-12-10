

	#include<iostream>

	#include<string>
	
	#include<map>

	using namespace std;

	void particle4()

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
		 

		ncharge = nprotons = nantiprotons = nkaons_plus = nkaons_min = npie_plus = npie_min = ntotal = 0;
		
		// Defining Histograms:
		
		map<int, int> pdgs;   //using map to print unique pdgs.
		
		while(!ptr.eof())
		
		{

	  ptr >> word >> word >> a >> word >> b;
	  
	  if(ptr.eof()) break;


	  for(int j=1; j<=b; j++)

	  {

	     ptr >> t >> x >> y >> z >> mass >> p0 >> px >> py >> pz >> pdg >> ID >> charge;

	 //cout << "Event " << a << " Track " << j << ":  t=" << t << "  x=" << x << "  y=" << y << "  z=" << z << "  mass=" << mass << "  p0=" << p0 << "  px=" << px << "  py=" << py << "  pz=" << pz << "  pdg=" << pdg << "  ID=" << ID << "  charge=" << charge << endl;   
	 
	 pdgs[pdg]++; 

	 if(charge==1 || charge==-1)      ncharge+=1;
         if(pdg==2212)                    nprotons+=1;
         if(pdg==-2212)                   nantiprotons+=1;
	 if(pdg==211)                     npie_plus+=1;
	 if(pdg==-211)                    npie_min+=1;
	 if(pdg==321)                     nkaons_plus+=1;
	 if(pdg==-321)                    nkaons_min+=1;
	 
	 ntotal+=1;


	}

          //getline(ptr, line);
	  
	  ptr >> word >> word >> word >> word >> word >> word >> word >> word >> word;
	  
	  if(a==99999) cout<<"File completed"<<endl;
	   

		}

		ptr.close();
		
		for(auto [pdg, n] : pdgs) {
        
        cout << pdg << " " << n << endl;
        
        }
			
 		cout << "No. of charged particles = " << ncharge << endl;
		cout << "No. of protons = " << nprotons << endl;
		cout << "No. of antiprotons = " << nantiprotons << endl;
		cout << "No. of pions plus = " << npie_plus << endl;
		cout << "No. of pions minus = " << npie_min << endl;
		cout << "No. of kaons plus = " << nkaons_plus << endl;
		cout << "No. of kaons minus = " << nkaons_min << endl << endl;
		
		cout << "Percentage of protons out of all charged particles = " << ((nprotons*1.0)/(ncharge))*100 << endl;
		cout << "Percentage of antiprotons out of all charged particles = " << ((nantiprotons*1.0)/(ncharge))*100 << endl;
		cout << "Percentage of pions plus out of all charged particles = " << ((npie_plus*1.0)/(ncharge))*100 << endl;
		cout << "Percentage of pions minus out of all charged particles = " << ((npie_min*1.0)/(ncharge))*100 << endl;
		cout << "Percentage of kaons plus out of all charged particles = " << ((nkaons_plus*1.0)/(ncharge))*100 << endl;
		cout << "Percentage of kaons minus out of all charged particles = " << ((nkaons_min*1.0)/(ncharge))*100 << endl;
		
		//Drawing of histograms:
		
		}

	}
