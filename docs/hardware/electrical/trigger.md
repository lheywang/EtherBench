# Triggering other devices

The motherboard is equipped with a trigger output, in the format of a standard BNC connector, matched to 50 Ohms.

The system can output short pulses (3.3V, 4 ns typically) on that connector, on specific events (matched frame, error...).
The configuration is done by the user.

The rising and falling times are short (< 1 ns), and boosted by the dedicated line buffer.

## How to use it

This output can be wired to any scopes or electrical device that has a trigger input, to start a measurement on a specific
condition. This can grealty extend the device ability, as these measures can be very specific, and way faster than we can imagine on the device.

The tool must be configured to use external trigger input, with a threshold of 1.65V.
