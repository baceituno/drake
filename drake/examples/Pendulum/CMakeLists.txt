if(lcm_FOUND)
  add_library_with_exports(LIB_NAME drakePendulum SOURCE_FILES
    pendulum_swing_up.cc
    )
  target_link_libraries(drakePendulum drakeDynamicConstraint
    drakeTrajectoryOptimization)
  pods_install_libraries(drakePendulum)
  drake_install_headers(Pendulum.h pendulum_swing_up.h)
  pods_install_pkg_config_file(drake-pendulum
    LIBS -ldrakePendulum
    REQUIRES
    VERSION 0.0.1)
  add_dependencies(drakePendulum drake_lcmtypes_hpp)

  add_executable(pendulum_run_dynamics pendulum_run_dynamics.cc)
  target_link_libraries(pendulum_run_dynamics
    drakeRBM
    drakeLCMSystem
    threads)
  add_test(NAME pendulum_run_dynamics
    COMMAND pendulum_run_dynamics --non-realtime)

  add_executable(pendulum_run_energy_shaping pendulum_run_energy_shaping.cc)
  target_link_libraries(pendulum_run_energy_shaping
    drakeRBM
    drakeLCMSystem
    threads)
  # add_test(NAME pendulum_run_energy_shaping COMMAND pendulum_run_energy_shaping --non-realtime)  # FIXME: disabled for now since it's not a good test, since it will always timeout

  add_executable(pendulum_run_lqr pendulum_run_lqr.cc)
  target_link_libraries(pendulum_run_lqr drakeRBM drakeLCMSystem)
  add_test(NAME pendulum_run_lqr
    COMMAND pendulum_run_lqr --non-realtime)

  add_executable(pendulum_run_swing_up pendulum_run_swing_up.cc)
  target_link_libraries(pendulum_run_swing_up
    drakePendulum
    drakeRBM
    drakeLCMSystem)
endif()

add_subdirectory(test)

add_matlab_test(NAME examples/Pendulum/PendulumEnergyShaping.run COMMAND PendulumEnergyShaping.run)
add_matlab_test(NAME examples/Pendulum/globalStability COMMAND globalStability REQUIRES mosek spotless)
add_matlab_test(NAME examples/Pendulum/runDLQR COMMAND runDLQR)
add_matlab_test(NAME examples/Pendulum/runLQR COMMAND runLQR)
add_matlab_test(NAME examples/Pendulum/runLQRtest COMMAND runLQRtest)
add_matlab_test(NAME examples/Pendulum/runPassive COMMAND runPassive)
add_matlab_test(NAME examples/Pendulum/runPassiveURDF COMMAND runPassiveURDF)
add_matlab_test(NAME examples/Pendulum/runSwingUp COMMAND runSwingUp)
add_matlab_test(NAME examples/Pendulum/runTrigLQR COMMAND runTrigLQR)
add_matlab_test(NAME examples/Pendulum/PendulumEnergyControl.run COMMAND PendulumEnergyControl.run)

if(LONG_RUNNING_TESTS)
  # add_matlab_test(NAME examples/Pendulum/runTrajectorySwingUpAndBalance COMMAND runTrajectorySwingUpAndBalance PROPERTIES TIMEOUT 1500)  # FIXME: see #2305
  add_matlab_test(NAME examples/Pendulum/runValueIteration COMMAND runValueIteration PROPERTIES TIMEOUT 1500)
endif()
