/**
 * @file ptp_suffix.h
 */
// struct Type{
//     unsigned char type; 
//     unsigned char reserved;
// }__attribute__ ((packed));

struct Data{
    uint16_t   seconds_msb; /* 16 bits + */
	uint32_t   seconds_lsb; /* 32 bits = 48 bits*/
	UInteger32 nanoseconds; 
}__attribute__ ((packed));

#define TLV_ORGANIZATION_EXTENSION			0x0003

// struct Organization_Subtype{
//     unsigned char reserved; 
//     unsigned char subtype;
//     unsigned char spare;
// }__attribute__ ((packed));

struct ptp_suffix {
    Enumeration16   type; // 2 bytes
    unsigned short  length; // 2 bytes
    Octet           organization_Id[3] ; // 3 bytes
    Octet           subtype[3]; // 3 bytes
    struct Data     data; // 10 bytes
} __attribute__ ((packed));