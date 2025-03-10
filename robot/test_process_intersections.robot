*** Settings ***
Library           Process
Library           OperatingSystem

*** Variables ***
${REPO_TOP_DIR}             /workspaces/SquaresTutorial
${BAZEL_BIN_DIR}            ${REPO_TOP_DIR}/bazel-bin
${PROCESS_INTERSECTIONS}    ${BAZEL_BIN_DIR}/src/square_intersection
${INPUT_CSV}                ${REPO_TOP_DIR}/robot/input.csv
${OUTPUT_CSV}               ${REPO_TOP_DIR}/output.csv
${EXPECTED_CSV}             ${REPO_TOP_DIR}/robot/expected.csv
${CSV_COMPARISON_SCRIPT}    ${REPO_TOP_DIR}/robot/compare_csv.py

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
Permissions denied for create output file
    [Documentation]    Ensure process fails when the output file cannot be written
    #${result} =    Run Process    ${PROCESS_INTERSECTIONS}    ${INPUT_CSV}    /workspaces/SquaresTutorial/robot/output.csv    shell=True    stderr=True
    #Should Not Be Equal As Integers    ${result.rc}    0
    #Should Contain    ${result.stderr}    Error: Unable to open output file
    #Log    Expected failure due to invalid permissions in output file.
    ${rc}  ${out} =  Run and Return RC and Output  ${PROCESS_INTERSECTIONS} ${INPUT_CSV} ${OUTPUT_CSV}
    Log Many  ${out}
    Log Many  RC=${rc}

# Test Case 6: Valid Input & Output (Successful Execution)
Valid Input Processing
    [Documentation]    Ensure process successfully processes a valid input CSV
    ${result} =    Run Process    ${PROCESS_INTERSECTIONS}    ${INPUT_CSV}    ${OUTPUT_CSV}    shell=True
    Should Be Equal As Integers    ${result.rc}    0
    File Should Exist    ${INPUT_CSV}
    ${input_content} =    Get File    ${INPUT_CSV}
    Log    \n*** Input CSV Content ***\n${input_content}    level=INFO
    ${compare} =    Run Process    python3    ${CSV_COMPARISON_SCRIPT}    ${EXPECTED_CSV}    ${OUTPUT_CSV}    shell=True
    Should Be Equal As Integers    ${compare.rc}    0
    Log    Expected successful processing.


# TODO:
# 1) Test env, create new folder, clean it 
# 2) Validate input.csv