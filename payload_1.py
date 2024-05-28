# // alamin masharqa 207358326            adan fadila 314705062 

# Define the content for the username and password exactly as provided
username = b"amin\n"
password = b"11111111111\n"

# Create the binary file with the payload
with open("var_buf_overflow.bin", "wb") as f:
    f.write(username + password)
