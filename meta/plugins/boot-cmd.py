from osdk import utils, build
import os
import shutil


DEFAULT_LOADER = "limine"


def kvmAvailable() -> bool:
    if os.path.exists("/dev/kvm") and os.access("/dev/kvm", os.R_OK):
        return True
    return False


def download_limine(efi: str, boot: str):
    BRANCH = "v4.x-branch-binary"
    limine = utils.downloadFile(
        f"https://github.com/limine-bootloader/limine/raw/{BRANCH}/BOOTX64.EFI"
    )
    shutil.copy(limine, f"{efi}/BOOTX64.EFI")
    shutil.copy("meta/config/limine.cfg", f"{boot}/limine.cfg")


def bootCmd(opts: dict, args: list[str]) -> None:
    ovmf = utils.downloadFile(
        "https://retrage.github.io/edk2-nightly/bin/DEBUGX64_OVMF.fd"
    )

    sysroot_dir = utils.mkdirP(".osdk/images/sysroot")
    efiboot_dir = utils.mkdirP(".osdk/images/sysroot/EFI/BOOT")
    boot_dir = utils.mkdirP(".osdk/images/sysroot/boot")

    try:
        loader = args[0]
    except IndexError:
        loader = DEFAULT_LOADER

    match loader:
        case "limine":
            download_limine(efiboot_dir, boot_dir)
        case _:
            raise utils.CliException(f"No such loader {loader}")

    chibi = build.buildOne("default", "chibi", props = {"loader": loader})
    shutil.copy(chibi, f"{boot_dir}/kernel.elf")

    qemuCmd = [
        "qemu-system-x86_64",
        "-no-reboot",
        "-no-shutdown",
        "-d", "guest_errors,cpu_reset",
        "-serial", "mon:stdio",
        "-bios", ovmf,
        "-smp","4",
        "-drive", f"file=fat:rw:{sysroot_dir},media=disk,format=raw",
    ]

    if kvmAvailable():
        qemuCmd += ["-enable-kvm"]
    else:
        print(f"KVM not available, using QEMU-TCG")

    utils.runCmd(*qemuCmd)


__plugin__ = {
    "name": "boot",
    "desc": "Boot a component in a QEMU instance",
    "func": bootCmd,
}
