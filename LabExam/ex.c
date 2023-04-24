#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int MAX_CUSTOMERS = 10;
const int MAX_RESOURCES = 5;

int available[MAX_RESOURCES];
int maximum[MAX_CUSTOMERS][MAX_RESOURCES];
int allocation[MAX_CUSTOMERS][MAX_RESOURCES];
int need[MAX_CUSTOMERS][MAX_RESOURCES];

mutex mtx;
condition_variable cv;

bool is_safe_state(vector<int> request, int cid) {
    vector<int> work(available, available + MAX_RESOURCES);
    vector<bool> finish(MAX_CUSTOMERS, false);

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] -= request[i];
        allocation[cid][i] += request[i];
        need[cid][i] -= request[i];
        finish[cid] = true;
    }

    int count = 0;
    while (count < MAX_CUSTOMERS) {
        bool found = false;
        for (int i = 0; i < MAX_CUSTOMERS; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    found = true;
                    finish[i] = true;
                    count++;
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                }
            }
        }
        if (!found) {
            for (int i = 0; i < MAX_RESOURCES; i++) {
                work[i] += request[i];
                allocation[cid][i] -= request[i];
                need[cid][i] += request[i];
            }
            return false;
        }
    }
    return true;
}

bool req_resource(int cid, vector<int> request) {
    unique_lock<mutex> lck(mtx);
    if (cid < 0 || cid >= MAX_CUSTOMERS) {
        return false;
    }
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[cid][i] || request[i] > available[i]) {
            return false;
        }
    }
    if (!is_safe_state(request, cid)) {
        return false;
    }
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[cid][i] += request[i];
        need[cid][i] -= request[i];
    }
    return true;
}

bool release_resource(int cid, vector<int> release) {
    unique_lock<mutex> lck(mtx);
    if (cid < 0 || cid >= MAX_CUSTOMERS) {
        return false;
    }
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (release[i] > allocation[cid][i]) {
            return false;
        }
    }
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] += release[i];
        allocation[cid][i] -= release[i];
        need[cid][i] += release[i];
    }
    cv.notify_all();
    return true;
}

void customer_thread(int cid) {
    while (true) {
        vector<int> request(MAX_RESOURCES);
        for (int i = 0; i < MAX_RESOURCES; i++) {
            request[i] = rand() % (need[cid][i] + 1);
        }
        if (req_resource(cid, request)) {
            cout << "Customer " << cid << " acquired resources: ";
            for (int i = 0; i < MAX_RESOURCES; i++) {
                cout << request[i] << " ";
            }
            cout << endl;
            this_thread::sleep_for(chrono::seconds(1));
            vector<int> release(MAX_RESOURCES);
            for (int i = 0; i < MAX_RESOURCES; i++) {
                release[i] = rand() % (allocation[cid][i] + 1);
            }
            if (release_resource(cid, release)) {
                cout << "Customer " << cid << " released resources: ";
                for (int i = 0; i < MAX_RESOURCES; i++) {
                    cout << release[i] << " ";
                }
                cout << endl;
            }
        } else {
            cout << "Customer " << cid << " failed to acquire resources." << endl;
            unique_lock<mutex> lck(mtx);
            cv.wait