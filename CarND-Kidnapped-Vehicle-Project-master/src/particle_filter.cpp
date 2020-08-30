/**
 * particle_filter.cpp
 *
 * Created on: Dec 12, 2016
 * Author: Tiffany Huang
 */

#include "particle_filter.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <limits>

#include "helper_functions.h"

using std::string;
using std::vector;
using std::normal_distribution;

void ParticleFilter::init(double x, double y, double theta, double std[]) 
{
  if(is_initialized)
      return;
  num_particles = 101;  // TODO: Set the number of particles

  normal_distribution<double> dist_x(0, std[0]);
  normal_distribution<double> dist_y(0, std[1]);
  normal_distribution<double> dist_theta(0, std[2]);

  for(int i =0;i<num_particles;i++)
  {
      Particle p;
      p.id = i;
      p.x = x;
      p.y = y;
      p.theta = theta;
      p.weight = 1.0;
      p.x += dist_x(m_gen);
      p.y += dist_y(m_gen);
      p.theta += dist_theta(m_gen);
      particles.push_back(p);
  }
  is_initialized = true;
}

void ParticleFilter::prediction(double delta_t, double std_pos[], 
                                double velocity, double yaw_rate) 
{
  /** you may find std::normal_distribution 
   *   and std::default_random_engine useful.
   *  http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
   *  http://www.cplusplus.com/reference/random/default_random_engine/
   */
    
  /*
   * x_f = x_0 + v/yaw_rate[sin(θ + yaw_rate*deta_t) - sin(θ)]
   * y_f = y_0 + v/yaw_rate[cos(θ) - cos(θ + yaw_rate*delta_t)]
   * θ_f = θ_0 + yaw_rate * deta_t
   */
  normal_distribution<double> dist_x(0, std_pos[0]);
  normal_distribution<double> dist_y(0, std_pos[1]);
  normal_distribution<double> dist_theta(0, std_pos[2]);
  for(int i =0;i<num_particles;i++)
  {
      
      if(fabs(yaw_rate) < 0.00001)
      {
          particles[i].x += velocity * delta_t * cos(particles[i].theta);
          particles[i].y += velocity * delta_t * sin(particles[i].theta);
      }
      else
      {
          particles[i].x += velocity/yaw_rate * (sin(particles[i].theta + yaw_rate*delta_t) - sin(particles[i].theta));
          particles[i].y += velocity/yaw_rate * (cos(particles[i].theta) - cos(particles[i].theta + yaw_rate*delta_t));
          particles[i].theta += yaw_rate * delta_t;
      }
      particles[i].x += dist_x(m_gen);
      particles[i].y += dist_y(m_gen);
      particles[i].theta += dist_theta(m_gen);
  }               
}

void ParticleFilter::dataAssociation(vector<LandmarkObs> predicted, 
                                     vector<LandmarkObs>& observations) {
  /**
   * Find the predicted measurement that is closest to each 
   *   observed measurement and assign the observed measurement to this 
   *   particular landmark.
   */
    for (auto &ob : observations)
    {
        int currid = -1;
        double minDist = std::numeric_limits<double>::max();
        for(auto pd : predicted)
        {
            double currDist = dist(ob.x,ob.y,pd.x,pd.y);
            if(currDist < minDist)
            {
                minDist = currDist;
                currid = pd.id;
            }
        }
        ob.id = currid;
    }
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[], 
                                   const vector<LandmarkObs> &observations, 
                                   const Map &map_landmarks) {
  /**
   *  Update the weights of each particle using a mult-variate Gaussian 
   *   distribution. You can read more about this distribution here: 
   *   https://en.wikipedia.org/wiki/Multivariate_normal_distribution
   * NOTE: The observations are given in the VEHICLE'S coordinate system. 
   *   Your particles are located according to the MAP'S coordinate system. 
   *   You will need to transform between the two systems. Keep in mind that
   *   this transformation requires both rotation AND translation (but no scaling).
   *   The following is a good resource for the theory:
   *   https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
   *   and the following is a good resource for the actual equation to implement
   *   (look at equation 3.33) http://planning.cs.uiuc.edu/node99.html
   */
    /*x_m = x_p + (cosθ * x_c)−(sinθ * y_c)
    y_m = y_p + (sinθ * x_c) +(cosθ * y_c)*/
    for (int i = 0; i < num_particles; i++) 
    {
       vector<LandmarkObs> transformed_obs;
       for(auto ob : observations)
       {
           double xt = particles[i].x + (cos(particles[i].theta) * ob.x) - (sin(particles[i].theta) * ob.y);
           double yt = particles[i].y + (sin(particles[i].theta) * ob.x) + (cos(particles[i].theta) * ob.y);
           transformed_obs.push_back({ob.id,xt,yt});
       }
       vector<LandmarkObs> sensor_predictions;
       for(auto lm : map_landmarks.landmark_list)
       {
           if((fabs(lm.x_f - particles[i].x) <= sensor_range) &&
              (fabs(lm.y_f - particles[i].y) <= sensor_range))
              {
                  sensor_predictions.push_back({lm.id_i,lm.x_f,lm.y_f});
              }
       }
       dataAssociation(sensor_predictions,transformed_obs);
       particles[i].weight = 1.0;
       for (auto trob : transformed_obs)
       {
           double x_obs,y_obs,mu_x,mu_y;
           x_obs = trob.x;
           y_obs = trob.y;
           for(auto sepre : sensor_predictions)
           {
               if(sepre.id == trob.id)
               {
                   mu_x = sepre.x;
                   mu_y = sepre.y;
               }
           }
           double gauss_norm;
           double sig_x = std_landmark[0];
           double sig_y = std_landmark[1];
           gauss_norm = 1 / (2 * M_PI * sig_x * sig_y);

           // calculate exponent
           double exponent;
           exponent = (pow(x_obs - mu_x, 2) / (2 * pow(sig_x, 2)))
                      + (pow(y_obs - mu_y, 2) / (2 * pow(sig_y, 2)));
    
            // calculate weight using normalization terms and exponent
            double weight;
            weight = gauss_norm * exp(-exponent);
            if (weight == 0)
            {
                particles[i].weight *= 0.00001;
            } 
           else 
           {
               particles[i].weight *= weight;
           }
       } 
    }
}

void ParticleFilter::resample() {
  /**
   * TODO: Resample particles with replacement with probability proportional 
   *   to their weight. 
   * NOTE: You may find std::discrete_distribution helpful here.
   *   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
   */
    vector<double> weights;
    for(int i = 0;i<num_particles;i++)
    {
        weights.push_back(particles[i].weight);
    }
    double max_weight = *max_element(weights.begin(),weights.end());
      // Creating distributions.
    std::uniform_real_distribution<double> distDouble(0.0, max_weight);
    std::uniform_int_distribution<int> distInt(0, num_particles - 1);
    // Generating index.
    int index = distInt(m_gen);
    double beta = 0.0;
    // the wheel
    vector<Particle> resampledParticles;
    for(int i = 0; i < num_particles; i++) 
    {
        beta += distDouble(m_gen) * 2.0;
        while( beta > weights[index]) 
        {
            beta -= weights[index];
            index = (index + 1) % num_particles;
        }
        resampledParticles.push_back(particles[index]);
    }
    particles = resampledParticles;
}

void ParticleFilter::SetAssociations(Particle& particle, 
                                     const vector<int>& associations, 
                                     const vector<double>& sense_x, 
                                     const vector<double>& sense_y) {
  // particle: the particle to which assign each listed association, 
  //   and association's (x,y) world coordinates mapping
  // associations: The landmark id that goes along with each listed association
  // sense_x: the associations x mapping already converted to world coordinates
  // sense_y: the associations y mapping already converted to world coordinates
  particle.associations= associations;
  particle.sense_x = sense_x;
  particle.sense_y = sense_y;
}

string ParticleFilter::getAssociations(Particle best) {
  vector<int> v = best.associations;
  std::stringstream ss;
  copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}

string ParticleFilter::getSenseCoord(Particle best, string coord) {
  vector<double> v;

  if (coord == "X") {
    v = best.sense_x;
  } else {
    v = best.sense_y;
  }

  std::stringstream ss;
  copy(v.begin(), v.end(), std::ostream_iterator<float>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}