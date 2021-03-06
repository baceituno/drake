#pragma once

#include <string>
#include <map>
#include <Eigen/Dense>

typedef std::map<
    std::string, Eigen::Isometry3d, std::less<std::string>,
    Eigen::aligned_allocator<std::pair<const std::string, Eigen::Isometry3d> > >
    PoseMap;
