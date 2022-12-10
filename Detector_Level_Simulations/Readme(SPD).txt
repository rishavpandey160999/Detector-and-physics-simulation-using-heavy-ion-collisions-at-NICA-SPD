           
 This file contains information about different directories and .C files present at **detector level**.
 
 Inside macro dir. there are three main sub directories:
    - MyProject1  --------> Contains Simulation script, Reconstruction script, Analysis scripts of p-p collisions @ sqrt(s)=27GeV.
    - MyProject2  --------> Contains Simulation script, Reconstruction script, Analysis scripts of Ca40-Ca40 collisions @ sqrt(s)=11GeV + Information about generator in .cxx & .h files.
    - MyProject3  --------> Contains Simulation script, Reconstruction script, Analysis scripts of C12-C12 collisions @ sqrt(s)=11GeV + Information about generator in .cxx & .h files.
    
    
    ************************************************Inside MyProject1 dir. following important files are present for p-p collision***************************************************
    
    1. analysis1.C ----> Total momentum distribution for different charged particles identified as pions (or pion spectra obtained for total momentum).
    
    2. analysis2.C ----> Total momentum distribution for different charged particles identified as kaons (or kaon spectra obtained for total momentum).
    
    3. analysis3.C ----> Total momentum distribution for different charged particles identified as protons (or proton spectra obtained for total momentum).
    
    4. analysis4.C -----> Transverse momentum distribution for different charged particles identified as pions (or pion spectra obtained for transverse momentum).
    
    5. analysis5.C -----> Transverse momentum distribution for different charged particles identified as kaons (or kaon spectra obtained for transverse momentum).
    
    6. analysis6.C -----> Transverse momentum distribution for different charged particles identified as protons (or proton spectra obtained for transverse momentum).
    
    7. analysis7.C -----> Total multiplicity of the charged particles (by considering both +ve & -ve charged particles) at detector stage + Unique pdg codes of particles just before identification.
                          
    8. RecoEventFull.C -----> Reconstruction Script.
    
    9. SimuQslPy8 ------> Simulation Script which uses SMASH as an event generator.
    
    10. SpdSmashGenerator.cxx -----> .cxx file of my generator.
    
    11. SpdSmashGenerator.h -------> Header file of generator.
    
    
    ************************************************Inside MyProject2 dir. following important files are present for Ca40-Ca40 collision***************************************************
    
    
    SAME INSTRUCTION AS GIVEN UNDER MyProject1
    
    
    ************************************************Inside MyProject3 dir. following important files are present for C12-C12 collision***************************************************
    
    
    SAME INSTRUCTION AS GIVEN UNDER MyProject1
    
    
   **************************************************************************************************************************************************************************************
    
    AGAIN PLEASE NOTE:
    
    MyProject1 is for p-p collisions, MyProject2 is for Ca40-Ca40 colisions, and MyProject3 is for C12-C12 collisions.
