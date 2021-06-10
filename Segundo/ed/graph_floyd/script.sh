cd build
make
cd ..
./run_tests.sh build/test_floyd tests_floyd-wmatrix
./run_tests.sh build/test_floyd tests_floyd-path
./run_tests.sh build/test_floyd tests_floyd