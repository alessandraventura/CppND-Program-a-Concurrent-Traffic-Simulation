#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <condition_variable>
#include <deque>
#include <mutex>

#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

template <class T>
class MessageQueue {
 public:
  void Send(T &&msg);
  T Receive();

 private:
  std::deque<T> _queue;
  std::condition_variable _condition_msg_queue;
  std::mutex _mutex_msg_queue;
};

enum class TrafficLightPhase { red, green };

class TrafficLight : public TrafficObject {
 public:
  // typical behaviour methods
  void WaitForGreen();
  void Simulate();

  TrafficLightPhase CurrentPhase();

 private:
  // typical behaviour methods
  void CycleThroughPhases();

  TrafficLightPhase _current_phase = TrafficLightPhase::red;

  MessageQueue<TrafficLightPhase> _traffic_light_msg_queue;
};

#endif