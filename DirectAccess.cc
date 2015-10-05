#include "G4Material.hh"
#include "G4Element.hh"

#include "G4hIonisation.hh"
#include "G4MaterialCutsCouple.hh"
#include "G4ProductionCuts.hh"
#include "G4BetheBlochModel.hh"
#include "G4BraggModel.hh"
#include "G4PhysicsListHelper.hh"

#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4EmCalculator.hh"
#include "G4RunManager.hh"

#include "G4Proton.hh"

#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4hNuclearStoppingModel.hh"
#include "G4hImpactIonisation.hh"
#include "G4hParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"

int main() {
    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);

    runManager->Initialize();
    runManager->RunInitialization();

    std::ofstream dedxFile("dedx.txt");

    G4UnitDefinition::BuildUnitsTable();
    G4double Emin, Emax, dE, Ecut;

    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* Water = nistManager->FindOrBuildMaterial("G4_WATER");

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    G4ParticleDefinition* proton = G4Proton::Proton();
    G4EmCalculator* EMCalculator = new G4EmCalculator;

    G4cout << "Common restricted stopping power for the two models" << G4endl;
    Emin = 1.1*keV; Emax = 1000*MeV; dE = 1*keV;
    for (G4double Energy = Emin; Energy <= Emax; Energy += dE)
    {
//        G4cout << G4BestUnit(Energy, "Energy") << " "
//               << G4BestUnit(EMCalculator->GetDEDX(Energy, proton, Water), "Energy/Length")
//               << "\n";
        dedxFile << Energy << " " << EMCalculator->GetDEDX(Energy, proton, Water) << "\n";
    }
    G4cout << G4endl;
    dedxFile << "\n";

    // Compute restricted stopping power for Bethe Bloch model

    G4VEmModel* ioni = new G4BetheBlochModel(proton);
    ioni->Initialise(proton, G4DataVector());

    Emin = 1.01*MeV; Emax = 302.01*MeV; dE = 1*keV;
    Ecut = 100*TeV;

    G4cout << "Restricted stopping power for Bethe Bloch model" << G4endl;
    for (G4double Energy = Emin; Energy <= Emax; Energy += dE)
    {
//        G4cout << G4BestUnit (Energy, "Energy") << " "
//               << G4BestUnit (ioni->ComputeDEDXPerVolume(Water, proton, Energy, Ecut), "Energy/Length")
//               << "\n";
        dedxFile << Energy << " " << ioni->ComputeDEDXPerVolume(Water, proton, Energy, Ecut) << "\n";
    }
    G4cout << G4endl;
    dedxFile << "\n";

    // Compute restricted stopping power for Bragg model
    ioni = new G4BraggModel(proton);
    ioni->Initialise(proton, G4DataVector());

    Emin = 1.1*keV; Emax = 2.01*MeV; dE = 1*keV;
    Ecut = 100*TeV;

    G4cout << "Restricted stopping power for Bragg model" << G4endl;
    for (G4double Energy = Emin; Energy <= Emax; Energy += dE)
    {
//        G4cout << G4BestUnit (Energy, "Energy") << " "
//               << G4BestUnit (ioni->ComputeDEDXPerVolume(Water, proton, Energy, Ecut), "Energy/Length")
//               << "\n";
        dedxFile << Energy << " " << ioni->ComputeDEDXPerVolume(Water, proton, Energy, Ecut) << "\n";
    }
    G4cout << G4endl;
    dedxFile << "\n";

    // Compute compute parameterized low energy
    G4hParametrisedLossModel *param = new G4hParametrisedLossModel("Ziegler1985p");

    Emin = 1.0*keV; Emax = 1000*MeV; dE = 1*keV;
    Ecut = 100*TeV;

    G4cout << "Restricted stopping power for Ziegler1988 for compounds" << G4endl;
    for (G4double Energy = Emin; Energy <= Emax; Energy += dE)
    {
//        G4cout << G4BestUnit (Energy, "Energy") << " "
//               << G4BestUnit (param->StoppingPower(Water, Energy), "Energy/Length")
//               << "\n";
        dedxFile << Energy << " " << param->StoppingPower(Water, Energy) << "\n";
    }
    G4cout << G4endl;
    dedxFile << "\n";

    param = new G4hParametrisedLossModel("ICRU_R49p");

    Emin = 1.0*keV; Emax = 10*MeV; dE = 1*keV;
    Ecut = 100*TeV;

    G4cout << "Restricted stopping power for ICRU_R49p" << G4endl;
    for (G4double Energy = Emin; Energy <= Emax; Energy += dE)
    {
//        G4cout << G4BestUnit (Energy, "Energy") << " "
//               << G4BestUnit (param->StoppingPower(Water, Energy), "Energy/Length")
//               << "\n";
        dedxFile << Energy << " " << param->StoppingPower(Water, Energy) << "\n";
    }
    G4cout << G4endl;
    dedxFile << "\n";

    G4hNuclearStoppingModel* nuc = new G4hNuclearStoppingModel("Ziegler1985");

    Emin = 1.0*keV; Emax = 100*MeV; dE = 1*keV;
    Ecut = 100*TeV;

    G4cout << "Nuclear stopping power" << G4endl;
    for (G4double Energy = Emin; Energy <= Emax; Energy += dE)
    {
//        G4cout << G4BestUnit (Energy, "Energy") << " "
//               << G4BestUnit (nuc->TheValue(proton, Water, Energy), "Energy/Length")
//               << "\n";
        dedxFile << Energy << " " << nuc->TheValue(proton, Water, Energy) << "\n";
    }
    G4cout << G4endl;
    dedxFile << "\n";


    return EXIT_SUCCESS;
}
