from typing import *
import sys
import os
import collections

class Input():
    def __init__(self):
        pass

    def __repr__(self):
        pass

def process_input(input_file: str) -> Input:
    with open(input_file, "r") as f:
        pass

def output(output_file: str, output: Any):
    with open(output_file, "w+") as f:
        pass


# write code here.
#
# // explanation of input
def solve(inp: Input) -> Any:
    pass

if __name__ == "__main__":
    input_filename = input("Enter input file: ")
    input_file = os.path.join(os.path.abspath(__file__), "../{}.in".format(input_filename))
    output_file = os.path.join(os.path.abspath(__file__), "../{}.out".format(input_filename))
    inp = process_input(input_file)
    out = solve(inp)
    output(output_file, out)
