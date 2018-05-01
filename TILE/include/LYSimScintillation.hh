#ifndef LYSimScintillation_h
#define LYSimScintillation_h

#include <G4Scintillation.hh>

#define G4DEBUG_SCINTILLATION 1

class LYSimScintillation : public G4Scintillation
{
public:
    LYSimScintillation(const G4String &processName="Scintillation", G4ProcessType type=fElectromagnetic);
    virtual ~LYSimScintillation();

    G4VParticleChange* PostStepDoIt(const G4Track& aTrack, const G4Step&  aStep);
    
};

#endif
