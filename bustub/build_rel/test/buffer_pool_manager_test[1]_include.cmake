if(EXISTS "/home/aakennes/code/database/Database/bustub/build_rel/test/buffer_pool_manager_test[1]_tests.cmake")
  include("/home/aakennes/code/database/Database/bustub/build_rel/test/buffer_pool_manager_test[1]_tests.cmake")
else()
  add_test(buffer_pool_manager_test_NOT_BUILT buffer_pool_manager_test_NOT_BUILT)
endif()
