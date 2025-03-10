import csv
import argparse
import sys

def read_csv(file_path):
    """Reads a CSV file and returns the content as a list of lists."""
    try:
        with open(file_path, mode='r', newline='') as file:
            reader = csv.reader(file)
            return [[cell.strip() for cell in row] for row in reader]
    except Exception as e:
        print(f"Error reading {file_path}: {e}")
        sys.exit(1)

def compare_csv(expected_file, output_file):
    """Compares two CSV files and returns True if they match."""
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

def main():
    parser = argparse.ArgumentParser(description="Compare two CSV files.")
    parser.add_argument("expected_csv", type=str, help="Path to the expected CSV file.")
    parser.add_argument("output_csv", type=str, help="Path to the output CSV file.")

    args = parser.parse_args()

    result = compare_csv(args.expected_csv, args.output_csv)
    sys.exit(0 if result else 1)

if __name__ == "__main__":
    main()
