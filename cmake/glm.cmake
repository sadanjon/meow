find_path(GLM_INCLUDE_DIRS NAMES glm/glm.hpp HINTS $ENV{GLM_HOME} ${GLM_HOME})

# Perspective function taking degrees as a parameter is deprecated. Need to add this.
add_definitions("-DGLM_FORCE_RADIANS")
