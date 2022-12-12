// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% //
//
//	Polarimeters for Energetic Transients (POET)
//	Created: April 10, 2014 - Camden Ertley
//
//	Edited:
//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% //

// ************************************************************************************ //
//	Included Files
// ************************************************************************************ //
#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "Constants.hh"
#include "ScintSD.hh"

#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"

#include "G4UserLimits.hh"
#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


#include "G4AssemblyVolume.hh"
//#include "G4ThreeVector.hh"
//#include "G4RotationMatrix.hh"

//#include "G4ios.hh"
//#include "globals.hh"


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  DetectorConstruction::DetectorConstruction()
  {
    fDetMessenger = new DetectorMessenger(this);
  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  DetectorConstruction::~DetectorConstruction()
  {
    delete fDetMessenger;
  }  

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  G4VPhysicalVolume* DetectorConstruction::Construct()
  {
    // Define materials 
    DefineMaterials();
    
    // Define volumes
    return DefineVolumes();
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void DetectorConstruction::DefineMaterials()
  { 
    // Materials defined using NIST Manager
    // https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/Appendix/materialNames.html
    auto nistManager = G4NistManager::Instance();

    //======================================================
    // define elements
    //======================================================
    auto isotopes = true;
    G4Element* eH  = nistManager -> FindOrBuildElement( "H" , isotopes ); // 1
    G4Element* eBe = nistManager -> FindOrBuildElement( "Be", isotopes ); // 4
    G4Element* eC  = nistManager -> FindOrBuildElement( "C" , isotopes ); // 6
    G4Element* eN  = nistManager -> FindOrBuildElement( "N" , isotopes ); // 7
    G4Element* eO  = nistManager -> FindOrBuildElement( "O" , isotopes ); // 8
    G4Element* eF  = nistManager -> FindOrBuildElement( "F" , isotopes ); // 9
    G4Element* eMg = nistManager -> FindOrBuildElement( "Mg", isotopes ); // 12
    G4Element* eAl = nistManager -> FindOrBuildElement( "Al", isotopes ); // 13
    G4Element* eSi = nistManager -> FindOrBuildElement( "Si", isotopes ); // 14
    G4Element* eTi = nistManager -> FindOrBuildElement( "Ti", isotopes ); // 22
    G4Element* eCr = nistManager -> FindOrBuildElement( "Cr", isotopes ); // 24
    G4Element* eMn = nistManager -> FindOrBuildElement( "Mn", isotopes ); // 25
    G4Element* eFe = nistManager -> FindOrBuildElement( "Fe", isotopes ); // 26
    G4Element* eCu = nistManager -> FindOrBuildElement( "Cu", isotopes ); // 29
    G4Element* eZn = nistManager -> FindOrBuildElement( "Zn", isotopes ); // 30
//    G4Element* eGa = nistManager -> FindOrBuildElement( "Ga", isotopes ); // 31
    G4Element* eSn = nistManager -> FindOrBuildElement( "Sn", isotopes ); // 50
    // G4Element* eI  = nistManager -> FindOrBuildElement( "I" , isotopes ); // 53
    // G4Element* eCs = nistManager -> FindOrBuildElement( "Cs", isotopes ); // 55
//    G4Element* eGd = nistManager -> FindOrBuildElement( "Gd", isotopes ); // 30
    G4Element* eW = nistManager -> FindOrBuildElement( "W", isotopes ); // 74
    G4Element* ePb = nistManager -> FindOrBuildElement( "Pb", isotopes ); // 82

    //======================================================
    // define materials
    //======================================================
    // Vacuum ( Nist G4_Galactic )
    nistManager -> FindOrBuildMaterial("G4_Galactic");
    nistManager -> FindOrBuildMaterial("G4_AIR");

    // Elements as materials
    nistManager -> FindOrBuildMaterial("G4_Pb");
    nistManager -> FindOrBuildMaterial("G4_W");
    nistManager -> FindOrBuildMaterial("G4_Sn");
    nistManager -> FindOrBuildMaterial("G4_Cu");

    // ALUMINUM 6061
    auto mAl6061 = new G4Material( "Aluminum6061", 2.6989*g/cm3, 9 );
      mAl6061 -> AddElement( eSi,  0.60*perCent );
      mAl6061 -> AddElement( eFe,  0.70*perCent );
      mAl6061 -> AddElement( eCu,  0.30*perCent );
      mAl6061 -> AddElement( eMn,  0.15*perCent );
      mAl6061 -> AddElement( eMg,  1.00*perCent );
      mAl6061 -> AddElement( eCr,  0.20*perCent );
      mAl6061 -> AddElement( eZn,  0.25*perCent );
      mAl6061 -> AddElement( eTi,  0.15*perCent );
      mAl6061 -> AddElement( eAl, 96.65*perCent );

    // PC Baord 80% G10 circuit board, 20% generic electronics
    auto mPC = new G4Material( "PCmaterial", 1.8*g/cm3, 9 );
      mPC -> AddElement( eH ,  3.0*perCent );
      mPC -> AddElement( eC , 17.4*perCent );
      mPC -> AddElement( eO , 39.2*perCent );
      mPC -> AddElement( eAl, 10.0*perCent );
      mPC -> AddElement( eSi, 24.4*perCent );
      mPC -> AddElement( eFe,  1.0*perCent );
      mPC -> AddElement( eCu,  3.0*perCent );
      mPC -> AddElement( eSn,  1.0*perCent );
      mPC -> AddElement( ePb,  1.0*perCent );

    // Delrin
    auto mDelrin = new G4Material( "Delrin", 1.415*g/cm3, 3 );
      mDelrin -> AddElement( eH , 2 );
      mDelrin -> AddElement( eC , 1 );
      mDelrin -> AddElement( eO , 1 );
    
    // Plastic for RA source
    auto mSrc = new G4Material( "PLASTIC", 1.032*g/cm3, 2 );
      mSrc -> AddElement( eH , 10 );
      mSrc -> AddElement( eC , 9 );


    // Connector
    auto mConnector = new G4Material( "ConnectorMaterial", 5.158*g/cm3, 2 );
      mConnector -> AddElement( eCu , 50.*perCent );
      mConnector -> AddMaterial( mDelrin , 50.*perCent );

    // MAPMT Material
    auto mPMT = new G4Material( "PMTmaterial", 0.741*g/cm3, 4 );
      mPMT -> AddElement( eO , 26.63*perCent );
      mPMT -> AddElement( eSi, 23.37*perCent );
      mPMT -> AddElement( eBe, 25.00*perCent );
      mPMT -> AddElement( eCu, 25.00*perCent );

    // Gigahertz Optik ODM98 Optical Diffuse Material
    // http://www.gigahertz-optik.de/476-1-ODM98+Specification.html
    auto mODM = new G4Material( "ODM", 1.5*g/cm3, 2 );
      mODM -> AddElement( eC, 24.0183*perCent );
      mODM -> AddElement( eF, 75.9817*perCent );

    // PLASTIC ( Nist G4_PLASTIC_SC_VINYLTOLUENE ? )
    auto mPlastic = nistManager->FindOrBuildMaterial( "G4_PLASTIC_SC_VINYLTOLUENE" );
      // auto birk = 0.0159*g/(cm2*MeV) / mPlastic->GetDensity();// Craun & Smith NIM 80 (1970)
      mPlastic -> GetIonisation() -> SetBirksConstant(0.154*mm/MeV); // original

    // CESIUM IODIDE ( Nist G4_CESIUM_IODIDE ? )
    auto mCsI = nistManager->FindOrBuildMaterial( "G4_CESIUM_IODIDE" );
      // auto birk = 0.0032*g/(cm2*MeV) / mCsI->GetDensity(); // Tretyak Astroparticl Physics 33 (2010)
      // auto birk = 0.0023*g/(cm2*MeV) / mCsI->GetDensity(); // Tretyak Astroparticl Physics 33 (2010)
      mCsI -> GetIonisation() -> SetBirksConstant(0.006*mm/MeV);
      
      
    // Shield Material
    // ---------------
    //
    // ECOMASS material (W only) is composed of
    // 		PA12/PEBA		4.09% by weight		44.49% by volume
    //		Tungsten (W)	95.91% by weight	55.51% by volume
    //
    //		Total density = 11.0 g/cm^3
    //
    //		Polyether Block Amide (PEBA)
    //		Nylon 12 (PA12) is a nylon polymer with the formula [(C12 H23 N O)n]n.
    //
    //
      
    auto mPEBA = new G4Material( "PEBA", 1.00*g/cm3, 4 );
      mPEBA -> AddElement( eH , 23 );
      mPEBA -> AddElement( eC , 12 );
      mPEBA -> AddElement( eN , 1 );
      mPEBA -> AddElement( eO , 1 );
      
    auto mShield = new G4Material( "ShieldMaterial", 11.0*g/cm3, 2 );
      mShield -> AddElement( eW ,     95.91*perCent );
      mShield -> AddMaterial( mPEBA , 4.09*perCent );
      

//     // STILBENE  ( Nist G4_STILBENE ? )
//     auto mStilbene = nistManager -> FindOrBuildMaterial( "G4_STILBENE" );
//       // auto birk = 0.00955*g/(cm2*MeV) / mStilbene->GetDensity();// Craun & Smith NIM 80 (1970)
//       // auto birk = 0.113*mm/MeV; // Papadopoulos NIM 401
//       mStilbene -> GetIonisation() -> SetBirksConstant(0.098*mm/MeV);
//     
//     // p-TERPHENYL  ( Nist G4_TERPHENYL ? )
//     auto mTerphenyl = nistManager -> FindOrBuildMaterial( "G4_TERPHENYL" );
//       mTerphenyl -> GetIonisation() -> SetBirksConstant(0.098*mm/MeV); // needs updated
//    
//     // GAGG  ( Gd3Al2Ga3O12 )
//     auto mGAGG = new G4Material( "GAGG", 6.67*g/cm3, 4 );
//       mGAGG -> AddElement( eGa,  3 );
//       mGAGG -> AddElement( eAl,  2 );
//       mGAGG -> AddElement( eGd,  3 );
//       mGAGG -> AddElement( eO , 12 );
//       
//       mGAGG -> GetIonisation() -> SetBirksConstant(0.008*mm/MeV); // needs updated
      // https://indico.cern.ch/event/642256/contributions/2958340/attachments/1654921/2648752/CALOR2018_GAGG_Dormenev.pdf

    //------------------------------------------------------
    // Print materials list
    //------------------------------------------------------
    //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  }










  //****************************************************************************
  // Method
  //****************************************************************************
  G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
  {
    //======================================================
    // Cleanup old geometry
    //======================================================
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    //======================================================
    // Materials
    //======================================================
    auto mVacuum = G4Material::GetMaterial("G4_Galactic");
//    auto mVacuum = G4Material::GetMaterial("G4_AIR");
//    auto mPb = G4Material::GetMaterial("G4_Pb");
	
	auto mCu = G4Material::GetMaterial( "G4_Cu" );
	auto mSn = G4Material::GetMaterial( "G4_Sn" );
//	auto mW  = G4Material::GetMaterial( "G4_W" );
// 	auto mPlastic = G4Material::GetMaterial( "Plastic" );
// 	auto mCsI = G4Material::GetMaterial( "CsI" );
	
    auto mAl6061 = G4Material::GetMaterial( "Aluminum6061" );
    auto mPC = G4Material::GetMaterial( "PCmaterial" );
    auto mConnector = G4Material::GetMaterial( "ConnectorMaterial" );
    auto mPMT = G4Material::GetMaterial( "PMTmaterial" );
    auto mODM = G4Material::GetMaterial( "ODM" );

    auto mScintCal = G4Material::GetMaterial("G4_CESIUM_IODIDE");
    auto mScintPla = G4Material::GetMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    auto mRAsrc    = G4Material::GetMaterial("PLASTIC");
    // auto mScintillator = G4Material::GetMaterial("G4_TERPHENYL");
    // auto mScintillator = G4Material::GetMaterial("GAGG");
    
    // auto mPEBA = G4Material::GetMaterial("PEBA");
    auto mECO = G4Material::GetMaterial("ShieldMaterial");
    
    
    
	
	// ==================================================================================== //
	//	Construct Volumes
	// ==================================================================================== //
// 		G4bool pMany = false;
// 		G4int pCopyNo = 0;
// 		G4bool pSurfChk = false;

	// ------------------------------------------------------------------------------------ //
	// World Volume
	// ------------------------------------------------------------------------------------ //
    auto world_X = kWorld_Xsize;
    auto world_Y = kWorld_Ysize;
    auto world_Z = kWorld_Zsize;

    auto world_S = new G4Box(
                  "World_S",            // its name
                  world_X/2,            // its X dimension 
                  world_Y/2,            // its Y dimension 
                  world_Z/2);           // its Z dimension 

    // LOGICAL VOLUME
    auto world_LV = new G4LogicalVolume(
                  world_S,              // its solid
                  mVacuum,                 // its material
                  "World_LV");          // its name

    // PHYSICAL VOLUME
    auto world_PV = new G4PVPlacement(
                  0,                    // no rotation
                  G4ThreeVector(),      // at (0,0,0)
                  world_LV,             // its logical volume
                  "World_PV",           // its name
                  0,                    // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //------------------------------------------------------
    // Instrument
    //------------------------------------------------------
    auto mod_Xpitch = kModule_Xpitch;
    auto mod_Ypitch = kModule_Ypitch;
    
    //----------------------------------
    // Module
    //----------------------------------
    // SOLID VOLUME
    auto mod_X = kModule_Xsize;
    auto mod_Y = kModule_Ysize;
    auto mod_Z = kModule_Zsize;

    auto module_S = new G4Box(
                  "Module_S",           // its name
                  mod_X/2,              // its X dimension 
                  mod_Y/2,              // its Y dimension
                  mod_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto module_LV = new G4LogicalVolume(
                  module_S,             // its solid
                  mVacuum,                 // its material
                  "Module_LV");         // its name

    // PHYSICAL VOLUME
    auto mod1_Xpos = -mod_Xpitch / 2.0 ;
    auto mod1_Ypos =  mod_Ypitch ;
    auto mod1_Zpos = 0.0*mm;
    auto mod1_Pos = G4ThreeVector( mod1_Xpos, mod1_Ypos, mod1_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod1_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module1_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // PHYSICAL VOLUME
    auto mod2_Xpos = mod_Xpitch / 2.0 ;
    auto mod2_Ypos = mod_Ypitch ;
    auto mod2_Zpos = 0.0*mm;
    auto mod2_Pos = G4ThreeVector( mod2_Xpos, mod2_Ypos, mod2_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod2_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module2_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  1,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // PHYSICAL VOLUME
    auto mod3_Xpos = -mod_Xpitch ;
    auto mod3_Ypos = 0.0*mm;
    auto mod3_Zpos = 0.0*mm;
    auto mod3_Pos = G4ThreeVector( mod3_Xpos, mod3_Ypos, mod3_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod3_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module3_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  2,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // PHYSICAL VOLUME
    auto mod4_Xpos = 0.0*mm;
    auto mod4_Ypos = 0.0*mm;
    auto mod4_Zpos = 0.0*mm;
    auto mod4_Pos = G4ThreeVector( mod4_Xpos, mod4_Ypos, mod4_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod4_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module4_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  3,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // PHYSICAL VOLUME
    auto mod5_Xpos = mod_Xpitch ;
    auto mod5_Ypos = 0.0*mm;
    auto mod5_Zpos = 0.0*mm;
    auto mod5_Pos = G4ThreeVector( mod5_Xpos, mod5_Ypos, mod5_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod5_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module5_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  4,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // PHYSICAL VOLUME
    auto mod6_Xpos = -mod_Xpitch / 2.0 ;
    auto mod6_Ypos = -mod_Ypitch ;
    auto mod6_Zpos = 0.0*mm;
    auto mod6_Pos = G4ThreeVector( mod6_Xpos, mod6_Ypos, mod6_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod6_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module6_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  5,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // PHYSICAL VOLUME
    auto mod7_Xpos =  mod_Xpitch / 2.0 ;
    auto mod7_Ypos = -mod_Ypitch ;
    auto mod7_Zpos = 0.0*mm;
    auto mod7_Pos = G4ThreeVector( mod7_Xpos, mod7_Ypos, mod7_Zpos );

    fPhysicalModule = new G4PVPlacement(
                  0,		            // its rotation
                  mod7_Pos,              // its position
                  module_LV,            // its logical volume
                  "Module7_PV",          // its name
                  world_LV,             // its mother  volume
                  false,                // no boolean operation
                  6,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


        
        
        
    //----------------------------------
    // Base Plate
    //----------------------------------
    // Solid Volume
    auto ENCL_Bot_X = kENCL_Bot_Xsize;
    auto ENCL_Bot_Y = kENCL_Bot_Ysize;
    auto ENCL_Bot_Z = kENCL_Bot_Zsize;

    auto ENCL_Bot_S = new G4Box(
                  "ENCL_Bot_S",         // its name
                  ENCL_Bot_X/2,         // its X dimension 
                  ENCL_Bot_Y/2,         // its Y dimension
                  ENCL_Bot_Z/2);        // its Z dimension
    
    // Logical Volume
    auto ENCL_Bot_LV = new G4LogicalVolume(
                  ENCL_Bot_S,           // its solid
                  mAl6061,              // its material
                  "ENCL_Bot_LV");       // its name

    // Pysical Volume
    auto ENCL_Bot_Xpos = 0.0*mm;
    auto ENCL_Bot_Ypos = 0.0*mm;
    auto ENCL_Bot_Zpos = -mod_Z/2 + ENCL_Bot_Z/2;
    auto ENCL_Bot_Pos = G4ThreeVector( ENCL_Bot_Xpos, ENCL_Bot_Ypos, ENCL_Bot_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Bot_Pos,         // its position
                  ENCL_Bot_LV,          // its logical volume
                  "ENCL_Bot_PV",        // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Side1 Plate
    //----------------------------------
    // Solid Volume
    auto ENCL_Side1_X = kENCL_Side1_Xsize;
    auto ENCL_Side1_Y = kENCL_Side1_Ysize;
    auto ENCL_Side1_Z = kENCL_Side1_Zsize;

    auto ENCL_Side1_S = new G4Box(
                  "ENCL_Side1_S",       // its name
                  ENCL_Side1_X/2,       // its X dimension 
                  ENCL_Side1_Y/2,       // its Y dimension
                  ENCL_Side1_Z/2);      // its Z dimension
    
    // Logical Volume
    auto ENCL_Side1_LV = new G4LogicalVolume(
                  ENCL_Side1_S,         // its solid
                  mAl6061,              // its material
                  "ENCL_Side1_LV");     // its name

    // Pysical Volume
    auto ENCL_Side1_Xpos = 0.0*mm;
    auto ENCL_Side1_Ypos = 0.0*mm;
    auto ENCL_Side1_Zpos = ENCL_Bot_Zpos - ENCL_Bot_Z/2 + ENCL_Side1_Z/2;
    auto ENCL_Side1_Pos = G4ThreeVector();

    ENCL_Side1_Xpos = ENCL_Bot_X/2 + ENCL_Side1_X/2;
    ENCL_Side1_Pos = G4ThreeVector( ENCL_Side1_Xpos, ENCL_Side1_Ypos, ENCL_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side1_Pos,       // its position
                  ENCL_Side1_LV,        // its logical volume
                  "ENCL_Side1_PV",      // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    ENCL_Side1_Xpos = -ENCL_Bot_X/2 - ENCL_Side1_X/2;
    ENCL_Side1_Pos = G4ThreeVector( ENCL_Side1_Xpos, ENCL_Side1_Ypos, ENCL_Side1_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side1_Pos,       // its position
                  ENCL_Side1_LV,        // its logical volume
                  "ENCL_Side1_PV",      // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Side2 Plate
    //----------------------------------
    // Solid Volume
    auto ENCL_Side2_X = kENCL_Side2_Xsize;
    auto ENCL_Side2_Y = kENCL_Side2_Ysize;
    auto ENCL_Side2_Z = kENCL_Side2_Zsize;

    auto ENCL_Side2_S = new G4Box(
                  "ENCL_Side2_S",       // its name
                  ENCL_Side2_X/2,       // its X dimension 
                  ENCL_Side2_Y/2,       // its Y dimension
                  ENCL_Side2_Z/2);      // its Z dimension
    
    // Logical Volume
    auto ENCL_Side2_LV = new G4LogicalVolume(
                  ENCL_Side2_S,         // its solid
                  mAl6061,              // its material
                  "ENCL_Side2_LV");     // its name

    // Pysical Volume
    auto ENCL_Side2_Xpos = 0.0*mm;
    auto ENCL_Side2_Ypos = 0.0*mm;
    auto ENCL_Side2_Zpos = ENCL_Bot_Zpos - ENCL_Bot_Z/2 + ENCL_Side2_Z/2;
    auto ENCL_Side2_Pos = G4ThreeVector();

    ENCL_Side2_Ypos = ENCL_Bot_Y/2 + ENCL_Side2_Y/2;
    ENCL_Side2_Pos = G4ThreeVector( ENCL_Side2_Xpos, ENCL_Side2_Ypos, ENCL_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side2_Pos,       // its position
                  ENCL_Side2_LV,        // its logical volume
                  "ENCL_Side2_PV",      // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    ENCL_Side2_Ypos = -ENCL_Bot_Y/2 - ENCL_Side2_Y/2;
    ENCL_Side2_Pos = G4ThreeVector( ENCL_Side2_Xpos, ENCL_Side2_Ypos, ENCL_Side2_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Side2_Pos,       // its position
                  ENCL_Side2_LV,        // its logical volume
                  "ENCL_Side2_PV",      // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Top Plate Edge
    //----------------------------------
    // Solid Volume
    auto ENCL_TopEdge_X = kENCL_TopEdge_Xsize;
    auto ENCL_TopEdge_Y = kENCL_TopEdge_Ysize;
    auto ENCL_TopEdge_Z = kENCL_TopEdge_Zsize;

    G4VSolid* ENCL_TopEdge_S;
    ENCL_TopEdge_S = new G4Box(
                  "ENCL_TopEdge_S",     // its name
                  ENCL_TopEdge_X/2,     // its X dimension 
                  ENCL_TopEdge_Y/2,     // its Y dimension
                  ENCL_TopEdge_Z/2);    // its Z dimension
                          
    // Hole
    auto ENCL_TopEdge_Hole_X = kENCL_TopEdge_Hole_Xsize;
    auto ENCL_TopEdge_Hole_Y = kENCL_TopEdge_Hole_Ysize;
    auto ENCL_TopEdge_Hole_Z = kENCL_TopEdge_Hole_Zsize;

    auto ENCL_TopEdge_Hole_S = new G4Box(
                  "ENCL_TopEdge_Hole_S",     // its name
                  ENCL_TopEdge_Hole_X/2,     // its X dimension
                  ENCL_TopEdge_Hole_Y/2,     // its Y dimension
                  ENCL_TopEdge_Hole_Z/2);    // its Z dimension

    auto ENCL_TopEdge_Hole_pos = G4ThreeVector( 0., 0., 0. );
    ENCL_TopEdge_S = new G4SubtractionSolid( 
                  "ENCL_TopEdge_S",     // its name
                  ENCL_TopEdge_S,       // starting solid
                  ENCL_TopEdge_Hole_S,  // solid to be subtracted
                  0,                    // its rotation
                  ENCL_TopEdge_Hole_pos );   // its position

    // Logical Volume
    auto ENCL_TopEdge_LV = new G4LogicalVolume(
                  ENCL_TopEdge_S,       // its solid
                  mAl6061,              // its material
                  "ENCL_TopEdge_LV");   // its name

    auto ENCL_TopEdge_Xpos = 0.0*mm;
    auto ENCL_TopEdge_Ypos = 0.0*mm;
    auto ENCL_TopEdge_Zpos = ENCL_Side1_Zpos + ENCL_Side1_Z/2 - ENCL_TopEdge_Z/2;
    auto ENCL_TopEdge_Pos = G4ThreeVector( ENCL_TopEdge_Xpos, ENCL_TopEdge_Ypos, ENCL_TopEdge_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_TopEdge_Pos,     // its position
                  ENCL_TopEdge_LV,      // its logical volume
                  "ENCL_TopEdge_PV",    // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 





    //----------------------------------
    // Analog Power Boards
    //----------------------------------
    // Solid Volume
    auto APB_X = kAPB_Xsize;
    auto APB_Y = kAPB_Ysize;
    auto APB_Z = kAPB_Zsize;

    auto APB_S = new G4Box(
                  "APB_S",              // its name
                  APB_X/2,              // its X dimension 
                  APB_Y/2,              // its Y dimension
                  APB_Z/2);             // its Z dimension

    // Logical Volume
    auto APB_LV = new G4LogicalVolume(
                  APB_S,                // its solid
                  mPC,                  // its material
                  "APB_LV");            // its name

//     auto APB_Xnum = kNumScint_X;
//     auto APB_Xpitch = kScint_Xpitch;
//    auto APB_Xoffset = ( kScint_Xpitch * (kNumScint_X-1) / 2 );
    auto APB_Xpos = 0.0*mm;
    auto APB_Ypos = 0.0*mm;
    auto APB_Zpos = ENCL_Bot_Zpos + ENCL_Bot_Z/2 + kAPB_Zoffset + APB_Z/2;
    auto APB_Pos = G4ThreeVector();


   //----------------------------------
    // APB - MIB Connectors
    //----------------------------------
    // Solid Volume
    auto APB_Con_X = kAPB_Con_Xsize;
    auto APB_Con_Y = kAPB_Con_Ysize;
    auto APB_Con_Z = kAPB_Con_Zsize;

    auto APB_Con_S = new G4Box(
                  "APB_Con_S",          // its name
                  APB_Con_X/2,          // its X dimension 
                  APB_Con_Y/2,          // its Y dimension
                  APB_Con_Z/2);         // its Z dimension
                          
    auto APB_Con_LV = new G4LogicalVolume(
                  APB_Con_S,            // its solid
                  mConnector,           // its material
                  "APB_Con_LV");        // its name

//     auto APB_Con_Xnum = APB_Xnum;
//     auto APB_Con_Xpitch = APB_Xpitch;
//     auto APB_Con_Xoffset = ( kScint_Xpitch * (kNumScint_X-1) / 2 ) - APB_X/2 - APB_Con_X/2;
//     auto APB_Con_Xpos = 0.0*mm;
//     auto APB_Con_Ypos = 0.0*mm;
    auto APB_Con_Zpos = APB_Zpos + APB_Z/2 - APB_Con_Z/2;
    auto APB_Con_Pos = G4ThreeVector();



    //----------------------------------
    // Module Interface Board (MIB)
    //----------------------------------
    // Solid Volume
    auto MIB_X = kMIB_Xsize;
    auto MIB_Y = kMIB_Ysize;
    auto MIB_Z = kMIB_Zsize;

    auto MIB_S = new G4Box(
                  "MIB_S",              // its name
                  MIB_X/2,              // its X dimension 
                  MIB_Y/2,              // its Y dimension
                  MIB_Z/2);             // its Z dimension
    
    // Logical Volume     
    auto MIB_LV = new G4LogicalVolume(
                  MIB_S,                // its solid
                  mPC,                  // its material
                  "MIB_LV");            // its name

    auto MIB_Xpos = 0.0*mm;
    auto MIB_Ypos = 0.0*mm;
    auto MIB_Zpos = APB_Con_Zpos + APB_Con_Z/2 + kAPB_MIB_Zoffset + MIB_Z/2;
    auto MIB_Pos = G4ThreeVector( MIB_Xpos, MIB_Ypos, MIB_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIB_Pos,              // its position
                  MIB_LV,               // its logical volume
                  "MIB_PV",             // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
     

    //----------------------------------
    // MIB Plate Edge
    //----------------------------------
    // Solid Volume
    auto MIBP_Edge_X = kMIBP_Edge_Xsize;
    auto MIBP_Edge_Y = kMIBP_Edge_Ysize;
    auto MIBP_Edge_Z = kMIBP_Edge_Zsize;

    G4VSolid* MIBP_Edge_S;
    MIBP_Edge_S = new G4Box(
                  "MIBP_Edge_S",        // its name
                  MIBP_Edge_X/2,        // its X dimension 
                  MIBP_Edge_Y/2,        // its Y dimension
                  MIBP_Edge_Z/2);       // its Z dimension
                          
    // Hole
    auto MIBP_Edge_Hole_X = kMIBP_Edge_Hole_Xsize;
    auto MIBP_Edge_Hole_Y = kMIBP_Edge_Hole_Ysize;
    auto MIBP_Edge_Hole_Z = kMIBP_Edge_Hole_Zsize;

    auto MIBP_Edge_Hole_S = new G4Box(
                  "MIBP_Edge_Hole_S",   // its name
                  MIBP_Edge_Hole_X/2,   // its X dimension
                  MIBP_Edge_Hole_Y/2,   // its Y dimension
                  MIBP_Edge_Hole_Z/2);  // its Z dimension

    auto MIBP_Edge_Hole_pos = G4ThreeVector( 0., 0., 0. );
    MIBP_Edge_S = new G4SubtractionSolid( 
                  "MIBP_Edge_S",        // its name
                  MIBP_Edge_S,          // starting solid
                  MIBP_Edge_Hole_S,     // solid to be subtracted
                  0,                    // its rotation
                  MIBP_Edge_Hole_pos ); // its position

    // Logical Volume
    auto MIBP_Edge_LV = new G4LogicalVolume(
                  MIBP_Edge_S,          // its solid
                  mAl6061,              // its material
                  "MIBP_Edge_LV");      // its name

    auto MIBP_Edge_Xpos = 0.0*mm;
    auto MIBP_Edge_Ypos = 0.0*mm;
    auto MIBP_Edge_Zpos = MIB_Zpos + MIB_Z/2 + kMIBP_Zoffset + MIBP_Edge_Z/2;
    auto MIBP_Edge_Pos = G4ThreeVector( MIBP_Edge_Xpos, MIBP_Edge_Ypos, MIBP_Edge_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Edge_Pos,        // its position
                  MIBP_Edge_LV,         // its logical volume
                  "MIBP_Edge_PV",       // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
                  
                  
                  
                  
    //------------------------------------------//
	// PCB Boards        						//
	// Analog Printed Wiring Board              //
	// Each board is 1.5 mm thick and 120 mm    //
	// tall. The length is dependent in the     //
	// size (order) of the module. For a 7x7    //
	// module, the length is 152 mm.            //
	//------------------------------------------//
	// solid volume
	G4double PCB_X = 240.0*mm;
	G4double PCB_Y = 240.0*mm;
	G4double PCB_Z =   2.5*mm;
	G4VSolid* PCB_SV = new G4Box( "PCB_box", 0.5 * PCB_X, 0.5 * PCB_Y, 0.5 * PCB_Z);

	// logical volume
	G4LogicalVolume* PCB_LV = new G4LogicalVolume( PCB_SV, mPC, "PCB_log", 0, 0, 0 );

	// place physical volumes
	G4double PCB_Xpos = 0.0*mm;
	G4double PCB_Ypos = 0.0*mm;

	G4double PCB1_Zpos = MIB_Zpos - 15.0*mm	;
	G4ThreeVector PCB1_Pos = G4ThreeVector( PCB_Xpos, PCB_Ypos, PCB1_Zpos );
//	ModuleAssembly -> AddPlacedVolume( PCB_log, PCB1_pos, 0 );		

    new G4PVPlacement(
                  0,                    // its rotation
                  PCB1_Pos, 	        // its position
                  PCB_LV,      	    // its logical volume
                  "PCB1_PV",    	    // its name
                  module_LV,        	    // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


	G4double PCB2_Zpos = MIB_Zpos - 30.0*mm	;
	G4ThreeVector PCB2_Pos = G4ThreeVector( PCB_Xpos, PCB_Ypos, PCB2_Zpos );
//	ModuleAssembly -> AddPlacedVolume( PCB_log, PCB2_pos, 0 );		
	
	new G4PVPlacement(
                  0,                    // its rotation
                  PCB2_Pos, 	        // its position
                  PCB_LV,      	    // its logical volume
                  "PCB2_PV",    	    // its name
                  module_LV,        	    // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


	G4double PCB3_Zpos = MIB_Zpos - 45.0*mm	;
	G4ThreeVector PCB3_Pos = G4ThreeVector( PCB_Xpos, PCB_Ypos, PCB3_Zpos );
//	ModuleAssembly -> AddPlacedVolume( PCB_log, PCB3_pos, 0 );
	
	new G4PVPlacement(
                  0,                    // its rotation
                  PCB3_Pos, 	        // its position
                  PCB_LV,      	    // its logical volume
                  "PCB3_PV",    	    // its name
                  module_LV,        	    // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
		

	G4double PCB4_Zpos = MIB_Zpos - 80.0*mm	;
	G4ThreeVector PCB4_Pos = G4ThreeVector( PCB_Xpos, PCB_Ypos, PCB4_Zpos );
//	ModuleAssembly -> AddPlacedVolume( PCB_log, PCB4_pos, 0 );
	
    new G4PVPlacement(
                  0,                    // its rotation
                  PCB4_Pos, 	        // its position
                  PCB_LV,      	    // its logical volume
                  "PCB4_PV",    	    // its name
                  module_LV,        	    // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 
 
 
//------------------------------------------//
// MIB Plate - ECOMASS               		//
//------------------------------------------//
	// solid volume for plate
	G4double MIBplateECO_X = kENCL_Bot_Xsize;
	G4double MIBplateECO_Y = kENCL_Bot_Ysize;
	G4double MIBplateECO_Z = kShieldW_thickness;
	G4VSolid* MIBplateECO_SV = new G4Box( "MIBplateECO_box", 0.5 * MIBplateECO_X, 0.5 * MIBplateECO_Y, 0.5 * MIBplateECO_Z);

//
// 	logical volume
	G4LogicalVolume* MIBplateECO_LV = new G4LogicalVolume( MIBplateECO_SV, mECO, "MIBplateECO_log", 0, 0, 0 );


	G4double MIBplateECO_Xpos = 0.0*mm;
	G4double MIBplateECO_Ypos = 0.0*mm;
	G4double MIBplateECO_Zpos = MIB_Zpos - 60.0*mm;
   
	G4ThreeVector MIBplateECO_Pos;
	MIBplateECO_Pos = G4ThreeVector( MIBplateECO_Xpos, MIBplateECO_Ypos, MIBplateECO_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBplateECO_Pos, 	    // its position
                  MIBplateECO_LV,      	// its logical volume
                  "MIBplateECO",    	    // its name
                  module_LV,        	// its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


//------------------------------------------//
// MIB Plate - Tin (Sn)          		//
//------------------------------------------//
	// solid volume for plate
	G4double MIBplateSn_X = kENCL_Bot_Xsize;
	G4double MIBplateSn_Y = kENCL_Bot_Ysize;
	G4double MIBplateSn_Z = kShieldSn_thickness;
	G4VSolid* MIBplateSn_SV = new G4Box( "MIBplateSn_box", 0.5 * MIBplateSn_X, 0.5 * MIBplateSn_Y, 0.5 * MIBplateSn_Z);

//
// 	logical volume
	G4LogicalVolume* MIBplateSn_LV = new G4LogicalVolume( MIBplateSn_SV, mSn, "MIBplateSn_log", 0, 0, 0 );


	G4double MIBplateSn_Xpos = 0.0*mm;
	G4double MIBplateSn_Ypos = 0.0*mm;
	G4double MIBplateSn_Zpos = MIB_Zpos - 60.0*mm + MIBplateECO_Z/2 + 0.1 + MIBplateSn_Z/2; 
   
	G4ThreeVector MIBplateSn_Pos;
	MIBplateSn_Pos = G4ThreeVector( MIBplateSn_Xpos, MIBplateSn_Ypos, MIBplateSn_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBplateSn_Pos, 	    // its position
                  MIBplateSn_LV,      	// its logical volume
                  "MIBplateSn",    	    // its name
                  module_LV,        	// its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

//------------------------------------------//
// MIB Plate - Copper (Cu)          		//
//------------------------------------------//
	// solid volume for plate
	G4double MIBplateCu_X = kENCL_Bot_Xsize;
	G4double MIBplateCu_Y = kENCL_Bot_Ysize;
	G4double MIBplateCu_Z = kShieldCu_thickness;
	G4VSolid* MIBplateCu_SV = new G4Box( "MIBplateCu_box", 0.5 * MIBplateCu_X, 0.5 * MIBplateCu_Y, 0.5 * MIBplateCu_Z);

//
// 	logical volume
	G4LogicalVolume* MIBplateCu_LV = new G4LogicalVolume( MIBplateCu_SV, mCu, "MIBplateCu_log", 0, 0, 0 );


	G4double MIBplateCu_Xpos = 0.0*mm;
	G4double MIBplateCu_Ypos = 0.0*mm;
	G4double MIBplateCu_Zpos = MIB_Zpos - 60.0*mm + MIBplateECO_Z/2 + 0.1 + MIBplateSn_Z + 0.1 + MIBplateCu_Z/2; 
   
	G4ThreeVector MIBplateCu_Pos;
	MIBplateCu_Pos = G4ThreeVector( MIBplateCu_Xpos, MIBplateCu_Ypos, MIBplateCu_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBplateCu_Pos, 	    // its position
                  MIBplateCu_LV,      	// its logical volume
                  "MIBplateCu",    	    // its name
                  module_LV,        	// its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


 

    //----------------------------------
    // Detector Element
    //----------------------------------
    // SOLID VOLUME
    auto det_X = kDetector_Xsize;
    auto det_Y = kDetector_Ysize;
    auto det_Z = kDetector_Zsize;

    auto detector_S = new G4Box(
                  "Detector_S",         // its name
                  det_X/2,              // its X dimension 
                  det_Y/2,              // its Y dimension
                  det_Z/2);             // its Z dimension

    // LOGICAL VOLUME
    auto detector_cal_LV = new G4LogicalVolume(
                  detector_S,           // its solid
                  mVacuum,                 // its material
                  "Detector_Cal_LV");       // its name

    auto detector_pla_LV = new G4LogicalVolume(
                  detector_S,           // its solid
                  mVacuum,                 // its material
                  "Detector_Pla_LV");       // its name

    auto detector_src_LV = new G4LogicalVolume(
                  detector_S,           // its solid
                  mVacuum,                 // its material
                  "Detector_Src_LV");       // its name


    // PHYSICAL VOLUME
    auto offsetX = ( kScint_Xpitch * (kNumScint_X-1) / 2 );
    auto offsetY = ( kScint_Ypitch * (kNumScint_Y-1) / 2 );
    auto det_Xpos = 0.0*mm;
    auto det_Ypos = 0.0*mm;
    auto det_Zpos = MIB_Zpos + MIB_Z/2 + det_Z/2;
    auto det_Pos = G4ThreeVector( det_Xpos, det_Ypos, det_Zpos );

    // G4cout << G4endl;
    // G4cout << "--> PDE Positions:" << G4endl;
    auto copyNum = 0;
    for (auto col = 0; col<kNumScint_Y; col++) {
      for (auto row = 0; row<kNumScint_X; row++) {
        det_Xpos =  ( col * kScint_Xpitch ) - offsetX;
        det_Ypos = -( row * kScint_Ypitch ) + offsetY;

        det_Pos = G4ThreeVector( det_Xpos, det_Ypos, det_Zpos );

        G4cout << "----> Copy Number: " << copyNum;
        G4cout << " (" << det_Xpos << ", " << det_Ypos << ")" << G4endl;
        G4cout << " (" << abs(det_Xpos) << ", " << abs(det_Ypos) << ")" << G4endl;


        if ( (row == 0) || (row == kNumScint_X-1) ) { // Calorimeter
          new G4PVPlacement(
                  0,                    // its rotation
                  det_Pos,              // its position
                  detector_cal_LV,      // its logical volume
                  "Detector_Cal_PV",        // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;
          G4cout << "calorimeter"  << G4endl;

        }

        else if ( (col == 0) || (col == kNumScint_Y-1) ) { // Calorimeter
          new G4PVPlacement(
                  0,                    // its rotation
                  det_Pos,              // its position
                  detector_cal_LV,      // its logical volume
                  "Detector_Cal_PV",        // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;
          G4cout << "calorimeter" << G4endl;

        }

        else if  ((abs(abs(det_Xpos) - abs(det_Ypos)) <= 0.01) && (row != 1) && (row!=10) && (col!=1) && (col!=10)) { // Calorimeter
          	if ( ((col == 5) && (row == 5)) || ((col == 6) && (row == 6)) ) {
			  new G4PVPlacement(
					  0,                    // its rotation
					  det_Pos,              // its position
					  detector_pla_LV,      // its logical volume
					  "Detector_Pla_PV",        // its name
					  module_LV,            // its mother  volume
					  false,                // no boolean operation
					  copyNum,              // copy number
					  fCheckOverlaps);      // checking overlaps 
			  copyNum++;
			  G4cout << "plastic" << G4endl;
			  }
			  
			else {
			  new G4PVPlacement(
					  0,                    // its rotation
					  det_Pos,              // its position
					  detector_cal_LV,      // its logical volume
					  "Detector_Cal_PV",        // its name
					  module_LV,            // its mother  volume
					  false,                // no boolean operation
					  copyNum,              // copy number
					  fCheckOverlaps);      // checking overlaps 
			  copyNum++;
			  G4cout << "calorimeter" << G4endl;

			}
		}

        else if ( (col == 5) && (row == 2) ) { // Calibration Source
          new G4PVPlacement(
                  0,                    // its rotation
                  det_Pos,              // its position
                  detector_src_LV,      // its logical volume
                  "Detector_Src_PV",        // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;
          G4cout << "calibration source" << G4endl;

        }

        else if ( (col == 6) && (row == 9) ) { // Calibration Source
          new G4PVPlacement(
                  0,                    // its rotation
                  det_Pos,              // its position
                  detector_src_LV,      // its logical volume
                  "Detector_Src_PV",        // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;
          G4cout << "calibration source" << G4endl;

        }

        else { // Plastic
          new G4PVPlacement(
                  0,                    // its rotation
                  det_Pos,              // its position
                  detector_pla_LV,      // its logical volume
                  "Detector_Pla_PV",        // its name
                  module_LV,            // its mother  volume
                  false,                // no boolean operation
                  copyNum,              // copy number
                  fCheckOverlaps);      // checking overlaps 
          copyNum++;
          // G4cout << "plastic" << G4endl;                                                                                                                                                                                                                                                                                                                                                ")" << G4endl;

        }

      }
    }


    //----------------------------------
    // MIB Plate
    //----------------------------------
    // Solid Volume
    auto MIBP_X = kMIBP_Xsize;
    auto MIBP_Y = kMIBP_Ysize;
    auto MIBP_Z = kMIBP_Zsize;

    G4VSolid* MIBP_S;
    MIBP_S = new G4Box(
                  "MIB_Plate_S",        // its name
                  MIBP_X/2,             // its X dimension 
                  MIBP_Y/2,             // its Y dimension
                  MIBP_Z/2);            // its Z dimension
                          
    // Hole
    auto MIBP_Hole_X = kMIBP_Hole_Xsize;
    auto MIBP_Hole_Y = kMIBP_Hole_Ysize;
    auto MIBP_Hole_Z = kMIBP_Hole_Zsize;

    auto MIBP_Hole_S = new G4Box(
                  "MIBP_Hole_S",        // its name
                  MIBP_Hole_X/2,        // its X dimension
                  MIBP_Hole_Y/2,        // its Y dimension
                  MIBP_Hole_Z/2);       // its Z dimension

    auto MIBP_Hole_pos = G4ThreeVector( 0., 0., 0. );
    MIBP_S = new G4SubtractionSolid( 
                  "MIBP_Hole_S",        // its name
                  MIBP_S,               // starting solid
                  MIBP_Hole_S,          // solid to be subtracted
                  0,                    // its rotation
                  MIBP_Hole_pos );      // its position

    // Logical Volume
    auto MIBP_LV = new G4LogicalVolume(
                  MIBP_S,               // its solid
                  mAl6061,              // its material
                  "MIB_Plate_LV");      // its name
    auto MIBP_Xpos = 0.0*mm;
    auto MIBP_Ypos = 0.0*mm;
    auto MIBP_Zpos = -det_Z/2 + kMIBP_Zoffset + MIBP_Z/2;
    auto MIBP_Pos = G4ThreeVector( MIBP_Xpos, MIBP_Ypos, MIBP_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Pos,             // its position
                  MIBP_LV,              // its logical volume
                  "MIB_Plate_PV",       // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Pos,             // its position
                  MIBP_LV,              // its logical volume
                  "MIB_Plate_PV",       // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  MIBP_Pos,             // its position
                  MIBP_LV,              // its logical volume
                  "MIB_Plate_PV",       // its name
                  detector_src_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Scintillator Case
    //----------------------------------
    // Solid Volume
    auto SCINT_Case_X = kScint_Case_Xsize;
    auto SCINT_Case_Y = kScint_Case_Ysize;
    auto SCINT_Case_Z = kScint_Case_Zsize;

    G4VSolid* SCINT_Case_S;
    SCINT_Case_S = new G4Box(
                  "Scint_Case_S",       // its name
                  SCINT_Case_X/2,       // its X dimension
                  SCINT_Case_Y/2,       // its Y dimension
                  SCINT_Case_Z/2);      // its Z dimension


    // Hole
    auto SCINT_Case_Hole_X = kScint_Xsize;
    auto SCINT_Case_Hole_Y = kScint_Ysize;
    auto SCINT_Case_Hole_Z = 2*kScint_Zsize;

    auto SCINT_Case_Hole_S = new G4Box(
                  "SCINT_Case_Hole_S",  // its name
                  SCINT_Case_Hole_X/2,  // its X dimension
                  SCINT_Case_Hole_Y/2,  // its Y dimension
                  SCINT_Case_Hole_Z/2); // its Z dimension

    auto SCINT_Case_Hole_pos = G4ThreeVector( 0., 0., 0. );
    SCINT_Case_S = new G4SubtractionSolid( 
                  "SCINT_Case_Hole_S",  // its name
                  SCINT_Case_S,         // starting solid
                  SCINT_Case_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  SCINT_Case_Hole_pos );// its position

    // Logical Volume
    auto SCINT_Case_LV = new G4LogicalVolume(
                  SCINT_Case_S,         // its solid
                  mODM,                 // its material
                  "Scint_Case_LV");     // its name

    // Physical Volume
    auto SCINT_Case_Xpos = 0.0*mm;
    auto SCINT_Case_Ypos = 0.0*mm;
    auto SCINT_Case_Zpos = MIBP_Zpos + MIBP_Z/2 + SCINT_Case_Z/2;
    auto SCINT_Case_Pos = G4ThreeVector( SCINT_Case_Xpos, SCINT_Case_Ypos, SCINT_Case_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Pos,       // its position
                  SCINT_Case_LV,        // its logical volume
                  "Scint_Case_PV",      // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Pos,       // its position
                  SCINT_Case_LV,        // its logical volume
                  "Scint_Case_PV",      // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Pos,       // its position
                  SCINT_Case_LV,        // its logical volume
                  "Scint_Case_PV",      // its name
                  detector_src_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Scintillator Case Bot
    //----------------------------------
    // Solid Volume
    auto SCINT_Case_Bot_X = kScint_Case_Bot_Xsize;
    auto SCINT_Case_Bot_Y = kScint_Case_Bot_Ysize;
    auto SCINT_Case_Bot_Z = kScint_Case_Bot_Zsize;

    G4VSolid* SCINT_Case_Bot_S;
    SCINT_Case_Bot_S = new G4Box(
                  "Scint_Case_Bot_S",   // its name
                  SCINT_Case_Bot_X/2,   // its X dimension
                  SCINT_Case_Bot_Y/2,   // its Y dimension
                  SCINT_Case_Bot_Z/2);  // its Z dimension

    auto SCINT_Case_Bot_Hole_Zpos = -SCINT_Case_Bot_Z/2 + kScint_Case_Thickness/2 + SCINT_Case_Hole_Z/2;
    auto SCINT_Case_Bot_Hole_pos = G4ThreeVector( 0., 0., SCINT_Case_Bot_Hole_Zpos );
    SCINT_Case_Bot_S = new G4SubtractionSolid( 
                  "Scint_Case_Bot_S",   // its name
                  SCINT_Case_Bot_S,     // starting solid
                  SCINT_Case_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  SCINT_Case_Bot_Hole_pos );  // its position

    // Logical Volume
    auto SCINT_Case_Bot_LV = new G4LogicalVolume(
                  SCINT_Case_Bot_S,     // its solid
                  mODM,                 // its material
                  "Scint_Case_Bot_LV"); // its name

    // Physical Volume
    auto SCINT_Case_Bot_Xpos = 0.0*mm;
    auto SCINT_Case_Bot_Ypos = 0.0*mm;
    auto SCINT_Case_Bot_Zpos = SCINT_Case_Zpos - SCINT_Case_Z/2 - SCINT_Case_Bot_Z/2;
    auto SCINT_Case_Bot_Pos = G4ThreeVector( SCINT_Case_Bot_Xpos, SCINT_Case_Bot_Ypos,SCINT_Case_Bot_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Bot_Pos,   // its position
                  SCINT_Case_Bot_LV,    // its logical volume
                  "Scint_Case_Bot_PV",  // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Bot_Pos,   // its position
                  SCINT_Case_Bot_LV,    // its logical volume
                  "Scint_Case_Bot_PV",  // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Bot_Pos,   // its position
                  SCINT_Case_Bot_LV,    // its logical volume
                  "Scint_Case_Bot_PV",  // its name
                  detector_src_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Scintillator Case Top
    //----------------------------------
    // Solid Volume
    auto SCINT_Case_Top_X = kScint_Case_Top_Xsize;
    auto SCINT_Case_Top_Y = kScint_Case_Top_Ysize;
    auto SCINT_Case_Top_Z = kScint_Case_Top_Zsize;

    G4VSolid* SCINT_Case_Top_S;
    SCINT_Case_Top_S = new G4Box(
                  "Scint_Case_Top_S",   // its name
                  SCINT_Case_Top_X/2,   // its X dimension
                  SCINT_Case_Top_Y/2,   // its Y dimension
                  SCINT_Case_Top_Z/2);  // its Z dimension

    auto SCINT_Case_Top_Hole_Zpos = SCINT_Case_Top_Z/2 - kScint_Case_Thickness - SCINT_Case_Hole_Z/2;
    auto SCINT_Case_Top_Hole_pos = G4ThreeVector( 0., 0., SCINT_Case_Top_Hole_Zpos );
    SCINT_Case_Top_S = new G4SubtractionSolid( 
                  "Scint_Case_Top_S",   // its name
                  SCINT_Case_Top_S,     // starting solid
                  SCINT_Case_Hole_S,    // solid to be subtracted
                  0,                    // its rotation
                  SCINT_Case_Top_Hole_pos );  // its position

    // Logical Volume
    auto SCINT_Case_Top_LV = new G4LogicalVolume(
                  SCINT_Case_Top_S,     // its solid
                  mODM,                 // its material
                  "Scint_Case_Top_LV"); // its name

    // Physical Volume
    auto SCINT_Case_Top_Xpos = 0.0*mm;
    auto SCINT_Case_Top_Ypos = 0.0*mm;
    auto SCINT_Case_Top_Zpos = SCINT_Case_Zpos + SCINT_Case_Z/2 + SCINT_Case_Top_Z/2;
    auto SCINT_Case_Top_Pos = G4ThreeVector( SCINT_Case_Top_Xpos, SCINT_Case_Top_Ypos,SCINT_Case_Top_Zpos );
   
    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Top_Pos,   // its position
                  SCINT_Case_Top_LV,    // its logical volume
                  "Scint_Case_Top_PV",  // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Top_Pos,   // its position
                  SCINT_Case_Top_LV,    // its logical volume
                  "Scint_Case_Top_PV",  // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  SCINT_Case_Top_Pos,   // its position
                  SCINT_Case_Top_LV,    // its logical volume
                  "Scint_Case_Top_PV",  // its name
                  detector_src_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // Enclosure Top/Support Frame
    //----------------------------------
    // Solid Volume
    auto ENCL_Top_X = kENCL_Top_Xsize;
    auto ENCL_Top_Y = kENCL_Top_Ysize;
    auto ENCL_Top_Z = kENCL_Top_Zsize;

    G4VSolid* ENCL_Top_S;
    ENCL_Top_S = new G4Box(
                  "ENCL_Top_S",         // its name
                  ENCL_Top_X/2,         // its X dimension
                  ENCL_Top_Y/2,         // its Y dimension
                  ENCL_Top_Z/2);        // its Z dimension

    // Holes
    auto ENCL_Top_Hole_X = kENCL_Top_Hole_Xsize;
    auto ENCL_Top_Hole_Y = kENCL_Top_Hole_Ysize;
    auto ENCL_Top_Hole_Z = kENCL_Top_Hole_Zsize;

    auto ENCL_Top_Hole_S = new G4Box(
                  "ENCL_Top_Hole_S",    // its name
                  ENCL_Top_Hole_X/2,    // its X dimension
                  ENCL_Top_Hole_Y/2,    // its Y dimension
                  ENCL_Top_Hole_Z/2);   // its Z dimension

    auto ENCL_Top_Hole_pos = G4ThreeVector( 0., 0., 0. );
    ENCL_Top_S = new G4SubtractionSolid( 
                  "ENCL_Top_S",         // its name
                  ENCL_Top_S,           // starting solid
                  ENCL_Top_Hole_S,      // solid to be subtracted
                  0,                    // its rotation
                  ENCL_Top_Hole_pos );  // its position

    // Logical Volume
    auto ENCL_Top_LV = new G4LogicalVolume(
                  ENCL_Top_S,           // its solid
                  mAl6061,              // its material
                  "ENCL_Top_LV");       // its name

    // Physical Volume
    auto ENCL_Top_Xpos = 0.0*mm;
    auto ENCL_Top_Ypos = 0.0*mm;
    auto ENCL_Top_Zpos = SCINT_Case_Zpos + SCINT_Case_Z/2 + kENCL_Top_Zoffset + ENCL_Top_Z/2;
    auto ENCL_Top_Pos = G4ThreeVector( ENCL_Top_Xpos, ENCL_Top_Ypos, ENCL_Top_Zpos );
    
    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Top_Pos,         // its position
                  ENCL_Top_LV,          // its logical volume
                  "ENCL_Top_PV",        // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Top_Pos,         // its position
                  ENCL_Top_LV,          // its logical volume
                  "ENCL_Top_PV",        // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  ENCL_Top_Pos,         // its position
                  ENCL_Top_LV,          // its logical volume
                  "ENCL_Top_PV",        // its name
                  detector_src_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // Scintillator
    //----------------------------------
    // SOLID VOLUME
    auto scint_X = kScint_Xsize;
    auto scint_Y = kScint_Ysize;
    auto scint_Z = kScint_Zsize;

    G4VSolid* scint_S;
    scint_S = new G4Box(
                  "Scint_S",            // its name
                  scint_X/2,            // its X dimension
                  scint_Y/2,            // its Y dimension
                  scint_Z/2);           // its Z dimension

    // Taper
    // auto scint_Taper_Z = kScint_Zsize;
    // auto scint_Taper_Rmin1 = 0.0*mm;
    // auto scint_Taper_Rmax1 = 1.2 * scint_Taper_Z * std::tan( kScint_Taper_Angle );
    // auto scint_Taper_Rmin2 = scint_Taper_Z * std::tan( kScint_Taper_Angle );
    // auto scint_Taper_Rmax2 = scint_Taper_Rmax1;

    // auto scint_Taper_S = new G4Cons(
    //                "Scint_Taper_S",     // its name
    //                scint_Taper_Rmin1,   // its minimum radius -pDz
    //                scint_Taper_Rmax1,   // its maximum radius -pDz
    //                scint_Taper_Rmin2,   // its minimum radius +pDz
    //                scint_Taper_Rmax2,   // its maximum radius +pDz
    //                scint_Taper_Z/2,     // its Z dimension
    //                0.*deg, 
    //                360.*deg);
   
    // auto scint_Taper_Xpos = 0.0*mm;
    // auto scint_Taper_Ypos = 0.0*mm;
    // auto scint_Taper_Zpos = -scint_Z/2 + scint_Taper_Z/2 - ( kScint_Taper_Radius / std::tan( kScint_Taper_Angle ));
    // auto scint_Taper_Pos = G4ThreeVector( scint_Taper_Xpos, scint_Taper_Ypos, scint_Taper_Zpos );

    // scint_S = new G4SubtractionSolid( 
    //                "Scint_S", 
    //                scint_S, 
    //                scint_Taper_S, 
    //                0, 
    //                scint_Taper_Pos );

    // LOGICAL VOLUME
    auto cal_LV = new G4LogicalVolume(
                  scint_S,              // its solid
                  mScintCal,            // its material
                  "Cal_LV");            // its name

    auto pla_LV = new G4LogicalVolume(
                  scint_S,              // its solid
                  mScintPla,            // its material
                  "Pla_LV");            // its name

    // PHYSICAL VOLUME
    auto scint_Xpos = 0.0*mm;
    auto scint_Ypos = 0.0*mm;
    auto scint_Zpos = SCINT_Case_Top_Zpos + SCINT_Case_Top_Z/2 - kScint_Case_Thickness - scint_Z/2;
    auto scint_Pos = G4ThreeVector( scint_Xpos, scint_Ypos, scint_Zpos );


    new G4PVPlacement(
                  0,                    // its rotation
                  scint_Pos,            // its position
                  cal_LV,               // its logical volume
                  "Cal_PV",             // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  scint_Pos,            // its position
                  pla_LV,               // its logical volume
                  "Pla_PV",             // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // Scintillator
    //----------------------------------
    // SOLID VOLUME
    auto SrcScint_radius = 4.0*mm;
    auto SrcScint_height = 10.0*mm;

    G4VSolid* SrcScint_S;
    SrcScint_S = new G4Tubs(
                  "SrcScint_S",         // its name
                  0.0,            		// its Rmin
                  SrcScint_radius,      // its Rmax
                  SrcScint_height/2,	// its height
                  0.*deg,				// its starting segment angle
                  360.*deg);   			// its ending segment angle

    // LOGICAL VOLUME

    auto src_LV = new G4LogicalVolume(
                  SrcScint_S,              // its solid
                  mRAsrc,            // its material
                  "Src_LV");            // its name

    // PHYSICAL VOLUME
    auto SrcScint_Xpos = 0.0*mm;
    auto SrcScint_Ypos = 0.0*mm;
    auto SrcScint_Zpos = SCINT_Case_Top_Zpos + SCINT_Case_Top_Z/2 - kScint_Case_Thickness - scint_Z + SrcScint_height/2;
    auto SrcScint_Pos = G4ThreeVector( SrcScint_Xpos, SrcScint_Ypos, SrcScint_Zpos );


    new G4PVPlacement(
                  0,                    // its rotation
                  SrcScint_Pos,            // its position
                  src_LV,               // its logical volume
                  "Src_PV",             // its name
                  detector_src_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



    //----------------------------------
    // PMT Cap (Conical Reflector)
    //----------------------------------
    // Solid Volume
    auto PMT_Cap_X = kPMT_Cap_Xsize;
    auto PMT_Cap_Y = kPMT_Cap_Ysize;
    auto PMT_Cap_Z = kPMT_Cap_Zsize;

    G4VSolid* PMT_Cap_S;
    PMT_Cap_S = new G4Box(
                  "PMT_Cap_S",          // its name
                  PMT_Cap_X/2,          // its X dimension 
                  PMT_Cap_Y/2,          // its Y dimension
                  PMT_Cap_Z/2);         // its Z dimension
    
    // Hole            
    auto PMT_Cap_Hole_Rmin = kPMT_Cap_Hole_Rmin;
    auto PMT_Cap_Hole_Rmax = kPMT_Cap_Hole_Rmax;
    auto PMT_Cap_Hole_Z    = kPMT_Cap_Hole_Zsize;

    auto PMT_Cap_Hole_S = new G4Tubs(
                  "PMT_Cap_Hole_S",     // its name
                  PMT_Cap_Hole_Rmin,    // its minimum radius 
                  PMT_Cap_Hole_Rmax,    // its maximum radius
                  PMT_Cap_Hole_Z/2,     // its Z dimension
                  0.*deg,               // its starting segment angle
                  360.*deg);            // its ending segment angle
                          
    auto PMT_Cap_Hole_Pos = G4ThreeVector( 0., 0., 0. );
    PMT_Cap_S = new G4SubtractionSolid( 
                  "PMT_Cap_S", 
                  PMT_Cap_S, 
                  PMT_Cap_Hole_S, 
                  0, 
                  PMT_Cap_Hole_Pos );

    // Logical Volume
    auto PMT_Cap_LV = new G4LogicalVolume(
                  PMT_Cap_S,            // its solid
                  mODM,                 // its material
                  "PMT_Cap_LV");        // its name

    // Physical Volume
    auto PMT_Cap_Xpos = 0.0*mm;
    auto PMT_Cap_Ypos = 0.0*mm;
    auto PMT_Cap_Zpos = scint_Zpos - scint_Z/2 - PMT_Cap_Z/2;
    auto PMT_Cap_Pos = G4ThreeVector( PMT_Cap_Xpos, PMT_Cap_Ypos, PMT_Cap_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_Cap_Pos,          // its position
                  PMT_Cap_LV,           // its logical volume
                  "PMT_Cap_PV",         // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_Cap_Pos,          // its position
                  PMT_Cap_LV,           // its logical volume
                  "PMT_Cap_PV",         // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    //----------------------------------
    // PMT
    //----------------------------------
    // Solid Volume
    auto PMT_Rmin = kPMT_Rmin;
    auto PMT_Rmax = kPMT_Rmax;
    auto PMT_Z    = kPMT_Zsize;

    auto PMT_S = new G4Tubs(
                  "PMT_S",              // its name
                  PMT_Rmin,             // its minimum radius 
                  PMT_Rmax,             // its maximum radius
                  PMT_Z/2,              // its Z dimension
                  0.*deg,               // its starting segment angle
                  360.*deg);            // its ending segment angle
                          
    // Logical Volume
    auto PMT_LV = new G4LogicalVolume(
                  PMT_S,                // its solid
                  mPMT,                 // its material
                  "PMT_LV");            // its name

    // Physical Volume
    auto PMT_Xpos = 0.0*mm;
    auto PMT_Ypos = 0.0*mm;
    auto PMT_Zpos = scint_Zpos - scint_Z/2 - kPMT_Zoffset - PMT_Z/2;
    auto PMT_Pos = G4ThreeVector( PMT_Xpos, PMT_Ypos, PMT_Zpos );
    
    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_Pos,              // its position
                  PMT_LV,               // its logical volume
                  "PMT_PV",             // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_Pos,              // its position
                  PMT_LV,               // its logical volume
                  "PMT_PV",             // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 


    //----------------------------------
    // PMT PCB
    //----------------------------------
    // Solid Volume
    auto PMT_PCB_X = kPMT_PCB_Xsize;
    auto PMT_PCB_Y = kPMT_PCB_Ysize;
    auto PMT_PCB_Z = kPMT_PCB_Zsize;

    auto PMT_PCB_S = new G4Box(
                  "PMT_PCB_S",          // its name
                  PMT_PCB_X/2,          // its X dimension 
                  PMT_PCB_Y/2,          // its Y dimension
                  PMT_PCB_Z/2);         // its Z dimension
                          
    // Logical Volume
    auto PMT_PCB_LV = new G4LogicalVolume(
                  PMT_PCB_S,            // its solid
                  mPC,                  // its material
                  "PMT_PCB_LV");        // its name

    // Physical Volume
    auto PMT_PCB_Xpos = 0.0*mm;
    auto PMT_PCB_Ypos = 0.0*mm;
    auto PMT_PCB_Zpos = 0.0*mm;
    auto PMT_PCB_Pos = G4ThreeVector();

    // Top
    PMT_PCB_Zpos = PMT_Zpos - PMT_Z/2 - kPMT_PCB_Gap - PMT_PCB_Z/2;
    PMT_PCB_Pos = G4ThreeVector( PMT_PCB_Xpos, PMT_PCB_Ypos, PMT_PCB_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_PCB_Pos,          // its position
                  PMT_PCB_LV,           // its logical volume
                  "PMT_PCB_PV",         // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_PCB_Pos,          // its position
                  PMT_PCB_LV,           // its logical volume
                  "PMT_PCB_PV",         // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    // Bottom
    PMT_PCB_Zpos += -PMT_PCB_Z/2 - kPCB_Gap - PMT_PCB_Z/2;
    PMT_PCB_Pos = G4ThreeVector( PMT_PCB_Xpos, PMT_PCB_Ypos, PMT_PCB_Zpos );

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_PCB_Pos,          // its position
                  PMT_PCB_LV,           // its logical volume
                  "PMT_PCB_PV",         // its name
                  detector_cal_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 

    new G4PVPlacement(
                  0,                    // its rotation
                  PMT_PCB_Pos,          // its position
                  PMT_PCB_LV,           // its logical volume
                  "PMT_PCB_PV",         // its name
                  detector_pla_LV,      // its mother  volume
                  false,                // no boolean operation
                  0,                    // copy number
                  fCheckOverlaps);      // checking overlaps 



	// ---------------------------------------------------//
	// PASSIVE SHIELD ASSEMBLY                            //
	// Shield Parameters         						  //
	//                                                    //
	// ISHT - InnerShieldHousingThickness (mm)            //
	// OSHT - OuterShieldHousingThickness (mm)            //
	// SnST - SnShieldThickness (mm)                      //
	// WST - PbShieldThickness (mm)                      //
	// ---------------------------------------------------//

		G4double CuST = kShieldCu_thickness;
		G4double SnST = kShieldSn_thickness;
		G4double WST  = kShieldW_thickness;
//		auto TotalST = CuST + 0.1 + SnST + 0.1 + WST;
		auto Shield_Top = det_Zpos + kDetector_Zsize/2 ;
		auto Shield_Bot = MIBplateECO_Zpos - MIBplateECO_Z/2 ;
		auto ShieldHeight = Shield_Top - Shield_Bot ; 
		auto Shield_Zpos = Shield_Bot + ShieldHeight/2 ;



	// ---------------------------------------------------//
	// PASSIVE SHIELD ASSEMBLY - SHIELD A                 //
	// Aluminum         						          //
	// ---------------------------------------------------//

	// SHIELD - TYPE A 


	// SHIELD - TYPE A - Cu SHIELD

	// 	solid volume

		G4double ShieldA_CuShield_Xmin = -mod_Xpitch - CuST ;
		G4double ShieldA_CuShield_Xmax =  mod_Xpitch + CuST ;
		G4double ShieldA_CuShield_dX   = ShieldA_CuShield_Xmax - ShieldA_CuShield_Xmin ;
		G4double ShieldA_CuShield_Xloc = ShieldA_CuShield_Xmin + 0.5*ShieldA_CuShield_dX;
	
		G4double ShieldA_CuShield_Yloc = 1.5*mod_Ypitch + 0.5*CuST;

		G4double  ShieldA_CuShield_dY = CuST;
		G4double  ShieldA_CuShield_dZ = ShieldHeight;
		G4VSolid* ShieldA_CuShield_sol = new G4Box( "ShieldA_CuShield_box", 0.5 * ShieldA_CuShield_dX, 0.5 * ShieldA_CuShield_dY, 0.5 * ShieldA_CuShield_dZ);


	//  logical volume
		G4LogicalVolume* ShieldA_CuShield_log = new G4LogicalVolume( ShieldA_CuShield_sol, mCu, "ShieldA_CuShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldA1_CuShield_pos = G4ThreeVector( ShieldA_CuShield_Xloc,      ShieldA_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldA2_CuShield_pos = G4ThreeVector( ShieldA_CuShield_Xloc, -1.0*ShieldA_CuShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldA1_CuShield_pos, ShieldA_CuShield_log, "ShieldA1_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldA2_CuShield_pos, ShieldA_CuShield_log, "ShieldA2_CuShield", world_LV, false, 0, fCheckOverlaps );




	// SHIELD - TYPE A - Sn SHIELD

	// 	solid volume

		G4double ShieldA_SnShield_Xmin = -mod_Xpitch - CuST - 0.1 - SnST ;
		G4double ShieldA_SnShield_Xmax =  mod_Xpitch + CuST + 0.1 + SnST;
		G4double ShieldA_SnShield_dX   = ShieldA_SnShield_Xmax - ShieldA_SnShield_Xmin ;
		G4double ShieldA_SnShield_Xloc = ShieldA_SnShield_Xmin + 0.5*ShieldA_SnShield_dX;
	
		G4double ShieldA_SnShield_Yloc = 1.5*mod_Ypitch + CuST + 0.1 + 0.5*SnST;

		G4double  ShieldA_SnShield_dY = SnST;
		G4double  ShieldA_SnShield_dZ = ShieldHeight;
		G4VSolid* ShieldA_SnShield_sol = new G4Box( "ShieldA_SnShield_box", 0.5 * ShieldA_SnShield_dX, 0.5 * ShieldA_SnShield_dY, 0.5 * ShieldA_SnShield_dZ);


	//  logical volume
		G4LogicalVolume* ShieldA_SnShield_log = new G4LogicalVolume( ShieldA_SnShield_sol, mSn, "ShieldA_SnShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldA1_SnShield_pos = G4ThreeVector( ShieldA_SnShield_Xloc,      ShieldA_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldA2_SnShield_pos = G4ThreeVector( ShieldA_SnShield_Xloc, -1.0*ShieldA_SnShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldA1_SnShield_pos, ShieldA_SnShield_log, "ShieldA1_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldA2_SnShield_pos, ShieldA_SnShield_log, "ShieldA2_SnShield", world_LV, false, 0, fCheckOverlaps );


	// SHIELD - TYPE A - W SHIELD

	// 	solid volume
		G4double ShieldA_ECOShield_Xmin = -mod_Xpitch - CuST - 0.1 - SnST - 0.1 - WST ;
		G4double ShieldA_ECOShield_Xmax =  mod_Xpitch + CuST + 0.1 + SnST + 0.1 + WST ;
		G4double ShieldA_ECOShield_dX   = ShieldA_ECOShield_Xmax - ShieldA_ECOShield_Xmin ;
		G4double ShieldA_ECOShield_Xloc = ShieldA_ECOShield_Xmin + 0.5*ShieldA_ECOShield_dX;
	
		G4double ShieldA_ECOShield_Yloc = 1.5*mod_Ypitch + CuST + 0.1 + SnST + 0.1 + 0.5*WST;

		G4double  ShieldA_ECOShield_dY = WST;
		G4double  ShieldA_ECOShield_dZ = ShieldHeight;
		G4VSolid* ShieldA_ECOShield_sol = new G4Box( "ShieldA_ECOShield_box", 0.5 * ShieldA_ECOShield_dX, 0.5 * ShieldA_ECOShield_dY, 0.5 * ShieldA_ECOShield_dZ);


	//  logical volume
		G4LogicalVolume* ShieldA_ECOShield_log = new G4LogicalVolume( ShieldA_ECOShield_sol, mSn, "ShieldA_ECOShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldA1_ECOShield_pos = G4ThreeVector( ShieldA_ECOShield_Xloc,      ShieldA_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldA2_ECOShield_pos = G4ThreeVector( ShieldA_ECOShield_Xloc, -1.0*ShieldA_ECOShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldA1_ECOShield_pos, ShieldA_ECOShield_log, "ShieldA1_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldA2_ECOShield_pos, ShieldA_ECOShield_log, "ShieldA2_ECOShield", world_LV, false, 0, fCheckOverlaps );


	// ---------------------------------------------------//
	// PASSIVE SHIELD ASSEMBLY - SHIELD B                 //
	// Aluminum         						          //
	// ---------------------------------------------------//


	// SHIELD - TYPE B 


	// SHIELD - TYPE B - Cu SHIELD

	// 	solid volume

		G4double ShieldB_CuShield_Ymin = mod_Ypitch / 2.0 ;
		G4double ShieldB_CuShield_Ymax = 1.5* mod_Ypitch - 0.1 ;
		G4double ShieldB_CuShield_dY   = ShieldB_CuShield_Ymax - ShieldB_CuShield_Ymin ;
		G4double ShieldB_CuShield_Yloc = ShieldB_CuShield_Ymin + 0.5*ShieldB_CuShield_dY;
	
		G4double ShieldB_CuShield_Xloc = mod_Xpitch + 0.5*CuST;
	
		G4double  ShieldB_CuShield_dX = CuST;
		G4double  ShieldB_CuShield_dZ = ShieldHeight;
		G4VSolid* ShieldB_CuShield_sol = new G4Box( "ShieldB_CuShield_box", 0.5 * ShieldB_CuShield_dX, 0.5 * ShieldB_CuShield_dY, 0.5 * ShieldB_CuShield_dZ);

	//  logical volume
		G4LogicalVolume* ShieldB_CuShield_log = new G4LogicalVolume( ShieldB_CuShield_sol, mCu, "ShieldB_CuShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
	
		G4ThreeVector ShieldB1_CuShield_pos = G4ThreeVector( -1.0*ShieldB_CuShield_Xloc,      ShieldB_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB2_CuShield_pos = G4ThreeVector(      ShieldB_CuShield_Xloc,      ShieldB_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB3_CuShield_pos = G4ThreeVector( -1.0*ShieldB_CuShield_Xloc, -1.0*ShieldB_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB4_CuShield_pos = G4ThreeVector(      ShieldB_CuShield_Xloc, -1.0*ShieldB_CuShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldB1_CuShield_pos, ShieldB_CuShield_log, "ShieldB1_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB2_CuShield_pos, ShieldB_CuShield_log, "ShieldB2_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB3_CuShield_pos, ShieldB_CuShield_log, "ShieldB3_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB4_CuShield_pos, ShieldB_CuShield_log, "ShieldB4_CuShield", world_LV, false, 0, fCheckOverlaps );



	// SHIELD - TYPE B - Sn SHIELD

	// 	solid volume

		G4double ShieldB_SnShield_Ymin = mod_Ypitch / 2.0 + CuST + 0.1 ;
		G4double ShieldB_SnShield_Ymax = 1.5* mod_Ypitch  + CuST  ;
		G4double ShieldB_SnShield_dY   = ShieldB_SnShield_Ymax - ShieldB_SnShield_Ymin ;
		G4double ShieldB_SnShield_Yloc = ShieldB_SnShield_Ymin + 0.5*ShieldB_SnShield_dY;
	
		G4double ShieldB_SnShield_Xloc = mod_Xpitch + CuST + 0.1 + 0.5*SnST;
	
		G4double  ShieldB_SnShield_dX = SnST;
		G4double  ShieldB_SnShield_dZ = ShieldHeight;
		G4VSolid* ShieldB_SnShield_sol = new G4Box( "ShieldB_SnShield_box", 0.5 * ShieldB_SnShield_dX, 0.5 * ShieldB_SnShield_dY, 0.5 * ShieldB_SnShield_dZ);

	//  logical volume
		G4LogicalVolume* ShieldB_SnShield_log = new G4LogicalVolume( ShieldB_SnShield_sol, mSn, "ShieldB_SnShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
	
		G4ThreeVector ShieldB1_SnShield_pos = G4ThreeVector( -1.0*ShieldB_SnShield_Xloc,      ShieldB_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB2_SnShield_pos = G4ThreeVector(      ShieldB_SnShield_Xloc,      ShieldB_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB3_SnShield_pos = G4ThreeVector( -1.0*ShieldB_SnShield_Xloc, -1.0*ShieldB_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB4_SnShield_pos = G4ThreeVector(      ShieldB_SnShield_Xloc, -1.0*ShieldB_SnShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldB1_SnShield_pos, ShieldB_SnShield_log, "ShieldB1_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB2_SnShield_pos, ShieldB_SnShield_log, "ShieldB2_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB3_SnShield_pos, ShieldB_SnShield_log, "ShieldB3_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB4_SnShield_pos, ShieldB_SnShield_log, "ShieldB4_SnShield", world_LV, false, 0, fCheckOverlaps );


	// SHIELD - TYPE B - W SHIELD

	// 	solid volume

		G4double ShieldB_ECOShield_Ymin = mod_Ypitch / 2.0 + CuST + 0.1 + SnST + 0.1;
		G4double ShieldB_ECOShield_Ymax = 1.5* mod_Ypitch + CuST + 0.1 + SnST  ;
		G4double ShieldB_ECOShield_dY   = ShieldB_ECOShield_Ymax - ShieldB_ECOShield_Ymin ;
		G4double ShieldB_ECOShield_Yloc = ShieldB_ECOShield_Ymin + 0.5*ShieldB_ECOShield_dY;
	
		G4double ShieldB_ECOShield_Xloc = mod_Xpitch + CuST + 0.1 + SnST + 0.1+ 0.5*WST;
	
		G4double  ShieldB_ECOShield_dX = WST;
		G4double  ShieldB_ECOShield_dZ = ShieldHeight;
		G4VSolid* ShieldB_ECOShield_sol = new G4Box( "ShieldB_ECOShield_box", 0.5 * ShieldB_ECOShield_dX, 0.5 * ShieldB_ECOShield_dY, 0.5 * ShieldB_ECOShield_dZ);


	//  logical volume
		G4LogicalVolume* ShieldB_ECOShield_log = new G4LogicalVolume( ShieldB_ECOShield_sol, mECO, "ShieldB_ECOShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldB1_ECOShield_pos = G4ThreeVector( -1.0*ShieldB_ECOShield_Xloc,     ShieldB_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB2_ECOShield_pos = G4ThreeVector(      ShieldB_ECOShield_Xloc,     ShieldB_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB3_ECOShield_pos = G4ThreeVector( -1.0*ShieldB_ECOShield_Xloc, -1.0*ShieldB_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldB4_ECOShield_pos = G4ThreeVector(      ShieldB_ECOShield_Xloc, -1.0*ShieldB_ECOShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldB1_ECOShield_pos, ShieldB_ECOShield_log, "ShieldB1_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB2_ECOShield_pos, ShieldB_ECOShield_log, "ShieldB2_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB3_ECOShield_pos, ShieldB_ECOShield_log, "ShieldB3_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldB4_ECOShield_pos, ShieldB_ECOShield_log, "ShieldB4_ECOShield", world_LV, false, 0, fCheckOverlaps );
















	// ---------------------------------------------------//
	// PASSIVE SHIELD ASSEMBLY - SHIELD C                 //
	// Aluminum         						          //
	// ---------------------------------------------------//


	// SHIELD - TYPE C


	// SHIELD - TYPE C - Cu SHIELD

	// 	solid volume
		G4double  ShieldC_CuShield_dX = CuST;
		G4double  ShieldC_CuShield_Ymin = -mod_Ypitch/2.0 ;
		G4double  ShieldC_CuShield_Ymax =  mod_Ypitch/2.0 ;
		G4double  ShieldC_CuShield_dY = ShieldC_CuShield_Ymax - ShieldC_CuShield_Ymin;
		G4double  ShieldC_CuShield_dZ = ShieldHeight;
		G4VSolid* ShieldC_CuShield_sol = new G4Box( "ShieldC_CuShield_box", 0.5 * ShieldC_CuShield_dX, 0.5 * ShieldC_CuShield_dY, 0.5 * ShieldC_CuShield_dZ);

		G4double  ShieldC_CuShield_Xloc = 1.5*mod_Xpitch + 0.5*CuST;

	//  logical volume
		G4LogicalVolume* ShieldC_CuShield_log = new G4LogicalVolume( ShieldC_CuShield_sol, mCu, "ShieldC_CuShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldC1_CuShield_pos = G4ThreeVector( -1.0*ShieldC_CuShield_Xloc,  0.0, Shield_Zpos );
		G4ThreeVector ShieldC2_CuShield_pos = G4ThreeVector(      ShieldC_CuShield_Xloc,  0.0, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldC1_CuShield_pos, ShieldC_CuShield_log, "ShieldC1_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldC2_CuShield_pos, ShieldC_CuShield_log, "ShieldC2_CuShield", world_LV, false, 0, fCheckOverlaps );



	// SHIELD - TYPE C - Sn SHIELD

	// 	solid volume
		G4double  ShieldC_SnShield_dX = SnST;
		G4double  ShieldC_SnShield_Ymin = -mod_Ypitch/2.0 - 0.1 - CuST ;
		G4double  ShieldC_SnShield_Ymax =  mod_Ypitch/2.0 + 0.1 + CuST ;
		G4double  ShieldC_SnShield_dY = ShieldC_SnShield_Ymax - ShieldC_SnShield_Ymin;
		G4double  ShieldC_SnShield_dZ = ShieldHeight;
		G4VSolid* ShieldC_SnShield_sol = new G4Box( "ShieldC_SnShield_box", 0.5 * ShieldC_SnShield_dX, 0.5 * ShieldC_SnShield_dY, 0.5 * ShieldC_SnShield_dZ);

		G4double  ShieldC_SnShield_Xloc = 1.5*mod_Xpitch + CuST + 0.1 + 0.5*SnST;

	//  logical volume
		G4LogicalVolume* ShieldC_SnShield_log = new G4LogicalVolume( ShieldC_SnShield_sol, mSn, "ShieldC_SnShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldC1_SnShield_pos = G4ThreeVector( -1.0*ShieldC_SnShield_Xloc,  0.0, Shield_Zpos );
		G4ThreeVector ShieldC2_SnShield_pos = G4ThreeVector(      ShieldC_SnShield_Xloc,  0.0, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldC1_SnShield_pos, ShieldC_SnShield_log, "ShieldC1_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldC2_SnShield_pos, ShieldC_SnShield_log, "ShieldC2_SnShield", world_LV, false, 0, fCheckOverlaps );



	// SHIELD - TYPE C - W SHIELD

	// 	solid volume
		G4double  ShieldC_ECOShield_dX = WST;
		G4double  ShieldC_ECOShield_Ymin = -mod_Ypitch/2.0 - 0.1 - CuST - 0.1 - SnST;
		G4double  ShieldC_ECOShield_Ymax =  mod_Ypitch/2.0 + 0.1 + CuST + 0.1 + SnST;
		G4double  ShieldC_ECOShield_dY = ShieldC_ECOShield_Ymax - ShieldC_ECOShield_Ymin;
		G4double  ShieldC_ECOShield_dZ = ShieldHeight;
		G4VSolid* ShieldC_ECOShield_sol = new G4Box( "ShieldC_ECOShield_box", 0.5 * ShieldC_ECOShield_dX, 0.5 * ShieldC_ECOShield_dY, 0.5 * ShieldC_ECOShield_dZ);

		G4double  ShieldC_ECOShield_Xloc = 1.5*mod_Xpitch + CuST + 0.1 + SnST + 0.1 + 0.5*WST;

	//  logical volume
		G4LogicalVolume* ShieldC_ECOShield_log = new G4LogicalVolume( ShieldC_ECOShield_sol, mECO, "ShieldC_ECOShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
		G4ThreeVector ShieldC1_ECOShield_pos = G4ThreeVector( -1.0*ShieldC_ECOShield_Xloc,  0.0, Shield_Zpos );
		G4ThreeVector ShieldC2_ECOShield_pos = G4ThreeVector(      ShieldC_ECOShield_Xloc,  0.0, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldC1_ECOShield_pos, ShieldC_ECOShield_log, "ShieldC1_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldC2_ECOShield_pos, ShieldC_ECOShield_log, "ShieldC2_ECOShield", world_LV, false, 0, fCheckOverlaps );















	// ---------------------------------------------------//
	// PASSIVE SHIELD ASSEMBLY - SHIELD D                //
	// Aluminum         						          //
	// ---------------------------------------------------//



	// SHIELD - TYPE D - 



	// SHIELD - TYPE D - Cu SHIELD

	// 	solid volume
		G4double ShieldD_CuShield_Xmin = mod_Xpitch + CuST + 0.1 ;
		G4double ShieldD_CuShield_Xmax = 1.5*mod_Xpitch + CuST ;
		G4double ShieldD_CuShield_dX   = ShieldD_CuShield_Xmax - ShieldD_CuShield_Xmin ;
		G4double ShieldD_CuShield_Xloc = ShieldD_CuShield_Xmin + 0.5*ShieldD_CuShield_dX;
	
		G4double ShieldD_CuShield_Yloc = mod_Ypitch/2.0 + 0.5*CuST;

		G4double  ShieldD_CuShield_dY = CuST;
		G4double  ShieldD_CuShield_dZ = ShieldHeight;
		G4VSolid* ShieldD_CuShield_sol = new G4Box( "ShieldD_CuShield_box", 0.5 * ShieldD_CuShield_dX, 0.5 * ShieldD_CuShield_dY, 0.5 * ShieldD_CuShield_dZ);

	//  logical volume
		G4LogicalVolume* ShieldD_CuShield_log = new G4LogicalVolume( ShieldD_CuShield_sol, mCu, "ShieldD_CuShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
	
		G4ThreeVector ShieldD1_CuShield_pos = G4ThreeVector( -1.0*ShieldD_CuShield_Xloc,       ShieldD_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD2_CuShield_pos = G4ThreeVector(      ShieldD_CuShield_Xloc,       ShieldD_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD3_CuShield_pos = G4ThreeVector( -1.0*ShieldD_CuShield_Xloc,  -1.0*ShieldD_CuShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD4_CuShield_pos = G4ThreeVector(      ShieldD_CuShield_Xloc,  -1.0*ShieldD_CuShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldD1_CuShield_pos, ShieldD_CuShield_log, "ShieldD1_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD2_CuShield_pos, ShieldD_CuShield_log, "ShieldD2_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD3_CuShield_pos, ShieldD_CuShield_log, "ShieldD3_CuShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD4_CuShield_pos, ShieldD_CuShield_log, "ShieldD4_CuShield", world_LV, false, 0, fCheckOverlaps );




	// SHIELD - TYPE D - Sn SHIELD

	// 	solid volume
		G4double ShieldD_SnShield_Xmin = mod_Xpitch + CuST + 0.1 + SnST + 0.1 ;
		G4double ShieldD_SnShield_Xmax = 1.5*mod_Xpitch + CuST + 0.1 + SnST ;
		G4double ShieldD_SnShield_dX   = ShieldD_SnShield_Xmax - ShieldD_SnShield_Xmin ;
		G4double ShieldD_SnShield_Xloc = ShieldD_SnShield_Xmin + 0.5*ShieldD_SnShield_dX;
	
		G4double ShieldD_SnShield_Yloc = mod_Ypitch/2.0 + CuST + 0.1 + 0.5*SnST;

		G4double  ShieldD_SnShield_dY = SnST;
		G4double  ShieldD_SnShield_dZ = ShieldHeight;
		G4VSolid* ShieldD_SnShield_sol = new G4Box( "ShieldD_SnShield_box", 0.5 * ShieldD_SnShield_dX, 0.5 * ShieldD_SnShield_dY, 0.5 * ShieldD_SnShield_dZ);

	//  logical volume
		G4LogicalVolume* ShieldD_SnShield_log = new G4LogicalVolume( ShieldD_SnShield_sol, mSn, "ShieldD_SnShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
	
		G4ThreeVector ShieldD1_SnShield_pos = G4ThreeVector( -1.0*ShieldD_SnShield_Xloc,       ShieldD_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD2_SnShield_pos = G4ThreeVector(      ShieldD_SnShield_Xloc,       ShieldD_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD3_SnShield_pos = G4ThreeVector( -1.0*ShieldD_SnShield_Xloc,  -1.0*ShieldD_SnShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD4_SnShield_pos = G4ThreeVector(      ShieldD_SnShield_Xloc,  -1.0*ShieldD_SnShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldD1_SnShield_pos, ShieldD_SnShield_log, "ShieldD1_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD2_SnShield_pos, ShieldD_SnShield_log, "ShieldD2_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD3_SnShield_pos, ShieldD_SnShield_log, "ShieldD3_SnShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD4_SnShield_pos, ShieldD_SnShield_log, "ShieldD4_SnShield", world_LV, false, 0, fCheckOverlaps );


	// SHIELD - TYPE D - W SHIELD

	// 	solid volume


		G4double ShieldD_ECOShield_Xmin = mod_Xpitch + CuST + 0.1 + SnST + 0.1 + WST;
		G4double ShieldD_ECOShield_Xmax = 1.5*mod_Xpitch + CuST + 0.1 + SnST + 0.1 + WST ;
		G4double ShieldD_ECOShield_dX   = ShieldD_ECOShield_Xmax - ShieldD_ECOShield_Xmin ;
		G4double ShieldD_ECOShield_Xloc = ShieldD_ECOShield_Xmin + 0.5*ShieldD_ECOShield_dX;
	
		G4double ShieldD_ECOShield_Yloc = mod_Ypitch/2.0 + CuST + 0.1 + SnST + 0.1 + 0.5*WST;

		G4double  ShieldD_ECOShield_dY = WST;
		G4double  ShieldD_ECOShield_dZ = ShieldHeight;
		G4VSolid* ShieldD_ECOShield_sol = new G4Box( "ShieldD_ECOShield_box", 0.5 * ShieldD_ECOShield_dX, 0.5 * ShieldD_ECOShield_dY, 0.5 * ShieldD_ECOShield_dZ);

	//  logical volume
		G4LogicalVolume* ShieldD_ECOShield_log = new G4LogicalVolume( ShieldD_ECOShield_sol, mECO, "ShieldD_ECOShield_log", 0, 0, 0 );
	
	//  physical volume positions
	
	
		G4ThreeVector ShieldD1_ECOShield_pos = G4ThreeVector( -1.0*ShieldD_ECOShield_Xloc,       ShieldD_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD2_ECOShield_pos = G4ThreeVector(      ShieldD_ECOShield_Xloc,       ShieldD_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD3_ECOShield_pos = G4ThreeVector( -1.0*ShieldD_ECOShield_Xloc,  -1.0*ShieldD_ECOShield_Yloc, Shield_Zpos );
		G4ThreeVector ShieldD4_ECOShield_pos = G4ThreeVector(      ShieldD_ECOShield_Xloc,  -1.0*ShieldD_ECOShield_Yloc, Shield_Zpos );

	//  place physical volumes 
		new G4PVPlacement( 0, ShieldD1_ECOShield_pos, ShieldD_ECOShield_log, "ShieldD1_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD2_ECOShield_pos, ShieldD_ECOShield_log, "ShieldD2_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD3_ECOShield_pos, ShieldD_ECOShield_log, "ShieldD3_ECOShield", world_LV, false, 0, fCheckOverlaps );
		new G4PVPlacement( 0, ShieldD4_ECOShield_pos, ShieldD_ECOShield_log, "ShieldD4_ECOShield", world_LV, false, 0, fCheckOverlaps );



	// ==================================================================================== //
	//	Instrument Base Plate
	//  Model as large-area plate of Aluminum, 1 cm thick.
	// ==================================================================================== //


	//------------------------------------------//
	// FRAM Plate								//
	//------------------------------------------//
		// solid volume
		G4double IBP_X = 900.0*mm;
		G4double IBP_Y = 900.0*mm;
		G4double IBP_Z = 10.0*mm;
		G4VSolid* IBP_SV = new G4Box( "IBP_box", 0.5 * IBP_X, 0.5 * IBP_Y, 0.5 * IBP_Z);
	
		// logical volume
		G4LogicalVolume* IBP_LV = new G4LogicalVolume( IBP_SV, mAl6061, "IBP_log", 0, 0, 0 );
	
		// place physical volume
		G4double IBP_Xpos = 0.0*mm;
		G4double IBP_Ypos = 0.0*mm;
		G4double IBP_Zpos = -150.0*mm;
		G4ThreeVector IBP_Pos = G4ThreeVector( IBP_Xpos, IBP_Ypos, IBP_Zpos );
	
		new G4PVPlacement( 0, IBP_Pos, IBP_LV, "IBP", world_LV, false, 0, fCheckOverlaps );



	// ==================================================================================== //
	//	PSEUDO-FRAM AASSEMBLY
	//  Model as large-area plate of Aluminum, 4 cm thick.
	// ==================================================================================== //


	//------------------------------------------//
	// FRAM Plate								//
	//------------------------------------------//
		// solid volume
		G4double FRAM_X = 1000.0*mm;
		G4double FRAM_Y = 40.0*mm;
		G4double FRAM_Z = 1000.0*mm;
		G4VSolid* FRAM_SV = new G4Box( "FRAM_box", 0.5 * FRAM_X, 0.5 * FRAM_Y, 0.5 * FRAM_Z);
	
		// logical volume
		G4LogicalVolume* FRAM_LV = new G4LogicalVolume( FRAM_SV, mAl6061, "FRAM_log", 0, 0, 0 );
	
		// place physical volume
		G4double FRAM_Xpos = 0.0*mm;
		G4double FRAM_Ypos = 500.0*mm;
		G4double FRAM_Zpos = -500.0*mm;
		G4ThreeVector FRAM_Pos = G4ThreeVector( FRAM_Xpos, FRAM_Ypos, FRAM_Zpos );
	
		new G4PVPlacement( 0, FRAM_Pos, FRAM_LV, "FRAM", world_LV, false, 0, fCheckOverlaps );














	// ==================================================================================== //
	//	Print some information
	// ==================================================================================== //
	//	G4int iNumOfScints = CalNum + PlaNum;
	//	G4ThreeVector center = G4ThreeVector( 0., 0., (TopPlate_Zpos + 0.5*TopPlate_Z) );
	//	G4RotationMatrix center_rot = G4RotationMatrix( dAzimuthAngle, dZenithAngle, 0. );
	//	center.transform( center_rot );


		G4cout << " " << G4endl;
		G4cout << "------ Module Size: " << G4endl;
		G4cout << "           dX: " << mod_X << " mm" << G4endl;
		G4cout << "           dY: " << mod_Y << " mm" << G4endl;
		G4cout << "           dZ: " << mod_Z << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Module 1 Position: " << G4endl;
		G4cout << "           dX: " << mod1_Xpos << " mm" << G4endl;
		G4cout << "           dY: " << mod1_Ypos << " mm" << G4endl;
		G4cout << "           dZ: " << mod1_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Module 2 Position: " << G4endl;
		G4cout << "           dX: " << mod2_Xpos << " mm" << G4endl;
		G4cout << "           dY: " << mod2_Ypos << " mm" << G4endl;
		G4cout << "           dZ: " << mod2_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Module 3 Position: " << G4endl;
		G4cout << "           dX: " << mod3_Xpos << " mm" << G4endl;
		G4cout << "           dY: " << mod3_Ypos << " mm" << G4endl;
		G4cout << "           dZ: " << mod3_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Module 4 Position: " << G4endl;
		G4cout << "           dX: " << mod4_Xpos << " mm" << G4endl;
		G4cout << "           dY: " << mod4_Ypos << " mm" << G4endl;
		G4cout << "           dZ: " << mod4_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Module 5 Position: " << G4endl;
		G4cout << "           dX: " << mod5_Xpos << " mm" << G4endl;
		G4cout << "           dY: " << mod5_Ypos << " mm" << G4endl;
		G4cout << "           dZ: " << mod5_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Module 6 Position: " << G4endl;
		G4cout << "           dX: " << mod6_Xpos << " mm" << G4endl;
		G4cout << "           dY: " << mod6_Ypos << " mm" << G4endl;
		G4cout << "           dZ: " << mod6_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Base Plate: " << G4endl;
		G4cout << "           dX: " << ENCL_Bot_X << " mm" << G4endl;
		G4cout << "           dY: " << ENCL_Bot_Y << " mm" << G4endl;
		G4cout << "           dZ: " << ENCL_Bot_Z << " mm" << G4endl;
		G4cout << "            X: " << ENCL_Bot_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << ENCL_Bot_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << ENCL_Bot_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Side 1 Plate: " << G4endl;
		G4cout << "           dX: " << ENCL_Side1_X << " mm" << G4endl;
		G4cout << "           dY: " << ENCL_Side1_Y << " mm" << G4endl;
		G4cout << "           dZ: " << ENCL_Side1_Z << " mm" << G4endl;
		G4cout << "            X: " << ENCL_Side1_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << ENCL_Side1_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << ENCL_Side1_Zpos << " mm" << G4endl;
		
		G4cout << " " << G4endl;
		G4cout << "------ Side 2 Plate: " << G4endl;
		G4cout << "           dX: " << ENCL_Side2_X << " mm" << G4endl;
		G4cout << "           dY: " << ENCL_Side2_Y << " mm" << G4endl;
		G4cout << "           dZ: " << ENCL_Side2_Z << " mm" << G4endl;
		G4cout << "            X: " << ENCL_Side2_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << ENCL_Side2_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << ENCL_Side2_Zpos << " mm" << G4endl;
				
		G4cout << " " << G4endl;
		G4cout << "------ Analog Power Board: " << G4endl;
		G4cout << "           dX: " << APB_X << " mm" << G4endl;
		G4cout << "           dY: " << APB_Y << " mm" << G4endl;
		G4cout << "           dZ: " << APB_Z << " mm" << G4endl;
		G4cout << "            X: " << APB_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << APB_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << APB_Zpos << " mm" << G4endl;

		G4cout << " " << G4endl;
		G4cout << "------ MIB: " << G4endl;
		G4cout << "           dX: " << MIB_X << " mm" << G4endl;
		G4cout << "           dY: " << MIB_Y << " mm" << G4endl;
		G4cout << "           dZ: " << MIB_Z << " mm" << G4endl;
		G4cout << "            X: " << MIB_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << MIB_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << MIB_Zpos << " mm" << G4endl;	

		G4cout << " " << G4endl;
		G4cout << "------ Analog PCB: " << G4endl;
		G4cout << "           dX: " << PCB_X << " mm" << G4endl;
		G4cout << "           dY: " << PCB_Y << " mm" << G4endl;
		G4cout << "           dZ: " << PCB_Z << " mm" << G4endl;
		G4cout << "           Z1: " << PCB1_Zpos << " mm" << G4endl;
		G4cout << "           Z2: " << PCB2_Zpos << " mm" << G4endl;
		G4cout << "           Z3: " << PCB3_Zpos << " mm" << G4endl;
		G4cout << "           Z4: " << PCB4_Zpos << " mm" << G4endl;

		G4cout << " " << G4endl;
		G4cout << "------ MIB Plate - Tungsten: " << G4endl;
		G4cout << "           dX: " << MIBplateECO_X << " mm" << G4endl;
		G4cout << "           dY: " << MIBplateECO_Y << " mm" << G4endl;
		G4cout << "           dZ: " << MIBplateECO_Z << " mm" << G4endl;
		G4cout << "            X: " << MIBplateECO_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << MIBplateECO_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << MIBplateECO_Zpos << " mm" << G4endl;	

		G4cout << " " << G4endl;
		G4cout << "------ MIB Plate - Tin: " << G4endl;
		G4cout << "           dX: " << MIBplateSn_X << " mm" << G4endl;
		G4cout << "           dY: " << MIBplateSn_Y << " mm" << G4endl;
		G4cout << "           dZ: " << MIBplateSn_Z << " mm" << G4endl;		
		G4cout << "            X: " << MIBplateSn_Xpos << " mm" << G4endl;
		G4cout << "            Y: " << MIBplateSn_Ypos << " mm" << G4endl;
		G4cout << "            Z: " << MIBplateSn_Zpos << " mm" << G4endl;	






// 
// 
// 		G4cout << " " << G4endl;
// 		G4cout << "------ MIB-PMT Connectors: " << G4endl;
// 		G4cout << "           dX: " << MIBconnect_X << " mm" << G4endl;
// 		G4cout << "           dY: " << MIBconnect_Y << " mm" << G4endl;
// 		G4cout << "           dZ: " << MIBconnect_Z << " mm" << G4endl;
// 		G4cout << "            Z: " << MIBconnect_Zpos << " mm" << G4endl;

		G4cout << " " << G4endl;
		G4cout << "------ PMT PCB: " << G4endl;
		G4cout << "           dX: " << PMT_PCB_X << " mm" << G4endl;
		G4cout << "           dY: " << PMT_PCB_Y << " mm" << G4endl;
		G4cout << "           dZ: " << PMT_PCB_Z << " mm" << G4endl;
		G4cout << "            Z: " << PMT_PCB_Zpos << " mm" << G4endl;
// 
// 		G4cout << " " << G4endl;
// 		G4cout << "------ PMT Clamp: " << G4endl;
// 		G4cout << "         Rmin: " << PMTclamp_Rmin << " mm" << G4endl;
// 		G4cout << "         Rmax: " << PMTclamp_Rmax << " mm" << G4endl;
// 		G4cout << "           dZ: " << PMTclamp_Z << " mm" << G4endl;
// 		G4cout << "            Z: " << PMTclamp_Zpos << " mm" << G4endl;

		G4cout << " " << G4endl;
		G4cout << "------ PMT: " << G4endl;
		G4cout << "         Rmin: " << PMT_Rmin << " mm" << G4endl;
		G4cout << "         Rmax: " << PMT_Rmax << " mm" << G4endl;
		G4cout << "           dZ: " << PMT_Z << " mm" << G4endl;
		G4cout << "            Z: " << PMT_Zpos << " mm" << G4endl;

		G4cout << " " << G4endl;
		G4cout << "------ Scintillators: " << G4endl;
		G4cout << "           dX: " << scint_X << " mm" << G4endl;
		G4cout << "           dY: " << scint_Y << " mm" << G4endl;
		G4cout << "           dZ: " << scint_Z << " mm" << G4endl;
		G4cout << "            Z: " << scint_Zpos << " mm" << G4endl;
// 
// 		G4cout << " " << G4endl;
// 		G4cout << "------ Scintillator Case (sides): " << G4endl;
// 		G4cout << "           dX: " << ScintCase_X << " mm" << G4endl;
// 		G4cout << "           dY: " << ScintCase_Y << " mm" << G4endl;
// 		G4cout << "           dZ: " << ScintCase_Z << " mm" << G4endl;
// 		G4cout << "            Z: " << ScintCase_Zpos << " mm" << G4endl;
// 
// 		G4cout << " " << G4endl;
// 		G4cout << "------ Scintillator Caps: " << G4endl;
// 		G4cout << "           dX: " << ScintCap_X << " mm" << G4endl;
// 		G4cout << "           dY: " << ScintCap_Y << " mm" << G4endl;
// 		G4cout << "           dZ: " << ScintCap_Z << " mm" << G4endl;
// 		G4cout << "            Z: " << ScintCap_Zpos << " mm" << G4endl;
// 
// 		G4cout << " " << G4endl;
// 		G4cout << "------ Top Grid Element: " << G4endl;
// 		G4cout << "           dX: " << TopGridElement_X << " mm" << G4endl;
// 		G4cout << "           dY: " << TopGridElement_Y << " mm" << G4endl;
// 		G4cout << "           dZ: " << TopGridElement_Z << " mm" << G4endl;
// 		G4cout << "            Z: " << TopGridElement_Zpos << " mm" << G4endl;




/*




	// 	G4cout << "------ Center of Top of Instrument: " << G4endl;
	// 	G4cout << "           X: " << center.x() << " mm" << G4endl;
	// 	G4cout << "           Y: " << center.y() << " mm" << G4endl;
	// 	G4cout << "           Z: " << center.z() << " mm" << G4endl;
	// 
	// 	G4cout << "------ Modules: 1" << G4endl;
	// 	G4cout << "           Total Plastics: " << PlaNum << G4endl;
	// 	G4cout << "           Total Calorimeters: " << CalNum << G4endl;
	// 	G4cout << "           Total Scintillators: " << iNumOfScints << G4endl;
	// 	G4cout << G4endl;
	// 	G4cout << G4endl;



	// ==================================================================================== //
	//	Sensitive Detectors
	// ==================================================================================== //
		// Initialize the manager
		G4SDManager* SDman = G4SDManager::GetSDMpointer();

		// Create SD if it doesn't exist
		ScintSD* aScintSD = dynamic_cast<ScintSD*>(SDman->FindSensitiveDetector("ScintSD",false));
		if ( !aScintSD ) {
			aScintSD = new ScintSD( "ScintSD" );
			SDman -> AddNewDetector( aScintSD );
		}
 
		// Add the scintillators 
		Cal_log -> SetSensitiveDetector( aScintSD );
		Pla_log -> SetSensitiveDetector( aScintSD );	

	// ==================================================================================== //
	//	Visualization attributes
	// ==================================================================================== //
		// Visual properties of the world
		World_log -> SetVisAttributes( G4VisAttributes::GetInvisible() );
		//CC_log -> SetVisAttributes( G4VisAttributes::Invisible );

		// PC Boards (green)
		G4VisAttributes* PCboard_VisAtt = new G4VisAttributes( G4Color::Green() );
		PCboard_VisAtt -> SetForceSolid( false ); 
		PCB_log -> SetVisAttributes( PCboard_VisAtt );
		MIB_log -> SetVisAttributes( PCboard_VisAtt );
		PMTPCB_log -> SetVisAttributes( PCboard_VisAtt );

		// Aluminum (blue)
		G4VisAttributes* Al_VisAtt = new G4VisAttributes( G4Color::Blue() );
		Al_VisAtt -> SetForceSolid( false ); 
		BasePlate_log -> SetVisAttributes( Al_VisAtt );
		LowerPMTclamp_log -> SetVisAttributes( Al_VisAtt );
		PMTclamp_log -> SetVisAttributes( Al_VisAtt );
	// 	TopPlate_log -> SetVisAttributes( Al_VisAtt );
		SidePlate1_log -> SetVisAttributes( Al_VisAtt );
		SidePlate2_log -> SetVisAttributes( Al_VisAtt );
		FRAM_log -> SetVisAttributes( Al_VisAtt );

		// Tungsten (Red)
		G4VisAttributes* MIBplateECO_VisAtt = new G4VisAttributes( G4Color::Red() );
		MIBplateECO_VisAtt -> SetForceSolid( false ); 
		MIBplateECO_VisAtt -> SetForceAuxEdgeVisible( true ); 
		MIBplateECO_log -> SetVisAttributes( MIBplateECO_VisAtt );
	
	


		// Tin (Yellow)
		G4VisAttributes* Sn_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		MIBplateSn_log -> SetVisAttributes( Sn_VisAtt );



		// MIB (magenta)
	//	G4VisAttributes* MIB_VisAtt = new G4VisAttributes( G4Color::Magenta() );

		// Connectors (light blue)
		G4VisAttributes* Connect_VisAtt = new G4VisAttributes( G4Colour( 0., 1., 1. ) );
		MIBconnect_log -> SetVisAttributes( Connect_VisAtt );

		// PMT (white)
		G4VisAttributes* PMT_VisAtt = new G4VisAttributes( G4Color::White() );
	//	G4VisAttributes* PMT_VisAtt = new G4VisAttributes( G4Color::Black() );
		PMT_VisAtt -> SetForceSolid( false );
		PMT_VisAtt -> SetForceAuxEdgeVisible( true ); 
		PMT_log -> SetVisAttributes( PMT_VisAtt );

		// Calorimeter Scintillators (red)
		G4VisAttributes* Cal_VisAtt = new G4VisAttributes( G4Color::Red() );
		Cal_VisAtt -> SetForceSolid( false );
		Cal_VisAtt -> SetForceAuxEdgeVisible( true ); 
		Cal_log -> SetVisAttributes( Cal_VisAtt );

		// Plastic Scintillators (yellow)
		G4VisAttributes* Pla_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		Pla_VisAtt -> SetForceSolid( false ); 
		Pla_VisAtt -> SetForceAuxEdgeVisible( true ); 
		Pla_log -> SetVisAttributes( Pla_VisAtt );
	
	
		//  Scintillator Case (gray)
		G4VisAttributes* ScintCase_VisAtt = new G4VisAttributes( G4Color::Gray() );
		ScintCase_VisAtt -> SetForceSolid( false );
		ScintCase_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ScintCase_log -> SetVisAttributes( ScintCase_VisAtt );

		//  Scintillator Cap (gray)
		G4VisAttributes* ScintCap_VisAtt = new G4VisAttributes( G4Color::Gray() );
		ScintCap_VisAtt -> SetForceSolid( false );
		ScintCap_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ScintCap_log -> SetVisAttributes( ScintCap_VisAtt );

		//  Top Grid Element (gray)
		G4VisAttributes* TopGridElement_VisAtt = new G4VisAttributes( G4Color::Gray() );
		TopGridElement_VisAtt -> SetForceSolid( false );
		TopGridElement_VisAtt -> SetForceAuxEdgeVisible( true ); 
		TopGridElement_log -> SetVisAttributes( TopGridElement_VisAtt );

*/

		// Side Shields - Cu (yellow)
		G4VisAttributes* ShieldA_CuShield_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		ShieldA_CuShield_VisAtt -> SetForceSolid( false ); 
		ShieldA_CuShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldA_CuShield_log -> SetVisAttributes( ShieldA_CuShield_VisAtt );

		G4VisAttributes* ShieldB_CuShield_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		ShieldB_CuShield_VisAtt -> SetForceSolid( false ); 
		ShieldB_CuShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldB_CuShield_log -> SetVisAttributes( ShieldB_CuShield_VisAtt );
	
		G4VisAttributes* ShieldC_CuShield_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		ShieldC_CuShield_VisAtt -> SetForceSolid( false ); 
		ShieldC_CuShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldC_CuShield_log -> SetVisAttributes( ShieldC_CuShield_VisAtt );

		G4VisAttributes* ShieldD_CuShield_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		ShieldD_CuShield_VisAtt -> SetForceSolid( false ); 
		ShieldD_CuShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldD_CuShield_log -> SetVisAttributes( ShieldD_CuShield_VisAtt );

		G4VisAttributes* MIBplateCu_VisAtt = new G4VisAttributes( G4Color::Yellow() );
		MIBplateCu_VisAtt -> SetForceSolid( false ); 
		MIBplateCu_VisAtt -> SetForceAuxEdgeVisible( true ); 
		MIBplateCu_LV -> SetVisAttributes( MIBplateCu_VisAtt );

	
		// Side Shields - Sn (blue)
		G4VisAttributes* ShieldA_SnShield_VisAtt = new G4VisAttributes( G4Color::Blue() );
		ShieldA_SnShield_VisAtt -> SetForceSolid( false ); 
		ShieldA_SnShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldA_SnShield_log -> SetVisAttributes( ShieldA_SnShield_VisAtt );

		G4VisAttributes* ShieldB_SnShield_VisAtt = new G4VisAttributes( G4Color::Blue() );
		ShieldB_SnShield_VisAtt -> SetForceSolid( false ); 
		ShieldB_SnShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldB_SnShield_log -> SetVisAttributes( ShieldB_SnShield_VisAtt );
	
		G4VisAttributes* ShieldC_SnShield_VisAtt = new G4VisAttributes( G4Color::Blue() );
		ShieldC_SnShield_VisAtt -> SetForceSolid( false ); 
		ShieldC_SnShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldC_SnShield_log -> SetVisAttributes( ShieldC_SnShield_VisAtt );

		G4VisAttributes* ShieldD_SnShield_VisAtt = new G4VisAttributes( G4Color::Blue() );
		ShieldD_SnShield_VisAtt -> SetForceSolid( false ); 
		ShieldD_SnShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldD_SnShield_log -> SetVisAttributes( ShieldD_SnShield_VisAtt );

		G4VisAttributes* MIBplateSn_VisAtt = new G4VisAttributes( G4Color::Blue() );
		MIBplateSn_VisAtt -> SetForceSolid( false ); 
		MIBplateSn_VisAtt -> SetForceAuxEdgeVisible( true ); 
		MIBplateSn_LV -> SetVisAttributes( MIBplateSn_VisAtt );



		// Side Shields - Pb (Red)
		G4VisAttributes* ShieldA_ECOShield_VisAtt = new G4VisAttributes( G4Color::Red() );
		ShieldA_ECOShield_VisAtt -> SetForceSolid( false ); 
		ShieldA_ECOShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldA_ECOShield_log -> SetVisAttributes( ShieldA_ECOShield_VisAtt );

		G4VisAttributes* ShieldB_ECOShield_VisAtt = new G4VisAttributes( G4Color::Red() );
		ShieldB_ECOShield_VisAtt -> SetForceSolid( false ); 
		ShieldB_ECOShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldB_ECOShield_log -> SetVisAttributes( ShieldB_ECOShield_VisAtt );

		G4VisAttributes* ShieldC_ECOShield_VisAtt = new G4VisAttributes( G4Color::Red() );
		ShieldC_ECOShield_VisAtt -> SetForceSolid( false ); 
		ShieldC_ECOShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldC_ECOShield_log -> SetVisAttributes( ShieldC_ECOShield_VisAtt );

		G4VisAttributes* ShieldD_ECOShield_VisAtt = new G4VisAttributes( G4Color::Red() );
		ShieldD_ECOShield_VisAtt -> SetForceSolid( false ); 
		ShieldD_ECOShield_VisAtt -> SetForceAuxEdgeVisible( true ); 
		ShieldD_ECOShield_log -> SetVisAttributes( ShieldD_ECOShield_VisAtt );

		G4VisAttributes* MIBplateECO_VisAtt = new G4VisAttributes( G4Color::Red() );
		MIBplateECO_VisAtt -> SetForceSolid( false ); 
		MIBplateECO_VisAtt -> SetForceAuxEdgeVisible( true ); 
		MIBplateECO_LV -> SetVisAttributes( MIBplateECO_VisAtt );



   //======================================================
    // Visualization attributes
    //======================================================
    world_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    module_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detector_cal_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    detector_pla_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    SCINT_Case_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    SCINT_Case_Top_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );
    SCINT_Case_Bot_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );

    auto metal_VisAtt = new G4VisAttributes( G4Color::Gray() );
    metal_VisAtt -> SetVisibility( true );
    ENCL_Bot_LV -> SetVisAttributes( metal_VisAtt );
    ENCL_Side1_LV -> SetVisAttributes( metal_VisAtt );
    ENCL_Side2_LV -> SetVisAttributes( metal_VisAtt );
    MIBP_LV -> SetVisAttributes( metal_VisAtt );
    MIBP_Edge_LV -> SetVisAttributes( metal_VisAtt );

    auto pc_VisAtt = new G4VisAttributes( G4Color::Green() );
    pc_VisAtt -> SetVisibility( true );
    APB_LV -> SetVisAttributes( pc_VisAtt );
    MIB_LV -> SetVisAttributes( pc_VisAtt );
    PMT_PCB_LV -> SetVisAttributes( pc_VisAtt );

    auto con_VisAtt = new G4VisAttributes( G4Colour( 0.92, 0.79, 0.61 ) );
    APB_Con_LV -> SetVisAttributes( con_VisAtt );
    
    auto pmt_VisAtt = new G4VisAttributes( G4Color::Blue() );
    pmt_VisAtt -> SetVisibility( true );
    PMT_LV -> SetVisAttributes( pmt_VisAtt );
    PMT_Cap_LV -> SetVisAttributes( metal_VisAtt );

    auto cal_VisAtt = new G4VisAttributes( G4Color::Red() );
    cal_VisAtt -> SetVisibility(true);
    cal_LV -> SetVisAttributes(cal_VisAtt);
    // cal_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );

    auto pla_VisAtt = new G4VisAttributes( G4Color::Cyan() );
    pla_VisAtt -> SetVisibility(true);
    pla_LV -> SetVisAttributes(pla_VisAtt);
    // pla_LV -> SetVisAttributes( G4VisAttributes::GetInvisible() );







	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//	Always return the root volume
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		return world_PV;
	}


  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void DetectorConstruction::ConstructSDandField()
  {
    auto SDManager = G4SDManager::GetSDMpointer();
    auto LVS = G4LogicalVolumeStore::GetInstance();

    //----------------------------------
    // Sensitive detectors
    //----------------------------------
    auto scint_SD = new ScintSD( "leapDet" );
    SDManager->AddNewDetector( scint_SD );
    LVS->GetVolume("Cal_LV")->SetSensitiveDetector( scint_SD );
    LVS->GetVolume("Pla_LV")->SetSensitiveDetector( scint_SD );
    LVS->GetVolume("Src_LV")->SetSensitiveDetector( scint_SD );

  }


	// ************************************************************************************ //
	//	Function: Update Geometry
	// ************************************************************************************ //
	#include "G4RunManager.hh"

	void DetectorConstruction::UpdateGeometry()
	{
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    G4RunManager::GetRunManager()->ReinitializeGeometry();
	}

	// ************************************************************************************ //
}