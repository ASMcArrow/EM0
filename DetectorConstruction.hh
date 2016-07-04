#ifndef DETECTORCONSTRUCTION_H
#define DETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

using namespace CLHEP;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction() {}
    ~DetectorConstruction() {}

    G4VPhysicalVolume* Construct();    
};

#endif

