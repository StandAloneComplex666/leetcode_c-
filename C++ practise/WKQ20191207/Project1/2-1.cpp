#include <iostream>
#include <math.h>
#include <vector>
#include<algorithm> 
using namespace std;
// p2-1

float get_option_res(string option, float s, float k)
{
    float v;
    if (option == "put")
    {
        v = std::max<float>((s - k), 0);
    }
    else if (option == "call")
    {
        v = std::max<float>((k - s), 0);
    }
    return v;
}

// tools
template <size_t N>
int getlen(double(&n)[N]) {
    return sizeof(n) / sizeof(n[0]);
}

bool is_valid(double cash_flow[], int size)
{
    // check if investment is negative
    if (cash_flow[0] >= 0 || size < 2) return false;

    //check if cashflows exhibit more than one sign reversal;
    for (int i = 1; i < size; i++)
    {
        if (cash_flow[i] < 0) return false;
    }

    return true;
}

// methods for compute npv 
double get_npv(double cash_flow[], float r, int size)
{
    double sum = 0;
    double cash;
    for (int i = 0; i < size; i++) {
        cash = cash_flow[i];
        //cout << cash << endl;
        sum = sum + cash / pow(1 + r, i);
    }
    return sum;
}

// methods for compute irr

#define LOW_RATE 0.01
#define HIGH_RATE 0.5
#define MAX_ITERATION 1000
#define PRECISION_REQ 0.00000001
double get_irr(double cf[], int numOfFlows)
{
    int i = 0, j = 0;
    double m = 0.0;
    double old_value = 0.0;
    double new_value = 0.0;
    double oldguessRate = LOW_RATE;
    double newguessRate = LOW_RATE;
    double guessRate = LOW_RATE;
    double lowGuessRate = LOW_RATE;
    double highGuessRate = HIGH_RATE;
    double npv = 0.0;
    double denom = 0.0;
    for (i = 0; i < MAX_ITERATION; i++)
    {
        npv = 0.00;
        for (j = 0; j < numOfFlows; j++)
        {
            denom = pow((1 + guessRate), j);
            npv = npv + (cf[j] / denom);
        }

        /* Stop checking once the required precision is achieved */
        if ((npv > 0) && (npv < PRECISION_REQ))
            break;
        if (old_value == 0)
            old_value = npv;
        else
            old_value = new_value;
        new_value = npv;
        if (i > 0)
        {
            if (old_value < new_value)
            {
                if (old_value < 0 && new_value < 0)
                    highGuessRate = newguessRate;
                else
                    lowGuessRate = newguessRate;
            }
            else
            {
                if (old_value > 0 && new_value > 0)
                    lowGuessRate = newguessRate;
                else
                    highGuessRate = newguessRate;
            }
        }
        oldguessRate = guessRate;
        guessRate = (lowGuessRate + highGuessRate) / 2;
        newguessRate = guessRate;
    }
    return guessRate;
}

// methods for compute pp
double get_pp(double cash_flow[], int size)
{
    double investment = fabs(cash_flow[0]);
    double cumulation = 0.0;
    int year = 1;
    double payback_period;
    double dot_month;

    while (cumulation < investment && year < size)
    {
        if (cumulation + cash_flow[year] > investment)
        {
            dot_month = (investment - cumulation) / cash_flow[year];
            payback_period = (double)year - 1 + dot_month;
            return payback_period;
        }
        else
        {
            cumulation = cumulation + cash_flow[year];
            year = year + 1;
            //cout << cumulation << " - " << year << endl;
        }
    }
    return -1.0;
}
// main for problem 3
/*
int main()
{
 double cash_flow_1[6] = {-6420.0, 2500.0, 3020.0, 1200.0, 950.0, 800.0};
 double cash_flow_2[8] = {-4500.0, 1050.0, 790.0, 850.0, 1150.0, 810.0, 800.0, 1300.0};
 double cash_flow_wrong1[] = {-1000.0, 200.0, -200.0};
 double cash_flow_wrong2[] = {200.0, 100.0, 150};
 float rate = 0.05;
    float npv;
 int size;
 size = getlen(cash_flow_1);

 if (is_valid(cash_flow_1, size))
 {
     //cout << size << endl;
     npv = get_npv(cash_flow_1, rate, size);
     cout << "NPV = " << npv << endl;
     double irr = get_irr(cash_flow_1, size);
     cout << "IRR = " << irr << endl;
     double pp = get_pp(cash_flow_1, size);
     cout << "PP = " << pp << endl;
        return 0;
 }
 else
 {
  cout << "ERROR.";
 }
}
*/

// main for problem2
int main()
{
    string option = "put";
    float s0 = 160;
    float k = 135;
    float u = 1.4;
    float d = 0.8;
    float e = 2.71;
    float r = 0.085;
    int T = 5;
    int n = 10;
    float e_exp = std::pow(e, T / n * r);
    float p = (e_exp - d) / (u - d);
    float rate = pow(e_exp, n);


    vector< vector<float> > s_binomial;
    vector< vector<float> > v_binomial;
    vector<float> s_start;
    vector<float> v_end;

    //get s-binomial
    s_start.push_back(s0);
    s_binomial.push_back(s_start);
    for (int i = 1; i <= n; i++)
    {
        vector<float> level;
        
        for (int level_i = 0; level_i < s_binomial[i-1].size();level_i++)
        {
            float s_pre = s_binomial[i-1][level_i];
            level.push_back(s_pre * u);
            level.push_back(s_pre * d);
        }
        s_binomial.push_back(level);
    }
    //cout << s_binomial.size() << endl;

    // get v-binomial
    // get Vt
    v_end = vector<float>(s_binomial[s_binomial.size()-1]);
    v_binomial = vector< vector<float> >(s_binomial.size());
    for (int i = 0; i < v_end.size(); i++)
    {
        v_end[i] = (get_option_res(option, s_binomial[s_binomial.size() - 1][i], k));
    }
    //cout << "v_end" << v_end.size() << endl;
    v_binomial[v_binomial.size() - 1] = v_end;
    //cout << v_binomial.size() << endl;
    // get v of other levels
    for (int i = 1; i< v_binomial.size(); i++)
    {
        vector<float>v_level;
        int curr_level = v_binomial.size() - i;
        //cout << curr_level << endl;
        v_level = vector<float>(s_binomial[curr_level - 1].size());
        v_binomial[curr_level -1] = v_level;
        for (int level_i = 0; level_i < v_binomial[curr_level - 1].size(); level_i++)
        {

            v_binomial[curr_level - 1][level_i] = (v_binomial[curr_level][level_i * 2] * p + v_binomial[curr_level][level_i * 2 + 1] * (1 - p)) / rate;
        }
        //cout << "test" << v_level.size() << endl;

    }

    //print s-binomial
    for (int i = 0; i < s_binomial.size(); i++)
    {
        for (int j = 0; j < s_binomial[i].size(); j++)
        {
            cout << s_binomial[i][j] << ',';
        }
        cout << endl;
    }

    cout << "____________________________________________________________________________" << endl;

    // print v-binomial;
    for (int i = 0; i < v_binomial.size(); i++)
    {
        for (int j = 0; j < v_binomial[i].size(); j++)
        {
            cout << v_binomial[i][j] << ',';

        }
        cout << endl;
    }
    // print p
    //float res = get_option_res(option, s ,k);
    //cout << res << endl;
}