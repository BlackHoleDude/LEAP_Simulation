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
/// \file RunAction.hh
/// \brief Definition of the RunAction class

#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Run;
class G4Timer;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  //****************************************************************************
  /// Run action class
  ///
  //****************************************************************************
  class RunAction : public G4UserRunAction
  {
    public:
      RunAction();
      ~RunAction() override;

      // methods from base class
      void BeginOfRunAction(const G4Run* run) override;
      void   EndOfRunAction(const G4Run* run) override;

    private:
      // data members
      G4Timer* fTimer = nullptr;

  };

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

