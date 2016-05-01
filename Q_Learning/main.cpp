#include "mat.h"
#include "rand.h"
#include <math.h>
#include <iostream>
#include <algorithm>    // std::max
#include <ctime>

#define Row 15                  // velocity
#define Col 41                  // position
#define Learning_Rate 0.05      // Learn Rate
#define RR 0.5                  // Discounting Parameter
#define e 0.9                   // For the e-greedy algorithm
#define Episode 300            // Training times
#define TEST 0                  // 1 - on // 0 - off //
using namespace std;

int pick_action(int curr_position, int curr_velocity, Matrix Reverse, Matrix Coast, Matrix Forward) {


    // There are 3 choice (-1, 0, +1)
    double R = Reverse.get(curr_velocity, curr_position);
    double C = Coast.get(curr_velocity, curr_position);
    double F = Forward.get(curr_velocity, curr_position);

    // R > C > F
    if (R > C && C > F) return choose(e) ? -1 : 0;
    // R > F > C
    else if (R > F && F > C) return choose(e) ? -1 : 1;
    // R > F = C
    else if (R > F && F == C) {
        if (choose(e)) return -1;
        else return choose(0.5) ? 0 : 1;
    }

    // C > R > F
    else if (C > R && R > F) return choose(e) ? 0 : -1;
    // C > F > R
    else if (C > F && F > R) return choose(e) ? 0 : 1;
    // C > F = R
    else if (C > F && F == R) {
        if (choose(e)) return 0;
        else return choose(0.5) ? -1 : 1;
    }

    // F > R > C
    else if (F > R && R > C) return choose(e) ? 1 : -1;
    // F > C > R
    else if (F > C && C > R) return choose(e) ? 1 : 0;
    // F > R = C
    else if (F > R && R == C) {
        if (choose(e)) return 1;
        else return choose(0.5) ? -1 : 0;
    }

    else {
        while(1) {
            if (choose(0.33)) return -1;
            if (choose(0.33)) return 0;
            if (choose(0.33)) return 1;
        }
    }
    
    


}

double calc_reward(int curr_position, int curr_velocity, int action) {

    //cout << "Index: " << curr_velocity << endl;
    double real_position, real_velocity;
    real_position = -1.2 + (0.05 * curr_position);
    real_velocity = -0.07 + (0.01 * curr_velocity);
    //cout << "Old: " << real_position << endl;
    //cout << "Action: " << action << endl;
    //cout << "Value: " << real_velocity << endl;
    
    // Now calculate new position applied with the action
    double new_velocity = real_velocity + (0.001 * action) + cos(3 * real_position) * (-0.0025);
    double new_position = real_position + new_velocity;    

    //cout << "New: " << new_position << endl;

    return new_position >= 0.8 ? 1 : -1;
}

double Qsa_by_action(int action, int curr_position, int curr_velocity, Matrix Reverse, Matrix Coast, Matrix Forward) {

    switch(action) {

        case -1:
            return Reverse.get(curr_velocity, curr_position);
            break;

        case 0:
            return Coast.get(curr_velocity, curr_position);
            break;

        case 1:
            return Forward.get(curr_velocity, curr_position);
            break;
    }

    return -1;

}

int main()
{
    const clock_t begin_time = clock();
    initRand();  

    // Three action Matrix
    Matrix Reverse(Row, Col, "Reverse");
    Reverse.constant(0);

    Matrix Coast(Row, Col, "Coast");
    Coast.constant(0);

    Matrix Forward(Row, Col, "Forward");
    Forward.constant(0);


    // Start each Episode
    for (int i = 0 ; i < Episode; i++) {

    // First, randomly pick a state (velocity and position)
    int curr_position = randMod(41);
    int curr_velocity = randMod(15);
    //int curr_velocity = 7; 
    double real_position = -1.2 + (0.05 * curr_position);
    double real_velocity = -0.07 + (0.01 * curr_velocity);
    
    


    
    while (1) {
        if (TEST) cout << "=================" << endl;
        // Select a action by E-Greedy algorithm
        int action = pick_action(curr_position, curr_velocity, Reverse, Coast, Forward);
        if (TEST) cout << "Action take: " << action << endl;

        // Calculate the reward with that certain action
        double reward = calc_reward(curr_position, curr_velocity, action);
        if (TEST) cout << "Reward: " << reward << endl;
        


        // Update Q(s,a)
        if (TEST) cout << "Start vel index: " << curr_velocity << endl;
        if (TEST) cout << "Velocity: " << real_velocity << endl;
        if (TEST) cout << "Start pos index: " << curr_position << endl;
        if (TEST) cout << "Position: " << real_position << endl;



        double new_velocity = real_velocity + (0.001 * action) + cos(3 * real_position) * (-0.0025);
        double new_position = real_position + new_velocity; 
        if (TEST) cout << "Original velocity: " << real_velocity << endl;
        if (TEST) cout << "New Velocity: " << new_velocity << endl;
        if (TEST) cout << "New Position: " << new_position << endl;


        if (new_position >= 0.8 || new_position <= -1.2 ) break;
        if (new_velocity > 0.07 || new_velocity < -0.07) break;

        double vel_index_temp;
        double pos_index_temp;

        int new_vel_index;
        int new_pos_index;

        real_position = new_position;
        real_velocity = new_velocity;

    
        // Remove after .2
        new_position = ((float)((int)(new_position*100)))/100;
        new_velocity = ((float)((int)(new_velocity*100)))/100;
    
        // mapping to index
        pos_index_temp = (new_position + 1.2) / 0.05;
        vel_index_temp = (new_velocity + 0.07) / 0.01;

        // make index more specific
        new_pos_index = (int)(pos_index_temp * 100 + .5) / 100. ; 
        new_vel_index = (int)(vel_index_temp * 100 + .5) / 100. ; 
        if (TEST) cout << "New Position index: " << new_pos_index << endl;
        if (TEST) cout << "New Velocity index: " << new_vel_index << endl;



        // Now calculate new position applied with the action
        double Q_s_a;
        // = Qsa_by_action(action, curr_position, curr_velocity, Reverse, Coast, Forward);
        double New_Q_s_a = Qsa_by_action(action, curr_position, curr_velocity, Reverse, Coast, Forward);
    
        switch (action) {
            case -1:
                Q_s_a = Reverse.get(curr_velocity, curr_position);
                break;

            case 0:
                Q_s_a = Coast.get(curr_velocity, curr_position);
                break;

            case 1:
                Q_s_a = Forward.get(curr_velocity, curr_position);
                break;
        }


    
        switch (action) {
            case -1:
                Reverse.set(curr_velocity, curr_position, Q_s_a + (Learning_Rate * (reward + RR * New_Q_s_a - Q_s_a)));
                break;

            case 0:
                Coast.set(curr_velocity, curr_position, Q_s_a + (Learning_Rate * (reward + RR * New_Q_s_a - Q_s_a)));
                break;

            case 1:
                Forward.set(curr_velocity, curr_position, Q_s_a + (Learning_Rate * (reward + RR * New_Q_s_a - Q_s_a)));
                break;
        }
    
        curr_velocity = new_vel_index;
        curr_position = new_pos_index;
    
    } // end while
    }
    //Forward.print();
    //Coast.print();
    //Reverse.print();
    if (TEST) cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    return 0;
}


