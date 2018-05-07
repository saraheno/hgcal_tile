# HGcal Tile
GEANT4-based simulation of CE-H HGCal optical tile

## compiling

  git clone https://github.com/saraheno/hgcal_tile.git

  cd hgcal_tile

  mkdir build

  cd build 

  cmake -DWITH_GEANT4_UIVIS=ON -DGeant4_DIR=$G4LIB ../TILE

  make

  ./LYSim 

## running
  interactivly try

  /tracking/verbose 1

  /run/beamOn 1

  at the prompt. 
 
  ./LYSim -m photontest.mac

do the commands in photontest.mac

  look at Analysis.root 