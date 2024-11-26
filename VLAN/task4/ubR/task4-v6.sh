#!/bin/sh
echo "Default routes"
ip route flush all
echo "Default NICs"
rm /etc/network/interfaces
touch /etc/network/interfaces
echo "auto enp0s3" >> /etc/network/interfaces
echo "iface enp0s3 inet dhcp" >> /etc/network/interfaces
echo "auto enp0s8" >> /etc/network/interfaces
echo "iface enp0s8 inet dhcp" >> /etc/network/interfaces
echo "auto lo" >> /etc/network/interfaces
echo "iface lo inet loopback" >> /etc/network/interfaces
echo "Default iptables rules"
iptables -F
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -t mangle -F
iptables -t mangle -X
iptables -P INPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -P OUTPUT ACCEPT

echo "auto vlan10" >> /etc/network/interfaces
echo "iface vlan10 inet static" >> /etc/network/interfaces
echo "address 18.23.14.0" >> /etc/network/interfaces
echo "netmask 255.255.255.128" >> /etc/network/interfaces
echo "vlan_raw_device enp0s3" >> /etc/network/interfaces

echo "auto vlan1003" >> /etc/network/interfaces
echo "iface vlavlan1003n202 inet static" >> /etc/network/interfaces
echo "address 118.23.14.123" >> /etc/network/interfaces
echo "netmask 255.255.255.0" >> /etc/network/interfaces
echo "vlan-raw-device enp0s8" >> /etc/network/interfaces


echo "Rebooting"
reboot
