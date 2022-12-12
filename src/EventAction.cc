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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "ScintSD.hh"
#include "ScintHit.hh"
#include "Constants.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace {
  //****************************************************************************
  // Utility function which finds a hit collection with the given Id
  // and print warnings if not found
  //****************************************************************************
  G4VHitsCollection* GetHitCollection(const G4Event* event, G4int hcID ) 
  {
    auto hce = event->GetHCofThisEvent();
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("EventAction::GetHitsCollection()",
                    "Code001", JustWarning, msg);
        return nullptr;
    }
    
    auto hc = hce->GetHC(hcID);
    if ( ! hc) {
      G4ExceptionDescription msg;
      msg << "Cannot access hitsCollection ID " << hcID; 
      G4Exception("EventAction::GetHitsCollection()",
        "Code0001", JustWarning, msg);
    }         

    return hc;
  }    
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  EventAction::EventAction()
  {}

  //****************************************************************************
  // Destructor
  //****************************************************************************
  EventAction::~EventAction()
  {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void EventAction::BeginOfEventAction(const G4Event* /*event*/)
  {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void EventAction::EndOfEventAction(const G4Event* event)
  {  
    
    auto sdManager = G4SDManager::GetSDMpointer();

    // Get hits collections IDs (only once)
    if ( fScintHCID == -1 ) {
      fScintHCID = sdManager->GetCollectionID("leapDet/ScintCollection");
    }

    // Get hits collection
    auto scintHC = GetHitCollection( event, fScintHCID );
    if ( ! scintHC ) return;

    // get number of hits
    auto nHits = scintHC->GetSize();

    // Check if there were any hits in instrument
    if ( nHits > 0 && nHits < kNumKeep ){
      // G4cout << "Scint hits: " << nHits << G4endl;
      // G4cout << "Scat hits:  " << scatHits << G4endl;

      // get analysis manager
      auto analysisManager = G4AnalysisManager::Instance();

      // Fill Ntuple
      auto col = 0; // ntuple column number
      analysisManager->FillNtupleIColumn(col++, event->GetEventID());

      auto primaryE = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy()/keV;
      analysisManager->FillNtupleIColumn(col++, primaryE);

      // Add number of hits
      analysisManager->FillNtupleIColumn(col++, nHits);

      // Data for each element
      auto totalE = 0.;
      for (unsigned long i=0; i<kNumKeep; i++ ) {
        if ( i < nHits ){
          auto hit = static_cast<ScintHit*>(scintHC->GetHit(i));

          analysisManager->FillNtupleIColumn(col++, hit->GetID());        // 1
          analysisManager->FillNtupleDColumn(col++, hit->GetPos().x());   // 2
          analysisManager->FillNtupleDColumn(col++, hit->GetPos().y());   // 3
          analysisManager->FillNtupleDColumn(col++, hit->GetPos().z());   // 4
          analysisManager->FillNtupleDColumn(col++, hit->GetEdep()/keV);  // 5
          analysisManager->FillNtupleDColumn(col++, BroadenEnergy(hit->GetType(),hit->GetEdep()/keV)); // 6
          analysisManager->FillNtupleDColumn(col++, hit->GetBirkEdep()/keV);  // 7
          analysisManager->FillNtupleDColumn(col++, BroadenEnergy(hit->GetType(),hit->GetBirkEdep()/keV)); // 8
          analysisManager->FillNtupleDColumn(col++, hit->GetVisEdep()/keV);  // 9
          analysisManager->FillNtupleDColumn(col++, BroadenEnergy(hit->GetType(),hit->GetVisEdep()/keV)); // 10
          analysisManager->FillNtupleDColumn(col++, hit->GetTime()/ns);   // 11
          analysisManager->FillNtupleSColumn(col++, hit->GetType());      // 12
          analysisManager->FillNtupleIColumn(col++, hit->GetDetType());      // 13

          totalE += hit->GetEdep()/keV;
        } else {
          col += 13;
        }
      }

      analysisManager->FillNtupleDColumn(col++, totalE);


      // Finish event
      analysisManager->AddNtupleRow();  

    }

  }  

  //****************************************************************************
  // Method
  //****************************************************************************
  G4double EventAction::BroadenEnergy(const G4String& type, G4double energy)
  {
    // Expects energy in keV
    //     Updated energy broadening (2016-09-09)
    if ( type == "Plastic" ) {
      // auto sigma = -8.3195 + ( 3.1992 * sqrt( energy ) ); // old GEANT4 sims
      // auto sigma = sqrt( 0.5692 + ( 2.837 * energy ) ); // fit to GRAPE calibration data
      // auto sigma = ( 0.478 / 2.35 ) * sqrt( 60. * energy ); // Peter's old numbers ( 47.8% at 60 keV )
      auto sigma = -1.035 + ( 1.66 * sqrt( energy ) ); // fit to LEAP calibration data
      energy = G4RandGauss::shoot( energy, sigma) ;
    }
    else if ( type == "CsI" ) { 
      // auto sigma = 1.89 + 1.20 * sqrt( energy ); // old GEANT4 sims
      // auto sigma = sqrt( -83.43 + ( 4.88 * energy ) ); // fit to calibration data
      // auto sigma = ( 0.14 / 2.35 ) * sqrt( 662. * energy ); // 14% at 662 keV
      auto sigma = 0.1146 + ( 1.662 * sqrt( energy ) ); // fit to LEAP calibration data
      energy = G4RandGauss::shoot( energy, sigma );
    }
    else if ( type == "GAGG" ) { 
      auto sigma = 1.42 + 0.90 * sqrt( energy ) ;
      energy = G4RandGauss::shoot( energy, sigma );
    }


    return energy;
  }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
