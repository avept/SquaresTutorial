*** Settings ***
Library           Process
Library           OperatingSystem
Library           utils.Utils    WITH NAME    Utils

Suite Setup      Prepare Test Environment
Suite Teardown   Clean Up Test Environment

Test Setup       Prepare Test Data
Test Teardown    Clean Up Output Files

*** Variables ***
${REPO_TOP_DIR}             /workspaces/SquaresTutorial
${BAZEL_BIN_DIR}            ${REPO_TOP_DIR}/bazel-bin
${TEST_DIR}                 ${REPO_TOP_DIR}/test_env
${PROCESS_INTERSECTIONS}    ${BAZEL_BIN_DIR}/src/square_intersection
${INPUT_CSV}                ${TEST_DIR}/input.csv
${OUTPUT_CSV}               ${TEST_DIR}/output.csv
${EXPECTED_CSV}             ${TEST_DIR}/expected.csv

*** Keywords ***

Prepare Test Environment
    [Documentation]    Create test directory and ensure a clean test environment
    Remove Directory    ${TEST_DIR}    recursive=True    
    Create Directory    ${TEST_DIR}

Clean Up Test Environment
    [Documentation]    Remove test directory after all tests are completed
    Remove Directory    ${TEST_DIR}    recursive=True    

Prepare Test Data
    [Documentation]    Generate new input.csv and expected.csv before each test
    Utils.Generate CSV    ${INPUT_CSV}    ${EXPECTED_CSV}
    Validate Input Data

Validate Input Data
    [Documentation]    Ensure input.csv exists and is not empty before running the test
    File Should Exist    ${INPUT_CSV}
    ${size} =    Get File Size    ${INPUT_CSV}
    Run Keyword If    ${size} == 0    Fail    Input CSV is empty. Skipping this test.

Clean Up Output Files
    [Documentation]    Remove the output CSV file after each test
    Remove File    ${OUTPUT_CSV}

*** Test Cases ***

# Test Case 1: No Input Arguments (Invalid Args)
Invalid Arguments: No Input
    [Documentation]    Ensure process fails when no arguments are given
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    shell=True    stderr=True
    Should Not Be Equal As Integers    ${result.rc}    0
    Log    Expected failure due to missing arguments.

# Test Case 2: Only One Argument (Invalid Args)
Invalid Arguments: One Argument
    [Documentation]    Ensure process fails when only one argument is provided
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    ${INPUT_CSV}    shell=True    stderr=True
    Should Not Be Equal As Integers    ${result.rc}    0
    Log    Expected failure due to missing output file argument.

# Test Case 3: Input File Does Not Exist
Invalid Input File
    [Documentation]    Ensure process fails when input file does not exist
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    /invalid/path/input.csv    ${OUTPUT_CSV}    shell=True    stderr=True
    Should Not Be Equal As Integers    ${result.rc}    0
    Should Contain    ${result.stderr}    Error: Unable to open input file
    Log    Expected failure due to missing input file.

# Test Case 4: Output File Cannot Be Written (Invalid Path)
Invalid Output File Path
    [Documentation]    Ensure process fails when the output file cannot be written
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    ${INPUT_CSV}    /invalid/path/output.csv    shell=True    stderr=True
    Should Not Be Equal As Integers    ${result.rc}    0
    Should Contain    ${result.stderr}    Error: Unable to open output file
    Log    Expected failure due to invalid output file path.

# Test Case 5: Output File Cannot Be Written (Permission issue)
Permissions Denied for Output File
    [Documentation]    Ensure process fails when the output file cannot be written
    Create File    ${OUTPUT_CSV}    Test content
    Run Process    chmod 400 ${OUTPUT_CSV}    shell=True
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    ${INPUT_CSV}    ${OUTPUT_CSV}    shell=True    stderr=True
    Should Not Be Equal As Integers    ${result.rc}    0
    Should Contain    ${result.stderr}    Error: Unable to open output file
    Run Process    chmod 644 ${OUTPUT_CSV}    shell=True

# Test Case 6: Valid Input & Output (Successful Execution)
Valid Input Processing
    [Documentation]    Ensure process successfully processes a valid input CSV
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    ${INPUT_CSV}    ${OUTPUT_CSV}    shell=True
    Should Be Equal As Integers    ${result.rc}    0
    File Should Exist    ${OUTPUT_CSV}
    ${match} =    Utils.compare_csv    ${EXPECTED_CSV}    ${OUTPUT_CSV}
    Should Be True    ${match}    Expected and output CSVs should match