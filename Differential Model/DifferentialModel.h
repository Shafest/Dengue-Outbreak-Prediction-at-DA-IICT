using namespace std;
void differentialModel() {    
    double A = 8;               // Constant Recruitment Rate of Vector Population
    double totalCases = 0;      // Intially Total Number of Cases to be 0

    // Initial Values
    double Sv0 = 10;             // Initial No. of Susceptible Vector
    double Sh0 = 1600;          // Initial No. of Susceptible Host
    double Iv0 = 1;             // Initial No. of Infected Vector
    double Ih0 = 0;             // Initial No. of Infected Host
    double R0 = 0;              // Initial No. of Recovered Patients

    // Rates
    double Dv = 1.0/12;         // Death Rate of Vector
    double Dh = 0;              // Death Rate of Host
    double Bv = 0.000045;       // Transmission Rate Host -> Vector
    double Bh = 0.00097;        // Transmission Rate Vector -> Host
    double r = 0.03;            // Recovery Rate of Patients

    cout << endl << endl << Dv << endl << endl;

    // DIFFERENTIAL EQUATIONS
    // dSv/dt = A - Bv * prev_Sv * prev_Ih - Dv * prev_Sv;
    // dSh/dt = -BhShIv;
    // dIv/dt = BvSvIh - dvIv;
    // dIh/dt = BhShIv - rIh;
    // dR/dt = +rIh;

    int dt = 1;
    int lengthOfSeason = 80;
    
    vector<double> Sv;
    vector<double> Sh;
    vector<double> Iv;
    vector<double> Ih;
    vector<double> R;
    
    // Pushing Initial Values into Vector Containers
    Sv.push_back(Sv0);
    Sh.push_back(Sh0);
    Iv.push_back(Iv0);
    Ih.push_back(Ih0);
    R.push_back(R0);

    cout << endl << endl;

    for(int day = 1; day <= (int)lengthOfSeason; day++) {
        double prev_Sv = Sv.back();
        double prev_Sh = Sh.back();
        double prev_Iv = Iv.back();
        double prev_Ih = Ih.back();
        double prev_R = R.back();

        // dSv/dt = A - Bv * prev_Sv * prev_Ih - Dv * prev_Sv;
        // (next_Sv - prev_Sv) / dt = A - Bv * prev_Sv * prev_Ih - Dv * prev_Sv; 
        // next_Sv = prev_Sv + (A - Bv * prev_Sv * prev_Ih - Dv * prev_Sv) * dt;
        double next_Sv = prev_Sv + (A - Bv*prev_Sv*prev_Ih - Dv*prev_Sv) * dt;
        Sv.push_back(next_Sv);

        // dSh/dt = -BhShIv;
        // (next_Sh - prev_Sh) / dt = - Bh0 * prev_Sh * prev_Iv;
        // next_Sh = prev_Sh - Bh0 * prev_Sh * prev_Iv * dt;
        double next_Sh = prev_Sh - Bh * prev_Sh * prev_Iv * dt;
        Sh.push_back(next_Sh);

        // dIv/dt = BvSvIh - DvIv;
        // (next_Iv - prev_Iv) / dt = Bv0 * Sv0 * prev_Ih - Dv0 * prev_Iv;
        // next_Iv = prev_IV + (Bv0 * Sv0 * prev_Ih - Dv0 * prev_Iv) * dt;
        double next_Iv = prev_Iv + (Bv * prev_Sv * prev_Ih - Dv * prev_Iv) * dt;
        Iv.push_back(next_Iv);
        
        // dIh/dt = BhShIv - rIh;
        // (next_Ih - prev_Ih) / dt = Bh0 * prev_Sh * prev_Iv * dt - r * prev_Ih;
        // next_Ih = prev_Ih + (Bh0 * prev_Sh * prev_Iv * dt - r * prev_Ih) * dt;
        double next_Ih = prev_Ih + (Bh * prev_Sh * prev_Iv * dt - r * prev_Ih) * dt;
        Ih.push_back(next_Ih);

        // dR/dt = +rIh;
        // (next_R - prev_R) / dt = r * prev_Ih;
        // next_R = prev_R + r * prev_Ih * dt;
        double next_R = prev_R + r * prev_Ih * dt;
        R.push_back(next_R);

        cout << "Day-" << day << "\t\t";
        cout << "Sh: " << Sh.back() << "\tIh: " << Ih.back() << "\t";
        cout << "Rh: " << R.back() - R[day - 1] << "\t";
        cout << "Iv: " << Iv.back() << "\t";
        cout << "Sv: " << Sv.back() << endl;

        totalCases += (Ih.back() - Ih[day - 1]) + (R.back() - R[day - 1]);
    }
    cout << endl << "Total Cases = " << totalCases << endl << endl;
}
