*** Settings ***
Library    Process

*** Variables ***
${BAZEL_CMD}    bazel run //tests:square_intersection_tests

*** Test Cases ***
Run Square Intersection Tests via Bazel
    [Documentation]    Run GTest using Bazel and verify all tests pass
    ${result}=    Run Process    ${BAZEL_CMD}    shell=True
    Log    ${result.stdout}
    Log    ${result.stderr}
    Should Be Equal As Numbers    ${result.rc}    0    msg=Square Intersection Test failed!
