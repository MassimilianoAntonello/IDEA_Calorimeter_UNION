//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B4aEventAction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file B4aEventAction.hh
/// \brief Definition of the B4aEventAction class

#ifndef B4aEventAction_h
#define B4aEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>


/// Event action class 

class B4aEventAction : public G4UserEventAction
{
  public:
    B4aEventAction();
    virtual ~B4aEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void Addem(G4double de);  //Add em component
    void AddScin(G4double de);//Add energy in scintillating fibers
    void AddCher(G4double de);//Add energy in Cherenkov fibers
    void AddCherenkov();//Add cherenkov photoelectron
    //void AddScintillation();
    void Addenergy(G4double de);//Add all energy deposited
    //void AddEnergyfibre(G4double de, G4int number);//Add energy in copy number fiber
    //void AddSignalfibre(G4int number);
    void SavePrimaryParticle(G4String name);
    void SavePrimaryEnergy(G4double primaryparticleenergy);

    //to save vectors in ntuple
    std::vector<G4double>& GetVectorSignalsR() {return VectorSignalsR;}
    std::vector<G4double>& GetVectorSignalsL() {return VectorSignalsL;} 
    std::vector<G4double>& GetVectorSignalsCherR() {return VectorSignalsCherR;}
    std::vector<G4double>& GetVectorSignalsCherL() {return VectorSignalsCherL;}
    std::vector<G4double>& GetVectorR() {return VectorR;}
    std::vector<G4double>& GetVectorL() {return VectorL;}

    //to fill vectors
    void AddVectorScinEnergyR(G4double de, G4int tower, G4int slice); //fill vector of scintillating fibers with energy deposition
    void AddVectorScinEnergyL(G4double de, G4int tower, G4int slice); //fill vector left side
    void AddVectorCherPER(G4int tower, G4int slice);//fill vector of cherenkov fibers with chernekov photoelectrons
    void AddVectorCherPEL(G4int tower, G4int slice);
    void AddVectorR(G4double de, G4int tower, G4int slice);
    void AddVectorL(G4double de, G4int tower, G4int slice);

  private:
    G4double  Energyem; //Energy of em component
    G4double  EnergyScin; //Energy in scintillating fibers
    G4double  EnergyCher; //Energy in Cherenkov fibers
    G4int     NofCherenkovDetected; //Number of Cherenkov photons detected (in cherenkov fibers)
    //G4int     NofScintillationDetected;//Number of Scintillating photons detected (in scintillating fibers)
    G4double  EnergyTot;//Total energy deposited (does not count invisibile energy)
    //G4double  Signalfibre[64];//Signal in 64 single module fibers, to be used with AddEnergyfibre
    G4String PrimaryParticleName; //Name of primary particle
    G4double PrimaryParticleEnergy;//Primary particle energy

    std::vector<G4double> VectorSignalsR;//Vector filled with scintillating fibers energy deposits
    std::vector<G4double> VectorSignalsL;//vector filled for left side
    std::vector<G4double> VectorSignalsCherR;//Vector filled with Cherenkov fibers Cherenkov photoelectrons
    std::vector<G4double> VectorSignalsCherL;//vector filled for left side
    
    std::vector<G4double> VectorR; //vector with energy deposited in towers right
    std::vector<G4double> VectorL;
};

// inline functions
inline void B4aEventAction::AddVectorR(G4double de, G4int tower, G4int slice){
	VectorR.at(tower+(slice*75)) += de;	
}

inline void B4aEventAction::AddVectorL(G4double de, G4int tower, G4int slice){
	tower = -1*tower;
	VectorL.at(tower+(slice*75)) += de;
}

inline void B4aEventAction::SavePrimaryParticle(G4String name){
  PrimaryParticleName = name;
}

inline void B4aEventAction::SavePrimaryEnergy(G4double primaryparticleenergy){
  PrimaryParticleEnergy = primaryparticleenergy;
}

inline void B4aEventAction::AddVectorScinEnergyR(G4double de, G4int tower, G4int slice) {
    VectorSignalsR.at(tower+(slice*75)) += de;
}

inline void B4aEventAction::AddVectorScinEnergyL(G4double de, G4int tower, G4int slice) {
    tower = -1*tower;
    VectorSignalsL.at(tower+(slice*75)) += de;
}

inline void B4aEventAction::AddVectorCherPEL(G4int tower, G4int slice) {
	tower = -1*tower;
    VectorSignalsCherL.at(tower+(slice*75)) = VectorSignalsCherL.at(tower+(slice*75))+1;
}

inline void B4aEventAction::AddVectorCherPER(G4int tower, G4int slice) {
    VectorSignalsCherR.at(tower+(slice*75)) = VectorSignalsCherR.at(tower+(slice*75))+1;
}

inline void B4aEventAction::Addem(G4double de) {
  Energyem += de; 
}

inline void B4aEventAction::AddScin(G4double de){
  EnergyScin += de;
}

inline void B4aEventAction::AddCher(G4double de){
  EnergyCher += de;
}

inline void B4aEventAction::AddCherenkov(){
  NofCherenkovDetected = NofCherenkovDetected + 1;
}

/*inline void B4aEventAction::AddScintillation(){
  NofScintillationDetected = NofScintillationDetected +1;
}*/

inline void B4aEventAction::Addenergy(G4double de){
  EnergyTot += de;
}

/*inline void B4aEventAction::AddEnergyfibre(G4double de, G4int number){
    Signalfibre[number] += de;
}*/

/*inline void B4aEventAction::AddSignalfibre(G4int number){
    Signalfibre[number] = Signalfibre[number] + 1;
}*/
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
