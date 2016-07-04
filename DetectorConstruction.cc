#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4VSolid.hh"

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    std::vector<G4Material*> MatVec;

    G4Element* H = nistManager->FindOrBuildElement(1);
    G4Element* C = nistManager->FindOrBuildElement(6);
    G4Element* O = nistManager->FindOrBuildElement(8);
    G4Element* N = nistManager->FindOrBuildElement(7);
    G4Element*Sb = nistManager->FindOrBuildElement(51);
    G4Element*Mg = nistManager->FindOrBuildElement(12);
    G4Element*Si = nistManager->FindOrBuildElement(14);
    G4Element*Cl = nistManager->FindOrBuildElement(17);
    G4Element*Ti = nistManager->FindOrBuildElement(22);
    G4Element*Ca = nistManager->FindOrBuildElement(20);

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
    LipowitzMetal -> AddElement(H, .500);
    LipowitzMetal -> AddElement(C, .267);
    LipowitzMetal -> AddElement(N, .133);
    LipowitzMetal -> AddElement(O, .100);
    MatVec.push_back(LipowitzMetal);

    // World
    G4Box* world = new G4Box("World", 3*m, 3*m, 3*m);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(world, LDfoam, "WorldLogic");
    G4VPhysicalVolume *worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "WorldPhys", 0, false, 0);

    return worldPhys;
}
