#include <bits/stdc++.h>
#include <thread>
#include <chrono>
using namespace std;

class Help {
public:
    void game() {
        cout << "###########    ###########    #         #    ###########" << endl;
        cout << "#          #    #         #    # #     # #    #          " << endl;
        cout << "#          #    #         #    #  #   #  #    #          " << endl;
        cout << "#          #    #         #    #   # #   #    #          " << endl;
        cout << "#     #####    ###########    #    #    #    ######     " << endl;
        cout << "#         #    #         #    #    #    #    #          " << endl;
        cout << "#         #    #         #    #    #    #    #          " << endl;
        cout << "#         #    #         #    #    #    #    #          " << endl;
        cout << "###########    #         #    #    #    #    ###########" << endl;
    }

    void start() {
        cout << "###########    ###########    ###########    ###########    ###########" << endl;
        cout << "#          #    #     #     #    #         #    #         #    #     # " << endl;
        cout << "#          #    #     #     #    #         #    #         #    #     # " << endl;
        cout << "#          #    #     #     #    #         #    #         #    #     # " << endl;
        cout << "###########    #     #     #    ###########    ###########    #     # " << endl;
        cout << "          #    #     #     #    #         #    #      #     #    #     " << endl;
        cout << "          #    #     #     #    #         #    #       #    #    #     " << endl;
        cout << "          #    #     #     #    #         #    #        #   #    #     " << endl;
        cout << "###########    #     #     #    #         #    #         #   #    #    " << endl;
    }

    void over() {
        cout << "###########    #         #    ###########    ###########" << endl;
        cout << "#         #    #         #    #          #    #         #" << endl;
        cout << "#         #    #         #    #          #    #         #" << endl;
        cout << "#         #    #         #    #          #    #         #" << endl;
        cout << "#         #    #       #      ###########    ###########" << endl;
        cout << "#         #    #     #        #          #    #      #  " << endl;
        cout << "#         #    #   #          #          #    #       # " << endl;
        cout << "#         #    # * *          #          #    #        #" << endl;
        cout << "###########    #     #        ###########    #         #" << endl;
    }

    void win() {
        cout << "#     #    #    #     #" << endl;
        cout << "#     #    #    ##    #" << endl;
        cout << "#     #    #    # #   #" << endl;
        cout << "#  #  #    #    #  #  #" << endl;
        cout << "# # # #    #    #   # #" << endl;
        cout << "##   ##    #    #    ##" << endl;
        cout << "#     #    #    #     #" << endl;
    }

    void lost() {
        cout << "#         #######    #######    #######" << endl;
        cout << "#         #     #    #          #   #" << endl;
        cout << "#         #     #    #          #   #" << endl;
        cout << "#         #     #    #######    #   #" << endl;
        cout << "#         #     #          #    #   #" << endl;
        cout << "#         #     #          #    #   #" << endl;
        cout << "#######   #######    #######    #   #" << endl;
    }
};

int main() {
    srand(time(0));
    Help ph;
    ph.game();
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "\n\n\n";
    ph.start();
    this_thread::sleep_for(chrono::seconds(1));

    int n;
    cout << "Enter grid size: ";
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n, 0));

    cout << "Enter the number of bombs: ";
    int b; cin >> b;

    int c = 0;
    int k = n - 1;
    while (c != b) {
        int r = rand() % n;
        int l = rand() % n;
        if (a[r][l] >= 100) continue; // prevent double bombs
        a[r][l] = 100;

        // Add numbers around bomb
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                int nr = r + dr, nc = l + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && a[nr][nc] < 100) {
                    a[nr][nc]++;
                }
            }
        }
        c++;
    }

    vector<vector<string>> na(n, vector<string>(n, "|__|"));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << setw(5) << na[i][j];
        cout << endl;
    }

    int m = 0, point = 0;
    while (m != n * n) {
        int y, z, ch;
        cout << "Enter row: "; cin >> y; y--;
        cout << "Enter column: "; cin >> z; z--;
        cout << "Enter choice 1-play 2-flag 3-doubt 4-exit: "; cin >> ch;

        switch (ch) {
            case 1:
                if (a[y][z] >= 100) {
                    ph.game();
                    this_thread::sleep_for(chrono::milliseconds(200));
                    cout << endl << endl;
                    ph.over();
                    this_thread::sleep_for(chrono::seconds(1));
                    goto endgame;
                } else {
                    na[y][z] = " " + to_string(a[y][z]) + " ";
                }
                break;
            case 2:
                na[y][z] = "|> ";
                if (a[y][z] >= 100) point++;
                break;
            case 3:
                na[y][z] = "? ";
                break;
            case 4:
                ph.game();
                this_thread::sleep_for(chrono::milliseconds(200));
                cout << endl << endl;
                ph.over();
                this_thread::sleep_for(chrono::seconds(1));
                goto endgame;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << setw(5) << na[i][j];
            cout << endl;
        }
        m++;
    }

endgame:
    cout << endl << endl;
    if (point >= b) {
        this_thread::sleep_for(chrono::milliseconds(500));
        ph.win();
    } else {
        this_thread::sleep_for(chrono::milliseconds(500));
        ph.lost();
    }
    cout << "Points: " << point << endl;
    return 0;
}
