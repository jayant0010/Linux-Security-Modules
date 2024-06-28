# Linux Security Modules (LSM) Project

This project implements custom security policies in the Linux kernel using Linux Security Modules (LSM). It consists of two parts:

1. Modifying an existing LSM module to enforce a system time setting policy.
2. Creating a new LSM module that includes the system time policy and an additional CPU affinity policy.

## Part 1: Modifying an Existing LSM Module

### Objective

Implement a security policy using an existing LSM module to prevent resetting the system time to a past value.

### Steps

1. **Set Up the Environment**
   - Ensure you have a Linux VM with Ubuntu 16.04, 18.04, or 20.04.
   - Install the Linux kernel source and build toolchain (GCC).

2. **Locate and Modify the LSM Module**
   - Find an existing LSM module (e.g., Yama) under the `security` directory of the Linux kernel source.
   - Add a hook for setting the system time and implement a policy to prevent setting the time to a past value.

3. **Update the Kernel Source**
   - Use `pr_info` to log successful time resets and attempts to set the time to the past.
   - Recompile the kernel with the modified source.

4. **Testing**
   - Use the `dmesg` command to check kernel logs when attempting to reset the system time both in the future and in the past.

### Deliverable

- A diff of the original and modified kernel source files.
- `dmesg` logs showing the enforcement of the policy.

## Part 2: Creating a New LSM Module

### Objective

Create a new LSM module named "oss-lsm" that includes the system time resetting hook and an additional CPU affinity policy.

### Steps

1. **Set Up the Environment**
   - Ensure you have the necessary build tools and kernel source as in Part 1.

2. **Create the New LSM Module**
   - Create a new directory `oss-lsm` under the `security` directory.
   - Implement the system time setting hook and policy in `oss-lsm.c`.

3. **Integrate with Kbuild**
   - Update `Kbuild` and `Kconfig` under the `security` directory to include the new `oss-lsm` module.
   - Create a `Makefile` within the `oss-lsm` directory to compile `oss-lsm.c`.

4. **Update Kernel Configuration**
   - Modify the `.config` file to add and enable the new `oss-lsm` module.

5. **Recompile and Install the Kernel**
   - Recompile the Linux kernel with the new `oss-lsm` module.
   - Install the new kernel image.

6. **Testing**
   - Use `dmesg` to collect kernel logging information demonstrating the new module in use.

### Deliverable

- A diff of the kernel source and modified files.
- The entire `oss-lsm` directory with all source files.
- `dmesg` logs showing the new module's functionality.

## Getting Started

### Prerequisites

- Linux kernel source
- GCC and build tools
- A Linux distribution (Ubuntu 16.04, 18.04, or 20.04 recommended)

### Building and Installing the Kernel

1. Clone the Linux kernel source:
   ```sh
   git clone https://github.com/torvalds/linux.git
   cd linux
   ```

2. Apply your modifications and create the `oss-lsm` directory and files.

3. Configure the kernel:
   ```sh
   make menuconfig
   ```

4. Build the kernel:
   ```sh
   make -j$(nproc)
   ```

5. Install the new kernel:
   ```sh
   sudo make modules_install
   sudo make install
   ```

6. Reboot into the new kernel:
   ```sh
   sudo reboot
   ```

### Verifying the Changes

Use the `dmesg` command to verify that the security policies are being enforced:
```sh
dmesg | grep "LSM"
```

## Conclusion

This project demonstrates how to extend the Linux kernel's security capabilities using LSM. By modifying an existing module and creating a new one, custom security policies can be implemented and enforced effectively.
