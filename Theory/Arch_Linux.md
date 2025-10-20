# Arch Linux Setup

Documentatiion for seeting up Arch Linux with the necessary tools and configurations for development.

## Installation 

1. Download the latest Arch Linux ISO from the [official website](https://archlinux.org/download/).

2. Create a bootable USB drive using tools like `Fedora Media Writer`.

3. Boot from the USB drive and select the Arch Linux installation option.

4. You can just follow the installation guide on the [Arch Wiki](https://wiki.archlinux.org/title/Installation_guide) to set up your system. But we will 
provide a some own ownsteps here.

### Custom Installation Steps

1. **Load Keys if needed:** `loadkeys de-latin1` for German

2. **Increase Font:** `setfont ter-132b` or `setfont -d`

3. **Connect to the internet**: Ensure the network interface is listed and enable with `ip link` 
For wireless connections run: `iwctl` and then run the following commands insede `[idw]#`in order:

- `device list`
- `device name set-property Powered on`
- `adapter adapter set-property Powered on`
- `station name scan`
- `station name get-networks`
- `station name connect SSID`
- `station name connect-hidden SSID`
-  Press `Crl + d` to quit

For direct connections you can skip and type: `- $ iwctl --passphrase passphrase station name connect SSID`
And to disconnect if needed: `[iwd]# station device disconnect`

4. **Update the system clock:** `timedatectl`

5. **Partion the disks using fdisk:** Identify the hardrive using `lsblk` then run the following commands in order:

- `fdisk /dev/your_drive_name`
- `p` Prints the partitions
- `g` Gives us an empty partition table 
- `n` Creates a new partition - `Enter` - `Enter` - `+1G` - `Y` if prompted
- `n` Creates a new partition - `Enter` - `Enter` - `+4G` - `Y` if prompted
- `n` Creates a new partition - `Enter` - `Enter` - `Enter` - `Y` if prompted

**Optional** because we are going to format them manually anyway

- `t` Mark a partition with a type - `2` - `82` For the swap type 
- `t` Mark a partition with a type - `3` - `48` For the linux file system type
- `t` Mark a partition with a type - `1` - `1` For the boot type

**Finally**

- `w` Write and quit

In case you messed up you can use `d` to delete a partition or `q` to quit without saving and start again.

6. **Format the partitions:**

Type the following commands to format the partition. I recommend using `ext4` or 
`btrfs` for the filesystem. Type the actual name o your partition in the following commands

- `mkfs.btrfs /dev/nvme0n1p3/`
- `mkfs.fat -F 32 /dev/nvme0n1p1/`
- `mkfs.swap /dev/nvme0n1p2/`
 
7. **Mount the filesystem:**

- `mount /dev/nvme0n1p3 /mnt`
- `mkdir -p /mnt/boot/efi`
- `mount /dev/nvme0n1p1 /mnt/boot/efi`
- `swapon /dev/nvme0n1p2`

8. **Install Essentials Packages:**

- `pacstrap /mnt base linux linux-firmware sof-firmware base-devel grub efibootmgr vim nano networkmanager ly dunst`

If asked for some audio dependency choose `pulse`

9. **Fstab**

- `genfstab /mnt > /mnt/etc/fstab`

10. **Chroot**

Enter the installed system 

- `arch-chroot /mnt`

11. **Time**

Run inside arch:

- `ln -sf /usr/share/zoneinfo/Europe/Berlin /etc/localtime`
- `hwclock --systohc`


12. **Localization**

Run inside arch:

- `vim /etc/locale.gen` Uncomment `en_US.UTF-8 UTF-8` for english and write changes 
- `locale-gen`
- `vim /etc/locale.conf` Type `LANG=en_US.UTF-8` for english and write changes 
- `vim /etc/vconsole.conf` Type`KEYMAP=us` for english and write changes 

13. **Host Name**

Choose an epic name for the computer

- `vim /etc/hostname` Type `Father` or some epic name.

14. **Root Password**

Run `passwd` and type a safe root password

15. **User plus sudo**

Creating user in the group wheel

- `useradd -m -G wheel -s /bin/bash migu`
- `passwd migu`

Sudo:

- `EDITOR=vim visudo` - Then Uncomment the line: `%wheel ALL=(ALL) ALL` and save

16. **Enbling core services**

- `systemctl enable NetworkManager`
- `systemctl enable ly.service`

17. **Bootloader**

- `grub-install /dev/nvme0n1`
- `grub-mkconfig -o /boot/grub/grub.cfg`

18. **Reboot**

- `exit`
- `umount -a`
- `reboot`

If everything was done correctly you sould have a working installation.

---

## Post Install

### Connecto to the internet via Wifi

List nearby Wi-Fi networks:

- `nmcli device wifi list`

Connect to a Wi-Fi network:

- `nmcli device wifi connect SSID_or_BSSID password password`

Alternatively a GUI can be used via the command 

- `nmtui` 

---

### Install SSH Agent

- `sudo pacman -S sshagent`
- `sudo systemctl enable sshd.service`

---

### Install a browser

- `sudo pacman -S firefox`

---

### Set up a firewall

- `sudo pacman -S ufw`
- `sudo systemctl enable ufw.service`

---

### Set up Basic Graphics with sway

- `sudo pacman -S sway`
- Reboot or run `sway`

---

### Set up SSH

#### Check if you already have an SSH key

- `ls ~/.ssh`

Look for files like `id_rsa` and `id_rsa.pub`. If they exist, skip to step 1.4.

#### 1.1 Generate a new SSH key

- `ssh-keygen -t ed25519 -C "your_email@example.com" `

> When prompted, press **Enter** to accept the default file location. You can add a passphrase for extra security (optional).

#### 1.2 Start the SSH agent

- `eval "$(ssh-agent -s)"`

#### 1.3 Add your key to the SSH agent

- `ssh-add ~/.ssh/id_ed25519`

#### 1.4 Add your SSH key to GitHub

Copy the public key:

- `cat ~/.ssh/id_ed25519.pub`

Go to **GitHub → Settings → SSH and GPG keys → New SSH key**, and paste it there.

---

### Install the Packages by copying the following command:

- `sudo pacman -S texlive fastetch 7zip make kitty neovim python pip stow npm python 
   wl-clippboard wofi xorg-wayland luarocks linux-lts lua wayland 
   nodejs waybar rust jdk-open-jdk htop man-db man-pages openssh git yazi vi zathura zathura-pdf-poppler
   julia noto-fonts noto-fonts-emoji noto-fonts-cjk ttf-linux-libertine wget ruby composer php
   xdotool biber wget pipewire pipewire-alsa pipewire-pulse wireplumber pavucontrol lm_sensors btop
   clamav sxiv bleachbit reflector jupyterlab jupyter-notebook python-numpy python-pandas python-matplotlib python-pygame
   tk nm-connection-editor iwd modemmanager usb_modeswitch timeshift tmux otf-font-awesome
   fzf bat lsd tldr lazygit swayidle thunar autotiling starship python-scikit-learn docker pyright
   lua-language-server bash-language-server texlab postgresql clang pacman-contrib ghc cabal-install
   julia`

---

### Setup yay

- `git clone https://aur.archlinux.org/yay.git`
- `cd yay/`
- `cd makepkg -si`

--- 

### Install Extra Packages

- `yay -S brave-bin` - `Enter` - `Enter`
- `yay -S ripgrep`
- `yay -S fd`
- `yay -S visual-studio-code-bin`
- `sudo npm install -g neovim`
- `sudo pacman -S python-neovim`
- `sudo pacman -S python-pylatexenc`
- `gem install neovim`
- `sudo npm install -g regex`
- `npm install -g tree-sitter-cli`
- `yay -S sql-language-server`
- `yay -S asm-lsp`
- `rustup component add rust-analyzer`
- `yay -S tex-fmt`

---

### GTK and Qt Themes 

- **Setting up the Qt env var:** write `QT_QPA_PLATFORMTHEME="qt5ct"` with `sudo vim /etc/environment `
- **Instaling Qt Themes:** `sudo pacman -S breeze` 

--- 

### ClamAV

- Initial Configuration:

* `clamconf -g freshclam.conf > freshclam.conf`
* `clamconf -g clamd.conf > clamd.conf`
* `clamconf -g clamav-milter.conf > clamav-milter.conf`

#### clamd.conf

```conf

##
## Example config file for the Clam AV daemon
## Please read the clamd.conf(5) manual before editing this file.
##


# Comment or remove the line below.
#Example

# Uncomment this option to enable logging.
# LogFile must be writable for the user running daemon.
# A full path is required.
# Default: disabled
LogFile /var/log/clamav/clamd.log

# By default the log file is locked for writing - the lock protects against
# running clamd multiple times (if want to run another clamd, please
# copy the configuration file, change the LogFile variable, and run
# the daemon with --config-file option).
# This option disables log file locking.
# Default: no
#LogFileUnlock yes

# Maximum size of the log file.
# Value of 0 disables the limit.
# You may use 'M' or 'm' for megabytes (1M = 1m = 1048576 bytes)
# and 'K' or 'k' for kilobytes (1K = 1k = 1024 bytes). To specify the size
# in bytes just don't use modifiers. If LogFileMaxSize is enabled, log
# rotation (the LogRotate option) will always be enabled.
# Default: 1M
#LogFileMaxSize 2M

# Log time with each message.
# Default: no
LogTime yes

DetectPUA yes
HeuristicAlerts yes
ScanPE yes
ScanELF yes
ScanOLE2 yes
ScanPDF yes
ScanSWF yes
ScanXMLDOCS yes
ScanHWP3 yes
ScanOneNote yes
ScanMail yes
ScanHTML yes
ScanArchive yes
Bytecode yes
AlertBrokenExecutables yes
AlertBrokenMedia yes
AlertEncrypted yes
AlertEncryptedArchive yes
AlertEncryptedDoc yes
AlertOLE2Macros yes
AlertPartitionIntersection yes

# Also log clean files. Useful in debugging but drastically increases the
# log size.
# Default: no
#LogClean yes

# Use system logger (can work together with LogFile).
# Default: no
#LogSyslog yes

# Specify the type of syslog messages - please refer to 'man syslog'
# for facility names.
# Default: LOG_LOCAL6
#LogFacility LOG_MAIL

# Enable verbose logging.
# Default: no
#LogVerbose yes

# Enable log rotation. Always enabled when LogFileMaxSize is enabled.
# Default: no
#LogRotate yes

# Enable Prelude output.
# Default: no
#PreludeEnable yes
#
# Set the name of the analyzer used by prelude-admin.
# Default: ClamAV
#PreludeAnalyzerName ClamAV

# Log additional information about the infected file, such as its
# size and hash, together with the virus name.
ExtendedDetectionInfo yes

# This option allows you to save a process identifier of the listening
# daemon.
# This file will be owned by root, as long as clamd was started by root.
# It is recommended that the directory where this file is stored is
# also owned by root to keep other users from tampering with it.
# Default: disabled
PidFile /run/clamav/clamd.pid

# Optional path to the global temporary directory.
# Default: system specific (usually /tmp or /var/tmp).
TemporaryDirectory /tmp

# Path to the database directory.
# Default: hardcoded (depends on installation options)
#DatabaseDirectory /var/lib/clamav

# Only load the official signatures published by the ClamAV project.
# Default: no
#OfficialDatabaseOnly no

# Return with a nonzero error code if the virus database is older than
# the specified number of days.
# Default: -1
#FailIfCvdOlderThan 7

# The daemon can work in local mode, network mode or both.
# Due to security reasons we recommend the local mode.

# Path to a local socket file the daemon will listen on.
# Default: disabled (must be specified by a user)
LocalSocket /run/clamav/clamd.ctl
LocalSocket /run/clamav/clamd.ctl

# Sets the group ownership on the unix socket.
# Default: disabled (the primary group of the user running clamd)
#LocalSocketGroup virusgroup

# Sets the permissions on the unix socket to the specified mode.
# Default: disabled (socket is world accessible)
#LocalSocketMode 660

# Remove stale socket after unclean shutdown.
# Default: yes
#FixStaleSocket no

# TCP port address.
# Default: no
#TCPSocket 3310

# TCP address.
# By default we bind to INADDR_ANY, probably not wise.
# Enable the following to provide some degree of protection
# from the outside world. This option can be specified multiple
# times if you want to listen on multiple IPs. IPv6 is now supported.
# Default: no
#TCPAddr localhost

# Maximum length the queue of pending connections may grow to.
# Default: 200
#MaxConnectionQueueLength 30

# Clamd uses FTP-like protocol to receive data from remote clients.
# If you are using clamav-milter to balance load between remote clamd daemons
# on firewall servers you may need to tune the options below.

# Close the connection when the data size limit is exceeded.
# The value should match your MTA's limit for a maximum attachment size.
# Default: 100M
#StreamMaxLength 25M

# Limit port range.
# Default: 1024
#StreamMinPort 30000
# Default: 2048
#StreamMaxPort 32000

# Maximum number of threads running at the same time.
# Default: 10
#MaxThreads 20

# Waiting for data from a client socket will timeout after this time (seconds).
# Default: 120
#ReadTimeout 300

# This option specifies the time (in seconds) after which clamd should
# timeout if a client doesn't provide any initial command after connecting.
# Default: 30
#CommandReadTimeout 30

# This option specifies how long to wait (in milliseconds) if the send buffer
# is full.
# Keep this value low to prevent clamd hanging.
#
# Default: 500
#SendBufTimeout 200

# Maximum number of queued items (including those being processed by
# MaxThreads threads).
# It is recommended to have this value at least twice MaxThreads if possible.
# WARNING: you shouldn't increase this too much to avoid running out  of file
# descriptors, the following condition should hold:
# MaxThreads*MaxRecursion + (MaxQueue - MaxThreads) + 6< RLIMIT_NOFILE (usual
# max is 1024).
#
# Default: 100
#MaxQueue 200

# Waiting for a new job will timeout after this time (seconds).
# Default: 30
#IdleTimeout 60

# Don't scan files and directories matching regex
# This directive can be used multiple times
# Default: scan all
#ExcludePath ^/proc/
#ExcludePath ^/sys/

# Maximum depth directories are scanned at.
# Default: 15
#MaxDirectoryRecursion 20

# Follow directory symlinks.
# Default: no
#FollowDirectorySymlinks yes

# Follow regular file symlinks.
# Default: no
#FollowFileSymlinks yes

# Scan files and directories on other filesystems.
# Default: yes
#CrossFilesystems no

# Perform a database check.
# Default: 600 (10 min)
#SelfCheck 600

# Enable non-blocking (multi-threaded/concurrent) database reloads.
# This feature will temporarily load a second scanning engine while scanning
# continues using the first engine. Once loaded, the new engine takes over.
# The old engine is removed as soon as all scans using the old engine have
# completed.
# This feature requires more RAM, so this option is provided in case users are
# willing to block scans during reload in exchange for lower RAM requirements.
# Default: yes
#ConcurrentDatabaseReload no

# Execute a command when virus is found.
# Use the following environment variables to identify the file and virus names:
# - $CLAM_VIRUSEVENT_FILENAME
# - $CLAM_VIRUSEVENT_VIRUSNAME
# In the command string, '%v' will also be replaced with the virus name.
# Note: The '%f' filename format character has been disabled and will no longer
# be replaced with the file name, due to command injection security concerns.
# Use the 'CLAM_VIRUSEVENT_FILENAME' environment variable instead.
# For the same reason, you should NOT use the environment variables in the
# command directly, but should use it carefully from your executed script.
# Default: no
#VirusEvent /opt/send_virus_alert_sms.sh

# Run as another user (clamd must be started by root for this option to work)
# Default: don't drop privileges
User clamav

# Stop daemon when libclamav reports out of memory condition.
#ExitOnOOM yes

# Don't fork into background.
# Default: no
#Foreground yes

# Enable debug messages in libclamav.
# Default: no
#Debug yes

# Do not remove temporary files (for debug purposes).
# Default: no
#LeaveTemporaryFiles yes

# Record metadata about the file being scanned.
# Scan metadata is useful for file analysis purposes and for debugging scan behavior.
# The JSON metadata will be printed after the scan is complete if Debug is enabled.
# A metadata.json file will be written to the scan temp directory if LeaveTemporaryFiles is enabled.
# Default: no
#GenerateMetadataJson yes

# Permit use of the ALLMATCHSCAN command. If set to no, clamd will reject
# any ALLMATCHSCAN command as invalid.
# Default: yes
#AllowAllMatchScan no

# Detect Possibly Unwanted Applications.
# Default: no
#DetectPUA yes

# Exclude a specific PUA category. This directive can be used multiple times.
# See https://github.com/vrtadmin/clamav-faq/blob/master/faq/faq-pua.md for
# the complete list of PUA categories.
# Default: Load all categories (if DetectPUA is activated)
#ExcludePUA NetTool
#ExcludePUA PWTool

# Only include a specific PUA category. This directive can be used multiple
# times.
# Default: Load all categories (if DetectPUA is activated)
#IncludePUA Spy
#IncludePUA Scanner
#IncludePUA RAT

# This option causes memory or nested map scans to dump the content to disk.
# If you turn on this option, more data is written to disk and is available
# when the LeaveTemporaryFiles option is enabled.
#ForceToDisk yes

# This option allows you to disable the caching feature of the engine. By
# default, the engine will store an MD5 in a cache of any files that are
# not flagged as virus or that hit limits checks. Disabling the cache will
# have a negative performance impact on large scans.
# Default: no
#DisableCache yes

# This option allows you to set the number of entries the cache can store.
# The value should be a square number or will be rounded up to the nearest
# square number.
#CacheSize 65536

# In some cases (eg. complex malware, exploits in graphic files, and others),
# ClamAV uses special algorithms to detect abnormal patterns and behaviors that
# may be malicious.  This option enables alerting on such heuristically
# detected potential threats.
# Default: yes
#HeuristicAlerts no

# Allow heuristic alerts to take precedence.
# When enabled, if a heuristic scan (such as phishingScan) detects
# a possible virus/phish it will stop scan immediately. Recommended, saves CPU
# scan-time.
# When disabled, virus/phish detected by heuristic scans will be reported only
# at the end of a scan. If an archive contains both a heuristically detected
# virus/phish, and a real malware, the real malware will be reported
#
# Keep this disabled if you intend to handle "Heuristics.*" viruses
# differently from "real" malware.
# If a non-heuristically-detected virus (signature-based) is found first,
# the scan is interrupted immediately, regardless of this config option.
#
# Default: no
#HeuristicScanPrecedence yes


##
## Heuristic Alerts
##

# With this option clamav will try to detect broken executables (both PE and
# ELF) and alert on them with the Broken.Executable heuristic signature.
# Default: no
#AlertBrokenExecutables yes

# With this option clamav will try to detect broken media file (JPEG,
# TIFF, PNG, GIF) and alert on them with a Broken.Media heuristic signature.
# Default: no
#AlertBrokenMedia yes

# Alert on encrypted archives _and_ documents with heuristic signature
# (encrypted .zip, .7zip, .rar, .pdf).
# Default: no
#AlertEncrypted yes

# Alert on encrypted archives with heuristic signature (encrypted .zip, .7zip,
# .rar).
# Default: no
#AlertEncryptedArchive yes

# Alert on encrypted archives with heuristic signature (encrypted .pdf).
# Default: no
#AlertEncryptedDoc yes

# With this option enabled OLE2 files containing VBA macros, which were not
# detected by signatures will be marked as "Heuristics.OLE2.ContainsMacros".
# Default: no
#AlertOLE2Macros yes

# Alert on SSL mismatches in URLs, even if the URL isn't in the database.
# This can lead to false positives.
# Default: no
#AlertPhishingSSLMismatch yes

# Alert on cloaked URLs, even if URL isn't in database.
# This can lead to false positives.
# Default: no
#AlertPhishingCloak yes

# Alert on raw DMG image files containing partition intersections
# Default: no
#AlertPartitionIntersection yes


##
## Executable files
##

# PE stands for Portable Executable - it's an executable file format used
# in all 32 and 64-bit versions of Windows operating systems. This option
# allows ClamAV to perform a deeper analysis of executable files and it's also
# required for decompression of popular executable packers such as UPX, FSG,
# and Petite. If you turn off this option, the original files will still be
# scanned, but without additional processing.
# Default: yes
#ScanPE no

# Certain PE files contain an authenticode signature. By default, we check
# the signature chain in the PE file against a database of trusted and
# revoked certificates if the file being scanned is marked as a virus.
# If any certificate in the chain validates against any trusted root, but
# does not match any revoked certificate, the file is marked as trusted.
# If the file does match a revoked certificate, the file is marked as virus.
# The following setting completely turns off authenticode verification.
# Default: no
#DisableCertCheck yes

# Executable and Linking Format is a standard format for UN*X executables.
# This option allows you to control the scanning of ELF files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanELF no


##
## Documents
##

# This option enables scanning of OLE2 files, such as Microsoft Office
# documents and .msi files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanOLE2 no

# This option enables scanning within PDF files.
# If you turn off this option, the original files will still be scanned, but
# without decoding and additional processing.
# Default: yes
#ScanPDF no

# This option enables scanning within SWF files.
# If you turn off this option, the original files will still be scanned, but
# without decoding and additional processing.
# Default: yes
#ScanSWF no

# This option enables scanning xml-based document files supported by libclamav.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanXMLDOCS no

# This option enables scanning of HWP3 files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanHWP3 no

# This option enables scanning of OneNote files.
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanOneNote no


##
## Other file types
##

# This option enables scanning of image (graphics).
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
# Default: yes
#ScanImage no

# This option enables detection by calculating a fuzzy hash of image (graphics)
# files.
# Signatures using image fuzzy hashes typically match files and documents by
# identifying images embedded or attached to those files.
# If you turn off this option, then some files may no longer be detected.
# Default: yes
#ScanImageFuzzyHash no


##
## Mail files
##

# Enable internal e-mail scanner.
# If you turn off this option, the original files will still be scanned, but
# without parsing individual messages/attachments.
# Default: yes
#ScanMail no

# Scan RFC1341 messages split over many emails.
# You will need to periodically clean up $TemporaryDirectory/clamav-partial
# directory.
# WARNING: This option may open your system to a DoS attack.
#	   Never use it on loaded servers.
# Default: no
#ScanPartialMessages yes

# With this option enabled ClamAV will try to detect phishing attempts by using
# HTML.Phishing and Email.Phishing NDB signatures.
# Default: yes
#PhishingSignatures no

# With this option enabled ClamAV will try to detect phishing attempts by
# analyzing URLs found in emails using WDB and PDB signature databases.
# Default: yes
#PhishingScanURLs no


##
## Data Loss Prevention (DLP)
##

# Enable the DLP module
# Default: No
#StructuredDataDetection yes

# This option sets the lowest number of Credit Card numbers found in a file
# to generate a detect.
# Default: 3
#StructuredMinCreditCardCount 5

# With this option enabled the DLP module will search for valid Credit Card
# numbers only. Debit and Private Label cards will not be searched.
# Default: no
#StructuredCCOnly yes

# This option sets the lowest number of Social Security Numbers found
# in a file to generate a detect.
# Default: 3
#StructuredMinSSNCount 5

# With this option enabled the DLP module will search for valid
# SSNs formatted as xxx-yy-zzzz
# Default: yes
#StructuredSSNFormatNormal no

# With this option enabled the DLP module will search for valid
# SSNs formatted as xxxyyzzzz
# Default: no
#StructuredSSNFormatStripped yes


##
## HTML
##

# Perform HTML normalisation and decryption of MS Script Encoder code.
# Default: yes
# If you turn off this option, the original files will still be scanned, but
# without additional processing.
#ScanHTML no


##
## Archives
##

# ClamAV can scan within archives and compressed files.
# If you turn off this option, the original files will still be scanned, but
# without unpacking and additional processing.
# Default: yes
#ScanArchive no


##
## Limits
##

# The options below protect your system against Denial of Service attacks
# using archive bombs.

# This option sets the maximum amount of time to a scan may take.
# In this version, this field only affects the scan time of ZIP archives.
# Value of 0 disables the limit.
# Note: disabling this limit or setting it too high may result allow scanning
# of certain files to lock up the scanning process/threads resulting in a
# Denial of Service.
# Time is in milliseconds.
# Default: 120000
#MaxScanTime 300000

# This option sets the maximum amount of data to be scanned for each input
# file. Archives and other containers are recursively extracted and scanned
# up to this value.
# Value of 0 disables the limit
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 400M
#MaxScanSize 1000M

# Files larger than this limit won't be scanned. Affects the input file itself
# as well as files contained inside it (when the input file is an archive, a
# document or some other kind of container).
# Value of 0 disables the limit.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Technical design limitations prevent ClamAV from scanning files greater than
# 2 GB at this time.
# Default: 100M
#MaxFileSize 400M

# Nested archives are scanned recursively, e.g. if a Zip archive contains a RAR
# file, all files within it will also be scanned. This options specifies how
# deeply the process should be continued.
# Note: setting this limit too high may result in severe damage to the system.
# Default: 17
#MaxRecursion 10

# Number of files to be scanned within an archive, a document, or any other
# container file.
# Value of 0 disables the limit.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 10000
#MaxFiles 15000

# Maximum size of a file to check for embedded PE. Files larger than this value
# will skip the additional analysis step.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 40M
#MaxEmbeddedPE 100M

# Maximum size of a HTML file to normalize. HTML files larger than this value
# will not be normalized or scanned.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 40M
#MaxHTMLNormalize 100M

# Maximum size of a normalized HTML file to scan. HTML files larger than this
# value after normalization will not be scanned.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 8M
#MaxHTMLNoTags 16M

# Maximum size of a script file to normalize. Script content larger than this
# value will not be normalized or scanned.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 20M
#MaxScriptNormalize 50M

# Maximum size of a ZIP file to reanalyze type recognition. ZIP files larger
# than this value will skip the step to potentially reanalyze as PE.
# Note: disabling this limit or setting it too high may result in severe damage
# to the system.
# Default: 1M
#MaxZipTypeRcg 1M

# This option sets the maximum number of partitions of a raw disk image to be
# scanned.
# Raw disk images with more partitions than this value will have up to
# the value number partitions scanned. Negative values are not allowed.
# Note: setting this limit too high may result in severe damage or impact
# performance.
# Default: 50
#MaxPartitions 128

# This option sets the maximum number of icons within a PE to be scanned.
# PE files with more icons than this value will have up to the value number
# icons scanned.
# Negative values are not allowed.
# WARNING: setting this limit too high may result in severe damage or impact
# performance.
# Default: 100
#MaxIconsPE 200

# This option sets the maximum recursive calls for HWP3 parsing during
# scanning. HWP3 files using more than this limit will be terminated and
# alert the user.
# Scans will be unable to scan any HWP3 attachments if the recursive limit
# is reached.
# Negative values are not allowed.
# WARNING: setting this limit too high may result in severe damage or impact
# performance.
# Default: 16
#MaxRecHWP3 16

# This option sets the maximum calls to the PCRE match function during
# an instance of regex matching.
# Instances using more than this limit will be terminated and alert the user
# but the scan will continue.
# For more information on match_limit, see the PCRE documentation.
# Negative values are not allowed.
# WARNING: setting this limit too high may severely impact performance.
# Default: 100000
#PCREMatchLimit 20000

# This option sets the maximum recursive calls to the PCRE match function
# during an instance of regex matching.
# Instances using more than this limit will be terminated and alert the user
# but the scan will continue.
# For more information on match_limit_recursion, see the PCRE documentation.
# Negative values are not allowed and values > PCREMatchLimit are superfluous.
# WARNING: setting this limit too high may severely impact performance.
# Default: 2000
#PCRERecMatchLimit 10000

# This option sets the maximum filesize for which PCRE subsigs will be
# executed. Files exceeding this limit will not have PCRE subsigs executed
# unless a subsig is encompassed to a smaller buffer.
# Negative values are not allowed.
# Setting this value to zero disables the limit.
# WARNING: setting this limit too high or disabling it may severely impact
# performance.
# Default: 100M
#PCREMaxFileSize 400M

# When AlertExceedsMax is set, files exceeding the MaxFileSize, MaxScanSize, or
# MaxRecursion limit will be flagged with the virus name starting with
# "Heuristics.Limits.Exceeded".
# Default: no
#AlertExceedsMax yes

##
## On-access Scan Settings
##

# Don't scan files larger than OnAccessMaxFileSize
# Value of 0 disables the limit.
# Default: 5M
#OnAccessMaxFileSize 10M

# Max number of scanning threads to allocate to the OnAccess thread pool at
# startup. These threads are the ones responsible for creating a connection
# with the daemon and kicking off scanning after an event has been processed.
# To prevent clamonacc from consuming all clamd's resources keep this lower
# than clamd's max threads.
# Default: 5
#OnAccessMaxThreads 10

# Max amount of time (in milliseconds) that the OnAccess client should spend
# for every connect, send, and receive attempt when communicating with clamd
# via curl.
# Default: 5000 (5 seconds)
# OnAccessCurlTimeout 10000

# Toggles dynamic directory determination. Allows for recursively watching
# include paths.
# Default: no
#OnAccessDisableDDD yes

# Set the include paths (all files inside them will be scanned). You can have
# multiple OnAccessIncludePath directives but each directory must be added
# in a separate line.
# Default: disabled
OnAccessIncludePath /home
#OnAccessIncludePath /students

# Set the exclude paths. All subdirectories are also excluded.
# Default: disabled
#OnAccessExcludePath /home/user

# Modifies fanotify blocking behaviour when handling permission events.
# If off, fanotify will only notify if the file scanned is a virus,
# and not perform any blocking.
# Default: no
OnAccessPrevention no

# When using prevention, if this option is turned on, any errors that occur
# during scanning will result in the event attempt being denied. This could
# potentially lead to unwanted system behaviour with certain configurations,
# so the client defaults this to off and prefers allowing access events in
# case of scan or connection error.
# Default: no
#OnAccessDenyOnError yes

# Toggles extra scanning and notifications when a file or directory is
# created or moved.
# Requires the  DDD system to kick-off extra scans.
# Default: no
OnAccessExtraScanning yes

# Set the  mount point to be scanned. The mount point specified, or the mount
# point containing the specified directory will be watched. If any directories
# are specified, this option will preempt (disable and ignore all options
# related to) the DDD system. This option will result in verdicts only.
# Note that prevention is explicitly disallowed to prevent common, fatal
# misconfigurations. (e.g. watching "/" with prevention on and no exclusions
# made on vital system directories)
# It can be used multiple times.
# Default: disabled
OnAccessMountPath /
#OnAccessMountPath /home/user

# With this option you can exclude the root UID (0). Processes run under
# root with be able to access all files without triggering scans or
# permission denied events.
# Note that if clamd cannot check the uid of the process that generated an
# on-access scan event (e.g., because OnAccessPrevention was not enabled, and
# the process already exited), clamd will perform a scan.  Thus, setting
# OnAccessExcludeRootUID is not *guaranteed* to prevent every access by the
# root user from triggering a scan (unless OnAccessPrevention is enabled).
# Default: no
#OnAccessExcludeRootUID no

# With this option you can exclude specific UIDs. Processes with these UIDs
# will be able to access all files without triggering scans or permission
# denied events.
# This option can be used multiple times (one per line).
# Using a value of 0 on any line will disable this option entirely.
# To exclude the root UID (0) please enable the OnAccessExcludeRootUID
# option.
# Also note that if clamd cannot check the uid of the process that generated an
# on-access scan event (e.g., because OnAccessPrevention was not enabled, and
# the process already exited), clamd will perform a scan.  Thus, setting
# OnAccessExcludeUID is not *guaranteed* to prevent every access by the
# specified uid from triggering a scan (unless OnAccessPrevention is enabled).
# Default: disabled
#OnAccessExcludeUID -1

# This option allows exclusions via user names when using the on-access
# scanning client. It can be used multiple times.
# It has the same potential race condition limitations of the
# OnAccessExcludeUID option.
# Default: disabled
OnAccessExcludeUname clamav

# Number of times the OnAccess client will retry a failed scan due to
# connection problems (or other issues).
# Default: 0
#OnAccessRetryAttempts 3

##
## Bytecode
##

# With this option enabled ClamAV will load bytecode from the database.
# It is highly recommended you keep this option on, otherwise you'll miss
# detections for many new viruses.
# Default: yes
#Bytecode no

# Set bytecode security level.
# Possible values:
#   None -      No security at all, meant for debugging.
#               DO NOT USE THIS ON PRODUCTION SYSTEMS.
#               This value is only available if clamav was built
#               with --enable-debug!
#   TrustSigned - Trust bytecode loaded from signed .c[lv]d files, insert
#               runtime safety checks for bytecode loaded from other sources.
#   Paranoid -  Don't trust any bytecode, insert runtime checks for all.
# Recommended: TrustSigned, because bytecode in .cvd files already has these
# checks.
# Note that by default only signed bytecode is loaded, currently you can only
# load unsigned bytecode in --enable-debug mode.
#
# Default: TrustSigned
#BytecodeSecurity TrustSigned

# Allow loading bytecode from outside digitally signed .c[lv]d files.
# **Caution**: You should NEVER run bytecode signatures from untrusted sources.
# Doing so may result in arbitrary code execution.
# Default: no
#BytecodeUnsigned yes

# Set bytecode timeout in milliseconds.
#
# Default: 10000
# bytecodetimeout 1000
VirusEvent /etc/clamav/virus-event.bash
```

- Create the file: `/etc/sudoers.d/clamav` and add this line

```
clamav ALL=(ALL) NOPASSWD: SETENV: /usr/bin/notify-send

```

- Create the file if it does not exists `/etc/clamav/virus-event.bash` and write 

```bash 
#!/bin/bash
PATH=/usr/bin
ALERT="Signature detected by clamav: $CLAM_VIRUSEVENT_VIRUSNAME in $CLAM_VIRUSEVENT_FILENAME"

# Send an alert to all graphical users.
for ADDRESS in /run/user/*; do
    USERID=${ADDRESS#/run/user/}
    /usr/bin/sudo -u "#$USERID" DBUS_SESSION_BUS_ADDRESS="unix:path=$ADDRESS/bus" PATH=${PATH} \
        /usr/bin/notify-send -u critical -i dialog-warning "Virus found!" "$ALERT"
done
```

- Finally edit the `clamav-clamonacc.service` by writting in the section 
for edits. Run `sudo systemctl edit clamav-clamonacc.service` to edit

```conf
[Service]
ExecStart=
ExecStart=/usr/sbin/clamonacc -F --fdpass --log=/var/log/clamav/clamonacc.log
```

Now restart the `clamav-clamonacc.service` using `systemctl`.


- Update database: `freshclam`
 
---

### Neovim

Maintenance 

- Delete Everything: `rm -rf ~/.local/share/nvim/*`

---

### Sensors 

To setup the sensors run the command 

`sensors-detect` then type `YES` for all safe operations. 

To see the data type `sensors`

---

### Clone Configuration repositories

For everything related to a 'Rice' clone the repositories or setup own configurations. One option is to 
clone the necessary repositories from github or use stow.

- `git clone git@github.com:HaoRyuZark/dotfiles.git` 
- `cd dotfiles`
- `stow */`

#### Functionality

1. To add files to stow use create a mirror of the original struture from the home directory to that file. 

2. Copy the file or directory to stow 

3. Run `stow --adopt .` inside the dotfiles directory

---

### Devdocs 

To have offline documentation run 

- `sudo docker run --name devdocs -d -p 9292:9292 ghcr.io/freecodecamp/devdocs:latest`

---

### systemctl For enabling key Packages

#### Basic `systemctl` Commands

`systemctl` is the primary tool used to examine and control the `systemd` system and service manager on Linux systems. Here are some essential commands:

- **Start a service**  `sudo systemctl start <service-name>`

- **Stop a service** `sudo systemctl stop <service-name>`

- **Restart a service** `sudo systemctl restart <service-name>`

- **Enable a service** `sudo systemctl enable <service-name>`

- **Disable a service** `sudo systemctl disable <service-name>`

- **Check status of a service** `systemctl status <service-name>`

- **List all active services** `systemctl list-units --type=service`

---

### Audio 

- `systemctl --user enable --now pipewire pipewire-pulse wireplumber`

---

### Set pdf viewer 

- `xdg-mime default org.pwmt.zathura.desktop application/pdf`

--- 

### Docker 

- `sudo systemctl enable docker.service`

---

### Clone development respositories

- `mkdir Homo_Deus`
- `cd Homo_Deus`
- `git clone git@github.com:HaoRyuZark/Computer_Science_Compedium.git`
- `git clone git@github.com:HaoRyuZark/Mathematica_Compendium.git`
- `git clone git@github.com:HaoRyuZark/Programming.git`

--- 

### Copilot in Neovim 

To set up copilot run 

- `Lazy load copilot.vim`
- `Copilot setup` and proceed to authenticate

### University Stuff

Download the Mathematics folder from Google Drive to obtain books and worksheets.

--- 

### Second Hardrive 

Use the same procedure like when during the installtion consisting of: 

- Identifying
- Paritioning
- Formating 
- Mounting 

The difference is that this time we want to add it to `fstab` to mount automatically when booting

- Get the UUID with `lsblk -f`
- Open and edit the `/etc/fstab` and add the line `UUID=id /mnt/... file_system_type permisions(defaults) dump_option (0)  policy_option (0)`

---

### Timeshift

#### Setup via GUI 

To open, use `sudo -E timeshift-gtk` (Not the best way TODO)
1. Select the type of snapshots
2. Select your second storage device 
3. Schedule the snapshot 
4. Select the users: `root` and `yourself`, ... 
5. Skip the filter and click ok 

#### Usage CLI 

- **Check config:** `sudo timeshift --check`
- **Snapshot type:** `sudo timeshift --rsync` or `sudo timeshift --btrfs`
- **Storage Location:** `sudo timeshift --rsync --snapshot-device /dev/disk_to_use` or
  `sudo timeshift --rsync --snapshot-device /mnt/disk_to_use`
- **Create a snapshot:** `sudo timeshift --create --comments "Something" --tags D`
- **See snapshots:** `sudo timeshift --list`
- **Restore system:** `sudo timeshift --restore` then type the identifier of the target
- **Delete snapshot:** `sudo timeshift --delete` then type  the identifier of the target
- **Delete specific snapshot:** `sudo timeshift --delete --snapshot 'date' `
- **Delete snapshots:** `sudo timeshift --delete-all `
- **Scheduleling:** `sudo timeshift --schedule --type_of_schedule num`

--- 

### Maintenance 

- **Clear Cache:** `sudo yay -Scc` and `sudo pacman -Scc`
- **Update database** `sudo yay -Syy`
- **Update:** `sudo yay -Syu`
- **Clean unwanted dependencies:** `yay -Yc`
- **Clean orphan packages:** `sudo pacman -Rns $(pacman -Qtdq)`
- **Free Disk Space:** Use `Bleachbit` or type `du -sh path` to see the disk usage of some directory and 
`rm -rf path/` to remove. Be carefull to not important directories.
- **Cleaning Logs of the Journal directory:** Use `journalctl` to activate the vacuum option. 
`sudo journalctl --vacuum-time=2weeks`
- **Update the mirror list:** `sudo reflector -c COUNTRY -a 6 --sort rate --save /etc/pacman.d/mirrorlist `

--- 

## Command ip link 

In linux the `ip link` command will return three device names 

- `lo` for the loop back device 
- `Ethernet Plug` 
- `Ẁifi card`

--- 

## Image viewer

- `sxiv path_to_the_image`

--- 

## Pacman and Yay

Pacman was used for almost all examples, but Yay can also be used.

* **Installing packages**:
  `pacman -S package_name1 package_name2 ...`

* **Installing groups**:
  `pacman -S gnome`

* **Removing packages**:
  `pacman -R gnome`

* **Removing packages with dependencies**:
  `pacman -Rs gnome`

* **Updating the official packages**:
  `pacman -Syu`

* **Updating the official and unofficial packages**:
  `yay -Syu`

* **Searching for a package in the official repos**:
  `pacman -Ss package_name`

* **Searching for a package in AUR (yay)**:
  `yay -Ss package_name`

* **Viewing installed packages**:
  `pacman -Q`

* **Viewing explicitly installed packages**:
  `pacman -Qe`

* **Viewing dependencies of a package**:
  `pacman -Qi package_name`

* **Cleaning the package cache (remove all except the latest version)**:
  `pacman -Sc`

* **Cleaning the package cache completely**:
  `pacman -Scc`

* **Installing a local package file (.pkg.tar.zst)**:
  `pacman -U ./package_file.pkg.tar.zst`

* **Reinstalling a package**:
  `pacman -S package_name`

* **Removing orphaned packages**:
  `pacman -Rns $(pacman -Qtdq)`

* **Editing and building packages from AUR with yay**:
  `yay -G aur_package_name && cd aur_package_name && makepkg -si`

* **Eliminate Orphan Packages**:
  `sudo pacman -Qdtq | sudo pacman -Rns -`

---

## Enviroment variables 

Like in other operating systems, an enviroment variable is user defined varible which affects 
the way processes run for the specific enviroment.

In Linux the variables can be printed using the the command `env`. To see the value we can use the 
command `printvar`. Finally to modify we can use the command `export NAME=value`

To create persistent enviroment variables we have to modify the `.bashrc` by adding 
`export NAME=value` and then source the file with the `source FILE` command. 

To set a global env. variable we have to modify the file `vim /etc/environment` using the 
export syntax and then sourcing.

To delete an environment variables we can use the command `unset NAME`

The PATH variable is an environment variable containing an ordered list of paths that Linux will search for executables when running a command. Using these paths means that we don’t have to specify an absolute path when running a command.

To modify the path both locally we have to create an `.profile` file using the export 
syntax and for the global approach it is very similar but we create the the file in `/etc/profile.d/varname.sh`

---

## Types of File Systems in Linux and Their Differences

* **ext2 (Second Extended Filesystem)**

  * No journaling
  * Good for flash drives

* **ext3 (Third Extended Filesystem)**

  * Journaling enabled (improved reliability)
  * Backward compatible with ext2

* **ext4 (Fourth Extended Filesystem)**

  * Most widely used
  * Supports large files and volumes
  * Journaling + extents for better performance

* **XFS**

  * High-performance journaling file system
  * Good for large files and parallel I/O

* **Btrfs (B-tree File System)**

  * Copy-on-write, snapshots, self-healing
  * Advanced features, but still maturing

* **FAT32 / exFAT**

  * File Allocation Table
  * Compatibility with Windows systems
  * No journaling

* **NTFS**

  * New Technology File System
  * Proprietary Microsoft file system
  * Supported via drivers (read/write)

---


## What is an Inode and How It Is Used

* An **inode** (index node) is a data structure on a filesystem that stores metadata about a file:

  * File type
  * Permissions
  * Owner/group
  * Size
  * Timestamps
  * Pointers to data blocks

* Every file has an inode (except for symbolic links in some filesystems).

* The inode number is used by the OS to identify files, not the filename.

---

## The Unix Philosophy

* **Do one thing and do it well**
* **Work together**: Tools should interact with each other through standard interfaces (e.g., stdin/stdout).
* **Handle text streams**: Treat everything as a stream of text.

This philosophy promotes simplicity, modularity, and composability.

---

## What is a File?

* A file is an abstract collection of data stored on disk.
* In Unix/Linux, **everything is a file**:

  * Regular files
  * Directories
  * Devices (`/dev`)
  * Pipes
  * Sockets
  * Symbolic links

---

## How Unix Uses Files

* **File Descriptors**: Integer handles for files (`0=stdin`, `1=stdout`, `2=stderr`)
* **Permissions and Ownership**:

  * Read (r), Write (w), Execute (x)
  * User, Group, Others
* **Processes interact with files through system calls**: `open()`, `read()`, `write()`, `close()`
* Devices and IPC mechanisms are accessed like files
* **Symlinks**: Short for symbolic link is a special type of file that points to another file or directory. It is 
like a pointer. They are useful to for example manage all dotfiles from one place

---

## Important Directories and Their Functions

| Directory | Function                                           |
|:--------- |:-------------------------------------------------- |
| `/`       | Root directory                                     |
| `/bin`    | Essential user binaries (e.g., ls, cp)             |
| `/sbin`   | System binaries (e.g., fsck, reboot)               |
| `/boot`   | Containg everything related to booting the system  |
| `/etc`    | Configuration files for system wide applications   |
| `/dev`    | Device files                                       |
| `/proc`   | Process and kernel info (virtual filesystem)       |
| `/sys`    | Kernel and hardware interface (virtual filesystem) |
| `/tmp`    | Temporary files                                    |
| `/var`    | Variable data (logs, spool files)                  |
| `/usr`    | Secondary hierarchy for user programs and data     |
| `/home`   | User home directories                              |
| `/lib`    | Essential shared libraries                         |
| `/opt`    | Optional/add-on software pckgs. Can add your own   |
| `/mnt`    | Mount point for temporary mounts                   |
| `/media`  | Mount point for removable media                    |
| `/root`   | For the root user                                  |
| `/run`    | Temp filesystem for temporal runtime information   |
| `/srv`    | If the computer is a service(server) the files for users will be stored here                    |
| `/sys`    | Acts as a dynamic interface between the kernel and the hardware  |

---

## Disk Partitions

* **Partition**: A division of a storage device that acts as a separate logical unit

* **Types**:

  * Primary (up to 4)
  * Extended (contains logical partitions)
  * Logical (within extended)

* **Tools**:

  * `fdisk` / `parted`: Manage partitions
  * `lsblk`, `blkid`: View block devices
  * `mount` / `umount`: Attach/detach partitions

* **Partition table types**:

  * **MBR (Master Boot Record)**
  * **GPT (GUID Partition Table)** - newer, supports more partitions

---

# Shortcuts and Keybinds


| Shortcut | Action |
|----------|--------|
| `Mod4  + Enter` | Open terminal |
| `Ctrl + Shift + Enter`    | Launch a new kitty window              |
| `Ctrl + Shift + Space`    | Launch a new kitty overlay             |
| `Ctrl + Shift + Q`        | Quit the current kitty window          |
| `Ctrl + Shift + N`        | Set window/tab title                   |
| `Ctrl + Shift + T`        | New tab                                |
| `Ctrl + Shift + W`        | Close current tab                      |
| `Ctrl + Shift + Left/Right` | Move to previous/next tab             |
| `Ctrl + Shift + [` or `]` | Switch tabs left/right                 |
| `Ctrl + Shift + Enter`    | New window (split horizontally)        |
| `Ctrl + Shift + \`        | New window (split vertically)          |
| `Ctrl + Shift + X`        | Close current window (split)           |
| `Ctrl + Shift + Arrow Keys` | Move focus to another window         |
| `Ctrl + Shift + =/-`      | Increase/decrease window size          |
| `Ctrl + Shift + F`        | Find text (search)                     |
| `Ctrl + Shift + Up/Down`  | Scroll up/down one line                |
| `Ctrl + Shift + PageUp/PageDown` | Scroll by full screen            |
| `Ctrl + Shift + C`        | Copy selected text                     |
| `Ctrl + Shift + V`        | Paste clipboard content                |


## Wofi

| Shortcut | Action |
|----------|--------|
| `Mod4 + d` | Open Wofi |
| `Mod4 + Shift + d` | Open Wofi run |


## Browser

| Shortcut | Action |
|----------|--------|
| `Crtl + t` | Open new tab |
| `Crtl + w` | Close tab |
| `Crtl + Shift + t` | Reopen last closed tab |
| `Crtl + r` | Reload page |
| `Crtl + e` | Go to the address bar |
| `Alt + left` | Go back |
| `Alt + right` | Go forward |
| `Ctrl + Shift + b` | Toggle bookmarks bar |
| `Ctrl + Shift + j` | Open developer tools |
| `Ctrl + Shift + arrow keys` | Select text |
| `Ctrl + f` | Find on page |


## Yazi 

| Shortcut                                                                    | Action                                                                                                                   |
| --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| `f1` or `~` | Open help menu |
| `k` or `↑`                                                                  | Move the cursor up                                                                                           |
| `j` or `↓`                                                                  | Move the cursor down                                                                                          |
| `l` or `→`                                                                  | Enter hovered directory                                                                                       |
| `h` or `←`                                                                  | Go to parent directory (leave current directory)                                                              |
| `K`                                                                         | Seek up 5 units in the preview                                                                                |
| `J`                                                                         | Seek down 5 units in the preview                                                                              |
| `g` + `g`                                                                   | Move cursor to the top                                                                                       |
| `G`                                                                         | Move cursor to the bottom                                                                                    |
| `z`                                                                         | cd to a directory or reveal a file via **fzf**                                                               |
| `Z`                                                                         | cd to a directory via **zoxide**                                                                              |
| `Space`                                                                     | Toggle selection of hovered file/directory                                                                    |
| `v`                                                                         | Enter visual mode (selection mode)                                                                            |
| `V`                                                                         | Enter visual mode (unset mode)                                                                                |
| `Ctrl + a`                                                                  | Select all files                                                                                              |
| `Ctrl + r`                                                                  | Inverse selection of all files                                                                                |
| `Esc`                                                                       | Cancel selection                                                                                             |
| `o`                                                                         | Open selected files                                                                                           |
| `O` or `Shift + Enter`                                                      | Open selected files interactively                                                                             |
| `Enter`                                                                     | Open selected files                                                                                          |
| `Tab`                                                                       | Show the file information (preview or info pane)                                                              |
| `y`                                                                         | Yank (copy) selected files                                                                                    |
| `x`                                                                         | Yank (cut) selected files                                                                                     |
| `p`                                                                         | Paste yanked files                                                                                            |
| `P`                                                                         | Paste yanked files, overwrite if destination exists                                                           |
| `Y` or `X`                                                                  | Cancel the yank (copy/cut) status                                                                             |
| `d`                                                                         | Trash selected files                                                                                         |
| `D`                                                                         | Permanently delete selected files                                                                             |
| `a`                                                                         | Create a file (or if name ends in `/`, directory)                                                             |
| `r`                                                                         | Rename selected file(s)                                                                                       |
| `.`                                                                         | Toggle visibility of hidden files                                                                             |
| `;` or `:`                                                                  | Run a shell command (blocking or non-blocking)                                                                |
| `-`                                                                         | Symlink the absolute path of yanked files                                                                     |
| `_`                                                                         | Symlink the relative path of yanked files                                                                     |
| `Ctrl + -`                                                                  | Hardlink yanked files                                                                                         |
| `f`                                                                         | Filter files                                                                                                  |
| `/`                                                                         | Find next file                                                                                                |
| `?`                                                                         | Find previous file                                                                                            |
| `n`                                                                         | Go to next found (search) item                                                                                |
| `N`                                                                         | Go to previous found item                                                                                     |
| `s`                                                                         | Search files by name using fd                                                                                 |
| `S`                                                                         | Search files by content using ripgrep                                                                         |
| `Ctrl + s`                                                                  | Cancel ongoing search                                                                                         |
| `,` ⇒ `m` / `M` / `b` / `B` / `e` / `E` / `a` / `A` / `n` / `N` / `s` / `S` | Sorting: modified time, birth time, extension, alphabetically, naturally, size, etc. (with reverse versions) |
| `~` or `F1`                                                                 | Open the help screen                                                                              |
| `q`                                                                         | Quit Yazi application                                                                                         |
| `Q`                                                                         | Quit without writing the current working directory file                                                       |
| `Ctrl + z`                                                                  | Suspend process (send to background)                                                              |


## Sway 

| Category       | Shortcut                        | Action                                |
|----------------|---------------------------------|-----------------------------------------------------|
| **Navigation** | `Mod + h/j/k/l`                 | Move focus left/down/up/right                       |
|                | `Mod + arrow keys`              | Move focus in corresponding direction               |
|                | `Mod + a`                       | Focus parent container                              |
|                | `Mod + s`                       | Toggle stacking layout                              |
|                | `Mod + w`                       | Toggle tabbed layout                                |
|                | `Mod + e`                       | Toggle split layout                                 |
| **Launching**  | `Mod + d`                       | Launch application launcher (`wofi` / `bemenu`)     |
|                | `Mod + Enter`                   | Launch terminal (usually `alacritty` or `foot`)     |
| **Splitting**  | `Mod + v`                       | Split container vertically                          |
|                | `Mod + b`                       | Split container horizontally                        |
|                | `Mod + Shift + v/b`             | Change orientation of existing split                |
| **Resizing**   | `Mod + r`                       | Enter resize mode                                   |
|                | `h/j/k/l` (in resize mode)      | Resize focused container left/down/up/right         |
|                | `Esc`                           | Exit resize mode                                    |
| **Tiling**     | `Mod + f`                       | Toggle fullscreen                                   |
|                | `Mod + Shift + space`           | Toggle floating mode                                |
|                | `Mod + space`                   | Toggle focus between tiling/floating containers     |
| **Workspaces** | `Mod + [0–9]`                   | Switch to workspace N                               |
|                | `Mod + Shift + [0–9]`           | Move focused container to workspace N               |
|                | `Mod + Tab`                     | Switch to previous workspace                        |
| **Screenshots**| `Print`                         | Take a screenshot (`grim`/`swappy` integration)     |
|                | `Shift + Print`                 | Select area for screenshot                          |
|                | `Ctrl + Print`                  | Copy screenshot to clipboard (`wl-copy`)            |
| **General**    | `Mod + Shift + q`               | Kill focused window                                 |
|                | `Mod + Shift + c`               | Reload sway configuration                           |
|                | `Mod + Shift + e`               | Exit sway                                           |
|                | `Mod + ?`                       | Show help (if configured)                           |


## NetRW File Manager in Vim

| Key/Command     | Action                                                 |
|-------------------|----------------------------------------------------------------------|
| `:Explore`        | Open netrw in the current window                                     |
| `:Ex`             | Shorthand for `:Explore`                                             |
| `:Sex`            | Open netrw in a horizontal split                                     |
| `:Vex`            | Open netrw in a vertical split                                       |
| `:Tex`            | Open netrw in a new tab                                              |
| `vim .`           | Open Vim with netrw in the current directory                         |
| `vim path/`       | Open Vim with netrw in a specific directory                          |
| `Enter`           | Open file or enter directory                                         |
| `-`               | Go up one directory                                                  |
| `gh`              | Toggle hidden files                                                  |
| `~`               | Go to home directory                                                 |
| `u`               | Go to previous directory                                             |
| `U`               | Go forward to next directory (after `u`)                             |
| `C`               | Set current dir as the browsing root                                 |
| `P`               | Go to parent of the browsing root                                    |
| `%`               | Create a new file                                                    |
| `d`               | Create a new directory                                               |
| `D`               | Delete selected file or directory                                    |
| `R`               | Rename file                                                          |
| `m`               | Mark file for operation (copy/move/delete)                           |
| `mc`              | Copy marked files                                                    |
| `mm`              | Move marked files                                                    |
| `md`              | Delete marked files                                                  |
| `mt`              | Tag current file for operation                                       |
| `p`               | Toggle preview window                                                |
| `:Rexplore`       | Return to previous netrw buffer                                      |


## fzf 


| Shortcut           | Action                                                                 |
|--------------------|----------------------------------------------------------------------|
| `CTRL-J` / `↓`     | Move cursor **down** one line                                         |
| `CTRL-K` / `↑`     | Move cursor **up** one line                                           |
| `CTRL-D`           | Move cursor **half-page down**                                        |
| `CTRL-U`           | Move cursor **half-page up**                                          |
| `CTRL-B`           | Move cursor **full-page up**                                          |
| `CTRL-F`           | Move cursor **full-page down**                                        |
| `TAB`              | Toggle selection of current item and move cursor **down**             |
| `Shift-TAB`        | Toggle selection of current item and move cursor **up**               |
| `CTRL-A`           | Select all items                                                     |
| `CTRL-T`           | Open **fzf** on file paths (useful inside the shell)                  |
| `CTRL-R`           | Open **fzf** on shell command history                                 |
| `CTRL-/`           | Toggle **preview window**                                             |
| `CTRL-Y`           | Copy current selection to system clipboard (when integrated)          |
| `CTRL-Q`           | Push selected items to the quickfix list (in Vim integration)         |
| `ESC`              | Cancel and exit without making a selection                            |
| `Enter`            | Accept current item (or all selected items if multi-select is active) |


### Notes
- `TAB` and `Shift-TAB` are key for **multi-select mode** (triggered with `fzf -m`).
- Some bindings like `CTRL-Y` or `CTRL-Q` depend on your shell/editor integration.

## Oil


| Shortcut | Action                                                                 |
|----------|---------------------------------------------------------------------------|
| `g?`     | Show a popup with this cheat sheet contents                               |
| `<CR>`   | Open the entry under the cursor                                           |
| `<C-p>`  | Open the entry under the cursor in a preview window, or close it if open  |
| `<C-s>`  | Open the entry under the cursor in a vertical split window                |
| `<C-h>`  | Open the entry under the cursor in a horizontal split window              |
| `<C-t>`  | Open the entry under the cursor in a new tab                              |
| `<C-l>`  | Refresh current directory list (:e! also works)                           |
| `<C-c>`  | Close Oil and restore original buffer                                     |
| `g.`     | Toggle hidden files and directories (including ../ parent entry)          |
| `g\`     | Jump to and from the trash for the current directory                      |
| `-`      | Navigate to the parent path                                               |
| `_`      | Open Oil at Neovim’s current working directory                            |
| `` ` ``  | Runs :cd to change cwd to the current Oil directory                       |
| `~`      | Show the current working directory (cwd)                                  |
| `gx`     | Open the entry under the cursor in an external program                    |
| `gs`     | Opens a popup for changing the sort order                                 |

