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
/// \file DetectorMessenger.cc
/// \brief Definition of the DetectorMessenger class

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  DetectorMessenger::DetectorMessenger( DetectorConstruction* det )
  : fDetectorConstruction(det)
  { 
    fUSERDir = new G4UIdirectory( "/user/" );
    fUSERDir -> SetGuidance( "UI commands specific to this example." );
    
    fDetDir = new G4UIdirectory( "/user/det/" );
    fDetDir -> SetGuidance( "detector control." );
    
    fOverlapCmd = new G4UIcmdWithABool("/user/det/setOverlapChecking",this);  
    fOverlapCmd->SetGuidance("Set overlap checking flag.");
    fOverlapCmd->SetParameterName("flag",false);
    fOverlapCmd->SetDefaultValue(true);
    fOverlapCmd->AvailableForStates(G4State_PreInit);

//     fZenithCmd = new G4UIcmdWithADoubleAndUnit("/user/det/setZenithAngle",this);  
//     fZenithCmd->SetGuidance("Set zenith angle.");
//     fZenithCmd->SetParameterName("zenith",false);
//     fZenithCmd->SetUnitCategory("Angle");
//     fZenithCmd->SetRange("zenith>=0.0 && zenith<=180.");
//     fZenithCmd->SetDefaultValue(0.);
//     fZenithCmd->SetDefaultUnit("degree");
//     fZenithCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
// 
//     fAzimuthCmd = new G4UIcmdWithADoubleAndUnit("/user/det/setAzimuthAngle",this);  
//     fAzimuthCmd->SetGuidance("Set azimuth angle.");
//     fAzimuthCmd->SetParameterName("azimuth",false);
//     fAzimuthCmd->SetUnitCategory("Angle");
//     fAzimuthCmd->SetRange("azimuth>=0.0 && azimuth<=360.");
//     fAzimuthCmd->SetDefaultValue(0.);
//     fAzimuthCmd->SetDefaultUnit("degree");
//     fAzimuthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
// 
//     fPolarizationCmd = new G4UIcmdWithADoubleAndUnit("/user/det/setPolarizationAngle",this);  
//     fPolarizationCmd->SetGuidance("Set poloarization angle.");
//     fPolarizationCmd->SetParameterName("polar",false);
//     fPolarizationCmd->SetUnitCategory("Angle");
//     fPolarizationCmd->SetRange("polar>=0.0 && polar<=360.");
//     fPolarizationCmd->SetDefaultValue(0.);
//     fPolarizationCmd->SetDefaultUnit("degree");
//     fPolarizationCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fUpdateCmd = new G4UIcmdWithoutParameter("/leap/det/update",this);
    fUpdateCmd->SetGuidance("Update geometry.");
    fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
    fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
    fUpdateCmd->AvailableForStates(G4State_Idle);
  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  DetectorMessenger::~DetectorMessenger() {
    delete fUpdateCmd;
//     delete fPolarizationCmd;
//     delete fAzimuthCmd;
//     delete fZenithCmd;
    delete fOverlapCmd;
    delete fDetDir;
    delete fUSERDir;
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void DetectorMessenger::SetNewValue( G4UIcommand* command,G4String newValue) 
  {
//     if( command == fZenithCmd ) 
//       { fDetectorConstruction->SetZenithAngle( fZenithCmd->GetNewDoubleValue(newValue) ); }
// 
//     else if( command == fAzimuthCmd ) 
//       { fDetectorConstruction->SetAzimuthAngle( fAzimuthCmd->GetNewDoubleValue(newValue) ); }
// 
//     else if( command == fPolarizationCmd ) 
//       { fDetectorConstruction->SetPolarizationAngle( fPolarizationCmd->GetNewDoubleValue(newValue) ); }

    if ( command == fUpdateCmd )
      { fDetectorConstruction->UpdateGeometry(); }

    else if ( command == fOverlapCmd )
        { fDetectorConstruction->SetOverlapFlag( fOverlapCmd->GetNewBoolValue(newValue)); }
    }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%