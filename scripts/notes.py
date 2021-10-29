#!/bin/env python3

def note_map(n):
    """
    map 0-11 to note names
    """
    return ['C', 'CS', 'D', 'DS', 'E', 'F', 'FS', 'G', 'GS', 'A', 'AS', 'B'][n]


print("#ifndef NOTES_H")
print("#define NOTES_H")

# prints '#define C1 0x18' to '#define C6 0x54'
# todo check if numbering matches ISO standard
for i in range(0x18, 0x54 + 1):
    print(f'#define {note_map(i % 12)}{(i - 0x18)//12 + 1} {hex(i)}')

print("#endif")
