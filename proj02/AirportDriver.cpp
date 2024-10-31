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

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
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
        // Format: "entrance_time id dir priority"
        // Example: "0 0 arriving  0"
        unsigned int entrance_time;
        int id, priority;
        string dir_str;
        DIRECTION dir;

        if (!(iss >> entrance_time >> id >> dir_str >> priority)) {
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
        os << plane.entrance_time << " " << plane.id << " " << dir << " " << plane.priority;
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
        if (this->empty()) {
            throw "Heap is empty";
        }
        swap(this->array[0], this->array[this->array.size() - 1]);
        Plane temp = this->array.back();
        this->array.pop_back();
        downward_heapify(0);
        return temp;
    }
    const Plane& peek() { return this->array[0]; }

    string dump() {
        stringstream str;
        str << "Heap: { ";
        for (auto plane : this->array) {
            str << plane << ", ";
        }
        str << "}";
        return str.str();
    }

   private:
    vector<Plane> array;
    void upward_heapify(int idx) {
        if (idx == 0) return;
        int parent = (idx - 1) / 2;
        if (this->array[idx] < this->array[parent]) {
            swap(this->array[idx], this->array[parent]);
            upward_heapify(parent);
        }
    }
    void downward_heapify(int idx) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;
        if (left < this->size() && this->array[left] < this->array[smallest]) {
            smallest = left;
        }
        if (right < this->size() && this->array[right] < this->array[smallest]) {
            smallest = right;
        }
        if (smallest != idx) {
            swap(this->array[idx], this->array[smallest]);
            downward_heapify(smallest);
        }
    }
};

class Simulation {
   private:
    MinHeap planes;
    int time_step;
    int expected;

   public:
    Simulation(int expected) {
        this->time_step = 0;
        this->expected = expected;
    }
    void step() {
        // Get all aircraft entering simulation at current timestep
        vector<Plane> entering;
        char next = cin.peek();
        if (next == '\n') {
            cin.ignore();
        }
        next = cin.peek();
        while (isdigit(next) && next - '0' == this->time_step) {
            Plane plane;
            cin >> plane;
            entering.push_back(plane);
        }

        if (entering.size() == 0 && this->planes.empty()) {
            this->time_step++;
            return;
        }

        cout << "Time step " << this->time_step << endl;
        cout << "\tEntering simulation" << endl;

        // insert entering planes into heap, maintaining input order.
        for (auto plane : entering) {
            cout << "\t\t" << plane << endl;
            this->planes.push(plane);
        }

        // pop two planes from the heap
        Plane plane_a = this->planes.pop();
        Plane plane_b = this->planes.pop();
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

    int planes_expected;
    int entered = 0;
    cin >> planes_expected;

    cout << "Planes expected: " << planes_expected << endl;

    while (entered < planes_expected) {
        char next = cin.peek();
        if (next == '\n') {
            cin.ignore();
            continue;
        }

        if (next != '0') {
            break;
        }

        Plane plane;
        cin >> plane;
        cout << "Plane: " << plane << endl;
        entered++;
    }
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
