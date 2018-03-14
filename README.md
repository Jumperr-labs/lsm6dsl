# Jumper Virtual Lab Peripheral Model - AT25SF081
This repo contains a model for the [lsm6dsl](http://www.st.com/en/mems-and-sensors/lsm6dsl.html) SPI accelerometer for [Jumper Virtual Lab](https://vlab.jumper.io).

For more information, visit [the docs](https://docs.jumper.io).

### Prerequisites
- GCC and Make: `apt install build-essential`
- [Jumper Virtual Lab](https://docs.jumper.io)

## Usage
- Follow the following steps in order to build the peripheral model:

  ```bash
  git clone https://github.com/Jumperr-labs/lsm6dsl.git
  cd lsm6dsl
  make
  ```

- If the peripheral model was build successfully, the result will be ready under "_build/LSM6DSL.so".
Copy this file to you working diretory, same one as the "board.json" file.
- Add the following component in your "board.json" file. Make sure to change the pin numbers to fit your configuration.

```json
{
  "name": "LSM6DSL",
  "id": 2,
  "type": "Peripheral",
  "file": "LSM6DSL.so",
  "config": {
    "pins": {
      "int2": 14,
      "int1": 16,
      "cs": 15,
      "sck": 0,
      "si": 21,
      "so": 1,
      "sa0": 10
    }
  }
}
```

## License
Licensed under the Apache License, Version 2.0. See the LICENSE file for more information
