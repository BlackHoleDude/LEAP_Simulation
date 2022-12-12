//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Large Area Burst Polarimeter (LEAP)
//  PhaseA Prototype
//  Created: Feb 24, 2022 by Camden Ertley
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  class DetectorMessenger;

  //****************************************************************************
  /// Detector construction class to define materials and geometry.
  ///
  //****************************************************************************
  class DetectorConstruction : public G4VUserDetectorConstruction
  {
    public:
      DetectorConstruction();
      ~DetectorConstruction() override;

      // methods from base class
      G4VPhysicalVolume* Construct() override;
      void ConstructSDandField() override;
      
      // set methods
      void SetOverlapFlag( G4bool flag ) {fCheckOverlaps = flag;};          
//       void SetZenithAngle( G4double zang );          
//       void SetAzimuthAngle( G4double aang );          
//       void SetPolarizationAngle( G4double pang );          
      void UpdateGeometry();

    private:
      // methods
      void DefineMaterials();
      G4VPhysicalVolume* DefineVolumes();
    
      // data members
      DetectorMessenger* fDetMessenger = nullptr;   // messenger

      G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps

      G4VPhysicalVolume* fPhysicalModule = nullptr;
      
//       G4double fZenithAngle = 0.;
//       G4double fAzimuthAngle = 0.;
//       G4double fPolarizationAngle = 0.;
  };
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

