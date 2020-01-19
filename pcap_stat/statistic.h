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
        os << "��      Address      ��   Packet   ��    Bytes   �� Tx Packets ��  Tx Bytes  �� Rx Packets ��  Rx Bytes  ��" << endl;
        os << "������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
        for (auto a : m.stat) {
            auto& d = a.second;
            os << "��" << setw(18) << a.first << " �� " << setw(10) << d.packets << " �� " << setw(10) << d.bytes << " �� " << setw(10) << d.tx_packets << " �� " << setw(10) << d.tx_bytes << " �� " << setw(10) << d.rx_packets << " �� " << setw(10) << d.rx_bytes << " ��" << endl;
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
        os << "��     Address A     ��     Address B     ��   Packet   ��    Bytes   ��Packets A->B�� Bytes A->B ��Packets B->A�� Bytes B->A ��" << endl;
        os << "����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������" << endl;
        for (auto a : m.stat) {
            auto& d = a.second;
            os << "��" << setw(18) << a.first.first << " ��" << setw(18) << a.first.second << " �� " << setw(10) << d.packets << " �� " << setw(10) << d.bytes << " �� " << setw(10) << d.tx_packets << " �� " << setw(10) << d.tx_bytes << " �� " << setw(10) << d.rx_packets << " �� " << setw(10) << d.rx_bytes << " ��" << endl;
        }
        return os;
    }
};