"""This tester simply scan the entire filesystem, look for executable files, and then produce the hash of the given file and compare it between rhash, and ft_ssl"""

import os
import subprocess
import argparse

def is_executable(file_path):
    """Check if the file is executable."""
    return os.path.isfile(file_path) and os.access(file_path, os.X_OK)

def calculate_with_ft_ssl(file_path, hash_type):
    """Calculate MD5 hash using ./ft_ssl."""
    result = subprocess.run(['./ft_ssl', hash_type, '-r', file_path], capture_output=True, text=True)
    return result.stdout.strip()

def calculate_with_rhash(file_path, hash_type):
    """Calculate MD5 hash using rhash."""
    result = subprocess.run(['rhash', f"--{hash_type}", file_path], capture_output=True, text=True)
    return result.stdout.strip()

def parse_arguments():
    parser = argparse.ArgumentParser(description='Compare hash outputs.')
    parser.add_argument('hash_type', choices=['md5', 'sha256', 'whirlpool'],
                        help='The type of hash to calculate (md5, sha256, whirlpool)')
    return parser.parse_args()

def main(hash_type):
    for dirpath, _, filenames in os.walk('/'):
        for filename in filenames:
            file_path = os.path.join(dirpath, filename)

            if is_executable(file_path):
                print(f"Comparing {file_path}...", end='')

                ft_ssl_output = calculate_with_ft_ssl(file_path, hash_type)
                rhash_output = calculate_with_rhash(file_path, hash_type)

                if ft_ssl_output == rhash_output:
                    print("OK")
                else:
                    print("ERROR!")
                    print(f"ft_ssl Output: {ft_ssl_output}")
                    print(f"rhash Output: {rhash_output}")
                    exit(1)  # Exit on error

if __name__ == "__main__":
    args = parse_arguments()
    main(args.hash_type)