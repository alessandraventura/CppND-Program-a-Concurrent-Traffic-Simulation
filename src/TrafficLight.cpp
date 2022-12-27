#include "TrafficLight.h"

#include <iostream>
#include <random>

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::Receive() {
  // FP.5a : The method receive should use std::unique_lock<std::mutex> and
  // _condition.wait()
  // to wait for and receive new messages and pull them from the queue using
  // move semantics.
  // The received object should then be returned by the receive function.

  std::unique_lock<std::mutex> access_queue_lock(_mutex_msg_queue);
  _condition_msg_queue.wait(access_queue_lock,
                            [this] { return !_queue.empty(); });
  TrafficLightPhase current_phase(std::move(_queue.at(0)));
  return current_phase;
}

template <typename T>
void MessageQueue<T>::Send(T &&msg) {
  // FP.4a : The method send should use the mechanisms
  // std::lock_guard<std::mutex>
  // as well as _condition.notify_one() to add a new message to the queue and
  // afterwards send a notification.
  std::lock_guard<std::mutex> access_queue_lockguard(_mutex_msg_queue);
  _queue.clear();
  _queue.emplace_back(msg);
  _condition_msg_queue.notify_one();
}

/* Implementation of class "TrafficLight" */

/*
TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}
*/

void TrafficLight::WaitForGreen() {
  // FP.5b : add the implementation of the method waitForGreen, in which an
  // infinite while-loop
  // runs and repeatedly calls the receive function on the message queue.
  // Once it receives TrafficLightPhase::green, the method returns.
  while (true) {
    if (_traffic_light_msg_queue.Receive() == TrafficLightPhase::green) {
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

TrafficLightPhase TrafficLight::CurrentPhase() { return _current_phase; }

void TrafficLight::Simulate() {
  // FP.2b : Finally, the private method „cycleThroughPhases“ should be
  // started in a thread when the public method „simulate“ is called. To do
  // this, use the thread queue in the base class.
  threads.emplace_back(std::thread(&TrafficLight::CycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::CycleThroughPhases() {
  // FP.2a : Implement the function with an infinite loop that measures the time
  // between two loop cycles and toggles the current phase of the traffic light
  // between red and green and sends an update method to the message queue using
  // move semantics. The cycle duration should be ab random value between 4 and
  // 6 seconds. Also, the while-loop should use std::this_thread::sleep_for to
  // wait 1ms between two cycles.

  std::random_device duration;
  std::uniform_int_distribution<int> dist(4, 6);

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(dist(duration)));
    switch (_current_phase) {
      case TrafficLightPhase::green:
        _current_phase = TrafficLightPhase::red;
        break;
      case TrafficLightPhase::red:
        _current_phase = TrafficLightPhase::green;
        break;
    }
    _traffic_light_msg_queue.Send(std::move(_current_phase));
  }
}
