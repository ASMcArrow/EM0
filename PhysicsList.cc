#include "PhysicsList.hh"

// Physic lists (contained inside the Geant4 source code, in the 'physicslists folder')
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4ParallelWorldScoringProcess.hh"
#include "G4EmParameters.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4WentzelVIModel.hh"

#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
#include "G4HadronPhysicsQGSP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4HadronicInteractionRegistry.hh"
#include "G4CascadeInterface.hh"
#include "G4AblaInterface.hh"
#include "FTFP_BERT_TRV.hh"
#include "G4HadronHElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT_TRV.hh"
#include "G4NuclearStopping.hh"

using namespace CLHEP;

PhysicsList::PhysicsList() : G4VModularPhysicsList()
{
    G4LossTableManager::Instance();
    defaultCutValue = 1*km;
    cutForGamma     = defaultCutValue;
    cutForElectron  = defaultCutValue;
    cutForPositron  = defaultCutValue;

    G4EmParameters* emParameters = G4EmParameters::Instance();
    emParameters->SetMinEnergy(0*eV);
    emParameters->SetMaxEnergy(300*MeV);
    emParameters->SetNumberOfBinsPerDecade(50);

    emParameters->SetApplyCuts(true);
    emParameters->SetVerbose(true);

    RegisterPhysics(new G4EmStandardPhysics_option4);
    //RegisterPhysics(new PhysListEmStandardSingleSc);
    RegisterPhysics(new G4HadronPhysicsINCLXX);
    RegisterPhysics(new G4EmExtraPhysics);
    RegisterPhysics(new G4HadronElasticPhysics);
    RegisterPhysics(new G4StoppingPhysics);
    RegisterPhysics(new G4IonBinaryCascadePhysics);
    RegisterPhysics(new G4NeutronTrackingCut);
    SetVerboseLevel(3);
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();
}

void PhysicsList::SetCuts()
{
    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma
    SetCutsWithDefault();
    SetCutValue(cutForGamma, "gamma");
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");

    G4cout << "Cut value for proton " << GetCutValue("proton") << " Cut valurfor ion " << GetCutValue("GenericIon") << G4endl;
}

