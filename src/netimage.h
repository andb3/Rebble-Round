#ifndef NET_IMAGE_H
#define NET_IMAGE_H

#include <pebble.h>

/* The key used to transmit image data. Contains byte array. */
//hexadecimal of decimal in package.json
#define NETIMAGE_DATA 0x696d6700 /* "img" */
/* The key used to start a new image transmission. Contains uint32 size */
#define NETIMAGE_BEGIN NETIMAGE_DATA + 1
/* The key used to finalize an image transmission. Data not defined. */
#define NETIMAGE_END NETIMAGE_DATA + 2

/* The key used to tell the JS how big chunks should be */
#define NETIMAGE_CHUNK_SIZE NETIMAGE_DATA + 3
/* The key used to request a PBI */
#define NETIMAGE_URL NETIMAGE_DATA + 4

#define ZOOMIMAGE_BEGIN NETIMAGE_DATA + 5
#define ZOOMIMAGE_DATA NETIMAGE_DATA + 6
#define ZOOMIMAGE_END NETIMAGE_DATA + 7



typedef void (*NetImageCallback)(GBitmap *image);

typedef struct
{
	/* size of the data buffer allocated */
	uint32_t length;
	/* buffer of data that will contain the actual image */
	uint8_t *data;
	/* Next byte to write */
	uint32_t index;
	/* Callback to call when we are done loading the image */
	NetImageCallback callback;
} NetImageContext;

NetImageContext *netimage_create_context(NetImageCallback callback);

void netimage_destroy_context(NetImageContext *ctx);

void netimage_request(int index);

void netimage_receive(DictionaryIterator *iter);

#endif
