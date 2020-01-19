#pragma once

using namespace std;


typedef struct Data {
    uint32_t packets = 0;
    uint32_t bytes = 0;
    uint32_t tx_packets = 0;
    uint32_t tx_bytes = 0;
    uint32_t rx_packets = 0;
    uint32_t rx_bytes = 0;
}data;


template <typename T>
class Statistic {
};


template <typename T>
class Endpoints : public Statistic<T> {
private:
    map<T, Data> stat;
public:
    void tx(T t, int bytes) {
        auto& data = stat[t];
        data.packets += 1;
        data.bytes += bytes;
        data.tx_packets += 1;
        data.tx_bytes += bytes;
    }

    void rx(T t, int bytes) {
        auto& data = stat[t];
        data.packets += 1;
        data.bytes += bytes;
        data.rx_packets += 1;
        data.rx_bytes += bytes;
    }

    friend ostream& operator<<(ostream& os, const Endpoints<T>& m) {
        os << "弛      Address      弛   Packet   弛    Bytes   弛 Tx Packets 弛  Tx Bytes  弛 Rx Packets 弛  Rx Bytes  弛" << endl;
        os << "戍式式式式式式式式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式扣" << endl;
        for (auto a : m.stat) {
            auto& d = a.second;
            os << "弛" << setw(18) << a.first << " 弛 " << setw(10) << d.packets << " 弛 " << setw(10) << d.bytes << " 弛 " << setw(10) << d.tx_packets << " 弛 " << setw(10) << d.tx_bytes << " 弛 " << setw(10) << d.rx_packets << " 弛 " << setw(10) << d.rx_bytes << " 弛" << endl;
        }
        return os;
    }
};


template <typename T>
class Conversations : public Statistic<T> {
private:
    map<T, Data> stat;

public:
    void packet(T addr, int bytes) {
        if (addr.second < addr.first) {
            Data& data = stat[make_pair(addr.second, addr.first)];
            data.packets += 1;
            data.bytes += bytes;
            data.rx_packets += 1;
            data.rx_bytes += bytes;
        }
        else {
            Data& data = stat[addr];
            data.packets += 1;
            data.bytes += bytes;
            data.tx_packets += 1;
            data.tx_bytes += bytes;
        }
    }

    friend ostream& operator<<(ostream& os, const Conversations<T>& m) {
        os << "弛     Address A     弛     Address B     弛   Packet   弛    Bytes   弛Packets A->B弛 Bytes A->B 弛Packets B->A弛 Bytes B->A 弛" << endl;
        os << "戍式式式式式式式式式式式式式式式式式式式托式式式式式式式式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式托式式式式式式式式式式式式扣" << endl;
        for (auto a : m.stat) {
            auto& d = a.second;
            os << "弛" << setw(18) << a.first.first << " 弛" << setw(18) << a.first.second << " 弛 " << setw(10) << d.packets << " 弛 " << setw(10) << d.bytes << " 弛 " << setw(10) << d.tx_packets << " 弛 " << setw(10) << d.tx_bytes << " 弛 " << setw(10) << d.rx_packets << " 弛 " << setw(10) << d.rx_bytes << " 弛" << endl;
        }
        return os;
    }
};