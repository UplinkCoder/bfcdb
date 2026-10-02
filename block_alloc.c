// block allotor
#include <stdint.h>
#include <stdlib.h>
extern uint32_t crc32c(uint32_t initial, const uint32_t* alignedData, uint32_t sz);

#define BLOCK_SIZE 4096

typedef struct block_header_t {
        uint32_t Checksum_Xor;
        uint32_t Checksum_Crc32c;
} block_header_t;

#define CONTENT_SIZE (BLOCK_SIZE - sizeof (block_header_t))

typedef struct block_t {
    union {
	struct {
            _Alignas(32) block_header_t Header;
            uint8_t Data[CONTENT_SIZE];
        };
	uint8_t Bytes[BLOCK_SIZE];
    };
} block_t ;

block_t XorBlock(block_t *restrict a,  block_t *restrict b) {
    uint32_t aXorSum = 0x10101010;
    uint32_t bXorSum = 0x10101010;

    _Alignas(32) block_t result;

    {
     	uint32_t i = 0;
        for(i = 0; i < CONTENT_SIZE; i++)
        {
            aXorSum ^= a->Data[i];
            bXorSum ^= b->Data[i];
        }
    }

    {
     	uint32_t i = 0;
        for(i = 0; i < BLOCK_SIZE; i++)
        {
            result.Bytes[i] = a->Bytes[i] ^ b->Bytes[i];
        }
    }
    if ( (a->Header.Checksum_Xor != aXorSum) | (b->Header.Checksum_Xor != bXorSum) )
    {
     	abort();
    }

    result.Header.Checksum_Crc32c = crc32c(~0, (uint32_t*)result.Data, CONTENT_SIZE);
    return result;
}
