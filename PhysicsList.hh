#ifndef PHYSICSLIST_H
#define PHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsList: public G4VModularPhysicsList
{
public:

  PhysicsList();
  virtual ~PhysicsList();

  void SetCuts();
  void ConstructProcess();

private:
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
};

#endif
