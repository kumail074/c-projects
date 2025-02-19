from scapy.layers.inet6 import IPv6
from scapy.layers.inet6 import ICMPv6ND_NS, ICMPv6ND_RA, ICMPv6NDOptMTU
from scapy.layers.dns import DNS
from scapy.layers.l2 import ARP
from scapy.sendrecv import sniff
from collections import defaultdict
import logging
from playsound import playsound
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

# Global variables
traffic_counter = defaultdict(int)
dns_queries = defaultdict(list)
flagged_packets = []
mac_ip_mapping = defaultdict(list)  # To track MAC and IP mappings for MITM detection

# Set up logging configuration
logging.basicConfig(
    filename='ipv6_security_toolkit.log',  # Log file name
    level=logging.INFO,  # Set log level to INFO to capture detailed logs
    format='%(asctime)s - %(levelname)s - %(message)s',  # Log format with timestamp, level, and message
)

# Create a logger object
logger = logging.getLogger()

def log_event(message):
    """
    Logs informational messages for packet analysis.
    """
    logger.info(message)

def alert_event(message):
    """
    Triggers an alert when a suspicious event is detected, logs the event, and sends notifications.
    """
    logger.warning(message)  # Log the warning in the log file with timestamp
    flagged_packets.append(message)  # Store flagged events for review
    send_email_alert("IPv6 Security Alert", message)
    playsound("alerts/alert.mp3")  # Play sound when alert is triggered

class PacketProcessor:
    def __init__(self):
        self.traffic_counter = defaultdict(int)
        self.dns_queries = defaultdict(list)
        self.mac_ip_mapping = defaultdict(list)

    def process_packet(self, packet):
        if IPv6 in packet:
            self.handle_ipv6_packet(packet)
        else:
            log_event(f"Non-IPv6 Packet Captured: {packet.summary()}")

    def handle_ipv6_packet(self, packet):
        src_ip = packet[IPv6].src
        dst_ip = packet[IPv6].dst

        # IPv6 Header Analysis
        if packet[IPv6].version != 6:
            alert_event(f"Malformed IPv6 Packet Detected: {packet.summary()}")

        # Fragmentation Detection
        if packet.haslayer('IPv6ExtHdrFragment'):
            log_event(f"Fragmented IPv6 Packet Detected: {packet.summary()}")

        # NDP Inspection
        if ICMPv6ND_NS in packet:
            log_event(f"NDP Solicitation Detected from {src_ip}")

        # Router Advertisement Spoofing Detection
        if ICMPv6ND_RA in packet:
            log_event(f"Router Advertisement from {src_ip}")

        # MTU Option Validation
        if ICMPv6NDOptMTU in packet:
            mtu = packet[ICMPv6NDOptMTU].mtu
            if mtu < 1280:
                alert_event(f"Invalid MTU Detected: {mtu} from {src_ip}")

        # DNS Spoofing Detection
        if DNS in packet and packet[DNS].qr == 1:
            self.dns_queries[packet[DNS].qd.qname].append(packet[DNS].an.rdata)
            if len(set(self.dns_queries[packet[DNS].qd.qname])) > 1:
                alert_event(f"DNS Spoofing Detected: {packet.summary()}")

        # Denial of Service (DoS) Detection
        self.traffic_counter[src_ip] += 1
        if self.traffic_counter[src_ip] > 100:
            alert_event(f"Potential DoS Attack from {src_ip} (Traffic: {self.traffic_counter[src_ip]})")

        # MITM Detection: Check for duplicate IP-MAC mapping
        if src_ip in self.mac_ip_mapping and packet.src not in self.mac_ip_mapping[src_ip]:
            log_event(f"MITM Attack Detected: Source IP {src_ip}, Destination IP {dst_ip}, Packet: {packet.summary()}")

        # ARP Spoofing Detection: NDP/ARP inspection
        if ARP in packet:
            if packet.op == 2:  # ARP reply
                if packet.psrc != src_ip:  # Mismatch in source IP
                    log_event(f"ARP Spoofing Detected: IP {src_ip}, MAC {packet.hwsrc}, Packet: {packet.summary()}")
        elif ICMPv6ND_NS in packet:
            if src_ip in self.mac_ip_mapping and packet.src not in self.mac_ip_mapping[src_ip]:
                log_event(f"ARP Spoofing Detected: IP {src_ip}, MAC {packet.src}, Packet: {packet.summary()}")

class EmailNotifier:
    @staticmethod
    def send_email_alert(subject, message):
        sender_email = "your_email@example.com"
        receiver_email = "alert_email@example.com"
        password = "your_email_password"

        msg = MIMEMultipart()
        msg['From'] = sender_email
        msg['To'] = receiver_email
        msg['Subject'] = subject

        body = MIMEText(message, 'plain')
        msg.attach(body)

        try:
            server = smtplib.SMTP('smtp.gmail.com', 587)
            server.starttls()
            server.login(sender_email, password)
            server.sendmail(sender_email, receiver_email, msg.as_string())
            server.quit()
            print(f"Email Alert Sent: {subject} - {message}")
        except Exception as e:
            print(f"Error sending email: {str(e)}")

# Sniffing the network for packets (IPv6 only)
def start_packet_sniffer():
    sniff(prn=process_packet, filter="ip6", store=0)  # Sniff IPv6 packets only

# Sample usage:
if __name__ == "__main__":
    packet_processor = PacketProcessor()
    sniff(prn=packet_processor.process_packet, filter="ip6", store=0)  # Start sniffing IPv6 packets
