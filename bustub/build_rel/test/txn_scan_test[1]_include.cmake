if(EXISTS "/home/aakennes/code/database/Database/bustub/build_rel/test/txn_scan_test[1]_tests.cmake")
  include("/home/aakennes/code/database/Database/bustub/build_rel/test/txn_scan_test[1]_tests.cmake")
else()
  add_test(txn_scan_test_NOT_BUILT txn_scan_test_NOT_BUILT)
endif()
