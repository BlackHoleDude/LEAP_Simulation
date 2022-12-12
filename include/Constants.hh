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
/// \file Constants.hh
/// \brief Definition of the Constants class


#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{
  //****************************************************************************
  /// Constants to define geometry.
  ///
  //****************************************************************************
  constexpr auto kNumKeep = 8;
  
  //--------------------------------------------------------
  // SCINTILLATOR
  //--------------------------------------------------------
  constexpr auto kScint_Taper_Angle = 30.0*deg;
  constexpr auto kScint_Taper_Radius = 4.0*mm;

  constexpr auto kScint_Xsize = 17.0*mm;
  constexpr auto kScint_Ysize = 17.0*mm;
  constexpr auto kScint_Zsize = 100.0*mm;
  // constexpr auto kScint_Xpitch = 22.0*mm;
  // constexpr auto kScint_Ypitch = 22.0*mm;
  constexpr auto kScint_Xpitch = 21.1*mm;
  constexpr auto kScint_Ypitch = 21.1*mm;

  constexpr auto kNumScint_X = 12;
  constexpr auto kNumScint_Y = 12;
  constexpr auto kNumScint = kNumScint_X * kNumScint_Y;


  //--------------------------------------------------------
  // SCINTILLATOR CASE
  //--------------------------------------------------------
  constexpr auto kScint_Case_Thickness = 2.0*mm;
  constexpr auto kScint_Case_Xsize = kScint_Xsize + 2*kScint_Case_Thickness;
  constexpr auto kScint_Case_Ysize = kScint_Ysize + 2*kScint_Case_Thickness;
  constexpr auto kScint_Case_Zsize = 107.0*mm;

  constexpr auto kScint_Case_Top_Xsize = kScint_Xsize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Top_Ysize = kScint_Ysize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Top_Zsize = 10.0*mm;

  constexpr auto kScint_Case_Bot_Xsize = kScint_Xsize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Bot_Ysize = kScint_Ysize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Bot_Zsize = 8.0*mm;

  //--------------------------------------------------------
  // PMT
  //--------------------------------------------------------
  constexpr auto kPMT_Rmin = 0.0*mm;
  constexpr auto kPMT_Rmax = 7.0*mm;
  constexpr auto kPMT_Zsize = 10.9*mm;

  constexpr auto kPMT_Zoffset = 0.75*mm;

  //--------------------------------------------------------
  // PMT Cap
  //--------------------------------------------------------
  constexpr auto kPMT_Cap_Xsize = kScint_Xsize;
  constexpr auto kPMT_Cap_Ysize = kScint_Xsize;
  constexpr auto kPMT_Cap_Zsize = 3.75*mm;

  constexpr auto kPMT_Cap_Hole_Rmin = 0.0*mm;
  constexpr auto kPMT_Cap_Hole_Rmax = kPMT_Rmax;
  constexpr auto kPMT_Cap_Hole_Zsize = kPMT_Cap_Zsize;

  //--------------------------------------------------------
  // PMT Power Board
  //--------------------------------------------------------
  constexpr auto kPMT_PCB_Xsize = kScint_Xsize;
  constexpr auto kPMT_PCB_Ysize = kScint_Xsize;
  constexpr auto kPMT_PCB_Zsize = 0.813*mm;

  constexpr auto kPMT_PCB_Gap = 2.5*mm;
  constexpr auto kPCB_Gap = 4.0*mm;

  //--------------------------------------------------------
  // Module Interface Board (MIB)
  //--------------------------------------------------------
  // constexpr auto kMIB_Xsize = 164.0*mm;
  // constexpr auto kMIB_Ysize = 164.0*mm;
  constexpr auto kMIB_Xsize = 240.0*mm;
  constexpr auto kMIB_Ysize = 240.0*mm;
  constexpr auto kMIB_Zsize = 1.5*mm;

  //--------------------------------------------------------
  // Analog Power Board (APB)
  //--------------------------------------------------------
  constexpr auto kAPB_Xsize = 1.5*mm;
  constexpr auto kAPB_Ysize = 147.0*mm;
  constexpr auto kAPB_Zsize = 120.0*mm;

  constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset
  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;

  //--------------------------------------------------------
  // APB - MIB Connectors
  //--------------------------------------------------------
  constexpr auto kAPB_Con_Xsize = 5.0*mm;
  constexpr auto kAPB_Con_Ysize = 75.0*mm;
  constexpr auto kAPB_Con_Zsize = 10.0*mm;

  //--------------------------------------------------------
  // Enclosure (ENCL) Base Plate 
  //--------------------------------------------------------
  constexpr auto kENCL_Thickness = 5.0*mm;
  constexpr auto kENCL_Bot_Xsize = 260.0*mm;
  constexpr auto kENCL_Bot_Ysize = 260.0*mm;
  constexpr auto kENCL_Bot_Zsize = kENCL_Thickness;

  //--------------------------------------------------------
  // Enclosure (ENCL) Top
  //--------------------------------------------------------
  constexpr auto kENCL_Top_Xsize = kScint_Xpitch;
  constexpr auto kENCL_Top_Ysize = kScint_Ypitch;
  constexpr auto kENCL_Top_Zsize = 7.5*mm;

  constexpr auto kENCL_Top_Hole_Xsize = kScint_Case_Top_Xsize;
  constexpr auto kENCL_Top_Hole_Ysize = kScint_Case_Top_Ysize;
  constexpr auto kENCL_Top_Hole_Zsize = 2*kENCL_Top_Zsize;

  constexpr auto kENCL_Top_Zoffset = 0.75*mm;

  //--------------------------------------------------------
  // Enclosure (ENCL) Top Edge
  //--------------------------------------------------------
  constexpr auto kENCL_TopEdge_Xsize = kENCL_Bot_Xsize;
  constexpr auto kENCL_TopEdge_Ysize = kENCL_Bot_Ysize;
  constexpr auto kENCL_TopEdge_Zsize = kENCL_Top_Zsize;

  constexpr auto kENCL_TopEdge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kENCL_TopEdge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kENCL_TopEdge_Hole_Zsize = 2*kENCL_TopEdge_Zsize;

  //--------------------------------------------------------
  // MIB Plate
  //--------------------------------------------------------
  constexpr auto kMIBP_Xsize = kScint_Xpitch;
  constexpr auto kMIBP_Ysize = kScint_Ypitch;
  constexpr auto kMIBP_Zsize = 10.5*mm;

  // holes
  constexpr auto kMIBP_Hole_Xsize = kScint_Case_Bot_Xsize;
  constexpr auto kMIBP_Hole_Ysize = kScint_Case_Bot_Ysize;
  constexpr auto kMIBP_Hole_Zsize = 2*kMIBP_Zsize;

  constexpr auto kMIBP_Zoffset = 1.5*mm;

  //--------------------------------------------------------
  // MIB Plate Edge
  //--------------------------------------------------------
  constexpr auto kMIBP_Edge_Xsize = kENCL_Bot_Xsize;
  constexpr auto kMIBP_Edge_Ysize = kENCL_Bot_Ysize;
  constexpr auto kMIBP_Edge_Zsize = kMIBP_Zsize;

  constexpr auto kMIBP_Edge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kMIBP_Edge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kMIBP_Edge_Hole_Zsize = 2*kMIBP_Edge_Zsize;

  //--------------------------------------------------------
  // DETECTOR
  //--------------------------------------------------------
  constexpr auto kDetector_Xsize = kScint_Xpitch;
  constexpr auto kDetector_Ysize = kScint_Ypitch;
  constexpr auto kDetector_Zsize = 
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kScint_Case_Top_Zsize;

  //--------------------------------------------------------
  // MODULE
  //--------------------------------------------------------
  constexpr auto kModule_Xsize = kENCL_Bot_Xsize + 2*kENCL_Thickness;
  constexpr auto kModule_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
  constexpr auto kModule_Zsize = 
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kDetector_Zsize;
  
  constexpr auto kModule_Sep = 5.0*mm;
  constexpr auto kModule_Xpitch = kModule_Xsize + kModule_Sep;
  constexpr auto kModule_Ypitch = kModule_Ysize + kModule_Sep;

  //--------------------------------------------------------
  // Enclosure (ENCL) Side
  //--------------------------------------------------------
  constexpr auto kENCL_Side1_Xsize = kENCL_Thickness;
  constexpr auto kENCL_Side1_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
  constexpr auto kENCL_Side1_Zsize = 
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kENCL_Top_Zoffset +
                  kENCL_Top_Zsize;

  constexpr auto kENCL_Side2_Xsize = kENCL_Bot_Ysize;
  constexpr auto kENCL_Side2_Ysize = kENCL_Thickness;
  constexpr auto kENCL_Side2_Zsize = kENCL_Side1_Zsize;



  //--------------------------------------------------------
  // SHIELD PARAMETERS
  //--------------------------------------------------------
  constexpr auto kShieldW_thickness  = 7.0*mm;
  constexpr auto kShieldECO_thickness  = 7.0*mm;
  constexpr auto kShieldSn_thickness = 1.0*mm;
  constexpr auto kShieldCu_thickness = 1.0*mm;



  //--------------------------------------------------------
  // WORLD
  //--------------------------------------------------------
  constexpr auto kWorld_Xsize = 6.0*m;
  constexpr auto kWorld_Ysize = 6.0*m;
  constexpr auto kWorld_Zsize = 6.0*m;

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
