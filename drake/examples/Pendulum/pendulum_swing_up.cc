#include <cmath>

#include <Eigen/Core>

#include "drake/common/drake_assert.h"
#include "drake/common/eigen_types.h"
#include "drake/examples/Pendulum/pendulum_swing_up.h"
#include "drake/solvers/Function.h"
#include "drake/systems/plants/constraint/dynamic_constraint.h"

using drake::solvers::detail::VecIn;
using drake::solvers::detail::VecOut;
using drake::solvers::LinearEqualityConstraint;

namespace drake {
namespace examples {
namespace pendulum {
namespace {

/**
 * Define a function to be evaluated as the running cost for a
 * pendulum trajectory (using the solvers::FunctionTraits style
 * interface).
 */
class PendulumRunningCost {
 public:
  static size_t numInputs() {
    DRAKE_ASSERT(PendulumState<double>::RowsAtCompileTime !=
                 Eigen::Dynamic);
    return PendulumState<double>::RowsAtCompileTime + 2; }
  static size_t numOutputs() { return 1; }

  template <typename ScalarType>
  void eval(const VecIn<ScalarType>& x, VecOut<ScalarType>& y) const {
    DRAKE_ASSERT(static_cast<size_t>(x.rows()) == numInputs());
    DRAKE_ASSERT(static_cast<size_t>(y.rows()) == numOutputs());

    // u represents the input vector.  Convention preserved here from
    // PendulumPlant.m.
    const auto u = x.tail(1);
    const double R = 10;  // From PendulumPlant.m, arbitrary AFAICT
    y = (R * u) * u;
  }
};

/**
 * Define a function to be evaluated as the final cost for a
 * pendulum trajectory (using the solvers::FunctionTraits style
 * interface).
 */
class PendulumFinalCost {
 public:
  static size_t numInputs() {
    DRAKE_ASSERT(PendulumState<double>::RowsAtCompileTime !=
                 Eigen::Dynamic);
    return PendulumState<double>::RowsAtCompileTime + 1; }
  static size_t numOutputs() { return 1; }

  template <typename ScalarType>
  void eval(const VecIn<ScalarType>& x, VecOut<ScalarType>& y) const {
    DRAKE_ASSERT(static_cast<size_t>(x.rows()) == numInputs());
    DRAKE_ASSERT(static_cast<size_t>(y.rows()) == numOutputs());

    y(0) = x(0);
  }
};
}  // anon namespace

void AddSwingUpTrajectoryParams(
    std::shared_ptr<Pendulum> pendulum,
    int num_time_samples,
    const Eigen::Vector2d& x0, const Eigen::Vector2d& xG,
    solvers::DircolTrajectoryOptimization* dircol_traj) {

  const int kTorqueLimit = 3;  // Arbitrary, taken from PendulumPlant.m.
  const drake::Vector1d umin(-kTorqueLimit);
  const drake::Vector1d umax(kTorqueLimit);
  dircol_traj->AddInputBounds(umin, umax);

  dircol_traj->AddStateConstraint(
      std::make_shared<LinearEqualityConstraint>(
          Eigen::Matrix2d::Identity(), x0), {0});
  dircol_traj->AddStateConstraint(
      std::make_shared<LinearEqualityConstraint>(
          Eigen::Matrix2d::Identity(), xG), {num_time_samples - 1});

  dircol_traj->AddRunningCost(PendulumRunningCost());
  dircol_traj->AddFinalCost(PendulumFinalCost());
  dircol_traj->AddDynamicConstraint(
      std::make_shared<drake::systems::SystemDynamicConstraint<Pendulum>>(
          pendulum));
}

}  // pendulum
}  // examples
}  // drake
