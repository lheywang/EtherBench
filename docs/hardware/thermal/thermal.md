# Thermal management

On the motherboard, only few components are sensitive to thermal stress. These are:

- Power regulators
- Main MCU

Others aren't using enough power to be concerned by thermal management.

## Passive cooling

By default, only passive cooling is available on the system.
All the sensitive circuits use the main board as heatsink, which provide a first cooling method.

An openning on the top level board enable the natural convection to be done, and thus, extract hot air from the system.
Do not try to block it.

## Forced cooling

In any case, if the passive cooling is not enough, for example, for long and power intensive tests, or,
simply because the external conditions require it, an 5V PWM fan connector is available.

The latter one is controlled by the STM32 from different temperature sensors, and will output a proportionnal duty cycle.

This fan can be used to force the air cycle trough the device, and thus, cool it.
