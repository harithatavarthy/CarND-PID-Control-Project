#include "PID.h"
#include <iostream>
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    //std::cout << "i am here" << std::endl;
    PID::Kp = Kp;
    PID::Ki = Ki;
    PID::Kd = Kd;
    p_error = 0.0;
    d_error = 0.0;
    i_error = 0.0;
    error = 0.0;
    index  = 2;
    upflag = false;
    downflag = false;
    //settle = 100;
    //eval = 100;
    twiddle = false;
    best_error = std::numeric_limits<double>::max();
    
    runstep = 1;
    dp = {0.005*Kp,0.005*Ki,0.005*Kd};
}

void PID::Twiddle(double avgerror){
    //std::cout << "entered twiddle" <<std::endl;
    //std::cout << "avg error:" << avgerror <<std::endl;
    //std::cout << "best_error" << best_error << std::endl;
    
    
    
    if(avgerror < best_error){
        best_error = avgerror;
        if(runstep != settle + eval){
        dp[index] *= 1.1;
        }
        //std::cout << "Did Nothing for :" << index  << std::endl;

        index = (index + 1)%3;
        upflag = false;
        downflag = false;
    }
    if(!upflag && !downflag){
        UpdateTau(index,dp[index]);
        //std::cout << "Incrementing :" << index << "New Value is :" << dp[index] << std::endl;

        upflag = true;
    }
    else if (upflag && !downflag){
        UpdateTau(index, -2 * dp[index]);
        downflag = true;
        //std::cout << "Decrementing  :" << index << "New Value is :" << dp[index] << std::endl;
       
        
    }
    else{
        UpdateTau(index,dp[index]);
        dp[index] *= 0.9;
        index = (index + 1)%3;
        upflag = downflag = false;
    }
    
    //error = 0.0;
    
    
}

void PID::UpdateTau(int index, double value){
    if(index == 0){
        PID::Kp += value;
        
    }
    else if(index == 1){
        PID::Ki += value;
    }
    else if(index == 2){
        PID::Kd += value;
    }
    
}

void PID::UpdateError(double cte) {
    if(runstep == 1){
        prev_cte = cte;
    }
    p_error = cte;
    d_error = cte - prev_cte;
    prev_cte = cte;
    i_error += cte;
    
    if(twiddle){
    //std::cout << "runstep :" << runstep << std::endl;
    //std::cout << "Modulus :" << runstep % (settle + eval) << std::endl;
    if(runstep % (settle_eval) > settle ){
    error += pow(cte,2);
        //std::cout << "error:" <<error<< std::endl;
        
    }
    
    if(runstep % (settle_eval) == 0  ){
        error_avg = error/eval;
        if(error_avg > 0.1){
        Twiddle(error_avg);
        //std::cout << "I Just Twiddled" << std::endl;
        error = 0.0;
        error_avg = 0.0;
        }
        
    }
    }
    
    
    runstep ++;
    
    
    
    
}

double PID::TotalError() {
    //return 0.0;
    return -Kp * p_error -Kd * d_error - Ki * i_error;
}

