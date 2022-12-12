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
/// \file ScintSD.cc
/// \brief Implementation of the ScintSD class

#include "ScintSD.hh"
#include "Constants.hh"
#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4LossTableManager.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  ScintSD::ScintSD(G4String name)
   : G4VSensitiveDetector(name)
  {
    collectionName.insert( "ScintCollection" );
  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  ScintSD::~ScintSD()
  {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ScintSD::Initialize(G4HCofThisEvent* hce)
  {
    // Create hits collection
    fHitsCollection = new ScintHitsCollection( SensitiveDetectorName, collectionName[0] );

    // Add this collection in hce
    if (fHCID<0) {
      fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
  
    hce->AddHitsCollection(fHCID,fHitsCollection);
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  G4bool ScintSD::ProcessHits(G4Step* step, G4TouchableHistory*)
  {  
    // energy deposit
    auto edep = step->GetTotalEnergyDeposit();
    if ( edep == 0. ) return false;      

    // visible energy deposit
    auto fEmSaturation = G4LossTableManager::Instance()->EmSaturation();
    auto visedep = fEmSaturation -> VisibleEnergyDepositionAtAStep( step );

    //  Energy deposit with manual Birks attenuation
    auto birkedep = BirksAttenuation( step );

    // get touchables
    auto preStepPoint = step->GetPreStepPoint();
    auto touchable = preStepPoint->GetTouchable();

    // get copy number from mother volume
    auto copyNo = touchable->GetCopyNumber(1);
    // G4cout << "copyNo:" << copyNo << G4endl;
    
    // get global time of hit
    auto hitTime = preStepPoint->GetGlobalTime();

    // Get correct hits collection
    auto ix = -1;
    for (std::size_t i=0;i<fHitsCollection->entries();++i) {
      if ((*fHitsCollection)[i]->GetID()==copyNo) {
        ix = i;
        break;
      }
    }

    if (ix>=0) {
      auto hit = (*fHitsCollection)[ix];

      // if it has, then take the earlier time
      if ( hit->GetTime() > hitTime ) {
        hit->SetTime(hitTime);
      }

      // Add energy
      hit->AddEdep(edep, birkedep, visedep);
    
    } else {
      // if not, create a new hit and set it to the collection
      auto hit = new ScintHit();

      // Get volumtes
      auto physical = touchable->GetVolume();
      auto logical = physical->GetLogicalVolume();

      // set the logical volume
      hit->SetLogV( logical );

      // set material
      G4String type = "";
      G4int dtype = 0;
      
      auto matName = logical->GetMaterial()->GetName();
      if ( matName == "G4_CESIUM_IODIDE" ) {
      	type = "CsI";
      	dtype = 2;
      }
      else if ( matName == "G4_PLASTIC_SC_VINYLTOLUENE" ) {
      	type = "Plastic";
      	dtype = 1;
      }
      else if ( matName == "G4_TERPHENYL" ) {
      	type = "p-Terphenyl";
      	dtype = 1;
      }
      else if ( matName == "GAGG" ) {
      	type = "GAGG";
      	dtype = 2;
      }
      else if ( matName == "PLASTIC" ) {
      	type = "Src";
      	dtype = 3;
      }

      else {
        G4cerr << "---> Type: " << matName << G4endl;
        type = "unknown";
        dtype = 0;
      }
      hit->SetType( type );
      hit->SetDetType( dtype );

      // set the volume id
      hit->SetID( copyNo );

      // set global position
      G4AffineTransform transform = touchable->GetHistory()->GetTopTransform();
      transform.Invert();
      // hit->SetRot(transform.NetRotation());
      hit->SetPos( transform.NetTranslation() );

      // set time
      hit->SetTime(hitTime);

      // Add energy
      hit->AddEdep(edep, birkedep, visedep);

      // insert the hit
      fHitsCollection->insert(hit);
    }
    return true;
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ScintSD::EndOfEvent(G4HCofThisEvent* /*hce*/)
  {}

  //****************************************************************************
  // Method
  //****************************************************************************
  G4double ScintSD::BirksAttenuation(const G4Step* aStep)
  {
    //Example of Birk attenuation law in organic scintillators.
    //adapted from Geant3 PHYS337. See MIN 80 (1970) 239-244
    //
    G4Material* material = aStep->GetTrack()->GetMaterial();
    G4double birk1       = material->GetIonisation()->GetBirksConstant();
    G4double destep      = aStep->GetTotalEnergyDeposit();
    G4double stepl       = aStep->GetStepLength();  
    G4double charge      = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
    //
    G4double response = destep;
    if (birk1*destep*stepl*charge != 0.)
    {
      response = destep/(1. + birk1*destep/stepl);
    }
    return response;
  }

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
}

