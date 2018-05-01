#include "Analysis.hh"

//User initialization
#include "LYSimDetectorConstruction.hh"
#include "LYSimPhysicsList.hh"

//User action
#include "LYSimPrimaryGeneratorAction.hh"
#include "LYSimRunAction.hh"
#include "LYSimTrackingAction.hh"
#include "LYSimSteppingAction.hh"
#include "LYSimEventAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"


//Always include VI, UI
//#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
//#endif
//#ifdef G4UI_USE
#include "G4UIExecutive.hh"
//#endif

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{

    // Construct the default run manager
    //
    G4RunManager * runManager = new G4RunManager;

    G4cout << "[LYSim] 11111" << G4endl;
    // Set mandatory initialization classes
    //
    // Detector construction
    LYSimDetectorConstruction* detector= new LYSimDetectorConstruction();
    //if (argc > 1) detector->SetDetectorType(std::atoi(argv[1]));
    //else detector->SetDetectorType(0);

    runManager->SetUserInitialization(detector);
    G4cout << "[LYSim] 22222" << G4endl;
    // Physics list
    LYSimPhysicsList *physlist = new LYSimPhysicsList();
    //if (detector->GetDetectorType()==1) physlist->SetHadProc(true);
    runManager-> SetUserInitialization(physlist);
    G4cout << "[LYSim] 33333" << G4endl;

    //Construct Analysis class
    Analysis::GetInstance()->SetDetector(detector);
    std::string outFileName= "Analysis";
    Analysis::GetInstance()->SetOutputFile(outFileName+".txt");
    Analysis::GetInstance()->SetROOTFile(outFileName+".root");
    LYSimPrimaryGeneratorAction* genaction = new LYSimPrimaryGeneratorAction(detector);
    Analysis::GetInstance()->SetGeneratorAction(genaction);

    // Set user action classes
    //    
    // Primary generator action
    runManager->SetUserAction(genaction);
    G4cout << "[LYSim] 44444" << G4endl;
    // Run action
    runManager->SetUserAction(new LYSimRunAction(detector));
    // Event action
    runManager->SetUserAction(new LYSimEventAction());
    // Tracking action
    runManager->SetUserAction(new LYSimTrackingAction());
    // Stepping action
    runManager->SetUserAction(new LYSimSteppingAction());

    // Initialize G4 kernel
    //
    runManager->Initialize();
    G4cout << "[LYSim] 55555" << G4endl;
    //#ifdef G4VIS_USE
    // Initialize visualization
    //G4VisManager* visManager = new G4VisExecutive();
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
    //#endif

    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc == 3) {
        G4cout << "[LYSim] argv[2] is " << argv[2] <<G4endl;
        if(std::string(argv[2]) == "-novis") {
            G4UIExecutive* ui = new G4UIExecutive(argc, argv);
            ui->SessionStart();
            UImanager->ApplyCommand("/control/execute init.mac");
            delete ui;
        }
        else {
            G4cout << "[LYSim] run in batch mode" <<G4endl;
            // batch mode
            G4String command = "/control/execute ";
            G4String fileName = argv[2];
            UImanager->ApplyCommand(command+fileName);
        }
    }
    else if (argc == 4) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[2];
        outFileName = argv[3];
        G4cout << "[LYSim] outFileName tag is " << outFileName <<G4endl;
        Analysis::GetInstance()->SetOutputFile(outFileName+".txt");
        Analysis::GetInstance()->SetROOTFile(outFileName+".root");
        UImanager->ApplyCommand(command+fileName);
    }
    else {
        // interactive mode : define UI session
        //#ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        //#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac"); 
        //#else
        //UImanager->ApplyCommand("/control/execute init.mac"); 
        //#endif
        ui->SessionStart();
        delete ui;
        //#endif
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted 
    // in the main() program !

    //#ifdef G4VIS_USE
    delete visManager;
    //#endif
    delete runManager;

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
