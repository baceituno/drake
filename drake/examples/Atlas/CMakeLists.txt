add_library_with_exports(LIB_NAME drakeAtlasUtil SOURCE_FILES atlasUtil.cpp)
pods_install_libraries(drakeAtlasUtil)
drake_install_headers(
        atlasUtil.h
        atlas_plant.h
        )
pods_install_pkg_config_file(drake-atlas-util
  LIBS -ldrakeAtlasUtil
  REQUIRES
  VERSION 0.0.1)

if (lcm_FOUND)
  add_executable(atlas_dynamics_demo atlas_dynamics_demo.cc atlas_plant.cc)
  target_link_libraries(atlas_dynamics_demo drakeRBSystem drakeLCMSystem)
  add_dependencies(atlas_dynamics_demo drake_lcmtypes drake_lcmtypes_hpp)
  pods_use_pkg_config_packages(atlas_dynamics_demo lcm)
  add_test(NAME atlas_dynamics_demo COMMAND atlas_dynamics_demo 0.4)
endif()

add_matlab_test(NAME examples/Atlas/robotiqHandInspector COMMAND robotiqHandInspector)
add_matlab_test(NAME examples/Atlas/runAtlasDynamics COMMAND runAtlasDynamics)
add_matlab_test(NAME examples/Atlas/runAtlasFootstepPlanning COMMAND runAtlasFootstepPlanning)
add_matlab_test(NAME examples/Atlas/runAtlasFrontalDynamics COMMAND runAtlasFrontalDynamics)
add_matlab_test(NAME examples/Atlas/runAtlasJumping COMMAND runAtlasJumping REQUIRES gurobi)
add_matlab_test(NAME examples/Atlas/runAtlasSagittalDynamics COMMAND runAtlasSagittalDynamics)
add_matlab_test(NAME examples/Atlas/runAtlasWalkingPlanning COMMAND runAtlasWalkingPlanning)
add_matlab_test(NAME examples/Atlas/runCOMFixedPointSearch COMMAND runCOMFixedPointSearch)

# Deactivated due to memory flakiness in instantaneousQP; see #2165, #2376.
# add_matlab_test(NAME examples/Atlas/runDRCDoorTask COMMAND runDRCDoorTask REQUIRES iris)

add_matlab_test(NAME examples/Atlas/runRobotiqPDControl COMMAND runRobotiqPDControl)

if(LONG_RUNNING_TESTS)
  add_matlab_test(NAME examples/Atlas/runAtlasBalancingPerturb COMMAND runAtlasBalancingPerturb PROPERTIES TIMEOUT 1500 REQUIRES gurobi)
  add_matlab_test(NAME examples/Atlas/runAtlasManip COMMAND runAtlasManip PROPERTIES TIMEOUT 1500 REQUIRES gurobi)

  # Deactivated due to memory flakiness in instantaneousQP; see #2165, #2376.
  # add_matlab_test(NAME examples/Atlas/runAtlasWalking COMMAND runAtlasWalking PROPERTIES TIMEOUT 1500 REQUIRES gurobi)

  # add_matlab_test(NAME examples/Atlas/runAtlasBalancing COMMAND runAtlasBalancing PROPERTIES TIMEOUT 1500 REQUIRES gurobi)  # FIXME: see #2839
  # add_matlab_test(NAME examples/Atlas/runAtlasBalancingWithContactSensor COMMAND runAtlasBalancingWithContactSensor PROPERTIES TIMEOUT 1500 REQUIRES gurobi)  # FIXME: see #2839
  # add_matlab_test(NAME examples/Atlas/runAtlasHandControl COMMAND runAtlasHandControl PROPERTIES TIMEOUT 3000)  # FIXME: see #2839

  add_matlab_test(NAME examples/Atlas/runRobotiqTendons COMMAND runRobotiqTendons PROPERTIES TIMEOUT 1500)

  # Deactivated due to excessive timeouts.
  # add_matlab_test(NAME examples/Atlas/runDRCPracticeTerrain COMMAND runDRCPracticeTerrain PROPERTIES TIMEOUT 3000 REQUIRES iris)  # FIXME

endif()

add_subdirectory(test)
