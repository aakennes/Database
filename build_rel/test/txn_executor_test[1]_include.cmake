if(EXISTS "/home/aakennes/code/database/Database/build_rel/test/txn_executor_test[1]_tests.cmake")
  include("/home/aakennes/code/database/Database/build_rel/test/txn_executor_test[1]_tests.cmake")
else()
  add_test(txn_executor_test_NOT_BUILT txn_executor_test_NOT_BUILT)
endif()
