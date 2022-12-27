#ifndef TRAFFICOBJECT_H
#define TRAFFICOBJECT_H

#include <mutex>
#include <thread>
#include <vector>

enum ObjectType {
  noObject,
  objectVehicle,
  objectIntersection,
  objectStreet,
};

class TrafficObject {
 public:
  TrafficObject();
  ~TrafficObject();

  int ID() { return _id; }
  void setPosition(double x, double y);
  void getPosition(double &x, double &y);
  ObjectType getType() { return _type; }

  // typical behaviour methods
  virtual void Simulate(){};

 protected:
  ObjectType _type;     // identifies the class type
  int _id;              // every traffic object has its own unique id
  double _posX, _posY;  // vehicle position in pixels
  std::vector<std::thread>
      threads;  // holds all threads that have been launched within this object
  static std::mutex
      _mtx;  // mutex shared by all traffic objects for protecting cout

 private:
  static int _id_cnt;  // global variable for counting object ids
};

#endif