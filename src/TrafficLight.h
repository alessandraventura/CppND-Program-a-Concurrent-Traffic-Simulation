#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <condition_variable>
#include <deque>
#include <mutex>

#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

// FP.3 Define a class „MessageQueue“ which has the public methods send and
// receive. Send should take an rvalue reference of type TrafficLightPhase
// whereas receive should return this type. Also, the class should define an
// std::dequeue called _queue, which stores objects of type TrafficLightPhase.
// Also, there should be an std::condition_variable as well as an std::mutex as
// private members.

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

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject.
// The class shall have the public methods „void waitForGreen()“ and „void
// simulate()“ as well as „TrafficLightPhase getCurrentPhase()“, where
// TrafficLightPhase is an enum that can be either „red“ or „green“. Also, add
// the private method „void cycleThroughPhases()“. Furthermore, there shall be
// the private member _currentPhase which can take „red“ or „green“ as its
// value.

enum class TrafficLightPhase { red, green };

class TrafficLight : public TrafficObject {
 public:
  // constructor / desctructor

  // getters / setters

  // typical behaviour methods
  void WaitForGreen();
  void Simulate();

  TrafficLightPhase CurrentPhase();

 private:
  // typical behaviour methods
  void CycleThroughPhases();

  TrafficLightPhase _current_phase = TrafficLightPhase::red;

  // FP.4b : create a private member of type MessageQueue for messages of
  // type TrafficLightPhase and use it within the infinite loop to push each
  // new TrafficLightPhase into it by calling send in conjunction with move
  // semantics.
  MessageQueue<TrafficLightPhase> _traffic_light_msg_queue;

  std::condition_variable _condition;
  std::mutex _mutex;
};

#endif