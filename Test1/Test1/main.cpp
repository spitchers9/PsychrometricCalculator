//
//  main.cpp
//  Test1
//
//  Created by Shaun Pitchers on 01/06/2018.
//  Copyright © 2018 Shaun Pitchers. All rights reserved.
//

#include <iostream>
#include <cmath>

double patm(double z)
{
    double K = 1.0 - (0.0000225577*z);
    return 101.325 * pow(K,5.2559);
}


double pws1(double TD)
{
    double T = TD + 273.15;
    double c1 = -5.6745359e3;
    double c2 = 6.3925247;
    double c3 = -9.6778430e-3;
    double c4 = 6.2215701e-7;
    double c5 = 2.0747825e-9;
    double c6 = -9.4840240e-13;
    double c7 = 4.1635019e0;
    
    double lnpws = (c1/T) + c2 + c3*T + c4*pow(T,2.0) + c5*pow(T,3.0) + c6*pow(T,4.0) +c7*log(T);

    return exp(lnpws);
}
double pws2(double TF)
{
    double T = TF + 273.15;
    double c8 = -5.8002206e3;
    double c9 = 1.3914993;
    double c10 = -4.8640239e-2;
    double c11 = 4.1764768e-5;
    double c12 = -1.4452093e-8;
    double c13 = 6.5459673e0;

    
    double lnpws = (c8/T) + c9 + c10*T + c11*pow(T,2.0) + c12*pow(T,3.0) + c13*log(T);
    
    return exp(lnpws);
}

double tsp(double W,double T,double p)
{
    int a = 0;
    double ts = T;
    double pws;
    double ws;
    double fts;
    double dt = 10.0;

    do {
        pws = pws2(ts);
        ws = 0.621945*(pws/(p-pws));
        fts = ts*(2.326*ws - 4.186*W - 1.006) + 2501*(W-ws) + 1.86*T*W + 1.006*T;
        if (fts>0.0)
        {
            ts = ts + dt;
        }
        else
        {
            ts = ts - dt;
        }
        dt = dt/2.0;
        a=a+1;
    } while (a<100);

    return ts;

}

double tsn(double W,double T,double p)
{
    int a=0;
    double ts = T;
    double pws;
    double ws;
    double fts;
    double dt = 10.0;
    
    do {
        pws = pws1(ts);
        ws = 0.621945*(pws/(p-pws));
        fts = ts*(0.24*ws - 2.1*W - 1.006) + 2830*(W-ws) + 1.86*T*W + 1.006*T;
        if (fts>0.0)
        {
            ts = ts + dt;
        }
        else
        {
            ts = ts - dt;
        }
        dt = dt/2.0;
        a=a+1;
    } while (a<100);
    
    return ts;
    
}


double RelHumid(double TC,double RH,double z)
{
    double pws;
    double pw;
    double w;
    double h;
    double p;
    double td;
    double ws;
    double tw;
    double alpha;
    long double mu;
    long double v;

    std::cout << "Dry Bulb Temperature: "; // ask user for a number

    std::cin >> TC; // read number from console and store it in x

    std::cout << "Relative Humidity (%): "; // ask user for a number

    std::cin >> RH; // read number from console and store it in x

    std::cout << "Altitude: "; // ask user for a number

    std::cin >> z; // read number from console and store it in x

    if (TC < 0.0)
    {

        pws = pws1(TC);
    }

    else
    {
       pws = pws2(TC);
    }

    p = patm(z)*1000;

    pw = (RH/100.0)*pws;
    w = 0.621945*(pw/(p-pw));
    h = 1.006*TC + w*(2501 + 1.86*TC);

    alpha = log(pw/1000);
    
    if (TC>0.0)
    {
        td = 6.54 + 14.526*alpha + 0.7389*pow(alpha,2.0) + 0.09486*pow(alpha,3.0) + 0.4569*pow(pw/1000,0.1984);
    }
    else
    {
        td = 6.09 + 12.608*alpha + 0.4959*pow(alpha,2.0);
    }
    
    ws = 0.621945*(pws/(p-pws));
    
    if (TC>0.0)
    {
        tw = tsp(w,TC,p);
    }
    else
    {
        tw = tsn(w,TC,p);
    }
    
    mu=w/ws;
    v=(287.042*(TC+273.15))/(p-pw);

    std::cout << "Humidity Ratio (kg/kg) = " << w << std::endl;
    std::cout << "Saturated Humidity Ratio (kg/kg) = " << ws << std::endl;
    std::cout << "Degree of Saturation (%) = " << mu*100 << std::endl;
    std::cout << "Enthalpy (kj/kg) = " << h << std::endl;
    std::cout << "Dew-Point (°C) = " << td << std::endl;
    std::cout << "Wet Bulb Temperature (°C) = " << tw << std::endl;
    std::cout << "partial pressure of water vapour (Pa) = " << pw << std::endl;
    std::cout << "Saturated Vapour Pressure = " << pws << std::endl;
    std::cout << "Specific Volume = (m^3/kg) " << v << std::endl;





    return 0;
}

double WetBulb(double TC, double TW, double z)
{

    double pwsw;
    double pws;
    double pw;
    double ws;
    double w;
    double h;
    double p;
    double RH;
    double td;
    double mu;
    double v;
    double alpha;

    std::cout << "Dry Bulb Temperature (°C): "; // ask user for a number

    std::cin >> TC; // read number from console and store it in x

    std::cout << "Wet Bulb Temperature (°C): "; // ask user for a number

    std::cin >> TW; // read number from console and store it in x

    std::cout << "Altitude: "; // ask user for a number

    std::cin >> z; // read number from console and store it in x

    if (TC < 0.0)
    {

        pwsw = pws1(TW);
    }

    else
    {
        pwsw = pws2(TW);
    }

    if (TC < 0.0)
    {

        pws = pws1(TC);
    }

    else
    {
        pws = pws2(TC);
    }

    p = patm(z)*1000;
    ws = 0.621945*(pwsw/(p-pwsw));

    if (TW>0.0)
    {
     w = ((2501 -2.326*TW)*ws - 1.006*(TC-TW))/(2501 + 1.86*TC - 4.186*TW);
    }
    else
    {
    w = ((2830 - 0.24*TW)*ws - 1.006*(TC-TW))/(2830 + 1.86*TC - 2.1*TW);
    }

    h = 1.006*TC + w*(2501 + 1.86*TC);
    pw = (p*w)/(0.621945 + w);
    RH = (pw/pws)*100;

    alpha = log(pw/1000);

    if (TW>0.0)
    {
        td = 6.54 + 14.526*alpha + 0.7389*pow(alpha,2.0) + 0.09486*pow(alpha,3.0) + 0.4569*pow(pw/1000,0.1984);
    }
    else
    {
        td = 6.09 + 12.608*alpha + 0.4959*pow(alpha,2.0);
    }
    
    mu=w/ws;
    v=(287.042*(TC+273.15))/(p-pw);
    
    std::cout << "Humidity Ratio (kg/kg) = " << w << std::endl;
    std::cout << "Enthalpy (kj/kg) = " << h << std::endl;
    std::cout << "RH (%) = " << RH << std::endl;
    std::cout << "Dew Point (°C) = " << td << std::endl;
    std::cout << "Saturated Humidity Ratio (kg/kg) = " << ws << std::endl;
    std::cout << "Degree of Saturation (%) = " << mu*100 << std::endl;
    std::cout << "partial pressure of water vapour (Pa) = " << pw << std::endl;
    std::cout << "Saturated Vapour Pressure = " << pws << std::endl;
    std::cout << "Specific Volume = (m^3/kg) " << v << std::endl;



    return 0;
}

//int main() {
//
//    return 0;
//}

