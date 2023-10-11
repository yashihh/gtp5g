struct Type{
    unsigned char type; 
    unsigned char reserved;
}__attribute__ ((packed));

struct Data{
    unsigned long secondsField:48 ; 
    unsigned int nanosecondsField;
}__attribute__ ((packed));

struct Organization_Subtype{
    unsigned char reserved; 
    unsigned char subtype;
    unsigned char spare;
}__attribute__ ((packed));

struct ptp_suffix {
    struct Type type;
    unsigned short length;
    unsigned int organization_Id:24 ;
    struct Organization_Subtype subtype;
    struct Data data;
} __attribute__ ((packed));