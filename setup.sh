#!/bin/bash

# Exit immediately if any command fails
set -e

echo "[INFO] Updating package lists..."
sudo apt update

echo "[INFO] Upgrading installed packages..."
sudo apt upgrade -y

echo "[INFO] Installing required packages..."
sudo apt install -y build-essential kmod linux-headers-$(uname -r) git

# Check if Git is installed
if ! command -v git &> /dev/null; then
    echo "[ERROR] Git is not installed. Install it manually and rerun the script."
    exit 1
fi

# Clone the repository if it doesn't already exist
REPO_DIR="physical-memory-access-module"
if [ ! -d "$REPO_DIR" ]; then
    echo "[INFO] Cloning repository..."
    git clone https://github.com/dp1405/physical-memory-access-module.git
else
    echo "[INFO] Repository already exists. Skipping clone."
fi

cd "$REPO_DIR"

echo "[INFO] Building kernel module..."
if ! make all; then
    echo "[ERROR] Failed to build the kernel module. Check the output above."
    exit 1
fi

echo "[SUCCESS] Build completed successfully!"
