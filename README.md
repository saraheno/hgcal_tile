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
  ./LYSIM photontest.mac [-novis] [output_filename] [root_filename}

    (if running without -novis
         /run/beamOn 5

  look at Analysis.root 