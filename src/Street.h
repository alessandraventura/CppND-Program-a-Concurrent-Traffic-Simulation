#ifndef STREET_H
#define STREET_H

#include <memory>

#include "TrafficObject.h"

// forward declaration to avoid include cycle
class Intersection;

class Street : public TrafficObject,
               public std::enable_shared_from_this<Street> {
 public:
  Street();

  double Length() { return _length; }
  void InIntersection(std::shared_ptr<Intersection> in);
  void OutIntersection(std::shared_ptr<Intersection> out);
  std::shared_ptr<Intersection> OutIntersection() { return _inter_out; }
  std::shared_ptr<Intersection> InIntersection() { return _inter_in; }

  // typical behaviour methods

  // miscellaneous
  std::shared_ptr<Street> get_shared_this() { return shared_from_this(); }

 private:
  double _length;  // length of this street in m
  std::shared_ptr<Intersection> _inter_in,
      _inter_out;  // intersections from which a vehicle can enter (one-way
                  // streets is always from 'in' to 'out')
};

#endif