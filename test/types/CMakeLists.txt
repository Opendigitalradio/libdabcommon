set(CUTE_GROUP "types")

cute_test(queue
  LIBRARIES ${${${PROJECT_NAME}_UPPER}_DEPS} ${${PROJECT_NAME}_LOWER}
  )
