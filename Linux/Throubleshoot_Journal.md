# Throubelshoot Journal

--- 

## Throuble Shooting 

Small section from the [Arch Doc](./Arch.md) about throubleshooting.

### Common Issues

- **Slow boot**: Check the boot time with `systemd-analyze blame` and `systemd-analyze critical-chain`. 
If you see a service taking too long, check its status with `systemctl status <service-name>` and its logs with `journalctl -u <service-name>`.

- **Idle waiting for keyboard input after locked screen (swaylock)**: Check the input of the following command 

```bash 
cat /etc/pam.d/swaylock
authselect current          # look for "with-fingerprint"
grep -r fprintd /etc/pam.d/

#
# PAM configuration file for the swaylock screen locker. By default, it includes
# the 'login' configuration file (see /etc/pam.d/login)
#
```

If the output looks like this:

```
auth include login
Profile ID: local
Enabled features:
- with-silent-lastlog
- with-fingerprint
- with-mdns4
```

then run:

```bash 
sudo authselect disable-feature with-fingerprint
```

### Broken System

If the system is broken and you cannot log in, boot into a live USB and mount the root partition. Then chroot into it:

```bash
sudo mount /dev/sdXn /mnt  # Replace sdXn with your root
```

--- 

## Thoubleshooting Julia in VS Code

During an update of the system, the Python version was upgraded from 3.14 to 3.15. PyCall which 
is a Julia package that allows calling Python from Julia, was built against the old version of Python.

```txt 
InitError: could not load library "/usr/lib64/libpython3.14.so.1.0"
during initialization of module PyCall
```

For the resolution of the problem, the following commands where run: 

**Version Check**

```bash 

ls /usr/lib64/libpython3*                  # which libpython versions exist

python3 --version                          # Python X.X.X

find ~/.julia/packages/PyCall -name deps.jl -path '*deps*' -exec cat {} \; # shows which libpython PyCall saved
```

**Rebuild PyCall against Python 3.15**

```bash
# Rebuild PyCall against Python 3.15
julia -e 'ENV["PYTHON"]="/usr/bin/python3"; using Pkg; Pkg.build("PyCall")'
```


**Reinstall the Python `sympy` module for 3.15**

```bash
python3 -m pip install --user sympy        # also installed mpmath as a dependency
```

Julia's `SymPy` package needs the Python `sympy` module. It had been installed
with pip under `~/.local/lib/python3.14/`, which Python 3.15 doesn't see.


### Future Reference

This could happen with other packages and updates, so to check other packages affected use: 

```bash 
ls ~/.local/lib/python3.14/site-packages

julia -e 'using Pkg; Pkg.build("PyCall")'
python3 -m pip install --user sympy   # plus any other pip packages you use
```

> When doing this, you are using a separate python environment for Julia 

### Conda Recomendation

To avoid this problem in the future, consider using a virtual environment or Conda to manage Python versions and dependencies. 

--- 

## Firewall Related

- **Docker**: If there are issues with Docker due to networking, check your firewall settings. 

For example, for `usw` you can use the following commands:  

```bash 
# Check the status of the firewall
sudo firewall-cmd --state

# Check if Docker is allowed
sudo firewall-cmd --list-all
```

- **Local Minecraft Server**:  If LAN connections are not working, check if the firewall is blocking 
the port for the Minecraft server. 

---




