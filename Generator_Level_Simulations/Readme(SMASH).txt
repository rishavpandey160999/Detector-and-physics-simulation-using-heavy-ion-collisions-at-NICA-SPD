           
 This file contains information about different directories and .C files present at **generator level**.
 
 Inside data dir. there are two main sub directories:
    - Ca40_Ca40  --------> Contains 100K generated events of Ca40-Ca40 collisions @ sqrt(s)=11GeV + some analysis files of .C format.
    - C12_C12  --------> Contains 100K generated events of C12-C12 collisions @ sqrt(s)=11GeV + some analysis files of .C format.
    
    
    ************************************************Inside Ca40_Ca40 dir. following files are present***************************************************
    
    1. particle1.C ----> Rapidity distribution, Transverse Momentum distribution, and Total Momentum distribution of all charged particles (p+, p-bar, K+, K-, mu+, mu-) **considered separately**. 
    
    2. particle2.C ----> Multiplicity of charged particles (p+, p-bar, K+, K-, mu+, mu-) considered separately + Fraction of charged particles distributions considered separately.
    
    3. particle3.C ----> Multiplicity of positive charged particles (by considering all +ve particles collectively) +  Multiplicity of negative charged particles (by considering all -ve particles 
                           collectively) + Total multiplicity of charged particles (considering both positive & negative particles collectively).
                           
    4. particle4.C -----> Contains some stats like unique pdg codes of particles present in .oscar file, No. of different types of charged particles, and Percentage of different types of charged 
                          particles out of all charged particles.
                          
    6. config.yaml -----> Input File
    
    7. particle_lists.oscar ----> Output File (contains 100K events of Ca40-Ca40 collisions)
    
    
    
    ************************************************Inside C12_C12 dir. following files are present***************************************************
    
    
    SAME AS Ca40_Ca40 Dir.
    
    
    **********************************************************************************************************************************************************
