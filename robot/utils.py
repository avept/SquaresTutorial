import csv
import sys
import os

class Utils:
    """Python library for generating and comparing CSV files in Robot Framework."""

    def generate_csv(self, input_file, expected_file):
        """Generates input.csv and expected.csv based on predefined test cases."""
        test_cases = [
            ([0, 0, 1, 0, 0, 1], "true"),
            ([1, 1, 2, 2, 2, 3], "true"),
            ([1, 1, -2, 2, 2, 3], "error"),
            ([1, 1, 2, 2, 2, -3], "error"),
            ([], "error"),                                        # Empty line
            ([1, 1, 1, 5, 5, 5], "false"),
            ([], "error"),                                        # Empty line
            ([1, 2, 3, 4, 5], "error"),
            ([], "error"),                                        # Empty line
            ([32, 45, 3], "error"),
            ([1, 1, 4, 2, 2, 4], "true"),                         # Overlapping Bottom Right
            ([1, 1, 4, 0, 2, 4], "true"),                         # Overlapping Bottom Left
            ([1, 1, 3, 4, 4, 3], "true"),                         # Touching Corner Bottom Right
            ([1, 1, 3, -2, 4, 3], "true"),                        # Touching Corner Bottom Left
            ([1, 1, 3, 4, 1, 3], "true"),                         # Touching Edge Right Side
            ([1, 1, 3, 1, 4, 3], "true"),                         # Touching Edge Bottom Side
            ([2, 2, 4, 2, 2, 4], "true"),                         # Identical Squares
            ([0, 0, 10, 2, 2, 4], "false"),                       # One Inside Another
            ([5, 5, 3, 1, 5, 3], "false"),                        # No Intersection - Left
            ([5, 5, 3, 9, 5, 3], "false"),                        # No Intersection - Right
            ([5, 5, 3, 5, 1, 3], "false"),                        # No Intersection - Top
            ([5, 5, 3, 5, 9, 3], "false"),                        # No Intersection - Bottom
            ([1, 1, 0], "error"),                                 # Zero-Length Square
            ([1, 1, -3], "error"),                                # Negative Side Length
            ([1, 1, 1000000, 500000, 500000, 1000000], "true"),   # Large Squares
            ([1000001, 1000001, 3, 1000003, 1000003, 3], "true"), # Floating Point Precision
            ([5, 5, 5, 5, 5, 3], "true"),                         # Advanced Overlapping
            ([5, 5, 5, 4, 4, 3], "true"),                         # Two Points of Intersection - Corner
            ([5, 5, 5, 4, 7, 2], "true"),                         # Two Points of Intersection - Side
        ]

        try:
            with open(input_file, mode='w', newline='') as infile, open(expected_file, mode='w', newline='') as expfile:
                input_writer = csv.writer(infile)
                expected_writer = csv.writer(expfile)

                for case, expected_result in test_cases:
                    input_writer.writerow(case)
                    expected_writer.writerow(case + [expected_result])

            print(f"Generated input CSV: {input_file}")
            print(f"Generated expected CSV: {expected_file}")
        except Exception as e:
            print(f"Error generating CSV files: {e}")
            sys.exit(1)

    def compare_csv(self, expected_file, output_file):
        """Compares expected.csv with output.csv."""
        def read_csv(file_path):
            """Reads a CSV file and returns the content as a list of lists."""
            try:
                with open(file_path, mode='r', newline='') as file:
                    reader = csv.reader(file)
                    return [[cell.strip() for cell in row] for row in reader]
            except Exception as e:
                print(f"Error reading {file_path}: {e}")
                sys.exit(1)

        expected_data = read_csv(expected_file)
        output_data = read_csv(output_file)

        if expected_data == output_data:
            print("CSV files match!")
            return True
        else:
            print("CSV files do not match!")
            max_len = max(len(expected_data), len(output_data))

            for i in range(max_len):
                exp = expected_data[i] if i < len(expected_data) else "MISSING"
                out = output_data[i] if i < len(output_data) else "MISSING"

                if exp != out:
                    print(f"Mismatch at line {i+1}: Expected {exp} but got {out}")

            return False
            