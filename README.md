# SLForceFPS

Forces a constant refresh rate on OSX's SkyLight window server.

## Usage

* [AMFIExemption][1] KEXT is required to use private entitlements.
* `./SLForceFPS -r 60` to force 60 refreshes per second
* `./SLForceFPS -r 0` disables constant refresh

## Power Usage

It is not recommended that you run this on battery powered devices as it will reduce your battery life. It also will not allow your CPU to idle as much.

  [1]: https://github.com/osy86/AMFIExemption
