// SPDX-License-Identifier: GPL-2.0-or-later
/*
 *  PCIe Switch Framework driver
 *
 */
#ifndef _PCISW_H
#define _PCISW_H

#include <stdint.h>

#define PCISW_RW_PAYLOAD_IN_SIZE	1024 * 1024 /* Support a maximum of 1MB of data in a single request */
#define PCISW_RW_PAYLOAD_OUT_SIZE	1024

enum sw_vendors {
	NONE = 0,
	SWITCHTECH,
	BROADCOM,
	RESERVED = 255
};

/*
 * struct swdev_write -	Representation of write command
 *			received from user space
 * @type:		Type Identifies the
 * @rsvd:		Reserved
 * @seq_num:	unique seq number from user space
 * @cmd:		Opcode/Command
 * @data_len:	Data length of Request/data_in
 * @data_in:	Command/Data to process
 */
typedef struct swdev_write {
	uint8_t type;
	uint8_t rsvd;
	uint16_t seq_num;
	uint32_t cmd;
	uint32_t data_len;
} __attribute__ ((packed)) swdev_write_t;

#define PCISW_WRITE_HEADER_SIZE	(sizeof(swdev_write_t))
#define PCISW_WRITE_MAX_SIZE	(sizeof(swdev_write_t) + PCISW_RW_PAYLOAD_IN_SIZE)

#define pcisw_write_dtata_in(swdev_write) ((void *)((char *)swdev_write + PCISW_WRITE_HEADER_SIZE))

/*
 * struct swdev_read -	Representation of Read command
 *			received from user space
 * @seq_num:	unique seq number from user space
 * @data_len:	Data length of the Response/data_out
 * @Status:		Write Command Status
 * @data_out:	Data out buffer
 */
typedef struct swdev_read {
	uint16_t seq_num;
	uint32_t status;
	uint32_t data_len;
	unsigned char data_out[PCISW_RW_PAYLOAD_OUT_SIZE];
} __attribute__ ((packed)) swdev_read_t;

#define PCISW_READ_HEADER_SIZE	(sizeof(swdev_read_t) - PCISW_RW_PAYLOAD_OUT_SIZE)
#define PCISW_READ_MAX_SIZE	(sizeof(swdev_read_t))

#endif
