#!/bin/bash
sed -z -e 's/[.]\n/:)\n/g' -e 's/[.]/$/g' sample.txt

