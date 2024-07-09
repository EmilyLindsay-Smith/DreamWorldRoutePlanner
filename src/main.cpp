#include <iostream>
using namespace std;

#include "CLI.h"

int main(){
    CLI* cli = new CLI(100);
    cli->Introduce(); //introduces DreamWorld to the user
    cli->SetUpLandscape(); //creates DreamWorld and its road network
    cli->SelectActivity(); // Displays the available activities and calls their methods

  return 0;  
}