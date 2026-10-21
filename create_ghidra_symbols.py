import regex

SYMBOLS_PATH = "config/SB4E01/symbols.txt"
GHIDRA_SYMBOLS_PATH = "ghidra_symbols.txt"

symbol_match = r"(?P<symbol>.+?)\s=\s(?P<section>.+?)\b:(?P<address>0x[0-9a-fA-F]+?)\b; // type:\b(?P<type>[a-zA-Z]+?)\b\ssize:\b(?P<size>0x[0-9a-fA-F]+?)\b(?P<other>.*)"
symbol_regex = regex.compile(symbol_match)


with open(SYMBOLS_PATH, "r") as rf, open(GHIDRA_SYMBOLS_PATH, "w") as wf:
    for line in rf:
        if (symbol := symbol_regex.match(line.rstrip())) is None:
            continue

        symbol_name = symbol.group("symbol")
        symbol_section = symbol.group("section")
        symbol_address = symbol.group("address")
        symbol_type = symbol.group("type")
        symbol_size = symbol.group("size")
        symbol_other = symbol.group("other")

        symbol_address = int(symbol_address, 16)

        if "0x" in symbol_size:
            symbol_size = int(symbol_size, 16)
        else:
            symbol_size = int(symbol_size)

        if symbol_section == ".text":
            wf.write(f"{symbol_name} 0x{symbol_address:08X} f\n")
        elif symbol_section == ".init":
            wf.write(f"{symbol_name} 0x{symbol_address:08X} f\n")
        else:
            wf.write(f"{symbol_name} 0x{symbol_address:08X} l\n")
