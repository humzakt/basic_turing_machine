#include "TM_TAPE.h" 
#include <math.h>

int charcter = 'a';
TuringMachineTape maintape;
TuringMachineTape temp;
TuringMachineTape temp_cp;
TuringMachineTape processing;

void Produce(TuringMachineTape &newtape, TuringMachineTape &tape){
    while(tape.read() != BLANK_SYMBOL){
        int a = tape.read();
        int i = 0;
        while(i<3) {    
            newtape.write(a);
            newtape.right();
            i++;
        }
        tape.right();
    }    
}

void Make(TuringMachineTape &newtape, TuringMachineTape &tape){
    while(tape.read() != BLANK_SYMBOL){
        int a = tape.read();
        int i = 0;
        while(i<2) {    
            newtape.write(a);
            newtape.right();
            i++;
        }
        tape.right();
    }
}

void Process(TuringMachineTape &temp,TuringMachineTape &temp_cp,TuringMachineTape &processing,TuringMachineTape &maintape) {
    int main_count = 0; 
    int process_count = 0; 
    processing.write(charcter);
    processing.right();
    TuringMachineUtility::rewind(&temp_cp);
    Produce(processing,temp_cp);
    TuringMachineUtility::rewind(&temp);
    Produce(processing,temp);
    TuringMachineUtility::rewind(&temp);
    temp_cp.write(charcter);
    temp_cp.right();
    Make(temp_cp,temp);
    temp.write(charcter);

    // Count the number of 'a' symbols on the main tape
    while (maintape.read() != BLANK_SYMBOL) {
        if (maintape.read() == charcter) {
            main_count++;
        }
        maintape.right();
    }

    // Count the number of 'a' symbols on the processing tape
    while (processing.read() != BLANK_SYMBOL) {
        if (processing.read() == charcter) {
            process_count++;
        }
        processing.right();
    }

    // Compare the counts and accept or reject the input accordingly
 if (main_count == pow(cbrt(main_count),3) && main_count != 0) {
    TuringMachineTape::accept();
} else {
    TuringMachineTape::reject();
}

}

void Insert(TuringMachineTape &temp,TuringMachineTape &temp_cp,TuringMachineTape &processing,TuringMachineTape &maintape) {
TuringMachineUtility::insertBegin(&maintape);
TuringMachineUtility::insertBegin(&temp);
TuringMachineUtility::insertBegin(&temp_cp);
TuringMachineUtility::insertBegin(&processing);
}

void BothMove(TuringMachineTape &maintape,TuringMachineTape &processing) {
maintape.right();
processing.right();
}

int main(int argc, char** argv) {
std::istream* input = &std::cin;
TuringMachineTape maintape ;
TuringMachineTape temp;
TuringMachineTape temp_cp;
TuringMachineTape processing;
int charcter = 'a';

// Insert begin symbols at the beginning of each tape
Insert(temp,temp_cp,processing,maintape);

while (true) {
    // Move the head of each tape to the right
    BothMove(maintape,processing);

    // If we reach a blank symbol on the main tape and a non-blank symbol on the processing tape, reject the input
    if (maintape.read() == BLANK_SYMBOL && processing.read() != BLANK_SYMBOL) {
        TuringMachineTape::reject();
    } 
    // If we reach a blank symbol on both tapes, accept the input
    else if (maintape.read() == BLANK_SYMBOL && processing.read() == BLANK_SYMBOL) {
        TuringMachineTape::accept();
    }
    // If we reach a non-blank symbol on the main tape and a blank symbol on the processing tape, process the input
    else if (maintape.read() != BLANK_SYMBOL && processing.read() == BLANK_SYMBOL) {
        Process(temp,temp_cp,processing,maintape);
    }
}
return 0;
}