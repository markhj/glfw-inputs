# Input Manager 🔭

The ``Manager`` class is responsible for translating control inputs, and
process them, so they can be provided in a streamlined fashion to the provided
control instances.

See the [Getting started chapter](../getting-started/basic-usage.md) to learn how to use it.

## Notes 📜

- The decision to keep ``onMove`` as a callback on the [ControlMapping](../controls/control-mapping.md) class, instead
  of
  on this ``Manager`` class, is because movement handling cannot be assumed to be the same across all mappings.
