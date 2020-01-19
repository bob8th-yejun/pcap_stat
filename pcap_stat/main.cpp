#include <pcap.h>
#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <map>

#include "packet.h"
#include "protocol.h"
#include "statistic.h"

using namespace std;


int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "pcap_stat <pcap file>" << endl;
		cout << "pcap 파일 경로가 인자로 필요합니다" << endl;
		return -1;
	}

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* handle = pcap_open_offline(argv[1], errbuf);
	if (!handle) {
		cout << "pcap open error: " << errbuf << endl;
		return -1;
	}

	Endpoints<Mac> ep_mac;
	Endpoints<Ip> ep_ip;
	Conversations<pair<Mac, Mac>> conv_mac;
	Conversations<pair<Ip, Ip>> conv_ip;

	while (true)
	{
		struct pcap_pkthdr* header;
		const u_char* raw;
		int res = pcap_next_ex(handle, &header, &raw);
		if (res < 0) break;
		Packet* packet = (Packet*)raw;

		ep_mac.tx(Mac(packet->ethernet.src), header->len);
		ep_mac.rx(Mac(packet->ethernet.dst), header->len);
		conv_mac.packet(make_pair(Mac(packet->ethernet.src), Mac(packet->ethernet.dst)), header->len);

		if (ntohs(packet->ethernet.type) != 0x0800) continue;
		ep_ip.tx(Ip(packet->ip.src), header->len);
		ep_ip.rx(Ip(packet->ip.dst), header->len);
		conv_ip.packet(make_pair(Ip(packet->ip.src), Ip(packet->ip.dst)), header->len);
	}

	cout << ep_mac << endl;
	cout << ep_ip << endl;
	cout << conv_mac << endl;
	cout << conv_ip << endl;
	return 0;
}