#include <mex.h>

#include "drake/util/drakeMexUtil.h"
#include "drake/systems/plants/RigidBodyTree.h"

using namespace Eigen;
using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
  if (nrhs < 2 || nlhs < 2) {
    mexErrMsgIdAndTxt(
        "Drake:jointLimitConstraintsmex:InvalidCall",
        "Usage: [phi, J] = jointLimitConstraintsmex(mex_model_ptr, q) ");
  }

  RigidBodyTree *model = (RigidBodyTree *)getDrakeMexPointer(prhs[0]);

  if (mxGetNumberOfElements(prhs[1]) != model->number_of_positions()) {
    mexErrMsgIdAndTxt(
        "Drake:jointLimitConstraintsmex:InvalidPositionVectorLength",
        "q contains the wrong number of elements");
  }

  Map<VectorXd> q(mxGetPrSafe(prhs[1]), model->number_of_positions());

  size_t numJointConstraints = model->getNumJointLimitConstraints();

  plhs[0] = mxCreateDoubleMatrix(numJointConstraints, 1, mxREAL);
  plhs[1] =
      mxCreateDoubleMatrix(numJointConstraints, model->number_of_positions(),
        mxREAL);

  Map<VectorXd> phi(mxGetPrSafe(plhs[0]), numJointConstraints);
  Map<MatrixXd> J(mxGetPrSafe(plhs[1]), numJointConstraints,
                  model->number_of_positions());

  model->jointLimitConstraints(q, phi, J);
}
