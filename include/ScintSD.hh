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
/// \file ScintSD.hh
/// \brief Definition of the ScintSD class

#ifndef ScintSD_h
#define ScintSD_h 1

#include "G4VSensitiveDetector.hh"

#include "ScintHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  class EventAction;

  //****************************************************************************
  /// Scint sensitive detector class
  ///
  /// In Initialize(), it creates one hit for each Scint 
  ///
  //****************************************************************************
  class ScintSD : public G4VSensitiveDetector
  {
    public:
      ScintSD(G4String name);
      ~ScintSD() override;
    
      // methods from base class
      void   Initialize(G4HCofThisEvent* hitCollection) override;
      G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
      void   EndOfEvent(G4HCofThisEvent* hitCollection) override;

    private:
      // methods
      G4double BirksAttenuation(const G4Step*);

      // data members
      ScintHitsCollection* fHitsCollection = nullptr;
      G4int fHCID = -1;

  };

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

