#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <opencv2/core.hpp>
#include <string>
#include <vector>

#include "TrafficObject.h"

class Graphics {
 public:
  void BgFilename(std::string filename) { _bg_filename = filename; }
  void TrafficObjects(
      std::vector<std::shared_ptr<TrafficObject>> &trafficObjects) {
    _traffic_objects = trafficObjects;
  };

  // typical behaviour methods
  void Simulate();

 private:
  // typical behaviour methods
  void LoadBackgroundImg();
  void DrawTrafficObjects();

  // member variables
  std::vector<std::shared_ptr<TrafficObject>> _traffic_objects;
  std::string _bg_filename;
  std::string _window_name;
  std::vector<cv::Mat> _images;
};

#endif