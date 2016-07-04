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
#include "G4Gamma.hh"
#include "G4MuonPlus.hh"

#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4hNuclearStoppingModel.hh"
#include "G4hImpactIonisation.hh"
#include "G4hParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"

#include <vector>

int main() {

    G4UnitDefinition::BuildUnitsTable();

    G4ParticleDefinition* gamma = G4Gamma::Gamma();
    G4ParticleDefinition* posit = G4Positron::Positron();
    G4ParticleDefinition* elec = G4Electron::Electron();
    G4ParticleDefinition* proton = G4Proton::Proton();
    G4ParticleDefinition* muon = G4MuonPlus::MuonPlus();
    G4ParticleTable* partTable = G4ParticleTable::GetParticleTable();
    partTable->SetReadiness();

    G4DataVector cuts;
    cuts.push_back(100*TeV);

    std::ofstream dedxG4File("dedxG4.txt");
    std::ofstream dedxJanniFile("dedxJanni.txt");

    //  Definition of necessary materials

    std::vector<G4Material*> MatVec;

    G4NistManager* nistManager = G4NistManager::Instance();

    G4Element* H = nistManager->FindOrBuildElement(1);
    G4Element* C = nistManager->FindOrBuildElement(6);
    G4Element* O = nistManager->FindOrBuildElement(8);
    G4Element* N = nistManager->FindOrBuildElement(7);
    G4Element* Sb = nistManager->FindOrBuildElement(51);
    G4Element* Mg = nistManager->FindOrBuildElement(12);
    G4Element* Si = nistManager->FindOrBuildElement(14);
    G4Element* Cl = nistManager->FindOrBuildElement(17);
    G4Element* Ti = nistManager->FindOrBuildElement(22);
    G4Element* Ca = nistManager->FindOrBuildElement(20);
    G4Element* Bi = nistManager->FindOrBuildElement(83);
    G4Element* Pb = nistManager->FindOrBuildElement(82);
    G4Element* Sn = nistManager->FindOrBuildElement(50);
    G4Element* Cd = nistManager->FindOrBuildElement(48);

    G4Material* Water = nistManager->FindOrBuildMaterial("G4_WATER");

    G4Material* LDfoam = new G4Material("LDfoam", 0.015*g/cm3, 2);
    LDfoam -> AddElement(H, .0774);
    LDfoam -> AddElement(C, .9226);
    MatVec.push_back(LDfoam);
    
    G4Material* HDfoam = new G4Material("HDfoam", 0.030*g/cm3, 2);
    HDfoam -> AddElement(H, .0774);
    HDfoam -> AddElement(C, .9226);
    MatVec.push_back(HDfoam);
    
    G4Material* DCPUfoam = new G4Material("DCPUfoam", 0.041*g/cm3, 4);
    DCPUfoam -> AddElement(H, .0454);
    DCPUfoam -> AddElement(C, .5405);
    DCPUfoam -> AddElement(N, .1261);
    DCPUfoam -> AddElement(O, .2880);
    MatVec.push_back(DCPUfoam);
    
    G4Material* TPLlung = new G4Material("TPLlung", 0.307*g/cm3, 5);
    TPLlung -> AddElement(H, .0918);
    TPLlung -> AddElement(C, .6778);
    TPLlung -> AddElement(N, .0250);
    TPLlung -> AddElement(O, .2031);
    TPLlung -> AddElement(Sb, .0022);
    MatVec.push_back(TPLlung);
    
    G4Material* RMIlung = new G4Material("RMIlung", 0.342*g/cm3, 7);
    RMIlung -> AddElement(H, .0833);
    RMIlung -> AddElement(C, .6032);
    RMIlung -> AddElement(N, .0167);
    RMIlung -> AddElement(O, .1738);
    RMIlung -> AddElement(Mg, .1154);
    RMIlung -> AddElement(Si, .0061);
    RMIlung -> AddElement(Cl, .0015);
    MatVec.push_back(RMIlung);

    G4Material* BolusWax = new G4Material("BolusWax", 0.926*g/cm3, 3);
    BolusWax -> AddElement(H, .141);
    BolusWax -> AddElement(C, .854);
    BolusWax -> AddElement(O, .005);
    MatVec.push_back(BolusWax);

    G4Material* HDPE = new G4Material("HDPE", 0.964*g/cm3, 2);
    HDPE -> AddElement(H, .1437);
    HDPE-> AddElement(C, .8563);
    MatVec.push_back(HDPE);

    G4Material* TPLtissue = new G4Material("TPLtissue", 1.011*g/cm3, 5);
    TPLtissue -> AddElement(H, .0918);
    TPLtissue -> AddElement(C, .6778);
    TPLtissue -> AddElement(N, .0250);
    TPLtissue -> AddElement(O, .2031);
    TPLtissue -> AddElement(Sb, .0022);
    MatVec.push_back(TPLtissue);

    G4Material* Spectra = new G4Material("Spectra", 1.012*g/cm3, 3);
    Spectra -> AddElement(H, .1073);
    Spectra -> AddElement(C, .8083);
    Spectra -> AddElement(O, .0844);
    MatVec.push_back(Spectra);

    G4Material* WHIPS = new G4Material("WHIPS", 1.026*g/cm3, 4);
    WHIPS -> AddElement(H, .0758);
    WHIPS -> AddElement(C, .9042);
    WHIPS -> AddElement(O, .0080);
    WHIPS -> AddElement(Ti, .0120);
    MatVec.push_back(WHIPS);

    G4Material* CLPS = new G4Material("CLPS", 1.048*g/cm3, 2);
    CLPS -> AddElement(H, .0774);
    CLPS -> AddElement(C, .9226);
    MatVec.push_back(CLPS);
    
    G4Material* PMMA = new G4Material("PMMA", 1.185*g/cm3, 3);
    PMMA -> AddElement(H, .0805);
    PMMA -> AddElement(C, .5999);
    PMMA -> AddElement(O, .3196);
    MatVec.push_back(PMMA);

    G4Material* PC = new G4Material("PC", 1.214*g/cm3, 3);
    PC -> AddElement(H, .0555);
    PC -> AddElement(C, .7558);
    PC -> AddElement(O, .1887);
    MatVec.push_back(PC);

    G4Material* Kevlar = new G4Material("Kevlar", 1.329*g/cm3, 4);
    Kevlar -> AddElement(H, .0566);
    Kevlar -> AddElement(C, .7331);
    Kevlar -> AddElement(N, .0588);
    Kevlar -> AddElement(O, .1515);
    MatVec.push_back(Kevlar);

    G4Material* PVCpod = new G4Material("PVCpod", 1.385*g/cm3, 3);
    PVCpod -> AddElement(H, .0484);
    PVCpod -> AddElement(C, .3844);
    PVCpod -> AddElement(Cl, .5672);
    MatVec.push_back(PVCpod);

    G4Material* CF = new G4Material("CF", 1.416*g/cm3, 3);
    CF -> AddElement(H, .0354);
    CF -> AddElement(C, .8802);
    CF -> AddElement(O, .0844);
    MatVec.push_back(CF);

    G4Material* FG = new G4Material("FG", 1.700*g/cm3, 4);
    FG -> AddElement(H, .0354);
    FG -> AddElement(C, .3802);
    FG -> AddElement(N, .3507);
    FG -> AddElement(O, .2337);
    MatVec.push_back(FG);

    G4Material* RMIbone = new G4Material("RMIbone", 1.829*g/cm3, 6);
    RMIbone -> AddElement(H, .0310);
    RMIbone -> AddElement(C, .3126);
    RMIbone -> AddElement(N, .0099);
    RMIbone -> AddElement(O, .3757);
    RMIbone -> AddElement(Cl, .0005);
    RMIbone -> AddElement(Ca, .2703);
    MatVec.push_back(RMIbone);
    
    G4Material* Aluminum = nistManager->FindOrBuildMaterial("G4_Al");
    MatVec.push_back(Aluminum);

    G4Material* LipowitzMetal = new G4Material("LipowitzMetal", 9.54*g/cm3, 4);
    LipowitzMetal -> AddElement(Bi, .500);
    LipowitzMetal -> AddElement(Pb, .267);
    LipowitzMetal -> AddElement(Sn, .133);
    LipowitzMetal -> AddElement(Cd, .100);
    MatVec.push_back(LipowitzMetal);

    std::vector<G4double> EnergyVector = {135*MeV, 175*MeV, 225*MeV};
    std::vector<G4double> JanniWater = {5.9122*MeV/cm, 4.9417*MeV/cm, 4.20125*MeV/cm};
    std::vector<G4double> Geant4Water;

    G4VEmModel* ioni = new G4BetheBlochModel();
    ioni->Initialise(proton, cuts);
    G4double Ecut = 100*TeV;

    for (G4int i = 0; i < 3; i++)
    {
        Geant4Water.push_back(ioni->ComputeDEDXPerVolume(Water, proton,
                                                         EnergyVector[i], Ecut));
    }

    for (G4double j = 0; j < MatVec.size(); j++)
    {
        dedxG4File << MatVec[j]->GetName() << "\n";
        dedxJanniFile << MatVec[j]->GetName() << "\n";

        for (G4int i = 0; i < 3; i++)
        {
            dedxG4File << EnergyVector[i] << " "
                     << ioni->ComputeDEDXPerVolume(MatVec[j], proton, EnergyVector[i], Ecut)/Geant4Water[i] << "\n";
            dedxJanniFile << EnergyVector[i] << " "
                     << ioni->ComputeDEDXPerVolume(MatVec[j], proton, EnergyVector[i], Ecut)/JanniWater[i] << "\n";
        }
    }

    return EXIT_SUCCESS;
}
