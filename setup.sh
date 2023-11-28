#!/bin/bash

# Name of the virtual environment
VENV_NAME="myenv"

# Check if virtualenv is installed
if ! command -v virtualenv &>/dev/null; then
    echo "virtualenv not found! Installing..."
    pip install virtualenv
    if [ $? -ne 0 ]; then
        echo "Error: Failed to install virtualenv. Make sure pip is installed."
        exit 1
    fi
fi

# Create the virtual environment
if [ ! -d "$VENV_NAME" ]; then
    echo "Creating virtual environment named $VENV_NAME..."
    virtualenv "$VENV_NAME"
    if [ $? -ne 0 ]; then
        echo "Error: Failed to create virtual environment."
        exit 1
    fi
else
    echo "Virtual environment $VENV_NAME already exists."
fi

# Activate the virtual environment
echo "Activating virtual environment..."
source "$VENV_NAME/bin/activate"

# Check for requirements.txt and install
if [ -f "requirements.txt" ]; then
    echo "Installing requirements from requirements.txt..."
    pip install -r requirements.txt
    if [ $? -ne 0 ]; then
        echo "Error: Failed to install packages from requirements.txt."
        exit 1
    fi
else
    echo "requirements.txt not found. Skipping installation."
fi

echo "Done!"
