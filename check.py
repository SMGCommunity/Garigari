# check.py
# script that marks functions as decompiled based on matching status

import os
from typing import overload
from elftools.elf.elffile import ELFFile
from colorama import Fore, Style
import glob
import hashlib
import sys
import struct
from capstone import *
from capstone.ppc import *
import pathlib
from collections import OrderedDict

class Function:
    def __init__(self, name, addr, size, matched):
        self.name = name
        self.addr = addr
        self.size = size
        if matched == "true":
            self.matched = True
        else:
            self.matched = False

class FunctionLibrary:
    def __init__(self):
        self.funcs = []

    def load(self):
        with open("data/funcs.csv", "r") as f:
            lines = f.readlines()

        for line in lines:
            if "Symbol Name" in line:
                continue

            spl = line.split(",")
            self.funcs.append(Function(spl[0], spl[1], spl[2], spl[3].rstrip("\r\n")))

    def getAddrFromSymbol(self, sym):
        for func in self.funcs:
            if func.name == sym:
                return int(func.addr, 16)

        return 0

    def getSizeFromSymbol(self, sym):
        for func in self.funcs:
            if func.name == sym:
                return int(func.size, 16)

        return 0

    def isDecompiled(self, sym):
        for func in self.funcs:
            if func.name == sym:
                return func.matched

        return False

    def markDecompiled(self, sym, cond):
        for func in self.funcs:
            if func.name == sym:
                func.matched = cond
    
    def save(self):
        with open("data/funcs.csv", "w") as w:
            w.write("Symbol Name, Symbol Address, Function Size, Matched\n")

            for func in self.funcs:
                decomp = "false"
                if func.matched == True:
                    decomp = "true"
                w.write(f"{func.name},{func.addr},{func.size},{decomp}\n")

def print_help_and_exit():
    print("Usage: check.py [mangled_symbol] [obj_file]")
    print("\t[mangled_symbol]: name of the symbol that should be checked.")
    print("\t[obj_file]: name of the object file that the function is contained in.")

    sys.exit(0)

def is_dol_correct():
    with open("baserom.dol", "rb") as input:
        data = input.read()

        hash = hashlib.sha256(data).hexdigest().upper()
        return hash == "F0F1638545A21366A2D86CF33AF1E7AB8AB286FAED8358152FBA7BE82C904A34" or hash == "ABEA6B0C498C4AF90B17CFA08D54A01781186F097BEE3E0761DBFB4838CBC281"

def get_code_from_dol(address, size):
    with open("baserom.dol", "rb") as input:
        data = input.read()
        
        # Grab .text offset and start offset
        txt_offset, = struct.unpack_from(">I", data, 4)
        start_address, = struct.unpack_from(">I", data, 0x4C)
        print(address)
        offset = address - start_address

        return data[txt_offset + offset:txt_offset + offset + size]

def print_error(message):
    print(f"ERROR: {message}")

def print_warning(message):
    print(f"WARNING: {message}")

def print_hint(message):
    print(f"HINT: {message}")

def print_instruction_comparison_error(message, original, custom):
    print_error(message)
    print_instruction_comparison(original, custom)

def print_instruction_comparison_warning(message, original, custom):
    print_warning(message)
    print_instruction_comparison(original, custom)

def print_instruction_comparison_hint(message, original, custom):
    print_hint(message)
    print_instruction_comparison(original, custom)

def print_instruction_comparison(original, custom):
    print(f"\tOriginal: {original}")
    print(f"\tCustom:   {custom}")

def check_symbol(function_library, mangled_symbol, obj_name):
    black_listed_instructions = {
        PPC_INS_VMSUMSHM, PPC_INS_VMHADDSHS, PPC_INS_XXSLDWI, PPC_INS_VSEL,
        PPC_INS_XVSUBSP, PPC_INS_XXSEL, PPC_INS_XVMULSP, PPC_INS_XVDIVSP,
        PPC_INS_VADDUHM, PPC_INS_XXPERMDI, PPC_INS_XVMADDASP, PPC_INS_XVMADDMSP,
        PPC_INS_XVCMPGTSP, PPC_INS_XXMRGHD, PPC_INS_XSMSUBMDP, PPC_INS_XSTDIVDP,
        PPC_INS_XVADDSP, PPC_INS_XVCMPEQSP, PPC_INS_XVMSUBASP, PPC_INS_XVCMPGESP,
        PPC_INS_MFESR, PPC_INS_MFDEAR, PPC_INS_MTESR, PPC_INS_MTDEAR, PPC_INS_MFICCR, PPC_INS_MFASR
    }

    obj_files = glob.glob(f"build/**/{obj_name}.o", recursive=True)

    if len(obj_files) > 1:
        print("Found multiple .o files. This should not happen.")
        return False

    if len(obj_files) == 0:
        print("Could not find any .o files for the function.")
        return False

    with open(pathlib.Path(obj_files[0]), "rb") as input:
        elf_file = ELFFile(input)
        symtab = elf_file.get_section_by_name('.symtab')

        if symtab.get_symbol_by_name(mangled_symbol) is None:
            print("Could not find symbol in object file. This may be caused by the code not being compiled, the function being in the wrong C++ source file or the function signature being wrong.")
            return False

        compiled_symbol = symtab.get_symbol_by_name(mangled_symbol)[0]

        # Get custom code
        custom_offset = compiled_symbol["st_value"]
        custom_size = compiled_symbol['st_size']

        text = elf_file.get_section_by_name('.text')
        custom_data = text.data()[custom_offset:custom_offset + custom_size]

        # Get original code
        original_address = function_library.getAddrFromSymbol(mangled_symbol)
        original_size = function_library.getSizeFromSymbol(mangled_symbol)

        if original_address == None or original_size == None:
            print("Could not find address and/or size for symbol")
            return False

        original_data = get_code_from_dol(original_address, original_size)

        if original_data == None:
            print("Could not get data from DOL file.")
            return False

        cs = Cs(CS_ARCH_PPC, CS_MODE_32 | CS_MODE_BIG_ENDIAN)
        cs.detail = True
        cs.imm_unsigned = False

        original_instructions = list(cs.disasm(original_data, 0))
        custom_instructions = list(cs.disasm(custom_data, 0))

        error_count = 0
        warning_count = 0
        hint_count = 0

        # Capstone doesn't seem to handle paired single instructions
        # If any is found, it just stops disassembling
        if 4 * len(original_instructions) != original_size:
            print_warning(f"Only {len(original_instructions)} out of the {original_size // 4} original instructions were loaded.")
            warning_count += 1

        if 4 * len(custom_instructions) != custom_size:
            print_warning(f"Only {len(custom_instructions)} out of the {custom_size // 4} custom instructions were loaded.")
            warning_count += 1

        if original_size > custom_size:
            print_error("Original code contains more instructions than custom code.")
            error_count += 1
        elif original_size < custom_size:
            print_error("Original code contains less instructions than custom code.")
            error_count += 1

        for i in range(min(len(original_instructions), len(custom_instructions))):
            line = i * 4
            line_string = f"{hex(line)} (Original: {hex(original_address + line)})"

            original_instruction = original_instructions[i]            
            custom_instruction = custom_instructions[i]

            original_operands = original_instruction.operands
            custom_operands = custom_instruction.operands

            if str(original_instruction) == str(custom_instruction):
                print(f"{Fore.GREEN}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                # Fully identical, nothing to be checked
                continue

            if original_instruction in black_listed_instructions:
                print_warning(f"Skipping blacklisted instruction at line {line_string}.")
                warning_count += 1
                continue
            
            if original_instruction.id == custom_instruction.id:
                assert(len(original_operands) == len(custom_operands))

                # First check common r2 and r13 issues
                if original_instruction.id in { PPC_INS_LBZ, PPC_INS_LWZ, PPC_INS_STB, PPC_INS_STW, PPC_INS_LFS }:
                    #assert(len(original_operands) == 2 and len(custom_operands) == 2)

                    # lbz, lwz, stb, stw and lfs are sometimes used with r13, which is a pointer to a read-write
                    # small data area (SDA). When compiling custom code, this SDA is not generated,
                    # so the register is set to r0 and the displacement is set to 0.

                    # Original must be (instr) rX, X(r13) and custom must be (instr) rX, 0(r0)
                    if original_operands[1].reg == PPC_REG_R13 and custom_operands[1].reg == PPC_REG_R0 and\
                            custom_operands[1].mem.disp == 0 and original_operands[0].reg == custom_operands[0].reg:
                        print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                        #print_instruction_comparison_hint(f"Skipping r13 issue at line {line_string}.", original_instruction, custom_instruction)
                        hint_count += 1
                        continue
                    
                if original_instruction.id in { PPC_INS_LWZ, PPC_INS_LFS, PPC_INS_LHZ, PPC_INS_LFS }:
                    #assert(len(original_operands) == 2 and len(custom_operands) == 2)

                    # Same as above, except with r2 instead of r13. r2 is a pointer to a read-only SDA.

                    # Original must be (instr) rX, X(r2) and custom must be (instr) rX, 0(0)
                    if original_operands[1].reg == PPC_REG_R2 and custom_operands[1].reg == PPC_REG_R0 and\
                            custom_operands[1].mem.disp == 0 and original_operands[0].reg == custom_operands[0].reg:
                        print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                        #print_instruction_comparison_hint(f"Skipping r2 issue at line {line_string}.", original_instruction, custom_instruction)
                        hint_count += 1 
                        continue

                # Check if all registers are equal
                registers_equal = True 

                for j in range(len(original_operands)):
                    if original_operands[j].reg != custom_operands[j].reg:
                        registers_equal = False
                        break

                if registers_equal:
                    print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_warning(f"Registers are identical but the instruction is not identical at line {line_string}.", original_instruction, custom_instruction)
                    warning_count += 1
                elif original_instruction.id == PPC_INS_ADDI:
                    # addi is commonly used when loading addresses
                    print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_warning(f"Skipping addi instruction at line {line_string}.", original_instruction, custom_instruction)
                    warning_count += 1
                elif original_instruction.id == PPC_INS_LIS:
                    # Same as addi
                    print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_warning(f"Skipping lis instruction at line {line_string}.", original_instruction, custom_instruction)
                    warning_count += 1
                elif original_instruction.id in { PPC_INS_B, PPC_INS_BL }:
                    # bl is used to call most functions, and since the functions are likely to be placed
                    # differently it's not possible to compare it
                    # If a function ends with a function call, and the returned value from the function, then b is sometimes used for branching
                    # to that function. Then it's not possible to compare this
                    print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_warning(f"Skipping branch instruction at line {line_string}.", original_instruction, custom_instruction)
                    warning_count += 1                
                else:
                    print(f"{Fore.RED}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_error(f"Instruction mismatch on line {line_string}.", original_instruction, custom_instruction)
                    error_count += 1                
            elif original_instruction.id == PPC_INS_ADDI and custom_instruction.id == PPC_INS_LI:
                assert(len(original_operands) == 3 and len(custom_operands) == 2)

                # This is caused by the read-write SDA, pointed by r13, is not generated in the custom code.

                # Original must be addi rX, r13, X and custom must be li rX, 0
                if original_operands[1].reg == PPC_REG_R13 and custom_operands[1].imm == 0 and\
                        original_operands[0].reg == custom_operands[0].reg:
                    print(f"{Fore.YELLOW}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_hint(f"Found addi / li mismatch at line {line_string}.", original_instruction, custom_instruction)
                    hint_count += 1
                else:
                    print(f"{Fore.RED}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                    #print_instruction_comparison_error(f"Instruction mismatch on line {line_string}.", original_instruction, custom_instruction)
                    error_count += 1
            else:
                print(f"{Fore.RED}{str(original_instruction):<80}{custom_instruction}{Style.RESET_ALL}")
                #print_instruction_comparison_error(f"Instruction mismatch on line {line_string}.", original_instruction, custom_instruction)
                error_count += 1


        print()
        print(f"Check finished with {error_count} error(s), {warning_count} warning(s) and {hint_count} hint(s).")

        is_decompiled = function_library.isDecompiled(mangled_symbol)
        passed = error_count == 0

        if passed:
            if is_decompiled:
                print("Function already marked as decompiled.")
            else:
                print("Marking as decompiled...")
                function_library.markDecompiled(mangled_symbol, True)
        else:
            if is_decompiled:
                print("Function is marked as decompiled, but does not match.")
                print("Unmarking as decompiled...")
                function_library.markDecompiled(mangled_symbol, False)
            else:
                print("Function is not marked as decompiled, and does not match either.")

        return passed

mangled_symbol = sys.argv[1]
obj_file = sys.argv[2]
compare = False
show_hints = True
show_warnings = True
show_errors = True

function_library = FunctionLibrary()
function_library.load()

if not is_dol_correct():
    print("DOL file is not valid.")
    sys.exit(1)

if check_symbol(function_library, mangled_symbol, obj_file) == True:
    function_library.save()
