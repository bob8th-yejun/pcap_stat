#pragma once


#pragma pack(push,1)
typedef struct Ethernet {
    uint8_t dst[6];
    uint8_t src[6];
    uint16_t type;
}Ethernet;


typedef struct Ipv4 {
    uint8_t vhl;
    uint8_t tos;
    uint16_t len;
    uint16_t id;
    uint16_t flag;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t checksum;
    uint32_t src;
    uint32_t dst;
}Ipv4;


typedef struct Packet {
    Ethernet ethernet;
    Ipv4 ip;
}Packet;
#pragma pack(pop)