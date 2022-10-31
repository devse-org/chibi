from osdk import utils, build


def bootCmd(opts: dict, args: list[str]) -> None:
    chibi = build.buildOne("default", "chibi")

    qemuCmd = [
        "qemu-system-i386",
        "-no-reboot",
        "-no-shutdown",
        "-d", "guest_errors,cpu_reset",
        "-kernel", chibi,
        "-debugcon", "stdio",
        "-machine", "type=pc-i440fx-3.1"
    ]

    utils.runCmd(*qemuCmd)


__plugin__ = {
    "name": "boot",
    "desc": "Boot a component in a QEMU instance",
    "func": bootCmd,
}
