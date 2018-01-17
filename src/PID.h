#ifndef PID_H
#define PID_H
#include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
    
  /*
  * Control Variables
  */

    int runstep;
    double prev_cte;
    double error;
    double best_error;
    double error_avg;
    std::vector<double> dp;
    int index;
    const int settle = 100;
    const int eval = 100;
    const int settle_eval = settle + eval;
    bool upflag;
    bool downflag;
    bool twiddle;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);
    
  /*
   * Initialize PID.
  */
  void Twiddle(double avgerror);
    
  /*
  * Initialize PID.
  */
  void UpdateTau(int index, double val);


  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
