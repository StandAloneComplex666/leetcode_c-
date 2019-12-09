#include <iostream>
#include <cmath>
using namespace std;


// tools
template <size_t N>
int getlen(double (&n)[N])
{
    return sizeof(n)/sizeof(n[0]);
}

bool is_valid(double cash_flow[], int size)
{
    // check if investment is negative
    if (cash_flow[0] >= 0 || size < 2)
    return false;
    
    //check if cashflows exhibit more than one sign reversal;
    for (int i = 1; i < size; i++)
    {
        if (cash_flow[i] < 0)
        return false;
    }
    
    return true;
}

// methods for compute npv
double get_npv(double cash_flow[], float r, int size)
{
    double sum = 0;
    double cash;
    for(int i = 0; i < size; i++){
        cash = cash_flow[i];
        //cout << cash << endl;
        sum = sum + cash/pow(1 + r, i);
    }
    return sum;
}




// methods for compute irr
#define  initial_rate -1.0
#define HIGH_RATE 10000.00
#define MAX_ITERATION 10000
#define PRECISION_REQ 0.000001
double get_irr(double cash_flow[], int size)
{
    int i = 0, j = 0;
    double old_value = 0.0;
    double new_value = 0.0;
    double oldguessRate = initial_rate;
    double newguessRate = initial_rate;
    double guessRate = initial_rate;
    double lowGuessRate = initial_rate;
    double highGuessRate = HIGH_RATE;
    double npv = 0.0;
    double denom = 0.0;
    for (i=0; i<MAX_ITERATION; i++)
    {
        npv = 0.00;
        for (j=0; j<size; j++)
        {
            denom = pow((1 + guessRate),j);
            npv = npv + (cash_flow[j]/denom);
        }

        /* Stop checking once the required precision is achieved */
        if ((npv > 0) && (npv < PRECISION_REQ))
            break;
        if (old_value == 0)
            old_value = npv;
        if (old_value != 0)
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
            else if (old_value > new_value)
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
    
    while (cumulation < investment && year <= size)
    {
        if (cumulation + cash_flow[year] > investment)
        {
            dot_month = (investment - cumulation) / cash_flow[year];
            payback_period =  year - 1 + dot_month; //payback_period = (double)year - 1 + dot_month;
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


int main()
{
    //double cash_flow_1[6] = {-6420.0, 2500.0, 3020.0, 1200.0, 950.0, 800.0};
    //double cash_flow_2[8] = {-4500.0, 1050.0, 790.0, 850.0, 1150.0, 810.0, 800.0, 1300.0};
    float rate;
    float npv;
    int size;
 
    //size = getlen();
     cout << "Please enter how many values you wanna input in project 1:"<< endl;
     cin >> size;
     double cash_flow[size];
     cout << "Plase enter the cash_flow year by year:"<< endl;
     for (int i = 0; i < size; i++)
     {
         cout << "in the year"<< " "<<i <<":"<< endl;
         cin >> cash_flow[i];
     }
     cout << "Please enter the interest rate:" << endl;
     cin >> rate;
    
    if (is_valid(cash_flow, size))
    {

        //cout << size << endl;
        npv = get_npv(cash_flow, rate, size);
        cout << "NPV1 = " << npv << endl;
        double irr = get_irr(cash_flow, size);
        cout << "IRR1= " << irr << endl;
        double pp = get_pp(cash_flow, size);
        cout << "PP1= " << pp << endl;
    }
    else
    {
        cout << "ERROR.";
    }
    
    
    
    cout << "Please enter how many values you wanna input in project 2:"<< endl;
    cin >> size;
    cout << "Plase enter the cash_flow year by year:"<< endl;
    for (int j = 0; j < size; j++)
    {
        cout << "in the year"<< j <<":"<< endl;
        cin >> cash_flow[j];
    }
    cout << "Please enter the interest rate:" << endl;
    cin >> rate;
    
    if (is_valid(cash_flow, size))
       {

           //cout << size << endl;
           npv = get_npv(cash_flow, rate, size);
           cout << "NPV2 = " << npv << endl;
           double irr = get_irr(cash_flow, size);
           cout << "IRR2= " << irr << endl;
           double pp = get_pp(cash_flow, size);
           cout << "PP2= " << pp << endl;
           return 0;
       }
       else
       {
           cout << "ERROR.";
       }
    
    
    
    
   
}
