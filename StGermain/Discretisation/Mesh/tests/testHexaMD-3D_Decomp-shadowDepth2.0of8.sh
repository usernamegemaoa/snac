#!/bin/sh

TEST_SCRIPT=./VMake/executableTester.sh
until test -r ${TEST_SCRIPT} ; do
        TEST_SCRIPT=../${TEST_SCRIPT}
done
. ${TEST_SCRIPT}

runAndHandleSystemTest "testHexaMD --decompDims=3 --shadowDepth=2" "$0" "$@"
