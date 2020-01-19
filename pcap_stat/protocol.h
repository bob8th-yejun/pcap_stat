#pragma once

using namespace std;


class Mac
{
private:
	uint8_t mac[6];

public:
	Mac(uint8_t* mac) {
		memcpy(this->mac, mac, 6);
	}

	bool operator <(const Mac& m) const {
		return memcmp(mac, m.mac, 6) < 0;
	}

	friend ostream& operator<<(ostream& os, const Mac& m) {
		char str[18];
		sprintf(str, "%02X:%02X:%02X:%02X:%02X:%02X", m.mac[0], m.mac[1], m.mac[2], m.mac[3], m.mac[4], m.mac[5]);
		os << str;
		return os;
	}
};


class Ip
{
private:
	uint32_t ip;
public:
	Ip(uint32_t ip) {
		this->ip = ip;
	}
	bool operator <(const Ip& i) const {
		return ip < i.ip;
	}
	friend ostream& operator<<(ostream& os, const Ip& i) {
		/*os << setw(3) << (i.ip & 0xFF) << '.'
			<< setw(3) << ((i.ip >> 8) & 0xFF) << '.'
			<< setw(3) << ((i.ip >> 16) & 0xFF) << '.'
			<< setw(3) << ((i.ip >> 24) & 0xFF);*/

		char str[16];
		sprintf(str, "%3d.%3d.%3d.%3d", (i.ip & 0xFF), ((i.ip >> 8) & 0xFF), ((i.ip >> 16) & 0xFF), ((i.ip >> 24) & 0xFF));
		os << str;
		return os;
	}
};
