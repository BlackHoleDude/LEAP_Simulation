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
/// \file ScintHit.hh
/// \brief Definition of the ScintHit class

#ifndef ScintHit_h
#define ScintHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Threading.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace leap
{

  //****************************************************************************
  /// Scintimeter hit class
  ///
  /// It defines data members to store the the energy deposit and track lengths
  /// of charged particles in a selected volume:
  //****************************************************************************
  class ScintHit : public G4VHit
  {
    public:
      ScintHit();
      ScintHit(const ScintHit&) = default;
      ~ScintHit() override;

      // operators
      ScintHit& operator=(const ScintHit&) = default;
      G4bool operator==(const ScintHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      // methods from base class
      virtual void Draw()  override;
      virtual void Print() override;

      // methods
      void SetID ( G4int val ) { fID = val; }
      G4int GetID() const { return fID; }

      void SetTime ( G4double sec ) { fTime = sec; }
      G4double GetTime() const { return fTime; }

      void AddEdep ( G4double de, G4double bde, G4double vde );
      G4double GetEdep()     const { return fEdep; }
      G4double GetBirkEdep() const { return fBirkEdep; }
      G4double GetVisEdep()  const { return fVisEdep; }

      void SetPos ( G4ThreeVector xyz ) { fPos = xyz; }
      G4ThreeVector GetPos() const { return fPos; }

      void SetLogV ( G4LogicalVolume* vol ) { fPLogV = vol; }
      const G4LogicalVolume* GetLogV() const { return fPLogV; }

      void SetType ( G4String& mat ) { fType = mat; }
      const G4String& GetType() const { return fType; }
      
      void SetDetType ( G4int det ) { fDetType = det; }
      G4int GetDetType() const { return fDetType; }
        
    private:
      // data members
      G4int    fID = 0;
      G4int    fDetType = 0;

      G4double fTime = 0.;

      G4ThreeVector fPos;

      G4double fEdep = 0.;
      G4double fBirkEdep = 0.;    ///< Energy deposit after birks correction in the sensitive volume
      G4double fVisEdep = 0.;     ///< Energy deposit GetVisibleEnergyDeposit in the  sensitive volume

      const G4LogicalVolume* fPLogV = nullptr;

      G4String fType = "";

  };

  //****************************************************************************
  //
  //****************************************************************************
  using ScintHitsCollection = G4THitsCollection<ScintHit>;

  extern G4ThreadLocal G4Allocator<ScintHit>* ScintHitAllocator;

  //****************************************************************************
  // Operators
  //****************************************************************************
  inline void* ScintHit::operator new(size_t)
  {
    if (!ScintHitAllocator) {
      ScintHitAllocator = new G4Allocator<ScintHit>;
    }
    return (void *) ScintHitAllocator->MallocSingle();
  }

  inline void ScintHit::operator delete(void *hit)
  {
    if (!ScintHitAllocator) {
      ScintHitAllocator = new G4Allocator<ScintHit>;
    }
    ScintHitAllocator->FreeSingle((ScintHit*) hit);
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  inline void ScintHit::AddEdep(G4double de, G4double bde, G4double vde) {
    fEdep += de; 
    fBirkEdep += bde; 
    fVisEdep += vde;
  }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
