#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;
using std::atof;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

static const double scodinitThrotle = 0.3;
static const double scodtopSpeed = 40.0;
static const double scodthrottleUpdate = 0.1;

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

// Get what throttle value to apply based on the situation
void getThrottleValue(double speed,
                      double &throttle,
                      double steer_value)
{
    if(speed > scodtopSpeed)
        throttle -= scodthrottleUpdate;
    else
        throttle += scodthrottleUpdate;
    if (fabs(steer_value) > 0.2)
        throttle -= 0.1;
    if (throttle <= 0.2)
        throttle += scodthrottleUpdate;
    if (throttle > 0.8)
        throttle -= scodthrottleUpdate;
}

int main(int argc,char *argv[]) {
  uWS::Hub h;

  PID pid;
  pid.Init(-0.099, -0.0022, -0.72); //Kp,Ki,Kd initialization
  double throttle = scodinitThrotle;
  h.onMessage([&pid,&throttle](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          //throttle += 0.1;
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          //double angle = std::stod(j[1]["steering_angle"].get<string>()); 'unused variable'
          pid.UpdateError(cte); // Update pid errors based on cte.
          double steer_value = pid.TotalError(); //TotalError would be our steering value

          getThrottleValue(speed,throttle,steer_value);
 
          std::cout << "CTE: " << cte << " Steering Value: " << steer_value 
                    <<" throttle: " <<throttle
                    << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}