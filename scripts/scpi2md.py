#
# Convert the source EtherBenchFirmware commands into the nicely formatted source
#

# Config path
# EtherBenchFirmware/src/tasks/parser/config/commands.toml

print("Working...")
print("Done")

with open("EtherBenchFirmware/src/tasks/parser/config/commands.toml", "r") as f:
    print(f.readlines())

# Elements lists:
# Required :
# description:
# args : dict
# returns : dict
#
# Optionnal
# duration: Timings
# blocking: Y/N
# image: Insert an image
# note:
# tip:
# important:
# warning:
# caution:
# ex_command:
# ex_ret:
# ex_comment:
