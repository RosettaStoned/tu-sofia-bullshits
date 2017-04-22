sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev

gcc gauss.c test_func.c run_test.c  -o test -g `pkg-config --cflags --libs cunit` && ./test
