#include "Street.h"

#include <iostream>

#include "Intersection.h"
#include "Vehicle.h"

Street::Street() {
  _type = ObjectType::objectStreet;
  _length = 1000.0;  // in m
}

void Street::InIntersection(std::shared_ptr<Intersection> in) {
  _inter_in = in;
  in->addStreet(get_shared_this());  // add this street to list of streets
                                     // connected to the intersection
}

void Street::OutIntersection(std::shared_ptr<Intersection> out) {
  _inter_out = out;
  out->addStreet(get_shared_this());  // add this street to list of streets
                                      // connected to the intersection
}
