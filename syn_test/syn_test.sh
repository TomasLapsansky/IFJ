#!/bin/bash

make
clear
cd code1_test && ./test_syn1
cd ../code2_test && ./test_syn2
cd ../code3_test && ./test_syn3
