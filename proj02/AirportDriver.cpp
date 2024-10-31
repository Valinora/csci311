/***********************************************
************CSCI-311-PROJECT-2-V-2071***********
************************************************
*******CODE-CHECKER-STARTING-ALIGNMENT**********
************************************************
*************CONTROL-NUMBER-XA-72***************
************************************************
**REPORT-GENERATION-MODE-AUTO_SYNC-EXCEPTION-2**
************************************************
*****************DATETIME-SYS*******************
************************************************/

// G1_EXCEPTION: Only produce your code as directed in Section A, B, C, and
// D1_EXCEPTION. G2_EXCEPTION: Do not write anything at the other places in this
// file. D1_EXCEPTION: Put you names here (on this line): Colin Jamison

/***********************************************
*************SECTION-A-HEADERS******************
************************************************/
// SECTION_A_START: put your header files here using the include directive.
// G3_EXCEPTION: You can also declare using standard namespace if you like, but
// do not use any global variable or method.

#include <iostream>
#include <vector>

using namespace std;

// SECTION_A_END: Section A ends here.
/***********************************************
*************SECTION-A-HEADERS-END**************
************************************************/

/***********************************************
*************SECTION-B-CLASSES******************
************************************************/
// SECTION_B_START: put all your classes definitions here.

class Plane {
   public:
    enum DIRECTION {
        ARRIVING,
        DEPARTING,
    };

    unsigned int entrance_time;
    DIRECTION dir;
    int id;
    int priority;

    Plane() : entrance_time(0), dir(ARRIVING), id(0), priority(0) {}

    Plane(int entrance_time, DIRECTION dir, int id, int priority) {
        this->entrance_time = entrance_time;
        this->dir = dir;
        this->id = id;
        this->priority = priority;
    }

    int true_priority() const {
        // Something that combines priority, direction, and entrance_time, somehow.
        return this->priority;
    }

    friend istream& operator>>(istream& iss, Plane& plane) {
        // Parse string and return a Plane object
        // Format: "entrance_time dir id priority"
        // Example: "0 ARRIVING 0 0"
        unsigned int entrance_time;
        int id, priority;
        string dir_str;
        DIRECTION dir;

        if (!(iss >> entrance_time >> dir_str >> id >> priority)) {
            throw "Invalid input string";
    }

        if (dir_str == "arriving") {
            dir = ARRIVING;
        } else if (dir_str == "departing") {
            dir = DEPARTING;
        } else {
            throw "Invalid direction";
        }

        plane = Plane(entrance_time, dir, id, priority);
        return iss;
    }

    friend ostream& operator<<(ostream& os, const Plane& plane) {
        string dir = plane.dir == ARRIVING ? "arriving" : "departing";
        os << plane.entrance_time << " " << dir << " " << plane.id << " " << plane.priority;
        return os;
    }

    bool operator>(const Plane& other) { return this->true_priority() > other.true_priority(); }
    bool operator<(const Plane& other) { return this->true_priority() < other.true_priority(); }
};

class MinHeap {
   public:
    int size() { return this->array.size(); }
    bool empty() { return this->size() == 0; }
    void push(Plane plane) {
        this->array.push_back(plane);
        upward_heapify(array.size() - 1);
    }
    Plane pop() {
        swap(this->array[0], this->array[this->array.size() - 1]);
        Plane temp = this->array.back();
        this->array.pop_back();
        downward_heapify(0);
        return temp;
    }
    const Plane& peek() { return this->array[0]; }

   private:
    vector<Plane> array;
    void upward_heapify(int idx);
    void downward_heapify(int idx);
};

class InputHandler {
   public:
    InputHandler();
    Plane read_line();
};

class Simulation {
   private:
    InputHandler input_hndl;
    MaxHeap planes;
    int time_step;

   public:
    // Dependency Injection Lite
    Simulation(InputHandler input_hndl) {
        this->input_hndl = input_hndl;
        this->time_step = 0;
    }
    void step() {
        // Get all aircraft entering simulation
        // TODO: Find best way of getting all lines that match our current timestep
        // Buffered Readers?

        // if num_entering == 0 && size(planes) == 0
        //     this->timestep++;
        //     return;

        // insert entering planes into heap
        cout << "Time step " << this->time_step << endl;
        cout << "\tEntering simulation" << endl;
        // for plane : entering:
        //   cout << "\t\t" << plane << endl;
        //  this->planes.insert(plane);

        // pop two planes from the heap
        cout << "\tRunway A" << endl;
        // if (plane_a)
        // cout << "\t\t" << plane_a << endl;
        cout << "\tRunway B" << endl;
        // if (plane_b)
        // cout << "\t\t" << plane_b << endl;

        this->time_step++;
    }
};

// SECTION_B_END: Section B ends here.
/***********************************************
*************SECTION-B-CLASSES-END**************
************************************************/

/***********************************************
*************SECTION-C-MAIN-FUNCTION************
************************************************/
// SECTION_C_START: write your main function here.

int main() {
    // High Level Overview:
    // .. initialization ..
    // while should_continue:
    //   receive_input()
    //   step()
    //   print_state()
}

// SECTION_C_END: Section C ends here.
/***********************************************
************SECTION-C-MAIN-FUNCTION-END*********
************************************************/

/***********************************************
**************PLAGIARISM-RTNG-PRTCL-C***********
****************GEN-AI-RTNG-PRTCL-K*************
*********LOOP-CS_SEC-CS_CHR-STU_R_R_RFR*********
*****************DICT-A-ENTRY-2071**************
***************ORI-KTIAN@CSUCHICO.EDU***********
************************************************/

/***********************************************
*********CODE-CHECKER-ENDING-ALIGNMENT**********
************************************************/
