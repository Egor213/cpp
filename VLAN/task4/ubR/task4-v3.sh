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

echo "auto vlan1011" >> /etc/network/interfaces
echo "iface vlan1011 inet static" >> /etc/network/interfaces
echo "address 1.1.20.3" >> /etc/network/interfaces
echo "netmask 255.128.0.0" >> /etc/network/interfaces
echo "vlan_raw_device enp0s3" >> /etc/network/interfaces

echo "auto vlan10040" >> /etc/network/interfaces
echo "iface vlan10040 inet static" >> /etc/network/interfaces
echo "address 11.120.255.17" >> /etc/network/interfaces
echo "netmask 255.255.224.0" >> /etc/network/interfaces
echo "vlan_raw_device enp0s8" >> /etc/network/interfaces


echo "Rebooting"
reboot
