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

echo "auto vlan111" >> /etc/network/interfaces
echo "iface vlan111 inet static" >> /etc/network/interfaces
echo "address 120.178.137.5" >> /etc/network/interfaces
echo "netmask 255.255.240.0" >> /etc/network/interfaces
echo "vlan_raw_device enp0s3" >> /etc/network/interfaces

echo "auto vlan1103" >> /etc/network/interfaces
echo "iface vlan1103 inet static" >> /etc/network/interfaces
echo "address 10.178.190.167" >> /etc/network/interfaces
echo "netmask 255.252.0.0" >> /etc/network/interfaces
echo "vlan_raw_device enp0s0" >> /etc/network/interfaces


echo "Rebooting"
reboot
