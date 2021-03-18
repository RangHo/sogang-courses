import os
import argparse
import re
from itertools import product


fpga_input_pins = {
    'clock': 'R4',
    'switch': {
        'reset': 'U7',
        'push_up': 'E21',
        'push_left': 'D21',
        'push_mid': 'G21',
        'push_right': 'G22',
        'push_down': 'F21',
        'dip_0': 'J4',
        'dip_1': 'L3',
        'dip_2': 'K3',
        'dip_3': 'M2',
        'dip_4': 'K6',
        'dip_5': 'J6',
        'dip_6': 'L5',
        'dip_7': 'L4',
        'dip_8': 'Y16',
        'dip_9': 'AA16',
        'dip_10': 'AB16',
        'dip_11': 'AA17',
        'dip_12': 'AA13',
        'dip_13': 'AB13',
        'dip_14': 'AA15',
        'dip_15': 'AB15'
    }
}


fpga_output_pins = {
    'led': {
        'led_0': 'F15',
        'led_1': 'F13',
        'led_2': 'F14',
        'led_3': 'F16',
        'led_4': 'E17',
        'led_5': 'C14',
        'led_6': 'C15',
        'led_7': 'E13',
        'led_8': 'AA10',
        'led_9': 'AA11',
        'led_10': 'V10',
        'led_11': 'W10',
        'led_12': 'Y11',
        'led_13': 'Y12',
        'led_14': 'W11',
        'led_15': 'W12'
    },
    '7_segment': {
        'seg_a': 'D20',
        'seg_b': 'C20',
        'seg_c': 'C22',
        'seg_d': 'B22',
        'seg_e': 'B21',
        'seg_f': 'A21',
        'seg_g': 'E22',
        'seg_dp': 'D22',
        'digit_1': 'E14',
        'digit_2': 'E16',
        'digit_3': 'D16',
        'digit_4': 'D14',
        'digit_5': 'AB11',
        'digit_6': 'AB12',
        'digit_7': 'AA9',
        'digit_8': 'AB10'
    }
}


def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')


def get_module_name(file_name):
    return os.path.basename(file_name[:-2])


def analyze_pins(file_name):
    """ Analyze a file and create a list of input and output files. """
    content = None

    pin_list = []
    input_list = []
    output_list = []

    try:
        with open(file_name, 'r') as input_file:
            content = input_file.read()
    except:
        print("Unable to open file " + file_name + "! Abortig...")
        return None

    # Find 'module' directive
    module_regex = re.compile(r'module \w+\s*(\(([\w\s,]+)\))?;')
    module_match = module_regex.search(content)

    # If the first group doesn't exist, that means it exposes no pins at all
    # so just skip the whole thing
    if not module_match.group(1):
        print(f"{file_name} doesn't expose any pin! Skipping...")
        return None

    # Grab the comma-separated list of pins
    argument_sanitizer_regex = re.compile(r',\s+')
    module_args = argument_sanitizer_regex.sub(
        ",", module_match.group(2)).strip()

    pin_list = module_args.split(',')

    # Analyze pin list and determine input and output pins
    pin_mode = None
    for pin in pin_list:
        if pin.startswith('input'):
            pin_mode = 'input'
            pin = pin[6:]  # consume the input keyword
        elif pin.startswith('output'):
            pin_mode = 'output'
            pin = pin[7:]  # consume the output keyword

        if pin_mode == 'input':
            input_list.append(pin)
        elif pin_mode == 'output':
            output_list.append(pin)
        else:
            continue

    content_position = module_match.end()
    input_regex = re.compile(r'input\s+(\w+(,\s+\w+)*);')
    output_regex = re.compile(r'output\s+(\w+(,\s+\w+)*);')

    # If input length + output length is not equal to total pin length
    # then there must be some pins that are undefined
    while len(pin_list) > len(input_list) + len(output_list):
        input_match = input_regex.search(content, content_position)
        output_match = output_regex.search(content, content_position)

        input_decl_list = argument_sanitizer_regex \
            .sub(',', input_match.group(1)) \
            .strip() \
            .split(',') \
            if input_match else []
        output_decl_list = argument_sanitizer_regex \
            .sub(',', output_match.group(1)) \
            .strip() \
            .split(',') \
            if output_match else []

        # Extend the input and output lists
        input_list.extend(input_decl_list)
        output_list.extend(output_decl_list)

        input_end = input_match.end() if input_match else -1
        output_end = output_match.end() if output_match else -1

        content_position = input_end if input_end > output_end else output_end

    return (input_list, output_list)


def generate_constraints(file_name):
    """ Generate constraints from a module. """

    result = analyze_pins(file_name)

    if not result:
        return

    input_list, output_list = result

    # Selection menu helper
    def select_fpga_pin(fpga_pin_dict, verilog_pin):
        # Create a pseudo-static property to save pins that are already chosen
        if not hasattr(select_fpga_pin, 'selected_pins'):
            select_fpga_pin.selected_pins = {}

        choice = [fpga_pin_dict]
        while isinstance(choice[-1], dict):
            # Clear the screen before showing the menu
            clear_screen()

            print("Creating XDC constraints file for {}!".format(file_name))
            print("Choose package pin to link with Verilog pin [{}]:".format(
                verilog_pin))
            for key in choice[-1]:
                if key in select_fpga_pin.selected_pins:
                    print(" - {:16} => {}".format(key,
                          select_fpga_pin.selected_pins[key]))
                else:
                    print(" - {}".format(key))

            print("Type `prev` to view the previous menu.")
            raw_choice = input(">>> ")

            if raw_choice == "prev" and len(choice) > 1:
                choice.pop()
                continue

            if raw_choice not in choice[-1]:
                continue

            choice.append(choice[-1][raw_choice])

        # If the pin is already selected, ask again
        if raw_choice in select_fpga_pin.selected_pins:
            print("It seems this pin was already selected before!")
            print("Are you sure you want to select this pin again?")
            if input("(y/N) ").lower() != 'y':
                return select_fpga_pin(fpga_pin_dict, verilog_pin)

        # Mark the package pin as selected
        select_fpga_pin.selected_pins[raw_choice] = verilog_pin
        return choice[-1]

    with open(get_module_name(file_name) + "_constraints.xdc", "w") as f:
        # Set IO standards for all pins
        for pin in input_list + output_list:
            f.write(
                "set_property IOSTANDARD LVCMOS18 [get_ports {}]\n".format(pin)
            )

        # Link input pins
        for verilog_pin in input_list:
            choice = select_fpga_pin(fpga_input_pins, verilog_pin)
            print("Linking Verilog pin {} with package pin {}...".format(
                verilog_pin, choice))
            f.write("set_property PACKAGE_PIN {} [get_ports {}]\n".format(
                choice, verilog_pin))

        # Link output pins
        for verilog_pin in output_list:
            choice = select_fpga_pin(fpga_output_pins, verilog_pin)
            print("Linking Verilog pin {} with package pin {}...".format(
                verilog_pin, choice))
            f.write("set_property PACKAGE_PIN {} [get_ports {}]\n".format(
                choice, verilog_pin))

        del select_fpga_pin.selected_pins


def generate_testbench(file_name):
    """ Generate testbench from a file. """

    result = analyze_pins(file_name)

    if not result:
        return

    input_list, output_list = result

    with open(get_module_name(file_name) + "_tb.v", "w") as f:
        # Write timescale
        f.write("`timescale 1ns / 1ps\n")
        f.write("\n")

        # Write module declaration
        f.write("module {}_tb;\n".format(get_module_name(file_name)))
        f.write("\n")

        # Write registers
        f.write("    reg ")
        for input_var in input_list:
            f.write(input_var)
            if input_var != input_list[len(input_list) - 1]:
                f.write(', ')
            else:
                f.write(';\n')

        # Write wires
        f.write("    wire ")
        for output_var in output_list:
            f.write(output_var)
            if output_var != output_list[len(output_list) - 1]:
                f.write(', ')
            else:
                f.write(';\n')

        # Define testing device
        f.write("    {} DUT (\n".format(get_module_name(file_name)))
        for var in input_list + output_list:
            f.write("        .{0}({0})".format(var))
            if var != output_list[len(output_list) - 1]:
                f.write(",\n")
            else:
                f.write('\n')
        f.write("    );\n")
        f.write("\n")

        # Start testing
        f.write("    initial begin\n")

        for item in product([0, 1], repeat=len(input_list)):
            for i in range(len(input_list)):
                f.write("        {} = {};\n".format(input_list[i], item[i]))
            f.write("        #20;\n")
            f.write("\n")

        f.write("        $finish;\n    end\n\nendmodule\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Generate constraints or testbench from a verilog file.'
    )
    parser.add_argument('--testbench', '-t',
                        action='store_true',
                        help="Generate testbench file")
    parser.add_argument('--constraints', '-c',
                        action='store_true',
                        help="Generate constraints file")
    parser.add_argument('file',
                        nargs='+',
                        help="Verilog file to analyze")

    args = parser.parse_args()

    # If nothing is specified, do all of them
    if not args.testbench and not args.constraints:
        args.testbench = args.constraints = True

    for f in args.file:
        if args.testbench:
            generate_testbench(f)
        if args.constraints:
            generate_constraints(f)
