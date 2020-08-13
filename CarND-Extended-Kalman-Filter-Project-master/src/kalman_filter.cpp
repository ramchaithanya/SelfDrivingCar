#include "kalman_filter.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

/* 
 * Please note that the Eigen library does not initialize 
 *   VectorXd or MatrixXd objects with zeros upon creation.
 */

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_ = H_in;
  R_ = R_in;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
   * TODO: predict the state
   */
#if 0
  x_ = F_ * x_;
  MatrixXd Ft = F_.transpose();
  P_ = F_ * P_ * Ft + Q_;
#endif
}

void KalmanFilter::Update(const VectorXd &z) {
  /**
   * TODO: update the state by using Kalman Filter equations
   */
#if 0
    for (unsigned int n = 0; n < measurements.size(); ++n) {



    VectorXd z = measurements[n];

    // TODO: YOUR CODE HERE

    /**

     * KF Measurement update step

     */

    VectorXd y = z - H * x;

    MatrixXd Ht = H.transpose();

    MatrixXd S = H * P * Ht + R;

    MatrixXd Si = S.inverse();

    MatrixXd K =  P * Ht * Si;



    // new state

    x = x + (K * y);

    P = (I - K * H) * P;



    /**

     * KF Prediction step

     */

    x = F * x + u;

    MatrixXd Ft = F.transpose();

    P = F * P * Ft + Q;



    cout << "x=" << endl <<  x << endl;

    cout << "P=" << endl <<  P << endl;

  }
#endif
}

void KalmanFilter::UpdateEKF(const VectorXd &z) {
  /**
   * TODO: update the state by using Extended Kalman Filter equations
   */
  VectorXd z_pred = H_ * x_;
  VectorXd y = z - z_pred;
  MatrixXd Ht = H_.transpose();
  MatrixXd S = H_ * P_ * Ht + R_;
  MatrixXd Si = S.inverse();
  MatrixXd PHt = P_ * Ht;
  MatrixXd K = PHt * Si;

  //new estimate
  x_ = x_ + (K * y);
  long x_size = x_.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_ = (I - K * H_) * P_;
}
