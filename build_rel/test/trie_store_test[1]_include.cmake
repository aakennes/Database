if(EXISTS "/home/aakennes/code/database/Database/build_rel/test/trie_store_test[1]_tests.cmake")
  include("/home/aakennes/code/database/Database/build_rel/test/trie_store_test[1]_tests.cmake")
else()
  add_test(trie_store_test_NOT_BUILT trie_store_test_NOT_BUILT)
endif()
