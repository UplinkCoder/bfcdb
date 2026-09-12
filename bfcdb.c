// magic allows you to detect the endianess because it's either
// [ 'B', 'f', 'c', 'D' 'b', '\a', '\0', '\0' ]
// or
// ['f', 'B', 'D', 'c', '\a', 'b', '\0', '\0']
//     0xbfcdb0

typedef struct BfcDb_Header {
    unsigned char Magic[3]; // 0xbfcdb0
    unsigned char Version;
    unsigned char StartOfRecords[4];
    unsigned char StartOfTypedescriptors[4];
} BfcDb_Header;

BfcDb_t* BfcDb_Open(const char* filename)
{
    BfcDb_Header *header;
    unsigned int descriptorCount;
}
