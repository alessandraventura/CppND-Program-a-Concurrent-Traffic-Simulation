#include "TrafficLight.h"

#include <iostream>
#include <random>

/* Implementation of class "MessageQueue" */

template <typename T>
T MessageQueue<T>::Receive() {
  std::unique_lock<std::mutex> access_queue_lock(_mutex_msg_queue);
  _condition_msg_queue.wait(access_queue_lock,
                            [this] { return !_queue.empty(); });
  TrafficLightPhase current_phase(std::move(_queue.at(0)));
  return current_phase;
}

template <typename T>
void MessageQueue<T>::Send(T &&msg) {
  std::lock_guard<std::mutex> access_queue_lockguard(_mutex_msg_queue);
  _queue.clear();
  _queue.emplace_back(msg);
  _condition_msg_queue.notify_one();
}

/* Implementation of class "TrafficLight" */

void TrafficLight::WaitForGreen() {
  while (true) {
    if (_traffic_light_msg_queue.Receive() == TrafficLightPhase::green) {
      return;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

TrafficLightPhase TrafficLight::CurrentPhase() { return _current_phase; }

void TrafficLight::Simulate() {
  threads.emplace_back(std::thread(&TrafficLight::CycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::CycleThroughPhases() {
  std::random_device duration;
  std::uniform_real_distribution<double> dist(4, 6);

  while (true) {
    int duration_in_milliseconds = 1000 * dist(duration);
    std::this_thread::sleep_for(
        std::chrono::milliseconds(duration_in_milliseconds));
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
