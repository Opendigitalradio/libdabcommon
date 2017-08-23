set(CUTE_GROUP "constants")

cute_test(transmission_mode
  LIBRARIES ${${${PROJECT_NAME}_UPPER}_DEPS} ${${PROJECT_NAME}_LOWER}
  )
