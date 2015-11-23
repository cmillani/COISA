#!/bin/bash

make benchmarks/models/blockly.x
python scripts/arduino_loader.py benchmarks/models/blockly.x -bt