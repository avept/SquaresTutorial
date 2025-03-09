*** Settings ***
Library    Process

*** Variables ***
${REPO_TOP_DIR}    /workspaces/SquaresTutorial/
${BAZEL_BIN_DIR}    ${REPO_TOP_DIR}/bazel-bin
${TEST_BINARY}    ${BAZEL_BIN_DIR}/tests/square_intersection_tests

*** Test Cases ***
Run Square Intersection Tests via Bazel
    [Documentation]    Run GTest using Bazel and verify all tests pass
    ${result}=    Run Process    ${TEST_BINARY}    shell=True
    Log    ${result.stdout}
    Log    ${result.stderr}
    Should Be Equal As Numbers    ${result.rc}    0    msg=Square Intersection Test failed!
