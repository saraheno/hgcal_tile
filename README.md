# HGcal Tile
GEANT4-based simulation of CE-H HGCal optical tile

## compiling

  git clone https://github.com/saraheno/hgcal_tile.git

  cd hgcal_tile

  mkdir build

  cd build 

  cmake -DWITH_GEANT4_UIVIS=ON -DGeant4_DIR=$G4LIB ../UMDSRDGEStudy

  make

  cp -r ../UMDSRDGEStudy-utils/* .

  ./LYSim 

## running
  at the prompt. do the commands in photontest.mac
  look at Analysis.root 